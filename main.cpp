#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // Q_INIT_RESOURCE(configdialog);

    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    if (argc == 2)
        w.openOrCreateProject(argv[1]);
    return app.exec();
}
