#pragma once

#include "modes/mode.h"
#include <QOpenGLWidget>

class GlWidget : public QOpenGLWidget, public Mode::ViewRefresher
{
public:
    GlWidget(QWidget *parent);
    virtual ~GlWidget();

    void setMode(Mode *mode);

    bool canRender();
    virtual void refreshView();

protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int width, int height);

private:
    void deleteMode();

    Mode *mMode;
    bool mOpenGlInitialized;
};
