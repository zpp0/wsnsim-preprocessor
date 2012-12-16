/**
 *
 * File: nodesStorage.h
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#ifndef NODESSTORAGE_H
#define NODESSTORAGE_H

#include <QtCore>

#include "projectParams.h"
#include "modulesParams.h"

class NodesStorage : public QObject
{
    Q_OBJECT
public:
    static NodesStorage& instance() {
        static NodesStorage instance;
        return instance;
    }

    void addNodeType(QString name);
    void removeNodeType(QString name);
    void renameNodeType(QString newName, QString oldName);

    void setNodes(ModuleDescriptionRaw* module, QString nodeType, int number);
    void removeNodes(ModuleDescriptionRaw* module, QString nodeType);

    QList<NodesData> getNodes();
    void setNodes(QList<NodesData> nodes);

    QList<QString> getNodeTypes();

    void clean();

signals:
    void nodeTypeAdded(QString name);
    void nodeTypeRemoved(QString name);
    void nodeTypeRenamed(QString newName, QString oldName);

    void nodesTotalChanged(int number);

    void nodesNumberChanged(ModuleDescriptionRaw* module, QString nodeType, int number);
    void nodesRemoved(ModuleDescriptionRaw* module, QString nodeType);

private:
    NodesStorage() {}
    NodesStorage(NodesStorage const&);
    void operator=(NodesStorage const&);

    void nodesTotal();

    QList<QString> m_nodeTypes;

    QMap<ModuleDescriptionRaw*, QMap<QString, int> > m_nodes;
    int m_nodesTotal;
};

#endif // NODESSTORAGE_H
