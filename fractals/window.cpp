#include "window.h"
#include "renderers/mandelbrot_renderer.h"

const unsigned width = 800;
const unsigned height = 600;

Window::Window()
{
	mIsFocused = true;
	mFpsCounter = 0;
	mFpsTimer = 0.0f;
	mIsLeftMouseButtonPressed = false;
	mViewScale = 0.005f;
	mCenterPointX = 0.0f;
	mCenterPointY = 0.0f;

	mRenderer = new MandelbrotRenderer(width, height);

	InputArgs args = InputArgs::fromPointAndScale(mCenterPointX, mCenterPointY, mViewScale, width, height);
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
		InputArgs args;
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

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
				{
					mWindow.close();
				}
				break;

			case sf::Event::MouseButtonPressed:
				mIsLeftMouseButtonPressed = true;
				mLastMousePositionX = event.mouseButton.x;
				mLastMousePositionY = event.mouseButton.y;
				break;

			case sf::Event::MouseWheelMoved:
				// TODO: zoom to mouse position (not to window center)
				if (event.mouseWheel.delta > 0)
				{
					mViewScale /= 2.0f;
				}
				else
				{
					mViewScale *= 2.0f;
				}
				args = InputArgs::fromPointAndScale(mCenterPointX, mCenterPointY, mViewScale, width, height);
				mRenderer->generate(args);
				break;

			case sf::Event::MouseButtonReleased:
				mIsLeftMouseButtonPressed = event.type == false;
				args = InputArgs::fromPointAndScale(mCenterPointX, mCenterPointY, mViewScale, width, height);
				mRenderer->generate(args);
				break;

			case sf::Event::MouseMoved:
				if (mIsLeftMouseButtonPressed && mIsFocused)
				{
					mCenterPointX -= (float) (event.mouseMove.x - mLastMousePositionX) * mViewScale;
					mCenterPointY += (float) (event.mouseMove.y - mLastMousePositionY) * mViewScale;
					mLastMousePositionX = event.mouseMove.x;
					mLastMousePositionY = event.mouseMove.y;
				}
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
