/**
 *
 * File: stringParam.h
 * Description: module param with string type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef STRINGPARAM_H
#define STRINGPARAM_H

#include "generalParam.h"

namespace Ui {
    class StringParam;
}

class ModuleParamString : protected ModuleParamGeneral
{
    Q_OBJECT

public:
    ModuleParamString(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw);
    virtual ~ModuleParamString();

    void setParam(ModuleParam param);
    ModuleParam getParam();

protected:
    Ui::StringParam *m_ui;
};

#endif // STRINGPARAM_H
