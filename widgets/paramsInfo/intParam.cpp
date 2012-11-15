/**
 *
 * File: intParam.cpp
 * Description: module param with int type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "intParam.h"
#include "ui_intParam.h"

ModuleParamInt::ModuleParamInt(ModuleParamRaw* paramRaw, ModuleParam* param)
    :m_ui(new Ui::IntParam), ModuleParamGeneral(paramRaw, param)
{
    m_ui->setupUi(this);

    m_ui->l_info->setText(paramRaw->info);
    m_ui->l_units->setText(paramRaw->units);

    connect(m_ui->spinBox, SIGNAL(valueChanged(int)),
            this, SLOT(setParamValue(int)));
}

ModuleParamInt::~ModuleParamInt()
{
    delete m_ui;
}

void ModuleParamInt::setParamValue(int value)
{
    m_param->value = value;
}
