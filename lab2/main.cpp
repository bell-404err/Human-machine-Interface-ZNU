#include <QApplication>

#include "MainWindow.h"

int main(int argc, char ** const argv)
{
    const QApplication application(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    mainWindow.adjustSize();
    return QApplication::exec();
}
