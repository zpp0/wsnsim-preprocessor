/**
 * File: interfaceInfo.cpp
 * Description: Module params widget
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "interfaceInfo.h"
#include "ui_interfaceInfo.h"

#include "modulesStorage.h"
#include "errorsStorage.h"

InterfaceInfo::InterfaceInfo(ModuleDescriptionRaw* module, ModuleDependRaw* dependence)
    : m_ui(new Ui::InterfaceInfo)
{
    m_ui->setupUi(this);

    m_module = module;
    m_dependence = dependence;

    m_ui->l_name->setText(m_dependence->name);

    ModulesStorage& storage = ModulesStorage::instance();

    if (!m_dependence->optional)
        setError(true);

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

        if (!m_dependence->optional)
            if (m_modules.isEmpty())
                setError(true);
    }
}

void InterfaceInfo::isValidDependence(ModuleDescriptionRaw* module)
{
    if (module->type == m_dependence->type) {
        // TODO: check for the interface compatibility
        addValidDependence(module->name);
        m_modules += module;

        if (!m_dependence->optional)
            if (m_modules.size() == 1)
                setError(false);
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

    // TODO: global block the saving if index count == 0
    int index = m_ui->cb_modules->currentIndex();
    ModuleDescriptionRaw* module = m_modules[index];
    quint16 moduleID = ModulesStorage::instance().getModule(module);

    dependence.name = m_dependence->name;
    dependence.type = m_dependence->type;
    dependence.moduleID = moduleID;
    if (!m_dependence->interface.functions.isEmpty())
        dependence.hasFunctions = "true";
    else
        dependence.hasFunctions = "false";

    foreach(ModuleEventRaw event, m_dependence->interface.events) {
        foreach(ModuleEventParamRaw param, event.params) {
            EventArgument arg;
            arg["name"] = param.name;
            arg["ID"] = QString::number(param.ID);
            arg["type"] = param.type;
            dependence.events[event.name] += arg;
        }
    }

    return dependence;
}

void InterfaceInfo::setError(bool error)
{
    ErrorsStorage::instance().setPossibleError(m_ui->cb_modules, error,
                                               tr("Module") + " " + m_module->name + ": "
                                               + tr("dependence") + " " + m_dependence->name + ": "
                                               + tr("unbinded"));
}

InterfaceInfo::~InterfaceInfo()
{
    delete m_ui;
}
