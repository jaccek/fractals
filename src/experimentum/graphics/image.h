#pragma once

#include "color.h"

class Image
{
public:
    virtual void create(int width, int height) = 0;

    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
    virtual Color getColor(int x, int y) = 0;

    virtual void setColor(int x, int y, Color &color) = 0;
};
