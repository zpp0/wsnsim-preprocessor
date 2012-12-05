/**
 *
 * File: moduleData.h
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#ifndef MODULEDATA_H
#define MODULEDATA_H

#include <QtCore>

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include "modulesParams.h"

class ModulesData : public QObject
{
    Q_OBJECT
public:

    ModulesData();

    ModuleDescriptionRaw load(QString& fileName, QString* errorMessage);

private:
    void open();
    void close();
    int loadFile(QString path);

    static int declareModule(lua_State* lua);

    static QString getField(lua_State* lua, QString name);

    static QList<ModuleParamRaw> getParams(lua_State* lua);
    static ModuleInterfaceRaw getInterface(lua_State* lua);
    static QList<ModuleDependRaw> getDependencies(lua_State* lua);

    static ModuleDescriptionRaw* m_module;

    QString* m_errorString;

    lua_State *m_lua;
};

#endif // MODULEDATA_H
