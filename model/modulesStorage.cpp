/**
 *
 * File: moduleStorage.cpp
 * Description: modules storage
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#include "modulesStorage.h"

void ModulesStorage::moduleScanSuccess(QString file, ModuleDescriptionRaw module)
{
    m_modules += module;
    emit registerModule(&m_modules.last());
}
