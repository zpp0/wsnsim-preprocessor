/**
 *
 * File: boolParam.cpp
 * Description: module param with bool type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "boolParam.h"
#include "ui_boolParam.h"

ModuleParamBool::ModuleParamBool(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw, ModuleParam* param)
    :ModuleParamGeneral(module, paramRaw, param), m_ui(new Ui::BoolParam)
{
    m_ui->setupUi(this);

    m_ui->checkBox->setText(paramRaw->info);

    if (!m_param->value.isNull())
        setParamValue(m_param->value);
}

ModuleParamBool::~ModuleParamBool()
{
    delete m_ui;
}

void ModuleParamBool::setParamValue(QVariant value)
{
    bool param = value.toBool();
    if (param == true)
        m_ui->checkBox->setCheckState(Qt::Checked);
    else
        m_ui->checkBox->setCheckState(Qt::Unchecked);
}
