#include <GL/glew.h>
#include <QApplication>
#include "ui/window.h"

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
	window.afterShow();
	return app.exec();
}
