#pragma once

#include "menu.h"

namespace mapi
{
    class ModeInfo
    {
    public:
        virtual ~ModeInfo() {}

        virtual const char* getModeName() = 0;

        virtual Menu* getMenuInfo() = 0;
    };
}
