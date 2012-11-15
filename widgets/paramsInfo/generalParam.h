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

#include "moduleParams.h"
#include "projectParams.h"

class ModuleParamGeneral : public QFrame
{
    Q_OBJECT

public:
    ModuleParamGeneral(ModuleParamRaw* paramRaw, ModuleParam* param)
        :m_paramRaw(paramRaw), m_param(param) {}
    virtual ~ModuleParamGeneral() {}

protected:
    ModuleParamRaw* m_paramRaw;
    ModuleParam* m_param;
};

#endif // GENERALPARAM_H