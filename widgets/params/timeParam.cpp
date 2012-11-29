/**
 *
 * File: timeParam.cpp
 * Description: module param with time type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "timeParam.h"
#include "ui_timeParam.h"
#include "projectParams.h"

ModuleParamTime::ModuleParamTime(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw)
    :ModuleParamGeneral(module, paramRaw), m_ui(new Ui::TimeParam)
{
    m_ui->setupUi(this);

    m_ui->l_info->setText(m_param->info);
}

ModuleParamTime::~ModuleParamTime()
{
    delete m_ui;
}

void ModuleParamTime::setParam(ModuleParam param)
{
}

ModuleParam ModuleParamTime::getParam()
{
    return ModuleParam();
}
