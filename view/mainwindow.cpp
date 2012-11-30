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

#include "settings.h"
#include "modulesStorage.h"
#include "nodesStorage.h"

MainWindow::MainWindow() :
    m_ui(new Ui::MainWindow)
{
    // инициализируем интерфейс
    m_ui->setupUi(this);

    // There is no another way to remove 10px title bar
    QWidget* treeTitle = new QWidget(this);
    m_ui->dockWidget->setTitleBarWidget(treeTitle);

    m_projectTree = new ProjectTree();
    m_ui->dockWidget->setWidget(m_projectTree);

    connect(m_projectTree, SIGNAL(newPage(QWidget*)),
            this, SLOT(newPage(QWidget*)));
    connect(m_projectTree, SIGNAL(pageSelected(QWidget*)),
            this, SLOT(switchPage(QWidget*)));

    // создаем элементы дерева стандартных страниц
    // проект
    QTreeWidgetItem* ti_projectPage = m_projectTree->addTiWidget(tr("Project information"));
    QTreeWidgetItem* ti_simulatorPage = m_projectTree->addTiWidget(tr("Simulator params"));
    QTreeWidgetItem* ti_modulesParams = m_projectTree->addTiWidget(tr("Modules"));
    QTreeWidgetItem* ti_nodeTypesPage = m_projectTree->addTiWidget(tr("Node Types"));

    // создаем объекты стандартных страниц
    // проект
    m_projectPage = new ProjectPage();
    // среда
    m_simulatorPage = new SimulatorPage();
    m_modulesPage = new ModulesPage(ti_modulesParams, m_projectTree);
    m_nodeTypesPage = new NodeTypesPage(ti_nodeTypesPage, m_projectTree);

    // создаем стандартные страницы
    m_projectTree->addPage(ti_projectPage, m_projectPage);

    m_projectTree->addPage(ti_simulatorPage, m_simulatorPage);
    m_projectTree->addPage(ti_modulesParams, m_modulesPage);
    m_projectTree->addPage(ti_nodeTypesPage, m_nodeTypesPage);

    // activate the default item
    m_projectTree->setCurrentItem(ti_projectPage);

    // путь к файлу исходных данных
    m_projectFileName = "";
    m_l_projectFileName = new QLabel();

    m_ui->statusBar->addPermanentWidget(m_l_projectFileName);

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
    m_modulesPage->clear();

    ModuleScanner scanner;
    ModulesStorage& storage = ModulesStorage::instance();

    connect(&scanner, SIGNAL(moduleScanError(QString, QString)),
            m_modulesPage, SLOT(moduleScanError(QString, QString)));

    connect(&scanner, SIGNAL(moduleScanSuccess(QString, ModuleDescriptionRaw)),
            &storage, SLOT(moduleScanSuccess(QString, ModuleDescriptionRaw)));

    QSettings settings("wsnsim", "simulator");
    QString modulesDirectory = settings.value("Modules/Directory").toString();
    scanner.scanDir(modulesDirectory);
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

        ProjectParams project;
        project.simulatorParams = m_simulatorPage->getParams();
        project.projectInfo = m_projectPage->getParams();
        project.projectInfo.revision = 0;
        project.modules = m_modulesPage->getModules();
        project.events.systemEvents = m_modulesPage->getEvents();
        project.nodeTypes = m_nodeTypesPage->getNodeTypes();

        project.nodes = NodesStorage::instance().getNodes();

        // сохраняем данные в xml
        ProjectStorage storage;
        storage.saveXML(project, m_projectFileName);
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
