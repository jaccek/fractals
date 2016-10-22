#include "mandelbrot_generator.h"
#include <cmath>

MandelbrotGenerator::~MandelbrotGenerator()
{
}

void MandelbrotGenerator::generate(Image &image, InputArgs &args)
{
    // TODO: do it in different thread
    for (int x = 0; x < image.getWidth(); ++x)
    {
        for (int y = 0; y < image.getHeight(); ++y)
        {
            Color color = generatePixel(x, y, image.getWidth(), image.getHeight(), args);
            image.setColor(x, y, color);
        }
    }
}

Color MandelbrotGenerator::generatePixel(int x, int y, int width, int height, InputArgs &args)
{
    float zRe = toRealis(x, width, args.left, args.right);
    float zIm = toImaginalis(y, height, args.top, args.bottom);

    return simulate(zRe, zIm);
}

float MandelbrotGenerator::toRealis(int pixel, int width, float left, float right)
{
    float t = (float) pixel / (float) width;
    return left * (1.0f - t) + right * t;
}

float MandelbrotGenerator::toImaginalis(int pixel, int height, float top, float bottom)
{
    float t = (float) pixel / (float) height;
    return top * (1.0f - t) + bottom * t;
}

Color MandelbrotGenerator::simulate(float re, float im)
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

    float percent = (float) i / (float) maxIter;
    float green = percent;
    float red = zRe*zRe / squareModule;
    float blue = zIm*zIm / squareModule;

    return Color(red, green, blue);
}
