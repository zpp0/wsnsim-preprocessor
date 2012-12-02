/**
 *
 * File: moduleInfoFormatter.cpp
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "moduleInfoFormatter.h"

ModuleInfoFormatter::ModuleInfoFormatter(ModuleDescriptionRaw* module)
{
    m_module = module;
}

QStringList ModuleInfoFormatter::getFunctions()
{
    QStringList functions;

    foreach(const ModuleFunctionRaw& function, m_module->interface.functions)
        functions << getFunction(function);

    return functions;
}

QStringList ModuleInfoFormatter::getEvents()
{
    QStringList events;

    foreach(const ModuleEventRaw& event, m_module->interface.events)
        events << getEvent(event);

    return events;
}

QStringList ModuleInfoFormatter::getDependencies()
{
    QStringList dependencies;

    foreach(const ModuleDependRaw& dependence, m_module->dependencies) {
        QString sdependence = (tr("Name: ") + dependence.name + " "
                               + tr("Type: ") + dependence.type + "\n");

        if (dependence.interface.functions.size() > 0) {
            sdependence += ("  " + tr("functions:") + "\n");

            foreach(const ModuleFunctionRaw& function, dependence.interface.functions)
                sdependence += ("    " + getFunction(function) + "\n");
        }

        if (dependence.interface.events.size() > 0) {
            sdependence += ("  " + tr("events:") + "\n");

            foreach(const ModuleEventRaw& event, dependence.interface.events)
                sdependence += ("    " + getEvent(event) + "\n");
        }

        dependencies << sdependence;
    }

    return dependencies;
}

QString ModuleInfoFormatter::getFunction(const ModuleFunctionRaw& function)
{
    QString sfunction;

    sfunction += (function.resultType + " " + function.name
                  + "(");

    foreach(const ModuleFunctionArgumentRaw& arg, function.arguments)
        sfunction += (arg.type + " " + arg.name
                      + (&arg != &(function.arguments.last()) ? ", " : ""));

    sfunction += (") " + function.info);

    return sfunction;
}

QString ModuleInfoFormatter::getEvent(const ModuleEventRaw& event)
{
    QString sevent;

    sevent += (event.name
               + "(");

    foreach(const ModuleEventParamRaw& param, event.params)
        sevent += (param.type + " " + param.name + (param.info != "" ? " " + param.info : "")
                   + (&param != &(event.params.last()) ? ", " : ""));

    sevent += (") " + event.info);

    return sevent;
}
