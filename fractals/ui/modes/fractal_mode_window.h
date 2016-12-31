#pragma once

#include "modes/fractal_mode/fractal_mode.h"
#include <QDialog>
#include <QLabel>
#include <QCheckBox>

class FractalMode;

class FractalModeWindow : public QDialog
{
public:
    virtual ~FractalModeWindow();

    void init(FractalMode *fractalMode);
    void setStartPoint(float x, float y);

private:
    QWidget *mContainer;
    QLabel *mStartPointLabel;
    QCheckBox *mDrawStartPointCheckbox;

    FractalMode *mFractalMode;

signals:
    void drawingStartPointCheckboxToggled();
};
