/**
 *
 * File: nodesStorage.cpp
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#include "nodesStorage.h"
#include "modulesStorage.h"

void NodesStorage::addNodeType(QString name)
{
    m_nodeTypes += name;
    emit nodeTypeAdded(name);
}

void NodesStorage::removeNodeType(QString name)
{
    m_nodeTypes.removeOne(name);
    emit nodeTypeRemoved(name);
}

void NodesStorage::renameNodeType(QString newName, QString oldName)
{
    int index = m_nodeTypes.indexOf(oldName);
    m_nodeTypes[index] = newName;
    emit nodeTypeRenamed(newName, oldName);
}

void NodesStorage::setNodes(ModuleDescriptionRaw* module, QString nodeType, int number)
{
    m_nodes[module][nodeType] = number;
    emit nodesNumberChanged(module, nodeType, number);

    nodesTotal();
}

void NodesStorage::removeNodes(ModuleDescriptionRaw* module, QString nodeType)
{
    m_nodes[module].remove(nodeType);
    emit nodesRemoved(module, nodeType);

    nodesTotal();
}

void NodesStorage::nodesTotal()
{
    m_nodesTotal = 0;
    foreach(ModuleDescriptionRaw* module, m_nodes.keys())
        foreach(QString nodeType, m_nodes[module].keys())
            m_nodesTotal += m_nodes[module][nodeType];

    emit nodesTotalChanged(m_nodesTotal);
}

QList<NodesData> NodesStorage::getNodes()
{
    QList<NodesData> nodes;

    foreach(ModuleDescriptionRaw* module, m_nodes.keys()) {
        foreach(QString nodeType, m_nodes[module].keys()) {
            NodesData nodeData;
            nodeData.moduleID = ModulesStorage::instance().getModule(module);
            nodeData.nodeType = nodeType;
            nodeData.nodesNumber = m_nodes[module][nodeType];

            nodes += nodeData;
        }
    }

    return nodes;
}

void NodesStorage::setNodes(QList<NodesData> nodes)
{
    foreach(NodesData nodeData, nodes) {
        ModuleDescriptionRaw* module = ModulesStorage::instance().getModule(nodeData.moduleID);
        setNodes(module, nodeData.nodeType, nodeData.nodesNumber);
    }
}

QList<QString> NodesStorage::getNodeTypes()
{
    return m_nodeTypes;
}
