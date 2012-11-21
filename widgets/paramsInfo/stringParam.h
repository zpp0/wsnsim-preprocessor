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
    ModuleParamString(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw, ModuleParam* param);
    virtual ~ModuleParamString();

    void setParamValue(QVariant value);

protected:
    Ui::StringParam *m_ui;

private slots:
    void setParamValue(QString value);
};

#endif // STRINGPARAM_H
