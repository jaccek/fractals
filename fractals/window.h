#pragma once

#include "renderers/renderer.h"
#include <SFML/Graphics.hpp>

class Window
{
public:
	Window();
	~Window();

	bool init();
	void end();

	void mainLoop();

private:
	void dispatchEvents();
	void render();

	sf::RenderWindow mWindow;
	Renderer *mRenderer;

	bool mIsFocused;
	int mFpsCounter;
	float mFpsTimer;
};
