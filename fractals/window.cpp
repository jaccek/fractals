#include "window.h"
#include "generators/mandelbrot_generator.h"
#include "graphics/impl/qt_image_impl.h"

const unsigned WIDTH = 800;
const unsigned HEIGHT = 600;

Window::Window()
{
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

	InputArgs args = InputArgs::fromPointAndScale(0.0f, 0.0f, 0.005f, mImage->getWidth(), mImage->getHeight());
	//Image &image = *mImage;
	mGenerator->generate(*mImage, args);

    QLabel *label = new QLabel(centralWidget);
    label->setPixmap(QPixmap::fromImage(*mImage->getImage()));

    QMenuBar *menuBar = new QMenuBar(centralWidget);
    QMenu *menu = new QMenu("menu");
    menu->addAction(new QAction("test", menu));
    menuBar->addMenu(menu);

    setCentralWidget(centralWidget);

	return true;
}
