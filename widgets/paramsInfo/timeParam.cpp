/**
 *
 * File: timeParam.cpp
 * Description: module param with time type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "timeParam.h"
#include "ui_timeParam.h"
#include "projectParams.h"

ModuleParamTime::ModuleParamTime(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw, ModuleParam* param)
    :m_ui(new Ui::TimeParam), ModuleParamGeneral(module, paramRaw, param)
{
    m_ui->setupUi(this);

    m_ui->l_info->setText(paramRaw->info);

    connect(m_ui->time, SIGNAL(setValue(int)),
            this, SLOT(setTimeValue(int)));
    connect(m_ui->cb_timeUnits, SIGNAL(activated(int)),
            this, SLOT(timeUnitsActivated(int)));
}

ModuleParamTime::~ModuleParamTime()
{
    delete m_ui;
}

void ModuleParamTime::setTimeValue(int time)
{
    QMap<QString, QVariant> value = m_param->value.toMap();
    value["time"] = time;
    m_param->value = value;
}

void ModuleParamTime::timeUnitsActivated(int units)
{
    QMap<QString, QVariant> value = m_param->value.toMap();
    value["timeUnits"] = units;
    m_param->value = value;
}
