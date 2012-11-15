/**
 *
 * File: moduleScanner.cpp
 * Description: API for scan modules in file and directory
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#include <QDir>
#include <QString>
#include <QStringList>
#include <QLibrary>
#include <QDebug>

#include "moduleScanner.h"

ModuleScanner::ModuleScanner(QObject* parent)
    : m_parent(parent)
{
    m_moduleFileExtensions << "*.xml";
}

void ModuleScanner::scanFile(QString& file)
{
    QLibrary moduleDataLib("./moduleData");
    moduleDataLib.load();

    if(!moduleDataLib.isLoaded()) {
        emit moduleScanError(file, moduleDataLib.errorString());
        return;
    }

    typedef ModuleDescriptionRaw(*moduleDataLoad) (QString& FileName, QString* errorMessage);
    moduleDataLoad load = (moduleDataLoad) moduleDataLib.resolve("load");

    QString errorMessage;

    ModuleDescriptionRaw moduleDescription = load(file, &errorMessage);
    if (errorMessage == "")
        // FIXME: don't send big structure with the signal
        emit moduleScanSuccess(file, moduleDescription);
    else
        emit moduleScanError(file, errorMessage);

    return;
}

void ModuleScanner::scanDir(QString& dir)
{
    qDebug() << dir;
    QDir modulesDir(dir);

    QStringList modulesFiles = modulesDir.entryList(m_moduleFileExtensions);
    foreach (QString moduleFile, modulesFiles) {
        qDebug() << "scan" << moduleFile;
        QString modulePath = dir + moduleFile;
        scanFile(modulePath);
    }
}