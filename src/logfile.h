#pragma once

#include <string>
#include <time.h>
#include <list>
#include "logmsg.h"

class Logfile
{
    std::string path;
    std::list<LogMsg> msgs;

public:
    typedef std::list<LogMsg>::const_iterator const_iterator;

    Logfile(std::string path);
    int parse();
    LogMsg getLatestMsg();
    const_iterator begin();
    const_iterator end();
};