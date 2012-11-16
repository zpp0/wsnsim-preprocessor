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
    :m_ui(new Ui::BoolParam), ModuleParamGeneral(module, paramRaw, param)
{
    m_ui->setupUi(this);

    m_ui->checkBox->setText(paramRaw->info);
}

ModuleParamBool::~ModuleParamBool()
{
    delete m_ui;
}
