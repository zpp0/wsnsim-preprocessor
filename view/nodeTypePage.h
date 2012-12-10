/**
 *
 * File: nodeTypePage.h
 * Description: nodeType widget
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef NODETYPEPAGE_H
#define NODETYPEPAGE_H

#include <QMap>
#include <QString>
#include <QLineEdit>
#include <QGroupBox>
#include <QComboBox>

#include "modulesParams.h"
#include "projectParams.h"

namespace Ui {
    class NodeTypePage;
}

class NodeTypePage : public QGroupBox
{
    Q_OBJECT

public:
    NodeTypePage(QString name);
    virtual ~NodeTypePage();

    NodeTypeData getNodeType();
    void setNodeType(NodeTypeData nodeType);

public slots:
    void moduleEnabled(ModuleDescriptionRaw* module, bool enabled);

private slots:

    void customContextMenuRequested(const QPoint &p);
    void addModule_toTable_fromCombobox();

    void renameNodeType(QString newName, QString oldName);
private:

    bool isNodeModule(ModuleDescriptionRaw* module);

    void addModule_toCombobox(ModuleDescriptionRaw* module);
    void removeModule(ModuleDescriptionRaw* module);
    void addModule_toTable(ModuleDescriptionRaw* module);
    void removeModule_fromTable(int row);
    void removeModule_fromCombobox(int index);

    QString m_name;

    // combobox index -> module
    QList<ModuleDescriptionRaw*> m_indexes;

    // table row -> module
    QList<ModuleDescriptionRaw*> m_nodeType;

    Ui::NodeTypePage *m_ui;
};

#endif // NODETYPEPAGE_H
