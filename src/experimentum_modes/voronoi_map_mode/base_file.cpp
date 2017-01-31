#include <mode_info.h>

namespace csm
{
    class VoronoiMapMode : public mapi::ModeInfo
    {
    public:
        VoronoiMapMode()
        {
            std::string name = "Voronoi Map";
            mMenu = new mapi::Menu(name);
        }

        virtual ~VoronoiMapMode()
        {
            delete mMenu;
        }

        virtual const char* getModeName()
        {
            return "Voronoi Map";
        }

        virtual mapi::Menu* getMenuInfo()
        {
            return mMenu;
        }

    private:
        mapi::Menu *mMenu;
    };
}

extern "C" mapi::ModeInfo* getModeInfo()
{
    return new csm::VoronoiMapMode();
}
