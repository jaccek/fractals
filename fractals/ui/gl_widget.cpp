#include <GL/glew.h>
#include "gl_widget.h"

GlWidget::GlWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    mRenderer = nullptr;

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setMajorVersion(3);
    format.setMinorVersion(3);
    // setFormat(format);
}

GlWidget::~GlWidget()
{
    deleteRenderer();
}

void GlWidget::deleteRenderer()
{
    if (mRenderer != nullptr)
    {
        delete mRenderer;
        mRenderer = nullptr;
    }
}

void GlWidget::setRenderer(Renderer *renderer)
{
    mRenderer = renderer;
    mRenderer->init();
    mRenderer->resize(width(), height());
}

void GlWidget::initializeGL()
{
	//glewExperimental = true;
	glewInit();

    char *version = (char*) glGetString(GL_VERSION);
    printf("%s\n", version);

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void GlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
