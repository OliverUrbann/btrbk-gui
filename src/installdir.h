#pragma once

#include <string>

#define QUOTE(name) #name
#define STR(macro) QUOTE(macro)
#define DATA_DIR STR(DATADIR)

std::string getInstallDir();