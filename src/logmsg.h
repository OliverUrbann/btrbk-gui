#pragma once

#include <string>

#define STR_FINISHED_SUCCESS "finished success"
#define STR_FINISHED_PARTIAL "finished partial"

class LogMsg
{
    tm t;
    std::string msg;
public:
    enum Meaning {running, finished_success, finished_fail};
    LogMsg(tm t, std::string msg);
    Meaning interpretMsg() const;
    const std::string getTimeMsgLine() const;
    const std::string getMsg() const;
    const std::string getTime() const;
};