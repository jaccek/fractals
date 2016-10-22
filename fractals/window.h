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

protected:
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void wheelEvent(QWheelEvent *event);

private:
	Generator *mGenerator;
	QtImageImpl *mImage;

	QLabel *mLabel;

	int mMousePositionX;
	int mMousePositionY;

	float mCenterPointX;
	float mCenterPointY;
	float mViewScale;
};
