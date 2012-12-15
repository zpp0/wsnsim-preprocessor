/**
 *
 * File: moduleValidator.cpp
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "moduleValidator.h"

bool ModuleValidator::isValidModule(const ModuleDescriptionRaw& module)
{
        // general
    if (module.name == "") {
        m_errorString = tr("module has no name");
        return false;
    }
    if (module.type != "environment"
        && module.type != "hardware"
        && module.type != "software") {

        m_errorString = tr("wrong type module") + " " + module.type;
        return false;
    }

    // params
    foreach(ModuleParamRaw param, module.params) {
        if (param.name == "") {
            // FIXME: what user supposed to do with it?
            m_errorString = tr("param has no name");
            return false;
        }
        if (param.type != "double"
            && param.type != "int"
            && param.type != "uint"
            && param.type != "string"
            && param.type != "file"
            && param.type != "nodes"
            && param.type != "bool"
            && param.type != "table") {

            m_errorString = (tr("param") + " " + param.name
                             + ": " + tr("wrong type param") + " " + param.type);

            return false;
        }
    }

    // events
    foreach(ModuleEventRaw event, module.interface.events) {
        if (event.name == "") {
            // FIXME: what user supposed to do with it?
            m_errorString = tr("event has no name");
            return false;
        }

        foreach(const ModuleEventParamRaw& param, event.params) {
            if (param.name == "") {
                // FIXME: what user supposed to do with it?
                m_errorString = tr("param of event") + " " + event.name + " " + tr("has no name");
                return false;
            }

            if (param.type != "int32"
                && param.type != "uint8"
                && param.type != "uint16"
                && param.type != "uint32"
                && param.type != "uint64"
                && param.type != "double"
                && param.type != "string"
                && param.type != "ByteArray"
                && param.type != "bool") {

                m_errorString = (tr("param") + " " + param.name
                                 + " " + tr("of event") + " " + event.name
                                 + ": " + tr("wrong type") + " " + param.type);

                return false;
            }
        }
    }


    // functions
    foreach(ModuleFunctionRaw function, module.interface.functions) {
        if (function.name == "") {
            // FIXME: what user supposed to do with it?
            m_errorString = tr("function has no name");
            return false;
        }
        // TODO: check args
        // TODO: check duplicates in names
    }


    // dependencies
    foreach(ModuleDependRaw dependence, module.dependencies) {
        if (dependence.name == "") {
            // FIXME: what user supposed to do with it?
            m_errorString = tr("dependence has no name");
            return false;
        }
        if (dependence.type != "environment"
            && dependence.type != "hardware"
            && dependence.type != "software") {

            m_errorString = tr("wrong type dependence") + " " + dependence.type;
            return false;
        }
    }

    return true;
}

QString ModuleValidator::errorString()
{
    return m_errorString;
}
