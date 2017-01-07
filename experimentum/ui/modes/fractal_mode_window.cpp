#include "fractal_mode_window.h"
#include <QVBoxLayout>

FractalModeWindow::~FractalModeWindow()
{
    printf("FractalModeWindow: destructor\n");
    delete mDrawStartPointCheckbox;
    delete mStartPointLabel;
    delete mContainer;
}

void FractalModeWindow::init(FractalMode *fractalMode)
{
    printf("FractalModeWindow: init()\n");
    mFractalMode = fractalMode;

    setGeometry(800, 0, 250, 200);

    mContainer = new QWidget(this);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSizeConstraint(QLayout::SetMinimumSize);
    mContainer->setLayout(layout);

    mStartPointLabel = new QLabel();
    layout->addWidget(mStartPointLabel);

    mDrawStartPointCheckbox = new QCheckBox("Draw start point");
    mDrawStartPointCheckbox->setCheckState(Qt::Checked);
    connect(mDrawStartPointCheckbox, &QCheckBox::stateChanged, this, &FractalModeWindow::drawingStartPointCheckboxToggled);
    layout->addWidget(mDrawStartPointCheckbox);
}

void FractalModeWindow::setStartPoint(float x, float y)
{
    if (mStartPointLabel == nullptr)
    {
        return;
    }
    const int textLength = 64;
    char text[textLength];
    sprintf(text, "start point: (%.8f, %.8f)", x, y);
    mStartPointLabel->setText(QString(text));
}

void FractalModeWindow::drawingStartPointCheckboxToggled()
{
    mFractalMode->setDrawStartPoint(mDrawStartPointCheckbox->checkState() == Qt::Checked);
}
