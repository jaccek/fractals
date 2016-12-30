#include "fractal_mode_window.h"
#include <QVBoxLayout>

FractalModeWindow::~FractalModeWindow()
{
    printf("FractalModeWindow: destructor\n");
    delete mLabel;
    delete mContainer;
}

void FractalModeWindow::init()
{
    printf("FractalModeWindow: init()\n");
    setGeometry(800, 0, 220, 200);

    mContainer = new QWidget(this);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSizeConstraint(QLayout::SetMinimumSize);
    mContainer->setLayout(layout);

    mLabel = new QLabel();
    mLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    mLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    mLabel->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(mLabel);
}

void FractalModeWindow::setStartPoint(float x, float y)
{
    if (mLabel == nullptr)
    {
        return;
    }
    const int textLength = 64;
    char text[textLength];
    sprintf(text, "center: (%.8f, %.8f)", x, y);
    mLabel->setText(QString(text));
}
