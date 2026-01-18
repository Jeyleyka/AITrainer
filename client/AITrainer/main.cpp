#include "./UI/MainWindow/MainWindow.h"
#include "./UI/Components/PrSettingUp/PrSettingUp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(nullptr);
    w.showMaximized();
    return a.exec();
}
