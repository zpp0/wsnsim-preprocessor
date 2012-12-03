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
        for (int i = 0; i < functions.size(); i++) {
            m_ui->functions->addWidget(new QLabel(functions[i]), i, 0);
            m_ui->functions->addWidget(new QLabel(m_module->interface.functions[i].info), i, 1);
        }
    }
    else
        m_ui->g_functions->setVisible(false);

    if (m_module->interface.events.size() != 0) {
        QStringList events = formatter.getEvents();
        for (int i = 0; i < events.size(); i++) {
            m_ui->events->addWidget(new QLabel(events[i]), i, 0);
            m_ui->events->addWidget(new QLabel(m_module->interface.events[i].info), i, 1);
        }
    }
    else
        m_ui->g_events->setVisible(false);

    if (m_module->dependencies.size() != 0) {
        QStringList dependencies = formatter.getDependencies();
        for (int i = 0; i < dependencies.size(); i++) {
            m_ui->dependencies->addWidget(new QLabel(m_module->dependencies[i].name), i, 0);
            m_ui->dependencies->addWidget(new QLabel(m_module->dependencies[i].type), i, 1);
            m_ui->dependencies->addWidget(new QLabel(dependencies[i]), i, 2);
            m_ui->dependencies->addWidget(new QLabel(m_module->dependencies[i].info), i, 3);
        }
    }
    else
        m_ui->g_dependencies->setVisible(false);
}

InfoWidget::~InfoWidget()
{
    delete m_ui;
}
