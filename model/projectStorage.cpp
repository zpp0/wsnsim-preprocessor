/**
 *
 * File: projectStorage.cpp
 * Description: projects storage
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#include "projectStorage.h"

#include "modulesStorage.h"

void ProjectStorage::setNodes(ModuleDescriptionRaw* module, QString nodeType, int numOfNodes)
{
    quint16 moduleID = getModuleID(module);

    if (numOfNodes > 0) {

        for (int i = 0; i < m_project.simulatorParams.nodes.size(); i++) {

            if ((m_project.simulatorParams.nodes[i].moduleID == moduleID)
                && (m_project.simulatorParams.nodes[i].nodeType == nodeType)) {

                m_project.simulatorParams.nodes[i].nodesNumber = numOfNodes;
                nodesNumber();

                return;
            }
        }

        NodesData nodes;
        nodes.moduleID = moduleID;
        nodes.nodeType = nodeType;
        nodes.nodesNumber = numOfNodes;

        m_project.simulatorParams.nodes += nodes;

    }
    else
        for (int i = 0; i < m_project.simulatorParams.nodes.size(); i++)
            if (m_project.simulatorParams.nodes[i].moduleID == moduleID)
                m_project.simulatorParams.nodes.removeAt(i);

    nodesNumber();
}

void ProjectStorage::nodesNumber()
{
    int nodesNumber = 0;
    foreach(const NodesData& nodes, m_project.simulatorParams.nodes)
        nodesNumber += nodes.nodesNumber;

    emit setNodesNum(nodesNumber);
}

void ProjectStorage::setNodeType(QString name, QList<ModuleDescriptionRaw*> modules)
{
    if (!modules.isEmpty()) {
        QList<quint16> hardware;
        QList<quint16> software;
        foreach(ModuleDescriptionRaw* module, modules) {
            quint16 moduleID = m_modulesID[module];
            if (module->type == "hardware")
                hardware += moduleID;
            else if (module->type == "software")
                software += moduleID;
        }

        for (int i = 0; i < m_project.nodeTypes.size(); i++) {
            if (m_project.nodeTypes[i].name == name) {
                m_project.nodeTypes[i].hardwareModules = hardware;
                m_project.nodeTypes[i].softwareModules = software;

                return;
            }
        }

        NodeTypeData nodeType;
        nodeType.name = name;
        nodeType.hardwareModules = hardware;
        nodeType.softwareModules = software;

        m_project.nodeTypes += nodeType;
        emit newNodeType(name);
    }
    // removing
    else {
        for (int i = 0; i < m_project.nodeTypes.size(); i++) {
            if (m_project.nodeTypes[i].name == name) {
                m_project.nodeTypes.removeAt(i);
                emit deleteNodeType(name);
            }
        }
    }
}

quint16 ProjectStorage::getModuleID(ModuleDescriptionRaw* module)
{
    return m_modulesID[module];
}

ModuleDescriptionRaw* ProjectStorage::getModule(quint16 moduleID)
{
    return m_modulesID.key(moduleID);
}

ModuleData* ProjectStorage::addModule(ModuleDescriptionRaw* moduleRaw)
{
    ModuleData module;
    module.moduleInfo["name"] = moduleRaw->name;
    module.moduleInfo["ID"] = QString::number(m_newModuleID);
    module.moduleInfo["UUID"] = moduleRaw->UUID;
    module.fileName = moduleRaw->fileName;

    return addModule(module, moduleRaw);
}

ModuleData* ProjectStorage::addModule(ModuleData module, ModuleDescriptionRaw* moduleRaw)
{
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

void ProjectStorage::addModule(ModuleData moduleData)
{
    ModulesStorage& storage = ModulesStorage::instance();
    ModuleDescriptionRaw* moduleRaw = storage.getDescription(moduleData.moduleInfo["UUID"]);;

    if (moduleRaw) {
        ModuleData* newModuleData = addModule(moduleData, moduleRaw);
        emit newModule(newModuleData);

        for (int i = 0; i < newModuleData->params.size(); i++)
            emit newModuleParam(newModuleData, &(newModuleData->params[i]));

        for (int i = 0; i < newModuleData->dependencies.size(); i++)
            emit newModuleDependence(newModuleData, &(newModuleData->dependencies[i]));
    }
}

void ProjectStorage::addNodeType(NodeTypeData nodeType)
{
    m_project.nodeTypes += nodeType;
    NodeTypeData* newType = &(m_project.nodeTypes.last());
    emit newNodeType(newType);
    emit newNodeType(newType->name);
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

void ProjectStorage::setUuid(QString uuid)
{
    m_uuid = QUuid(uuid);
    qDebug() << "uuid" << m_uuid << uuid;
}

void ProjectStorage::saveXML(QString file)
{
    m_project.version = "0.6.0";

    if (m_uuid.isNull())
        m_uuid = QUuid::createUuid();

    m_project.uuid = m_uuid.toString();

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
        emit savingFileError(projectDataLib.errorString());
        return;
    }

    // FIXME: make it easy
    typedef void(*projectDataSave) (QString& projectFileName, QString* errorMessage, ProjectParams params);
    projectDataSave pd = (projectDataSave) projectDataLib.resolve("save");

    QString errorMessage;

    pd(file, &errorMessage, m_project);

    m_project.events.systemEvents.clear();
}
