/**
 *
 * File: moduleInfoFormatter.h
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef MODULEINFOFORMATTER_H
#define MODULEINFOFORMATTER_H

#include <QString>
#include <QStringList>
#include <QObject>

#include "modulesParams.h"

class ModuleInfoFormatter : public QObject
{
    Q_OBJECT
public:
    ModuleInfoFormatter(ModuleDescriptionRaw* module);

    QStringList getFunctions();
    QStringList getEvents();
    QStringList getDependencies();

private:
    QString getFunction(const ModuleFunctionRaw& function);
    QString getEvent(const ModuleEventRaw& event);

    ModuleDescriptionRaw* m_module;
};

#endif // MODULEINFOFORMATTER_H
