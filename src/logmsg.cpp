#include "logmsg.h"

LogMsg::LogMsg(tm t, std::string msg) 
{ 
    this->t = t; 
    this->msg = msg;
}

LogMsg::Meaning LogMsg::interpretMsg() const
{
    if (this->msg.find(STR_FINISHED_SUCCESS) != std::string::npos)
        return Meaning::finished_success;
    else if (this->msg.find(STR_FINISHED_PARTIAL) != std::string::npos)
        return Meaning::finished_fail;
    else
        return Meaning::running;
}

const std::string LogMsg::getTimeMsgLine() const
{
    return getTime() + ": " + getMsg() + "\n";
}

const std::string LogMsg::getMsg() const
{
    return msg;
}

const std::string LogMsg::getTime() const
{
    char buffer[80];
    strftime(buffer, 80, "%c", &t);
    return buffer;
}