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
#include "projectScanner.h"

#include "model/modulesStorage.h"
#include "settings.h"

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
    QTreeWidgetItem* ti_nodeTypesPage = m_projectTree->addTiWidget(tr("Node Types"));

    // создаем объекты стандартных страниц
    // проект
    m_project = new ProjectInfoPage();
    // среда
    m_simulatorParams = new SimulatorParamsPage();
    m_modulesPage = new ModulesPage(ti_modulesParams, m_projectTree);
    m_nodeTypesPage = new NodeTypesPage(ti_nodeTypesPage, m_projectTree);

    // создаем стандартные страницы
    m_projectTree->addPage(ti_projectInfo, m_project);

    m_projectTree->addPage(ti_simulatorParams, m_simulatorParams);
    m_projectTree->addPage(ti_modulesParams, m_modulesPage);
    m_projectTree->addPage(ti_nodeTypesPage, m_nodeTypesPage);

    // activate the default item
    m_projectTree->setCurrentItem(ti_projectInfo);

    // путь к файлу исходных данных
    m_projectFileName = "";
    m_l_projectFileName = new QLabel();

    m_ui->statusBar->addPermanentWidget(m_l_projectFileName);

    // сигналы

    ModulesStorage& storage = ModulesStorage::instance();
    connect(&storage, SIGNAL(registerModule(ModuleDescriptionRaw*)),
            m_modulesPage, SLOT(registerModule(ModuleDescriptionRaw*)));

    connect(m_modulesPage, SIGNAL(moduleEnable(ModuleDescriptionRaw*)),
            m_nodeTypesPage, SLOT(moduleEnabled(ModuleDescriptionRaw*)));
    connect(m_modulesPage, SIGNAL(moduleDisable(ModuleDescriptionRaw*)),
            m_nodeTypesPage, SLOT(moduleDisabled(ModuleDescriptionRaw*)));

    ProjectStorage& project = ProjectStorage::instance();
    connect(&project, SIGNAL(newModule(ModuleData*)),
            m_modulesPage, SLOT(newModule(ModuleData*)));
    connect(&project, SIGNAL(newModuleParam(ModuleData*, ModuleParam*)),
            m_modulesPage, SLOT(newModuleParam(ModuleData*, ModuleParam*)));
    connect(&project, SIGNAL(newModuleDependence(ModuleData*, ModuleDependence*)),
            m_modulesPage, SLOT(newModuleDependence(ModuleData*, ModuleDependence*)));

    connect(&project, SIGNAL(setNodesNum(int)),
            m_simulatorParams, SLOT(setNodesTotal(int)));

    connect(&project, SIGNAL(newNodeType(NodeTypeData*)),
            m_nodeTypesPage, SLOT(newNodeType(NodeTypeData*)));

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

    connect(m_ui->actionSettings, SIGNAL(triggered()),
            this, SLOT(actionSettings()));

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
    if (page)
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

    QSettings settings("wsnsim", "simulator");
    QString modulesDirectory = settings.value("Modules/Directory").toString();
    QString modulesDir = QDir::currentPath() + modulesDirectory;
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
        m_l_projectFileName->setText(project);

        ProjectScanner scanner;

        connect(&scanner, SIGNAL(setLogFileName(QString)),
                m_simulatorParams, SLOT(setNewFileName(QString)));
        connect(&scanner, SIGNAL(setMaxTime(int)),
                m_simulatorParams, SLOT(setNewTimeValue(int)));
        connect(&scanner, SIGNAL(setTimeUnits(int)),
                m_simulatorParams, SLOT(setNewTimeUnits(int)));

        connect(&scanner, SIGNAL(setAuthor(QString)),
                m_project, SLOT(setNewAuthor(QString)));
        connect(&scanner, SIGNAL(setComment(QString)),
                m_project, SLOT(setNewComment(QString)));
        connect(&scanner, SIGNAL(setKeywords(QString)),
                m_project, SLOT(setNewKeywords(QString)));
        connect(&scanner, SIGNAL(setTitle(QString)),
                m_project, SLOT(setNewTitle(QString)));

        ProjectStorage& project = ProjectStorage::instance();

        connect(&scanner, SIGNAL(setUuid(QString)),
                &project, SLOT(setUuid(QString)));

        connect(&scanner, SIGNAL(addModule(ModuleData)),
                &project, SLOT(addModule(ModuleData)));

        connect(&scanner, SIGNAL(addNodeType(NodeTypeData)),
                &project, SLOT(addNodeType(NodeTypeData)));

        scanner.scanFile(m_projectFileName);

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
        m_l_projectFileName->setText(file);

        // сохраняем данные в xml
        ProjectStorage& project = ProjectStorage::instance();
        project.saveXML(m_projectFileName);
    }
}

void MainWindow::actionSettings()
{
    Settings settings;
    settings.exec();
}

void MainWindow::actionQuit()
{
    // нажата кнопка выйти

    // TODO: спрашивать сохранить ли результат
    // выходим
    close();
}
