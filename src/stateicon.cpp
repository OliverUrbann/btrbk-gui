#include "stateicon.h"

StateIcon::StateIcon(std::string logfilePath)
{
  if (logfilePath != "")
    this->logfilePath = logfilePath;
  
  // https://cpp.hotexamples.com/examples/-/-/app_indicator_set_icon_theme_path/cpp-app_indicator_set_icon_theme_path-function-examples.html
  // https://github.com/3v1n0/indicators-examples-snaps/blob/master/gtk3-appindicator/simple-client.c
  indicator = app_indicator_new ("Btrbk-GUI",
                                 "",
                                 APP_INDICATOR_CATEGORY_APPLICATION_STATUS);
  indicator_menu = gtk_menu_new ();

  newMenuItem("Info", G_CALLBACK (info_clicked));
  newMenuItem("Quit", G_CALLBACK (quit_clicked));

  app_indicator_set_status (indicator, APP_INDICATOR_STATUS_ACTIVE);
  app_indicator_set_icon_theme_path(indicator, iconPath.c_str());
  app_indicator_set_icon (indicator, "backup");
  app_indicator_set_menu (indicator, GTK_MENU (indicator_menu));

}

void StateIcon::newMenuItem(std::string title, GCallback c_handler)
{
  GtkWidget *item;
  item = gtk_menu_item_new_with_label (title.c_str());
  g_signal_connect (item, "activate", G_CALLBACK (c_handler), this);
  gtk_menu_shell_append (GTK_MENU_SHELL (indicator_menu), item);
  gtk_widget_show(item);
  app_indicator_set_secondary_activate_target(indicator, item);
}

void StateIcon::info_clicked(GtkWidget *widget, gpointer data)
{
  StateIcon *icon = (StateIcon*) data;
  icon->win.showWin(true);
  return;
}

void StateIcon::quit_clicked(GtkWidget *widget, gpointer data)
{
  exit(0);
}

void StateIcon::updateIcon(IconType t)
{
  switch(t)
  {
  case IconType::ok:
    app_indicator_set_icon (indicator, "backup-ok");
    break;
  case IconType::err:
    app_indicator_set_icon (indicator, "backup-err");
    break;
  case IconType::running:
    app_indicator_set_icon (indicator, "backup-running");
    break;
  default:
    app_indicator_set_icon (indicator, "backup");
    break;
  }
}

InfoWin& StateIcon::getInfoWin()
{
  return win;
}
