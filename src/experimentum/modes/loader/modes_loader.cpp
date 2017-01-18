#include "modes_loader.h"
#include <cstdio>
#include <dirent.h>
#include <dlfcn.h>

using namespace mapi;

typedef ModeInfo* (*Function)();

std::vector<mapi::ModeInfo*> ModesLoader::loadModes()
{
    printf("ModesLoader: loading modes\n");

    DIR *dir = opendir("./modes");
    if (dir == NULL)
    {
        printf("ModesLoader: cannot find modes!\n");
        throw 1;
    }

    std::vector<ModeInfo*> modes;

    dirent *entity;
    while ((entity = readdir(dir)) != NULL)
    {
        // TODO: it also returns . and .. - filter them!
        if (isDirValid(entity->d_name))
        {
            printf("ModesLoader: found dir: %s\n", entity->d_name);
            char filename[512];
            // TODO: what if filename will be too long?
            sprintf(filename, "./modes/%s/lib%s.so", entity->d_name, entity->d_name);
            printf("ModesLoader: loading %s\n", filename);
            void *library = dlopen(filename, RTLD_NOW);
            // TODO check if library exists!
            ModeInfo* (*functionGetModeInfo)();
            functionGetModeInfo = (Function) dlsym(library, "getModeInfo");
            if (functionGetModeInfo == nullptr)
            {
                printf("ModesLoader: cannot find function: getModeInfo\n");
                dlclose(library);
                continue;
            }
            ModeInfo *modeInfo = functionGetModeInfo();
            //dlclose(library); // TODO: close libraries at the end of program
            modes.push_back(modeInfo);
        }
    }

    closedir(dir);
    printf("ModesLoader: %d modes loaded\n", (int) modes.size());

    return modes;
}

bool ModesLoader::isDirValid(const char* dirName)
{
    return dirName[0] != '.';
}
