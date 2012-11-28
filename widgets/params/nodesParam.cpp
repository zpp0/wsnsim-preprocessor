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
    :ModuleParamGeneral(module, paramRaw, param), m_ui(new Ui::NodesParam)
{
    m_ui->setupUi(this);

    m_dummyNodeType = tr("Nothing to add");

    m_ui->t_nodes->setContextMenuPolicy(Qt::CustomContextMenu);

    m_ui->t_nodes->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    m_ui->t_nodes->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    addDummyNodeType();

    if (!m_param->value.isNull())
        setParamValue(m_param->value);

    ProjectStorage& storage = ProjectStorage::instance();
    connect(&storage, SIGNAL(newNodeType(QString)),
            this, SLOT(addNodeType(QString)));

    connect(&storage, SIGNAL(deleteNodeType(QString)),
            this, SLOT(removeNodeType(QString)));

    connect(m_ui->b_add, SIGNAL(clicked()),
            this, SLOT(addNodeType()));

    connect(m_ui->t_nodes, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(customContextMenuRequested(const QPoint &)));
}

ModuleParamNodes::~ModuleParamNodes()
{
    delete m_ui;
}

void ModuleParamNodes::addNodeType()
{
    QString nodeType = m_ui->cb_nodeType->currentText();
    if ((nodeType != "") && (nodeType != m_dummyNodeType)) {
        addNodeType(nodeType, 0);
        removeNodeType(nodeType);
    }
}

void ModuleParamNodes::addNodeType(QString nodeType, int number)
{
    int row = m_ui->t_nodes->rowCount();
    m_ui->t_nodes->insertRow(row);

    QTableWidgetItem* ti_nodeType = new QTableWidgetItem(nodeType);
    NodeTypeSpinBox* nodeSpinBox = new NodeTypeSpinBox(nodeType);

    connect(nodeSpinBox, SIGNAL(setNodesNum(QString, int)),
            this, SLOT(setNodes(QString, int)));

    m_ui->t_nodes->setItem(row, 0, ti_nodeType);
    m_ui->t_nodes->setCellWidget(row, 1, nodeSpinBox);

    m_nodeTypesRows[nodeType] = row;
    m_nodeTypes += nodeType;

    nodeSpinBox->setValue(number);
}

void ModuleParamNodes::setNodes(QString nodeType, int number)
{
    QMap<QString, QVariant> value = m_param->value.toMap();

    // set the param value
    if (number > 0)
        value[nodeType] = number;
    else
        value.remove(nodeType);

    m_param->value = value;

    // set the simulator's nodes number
    ProjectStorage& storage = ProjectStorage::instance();
    storage.setNodes(m_module, nodeType, number);
}

void ModuleParamNodes::addNodeType(QString name)
{
    if (m_nodeTypes.contains(name))
        return;

    if ((m_ui->cb_nodeType->count() == 1)
        && (m_ui->cb_nodeType->currentText() == m_dummyNodeType))
        removeDummyNodeType();

    m_ui->cb_nodeType->addItem(name);
    m_nodeTypes += name;
}

void ModuleParamNodes::removeNodeType(QString name)
{
    int index = m_ui->cb_nodeType->findText(name, Qt::MatchFixedString);
    if (index != -1 && m_nodeTypes.contains(name)) {
        m_ui->cb_nodeType->removeItem(index);
        m_nodeTypes.removeOne(name);
    }

    if (m_ui->cb_nodeType->count() == 0)
        addDummyNodeType();
}

void ModuleParamNodes::addDummyNodeType()
{
    m_ui->cb_nodeType->addItem(m_dummyNodeType);
    m_ui->b_add->setEnabled(false);
    m_ui->cb_nodeType->setEnabled(false);
}

void ModuleParamNodes::removeDummyNodeType()
{
    m_ui->cb_nodeType->removeItem(m_ui->cb_nodeType->findText(m_dummyNodeType));
    m_ui->b_add->setEnabled(true);
    m_ui->cb_nodeType->setEnabled(true);
}

void ModuleParamNodes::customContextMenuRequested(const QPoint &p)
{
    QTableWidgetItem* ti_nt_name = m_ui->t_nodes->itemAt(p);

    if (ti_nt_name == NULL)
        return;

    QMenu menu(m_ui->t_nodes);

    QAction* actionRemove = menu.addAction(tr("&Remove"));

    QAction *a = menu.exec(m_ui->t_nodes->mapToGlobal(p));

    if (a == actionRemove)
        removeNodes(ti_nt_name->text());
}

void ModuleParamNodes::removeNodes(QString nodeType)
{
    int row = m_nodeTypesRows[nodeType];
    m_ui->t_nodes->removeCellWidget(row, 1);
    m_ui->t_nodes->removeRow(row);

    m_nodeTypes.removeOne(nodeType);

    addNodeType(nodeType);
}

void ModuleParamNodes::setParamValue(QVariant value)
{
    QMap<QString, QVariant> nodes = value.toMap();
    foreach(QString name, nodes.keys()) {
        removeNodeType(name);
        addNodeType(name, nodes[name].toInt());
    }
}
