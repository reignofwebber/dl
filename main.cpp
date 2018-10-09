#include <QApplication>

#include "mainwindow.h"
#include "settingsdialog.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
//    MainWindow w;
//    w.show();
    SettingsDialog dlg;
    dlg.show();
    return app.exec();
}
