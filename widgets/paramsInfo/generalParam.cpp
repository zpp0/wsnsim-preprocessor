/**
 *
 * File: generalParam.cpp
 * Description: module param with general type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "generalParam.h"
#include "projectParams.h"

ModuleParamGeneral::ModuleParamGeneral(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw, ModuleParam* param)
{
    m_module = module;
    m_paramRaw = paramRaw;
    m_param = param;
}
