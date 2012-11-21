/**
 *
 * File: intParam.cpp
 * Description: module param with int type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "intParam.h"
#include "ui_intParam.h"

ModuleParamInt::ModuleParamInt(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw, ModuleParam* param)
    :ModuleParamGeneral(module, paramRaw, param), m_ui(new Ui::IntParam)
{
    m_ui->setupUi(this);

    m_ui->l_info->setText(paramRaw->info);
    m_ui->l_units->setText(paramRaw->units);

    if (!m_param->value.isNull())
        setParamValue(m_param->value);

    connect(m_ui->spinBox, SIGNAL(valueChanged(int)),
            this, SLOT(setParamValue(int)));
}

ModuleParamInt::~ModuleParamInt()
{
    delete m_ui;
}

void ModuleParamInt::setParamValue(QVariant value)
{
    m_ui->spinBox->setValue(value.toInt());
}

void ModuleParamInt::setParamValue(int value)
{
    m_param->value = value;
}
