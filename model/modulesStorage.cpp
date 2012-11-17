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

ModuleDescriptionRaw* ModulesStorage::getDescription(QString Uuid)
{
    for (int i = 0; i < m_modules.size(); i++)
        if (m_modules[i].UUID == Uuid)
            return &(m_modules[i]);
}
