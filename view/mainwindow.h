#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QHash>
#include <QLabel>

#include "projectInfo.h"
#include "paramsPage.h"
#include "modulesPage.h"
#include "simulatorParams.h"

#include "projectTree.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    virtual ~MainWindow();

    void openOrCreateProject(QString project);

public slots:
    void newPage(QWidget *page);
    void switchPage(QWidget *page);

private:
    Ui::MainWindow *m_ui;

    // путь к файлу проекта
    QString m_projectFileName;

    ProjectTree* m_projectTree;

    // стандартные страницы
    // проект
    ProjectInfoPage *m_project;
    // среда
    SimulatorParamsPage *m_simulatorParams;
    ModulesPage *m_modulesPage;

private slots:
    // события
    // нажата кнопка сохранить
    void actionSave();
    // сохранить как
    void actionSaveAs();
    // открыть проект
    void actionOpen();
    // выйти
    void actionQuit();

    // scan for modules
    void actionScan();
};

#endif // MAINWINDOW_H
