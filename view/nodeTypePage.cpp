/**
 *
 * File: nodeTypePage.cpp
 * Description: nodeType widget
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include <QMenu>

#include "nodeTypePage.h"
#include "ui_nodeTypePage.h"

#include "modulesStorage.h"

NodeTypePage::NodeTypePage(QString name)
    :m_ui(new Ui::NodeTypePage)
{
    m_ui->setupUi(this);

    m_name = name;

    setTitle(name);

    m_ui->t_modules->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    m_ui->t_modules->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    connect(m_ui->t_modules, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(customContextMenuRequested(const QPoint &)));

    connect(m_ui->b_addModule, SIGNAL(clicked()),
            this, SLOT(addModule_toTable_fromCombobox()));

    ModulesStorage& storage = ModulesStorage::instance();

    QList<ModuleDescriptionRaw*> modules = storage.getEnabled();
    foreach(ModuleDescriptionRaw* module, modules)
        moduleEnabled(module, true);

    connect(&storage, SIGNAL(moduleEnabled(ModuleDescriptionRaw*, bool)),
            this, SLOT(moduleEnabled(ModuleDescriptionRaw*, bool)));
}

//
// -- interface --
//

NodeTypeData NodeTypePage::getNodeType()
{
    NodeTypeData nodeType;
    nodeType.name = m_name;
    foreach(ModuleDescriptionRaw* module, m_nodeType) {
        quint16 moduleID = ModulesStorage::instance().getModule(module);
        if (module->type == "hardware")
            nodeType.hardwareModules += moduleID;
        else if (module->type == "software")
            nodeType.softwareModules += moduleID;
    }
    return nodeType;
}

void NodeTypePage::setNodeType(NodeTypeData nodeType)
{
    ModuleDescriptionRaw* module;
    QList<quint16> modules;
    modules += nodeType.hardwareModules;
    modules += nodeType.softwareModules;
    foreach(quint16 moduleID, modules) {
        module = ModulesStorage::instance().getModule(moduleID);
        addModule_toTable(module);
        int row = m_nodeType.indexOf(module);
        if (row != -1)
            removeModule_fromTable(row);
    }
}

//
// -- slots --
//

void NodeTypePage::moduleEnabled(ModuleDescriptionRaw* module, bool enabled)
{
    if (isNodeModule(module)) {
        if (enabled)
            addModule_toCombobox(module);
        else
            removeModule(module);
    }
}

//
// -- private methods --
//

bool NodeTypePage::isNodeModule(ModuleDescriptionRaw* module)
{
    return ((module->type == "software") || (module->type == "hardware"));
}

void NodeTypePage::addModule_toCombobox(ModuleDescriptionRaw* module)
{
    m_indexes += module;
    m_ui->cb_modules->addItem(module->name);
}

void NodeTypePage::removeModule(ModuleDescriptionRaw* module)
{
    int index = m_indexes.indexOf(module);
    if (index != -1)
        removeModule_fromCombobox(index);

    int row = m_nodeType.indexOf(module);
    if (row != -1)
        removeModule_fromTable(row);
}

void NodeTypePage::addModule_toTable_fromCombobox()
{
    int index = m_ui->cb_modules->currentIndex();
    if (index != -1) {
        addModule_toTable(m_indexes[index]);
        removeModule_fromCombobox(index);
    }
}

void NodeTypePage::addModule_toTable(ModuleDescriptionRaw* module)
{
    if (!module)
        return;

    int row = m_ui->t_modules->rowCount();
    m_ui->t_modules->setRowCount(row + 1);

    m_ui->t_modules->setItem(row, 0, new QTableWidgetItem(module->name));
    m_ui->t_modules->setItem(row, 1, new QTableWidgetItem(module->type));
    m_ui->t_modules->setItem(row, 2, new QTableWidgetItem(module->description));

    m_nodeType += module;
}

void NodeTypePage::customContextMenuRequested(const QPoint &p)
{
    QTableWidgetItem* ti_nt_name = m_ui->t_modules->itemAt(p);

    if (ti_nt_name == NULL)
        return;

    QMenu menu(m_ui->t_modules);

    QAction* actionRemove = menu.addAction(tr("&Remove"));

    QAction *a = menu.exec(m_ui->t_modules->mapToGlobal(p));

    if (a == actionRemove) {
        int row = m_ui->t_modules->row(ti_nt_name);
        ModuleDescriptionRaw* module = m_nodeType[row];
        removeModule_fromTable(row);
        addModule_toCombobox(module);
    }
}

void NodeTypePage::removeModule_fromTable(int row)
{
    m_ui->t_modules->removeRow(row);
    m_nodeType.removeAt(row);
}

void NodeTypePage::removeModule_fromCombobox(int index)
{
    m_ui->cb_modules->removeItem(index);
    m_indexes.removeAt(index);
}

NodeTypePage::~NodeTypePage()
{
    delete m_ui;
}
