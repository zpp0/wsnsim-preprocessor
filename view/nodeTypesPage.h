/**
 *
 * File: nodeTypesPage.h
 * Description: Page of node types
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef NODETYPESPAGE_H
#define NODETYPESPAGE_H

#include <QtGui>

#include "projectParams.h"
#include "moduleParams.h"
#include "projectTree.h"

#include "nodeTypePage.h"

namespace Ui {
    class NodeTypesPage;
}

class NodeTypesPage : public QGroupBox
{
    Q_OBJECT

public:
    NodeTypesPage(QTreeWidgetItem* treeElement = 0, ProjectTree* projectTree = 0);
    virtual ~NodeTypesPage();

    QList<NodeTypeData> getNodeTypes();
    void setNodeTypes(QList<NodeTypeData> nodeTypes);

    void clear();

private slots:
    void isNewNodeTypeName(QString name);
    void customContextMenuRequested(const QPoint &p);
    void createNodeTypePage();

private:
    void createNodeTypePage(QString name);
    void deleteNodeTypePage(QListWidgetItem* nodeTypeItem);

    QList<QString> m_nodeTypesNames;

    QMap<QString, NodeTypePage*> m_nodeTypes;

    ProjectTree* m_projectTree;
    QTreeWidgetItem* m_selfTreeElement;

    Ui::NodeTypesPage *m_ui;
};

#endif // NODETYPESPAGE_H
