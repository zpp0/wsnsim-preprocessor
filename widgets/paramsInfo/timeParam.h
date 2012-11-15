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
    ModuleParamTime(ModuleParamRaw* paramRaw, ModuleParam* param);
    virtual ~ModuleParamTime();

private slots:
    void setTimeValue(int time);
    void timeUnitsActivated(int units);

protected:
    Ui::TimeParam *m_ui;
};

#endif // TIMEPARAM_H
