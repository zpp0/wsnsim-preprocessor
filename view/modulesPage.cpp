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
    :m_ui(new Ui::ModulesPage), m_selfTreeElement(treeElement), m_projectTree(projectTree)
{
    m_ui->setupUi(this);

    m_modulesInfo = new ModulesInfo(this);
    m_ui->vertical->addWidget(m_modulesInfo);

    // setup warnings table header
    QStringList warningInfo;
    warningInfo << tr("File")
                << tr("Error");

    m_t_warnings =  new QTableWidget();
    m_t_warnings->setColumnCount(warningInfo.size());
    m_t_warnings->setHorizontalHeaderLabels(warningInfo);

    m_ui->vertical->addWidget(m_t_warnings);

    m_paramsTreeElement = m_projectTree->addTiWidget(tr("Params"), m_selfTreeElement);
    m_dependenciesTreeElement = m_projectTree->addTiWidget(tr("Dependencies"), m_selfTreeElement);
}

ModulesPage::~ModulesPage()
{
    delete m_ui;
}

void ModulesPage::registerModule(ModuleDescriptionRaw* module)
{
    m_modules += module;
    m_modulesInfo->addModuleInfo(module);
}

void ModulesPage::moduleScanError(QString file, QString error)
{
    int rows = m_t_warnings->rowCount();
    m_t_warnings->insertRow(rows);

    m_t_warnings->setItem(rows, 0, new QTableWidgetItem(file));
    m_t_warnings->setItem(rows, 1, new QTableWidgetItem(error));
}

void ModulesPage::moduleEnabled(ModuleDescriptionRaw* module)
{
    qDebug() << "enabled" << module->name;

    m_enabledModules += module;
    ProjectStorage& project = ProjectStorage::instance();
    ModuleData* moduleData = project.addModule(module);

    m_modulesPairs[module] = moduleData;

    foreach(DependenciesPage* page, m_dependencies.values())
        moduleEnabled(module);

    createParamsPage(module, moduleData);
    createDependenciesPage(module, moduleData);
}

void ModulesPage::moduleDisabled(ModuleDescriptionRaw* module)
{
    qDebug() << "disabled" << module->name;

    ModuleData* moduleData = m_modulesPairs[module];
    ProjectStorage& project = ProjectStorage::instance();
    project.removeModule(moduleData);

    m_enabledModules.removeOne(module);
    deleteParamsPage(module);
    deleteDependenciesPage(module);

    foreach(DependenciesPage* page, m_dependencies.values())
        moduleDisabled(module);
}

void ModulesPage::createParamsPage(ModuleDescriptionRaw* module, ModuleData* moduleData, bool withParams)
{
    ParamsPage* paramsPage = new ParamsPage(module, moduleData, withParams);
    m_params[module] = paramsPage;

    QTreeWidgetItem* ti_paramsPage = m_projectTree->addTiWidget(module->name, m_paramsTreeElement);
    m_projectTree->addPage(ti_paramsPage, paramsPage);
}

void ModulesPage::deleteParamsPage(ModuleDescriptionRaw* module)
{
    // TODO: check if user change params
    ParamsPage* page = m_params[module];
    m_params.remove(module);

    m_projectTree->removePage(page);
}

void ModulesPage::createDependenciesPage(ModuleDescriptionRaw* module, ModuleData* moduleData, bool withDeps)
{
    DependenciesPage* page = new DependenciesPage(module, moduleData, withDeps);
    m_dependencies[module] = page;

    QTreeWidgetItem* ti_page = m_projectTree->addTiWidget(module->name, m_dependenciesTreeElement);
    m_projectTree->addPage(ti_page, page);
}

void ModulesPage::deleteDependenciesPage(ModuleDescriptionRaw* module)
{
    // TODO: check if user change params
    DependenciesPage* page = m_dependencies[module];
    m_dependencies.remove(module);

    m_projectTree->removePage(page);
}

void ModulesPage::newModule(ModuleData* moduleData)
{
    ModulesStorage& storage = ModulesStorage::instance();

    ModuleDescriptionRaw* module = storage.getDescription(moduleData->moduleInfo["uuid"]);
    if (module) {
        m_enabledModules += module;

        m_modulesPairs[module] = moduleData;

        foreach(DependenciesPage* page, m_dependencies.values())
            moduleEnabled(module);

        createParamsPage(module, moduleData, false);
        createDependenciesPage(module, moduleData, false);
    }
    else {
        // TODO: handle error
    }
}

void ModulesPage::newModuleParam(ModuleData* moduleData, ModuleParam* param)
{
    ModuleDescriptionRaw* module = m_modulesPairs.key(moduleData);
    if (module) {
        ModuleParamRaw* paramRaw;
        foreach(ModuleParamRaw paramR, module->params) {
            if (paramR.name == param->name) {
                paramRaw = &paramR;
                break;
            }
        }

        ParamsPage* page = m_params[module];

        page->createParam(module, paramRaw, param);
    }
    else {
        // TODO: handle error
    }
}

void ModulesPage::newModuleDependence(ModuleData* moduleData, ModuleDependence* dependence)
{
    ModuleDescriptionRaw* module = m_modulesPairs.key(moduleData);
    if (module) {
        DependenciesPage* page = m_dependencies[module];
        page->createDependence(module, dependence);
    }
    else {
        // TODO: handle error
    }
}

void ModulesPage::clean()
{
    foreach(ModuleDescriptionRaw* module, m_enabledModules)
        deleteParamsPage(module);
    foreach(ModuleDescriptionRaw* module, m_enabledModules)
        deleteDependenciesPage(module);

    delete m_modulesInfo;

    m_modulesInfo = new ModulesInfo(this);
    m_ui->vertical->insertWidget(0, m_modulesInfo);
}
