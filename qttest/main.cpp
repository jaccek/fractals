#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QLabel>

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

    return app.exec();
}
