#pragma once

#include <QDialog>
#include <QLabel>

class FractalModeWindow : public QDialog
{
public:
    virtual ~FractalModeWindow();

    void init();

    void setStartPoint(float x, float y);

private:
    QWidget *mContainer;
    QLabel *mLabel;
};
