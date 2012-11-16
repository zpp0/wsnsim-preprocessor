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

public slots:
    void addNodeType(QString name);
    void removeNodeType(QString name);

private slots:
    void addNodes();

protected:
    Ui::NodesParam *m_ui;

private:
    // nodeTypeName -> row
    QMap<QString, int> m_nodeTypesRows;
};

#endif // NODESPARAM_H
