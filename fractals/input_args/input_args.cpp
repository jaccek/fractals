#include "input_args.h"

InputArgs InputArgs::fromPointAndScale(float x, float y, float scale, int width, int height)
{
    float halfScaledWidth = scale * (float) width / 2.0f;
    float halfScaledHeight = scale * (float) height / 2.0f;

    InputArgs args;
    args.left = x - halfScaledWidth;
    args.right = x + halfScaledWidth;
    args.top = y + halfScaledHeight;
    args.bottom = y - halfScaledHeight;

    return args;
}
