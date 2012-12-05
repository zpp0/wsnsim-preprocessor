/**
 *
 * File: generalParam.h
 * Description: module param interface
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef GENERALPARAM_H
#define GENERALPARAM_H

#include <QtGui>

#include "projectParams.h"
#include "modulesParams.h"

class ModuleParamGeneral : public QFrame
{
    Q_OBJECT

public:
    ModuleParamGeneral(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw);

    virtual ~ModuleParamGeneral() {}

    virtual void setParam(ModuleParam param) = 0;
    virtual ModuleParam getParam() = 0;

protected:
    ModuleParamRaw* m_param;
    ModuleDescriptionRaw* m_module;
};

#endif // GENERALPARAM_H
