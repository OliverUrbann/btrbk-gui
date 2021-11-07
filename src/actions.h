#include <string>

class Actions 
{
    static int execute(std::string cmd);
public:
    static void run();
    static void resume();
    static void stop();
    static void clean();
};