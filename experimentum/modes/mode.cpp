#include "mode.h"

Mode::Mode(ViewRefresher *refresher)
{
    mRefresher = refresher;
}

Mode::~Mode()
{
}

void Mode::render()
{
    Renderer *renderer = getRenderer();
    if (renderer != nullptr)
    {
        renderer->render();
    }
}

void Mode::refreshView()
{
    mRefresher->refreshView();
}
