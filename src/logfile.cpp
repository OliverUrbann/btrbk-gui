#include "logfile.h"
#include <iostream>
#include <fstream> 

Logfile::Logfile(std::string path)
{
    this->path = path;
}

int Logfile::parse()
{
    tm t;
    char msg[1024], tz[10];

    std::string line;
    std::ifstream f;
    f.open(this->path);

    if(!f.is_open())
        return -1;
    
    while(getline(f, line))
    {
        int y, m, d;

        if(sscanf(line.c_str(), "%d-%d-%dT%d:%d:%d%s %1024[^\n]", 
            &y, &m, &t.tm_mday, &t.tm_hour, &t.tm_min, &t.tm_sec, tz, msg) >= 0)
            {
                t.tm_year = y - 1900;
                t.tm_mon = m - 1;
                t.tm_zone = NULL;
                mktime(&t);
                msgs.push_back(LogMsg(t, msg));
            }
    } 
           
    return 0; 
}

LogMsg Logfile::getLatestMsg()
{
    return this->msgs.back();
}

Logfile::const_iterator Logfile::begin()
{
    return msgs.begin();
}

Logfile::const_iterator Logfile::end()
{
    return msgs.end();
}
