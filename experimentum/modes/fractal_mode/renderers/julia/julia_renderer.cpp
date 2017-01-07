#include "julia_renderer.h"

JuliaRenderer::JuliaRenderer()
{
    createShaderProgram("shaders/base.vert", "shaders/julia.frag");
}

JuliaRenderer::~JuliaRenderer()
{
}
