#pragma once

class Color
{
public:
    Color();
    Color(unsigned int color);
    Color(float r, float g, float b);

    unsigned int toUint();

    float r;
    float g;
    float b;
};
