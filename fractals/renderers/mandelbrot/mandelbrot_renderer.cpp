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

void MandelbrotRenderer::bindShaderUniforms()
{
    GLint z0Location = glGetUniformLocation(getShaderProgram(), "inZ0");
    glUniform2f(z0Location, 1.0f, 0.0f);
}
