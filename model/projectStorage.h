/**
 *
 * File: projectStorage.h
 * Description: projects storage
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#ifndef PROJECTSSTORAGE_H
#define PROJECTSSTORAGE_H

#include <QString>
#include <QList>

#include "projectParams.h"
#include "moduleParams.h"

class ProjectStorage : public QObject
{
    Q_OBJECT
public:
    static ProjectStorage& instance() {
        static ProjectStorage instance;
        return instance;
    }

public slots:
    void saveXML(QString file);

    void setUuid(QString uuid);

    void setAuthor(QString author);
    void setComment(QString comment);
    void setKeywords(QStringList keyword);
    void setTitle(QString title);

    void setMaxTime(int time);
    void setTimeUnits(TimeUnits units);
    void setFileName(QString value);

    void setNodes(ModuleDescriptionRaw* module, QString nodeType, int numOfNodes);
    // void removeNodes(QString nodeType, int numOfNodes);

    void setNodeType(QString name, QList<ModuleDescriptionRaw*> modules);

public:
    quint16 getModuleID(ModuleDescriptionRaw* module);
    ModuleDescriptionRaw* getModule(quint16 moduleID);

    ModuleData* addModule(ModuleDescriptionRaw* module);
    ModuleParam* addModuleParam(ModuleData* module);
    ModuleDependence* addModuleDependence(ModuleData* module);

    void removeModule(ModuleData* module);

public slots:
    void addModule(ModuleData module);
    void addNodeType(NodeTypeData nodeType);
    // void setNodesNum(quint16 moduleID, QString nodeType, quint16 nodesNumber);

signals:
    void setNodesNum(int num);

    void newNodeType(QString name);
    void deleteNodeType(QString name);

    void newModule(ModuleData* module);
    void newModuleParam(ModuleData* module, ModuleParam* param);
    void newModuleDependence(ModuleData* module, ModuleDependence* dependence);

    void savingFileError(QString errorString);

private:
    ProjectStorage() : m_newModuleID(0) {}
    ProjectStorage(ProjectStorage const&);
    void operator=(ProjectStorage const&);

    void nodesNumber();

    ProjectParams m_project;
    quint16 m_newModuleID;

    QMap<quint16, QList<EventParams> > m_events;
    QMap<ModuleDescriptionRaw*, quint16> m_modulesID;

    QUuid m_uuid;
};

#endif // PROJECTSSTORAGE_H
