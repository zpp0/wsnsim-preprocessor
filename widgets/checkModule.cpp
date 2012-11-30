/**
 *
 * File: checkModule.cpp
 * Description: QCheckBox Widget with link to ModuleDescriptionRaw
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#include "checkModule.h"

CheckModule::CheckModule(ModuleDescriptionRaw* module)
    :QCheckBox(), m_module(module)
{
    connect(this, SIGNAL(clicked(bool)),
            this, SLOT(enabled(bool)));
}

void CheckModule::enabled(bool enable)
{
    if (enable == true) {
        setCheckState(Qt::Checked);
        emit moduleEnabled(m_module);
    }
    else {
        setCheckState(Qt::Unchecked);
        emit moduleDisabled(m_module);
    }
}
