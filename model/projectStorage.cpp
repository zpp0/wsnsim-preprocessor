/**
 *
 * File: projectStorage.cpp
 * Description: projects storage
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#include <QLibrary>

#include "projectStorage.h"

void ProjectStorage::saveXML(ProjectParams project, QString file)
{
    project.version = "0.6.0";

    if (project.uuid.isNull())
        project.uuid = QUuid::createUuid().toString();

    project.projectInfo.revision++;
    project.projectInfo.modified = QDateTime::currentDateTime().toString();

    for (int i = 0; i < project.events.systemEvents.size(); i++)
        project.events.systemEvents[i].eventInfo["ID"] = QString::number(i);

    LogFileInfo info;
    info["ID"] = QString::number(0);
    info["name"] = project.simulatorParams.logFile;
    project.logFiles += info;

    QLibrary projectDataLib("./projectData");
    projectDataLib.load();

    if(!projectDataLib.isLoaded()) {
        emit savingFileError(projectDataLib.errorString());
        return;
    }

    // FIXME: make it easy
    typedef void(*projectDataSave) (QString& projectFileName, QString* errorMessage, ProjectParams params);
    projectDataSave pd = (projectDataSave) projectDataLib.resolve("save");

    QString errorMessage;

    pd(file, &errorMessage, project);
}
