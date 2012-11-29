/**
 *
 * File: generalParam.cpp
 * Description: module param with general type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "generalParam.h"

ModuleParamGeneral::ModuleParamGeneral(ModuleDescriptionRaw* module, ModuleParamRaw* param)
{
    m_module = module;
    m_param = param;
}
