#include <string>

class Actions 
{
    static void execute(std::string cmd);
public:
    static void run();
    static void resume();
    static void stop();
};