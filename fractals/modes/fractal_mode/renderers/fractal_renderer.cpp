#include "fractal_renderer.h"
#include <GL/glew.h>
#include <GL/gl.h>

FractalRenderer::FractalRenderer()
{
    mDrawStartPoint = true;
}

void FractalRenderer::render()
{
    Renderer::render();

    if (mDrawStartPoint)
    {
        renderStartPoint();
    }
}

void FractalRenderer::setDrawStartPoint(bool draw)
{
    mDrawStartPoint = draw;
}

void FractalRenderer::renderStartPoint()
{
    InputArgs &args = getLastInputArgs();

    float sx = 2.0f * (args.startX - args.left) / (args.right - args.left) - 1.0f;
    float sy = 2.0f * (args.startY - args.bottom) / (args.top - args.bottom) - 1.0f;

    // TODO: change it to bilboard
    glPointSize(5.0f);
    glBegin(GL_POINTS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(sx, sy, 0.0f);
    glEnd();
}
