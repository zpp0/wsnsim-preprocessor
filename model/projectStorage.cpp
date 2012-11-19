/**
 *
 * File: projectStorage.cpp
 * Description: projects storage
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#include "projectStorage.h"

void ProjectStorage::setNodes(ModuleDescriptionRaw* module, QString nodeType, int numOfNodes)
{
    quint16 moduleID = getModuleID(module);

    if (numOfNodes > 0) {
        m_nodes[module][nodeType] = numOfNodes;
        m_project.simulatorParams.nodes[moduleID] = numOfNodes;
    }
    else {
        m_nodes[module].remove(nodeType);
        m_project.simulatorParams.nodes.remove(moduleID);
    }

    emit setNodesNum(numOfNodes);
}

quint16 ProjectStorage::getModuleID(ModuleDescriptionRaw* module)
{
    return m_modulesID[module];
}

ModuleData* ProjectStorage::addModule(ModuleDescriptionRaw* moduleRaw)
{
    ModuleData module;

    module.moduleInfo["name"] = moduleRaw->name;
    module.moduleInfo["ID"] = QString::number(m_newModuleID);
    module.fileName = moduleRaw->fileName;
    m_project.modules += module;

    m_modulesID[moduleRaw] = m_newModuleID;

    QList<EventParams> events;
    QList<ModuleEventRaw> eventsRaw = moduleRaw->interface.events;
    for (int i = 0; i < eventsRaw.size(); i++) {
        EventParams event;
        event.eventInfo["name"] = eventsRaw[i].name;
        event.eventInfo["ID"] = QString::number(i);
        event.eventInfo["moduleID"] = QString::number(m_newModuleID);

        QList<ModuleEventArgumentRaw> arguments = eventsRaw[i].arguments;
        for (int j = 0; j < arguments.size(); j++) {
            EventArgument arg;
            arg["ID"] = QString::number(arguments[j].ID);
            arg["type"] = arguments[j].type;
            arg["name"] = arguments[j].name;

            event.arguments += arg;
        }
        events += event;
    }

    m_events[m_newModuleID] = events;
    m_newModuleID++;

    return &(m_project.modules.last());
}

void ProjectStorage::removeModule(ModuleData* module)
{
    quint16 moduleID = module->moduleInfo["ID"].toInt();
    m_events.remove(moduleID);

    for (int i = 0; i < m_project.modules.size(); i++)
        if (module == &(m_project.modules[i]))
            m_project.modules.removeAt(i);
}

ModuleParam* ProjectStorage::addModuleParam(ModuleData* module)
{
    ModuleParam param;
    module->params += param;
    return &(module->params.last());
}

ModuleDependence* ProjectStorage::addModuleDependence(ModuleData* module)
{
    ModuleDependence dep;
    module->dependencies += dep;
    return &(module->dependencies.last());
}

void ProjectStorage::addModule(ModuleData module)
{
    m_project.modules += module;
    ModuleData* newModuleData = &(m_project.modules.last());
    emit newModule(newModuleData);

    for (int i = 0; i < newModuleData->params.size(); i++)
        emit newModuleParam(newModuleData, &(newModuleData->params[i]));

    for (int i = 0; i < newModuleData->dependencies.size(); i++)
        emit newModuleDependence(newModuleData, &(newModuleData->dependencies[i]));
}

void ProjectStorage::setMaxTime(int time)
{
    m_project.simulatorParams.maxTime = time;
}

void ProjectStorage::setTimeUnits(TimeUnits units)
{
    m_project.simulatorParams.timeUnits = units;
}

void ProjectStorage::setFileName(QString value)
{
    m_project.simulatorParams.logFile = value;
    LogFileInfo info;
    info["ID"] = QString::number(0);
    info["name"] = value;
    if (m_project.logFiles.isEmpty())
        m_project.logFiles += info;
    else
        m_project.logFiles[0] = info;
}

void ProjectStorage::setAuthor(QString author)
{
    m_project.projectInfo.projectAutor = author;
}

void ProjectStorage::setComment(QString comment)
{
    m_project.projectInfo.projectComment = comment;
}

void ProjectStorage::setKeywords(QStringList keyword)
{
    m_project.projectInfo.keywords = keyword;
}

void ProjectStorage::setTitle(QString title)
{
    m_project.projectInfo.projectTitle = title;
}

void ProjectStorage::saveXML(QString file)
{
    m_project.version = "0.6.0";

    if (m_uuid.isNull()) {
        m_uuid = QUuid::createUuid();
        m_project.uuid = m_uuid.toString();
    }

    m_project.projectInfo.modified = QDateTime::currentDateTime().toString();

    int numberDrift = 0;

    // append events to project params
    foreach(QList<EventParams> events, m_events) {
        foreach(EventParams event, events) {
            event.eventInfo["ID"] = QString::number(numberDrift + event.eventInfo["ID"].toInt());
            m_project.events.systemEvents += event;
        }
        numberDrift += events.size();
    }

    QLibrary projectDataLib("./projectData");
    projectDataLib.load();

    if(!projectDataLib.isLoaded()) {
        qDebug() << "Error load library";
    }

    // FIXME: make it easy
    typedef void(*projectDataSave) (QString& projectFileName, QString* errorMessage, ProjectParams params);
    projectDataSave pd = (projectDataSave) projectDataLib.resolve("save");

    QString errorMessage;

    pd(file, &errorMessage, m_project);
}
