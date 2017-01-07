#include "qt_image_impl.h"

QtImageImpl::QtImageImpl()
{
    mImage = nullptr;
}

QtImageImpl::~QtImageImpl()
{
    if (mImage != nullptr)
    {
        delete mImage;
    }
}

void QtImageImpl::create(int width, int height)
{
    mImage = new QImage(width, height, QImage::Format_ARGB32);
}

int QtImageImpl::getWidth()
{
    if (mImage == nullptr)
    {
        return 0;
    }
    return mImage->width();
}

int QtImageImpl::getHeight()
{
    if (mImage == nullptr)
    {
        return 0;
    }
    return mImage->height();
}

Color QtImageImpl::getColor(int x, int y)
{
    QRgb color = mImage->pixel(x, y);

    float r = (float) qRed(color) / 255.0f;
    float g = (float) qGreen(color) / 255.0f;
    float b = (float) qBlue(color) / 255.0f;

    return Color(r, g, b);
}

void QtImageImpl::setColor(int x, int y, Color &color)
{
    mImage->setPixel(x, y, color.toUint());
}

QImage* QtImageImpl::getImage()
{
    return mImage;
}
