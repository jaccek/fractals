#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QLabel>
#include <dlfcn.h>
#include "common_class.h"

typedef CommonClass* (*Function)();

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QMainWindow *window = new QMainWindow();

    window->resize(800, 600);

    QWidget *centralWidget = new QWidget(window);

    QImage image(800, 500, QImage::Format_RGB888);
    image.setPixel(400, 300, 0xffff0000);

    QLabel *label = new QLabel(centralWidget);
    label->setPixmap(QPixmap::fromImage(image));

    QMenuBar *menuBar = new QMenuBar(centralWidget);
    QMenu *menu = new QMenu("menu");
    menu->addAction(new QAction("test", menu));
    menuBar->addMenu(menu);

    window->setCentralWidget(centralWidget);
    window->show();

    printf("1\n");
    void *myLib = dlopen("./libsimplelib.so", RTLD_NOW);
    printf("2\n");
    CommonClass* (*abc)();
    abc = (Function) dlsym(myLib, "getClass");
    printf("3\n");
    CommonClass *obj = (CommonClass*) abc();
    printf("4\n");
    obj->printNumber(143);
    printf("5\n");
    delete obj;
    dlclose(myLib);
    printf("6\n");

    return 0;//app.exec();
}
