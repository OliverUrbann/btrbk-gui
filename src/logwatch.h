#pragma once

#include <string>
#include "stateicon.h"
#include "logfile.h"
#include <thread>
#include <gtk/gtk.h>

class LogWatch
{
    std::string logfilePath;
    void notifyMainLoop();
    void watch_logfile();
    StateIcon icon;
    Logfile l;
    GMainContext *context;

    void updateIcon();
    static gboolean logfileChanged(gpointer user_data);
    void updateLogView();
    void updateStatus();


public:
    LogWatch(std::string, GMainContext*);
    std::thread runWatchThread();
};