#include "fractal_mode.h"
#include "renderers/mandelbrot/mandelbrot_renderer.h"
#include "renderers/julia/julia_renderer.h"

FractalMode::FractalMode(ViewRefresher *refresher, FractalType fractalType, int width, int height):
        Mode(refresher)
{
    mWidth = width;
    mHeight = height;

    mCenterPointX = 0.0f;
	mCenterPointY = 0.0f;
	mViewScale = 0.005f;

    switch(fractalType)
    {
        case MANDELBROT:
            mRenderer = new MandelbrotRenderer();
            break;

        case JULIA_SET:
            mRenderer = new JuliaRenderer();
            break;

        default:
            printf("FractalMode(): Unknown renderer\n");
            throw 0;
    }
}

FractalMode::~FractalMode()
{
    delete mRenderer;
}

void FractalMode::onModeSelected()
{
    mRenderer->init();
    refreshFractal();
}

void FractalMode::onModeDeselected()
{
}

void FractalMode::onResizeEvent(QResizeEvent *event)
{
    QSize size = event->size();
    mWidth = size.width();
    mHeight = size.height();
    mRenderer->resize(size.width(), size.height());
}

void FractalMode::onMouseMoveEvent(QMouseEvent *event)
{
    mCenterPointX -= (float) (event->x() - mMousePositionX) * mViewScale;
	mCenterPointY += (float) (event->y() - mMousePositionY) * mViewScale;
    refreshFractal();

	mMousePositionX = event->x();
	mMousePositionY = event->y();
}

void FractalMode::onMousePressEvent(QMouseEvent *event)
{
	mMousePositionX = event->x();
	mMousePositionY = event->y();
}

void FractalMode::onMouseReleaseEvent(QMouseEvent *event)
{
}

void FractalMode::onMouseWheelEvent(QWheelEvent *event)
{
	QPoint numDegrees = event->angleDelta() / 8;
	if (numDegrees.y() < 0)
	{
		mViewScale *= 1.1f;
	}
	else
	{
		mViewScale /= 1.1f;
	}
    refreshFractal();
}

Renderer* FractalMode::getRenderer()
{
    return mRenderer;
}

void FractalMode::refreshFractal()
{
    InputArgs args = InputArgs::fromPointAndScale(mCenterPointX, mCenterPointY, mViewScale, mWidth, mHeight);
	mRenderer->onInputArgsChanged(args);
    refreshView();
}
