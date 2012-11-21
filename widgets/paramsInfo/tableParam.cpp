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
    for (int i = 0; i < columns; i++)
        columnsNames << args["columnName" + QString::number(i+1)];

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

    // TODO: remove old connections and the relevant values from param->value if the current rows count are less than new number

    for (int i = 0; i < number; i++) {
        m_ui->table->setItem(i, 0, new QTableWidgetItem(QString::number(i)));

        for (int col = 1; col < m_columns; col++) {
            QTableWidgetItem* item = new QTableWidgetItem();

            m_ui->table->setItem(i, col, item);

            m_tableColumns[item] = col;
            m_tableRows[item] = i;
        }
    }
}

void ModuleParamTable::setParamValue(QVariant value)
{
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

void ModuleParamTable::setParamValue(int row, int column, double value)
{
    // QMap<QString, QVariant> value = m_param->value.toMap();
    // TODO: do it
}
