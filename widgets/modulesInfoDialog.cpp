/**
 *
 * File: modulesInfoDialog.cpp
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "modulesInfoDialog.h"
#include "ui_modulesInfoDialog.h"

#include "infoWidget.h"

ModulesInfoDialog::ModulesInfoDialog(QWidget* parent)
    : QDialog(parent), m_ui(new Ui::ModulesInfoDialog)
{
    m_ui->setupUi(this);
}

void ModulesInfoDialog::addModule(ModuleDescriptionRaw* module)
{
    m_ui->modules->addWidget(new InfoWidget(module));
}

ModulesInfoDialog::~ModulesInfoDialog()
{
    delete m_ui;
}
