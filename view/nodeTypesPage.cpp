/**
 *
 * File: nodeTypesPage.cpp
 * Description: Page of choosing nodeTypes from list
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#include "nodeTypesPage.h"
#include "ui_nodeTypesPage.h"

#include "nodesStorage.h"

NodeTypesPage::NodeTypesPage(QTreeWidgetItem* treeElement, ProjectTree* projectTree)
    :m_ui(new Ui::NodeTypesPage)
{
    m_ui->setupUi(this);

    m_selfTreeElement = treeElement;
    m_projectTree = projectTree;

    connect(m_ui->le_nodeType, SIGNAL(textChanged(QString)),
            this, SLOT(isNewNodeTypeName(QString)));

    connect(m_ui->b_add, SIGNAL(clicked()),
            this, SLOT(createNodeTypePage()));

    connect(m_ui->list_nodeTypes, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(customContextMenuRequested(const QPoint &)));
}

void NodeTypesPage::createNodeTypePage(QString nodeTypeName)
{
    NodeTypePage* page = new NodeTypePage(nodeTypeName);

    m_nodeTypes[nodeTypeName] = page;
    m_nodeTypesNames += nodeTypeName;

    m_ui->list_nodeTypes->addItem(new QListWidgetItem(nodeTypeName));

    QTreeWidgetItem* ti_page = m_projectTree->addTiWidget(nodeTypeName, m_selfTreeElement);
    m_projectTree->addPage(ti_page, page);

    NodesStorage::instance().addNodeType(nodeTypeName);
}

void NodeTypesPage::createNodeTypePage()
{
    QString nodeTypeName = m_ui->le_nodeType->text();
    createNodeTypePage(nodeTypeName);
    m_ui->le_nodeType->setText("");
}

void NodeTypesPage::deleteNodeTypePage(QListWidgetItem* nodeTypeItem)
{
    // TODO: check if user change params
    QString nodeTypeName = nodeTypeItem->text();

    NodeTypePage* page = m_nodeTypes[nodeTypeName];
    m_nodeTypes.remove(nodeTypeName);

    m_projectTree->removePage(page);

    delete page;

    m_ui->list_nodeTypes->removeItemWidget(nodeTypeItem);
    delete nodeTypeItem;

    NodesStorage::instance().removeNodeType(nodeTypeName);
}

void NodeTypesPage::isNewNodeTypeName(QString name)
{
    if (m_nodeTypesNames.contains(name))
        m_ui->b_add->setEnabled(false);
    if ((!m_nodeTypesNames.contains(name))
        && (!m_ui->b_add->isEnabled()))
        m_ui->b_add->setEnabled(true);
}

void NodeTypesPage::customContextMenuRequested(const QPoint &p)
{
    QListWidgetItem* nt_name = m_ui->list_nodeTypes->itemAt(p);

    if (nt_name == NULL)
        return;

    QMenu menu(m_ui->list_nodeTypes);

    QAction* actionRemove = menu.addAction(tr("&Remove"));

    QAction* a = menu.exec(m_ui->list_nodeTypes->mapToGlobal(p));

    if (a == actionRemove)
        deleteNodeTypePage(nt_name);
}

QList<NodeTypeData> NodeTypesPage::getNodeTypes()
{
    QList<NodeTypeData> nodeTypes;

    foreach(NodeTypePage* nodeTypePage, m_nodeTypes.values())
        nodeTypes += nodeTypePage->getNodeType();

    return nodeTypes;
}

void NodeTypesPage::setNodeTypes(QList<NodeTypeData> nodeTypes)
{
    foreach(NodeTypeData nodeType, nodeTypes) {
        createNodeTypePage(nodeType.name);
        m_nodeTypes[nodeType.name]->setNodeType(nodeType);
    }
}

void NodeTypesPage::clear()
{
    foreach(QString name, m_nodeTypesNames) {
        QList<QListWidgetItem*> items = m_ui->list_nodeTypes->findItems(name, Qt::MatchFixedString);
        foreach(QListWidgetItem* item, items)
            deleteNodeTypePage(item);
    }

    m_ui->list_nodeTypes->clear();
}

NodeTypesPage::~NodeTypesPage()
{
    delete m_ui;
}
