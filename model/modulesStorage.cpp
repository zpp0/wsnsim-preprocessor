/**
 *
 * File: moduleStorage.cpp
 * Description: modules storage
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#include <QSettings>

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

void ModulesStorage::addBrokenProjectModule(quint16 moduleID)
{
    m_brokenModules += moduleID;
}

void ModulesStorage::setProjectModuleID(quint16 moduleID, QString file)
{
    m_projectModule[moduleID] = file;
}

quint16 ModulesStorage::getModuleFromProject(ModuleDescriptionRaw* module)
{
    foreach(QString moduleFile, m_projectModule.values())
        if (module->fileName == moduleFile)
            return m_projectModule.key(moduleFile);
}

ModuleDescriptionRaw* ModulesStorage::getModuleFromProject(quint16 moduleID)
{
    if (m_brokenModules.contains(moduleID))
        return NULL;
    else
        return getModule(m_projectModule[moduleID]);
}

ModuleDescriptionRaw* ModulesStorage::getModule(quint16 moduleID)
{
    if (m_enabled.size() > moduleID)
        return m_enabled[moduleID];
    else
        return NULL;
}

quint16 ModulesStorage::getModule(ModuleDescriptionRaw* module)
{
    return m_enabled.indexOf(module);
}

QList<ModuleDescriptionRaw*> ModulesStorage::getEnabled()
{
    return m_enabled;
}

QString ModulesStorage::getModuleFilePath(QString fileName)
{
    QString modulesDir = QSettings("wsnsim", "simulator").value("Modules/Directory").toString();
    return modulesDir + "/" + fileName;
}

void ModulesStorage::clean()
{
    m_enabled.clear();
    m_modules.clear();
    m_projectModule.clear();
    m_brokenModules.clear();
}
