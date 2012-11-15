/**
 *
 * File: mainwindow.cpp
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore>
#include <QtGui>

#include "moduleScanner.h"
#include "model/modulesStorage.h"

MainWindow::MainWindow() :
    m_ui(new Ui::MainWindow)
{
    // инициализируем интерфейс
    m_ui->setupUi(this);

    // There is no another way to remove 10px title bar
    QWidget* treeTitle = new QWidget(this);
    m_ui->dockWidget->setTitleBarWidget(treeTitle);

    // устанавливаем кодировки для строк
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));

    m_projectTree = new ProjectTree();
    m_ui->dockWidget->setWidget(m_projectTree);

    connect(m_projectTree, SIGNAL(newPage(QWidget*)),
            this, SLOT(newPage(QWidget*)));
    connect(m_projectTree, SIGNAL(pageSelected(QWidget*)),
            this, SLOT(switchPage(QWidget*)));

    // создаем элементы дерева стандартных страниц
    // проект
    QTreeWidgetItem* ti_projectInfo = m_projectTree->addTiWidget(tr("Project information"));
    QTreeWidgetItem* ti_simulatorParams = m_projectTree->addTiWidget(tr("Simulator params"));
    QTreeWidgetItem* ti_modulesParams = m_projectTree->addTiWidget(tr("Modules"));

    // создаем объекты стандартных страниц
    // проект
    m_project = new ProjectInfoPage();
    // среда
    m_simulatorParams = new SimulatorParamsPage();
    m_modulesPage = new ModulesPage(ti_modulesParams, m_projectTree);

    // создаем стандартные страницы
    m_projectTree->addPage(ti_projectInfo, m_project);

    m_projectTree->addPage(ti_simulatorParams, m_simulatorParams);
    m_projectTree->addPage(ti_modulesParams, m_modulesPage);

    // путь к файлу исходных данных
    m_projectFileName = "";

    // сигналы

    ModulesStorage& storage = ModulesStorage::instance();
    connect(&storage, SIGNAL(registerModule(ModuleDescriptionRaw*)),
            m_modulesPage, SLOT(registerModule(ModuleDescriptionRaw*)));

    // сигнал нажатия кнопок обрабатывает основное окно
    connect(m_ui->actionScanForModules, SIGNAL(triggered()),
            this, SLOT(actionScan()));

    // сигнал нажатия кнопок обрабатывает основное окно
    connect(m_ui->actionSave, SIGNAL(triggered()),
            this, SLOT(actionSave()));

    connect(m_ui->actionOpen, SIGNAL(triggered()),
            this, SLOT(actionOpen()));

    connect(m_ui->actionSaveAs, SIGNAL(triggered()),
            this, SLOT(actionSaveAs()));

    connect(m_ui->actionQuit, SIGNAL(triggered()),
            this, SLOT(actionQuit()));
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::newPage(QWidget *page)
{
    // создаем страницу на объекте страниц
    m_ui->pages->addWidget(page);
}

void MainWindow::switchPage(QWidget *page)
{
    // получаем указатель на страницу и показываем ее
    m_ui->pages->setCurrentWidget(page);
}

void MainWindow::actionScan()
{
    m_modulesPage->clean();

    ModuleScanner scanner;
    ModulesStorage& storage = ModulesStorage::instance();

    connect(&scanner, SIGNAL(moduleScanError(QString, QString)),
            m_modulesPage, SLOT(moduleScanError(QString, QString)));

    connect(&scanner, SIGNAL(moduleScanSuccess(QString, ModuleDescriptionRaw)),
            &storage, SLOT(moduleScanSuccess(QString, ModuleDescriptionRaw)));

    // FIXME: get directory from preferences
    QString modulesDir = QDir::currentPath() + "/modules/";
    scanner.scanDir(modulesDir);
}

void MainWindow::actionSave()
{
    // нажата кнока сохранить

    // если еще не известно куда сохранять
    if (m_projectFileName == "")
        // спрашиваем полщователя
        actionSaveAs();

    // сохраняем
    // saveXml();
}

void MainWindow::actionOpen()
{
    QString projectFileName = QFileDialog::getOpenFileName(this,
                                                           tr("Open File"),
                                                           "", "XML Project files (*.xml)");

    openOrCreateProject(projectFileName);
}

void MainWindow::openOrCreateProject(QString project)
{
    if (project != "") {
        // TODO: спрашивать, надо ли их сохранить

        m_projectFileName = project;

        // TODO: implement this
        // QFile projectFile(m_projectFileName);
        // if (projectFile.exists())
        //     // загружаем данные
        //     loadXml();
        // else
        //     actionSave();

        // m_l_projectName->setText(m_projectFileName);
    }
}

void MainWindow::actionSaveAs()
{
    // нажата кнопка сохранить как

    // спрашиваем пользователя файл
    QString file = QFileDialog::getSaveFileName(this,
                                                tr("Save XML Project file"),
                                                // FIXME: не очень удобно
                                                "project.xml",
                                                tr("XML Project file (*.xml)"));

    if (file != "") {
        m_projectFileName = file;

        // сохраняем данные в xml
        ProjectStorage& project = ProjectStorage::instance();
        project.saveXML(m_projectFileName);
    }
}

void MainWindow::actionQuit()
{
    // нажата кнопка выйти

    // TODO: спрашивать сохранить ли результат
    // выходим
    close();
}
