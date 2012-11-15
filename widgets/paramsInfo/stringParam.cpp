/**
 *
 * File: stringParam.cpp
 * Description: module param with string type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "stringParam.h"
#include "ui_stringParam.h"

ModuleParamString::ModuleParamString(ModuleParamRaw* paramRaw, ModuleParam* param)
    :m_ui(new Ui::StringParam), ModuleParamGeneral(paramRaw, param)
{
    m_ui->setupUi(this);

    m_ui->l_info->setText(paramRaw->info);
    if (paramRaw->units == "")
        m_ui->l_units->setVisible(false);
    else
        m_ui->l_units->setText(paramRaw->units);

    connect(m_ui->lineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(setParamValue(QString)));
}

ModuleParamString::~ModuleParamString()
{
    delete m_ui;
}

void ModuleParamString::setParamValue(QString value)
{
    m_param->value = value;
}
