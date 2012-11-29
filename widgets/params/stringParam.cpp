/**
 *
 * File: stringParam.cpp
 * Description: module param with string type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "stringParam.h"
#include "ui_stringParam.h"

ModuleParamString::ModuleParamString(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw)
    :ModuleParamGeneral(module, paramRaw), m_ui(new Ui::StringParam)
{
    m_ui->setupUi(this);

    m_ui->l_info->setText(m_param->info);
    if (m_param->units == "")
        m_ui->l_units->setVisible(false);
    else
        m_ui->l_units->setText(paramRaw->units);
}

void ModuleParamString::setParam(ModuleParam param)
{
    m_ui->lineEdit->setText(param.value.toString());
}

ModuleParam ModuleParamString::getParam()
{
    ModuleParam param;
    param.name = m_param->name;
    param.type = m_param->type;
    param.value = m_ui->lineEdit->text();

    return param;
}

ModuleParamString::~ModuleParamString()
{
    delete m_ui;
}
