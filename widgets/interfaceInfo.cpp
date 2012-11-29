/**
 * File: interfaceInfo.cpp
 * Description: Module params widget
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "interfaceInfo.h"
#include "ui_interfaceInfo.h"

#include "modulesStorage.h"

InterfaceInfo::InterfaceInfo(ModuleDescriptionRaw* module, ModuleDependRaw* dependence)
    : m_ui(new Ui::InterfaceInfo)
{
    m_ui->setupUi(this);

    m_module = module;
    m_dependence = dependence;

    m_ui->l_name->setText(m_dependence->name);

    ModulesStorage& storage = ModulesStorage::instance();

    QList<ModuleDescriptionRaw*> modules = storage.getEnabled();
    foreach(ModuleDescriptionRaw* module, modules)
        moduleEnabled(module, true);

    connect(&storage, SIGNAL(moduleEnabled(ModuleDescriptionRaw*, bool)),
            this, SLOT(moduleEnabled(ModuleDescriptionRaw*, bool)));
}

void InterfaceInfo::moduleEnabled(ModuleDescriptionRaw* module, bool enabled)
{
    if (enabled)
        isValidDependence(module);
    else {
        int index = m_modules.indexOf(module);
        m_ui->cb_modules->removeItem(index);
        m_modules.removeAt(index);
    }
}

void InterfaceInfo::isValidDependence(ModuleDescriptionRaw* module)
{
    if (module->type == m_dependence->type) {
        // TODO: check for the interface compatibility
        addValidDependence(module->name);
        m_modules += module;
    }
}

void InterfaceInfo::addValidDependence(QString moduleName)
{
    m_ui->cb_modules->addItem(moduleName);
}

void InterfaceInfo::setValue(ModuleDependence dependence)
{
    ModuleDescriptionRaw* module = ModulesStorage::instance().getModule(dependence.moduleID);
    int index = m_modules.indexOf(module);
    if (index != -1)
        m_ui->cb_modules->setCurrentIndex(index);
    // TODO: errors handling
}

ModuleDependence InterfaceInfo::getValue()
{
    ModuleDependence dependence;

    int index = m_ui->cb_modules->currentIndex();
    ModuleDescriptionRaw* module = m_modules[index];
    quint16 moduleID = ModulesStorage::instance().getModule(module);

    dependence.name = m_dependence->name;
    dependence.type = m_dependence->type;
    dependence.moduleID = moduleID;

    return dependence;
}

InterfaceInfo::~InterfaceInfo()
{
    delete m_ui;
}
