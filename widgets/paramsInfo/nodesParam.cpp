/**
 *
 * File: nodesParam.cpp
 * Description: module param with nodes type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "nodesParam.h"
#include "ui_nodesParam.h"

#include "projectStorage.h"

ModuleParamNodes::ModuleParamNodes(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw, ModuleParam* param)
    :m_ui(new Ui::NodesParam), ModuleParamGeneral(module, paramRaw, param)
{
    m_ui->setupUi(this);

    m_ui->t_nodes->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    connect(m_ui->b_add, SIGNAL(clicked()),
            this, SLOT(addNodes()));
}

ModuleParamNodes::~ModuleParamNodes()
{
    delete m_ui;
}

void ModuleParamNodes::addNodes()
{
    QString nodeType = m_ui->cb_nodeType->currentText();

    int number = m_ui->sb_nodesNum->value();

    int row = m_nodeTypesRows.value(nodeType, -1);
    if (row == -1) {
        row = m_ui->t_nodes->rowCount();
        m_ui->t_nodes->insertRow(row);
    }

    m_ui->t_nodes->setItem(row, 0, new QTableWidgetItem(nodeType));
    m_ui->t_nodes->setItem(row, 1, new QTableWidgetItem(QString::number(number)));

    m_nodeTypesRows[nodeType] = row;

    QMap<QString, QVariant> value = m_param->value.toMap();
    value[nodeType] = row;
    m_param->value = value;

    ProjectStorage& storage = ProjectStorage::instance();
    storage.addNodes(m_module, nodeType, number);
}

void ModuleParamNodes::addNodeType(QString name)
{
    m_ui->cb_nodeType->addItem(name);
}

void ModuleParamNodes::removeNodeType(QString name)
{
    m_ui->cb_nodeType->removeItem(m_ui->cb_nodeType->findText(name));
}
