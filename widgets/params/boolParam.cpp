/**
 *
 * File: boolParam.cpp
 * Description: module param with bool type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "boolParam.h"
#include "ui_boolParam.h"

ModuleParamBool::ModuleParamBool(ModuleDescriptionRaw* module, ModuleParamRaw* param)
    :ModuleParamGeneral(module, param), m_ui(new Ui::BoolParam)
{
    m_ui->setupUi(this);

    m_ui->checkBox->setText(param->info);

    if (m_param->defaultValue.isValid())
        m_ui->checkBox->setCheckState(m_param->defaultValue.toBool() == true
                                      ? Qt::Checked
                                      : Qt::Unchecked);
}

void ModuleParamBool::setParam(ModuleParam param)
{
    bool value = param.value.toBool();
    if (value == true)
        m_ui->checkBox->setCheckState(Qt::Checked);
    else
        m_ui->checkBox->setCheckState(Qt::Unchecked);
}

ModuleParam ModuleParamBool::getParam()
{
    ModuleParam param;
    param.name = m_param->name;
    param.type = m_param->type;
    param.value = m_ui->checkBox->checkState() == Qt::Checked ? true : false;

    return param;
}

ModuleParamBool::~ModuleParamBool()
{
    delete m_ui;
}
