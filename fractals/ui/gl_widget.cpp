#include <GL/glew.h>
#include "gl_widget.h"

GlWidget::GlWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    mRenderer = nullptr;
}

GlWidget::~GlWidget()
{
    if (mRenderer != nullptr)
    {
        delete mRenderer;
    }
}

void GlWidget::setRenderer(Renderer *renderer)
{
    Renderer *oldRenderer = mRenderer;
    mRenderer = renderer;
    mRenderer->init();
    mRenderer->resize(width(), height());

    if (oldRenderer != nullptr)
    {
        delete oldRenderer;
    }
}

void GlWidget::initializeGL()
{
	glewExperimental = true;
	glewInit();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    if (mRenderer != nullptr)
    {
        mRenderer->init();
    }
}

void GlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (mRenderer != nullptr)
    {
        mRenderer->render();
    }
}

void GlWidget::resizeGL(int width, int height)
{
    if (mRenderer != nullptr)
    {
        mRenderer->resize(width, height);
    }
}
