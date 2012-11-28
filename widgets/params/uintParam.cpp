/**
 *
 * File: uintParam.cpp
 * Description: module param with uint type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "uintParam.h"
#include "ui_intParam.h"

ModuleParamUint::ModuleParamUint(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw, ModuleParam* param)
    :ModuleParamInt(module, paramRaw, param)
{
    m_ui->spinBox->setMinimum(0);
}
