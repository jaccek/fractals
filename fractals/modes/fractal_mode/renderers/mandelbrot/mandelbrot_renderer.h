#pragma once

#include "modes/renderer.h"

class MandelbrotRenderer : public Renderer
{
public:
    MandelbrotRenderer();
    virtual ~MandelbrotRenderer();

protected:
    virtual void bindShaderUniforms();
};
