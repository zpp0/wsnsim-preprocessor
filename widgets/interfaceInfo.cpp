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
    : m_ui(new Ui::InterfaceInfo)
{
    m_ui->setupUi(this);

    m_module = module;
    m_dependence = dependence;

    m_ui->l_name->setText(m_dependence->name);

    m_valueFromProject = false;

    connect(m_ui->cb_modules, SIGNAL(activated(int)),
            this, SLOT(setDependence(int)));
}

void InterfaceInfo::setValue(quint16 moduleID)
{
    m_valueFromProject = true;
    ProjectStorage& storage = ProjectStorage::instance();
    ModuleDescriptionRaw* depModule = storage.getModule(moduleID);

    int index = m_modules.indexOf(depModule);
    setDependence(index);
}

void InterfaceInfo::moduleEnabled(ModuleDescriptionRaw* module)
{
    isValidDependence(module);
}

void InterfaceInfo::moduleDisabled(ModuleDescriptionRaw* module)
{
    int index = m_modules.indexOf(module);
    m_ui->cb_modules->removeItem(index);
    m_modules.removeAt(index);
}

void InterfaceInfo::isValidDependence(ModuleDescriptionRaw* module)
{
    if (module->type == m_dependence->type) {
        // TODO: check for the interface compatibility

        m_modules += module;

        addValidDependence(module->name);
    }
}

void InterfaceInfo::addValidDependence(QString moduleName)
{
    m_ui->cb_modules->addItem(moduleName);
    if (!m_valueFromProject)
        setDependence(m_ui->cb_modules->count() - 1);
}

void InterfaceInfo::setDependence(int index)
{
    if (m_ui->cb_modules->currentText() != "") {
        ModuleDescriptionRaw* module = m_modules[index];
        ProjectStorage& storage = ProjectStorage::instance();
        quint16 moduleID = storage.getModuleID(module);

        m_dependence->moduleID = moduleID;
    }
}

InterfaceInfo::~InterfaceInfo()
{
    delete m_ui;
}
