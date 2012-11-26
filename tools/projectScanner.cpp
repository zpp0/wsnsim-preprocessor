/**
 *
 * File: projectScanner.cpp
 * Description: API for scan projects files
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#include <QDir>
#include <QString>
#include <QStringList>
#include <QLibrary>

#include "projectScanner.h"

ProjectScanner::ProjectScanner(QObject* parent)
    : QObject(parent)
{
}

void ProjectScanner::scanFile(QString& file)
{
    QLibrary projectDataLib("./projectData");
    projectDataLib.load();

    if(!projectDataLib.isLoaded())
        return;

    // FIXME: make it easy
    typedef ProjectParams(*projectDataLoad) (QString& projectFileName, QString* errorMessage);
    projectDataLoad pd = (projectDataLoad) projectDataLib.resolve("load");

    QString errorMessage;

    m_project = pd(file, &errorMessage);

    emit setVersion(m_project.version);
    emit setUuid(m_project.uuid);

    emit setLogFileName(m_project.simulatorParams.logFile);
    emit setMaxTime(m_project.simulatorParams.maxTime);
    emit setTimeUnits(m_project.simulatorParams.timeUnits);

    emit setAuthor(m_project.projectInfo.projectAutor);
    emit setComment(m_project.projectInfo.projectComment);
    emit setKeywords(m_project.projectInfo.keywords.join(" "));
    emit setTitle(m_project.projectInfo.projectTitle);

    foreach(ModuleData module, m_project.modules)
        emit addModule(module);

    foreach(NodeTypeData nodeType, m_project.nodeTypes)
        emit addNodeType(nodeType);

}
