/**
 *
 * File: tableParam.h
 * Description: module param with table type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef TABLEPARAM_H
#define TABLEPARAM_H

#include "generalParam.h"

namespace Ui {
    class TableParam;
}

class ModuleParamTable : protected ModuleParamGeneral
{
    Q_OBJECT

public:
    ModuleParamTable(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw);
    virtual ~ModuleParamTable();

    void setParam(ModuleParam param);
    ModuleParam getParam();

protected:
    Ui::TableParam *m_ui;

private slots:
    void setNodesNum(int number);

private:
    void createNodes(int number, int from = 0);

    QMap<int, QString> m_columnsNames;
    int m_columns;
};

#endif // TABLEPARAM_H
