/**
 * File: interfaceInfo.cpp
 * Description: Module params widget
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "interfaceInfo.h"
#include "ui_interfaceInfo.h"

#include "projectStorage.h"

InterfaceInfo::InterfaceInfo(ModuleDescriptionRaw* module, ModuleDependence* dependence)
    : m_ui(new Ui::InterfaceInfo), m_module(module), m_dependence(dependence)
{
    m_ui->setupUi(this);

    m_ui->l_name->setText(m_dependence->name);

    connect(m_ui->cb_modules, SIGNAL(activated(int)),
            this, SLOT(setDependence(int)));
}

void InterfaceInfo::moduleEnabled(ModuleDescriptionRaw* module)
{
    m_possibleDependencies += module;
}

void InterfaceInfo::moduleDisabled(ModuleDescriptionRaw* module)
{
    m_possibleDependencies.removeOne(module);
}

void InterfaceInfo::isValidDependence(ModuleDescriptionRaw* module)
{
    if (module->type == m_dependence->type) {
        // TODO: check for the interface compatibility

        ProjectStorage& storage = ProjectStorage::instance();
        quint16 moduleID = storage.getModuleID(module);

        addValidDependence(module->name, moduleID);
    }
}

void InterfaceInfo::addValidDependence(QString moduleName, quint16 moduleID)
{
    int count = m_ui->cb_modules->count();
    m_ui->cb_modules->addItem(moduleName);
    m_dependencies[count+1] = moduleID;
}

void InterfaceInfo::setDependence(int index)
{
    int moduleID = m_dependencies[index];
    m_dependence->moduleID = moduleID;
}

InterfaceInfo::~InterfaceInfo()
{
    delete m_ui;
}
