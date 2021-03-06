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
#include <QSettings>

#include "moduleScanner.h"
#include "modulesData.h"

#include "moduleValidator.h"

ModuleScanner::ModuleScanner(QObject* parent)
    : m_parent(parent)
{
    m_moduleFileExtensions << "*.lua";
}

void ModuleScanner::scanFile(QString& file)
{
    QString errorMessage;

    ModulesData data;
    ModuleDescriptionRaw moduleDescription = data.load(file, &errorMessage);

    ModuleValidator validator;

    if (!(errorMessage == "")) {
        emit moduleScanError(file, errorMessage);
        return;
    }
    else if (!validator.isValidModule(moduleDescription)) {
        emit moduleScanError(file, validator.errorString());
        return;
    }

    QSettings settings("wsnsim", "simulator");

    QString modulesDirectory = settings.value("Modules/Directory").toString();
    QDir modulesDir(modulesDirectory);

    QString moduleFile = modulesDir.relativeFilePath(moduleDescription.fileName);
    moduleDescription.fileName = moduleFile;

    emit moduleScanSuccess(file, moduleDescription);

    return;
}

void ModuleScanner::scanModulesDir(QString& dir)
{
    QDir modulesDir(dir);

    QStringList modulesFiles = modulesDir.entryList(m_moduleFileExtensions);
    foreach (QString moduleFile, modulesFiles) {
        QString modulePath = dir + "/" + moduleFile;
        scanFile(modulePath);
    }
}
