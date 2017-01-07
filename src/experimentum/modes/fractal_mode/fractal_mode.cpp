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

    mMouseButton = Qt::NoButton;

    switch(fractalType)
    {
        case MANDELBROT:
            mRenderer = new MandelbrotRenderer();
            mStartPointX = 0.0f;
            mStartPointY = 0.0f;
            break;

        case JULIA_SET:
            mRenderer = new JuliaRenderer();
            mStartPointX = -0.1f;
            mStartPointY = 0.65f;
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

    mSubWindow = new FractalModeWindow();
    mSubWindow->init(this);
    mSubWindow->show();

    refreshFractal();
}

void FractalMode::onModeDeselected()
{
    mSubWindow->close();
    delete mSubWindow;
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
    if (mMouseButton == Qt::RightButton)
    {
        mCenterPointX -= (float) (event->x() - mMousePositionX) * mViewScale;
    	mCenterPointY += (float) (event->y() - mMousePositionY) * mViewScale;
        refreshFractal();
    }
    else if (mMouseButton == Qt::LeftButton)
    {
        InputArgs args = InputArgs::fromPointAndScale(mCenterPointX, mCenterPointY, mViewScale, mWidth, mHeight);
        mStartPointX = interpolate(event->x(), 0, mWidth, args.left, args.right);
        mStartPointY = interpolate(mHeight - event->y(), 0, mHeight, args.bottom, args.top);
        refreshFractal();
    }

	mMousePositionX = event->x();
	mMousePositionY = event->y();
}

void FractalMode::onMousePressEvent(QMouseEvent *event)
{
    mMouseButton = event->button();

	mMousePositionX = event->x();
	mMousePositionY = event->y();
}

void FractalMode::onMouseReleaseEvent(QMouseEvent *event)
{
    mMouseButton = Qt::NoButton;
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

void FractalMode::setDrawStartPoint(bool draw)
{
    mRenderer->setDrawStartPoint(draw);
    refreshFractal();
}

Renderer* FractalMode::getRenderer()
{
    return mRenderer;
}

void FractalMode::refreshFractal()
{
    InputArgs args = InputArgs::fromPointAndScale(mCenterPointX, mCenterPointY, mViewScale, mWidth, mHeight).
            setStartPoint(mStartPointX, mStartPointY);
	mRenderer->onInputArgsChanged(args);
    mSubWindow->setStartPoint(mStartPointX, mStartPointY);
    refreshView();
}

float FractalMode::interpolate(int value, int minOld, int maxOld, float minNew, float maxNew)
{
    float t = (float) (value - minOld) / (float) (maxOld - minOld);
    return minNew * (1.0f - t) + maxNew * t;
}
