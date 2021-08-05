#include "infowin.h"
#include "tools.h"

// https://riptutorial.com/gtk3/example/19806/-cplusplus--using-gtk--builder-in-gtkmm
InfoWin::InfoWin() : 
  ui{Gtk::Builder::create_from_file((getInstallDir() + "/infowin.glade").c_str())}
{
  
  if(ui)
  {
    ui->get_widget<Gtk::Box>("box", cont);
    logView = Glib::RefPtr<Gtk::TextView>::cast_dynamic(
      ui->get_object("LogView"));
    label = Glib::RefPtr<Gtk::Label>::cast_dynamic(
      ui->get_object("StatusLabel"));
    status = Glib::RefPtr<Gtk::Label>::cast_dynamic(
      ui->get_object("Status"));
    if (cont)
      add(*cont);
  }

  set_title("Btrbk GUI Info");
  set_default_size(600, 400);
}

bool InfoWin::on_delete_event(GdkEventAny *a)
{
  showWin(false);
  return TRUE;
}

void InfoWin::showWin(bool visible)
{
  if (visible)
  {
    set_visible();
    this->visible = true;
  }
  else
  {
    hide();
    this->visible = false;
  }   
}

bool InfoWin::isVisible()
{
  return visible;
}

void InfoWin::clearLog()
{
  logTxt = "";
}

void InfoWin::addLogMsg(const std::string m)
{
  if (!logView)
    return;

  auto buf = logView->get_buffer();
  logTxt += m;
  buf->set_text(logTxt);
  logView->set_buffer(buf);
}

void InfoWin::updateStatus(std::string label, std::string status)
{
  this->status->set_text(status);
  this->label->set_text(label);
}