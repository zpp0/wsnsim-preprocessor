#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // Q_INIT_RESOURCE(configdialog);

    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("wsnsim");
    QCoreApplication::setApplicationName("projecteditor");

    QSettings settings;

    if(!settings.contains("Modules/Directory"))
        settings.setValue("Modules/Directory", "/modules/");

    QTranslator translator_qt;
    QTranslator translator_postprocessor;

    translator_qt.load(":/languages/qt.qm");
    translator_postprocessor.load(":/languages/preprocessor.qm");

    app.installTranslator(&translator_qt);
    app.installTranslator(&translator_postprocessor);

    MainWindow w;
    w.show();
    if (argc == 2)
        w.openOrCreateProject(argv[1]);
    return app.exec();
}
