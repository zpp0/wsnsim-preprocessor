/**
 *
 * File: doubleParam.cpp
 * Description: module param with double type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "doubleParam.h"
#include "ui_doubleParam.h"

ModuleParamDouble::ModuleParamDouble(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw, ModuleParam* param)
    :ModuleParamGeneral(module, paramRaw, param), m_ui(new Ui::DoubleParam)
{
    m_ui->setupUi(this);

    m_ui->l_info->setText(m_paramRaw->info);
    m_ui->l_units->setText(m_paramRaw->units);

    if (!m_param->value.isNull())
        setParamValue(m_param->value);

    connect(m_ui->doubleSpinBox, SIGNAL(valueChanged(double)),
            this, SLOT(setParamValue(double)));
}

ModuleParamDouble::~ModuleParamDouble()
{
    delete m_ui;
}

void ModuleParamDouble::setParamValue(QVariant value)
{
    double param = value.toDouble();
    m_ui->doubleSpinBox->setValue(param);
}

void ModuleParamDouble::setParamValue(double value)
{
    m_param->value = value;
    qDebug() << m_param->value;
}
