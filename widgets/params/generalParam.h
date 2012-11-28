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
    ModuleParamGeneral(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw, ModuleParam* param);

    virtual ~ModuleParamGeneral() {}

    virtual void setParamValue(QVariant value) = 0;

protected:
    ModuleParamRaw* m_paramRaw;
    ModuleParam* m_param;
    ModuleDescriptionRaw* m_module;
};

#endif // GENERALPARAM_H
