/**
 *
 * File: moduleScanner.h
 * Description: API for scan modules in file and directory
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#ifndef MODULESCANNER_H
#define MODULESCANNER_H

#include <QString>
#include <QStringList>
#include <QObject>

#include "modulesParams.h"

class ModuleScanner : public QObject
{
    Q_OBJECT

public:
    ModuleScanner(QObject* parent = 0);

    void scanModulesDir(QString& dir);
    void scanFile(QString& filePath);

signals:
    void moduleScanSuccess(QString file, ModuleDescriptionRaw module);
    void moduleScanError(QString file, QString error);

private:
    bool isValueModule(ModuleDescriptionRaw module);

    QStringList m_moduleFileExtensions;

    QObject* m_parent;
};

#endif // MODULESCANNER_H
