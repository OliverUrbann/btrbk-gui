#include "logwatch.h"
#include <string>
#include <gtk/gtk.h>

// https://developer.ibm.com/tutorials/l-ubuntu-inotify/
// https://www.bogotobogo.com/cplusplus/C11/1_C11_creating_thread.php
// https://www.thegeekstuff.com/2010/04/inotify-c-program-example/

// This complete program
// https://wiki.ubuntu.com/mhall119/devportal/indicators


int main (int argc, char **argv)
{
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(
      argc, argv, 
      "org.esd.btrbkgui"
  );
  
  std::string logfilePath = "/var/log/btrbk.log";
  if (argc >= 2)
    logfilePath = argv[1];

  GMainContext *context = g_main_context_default();
  LogWatch lw(logfilePath, context);
  lw.runWatchThread();
  app->hold();
  int ret = app->run();
  lw.join();

  return ret;
}