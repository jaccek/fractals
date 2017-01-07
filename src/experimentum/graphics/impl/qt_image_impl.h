#pragma once

#include "../image.h"
#include <QtGui/QImage>

class QtImageImpl : public Image
{
public:
    QtImageImpl();
    virtual ~QtImageImpl();

    virtual void create(int width, int height);

    virtual int getWidth();
    virtual int getHeight();
    virtual Color getColor(int x, int y);

    virtual void setColor(int x, int y, Color &color);

    QImage* getImage();

private:
    QImage *mImage;
};
