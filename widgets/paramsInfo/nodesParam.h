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
    ModuleParamNodes(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw, ModuleParam* param);
    virtual ~ModuleParamNodes();

    void setParamValue(QVariant value);

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

    void addDummyNodeType();
    void removeDummyNodeType();

    QString m_dummyNodeType;
    // nodeTypeName -> row
    QMap<QString, int> m_nodeTypesRows;
};

#endif // NODESPARAM_H
