/**
 *
 * File: uintParam.h
 * Description: module param with uint type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef UINTPARAM_H
#define UINTPARAM_H

#include "intParam.h"

class ModuleParamUint : protected ModuleParamInt
{
    Q_OBJECT

public:
    ModuleParamUint(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw, ModuleParam* param);
    virtual ~ModuleParamUint() {}
};

#endif // UINTPARAM_H
