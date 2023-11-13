#include <QApplication>
#include "gui.h"

int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath("./");
    QApplication a(argc, argv);
    GUI gui;
    gui.show();
    return a.exec();
}
