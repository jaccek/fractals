#include "window.h"
#include "renderers/mandelbrot_renderer.h"

const unsigned width = 800;
const unsigned height = 600;

Window::Window()
{
	mIsFocused = true;
	mFpsCounter = 0;
	mFpsTimer = 0.0f;

	mRenderer = new MandelbrotRenderer(width, height);

	InputArgs args = InputArgs::fromPointAndScale(0.0f, 0.0f, 0.005f, width, height);
	mRenderer->generate(args);
}


Window::~Window()
{
	delete mRenderer;
}


bool Window::init()
{

	// init window
	mWindow.create(sf::VideoMode(width, height), "fractals");
	//mWindow.setVerticalSyncEnabled(true);

	return true;
}


void Window::end()
{
}


void Window::mainLoop()
{
	sf::Clock clock;

	// main loop
	while (mWindow.isOpen())
	{
		// dispatch events
		dispatchEvents();

		// TODO: do some logics (get delta time)
		float deltaTime = clock.restart().asSeconds();
		if (mIsFocused)
		{
			//mRenderer.update(deltaTime);
		}

		// render
		render();

		// fps counter
		++mFpsCounter;
		mFpsTimer += deltaTime;
		if (mFpsTimer > 1.0f)
		{
			char buffer[100];
			sprintf(buffer, "fractals (FPS=%d)", mFpsCounter);
			mWindow.setTitle(buffer);

			mFpsCounter = 0;
			mFpsTimer -= 1.0f;
		}
	}
}


void Window::dispatchEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				mWindow.close();
				break;

			case sf::Event::GainedFocus:
				mIsFocused = true;
				break;

			case sf::Event::LostFocus:
				mIsFocused = false;
				break;

			default:
				//mRenderer.consumeEvent(event);
				break;
		}
	}
}


void Window::render()
{
	mWindow.clear(sf::Color::Black);

	mRenderer->render(&mWindow);

	mWindow.display();
}
