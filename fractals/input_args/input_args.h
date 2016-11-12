#pragma once

struct InputArgs
{
    // TODO: I need builder!

    float left;
    float top;
    float right;
    float bottom;

    float startX = 0.0f;
    float startY = 0.0f;

    InputArgs& setStartPoint(float x, float y);

public:
    static InputArgs fromPointAndScale(float x, float y, float scale, int width, int height);
};
