#include <string>

class Actions 
{
    static const std::string cmd_run;
    static const std::string cmd_test;
    static const std::string cmd_template;
    static void execute(std::string cmd);
public:
    static void run();
};