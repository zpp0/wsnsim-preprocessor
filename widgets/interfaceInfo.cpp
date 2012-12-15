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

#include "moduleInfoFormatter.h"

InterfaceInfo::InterfaceInfo(ModuleDescriptionRaw* module, ModuleDependRaw* dependence)
    : m_ui(new Ui::InterfaceInfo)
{
    m_ui->setupUi(this);

    m_module = module;
    m_dependence = dependence;

    m_ui->l_name->setText(m_dependence->name);
    m_ui->l_type->setText(m_dependence->type);

    ModuleInfoFormatter formatter(m_module);
    foreach(const ModuleFunctionRaw& function, m_dependence->interface.functions)
        m_ui->functions->addWidget(new QLabel(" " + formatter.getFunction(function)));

    foreach(const ModuleEventRaw& event, m_dependence->interface.events)
        m_ui->events->addWidget(new QLabel(" " + formatter.getEvent(event)));

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
    if (enabled && isValidDependence(module))
        addValidDependence(module);
    else {
        int index = m_modules.indexOf(module);
        m_ui->cb_modules->removeItem(index);
        m_modules.removeAt(index);

        if (!m_dependence->optional)
            if (m_modules.isEmpty())
                setError(true);
    }
}

bool InterfaceInfo::isValidDependence(ModuleDescriptionRaw* module)
{
    if (module == m_module)
        return false;

    // check types
    // NOTE: a little hack
    // check if hardware module depends on environment module
    if (m_module->type == "hardware" && m_dependence->type == "environment") {
        // pass if dependence has type "environment" or "hardware"
        if (!((module->type == m_dependence->type) || (module->type == "hardware"))) {
            return false;
        }
    }
    // check dependence type for the other cases
    else if (!(module->type == m_dependence->type))
        return false;

    // check functions
    QList<ModuleFunctionRaw> depFunctions = m_dependence->interface.functions;

    bool match;
    foreach(ModuleFunctionRaw depFunc, depFunctions) {
        match = false;
        foreach(ModuleFunctionRaw modFunc, module->interface.functions) {
            // check name of the function
            if (depFunc.name == modFunc.name
                // WARNING: this is a possible error
                // check args number
                && depFunc.arguments.size() == modFunc.arguments.size()) {
                match = true;
                break;
            }
        }
        if (!match)
            return false;
    }

    // WARNING: arr, too much sophisticated code
    QList<ModuleEventRaw> depEvents = m_dependence->interface.events;
    foreach(ModuleEventRaw depEvent, depEvents) {
        match = false;
        // match events
        foreach(ModuleEventRaw modEvent, module->interface.events) {
            // check name of the event
            if (depEvent.name == modEvent.name) {
                bool paramsMatch = false;

                // match event params
                // if event doesn't have params
                if (depEvent.params.size() == 0)
                    paramsMatch = true;
                // if it has
                else {
                    foreach(const ModuleEventParamRaw& depParam, depEvent.params) {
                        foreach(const ModuleEventParamRaw& modParam, modEvent.params) {
                            // check names and types
                            if (depParam.name == modParam.name && depParam.type == modParam.type) {
                                paramsMatch = true;
                                break;
                            }
                        }
                    }
                }

                if (paramsMatch) {
                    match = true;
                    break;
                }
            }
        }
        if (!match)
            return false;
    }

    return true;
}

void InterfaceInfo::addValidDependence(ModuleDescriptionRaw* module)
{
    m_ui->cb_modules->addItem(module->name);
    m_modules += module;

    if (!m_dependence->optional)
        if (m_modules.size() == 1)
            setError(false);
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
