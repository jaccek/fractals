#pragma once

#include "modes/renderer.h"

class FractalRenderer : public Renderer
{
public:
    FractalRenderer();

    virtual void render();
    void setDrawStartPoint(bool draw);

private:
    bool mDrawStartPoint;

    void renderStartPoint();
};
