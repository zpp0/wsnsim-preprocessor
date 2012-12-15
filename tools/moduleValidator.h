/**
 *
 * File: moduleValidator.h
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef MODULEVALIDATOR_H
#define MODULEVALIDATOR_H

#include <QString>
#include <QObject>

#include "modulesParams.h"

class ModuleValidator : public QObject
{
    Q_OBJECT

public:
    bool isValidModule(const ModuleDescriptionRaw& module);
    QString errorString();

private:
    QString m_errorString;
};

#endif // MODULEVALIDATOR_H
