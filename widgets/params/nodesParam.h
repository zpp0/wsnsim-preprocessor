/**
 *
 * File: nodesParam.h
 * Description: module param with nodes type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef NODESPARAM_H
#define NODESPARAM_H

#include "generalParam.h"

namespace Ui {
    class NodesParam;
}

class ModuleParamNodes : protected ModuleParamGeneral
{
    Q_OBJECT

public:
    ModuleParamNodes(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw);
    virtual ~ModuleParamNodes();

    void setParam(ModuleParam param);
    ModuleParam getParam();

public slots:
    void addNodeType(QString name);
    void removeNodeType(QString name);

private slots:
    void addNodeType();
    void addNodeType(QString name, int number);

    void setNodes(QString nodeType, int number);

    void customContextMenuRequested(const QPoint &p);

protected:
    Ui::NodesParam *m_ui;

private:
    void removeNodes(QString nodeType);

    int getNodes_fromTable(int row);

    void addDummyNodeType();
    void removeDummyNodeType();

    QString m_dummyNodeType;
    // nodeTypeName -> row
    QMap<QString, int> m_nodeTypesRows;
    QList<QString> m_nodeTypes;
};

#endif // NODESPARAM_H
