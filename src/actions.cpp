#include "actions.h"

const std::string Actions::cmd_run = "pkexec btrbk run";
const std::string Actions::cmd_template = "gnome-terminal -x sh -c 'cd /tmp ; $CMD'";
const std::string Actions::cmd_test = "CMD='sleep 100'";


void Actions::execute(std::string cmd)
{
    std::string full_cmd = cmd + " " + Actions::cmd_template;
    system(full_cmd.c_str());
}

void Actions::run()
{
    execute(cmd_test);
}