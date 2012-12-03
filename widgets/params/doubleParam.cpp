/**
 *
 * File: doubleParam.cpp
 * Description: module param with double type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "doubleParam.h"
#include "ui_doubleParam.h"

ModuleParamDouble::ModuleParamDouble(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw)
    :ModuleParamGeneral(module, paramRaw), m_ui(new Ui::DoubleParam)
{
    m_ui->setupUi(this);

    m_ui->l_info->setText(m_param->info);

    if (m_param->units == "")
        m_ui->l_units->setVisible(false);
    else
        m_ui->l_units->setText(m_param->units);

    if (m_param->defaultValue.isValid())
        m_ui->doubleSpinBox->setValue(m_param->defaultValue.toDouble());
}

void ModuleParamDouble::setParam(ModuleParam param)
{
    double value = param.value.toDouble();
    m_ui->doubleSpinBox->setValue(value);
}

ModuleParam ModuleParamDouble::getParam()
{
    ModuleParam param;
    param.name = m_param->name;
    param.type = m_param->type;
    param.value = m_ui->doubleSpinBox->value();

    return param;
}

ModuleParamDouble::~ModuleParamDouble()
{
    delete m_ui;
}
