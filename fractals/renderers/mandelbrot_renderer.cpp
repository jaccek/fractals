#include "mandelbrot_renderer.h"
#include <cmath>

MandelbrotRenderer::MandelbrotRenderer(int width, int height) : Renderer(width, height)
{
    mScale = 0.005f;
    mLeftRealis = -2.0f;
    mTopImaginalis = 1.0f;

    mTexture.create(mWidth, mHeight);
    mSprite.setTexture(mTexture);
    mImage.create(mWidth, mHeight);
}

MandelbrotRenderer::~MandelbrotRenderer()
{
}

void MandelbrotRenderer::generate(InputArgs &args)
{
    // TODO: do it in different thread
    for (int x = 0; x < mWidth; ++x)
    {
        for (int y = 0; y < mHeight; ++y)
        {
            float zRe = toRealis(x, args.left, args.right);
            float zIm = toImaginalis(y, args.top, args.bottom);

            sf::Color color = simulate(zRe, zIm);
            mImage.setPixel(x, y, color);
        }
    }

    mTexture.update(mImage);
}

void MandelbrotRenderer::render(sf::RenderWindow *window)
{
    window->draw(mSprite);
}

float MandelbrotRenderer::toRealis(int pixel, float left, float right)
{
    float t = (float) pixel / (float) mWidth;
    return left * (1.0f - t) + right * t;
}

float MandelbrotRenderer::toImaginalis(int pixel, float top, float bottom)
{
    float t = (float) pixel / (float) mHeight;
    return top * (1.0f - t) + bottom * t;
}

sf::Color MandelbrotRenderer::simulate(float re, float im)
{
    const int maxIter = 100;
    float zRe = 0.0f, zIm = 0.0f;
    float nextRe, nextIm;
    int i;
    float squareModule;

    for (i = 0; i < maxIter; ++i)
    {
        nextRe = zRe*zRe - zIm*zIm + re;
        nextIm = 2.0f*zRe*zIm + im;

        squareModule = nextRe*nextRe + nextIm*nextIm;
        if (squareModule > 4.0f)
        {
            break;
        }

        zRe = nextRe;
        zIm = nextIm;
    }

    unsigned char green = (unsigned char) (zRe*zRe / squareModule * 255.0f);
    unsigned char blue = (unsigned char) (zIm*zIm / squareModule * 255.0f);
    return sf::Color(blue, green, 128);

    // float percent = (float) i / (float) maxIter;
    // unsigned char color = (unsigned char) (percent * 255.0f);
    // return sf::Color(color, color, color);
}
