#include "menu.h"

namespace mapi
{
    Menu::Menu(std::string name)
    {
        mName = name;
    }

    Menu::~Menu()
    {
        if (!isLeaf())
        {
            for (auto subMenu : mSubMenus)
            {
                delete subMenu;
            }
        }
    }

    void Menu::addSubMenu(Menu *subMenu)
    {
        mSubMenus.push_back(subMenu);
    }

    bool Menu::isLeaf()
    {
        return mSubMenus.empty();
    }

    std::vector<Menu*> Menu::getSubMenus()
    {
        return mSubMenus;
    }

    std::string Menu::getName()
    {
        return mName;
    }
}
