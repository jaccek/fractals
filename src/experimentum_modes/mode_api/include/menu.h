#pragma once

#include <vector>
#include <string>

namespace mapi
{
    class Menu
    {
    public:
        Menu(std::string name);
        ~Menu();

        void addSubMenu(Menu *subMenu);

        bool isLeaf();
        std::vector<Menu*> getSubMenus();
        std::string getName();

    private:
        std::vector<Menu*> mSubMenus;
        std::string mName;
    };
}
