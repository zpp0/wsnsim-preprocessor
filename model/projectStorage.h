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

    void saveXML(QString file);

    void setAuthor(QString author);
    void setComment(QString comment);
    void setKeywords(QStringList keyword);
    void setTitle(QString title);

    void setMaxTime(int time);
    void setTimeUnits(TimeUnits units);
    void setFileName(QString value);

    void addNodes(QString nodeType, int numOfNodes);
    // void removeNodes(QString nodeType, int numOfNodes);

    ModuleData* addModule(ModuleDescriptionRaw* module);
    ModuleParam* addModuleParam(ModuleData* module);

signals:
    void setNodesNum(int num);
    void newModule(ModuleData* module);

private:
    ProjectStorage() : m_newModuleID(0) {}
    ProjectStorage(ProjectStorage const&);
    void operator=(ProjectStorage const&);

    ProjectParams m_project;
    // nodeType -> nodesNum
    QMap<QString, int> m_nodes;
    QMap<QString, quint16> m_modulesIDs;
    quint16 m_newModuleID;

    QMap<quint16, QList<EventParams> > m_events;

    QUuid m_uuid;
    // QList<ProjectDescriptionRaw> m_projects;
};

#endif // PROJECTSSTORAGE_H
