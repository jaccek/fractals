#pragma once

#include "renderers/renderer.h"
#include <QResizeEvent>
#include <QMouseEvent>
#include <QWheelEvent>

class Mode
{
public:
    class ViewRefresher
    {
    public:
        virtual void refreshView() = 0;
    };

    Mode(ViewRefresher *refresher);
    virtual ~Mode();

    virtual void onModeSelected() = 0;
    virtual void onModeDeselected() = 0;
    virtual void onResizeEvent(QResizeEvent *event) = 0;

    virtual void onMouseMoveEvent(QMouseEvent *event) = 0;
	virtual void onMousePressEvent(QMouseEvent *event) = 0;
	virtual void onMouseReleaseEvent(QMouseEvent *event) = 0;
	virtual void onMouseWheelEvent(QWheelEvent *event) = 0;

    void render();

protected:
    virtual Renderer* getRenderer() = 0;

    void refreshView();

private:
    ViewRefresher *mRefresher;
};
