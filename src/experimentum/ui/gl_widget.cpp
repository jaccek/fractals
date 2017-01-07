#include <GL/glew.h>
#include "gl_widget.h"

GlWidget::GlWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    mMode = nullptr;
    mOpenGlInitialized = false;
}

GlWidget::~GlWidget()
{
    deleteMode();
}

void GlWidget::setMode(Mode *mode)
{
    deleteMode();
    mMode = mode;
}

bool GlWidget::canRender()
{
    return mOpenGlInitialized;
}

void GlWidget::refreshView()
{
    update();
}

void GlWidget::initializeGL()
{
	//glewExperimental = true;
	glewInit();

    char *version = (char*) glGetString(GL_VERSION);
    printf("%s\n", version);

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    mOpenGlInitialized = true;
}

void GlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (mMode != nullptr)
    {
        mMode->render();
    }
}

void GlWidget::resizeGL(int width, int height)
{
}

void GlWidget::deleteMode()
{
    if (mMode != nullptr)
    {
        delete mMode;
        mMode = nullptr;
    }
}
