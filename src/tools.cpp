#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <list>

#include "tools.h"


std::string getInstallDir()
{
    return (std::string)DATA_DIR;
}

int getBtrbkPID()
{
    int pid = -1;

    std::list<std::string> idStrings = {
        "perl",
        "btrbk"
    };

    // Open the /proc directory
    DIR *dp = opendir("/proc");
    if (dp != NULL)
    {
        // Enumerate all entries in directory until process found
        struct dirent *dirp;
        while (pid < 0 && (dirp = readdir(dp)))
        {
            // Skip non-numeric entries
            int id = atoi(dirp->d_name);
            if (id > 0)
            {
                // Read contents of virtual /proc/{pid}/cmdline file
                std::string cmdPath = std::string("/proc/") + dirp->d_name + "/cmdline";
                std::ifstream cmdFile(cmdPath.c_str());
                std::string cmdLine;
                std::getline(cmdFile, cmdLine);
                if (!cmdLine.empty())
                {
                    bool found = true;
                    for (auto s: idStrings)
                    {
                        size_t pos = cmdLine.find(s);
                        if (pos == std::string::npos)
                            found = false;
                    }
                    if (found)
                    {
                        pid = id;
                        break;
                    }
                }
            }
        }
    }

    closedir(dp);

    return pid;
}

long getFileModTime(std::string path)
{
  struct stat s;
  stat(path.c_str(), &s);
  return s.st_mtim.tv_sec;
}