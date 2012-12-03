#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QHash>
#include <QLabel>

#include "projectPage.h"
#include "modulesPage.h"
#include "simulatorPage.h"
#include "nodeTypesPage.h"

#include "projectTree.h"

#include "errorsPanel.h"

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

private slots:
    void showAboutDialog();
    void showAboutQtDialog();

private:
    Ui::MainWindow *m_ui;

    void loadProject();
    void saveProject();

    // путь к файлу проекта
    QString m_projectFileName;
    QLabel* m_l_projectFileName;

    ErrorsPanel* m_errorsPanel;

    ProjectTree* m_projectTree;

    // стандартные страницы
    // проект
    ProjectPage *m_projectPage;
    // среда
    SimulatorPage *m_simulatorPage;
    ModulesPage *m_modulesPage;
    NodeTypesPage* m_nodeTypesPage;

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

    void actionSettings();

    // scan for modules
    void actionScan();
};

#endif // MAINWINDOW_H
