#pragma once

#include "graphics/image.h"
#include "input_args/input_args.h"

class Generator
{
public:
    virtual ~Generator() {}

    virtual void generate(Image &image, InputArgs &args) = 0;
};
