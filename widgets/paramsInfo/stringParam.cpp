/**
 *
 * File: stringParam.cpp
 * Description: module param with string type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "stringParam.h"
#include "ui_stringParam.h"

ModuleParamString::ModuleParamString(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw, ModuleParam* param)
    :m_ui(new Ui::StringParam), ModuleParamGeneral(module, paramRaw, param)
{
    m_ui->setupUi(this);

    m_ui->l_info->setText(paramRaw->info);
    if (paramRaw->units == "")
        m_ui->l_units->setVisible(false);
    else
        m_ui->l_units->setText(paramRaw->units);

    if (!m_param->value.isNull())
        setParamValue(m_param->value);

    connect(m_ui->lineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(setParamValue(QString)));
}

ModuleParamString::~ModuleParamString()
{
    delete m_ui;
}

void ModuleParamString::setParamValue(QVariant value)
{
    m_ui->lineEdit->setText(value.toString());
}

void ModuleParamString::setParamValue(QString value)
{
    m_param->value = value;
}
