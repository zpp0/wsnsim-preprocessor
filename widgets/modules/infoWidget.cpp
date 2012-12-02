/**
 *
 * File: infoWidget.h
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "infoWidget.h"
#include "ui_infoWidget.h"

#include "moduleInfoFormatter.h"

InfoWidget::InfoWidget(ModuleDescriptionRaw* module)
    : m_ui(new Ui::InfoWidget)
{
    m_ui->setupUi(this);

    m_module = module;

    m_ui->l_module->setText(module->name);
    m_ui->l_type->setText(module->type);
    m_ui->l_description->setText(module->description);

    ModuleInfoFormatter formatter(m_module);

    if (m_module->interface.functions.size() != 0) {
        QStringList functions = formatter.getFunctions();
        foreach(QString function, functions)
            m_ui->functions->addWidget(new QLabel(function));
    }
    else
        m_ui->g_functions->setVisible(false);

    if (m_module->interface.events.size() != 0) {
        QStringList events = formatter.getEvents();
        foreach(QString event, events)
            m_ui->events->addWidget(new QLabel(event));
    }
    else
        m_ui->g_events->setVisible(false);

    if (m_module->dependencies.size() != 0) {
        QStringList dependencies = formatter.getDependencies();
        foreach(QString dependence, dependencies)
            m_ui->dependencies->addWidget(new QLabel(dependence));
    }
    else
        m_ui->g_dependencies->setVisible(false);
}

InfoWidget::~InfoWidget()
{
    delete m_ui;
}
