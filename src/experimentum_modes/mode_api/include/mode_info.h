#pragma once

namespace mapi
{
    class ModeInfo
    {
    public:
        virtual ~ModeInfo() {}

        virtual const char* getModeName() = 0;
    };
}
