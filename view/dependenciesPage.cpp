/**
 * File: dependenciesPage.cpp
 * Description: Module params widget
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "dependenciesPage.h"
#include "ui_dependenciesPage.h"

#include "projectStorage.h"

DependenciesPage::DependenciesPage(ModuleDescriptionRaw* module, ModuleData* moduleData, bool withDeps)
    : m_ui(new Ui::DependenciesPage)
{
    m_ui->setupUi(this);

    m_module = module;
    m_moduleData = moduleData;

    setTitle(m_module->name);

    if (withDeps == true) {
        ProjectStorage& storage = ProjectStorage::instance();

        foreach(ModuleDependRaw dep, module->dependencies) {
            ModuleDependence* dependence = storage.addModuleDependence(moduleData);
            dependence->name = dep.name;
            dependence->type = dep.type;

            createDependence(module, dependence);
        }
    }
}

void DependenciesPage::createDependence(ModuleDescriptionRaw* module, ModuleDependence* dependence)
{
    InterfaceInfo* interface = new InterfaceInfo(module, dependence);
    foreach(ModuleDescriptionRaw* module, m_modules)
        interface->moduleEnabled(module);

    m_ui->layout->insertWidget(0, interface);
    m_interfaces += interface;
}

void DependenciesPage::moduleEnabled(ModuleDescriptionRaw* module)
{
    m_modules += module;

    foreach(InterfaceInfo* interface, m_interfaces)
        interface->moduleEnabled(module);
}

void DependenciesPage::moduleDisabled(ModuleDescriptionRaw* module)
{
    m_modules.removeOne(module);

    foreach(InterfaceInfo* interface, m_interfaces)
        interface->moduleDisabled(module);
}

DependenciesPage::~DependenciesPage()
{
    delete m_ui;
}
