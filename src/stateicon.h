#pragma once

#include <libappindicator/app-indicator.h>
#include <string>
#include "infowin.h"
#include <gtkmm.h>
#include "tools.h"

class StateIcon
{
  std::string logfilePath = "/var/log/btrbk.log";
  std::string iconPath = getInstallDir() + "/icons/";
  AppIndicator *indicator;
  GtkWidget *indicator_menu;
  InfoWin win;
  static void info_clicked(GtkWidget *widget, gpointer data);
  static void quit_clicked(GtkWidget *widget, gpointer data);
  void newMenuItem(std::string title, GCallback c_handler);
public:
  StateIcon(std::string logfilePath = "");
  enum IconType {ok, err, running, def};
  void updateIcon(IconType t);
  InfoWin& getInfoWin();
};
