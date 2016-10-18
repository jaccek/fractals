#include "window.h"

int main()
{
	Window window;
	if (!window.init())
	{
		printf("Cannot initialize window\n");
		return 1;
	}

	window.mainLoop();

	window.end();
	return 0;
}
