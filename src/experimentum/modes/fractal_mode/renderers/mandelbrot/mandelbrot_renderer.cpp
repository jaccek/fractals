#include "mandelbrot_renderer.h"
#include <GL/glew.h>
#include <GL/gl.h>

MandelbrotRenderer::MandelbrotRenderer()
{
    createShaderProgram("shaders/base.vert", "shaders/mandelbrot.frag");
}

MandelbrotRenderer::~MandelbrotRenderer()
{
}
