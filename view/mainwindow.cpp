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

#include "settings.h"

#include "modulesStorage.h"
#include "nodesStorage.h"
#include "errorsStorage.h"

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

    // путь к файлу исходных данных
    m_projectFileName = "";
    m_l_projectFileName = new QLabel();

    m_errorsPanel = new ErrorsPanel(this);

    ErrorsStorage& errors = ErrorsStorage::instance();
    connect(&errors, SIGNAL(hasErrors(bool)),
            this, SLOT(hasErrors(bool)));
    connect(&errors, SIGNAL(errorSelected(QWidget*, QWidget*)),
            this, SLOT(errorSelected(QWidget*, QWidget*)));

    connect(&errors, SIGNAL(errorAdded(QWidget*, QWidget*, QString)),
            m_errorsPanel, SLOT(errorAdded(QWidget*, QWidget*, QString)));
    connect(&errors, SIGNAL(errorRemoved(QWidget*, QWidget*)),
            m_errorsPanel, SLOT(errorRemoved(QWidget*, QWidget*)));

    connect(&errors, SIGNAL(hasErrors(bool)),
            m_errorsPanel, SLOT(hasErrors(bool)));

    m_ui->statusBar->addPermanentWidget(m_l_projectFileName);
    m_ui->statusBar->addPermanentWidget(m_errorsPanel);

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

    m_ui->actionClose->setEnabled(false);

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

    connect(m_ui->actionNew, SIGNAL(triggered()),
            this, SLOT(actionNew()));

    connect(m_ui->actionClose, SIGNAL(triggered()),
            this, SLOT(actionClose()));

    connect(m_ui->actionOpen, SIGNAL(triggered()),
            this, SLOT(actionOpen()));

    connect(m_ui->actionSaveAs, SIGNAL(triggered()),
            this, SLOT(actionSaveAs()));

    connect(m_ui->actionSettings, SIGNAL(triggered()),
            this, SLOT(actionSettings()));

    connect(m_ui->actionQuit, SIGNAL(triggered()),
            this, SLOT(actionQuit()));

    connect(m_ui->actionAbout, SIGNAL(triggered()),
            this, SLOT(showAboutDialog()));

    connect(m_ui->actionAbout_Qt, SIGNAL(triggered()),
            this, SLOT(showAboutQtDialog()));

    m_ui->toolBar->addAction(m_ui->actionNew);
    m_ui->toolBar->addAction(m_ui->actionClose);
    m_ui->toolBar->addAction(m_ui->actionOpen);
    m_ui->toolBar->addAction(m_ui->actionSave);
    m_ui->toolBar->addSeparator();
    m_ui->toolBar->addAction(m_ui->actionScanForModules);
    m_ui->toolBar->addSeparator();
    m_ui->toolBar->addAction(m_ui->actionSettings);

    insertActionsRecent();

    actionScan();
}

void MainWindow::setProjectFile(QString file)
{
    if (m_projectFileName == "" && file != "")
        m_ui->actionClose->setEnabled(true);
    if (m_projectFileName != "" && file == "")
        m_ui->actionClose->setEnabled(false);

    m_projectFileName = file;
    m_l_projectFileName->setText(file);
}

void MainWindow::loadProject(QString file)
{
    if (!(QFile::exists(file))) {
        QMessageBox::warning(this, tr("Errors Loading Project"),
                             "File not found",
                             QMessageBox::Close);
        return;
    }

    closeProject();

    setProjectFile(file);

    ProjectStorage& storage = ProjectStorage::instance();

    ProjectParams& project = storage.loadXML(m_projectFileName);

    m_simulatorPage->setParams(project.simulatorParams);
    m_projectPage->setParams(project.projectInfo);
    m_modulesPage->activateModules(project.modules);
    m_nodeTypesPage->setNodeTypes(project.nodeTypes);
    m_modulesPage->setModules(project.modules);
    m_modulesPage->setEvents(project.events.systemEvents);

    if (storage.hasErrors()) {
        QMessageBox::warning(this, tr("Errors Loading Project"),
                             storage.getErrors().join("\n"),
                             QMessageBox::Close);
    }

    insertToRecent(file);
    insertActionsRecent();
}

void MainWindow::saveProject()
{
    ProjectStorage& storage = ProjectStorage::instance();
    ProjectParams& project = storage.getProject();
    project.simulatorParams = m_simulatorPage->getParams();
    project.projectInfo = m_projectPage->getParams();
    project.projectInfo.revision = 0;
    project.modules = m_modulesPage->getModules();
    project.events.systemEvents = m_modulesPage->getEvents();
    project.nodeTypes = m_nodeTypesPage->getNodeTypes();
    project.nodes = NodesStorage::instance().getNodes();

    // сохраняем данные в xml
    storage.saveXML(m_projectFileName);
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

void MainWindow::errorSelected(QWidget* page, QWidget* widget)
{
    switchPage(page);
    m_projectTree->setCurrentWidget(page);
    widget->setFocus(Qt::OtherFocusReason);
}

void MainWindow::switchPage(QWidget *page)
{
    // получаем указатель на страницу и показываем ее
    if (page)
        m_ui->pages->setCurrentWidget(page);
}

void MainWindow::hasErrors(bool yes)
{
    if (yes) {
        m_ui->actionSave->setEnabled(false);
        m_ui->actionSaveAs->setEnabled(false);
    }
    else {
        m_ui->actionSave->setEnabled(true);
        m_ui->actionSaveAs->setEnabled(true);
    }
}

void MainWindow::insertToRecent(QString fileName)
{
    int recentNumber = QSettings().value("General/Gui/Recent_number").toInt();

    bool repeated = false;
    bool inserted = false;
    QStringList recentNames = QSettings().value("General/Gui/Recent").toStringList();
    for (int i = 0; i < recentNumber; i ++) {
        if (recentNames[i] == " ") {
            recentNames[i] = fileName;
            inserted = true;
            break;
        }
        else if (recentNames[i] == fileName) {
            repeated = true;
            break;
        }
    }

    if (!inserted && !repeated) {
        for (int i = 0; i < recentNumber; i ++) {
            if (i == recentNumber - 1)
                recentNames[i] = fileName;
            else
                recentNames[i] = recentNames[i + 1];
        }
    }

    QSettings().setValue("General/Gui/Recent", recentNames);
}

void MainWindow::insertActionsRecent()
{
    m_recentMenu = new QMenu(this);
    m_actionsRecent = new QActionGroup(this);
    QStringList recentFilesNames = QSettings().value("General/Gui/Recent").toStringList();
    for(int i = 0; i < recentFilesNames.size(); i ++) {
        if(recentFilesNames[i] != " ") {
            QString recentFileName = QFileInfo(recentFilesNames[i]).fileName();
            QAction *action = new QAction(("&" + QString::number(i + 1)
                                           + " " + recentFileName.toAscii().data()),
                                          this);

            action->setData(recentFilesNames[i]);
            m_actionsRecent->addAction(action);

            connect(m_actionsRecent->actions()[i], SIGNAL(triggered()),
                    this, SLOT(openRecentProject()));
        }
    }
    m_recentMenu->addActions(m_actionsRecent->actions());
    m_ui->actionRecent_projects->setMenu(m_recentMenu);
}

void MainWindow::openRecentProject()
{
    QAction* action = qobject_cast<QAction*>(sender());
    if(action)
        loadProject(action->data().toString());
}

void MainWindow::actionScan()
{
    m_modulesPage->clean();

    ModuleScanner scanner;
    ModulesStorage& storage = ModulesStorage::instance();

    storage.clear();

    connect(&scanner, SIGNAL(moduleScanError(QString, QString)),
            m_modulesPage, SLOT(moduleScanError(QString, QString)));

    connect(&scanner, SIGNAL(moduleScanSuccess(QString, ModuleDescriptionRaw)),
            &storage, SLOT(moduleScanSuccess(QString, ModuleDescriptionRaw)));

    QSettings settings("wsnsim", "simulator");
    QString modulesDirectory = settings.value("Modules/Directory").toString();
    scanner.scanModulesDir(modulesDirectory);
}

void MainWindow::actionSave()
{
    // нажата кнока сохранить

    // если еще не известно куда сохранять
    if (m_projectFileName == "")
        // спрашиваем полщователя
        actionSaveAs();
    else
        saveProject();
}

void MainWindow::actionOpen()
{
    QString projectFileName = QFileDialog::getOpenFileName(this,
                                                           tr("Open File"),
                                                           "", "XML Project files (*.xml)");

    if (projectFileName != "")
        loadProject(projectFileName);
}

void MainWindow::openOrCreateProject(QString project)
{
    if (project != "") {
        // TODO: спрашивать, надо ли их сохранить

        if (QFile::exists(project))
            loadProject(project);
        else
            setProjectFile(project);
    }
}

void MainWindow::closeProject()
{
    m_simulatorPage->clear();
    m_projectPage->clear();
    m_modulesPage->clear();
    m_nodeTypesPage->clear();
    ModulesStorage::instance().clean();
    NodesStorage::instance().clean();

    setProjectFile("");
}

void MainWindow::actionNew()
{
    // спрашиваем пользователя файл
    QString file = QFileDialog::getSaveFileName(this,
                                                tr("Save XML Project file"),
                                                // FIXME: не очень удобно
                                                "project.xml",
                                                tr("XML Project file (*.xml)"));

    if (file != "") {
        closeProject();
        setProjectFile(file);
    }
}

void MainWindow::actionClose()
{
    closeProject();
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
        setProjectFile(file);

        saveProject();
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

void MainWindow::showAboutDialog()
{
    QFile file(":/about/about.txt");

    file.open(QFile::ReadOnly);

    QTextStream stream(&file);

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    stream.setCodec(codec);

    QMessageBox::about(this, tr("About"), stream.readAll());
}

void MainWindow::showAboutQtDialog()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}
