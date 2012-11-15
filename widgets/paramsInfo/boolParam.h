/**
 *
 * File: boolParam.h
 * Description: module param with bool type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef BOOLPARAM_H
#define BOOLPARAM_H

#include "generalParam.h"

namespace Ui {
    class BoolParam;
}

class ModuleParamBool : protected ModuleParamGeneral
{
    Q_OBJECT

public:
    ModuleParamBool(ModuleParamRaw* paramRaw, ModuleParam* param);
    virtual ~ModuleParamBool();

protected:
    Ui::BoolParam *m_ui;
};

#endif // BOOLPARAM_H
