#pragma once

#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/textview.h>
#include <gtkmm/label.h>
#include "logfile.h"

class InfoWin : public Gtk::ApplicationWindow
{
    Gtk::Box *cont;
    Glib::RefPtr<Gtk::Button> display_btn;
    Glib::RefPtr<Gtk::TextView> logView;
    Glib::RefPtr<Gtk::Builder> ui;
    Glib::RefPtr<Gtk::Label> label;
    Glib::RefPtr<Gtk::Label> status;
    bool visible;
    std::string logTxt;

    bool on_delete_event(GdkEventAny *);
public:
    InfoWin();
    void addLogMsg(const std::string);
    void clearLog();
    void showWin(bool visible);
    bool isVisible();
    void updateStatus(std::string label, std::string status);
};