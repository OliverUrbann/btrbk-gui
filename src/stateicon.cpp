#include "stateicon.h"
#include "actions.h"

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

  newMenuItem("Info", NULL, G_CALLBACK (info_clicked));
  GtkWidget *actions_menu = newMenuItem("Actions", NULL);
  run_menu = newMenuItem("Run", actions_menu, G_CALLBACK (run_clicked));
  resume_menu = newMenuItem("Resume", actions_menu, G_CALLBACK (resume_clicked));
  clean_menu = newMenuItem("Clean", actions_menu, G_CALLBACK (clean_clicked));
  stop_menu = newMenuItem("Stop", actions_menu, G_CALLBACK (stop_clicked));
  newMenuItem("Quit", NULL, G_CALLBACK (quit_clicked));

  app_indicator_set_status (indicator, APP_INDICATOR_STATUS_ACTIVE);
  app_indicator_set_icon_theme_path(indicator, iconPath.c_str());
  app_indicator_set_icon (indicator, "backup");
  app_indicator_set_menu (indicator, GTK_MENU (indicator_menu));
}

// Adding new item to the menu. parent should NULL if the new item is not a submenu.
// c_handler is NULL in case this is the parent for new submenus. Returns
// the new menu to use it later as parent or the new item if it is not a submenu.
GtkWidget * StateIcon::newMenuItem(std::string title, GtkWidget *parent, GCallback c_handler)
{
  GtkWidget *item, *submenu = NULL, *ret = NULL;
  item = gtk_menu_item_new_with_label (title.c_str());

  // In case there is nothing to do when this item is clicked, we assume this is a submenu
  if (c_handler != NULL)
  {
    g_signal_connect (item, "activate", G_CALLBACK (c_handler), this);
    ret = item;
  }
  else
  {
    submenu = gtk_menu_new();
    ret = submenu;
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), submenu);
  }

  if (parent == NULL)
  {
    parent = indicator_menu;
  }

  gtk_menu_shell_append (GTK_MENU_SHELL (parent), item);
  gtk_widget_show(item);
  app_indicator_set_secondary_activate_target(indicator, item);

  return ret;
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

void StateIcon::stop_clicked(GtkWidget *widget, gpointer data)
{
  Actions::stop();
}

void StateIcon::clean_clicked(GtkWidget *widget, gpointer data)
{
  Actions::clean();
}

void StateIcon::resume_clicked(GtkWidget *widget, gpointer data)
{
  Actions::resume();
}

void StateIcon::run_clicked(GtkWidget *widget, gpointer data)
{
  Actions::run();
}

void StateIcon::updateIcon(IconType t)
{
  switch(t)
  {
  case IconType::ok:
    app_indicator_set_icon (indicator, "backup-ok");
    updateMenuSensitivity(false);
    break;
  case IconType::err:
    app_indicator_set_icon (indicator, "backup-err");
    updateMenuSensitivity(false);
    break;
  case IconType::running:
    app_indicator_set_icon (indicator, "backup-running");
    updateMenuSensitivity(true);
    break;
  default:  
    app_indicator_set_icon (indicator, "backup");
    updateMenuSensitivity(true);
    break;
  }
}

void StateIcon::updateMenuSensitivity(bool running)
{
  gtk_widget_set_sensitive (run_menu, !running);
  gtk_widget_set_sensitive (stop_menu, running);
  gtk_widget_set_sensitive (resume_menu, !running);
}

InfoWin& StateIcon::getInfoWin()
{
  return win;
}
