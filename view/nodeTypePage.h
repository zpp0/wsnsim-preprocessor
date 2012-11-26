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

#include "moduleParams.h"
#include "projectParams.h"

namespace Ui {
    class NodeTypePage;
}

class NodeTypePage : public QGroupBox
{
    Q_OBJECT

public:
    NodeTypePage(QString name, QList<ModuleDescriptionRaw*> modules);
    virtual ~NodeTypePage();

    void moduleEnabled(ModuleDescriptionRaw* module);
    void moduleDisabled(ModuleDescriptionRaw* module);

    void newModule(quint16 moduleID);

private slots:

    void customContextMenuRequested(const QPoint &p);
    // void removeModule(int row);

    void addModule_toTable_fromCombobox();
private:

    bool isNodeModule(ModuleDescriptionRaw* module);

    void addModule_toCombobox(ModuleDescriptionRaw* module);
    void removeModule(ModuleDescriptionRaw* module);
    void addModule_toTable(ModuleDescriptionRaw* module);
    void removeModule_fromTable(int row);
    void removeModule_fromCombobox(int index);

    QString m_name;
    // module -> moduleID
    QList<ModuleDescriptionRaw*> m_nodeTypesModules;

    // combobox index -> module
    QList<ModuleDescriptionRaw*> m_indexes;

    // table row -> module
    QList<ModuleDescriptionRaw*> m_nodeType;

    Ui::NodeTypePage *m_ui;
};

#endif // NODETYPEPAGE_H
