#include <QApplication>

#include "mainwindow.h"

#define DEFAULT_RECENT_NUMBER 5

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("wsnsim");
    QCoreApplication::setApplicationName("projecteditor");

    // устанавливаем кодировки для строк
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QSettings simsettings("wsnsim", "simulator");

    if(!simsettings.contains("Modules/Directory"))
        simsettings.setValue("Modules/Directory", QDir::currentPath() + "/modules/");

    QTranslator translator_qt;
    QTranslator translator_postprocessor;

    translator_qt.load(":/languages/qt.qm");
    translator_postprocessor.load(":/languages/preprocessor.qm");

    app.installTranslator(&translator_qt);
    app.installTranslator(&translator_postprocessor);

    QSettings resent;
    if (!resent.contains("General/Gui/Recent_number"))
        resent.setValue("General/Gui/Recent_number", DEFAULT_RECENT_NUMBER);

    if (!resent.contains("General/Gui/Recent")) {
        QStringList emptyRecent;
        for(int i = 0; i < DEFAULT_RECENT_NUMBER; i ++)
            emptyRecent.append(" ");

        resent.setValue("General/Gui/Recent", emptyRecent);
    }

    MainWindow w;
    w.show();
    if (argc == 2)
        w.openOrCreateProject(argv[1]);
    return app.exec();
}
