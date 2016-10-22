#pragma once

#include "generator.h"
#include "graphics/color.h"

class MandelbrotGenerator : public Generator
{
public:
    virtual ~MandelbrotGenerator();

    virtual void generate(Image &image, InputArgs &args);
    virtual Color generatePixel(int x, int y, int width, int height, InputArgs &args);

private:
    float toRealis(int pixel, int width, float left, float right);
    float toImaginalis(int pixel, int height, float top, float bottom);
    Color simulate(float re, float im);
};
