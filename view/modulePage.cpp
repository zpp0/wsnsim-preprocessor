/**
 *
 * File: modulePage.cpp
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "modulePage.h"
#include "ui_modulePage.h"

#include "modulesStorage.h"
#include "moduleInfoFormatter.h"

ModulePage::ModulePage(ModuleDescriptionRaw* module)
    :m_ui(new Ui::ModulePage)
{
    m_ui->setupUi(this);

    m_module = module;

    setTitle(m_module->name);

    // m_info = new InfoWidget(module);
    // m_ui->info->addWidget(m_info);

    m_ui->l_module->setText(module->name);
    m_ui->l_type->setText(module->type);
    m_ui->l_description->setText(module->description);

    m_events = NULL;
    m_param = NULL;
    m_dependencies = NULL;

    if (m_module->interface.events.size() > 0) {
        m_events = new EventsWidget(module);
        m_ui->settings->insertWidget(1, m_events);
    }

    if (m_module->dependencies.size() > 0) {
        m_dependencies = new DependenciesWidget(module);
        m_ui->settings->insertWidget(1, m_dependencies);
    }

    if (m_module->params.size() > 0) {
        m_param = new ParamsWidget(module);
        m_ui->settings->insertWidget(1, m_param);
    }
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
    if (m_events)
        return m_events->getEvents();
    else
        return QList<EventParams>();
}

void ModulePage::setEvents(QList<EventParams> events)
{
    if (m_events)
        m_events->setEvents(events);
}

ModulePage::~ModulePage()
{
    delete m_param;
    delete m_dependencies;
    delete m_ui;
}
