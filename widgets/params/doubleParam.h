/**
 *
 * File: doubleParam.h
 * Description: module param with double type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef DOUBLEPARAM_H
#define DOUBLEPARAM_H

#include "generalParam.h"

namespace Ui {
    class DoubleParam;
}

class ModuleParamDouble : protected ModuleParamGeneral
{
    Q_OBJECT

public:
    ModuleParamDouble(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw);
    virtual ~ModuleParamDouble();

    void setParam(ModuleParam param);
    ModuleParam getParam();

protected:
    Ui::DoubleParam *m_ui;
};

#endif // DOUBLEPARAM_H
