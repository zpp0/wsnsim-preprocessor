/**
 *
 * File: checkModule.cpp
 * Description: QCheckBox Widget with link to ModuleDescriptionRaw
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#include "checkModule.h"

#include <QDebug>

CheckModule::CheckModule(ModuleDescriptionRaw* module)
    :QCheckBox(), m_module(module)
{
    connect(this, SIGNAL(clicked(bool)),
            this, SLOT(enabled(bool)));
}

void CheckModule::enabled(bool enable)
{
    if (enable == true)
        emit moduleEnabled(m_module);
    else
        emit moduleDisabled(m_module);
}
