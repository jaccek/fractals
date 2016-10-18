#pragma once

struct InputArgs
{
    float left;
    float top;
    float right;
    float bottom;

    // TODO: x, y as point
public:
    static InputArgs fromPointAndScale(float x, float y, float scale, int width, int height);
};
