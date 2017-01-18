#include <mode_info.h>

namespace csm
{
    class VoronoiMapMode : public mapi::ModeInfo
    {
    public:
        virtual ~VoronoiMapMode() {}

        virtual const char* getModeName()
        {
            return "Voronoi Map";
        }
    };
}

extern "C" mapi::ModeInfo* getModeInfo()
{
    return new csm::VoronoiMapMode();
}
