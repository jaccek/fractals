#pragma once

#include "gl_widget.h"
#include "modes/mode.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QLabel>
#include <vector>

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
	virtual void resizeEvent(QResizeEvent *event);
	virtual void closeEvent(QCloseEvent *event);

private slots:
	void changeModeMandelbrot();
	void changeModeJuliaSet();

private:
	typedef void (Window::*SlotFunction)();

	void changeMode(Mode *mode);
	void addMenu(QMenu *parent, const char *actionName, SlotFunction slot);

	std::vector<QMenu*> mMenus;
	GlWidget *mGlWidget;
	Mode *mMode;
};
