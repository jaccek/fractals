#include "window.h"
#include "generators/mandelbrot_generator.h"
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

	InputArgs args = InputArgs::fromPointAndScale(mCenterPointX, mCenterPointY, mViewScale, mImage->getWidth(), mImage->getHeight());
	mGenerator->generate(*mImage, args);

    mLabel = new QLabel(centralWidget);
    mLabel->setPixmap(QPixmap::fromImage(*mImage->getImage()));

    QMenuBar *menuBar = new QMenuBar(centralWidget);
    QMenu *menu = new QMenu("menu");
    menu->addAction(new QAction("test", menu));
    menuBar->addMenu(menu);

    setCentralWidget(centralWidget);
	setMouseTracking(true);

	return true;
}

void Window::mouseMoveEvent(QMouseEvent *event)
{
}

void Window::mousePressEvent(QMouseEvent *event)
{
	mMousePositionX = event->x();
	mMousePositionY = event->y();
}

void Window::mouseReleaseEvent(QMouseEvent *event)
{
	mCenterPointX -= (float) (event->x() - mMousePositionX) * mViewScale;
	mCenterPointY += (float) (event->y() - mMousePositionY) * mViewScale;
	InputArgs args = InputArgs::fromPointAndScale(mCenterPointX, mCenterPointY, mViewScale, mImage->getWidth(), mImage->getHeight());
	mGenerator->generate(*mImage, args);
	mLabel->setPixmap(QPixmap::fromImage(*mImage->getImage()));
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

	InputArgs args = InputArgs::fromPointAndScale(mCenterPointX, mCenterPointY, mViewScale, mImage->getWidth(), mImage->getHeight());
	mGenerator->generate(*mImage, args);
	mLabel->setPixmap(QPixmap::fromImage(*mImage->getImage()));
}
