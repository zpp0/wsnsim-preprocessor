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
#include "errorsStorage.h"

#include "renamingNodeTypeDialog.h"

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

    m_ui->b_add->setEnabled(false);
    setNodeTypesError(true);
}

void NodeTypesPage::createNodeTypePage(QString nodeTypeName)
{
    NodeTypePage* page = new NodeTypePage(nodeTypeName);

    m_nodeTypes[nodeTypeName] = page;
    m_nodeTypesNames += nodeTypeName;

    m_ui->list_nodeTypes->addItem(new QListWidgetItem(nodeTypeName));

    QTreeWidgetItem* ti_page = m_projectTree->addTiWidget(nodeTypeName, m_selfTreeElement);
    m_nodeTypesTree[nodeTypeName] = ti_page;

    m_projectTree->addPage(ti_page, page);

    NodesStorage::instance().addNodeType(nodeTypeName);

    if (m_nodeTypesNames.size() == 1)
        setNodeTypesError(false);
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

    if (m_nodeTypesNames.isEmpty())
        setNodeTypesError(true);
}

void NodeTypesPage::isNewNodeTypeName(QString name)
{
    if (name == "")
        m_ui->b_add->setEnabled(false);
    else if (m_nodeTypesNames.contains(name))
        m_ui->b_add->setEnabled(false);
    else if ((!m_nodeTypesNames.contains(name))
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
    QAction* actionRename = menu.addAction(tr("&Rename"));

    QAction* a = menu.exec(m_ui->list_nodeTypes->mapToGlobal(p));

    if (a == actionRemove)
        deleteNodeTypePage(nt_name);
    else if (a == actionRename)
        renameNodeTypePage(nt_name);
}

void NodeTypesPage::renameNodeTypePage(QListWidgetItem* nodeTypeItem)
{
    QString name = nodeTypeItem->text();
    RenamingNodeTypeDialog dialog(name, this);

    int ret = dialog.exec();
    if (ret == QDialog::Accepted) {
        QString newName = dialog.getNewName();
        NodesStorage::instance().renameNodeType(newName, name);

        nodeTypeItem->setText(newName);

        QTreeWidgetItem* ti_page = m_nodeTypesTree[name];
        ti_page->setText(0, newName);
        m_nodeTypesTree.remove(name);
        m_nodeTypesTree[newName] = ti_page;
    }
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

void NodeTypesPage::setNodeTypesError(bool error)
{
    ErrorsStorage::instance().setPossibleError(m_ui->list_nodeTypes,
                                               error,
                                               title() + ": " + tr("no node types chosen"));
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
