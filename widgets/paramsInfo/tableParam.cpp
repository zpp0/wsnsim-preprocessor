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

#include "projectStorage.h"

ModuleParamTable::ModuleParamTable(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw, ModuleParam* param)
    :ModuleParamGeneral(module, paramRaw, param), m_ui(new Ui::TableParam)
{
    m_ui->setupUi(this);

    m_ui->g_info->setTitle(m_paramRaw->name);

    QMap<QString, QString> args = m_paramRaw->arguments;

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

    if (!m_param->value.isNull())
        setParamValue(m_param->value);

    ProjectStorage& storage = ProjectStorage::instance();
    connect (&storage, SIGNAL(setNodesNum(int)),
             this, SLOT(setNodesNum(int)));

    connect(m_ui->table, SIGNAL(itemChanged(QTableWidgetItem*)),
            this, SLOT(itemChanged(QTableWidgetItem*)));
}

void ModuleParamTable::setNodesNum(int number)
{
    m_ui->table->setRowCount(number);
    createNodes(number);
}

void ModuleParamTable::createNodes(int number, int from)
{
    // TODO: remove old connections and the relevant values from param->value if the current rows count are less than new number
    for (int i = from; i < number; i++) {
        m_ui->table->setItem(i, 0, new QTableWidgetItem(QString::number(i)));

        for (int col = 1; col < m_columns; col++) {
            QTableWidgetItem* item = new QTableWidgetItem("0");

            m_ui->table->setItem(i, col, item);

            m_tableColumns[item] = col;
            m_tableRows[item] = i;

            setParamValue(i, col, 0);
        }
    }
}

void ModuleParamTable::setParamValue(QVariant value)
{
    QMap<QString, QVariant> map = value.toMap();
    foreach(QString column, map.keys()) {
        foreach(QString row, map[column].toMap().keys()) {
            int irow = row.toInt();

            int rows = m_ui->table->rowCount();
            if (rows <= irow) {
                m_ui->table->setRowCount(irow + 1);

                for (int i = rows; i <= irow; i++)
                    m_ui->table->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
            }

            QString svalue = QString::number(map[column].toMap()[row].toDouble());

            QTableWidgetItem* item = new QTableWidgetItem(svalue);
            int icol = m_columnsNames.key(column);

            m_tableColumns[item] = icol;
            m_tableRows[item] = irow;

            m_ui->table->setItem(irow, icol, item);
        }
    }
}

ModuleParamTable::~ModuleParamTable()
{
    delete m_ui;
}

void ModuleParamTable::itemChanged(QTableWidgetItem* item)
{
    if (m_tableColumns.contains(item) && m_tableRows.contains(item)) {
        double value = item->text().toDouble();
        int col = m_tableColumns[item];
        int row = m_tableRows[item];
        setParamValue(row, col, value);
    }
}

void ModuleParamTable::setParamValue(int row, int column, double paramValue)
{
    QMap<QString, QVariant> value = m_param->value.toMap();
    QString name = m_columnsNames[column];
    QMap<QString, QVariant> array = value[name].toMap();
    array[QString::number(row)] = paramValue;
    value[name] = array;
    m_param->value = value;
}
