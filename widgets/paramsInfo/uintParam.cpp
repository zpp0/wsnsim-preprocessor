/**
 *
 * File: uintParam.cpp
 * Description: module param with uint type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "uintParam.h"
#include "ui_intParam.h"

ModuleParamUint::ModuleParamUint(ModuleParamRaw* paramRaw, ModuleParam* param)
    :ModuleParamInt(paramRaw, param)
{
    m_ui->spinBox->setMinimum(0);
}
