#pragma once

#include <string>
#include "stateicon.h"
#include "logfile.h"
#include <thread>
#include <gtk/gtk.h>

class WatchThreads
{
    std::string logfilePath;
    std::string btrbkPath = "/usr/sbin/btrbk";
    StateIcon icon;
    Logfile l;
    GMainContext *context;
    bool procRunning = false;
    long last_mod = 0;
    std::thread fileThread, procThread;

    void updateIcon();
    static gboolean stateChanged(gpointer user_data);
    void updateLogView();
    void updateStatus();
    void checkProcState();
    void watch_proc();
    void notifyMainLoop();
    void watch_logfile();

public:
    WatchThreads(std::string, GMainContext*);
    void runWatchThreads();
    void join();
};