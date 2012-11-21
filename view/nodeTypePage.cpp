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

#include "projectStorage.h"

NodeTypePage::NodeTypePage(QString name, QList<ModuleDescriptionRaw*> modules)
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

    foreach(ModuleDescriptionRaw* module, modules)
        if (isNodeModule(module))
            moduleEnabled(module);
}

NodeTypePage::~NodeTypePage()
{
    ProjectStorage& storage = ProjectStorage::instance();
    storage.setNodeType(m_name, QList<ModuleDescriptionRaw*>());

    delete m_ui;
}

//
// -- interface --
//

void NodeTypePage::moduleEnabled(ModuleDescriptionRaw* module)
{
    addModule_toCombobox(module);
}

void NodeTypePage::moduleDisabled(ModuleDescriptionRaw* module)
{
    removeModule(module);
}

void NodeTypePage::newModule(quint16 moduleID)
{
    ProjectStorage& storage = ProjectStorage::instance();
    ModuleDescriptionRaw* module = storage.getModule(moduleID);
    addModule_toTable(module);
    int index = m_indexes.key(module, -1);
    if (index != -1)
        removeModule_fromCombobox(index);
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
    int count = m_ui->cb_modules->count();
    m_indexes[count] = module;
    m_ui->cb_modules->addItem(module->name);
}

void NodeTypePage::removeModule(ModuleDescriptionRaw* module)
{
    int index = m_indexes.key(module, -1);
    if (index != -1)
        removeModule_fromCombobox(index);

    int row = m_nodeType.key(module, -1);
    if (row != -1)
        removeModule_fromTable(row);
}

void NodeTypePage::addModule_toTable_fromCombobox()
{
    int index = m_ui->cb_modules->currentIndex();
    addModule_toTable(m_indexes[index]);
    removeModule_fromCombobox(index);
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

    m_nodeTypesModules += module;
    m_nodeType[row] = module;

    ProjectStorage& storage = ProjectStorage::instance();
    storage.setNodeType(m_name, m_nodeTypesModules);
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
    ModuleDescriptionRaw* module = m_nodeType[row];
    m_ui->t_modules->removeRow(row);
    m_nodeType.remove(row);
    m_nodeTypesModules.removeAll(module);

    ProjectStorage& storage = ProjectStorage::instance();
    storage.setNodeType(m_name, m_nodeTypesModules);
}

void NodeTypePage::removeModule_fromCombobox(int index)
{
    m_ui->cb_modules->removeItem(index);
    m_indexes.remove(index);
}
