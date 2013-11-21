#include "src/views/mainwindow.hpp"
#include "src/utils/LogManager.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    Log logger;
    logger << std::endl;
    logger << "Application started." << std::endl;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
