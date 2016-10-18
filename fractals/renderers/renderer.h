#pragma once

#include "input_args/input_args.h"
#include <SFML/Graphics.hpp>

class Renderer
{
public:
    Renderer(int width, int height);
    virtual ~Renderer();

    virtual void generate(InputArgs &args) = 0;
    virtual void render(sf::RenderWindow *window) = 0;

protected:
    int mWidth;
    int mHeight;
};
