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

    void clean();

public slots:
    void newNodeType(NodeTypeData* nodeType);

    void moduleEnabled(ModuleDescriptionRaw* module);
    void moduleDisabled(ModuleDescriptionRaw* module);

private slots:
    void isNewNodeTypeName(QString name);
    void customContextMenuRequested(const QPoint &p);
    void createNodeTypePage();

private:
    void createNodeTypePage(QString name);

    void deleteNodeTypePage(QListWidgetItem* nodeTypeItem);
    void deleteNodeTypePage(QString nodeTypeName);

    QList<ModuleDescriptionRaw*> m_modules;

    QList<QString> m_nodeTypesNames;

    QMap<QString, NodeTypePage*> m_nodeTypes;

    ProjectTree* m_projectTree;
    QTreeWidgetItem* m_selfTreeElement;

    Ui::NodeTypesPage *m_ui;
};

#endif // NODETYPESPAGE_H
