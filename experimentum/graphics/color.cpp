#include "color.h"
#include <iostream>

Color::Color() : Color(0.0f, 0.0f, 0.0f)
{
}

Color::Color(unsigned int color)
{
    int ir = (color & 0x00ff0000) >> 16;
    int ig = (color & 0x0000ff00) >> 8;
    int ib = (color & 0x000000ff);

    r = (float) ir / 255.0f;
    g = (float) ig / 255.0f;
    b = (float) ib / 255.0f;
}

Color::Color(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

unsigned int Color::toUint()
{
    int ir = (int) (r * 255.0f);
    int ig = (int) (g * 255.0f);
    int ib = (int) (b * 255.0f);

    return 0xff000000 + (ir << 16) + (ig << 8) + ib;
}
