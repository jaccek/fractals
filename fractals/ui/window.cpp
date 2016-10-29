#include "window.h"
#include "generators/mandelbrot_generator.h"
#include "renderers/julia/julia_renderer.h"
#include "renderers/mandelbrot/mandelbrot_renderer.h"
#include "graphics/impl/qt_image_impl.h"

#include <QMouseEvent>

const unsigned WIDTH = 800;
const unsigned HEIGHT = 600;

Window::Window()
{
	mCenterPointX = 0.0f;
	mCenterPointY = 0.0f;
	mViewScale = 0.005f;

	mGenerator = new MandelbrotGenerator();
}


Window::~Window()
{
	delete mGenerator;
}


bool Window::init()
{
	resize(WIDTH, HEIGHT);

	QWidget *centralWidget = new QWidget(this);

	mImage = new QtImageImpl();
	mImage->create(WIDTH, HEIGHT);

	mGlWidget = new GlWidget(centralWidget);
	mGlWidget->resize(WIDTH, HEIGHT);

    QMenuBar *menuBar = new QMenuBar(centralWidget);
    QMenu *modeMenu = new QMenu("mode");
	QMenu *fractalsMenu = new QMenu("fractals");

	QAction *mandelbrotAction = new QAction("Mandelbrot", fractalsMenu);
	connect(mandelbrotAction, &QAction::triggered, this, &Window::changeModeMandelbrot);
    fractalsMenu->addAction(mandelbrotAction);

	QAction *juliaAction = new QAction("Julia Set", fractalsMenu);
	connect(juliaAction, &QAction::triggered, this, &Window::changeModeJuliaSet);
    fractalsMenu->addAction(juliaAction);

	modeMenu->addMenu(fractalsMenu);
    menuBar->addMenu(modeMenu);

    setCentralWidget(centralWidget);
	setMouseTracking(true);

	return true;
}

void Window::afterShow()
{
	mRenderer = new JuliaRenderer();
	// mRenderer = new MandelbrotRenderer();
	mGlWidget->setRenderer(mRenderer);
	redrawContent();

	// changeModeMandelbrot();
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

	mGlWidget->deleteRenderer();
	mRenderer = new MandelbrotRenderer();
	mGlWidget->setRenderer(mRenderer);
	redrawContent();
}

void Window::changeModeJuliaSet()
{
	mCenterPointX = 0.0f;
	mCenterPointY = 0.0f;
	mViewScale = 0.005f;

	mGlWidget->deleteRenderer();
	mRenderer = new JuliaRenderer();
	mGlWidget->setRenderer(mRenderer);
	redrawContent();
}

void Window::redrawContent()
{
	InputArgs args = InputArgs::fromPointAndScale(mCenterPointX, mCenterPointY, mViewScale, mGlWidget->width(), mGlWidget->height());
	mRenderer->onInputArgsChanged(args);
	mGlWidget->update();
}
