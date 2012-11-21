/**
 *
 * File: nodeTypesPage.cpp
 * Description: Page of choosing nodeTypes from list
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#include "nodeTypesPage.h"
#include "ui_nodeTypesPage.h"

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

NodeTypesPage::~NodeTypesPage()
{
    delete m_ui;
}

void NodeTypesPage::newNodeType(NodeTypeData* nodeType)
{
    createNodeTypePage(nodeType->name);
    NodeTypePage* page = m_nodeTypes[nodeType->name];

    for (int i = 0; i < nodeType->hardwareModules.size(); i++)
        page->newModule(nodeType->hardwareModules[i]);
    for (int i = 0; i < nodeType->softwareModules.size(); i++)
        page->newModule(nodeType->softwareModules[i]);
}

void NodeTypesPage::moduleEnabled(ModuleDescriptionRaw* module)
{
    m_modules += module;

    foreach(NodeTypePage* page, m_nodeTypes.values())
        page->moduleEnabled(module);
}

void NodeTypesPage::moduleDisabled(ModuleDescriptionRaw* module)
{
    m_modules.removeOne(module);

    foreach(NodeTypePage* page, m_nodeTypes.values())
        page->moduleDisabled(module);
}

void NodeTypesPage::createNodeTypePage(QString nodeTypeName)
{
    NodeTypePage* page = new NodeTypePage(nodeTypeName, m_modules);

    m_nodeTypes[nodeTypeName] = page;
    m_nodeTypesNames += nodeTypeName;

    m_ui->list_nodeTypes->addItem(new QListWidgetItem(nodeTypeName));

    QTreeWidgetItem* ti_page = m_projectTree->addTiWidget(nodeTypeName, m_selfTreeElement);
    m_projectTree->addPage(ti_page, page);
}

void NodeTypesPage::createNodeTypePage()
{
    QString nodeTypeName = m_ui->le_nodeType->text();
    createNodeTypePage(nodeTypeName);
    m_ui->le_nodeType->setText("");
}

void NodeTypesPage::deleteNodeTypePage(QListWidgetItem* nodeTypeItem)
{
    QString nodeTypeName = nodeTypeItem->text();

    deleteNodeTypePage(nodeTypeName);

    m_ui->list_nodeTypes->removeItemWidget(nodeTypeItem);
    delete nodeTypeItem;
}

void NodeTypesPage::deleteNodeTypePage(QString nodeTypeName)
{
    // TODO: check if user change params
    NodeTypePage* page = m_nodeTypes[nodeTypeName];
    m_nodeTypes.remove(nodeTypeName);

    m_projectTree->removePage(page);

    delete page;
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

void NodeTypesPage::clean()
{
    foreach(QString name, m_nodeTypesNames)
        deleteNodeTypePage(name);
    m_ui->list_nodeTypes->clear();
}
