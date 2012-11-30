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
    m_t_warnings->setColumnCount(warningInfo.size());
    m_t_warnings->setHorizontalHeaderLabels(warningInfo);

    m_t_warnings->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    m_t_warnings->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    m_t_warnings->setVisible(false);
    m_ui->vertical->addWidget(m_t_warnings);
}

ModulesPage::~ModulesPage()
{
    delete m_ui;
}

void ModulesPage::registerModule(ModuleDescriptionRaw* module)
{
    m_modulesInfo->addModuleInfo(module);
}

void ModulesPage::moduleScanError(QString file, QString error)
{
    if (!m_t_warnings->isVisible())
        m_t_warnings->setVisible(true);

    int rows = m_t_warnings->rowCount();
    m_t_warnings->insertRow(rows);

    m_t_warnings->setItem(rows, 0, new QTableWidgetItem(file));
    m_t_warnings->setItem(rows, 1, new QTableWidgetItem(error));
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
}

void ModulesPage::deleteModulePage(ModuleDescriptionRaw* module)
{
    // TODO: check if user change params
    ModulePage* page = m_modules[module];
    m_modules.remove(module);

    m_projectTree->removePage(page);
    delete page;
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
        ModuleDescriptionRaw* module = ModulesStorage::instance().getModule(moduleData.fileName);
        if (module)
            m_modulesInfo->enableModuleInfo(module);
        else {
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
}

void ModulesPage::clear()
{
    foreach(ModuleDescriptionRaw* module, m_modules.keys())
        deleteModulePage(module);

    delete m_modulesInfo;

    m_modulesInfo = new ModulesInfo(this);
    m_ui->vertical->insertWidget(0, m_modulesInfo);
}
