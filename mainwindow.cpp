#include <QFileDialog>

#include <QtCore>

#include <QMessageBox>
#include <QStatusBar>
#include <QLabel>
#include <QDir>

#include <QTextCodec>
#include <QString>

#include <QPluginLoader>

#include "projectParams.h"

#include <QLibrary>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow() :
    QMainWindow(),
    m_ui(new Ui::MainWindow)
{
    // инициализируем интерфейс
    m_ui->setupUi(this);

    // устанавливаем кодировки для строк
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));

    // FUCK! There is no another way to remove 10px title bar
    QWidget* treeTitle = new QWidget(this);
    m_ui->dockWidget->setTitleBarWidget(treeTitle);
    
    // создаем объекты стандартных страниц
    // проект
    m_project = new ProjectInfoPage();
    // среда
    m_simulatorParams = new SimulatorParamsPage();
    
    // создаем элементы дерева стандартных страниц
    // проект
    m_ti_project = addTiWidget("Параметры проекта");
    // размеры
    m_ti_simulatorParams = addTiWidget("Параметры симулятора");

    // создаем стандартные страницы
    addPage(m_ti_project, m_project);
    addPage(m_ti_simulatorParams, m_simulatorParams);

    // путь к файлу исходных данных
    m_projectFileName = "";

    QDir myDir(QDir::currentPath() + "/modules");
    QStringList plugins = myDir.entryList(QStringList() << "*.so" << "*.dll");

    foreach(QString plugin, plugins) {
        QPluginLoader loader(QDir::currentPath() + "/modules/" + plugin);
        QObject* plugin = loader.instance();
        // qDebug() << plugin;
        IModule* module = qobject_cast<IModule *>(plugin);
        m_modules += module;

        if (!module->moduleInfo.params.empty()) {
            ParamsPage* moduleParams = new ParamsPage();
            moduleParams->setPage(module->moduleInfo.params,
                                  module->moduleInfo.name,
                                  module->moduleInfo.version,
                                  module->moduleInfo.description,
                                  module->moduleInfo.paramDescription);
            QTreeWidgetItem* t_scene = addTiWidget("Параметры " + module->moduleInfo.name);
        
            addPage(t_scene, moduleParams);

            m_paramsPages[module->moduleInfo.name] = moduleParams;
        }
    }    
    
    // сигналы

    // сигнал о нажатии на элемент дерева обрабатывает основное окно
    connect(m_ui->tr_options, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)),
            this, SLOT(changePage(QTreeWidgetItem*, QTreeWidgetItem*)));

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

void MainWindow::changePage(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    // нажат элемент дерева - надо показать соответствующую страницу

    // если элемент дерева нажат повторно, то просто выходим
    if (current == previous)
        return;

    // иначе получаем указатель на страницу и показываем ее
    m_ui->pages->setCurrentWidget(m_h_pages.value(current));
}

QTreeWidgetItem* MainWindow::addTiWidget(QString name, QTreeWidgetItem* parent)
{
    // добавляем элемент дерева
    QTreeWidgetItem *ti_widget;

    // если указан родитель
    if (parent)
        // то новый элемент дерева будет дочерним от родительского
        ti_widget = new QTreeWidgetItem(parent);
    else
        // иначе новый элемент будет на верхнем уровне дерева
        ti_widget = new QTreeWidgetItem(m_ui->tr_options);

    // выставляем имя элементу
    ti_widget->setText(0, name);
    
    // возвращаем его
    return ti_widget;
}

void MainWindow::addPage(QString m_p_name, QWidget *page, QTreeWidgetItem* parent)
{
    // создаем страницу на объекте страниц
    m_ui->pages->addWidget(page);
    
    // создаем новый элемент дерева для этой страницы
    QTreeWidgetItem *ti_page = addTiWidget(m_p_name, parent);
    
    // запоминаем связь между этими страницами
    m_h_pages.insert(ti_page, page);
}

void MainWindow::addPage(QTreeWidgetItem* ti_page, QWidget *page)
{
    // создаем страницу на объекте страниц
    m_ui->pages->addWidget(page);
    
    // запоминаем связь между переданным элементом дерева и новой страницой
    m_h_pages.insert(ti_page, page);
}

void MainWindow::saveXml()
{
    // запись данных в xml
    ProjectParams projectParams;
    projectParams.version = "0.6.0";
    projectParams.projectInfo = m_project->getParams();
    projectParams.simulatorParams = m_simulatorParams->getParams();

    foreach(QString moduleName, m_paramsPages.keys())
        projectParams.modulesParams += m_paramsPages[moduleName]->getParams();

    Events events;
    
    quint8 eventID = 0;
    foreach (IModule* module, m_modules) {
        foreach (QString eventName, module->interfaceInfo.events.keys()) {
            EventParams eventParams;
            
            eventParams.eventInfo["ID"] = QString::number(eventID);
            eventParams.eventInfo["name"] = eventName;
            eventParams.eventInfo["group"] = "";

            quint8 eventArgID = 0;

            QPair<QString, QString> eventArg;
            
            foreach (eventArg, module->interfaceInfo.events[eventName]) {
                EventArgument argument;
                argument["ID"] = QString::number(eventArgID);
                argument["name"] = eventArg.first;
                argument["type"] = eventArg.second;
                eventParams.arguments += argument;
                eventArgID++;
            }
            
            events.systemEvents += eventParams;
            eventID++;
        }
    }
    
    projectParams.events = events;

    QList<LogFileInfo> logs;
    QList<QString> logFileNames;
    int number = 0;
    foreach(QString name, m_logs) {
        LogFileInfo log;
        log["ID"] = QString::number(number++);
        log["name"] = name;
        logFileNames += name;
        logs += log;
    }

    QString newLog = projectParams.simulatorParams.logFile;
    if (!logFileNames.contains(newLog)) {
        LogFileInfo log;
        log["ID"] = QString::number(number++);
        log["name"] = newLog;
        logs += log;
    }

    projectParams.logFiles = logs;

    QDir myDir(QDir::currentPath());
    QStringList projectLib = myDir.entryList(QStringList() << "*projectData.so" << "*projectData.dll");

    qDebug() << projectLib << QDir::currentPath() + "/" + projectLib[0];
    QLibrary projectDataLib(QDir::currentPath() + "/" + projectLib[0]);
    projectDataLib.load();

    if(!projectDataLib.isLoaded()) {
        qDebug() << "Error load library";
    }        

    // FIXME: make it easy
    typedef void(*projectDataSave) (QString& projectFileName, QString* errorMessage, ProjectParams params);
    projectDataSave pd = (projectDataSave) projectDataLib.resolve("save");

    QString errorMessage;
    QString projectFile;

    pd(m_projectFileName, &errorMessage, projectParams);
}

void MainWindow::loadXml()
{
    QDir myDir(QDir::currentPath());
    QStringList projectLib = myDir.entryList(QStringList() << "*projectData.so" << "*projectData.dll");
    // QStringList projectLib = myDir.entryList(QStringList() << "*.so" << "*.dll");

    QLibrary projectDataLib(QDir::currentPath() + "/" + projectLib[0]);
    // QLibrary projectDataLib("./libprojectData");
    projectDataLib.load();

    if(!projectDataLib.isLoaded()) {
        // TODO: throw good exception
        qDebug() << "Error load library";
        throw;
        // return projectParams;
    }

    // FIXME: make it easy
    typedef ProjectParams(*projectDataLoad) (QString& projectFileName, QString* errorMessage);
    projectDataLoad pd = (projectDataLoad) projectDataLib.resolve("load");

    QString errorMessage;
    QString projectFile;

    ProjectParams projectParams = pd(m_projectFileName, &errorMessage);

    m_simulatorParams->setParams(projectParams.simulatorParams);
    m_project->setParams(projectParams.projectInfo);
    foreach(ModuleParams moduleParams, projectParams.modulesParams)
        m_paramsPages[moduleParams.moduleName]->setParams(moduleParams.params);

    m_logs.erase(m_logs.begin(), m_logs.end());

    foreach(LogFileInfo logInfo, projectParams.logFiles)
        m_logs += logInfo["name"];
}

void MainWindow::actionSave()
{
    // нажата кнока сохранить

    // если еще не известно куда сохранять
    if (m_projectFileName == "")
        // спрашиваем полщователя
        actionSaveAs();

    // сохраняем
    saveXml();
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

        QFile projectFile(m_projectFileName);
        if (projectFile.exists())
            // загружаем данные
            loadXml();
        else
            actionSave();
        
        // m_l_projectName->setText(m_projectFileName);
    }
}

void MainWindow::actionSaveAs()
{
    // нажата кнопка сохранить как

    // спрашиваем пользователя файл
    m_projectFileName = QFileDialog::getSaveFileName(this,
                                                     tr("Save XML Project file"),
                                                     // FIXME: не очень удобно
                                                     "project.xml",
                                                     tr("XML Project file (*.xml)"));

    // сохраняем данные в xml
    saveXml();
}

void MainWindow::actionQuit()
{
    // нажата кнопка выйти

    // TODO: спрашивать сохранить ли результат
    // выходим
    close();
}
