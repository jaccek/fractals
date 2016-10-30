#pragma once

#include "gl_widget.h"
#include "renderers/renderer.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QLabel>

class Window : public QMainWindow
{
public:
	Window();
	~Window();

	bool init();
	void afterShow();

protected:
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void wheelEvent(QWheelEvent *event);

private slots:
	void changeModeMandelbrot();
	void changeModeJuliaSet();

private:
	typedef void (Window::*SlotFunction)();

	void changeMode(Renderer *renderer);
	void redrawContent();
	void addMenu(QMenu *parent, const char *actionName, SlotFunction slot);

	GlWidget *mGlWidget;
	Renderer *mRenderer;

	int mMousePositionX;
	int mMousePositionY;

	float mCenterPointX;
	float mCenterPointY;
	float mViewScale;
};
