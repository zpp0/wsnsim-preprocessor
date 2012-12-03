/**
 *
 * File: modulePage.cpp
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "modulePage.h"
#include "ui_modulePage.h"

#include "modulesStorage.h"

ModulePage::ModulePage(ModuleDescriptionRaw* module)
    :m_ui(new Ui::ModulePage)
{
    m_ui->setupUi(this);

    m_module = module;

    setTitle(m_module->name);

    m_info = new InfoWidget(module);
    m_ui->info->addWidget(m_info);

    m_param = NULL;
    m_dependencies = NULL;

    if (m_module->params.size() > 0) {
        m_param = new ParamsWidget(module);
        m_ui->params->addWidget(m_param);
    }
    else
        m_ui->tabWidget->removeTab(m_ui->tabWidget->indexOf(m_ui->paramsPage));

    if (m_module->interface.events.size() > 0) {
        // m_dependencies = new DependenciesWidget(module);
        // m_ui->dependencies->addWidget(m_dependencies);
    }
    else
        m_ui->tabWidget->removeTab(m_ui->tabWidget->indexOf(m_ui->eventsPage));

    if (m_module->dependencies.size() > 0) {
        m_dependencies = new DependenciesWidget(module);
        m_ui->dependencies->addWidget(m_dependencies);
    }
    else
        m_ui->tabWidget->removeTab(m_ui->tabWidget->indexOf(m_ui->dependenciesPage));
}

ModuleData ModulePage::getModule()
{
    ModuleData moduleData;
    moduleData.fileName = m_module->fileName;
    moduleData.moduleInfo["ID"] = QString::number(ModulesStorage::instance().getModule(m_module));
    moduleData.moduleInfo["name"] = m_module->name;
    moduleData.moduleInfo["type"] = m_module->type;

    if (m_param)
        moduleData.params = m_param->getParams();
    if (m_dependencies)
        moduleData.dependencies = m_dependencies->getDependencies();

    return moduleData;
}

void ModulePage::setModule(ModuleData module)
{
    if (m_param)
        m_param->setParams(module.params);
    if (m_dependencies)
        m_dependencies->setDependencies(module.dependencies);
}

QList<EventParams> ModulePage::getEvents()
{
    QList<EventParams> events;
    QList<ModuleEventRaw> eventsRaw = m_module->interface.events;
    for (int i = 0; i < eventsRaw.size(); i++) {
        EventParams event;
        event.eventInfo["name"] = eventsRaw[i].name;
        event.eventInfo["moduleID"] = QString::number(ModulesStorage::instance().getModule(m_module));

        QList<ModuleEventParamRaw> arguments = eventsRaw[i].params;
        for (int j = 0; j < arguments.size(); j++) {
            EventArgument arg;
            arg["ID"] = QString::number(arguments[j].ID);
            arg["type"] = arguments[j].type;
            arg["name"] = arguments[j].name;

            event.arguments += arg;
        }
        events += event;
    }

    return events;
}

void ModulePage::setEvents(QList<EventParams>)
{
}

ModulePage::~ModulePage()
{
    delete m_param;
    delete m_dependencies;
    delete m_ui;
}
