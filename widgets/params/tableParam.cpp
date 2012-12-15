/**
 *
 * File: tableParam.cpp
 * Description: module param with table type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include <QTableWidgetItem>

#include "tableParam.h"
#include "ui_tableParam.h"

#include "nodesStorage.h"

ModuleParamTable::ModuleParamTable(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw)
    :ModuleParamGeneral(module, paramRaw), m_ui(new Ui::TableParam)
{
    m_ui->setupUi(this);

    m_ui->g_info->setTitle(m_param->info);

    QMap<QString, QString> args = m_param->arguments;

    int columns = args["columns"].toInt();

    m_columns = columns;

    QStringList columnsNames;
    for (int i = 0; i < columns; i++) {
        columnsNames << args["columnName" + QString::number(i+1)];
        m_columnsNames[i] = args["columnName" + QString::number(i+1)];
    }

    m_ui->table->setColumnCount(columns);
    m_ui->table->setHorizontalHeaderLabels(columnsNames);

    m_ui->table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    m_ui->table->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    NodesStorage& storage = NodesStorage::instance();
    connect(&storage, SIGNAL(nodesTotalChanged(int)),
            this, SLOT(setNodesNum(int)));
}

void ModuleParamTable::setNodesNum(int number)
{
    int rows = m_ui->table->rowCount();
    m_ui->table->setRowCount(number);
    if (number > rows)
        createNodes(number, rows);
}

void ModuleParamTable::createNodes(int number, int from)
{
    for (int i = from; i < number; i++) {
        m_ui->table->setItem(i, 0, new QTableWidgetItem(QString::number(i)));

        for (int col = 1; col < m_columns; col++)
            m_ui->table->setItem(i, col, new QTableWidgetItem("0"));
    }
}

void ModuleParamTable::setParam(ModuleParam param)
{
    QMap<QString, QVariant> map = param.value.toMap();
    foreach(QString row, map.keys()) {
        foreach(QString column, map[row].toMap().keys()) {
            int irow = row.toInt();

            int rows = m_ui->table->rowCount();
            if (rows < irow) {
                m_ui->table->setRowCount(irow + 1);

                for (int i = rows; i <= irow; i++)
                    m_ui->table->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
            }

            QString svalue = QString::number(map[row].toMap()[column].toDouble());

            int icol = m_columnsNames.key(column);

            m_ui->table->setItem(irow, icol, new QTableWidgetItem(svalue));
        }
    }
}

ModuleParam ModuleParamTable::getParam()
{
    ModuleParam param;
    param.name = m_param->name;
    param.type = m_param->type;

    QMap<QString, QVariant> table;

    int rows = m_ui->table->rowCount();
    for (int i = 0; i < rows; i++) {
        QMap<QString, QVariant> row;
        for (int j = 0; j < m_columns; j++)
            row[m_columnsNames[j]] = m_ui->table->item(i, j)->text().toDouble();
        table[QString::number(i)] = row;
    }

    param.value = table;

    return param;
}

ModuleParamTable::~ModuleParamTable()
{
    delete m_ui;
}
