#include "window.h"
#include "renderers/julia/julia_renderer.h"
#include "renderers/mandelbrot/mandelbrot_renderer.h"
#include "graphics/impl/qt_image_impl.h"

#include <QMouseEvent>

const unsigned WIDTH = 800;
const unsigned HEIGHT = 600;

Window::Window()
{
}

Window::~Window()
{
}

bool Window::init()
{
	resize(WIDTH, HEIGHT);

	QWidget *centralWidget = new QWidget(this);

	mGlWidget = new GlWidget(centralWidget);
	mGlWidget->resize(WIDTH, HEIGHT);

    QMenuBar *menuBar = new QMenuBar(centralWidget);
    QMenu *modeMenu = new QMenu("mode");
	QMenu *fractalsMenu = new QMenu("fractals");

	addMenu(fractalsMenu, "Mandelbrot", &Window::changeModeMandelbrot);
	addMenu(fractalsMenu, "Julia Set", &Window::changeModeJuliaSet);

	modeMenu->addMenu(fractalsMenu);
    menuBar->addMenu(modeMenu);

    setCentralWidget(centralWidget);
	setMouseTracking(true);

	return true;
}

void Window::afterShow()
{
	changeModeMandelbrot();
}

void Window::mouseMoveEvent(QMouseEvent *event)
{
	mCenterPointX -= (float) (event->x() - mMousePositionX) * mViewScale;
	mCenterPointY += (float) (event->y() - mMousePositionY) * mViewScale;
	redrawContent();

	mMousePositionX = event->x();
	mMousePositionY = event->y();
}

void Window::mousePressEvent(QMouseEvent *event)
{
	mMousePositionX = event->x();
	mMousePositionY = event->y();
}

void Window::mouseReleaseEvent(QMouseEvent *event)
{
}

void Window::wheelEvent(QWheelEvent *event)
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

	redrawContent();
}

void Window::changeModeMandelbrot()
{
	mCenterPointX = 0.0f;
	mCenterPointY = 0.0f;
	mViewScale = 0.005f;

	changeMode(new MandelbrotRenderer());
}

void Window::changeModeJuliaSet()
{
	mCenterPointX = 0.0f;
	mCenterPointY = 0.0f;
	mViewScale = 0.005f;

	changeMode(new JuliaRenderer());
}

void Window::changeMode(Renderer *renderer)
{
	mGlWidget->deleteRenderer();
	mRenderer = renderer;
	mGlWidget->setRenderer(renderer);
	redrawContent();
}

void Window::redrawContent()
{
	InputArgs args = InputArgs::fromPointAndScale(mCenterPointX,
					mCenterPointY,
					mViewScale,
					mGlWidget->width(),
					mGlWidget->height());

	mRenderer->onInputArgsChanged(args);
	mGlWidget->update();
}

void Window::addMenu(QMenu *parent, const char *actionName, SlotFunction slot)
{
	QAction *action = new QAction(actionName, parent);
	connect(action, &QAction::triggered, this, slot);
    parent->addAction(action);
}
