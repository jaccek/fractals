#pragma once

#include <mode_info.h>
#include <vector>

class ModesLoader
{
public:
    static std::vector<mapi::ModeInfo*> loadModes();

private:
    static bool isDirValid(const char* dirName);
};
