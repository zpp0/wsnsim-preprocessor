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
    ModuleParamTable(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw, ModuleParam* param);
    virtual ~ModuleParamTable();

protected:
    Ui::TableParam *m_ui;

private slots:
    void setNodesNum(int number);
    void itemChanged(QTableWidgetItem* item);

private:
    void setParamValue(int row, int column, double value);
    QMap<QTableWidgetItem*, int> m_tableColumns;
    QMap<QTableWidgetItem*, int> m_tableRows;
    int m_columns;
};

#endif // TABLEPARAM_H
