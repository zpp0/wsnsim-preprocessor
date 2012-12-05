/**
 *
 * File: project.cpp
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#include <QLibrary>

#include "projectStorage.h"

ProjectStorage::ProjectStorage()
{
}

ProjectParams& ProjectStorage::getProject()
{
    return m_project;
}

void ProjectStorage::saveXML(QString file)
{
    m_project.version = "0.6.0";

    if (m_project.uuid.isNull())
        m_project.uuid = QUuid::createUuid().toString();

    m_project.projectInfo.revision++;
    m_project.projectInfo.modified = QDateTime::currentDateTime().toString();

    for (int i = 0; i < m_project.events.systemEvents.size(); i++)
        m_project.events.systemEvents[i].eventInfo["ID"] = QString::number(i);

    LogFileInfo info;
    info["ID"] = QString::number(0);
    info["name"] = m_project.simulatorParams.logFile;
    m_project.logFiles += info;

    QString errorMessage = "";

    ProjectData data;
    data.save(file, &errorMessage, m_project);

    if (errorMessage != "")
        emit savingProjectError(errorMessage);
}

ProjectParams& ProjectStorage::loadXML(QString file)
{
    QString errorMessage = "";

    ProjectData data;
    m_project = data.load(file, &errorMessage);

    if (errorMessage != "")
        emit loadingProjectError(errorMessage);

    return getProject();
}
