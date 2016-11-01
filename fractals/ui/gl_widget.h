#pragma once

#include "renderers/renderer.h"
#include <QOpenGLWidget>

class GlWidget : public QOpenGLWidget
{
public:
    GlWidget(QWidget *parent);
    virtual ~GlWidget();

    void deleteRenderer();
    void setRenderer(Renderer *renderer);

    bool canRender();

protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int width, int height);

private:
    Renderer *mRenderer;
    bool mOpenGlInitialized;
};
