/**
 *
 * File: timeParam.h
 * Description: module param with time type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef TIMEPARAM_H
#define TIMEPARAM_H

#include "generalParam.h"

namespace Ui {
    class TimeParam;
}

class ModuleParamTime : protected ModuleParamGeneral
{
    Q_OBJECT

public:
    ModuleParamTime(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw, ModuleParam* param);
    virtual ~ModuleParamTime();

    void setParamValue(QVariant value);

private slots:
    void setTimeValue(int time);
    void timeUnitsActivated(int units);

protected:
    Ui::TimeParam *m_ui;
};

#endif // TIMEPARAM_H
