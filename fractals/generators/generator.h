#pragma once

#include "graphics/image.h"
#include "input_args/input_args.h"

class Generator
{
public:
    virtual ~Generator() {}

    virtual void generate(Image &image, InputArgs &args) = 0;
    virtual Color generatePixel(int x, int y, int width, int height, InputArgs &args) = 0;
};
