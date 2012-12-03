/**
 *
 * File: intParam.cpp
 * Description: module param with int type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "intParam.h"
#include "ui_intParam.h"

ModuleParamInt::ModuleParamInt(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw)
    :ModuleParamGeneral(module, paramRaw), m_ui(new Ui::IntParam)
{
    m_ui->setupUi(this);

    m_ui->l_info->setText(m_param->info);

    if (m_param->units == "")
        m_ui->l_units->setVisible(false);
    else
        m_ui->l_units->setText(m_param->units);

    if (m_param->defaultValue.isValid())
        m_ui->spinBox->setValue(m_param->defaultValue.toInt());
}

void ModuleParamInt::setParam(ModuleParam param)
{
    m_ui->spinBox->setValue(param.value.toInt());
}

ModuleParam ModuleParamInt::getParam()
{
    ModuleParam param;
    param.name = m_param->name;
    param.type = m_param->type;
    param.value = m_ui->spinBox->value();

    return param;
}

ModuleParamInt::~ModuleParamInt()
{
    delete m_ui;
}
