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

#include "moduleParams.h"

class ModuleScanner : public QObject
{
    Q_OBJECT

public:
    ModuleScanner(QObject* parent = 0);

    void scanDir(QString& dir);

signals:
    void moduleScanSuccess(QString file, ModuleDescriptionRaw module);
    void moduleScanError(QString file, QString error);

private:
    void scanFile(QString& file);

    QStringList m_moduleFileExtensions;

    QObject* m_parent;
};

#endif // MODULESCANNER_H
