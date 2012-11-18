/**
 *
 * File: nodesParam.cpp
 * Description: module param with nodes type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "nodesParam.h"
#include "ui_nodesParam.h"

#include "nodeTypeSpinBox.h"

#include "projectStorage.h"

ModuleParamNodes::ModuleParamNodes(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw, ModuleParam* param)
    :m_ui(new Ui::NodesParam), ModuleParamGeneral(module, paramRaw, param)
{
    m_ui->setupUi(this);

    m_ui->t_nodes->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    m_ui->t_nodes->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    connect(m_ui->b_add, SIGNAL(clicked()),
            this, SLOT(addNodeType()));
    connect(m_ui->b_remove, SIGNAL(clicked()),
            this, SLOT(removeNodeType()));
}

ModuleParamNodes::~ModuleParamNodes()
{
    delete m_ui;
}

void ModuleParamNodes::addNodeType()
{
    QString nodeType = m_ui->cb_nodeType->currentText();

    int row = m_nodeTypesRows.value(nodeType, -1);
    if (row == -1) {
        row = m_ui->t_nodes->rowCount();
        m_ui->t_nodes->insertRow(row);
    }

    NodeTypeSpinBox* nodeSpinBox = new NodeTypeSpinBox(nodeType);

    connect(nodeSpinBox, SIGNAL(setNodesNum(QString, int)),
            this, SLOT(setNodes(QString, int)));

    m_ui->t_nodes->setItem(row, 0, new QTableWidgetItem(nodeType));
    m_ui->t_nodes->setCellWidget(row, 1, nodeSpinBox);

    m_nodeTypesRows[nodeType] = row;
}

void ModuleParamNodes::setNodes(QString nodeType, int number)
{
    // set the param value
    QMap<QString, QVariant> value = m_param->value.toMap();
    value[nodeType] = number;
    m_param->value = value;

    // set the simulator's nodes number
    ProjectStorage& storage = ProjectStorage::instance();
    storage.setNodes(m_module, nodeType, number);

}

void ModuleParamNodes::addNodeType(QString name)
{
    m_ui->cb_nodeType->addItem(name);
}

void ModuleParamNodes::removeNodeType(QString name)
{
    m_ui->cb_nodeType->removeItem(m_ui->cb_nodeType->findText(name));
}
