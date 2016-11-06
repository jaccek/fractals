#include "window.h"
#include "renderers/julia/julia_renderer.h"
#include "renderers/mandelbrot/mandelbrot_renderer.h"
#include "graphics/impl/qt_image_impl.h"

#include "modes/fractal_mode.h"

#include <QMouseEvent>

const unsigned WIDTH = 800;
const unsigned HEIGHT = 600;

Window::Window()
{
	mMode = nullptr;
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
	QSizePolicy policy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	mGlWidget->setSizePolicy(policy);

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
	mMode->onMouseMoveEvent(event);
}

void Window::mousePressEvent(QMouseEvent *event)
{
	mMode->onMousePressEvent(event);
}

void Window::mouseReleaseEvent(QMouseEvent *event)
{
	mMode->onMouseReleaseEvent(event);
}

void Window::wheelEvent(QWheelEvent *event)
{
	mMode->onMouseWheelEvent(event);
}

void Window::resizeEvent(QResizeEvent *event)
{
	mGlWidget->resize(event->size());
	if (mMode != nullptr)
	{
		mMode->onResizeEvent(event);
	}
}

void Window::changeModeMandelbrot()
{
	changeMode(new FractalMode(mGlWidget, FractalMode::MANDELBROT, mGlWidget->width(), mGlWidget->height()));
}

void Window::changeModeJuliaSet()
{
	changeMode(new FractalMode(mGlWidget, FractalMode::JULIA_SET, mGlWidget->width(), mGlWidget->height()));
}

void Window::changeMode(Mode *mode)
{
	mMode = mode;
	mMode->onModeSelected();
	mGlWidget->setMode(mMode);
}

void Window::addMenu(QMenu *parent, const char *actionName, SlotFunction slot)
{
	QAction *action = new QAction(actionName, parent);
	connect(action, &QAction::triggered, this, slot);
    parent->addAction(action);
}
