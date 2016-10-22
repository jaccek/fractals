#pragma once

#include "generators/generator.h"
#include "graphics/impl/qt_image_impl.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QLabel>

class Window : public QMainWindow
{
public:
	Window();
	~Window();

	bool init();

private:
	Generator *mGenerator;
	QtImageImpl *mImage;
};
