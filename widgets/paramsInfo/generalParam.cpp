/**
 *
 * File: generalParam.cpp
 * Description: module param with general type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "generalParam.h"
#include "ui_generalParam.h"
#include "projectParams.h"

ModuleParamGeneral::ModuleParamGeneral(ModuleParamRaw* paramRaw, ModuleParam* param)
    :m_ui(new Ui::GeneralParam), ModuleParamGeneral(paramRaw, param)
{
}
