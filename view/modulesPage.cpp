/**
 *
 * File: modulesPage.cpp
 * Description: Page of choosing modules from list
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#include "modulesPage.h"
#include "ui_modulesPage.h"

#include "modulesStorage.h"
#include "errorsStorage.h"

#include "luaEditor.h"
#include "moduleScanner.h"

ModulesPage::ModulesPage(QTreeWidgetItem* treeElement, ProjectTree* projectTree)
    :m_ui(new Ui::ModulesPage)
{
    m_ui->setupUi(this);

    m_selfTreeElement = treeElement;
    m_projectTree = projectTree;

    m_modulesInfo = new ModulesInfo(this);
    m_ui->vertical->addWidget(m_modulesInfo);

    // setup warnings table header
    QStringList warningInfo;
    warningInfo << tr("File")
                << tr("Error");

    m_t_warnings = new QTableWidget();
    m_t_warnings->setContextMenuPolicy(Qt::CustomContextMenu);
    m_t_warnings->setColumnCount(warningInfo.size());
    m_t_warnings->setHorizontalHeaderLabels(warningInfo);

    m_t_warnings->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    m_t_warnings->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    connect(m_t_warnings, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(errorsContextMenuRequested(const QPoint &)));

    m_t_warnings->setVisible(false);
    m_ui->vertical->addWidget(m_t_warnings);

    setModulesError(true);
}

ModulesPage::~ModulesPage()
{
    delete m_ui;
}

void ModulesPage::registerModule(ModuleDescriptionRaw* module)
{
    m_modulesInfo->addModuleInfo(module);

    QString moduleFile = ModulesStorage::instance().getModuleFilePath(module->fileName);

    foreach(QString file, m_errors) {
        if (file != moduleFile)
            continue;

        m_t_warnings->removeRow(m_errors.indexOf(file));
        m_errors.removeOne(file);

        if (m_errors.isEmpty())
            m_t_warnings->setVisible(false);

        return;
    }

}

void ModulesPage::moduleScanError(QString file, QString error)
{
    if (!m_t_warnings->isVisible())
        m_t_warnings->setVisible(true);

    int index = m_errors.indexOf(file);
    if (index == -1) {
        int rows = m_t_warnings->rowCount();
        m_t_warnings->insertRow(rows);

        m_errors += file;

        m_t_warnings->setItem(rows, 0, new QTableWidgetItem(file));
        m_t_warnings->setItem(rows, 1, new QTableWidgetItem(error));
    }
    else
        m_t_warnings->setItem(index, 1, new QTableWidgetItem(error));
}

void ModulesPage::moduleEnabled(ModuleDescriptionRaw* module)
{
    createModulePage(module);
    ModulesStorage::instance().enableModule(module, true);
}

void ModulesPage::moduleDisabled(ModuleDescriptionRaw* module)
{
    deleteModulePage(module);
    ModulesStorage::instance().enableModule(module, false);
}

void ModulesPage::createModulePage(ModuleDescriptionRaw* module)
{
    ModulePage* page = new ModulePage(module);
    m_modules[module] = page;

    QTreeWidgetItem* ti_page = m_projectTree->addTiWidget(module->name, m_selfTreeElement);
    m_projectTree->addPage(ti_page, page);

    if (m_modules.size() == 1) {
        setModulesError(false);
        m_selfTreeElement->setExpanded(true);
    }
}

void ModulesPage::deleteModulePage(ModuleDescriptionRaw* module)
{
    // TODO: check if user change params
    ModulePage* page = m_modules[module];
    m_modules.remove(module);

    m_projectTree->removePage(page);
    delete page;

    if (m_modules.isEmpty()) {
        setModulesError(true);
        m_selfTreeElement->setExpanded(false);
    }
}

ModuleDescriptionRaw* ModulesPage::getModuleRaw(ModuleData moduleData)
{
    QList<ModuleDescriptionRaw*> modules = ModulesStorage::instance().getEnabled();
    ModuleDescriptionRaw* module = NULL;
    foreach(ModuleDescriptionRaw* moduleRaw, modules) {
        if (moduleRaw->fileName == moduleData.fileName) {
            module = moduleRaw;
            break;
        }
    }
    return module;
}

QList<ModuleData> ModulesPage::getModules()
{
    QList<ModuleData> modules;

    foreach(ModulePage* page, m_modules.values())
        modules += page->getModule();

    return modules;
}

bool moduleIDLessThan(const ModuleData &s1, const ModuleData &s2)
{
    return s1.moduleInfo["ID"].toUInt() < s2.moduleInfo["ID"].toUInt();
}

void ModulesPage::activateModules(QList<ModuleData> modules)
{
    // sort by moduleID
    qSort(modules.begin(), modules.end(), moduleIDLessThan);

    foreach(ModuleData moduleData, modules) {
        ModulesStorage& storage = ModulesStorage::instance();
        ModuleDescriptionRaw* module = storage.getModule(moduleData.fileName);
        if (module) {
            m_modulesInfo->enableModuleInfo(module);
            storage.setProjectModuleID(moduleData.moduleInfo["ID"].toInt(), moduleData.fileName);
        }
        else {
            storage.addBrokenProjectModule(moduleData.moduleInfo["ID"].toInt());
            // TODO: errors handling
        }
    }
}

void ModulesPage::setModules(QList<ModuleData> modules)
{
    foreach(ModuleData moduleData, modules) {
        ModuleDescriptionRaw* module = getModuleRaw(moduleData);
        if (!module)
            // TODO: errors handling
            continue;
        m_modules[module]->setModule(moduleData);
    }
}

QList<EventParams> ModulesPage::getEvents()
{
    QList<EventParams> events;

    foreach(ModulePage* page, m_modules.values())
        events += page->getEvents();

    return events;
}

void ModulesPage::setEvents(QList<EventParams> events)
{
    foreach(ModuleDescriptionRaw* module, m_modules.keys()) {
        QList<EventParams> moduleEvents;
        quint16 moduleID = ModulesStorage::instance().getModuleFromProject(module);
        foreach(EventParams event, events)
            if (event.eventInfo["moduleID"].toInt() == moduleID)
                moduleEvents += event;

        m_modules[module]->setEvents(moduleEvents);
    }
}

void ModulesPage::errorsContextMenuRequested(const QPoint &p)
{
    QTableWidgetItem* ti_item = m_t_warnings->itemAt(p);
    if (ti_item != NULL) {

        QMenu menu(this);

        QAction* actionOpen = menu.addAction(tr("&Edit"));
        QAction* actionOpenInExternalEditor = menu.addAction(tr("Edit in e&xternal editor"));
        QAction* actionRescan = menu.addAction(tr("Re&scan"));

        QAction *a = menu.exec(m_t_warnings->mapToGlobal(p));

        int row = m_t_warnings->row(ti_item);
        QString file = m_t_warnings->item(row, 0)->text();

        if (a == actionOpen) {
            LuaEditor editor;
            editor.openFile(file);
            editor.exec();
        }

        else if (a == actionOpenInExternalEditor) {
            LuaEditor::openFileInExternalEditor(file);
        }

        else if (a == actionRescan) {
            ModuleScanner scanner;
            ModulesStorage& storage = ModulesStorage::instance();
            connect(&scanner, SIGNAL(moduleScanError(QString, QString)),
                    this, SLOT(moduleScanError(QString, QString)));

            connect(&scanner, SIGNAL(moduleScanSuccess(QString, ModuleDescriptionRaw)),
                    &storage, SLOT(moduleScanSuccess(QString, ModuleDescriptionRaw)));

            scanner.scanFile(file);
        }
    }
}

void ModulesPage::clear()
{
    foreach(ModuleDescriptionRaw* module, m_modules.keys())
        deleteModulePage(module);

    m_modulesInfo->disableAllModules();

    // delete m_modulesInfo;

    // m_modulesInfo = new ModulesInfo(this);
    // m_ui->vertical->insertWidget(0, m_modulesInfo);
}

void ModulesPage::setModulesError(bool error)
{
    ErrorsStorage::instance().setPossibleError(this, m_modulesInfo,
                                               error,
                                               title() + ": " + tr("no modules chosen"));
}

void ModulesPage::clean()
{
    clear();
    m_modulesInfo->clean();

    m_t_warnings->clearContents();
    m_t_warnings->setRowCount(0);
    m_t_warnings->setVisible(false);
    m_errors.clear();
}
