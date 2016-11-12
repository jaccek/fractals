#pragma once

#include "modes/mode.h"
#include "ui/modes/fractal_mode_window.h"

class FractalMode : public Mode
{
public:
    enum FractalType
    {
        MANDELBROT,
        JULIA_SET
    };

    FractalMode(ViewRefresher *refresher, FractalType fractalType, int width, int height);
    virtual ~FractalMode();

    virtual void onModeSelected();
    virtual void onModeDeselected();
    virtual void onResizeEvent(QResizeEvent *event);

    virtual void onMouseMoveEvent(QMouseEvent *event);
    virtual void onMousePressEvent(QMouseEvent *event);
    virtual void onMouseReleaseEvent(QMouseEvent *event);
    virtual void onMouseWheelEvent(QWheelEvent *event);

protected:
    virtual Renderer* getRenderer();

private:
    void refreshFractal();
    float interpolate(int value, int minOld, int maxOld, float minNew, float maxNew);

	int mMousePositionX;
	int mMousePositionY;
    Qt::MouseButton mMouseButton;

    int mWidth;
    int mHeight;

	float mCenterPointX;
	float mCenterPointY;
	float mViewScale;
    float mStartPointX;
    float mStartPointY;

    Renderer *mRenderer;
    FractalModeWindow *mSubWindow;
};
