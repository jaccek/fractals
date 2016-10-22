#include "window.h"
#include <QApplication>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	Window window;

	if (!window.init())
	{
		printf("Cannot initialize window\n");
		return 1;
	}

	window.show();
	return app.exec();
}
