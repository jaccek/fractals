#pragma once

#include "renderers/renderer.h"

class MandelbrotRenderer : public Renderer
{
public:
    MandelbrotRenderer();
    virtual ~MandelbrotRenderer();

    virtual void init();
    virtual void resize(int width, int height);
    virtual void render();

private:
    unsigned int mVertexBuffer;
    unsigned int mVertexArray;
    unsigned int mShaderProgram;

    int mWidth;
    int mHeight;
};
