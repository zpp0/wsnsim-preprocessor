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

void ModulesStorage::enableModule(ModuleDescriptionRaw* module, bool enable)
{
    if (enable)
        m_enabled += module;
    else
        m_enabled.removeOne(module);

    emit moduleEnabled(module, enable);
}

ModuleDescriptionRaw* ModulesStorage::getModule(QString fileName)
{
    ModuleDescriptionRaw* module = NULL;
    for (int i = 0; i < m_modules.size(); i++) {
        if (m_modules[i].fileName == fileName) {
            module = &(m_modules[i]);
            break;
        }
    }

    return module;
}

ModuleDescriptionRaw* ModulesStorage::getModule(quint16 moduleID)
{
    return m_enabled[moduleID];
}

quint16 ModulesStorage::getModule(ModuleDescriptionRaw* module)
{
    return m_enabled.indexOf(module);
}

QList<ModuleDescriptionRaw*> ModulesStorage::getEnabled()
{
    return m_enabled;
}
