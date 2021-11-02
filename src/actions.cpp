#include "actions.h"
#include "tools.h"
#include <sstream>

void Actions::execute(std::string cmd)
{
    std::stringstream full_cmd;
    full_cmd << getInstallDir() << "/execute_btrbk.sh " << cmd;
    system(full_cmd.str().c_str());
}

void Actions::run()
{
    execute("run");
}

void Actions::resume()
{
    execute("resume");
}

void Actions::stop()
{
    int pid = getBtrbkPID();
    if (pid != -1)
    {
        std::stringstream full_cmd;
        full_cmd << "kill " << pid;
        execute(full_cmd.str());  
    }
}