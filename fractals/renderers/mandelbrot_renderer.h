#pragma once

#include "renderer.h"
#include <SFML/Graphics.hpp>

class MandelbrotRenderer : public Renderer
{
public:
    MandelbrotRenderer(int width, int height);
    virtual ~MandelbrotRenderer();

    virtual void generate(InputArgs &args);
    virtual void render(sf::RenderWindow *window);

private:
    float toRealis(int pixel, float left, float right);
    float toImaginalis(int pixel, float top, float bottom);
    sf::Color simulate(float re, float im);

    float mLeftRealis;
    float mTopImaginalis;
    float mScale;

    sf::Image mImage;
    sf::Sprite mSprite;
    sf::Texture mTexture;
};
