#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QHash>
#include <QLabel>

#include "paramsPage.h"
#include "projectInfo.h"
#include "simulatorParams.h"

#include "IModule.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    virtual ~MainWindow();
    
private:

    // добавление страницы в список страниц
    void addPage(QString p_name, QWidget *page, QTreeWidgetItem* parent = 0);
    void addPage(QTreeWidgetItem* ti_page, QWidget *page);

    // создание элемента дерева
    QTreeWidgetItem* addTiWidget(QString name, QTreeWidgetItem* parent = 0);

    // запись данных в XML
    void saveXml();
    // чтение данных из XML
    void loadXml();
    
    Ui::MainWindow *m_ui;

    // массив страниц
    QHash <QTreeWidgetItem*, QWidget*> m_h_pages;

    // путь к файлу проекта
    QString m_projectFileName;

    // стандартные страницы
    // проект
    ProjectInfoPage *m_project;
    // среда
    SimulatorParamsPage *m_simulatorParams;

    // объекты дерева, к ним привязываюся обекты страниц
    // проект
    QTreeWidgetItem *m_ti_project;
    // среда
    QTreeWidgetItem *m_ti_simulatorParams;

    QList<IModule*> m_modules;
    QMap<QString, ParamsPage*> m_paramsPages;
    
    // версия
    static const quint16 m_version = 1;
    
    // QUndoStack *undostack;
    
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

public slots:
    // пользователь перешел на другую страницу
    void changePage(QTreeWidgetItem *current, QTreeWidgetItem *previous);
};

#endif // MAINWINDOW_H
