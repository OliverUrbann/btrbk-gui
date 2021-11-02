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
  GtkWidget *indicator_menu, *run_menu, *resume_menu, *stop_menu;
  InfoWin win;
  static void info_clicked(GtkWidget *widget, gpointer data);
  static void resume_clicked(GtkWidget *widget, gpointer data);
  static void quit_clicked(GtkWidget *widget, gpointer data);
  static void stop_clicked(GtkWidget *widget, gpointer data);
  static void run_clicked(GtkWidget *widget, gpointer data);
  GtkWidget * newMenuItem(std::string title, GtkWidget *parent, GCallback c_handler = NULL);
  void updateMenuSensitivity(bool running);
public:
  StateIcon(std::string logfilePath = "");
  enum IconType {ok, err, running, def};
  void updateIcon(IconType t);
  InfoWin& getInfoWin();
};
