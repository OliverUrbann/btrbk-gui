#include "logwatch.h"
#include <sys/inotify.h>


#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * (EVENT_SIZE + 16 ) )

// All following functions run in main (GUI) thread

LogWatch::LogWatch(std::string logfilePath, GMainContext *context) :
    logfilePath(logfilePath),
    l(logfilePath),
    context(context)
{

}

std::thread LogWatch::runWatchThread()
{
    return std::thread(&LogWatch::watch_logfile, this);
}

gboolean LogWatch::logfileChanged(gpointer user_data)
{
  LogWatch *lw = (LogWatch *)user_data;
  lw->l.parse();
  lw->updateIcon();
  lw->updateLogView();
  lw->updateStatus();
  return G_SOURCE_REMOVE;
}

void LogWatch::updateIcon()
{
  
  switch(l.getLatestMsg().interpretMsg())
  {
    case LogMsg::finished_success:
      icon.updateIcon(StateIcon::IconType::ok);
      break;
    case LogMsg::finished_fail:
      icon.updateIcon(StateIcon::IconType::err);
      break;
    case LogMsg::running:
      icon.updateIcon(StateIcon::IconType::running);
      break;
    default:
      icon.updateIcon(StateIcon::IconType::def);
      break;
  }
}

void LogWatch::updateStatus()
{
  std::string statusMsg, statusLabel = "Last successful run: ";
  switch(l.getLatestMsg().interpretMsg())
  {
    case LogMsg::finished_success:
      statusMsg = l.getLatestMsg().getTime();
      break;
    case LogMsg::finished_fail:
    case LogMsg::running:
      for (Logfile::const_iterator i = l.begin(); i != l.end(); i++)
      {
        if (i->interpretMsg() == LogMsg::finished_success)
        {
          statusMsg = i->getTime();
          break;
        }
      }
      break;
    default:
      statusLabel = "Unknown state!";
      statusMsg = "";
      break;
  }
  icon.getInfoWin().updateStatus(statusLabel, statusMsg);
}

void LogWatch::updateLogView()
{
  Logfile::const_iterator m = l.end();
  m--;
  icon.getInfoWin().clearLog();
  for (int i = 0; i < 100 && m != l.begin(); i++, m--)
  {
    const std::string msg = m->getTimeMsgLine();
    icon.getInfoWin().addLogMsg(msg);
  }
}

// Below all functions running in worker thread

void LogWatch::notifyMainLoop()
{
  GSource *source;
  source = g_idle_source_new();
  g_source_set_callback(source, logfileChanged, this, NULL);
  g_source_attach(source, context);
  g_source_unref(source);
}

void LogWatch::watch_logfile()
{
  int length, i = 0;
  int fd;
  int wd;
  char buffer[BUF_LEN];
  
  int dirPos = logfilePath.find_last_of("/");
  std::string logfileDir;
  if (dirPos == -1)
    logfileDir = ".";
  else
    logfileDir = logfilePath.substr(0, dirPos);

  Logfile l = Logfile(logfilePath);
  notifyMainLoop();

  fd = inotify_init();

  if ( fd < 0 ) {
    perror( "inotify_init" );
  }

  while(true)
  {
    while ((wd = inotify_add_watch( fd, logfilePath.c_str(),  IN_MODIFY)) < 0)
    {
      if (errno == ENOENT)
      {
        bool created = false;
        wd = inotify_add_watch( fd, logfileDir.c_str(), IN_CREATE);
        if (wd < 0)
        {
          perror("logfile_create");
          exit(-1);
        }
        length = read( fd, buffer, BUF_LEN );  
        if ( length < 0 )
        {
          perror( "read" );
          exit(-1);
        }  
        while ( i < length && !created) 
        {
          inotify_event* event = (inotify_event*) &buffer[ i ];
          if (event->mask & IN_CREATE)
            created = true;
          i += EVENT_SIZE + event->len;
        }
        inotify_rm_watch(fd, wd);
      }
      else
      {
        perror("watch_file");
        exit(-1);
      }
    }

    i = 0;
    length = read( fd, buffer, BUF_LEN );  

    if ( length < 0 ) {
      perror( "read" );
    }  

    while ( i < length ) {
      inotify_event* event = (inotify_event*) &buffer[ i ];
      if ( event->mask & IN_MODIFY )
        notifyMainLoop();
      i += EVENT_SIZE + event->len;
    }
  }
  inotify_rm_watch(fd, wd);
  close(fd);
}
