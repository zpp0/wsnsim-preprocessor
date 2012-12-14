/**
 *
 * File: modulesInfo.cpp
 * Description: Display module parameters widget
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#include "modulesInfo.h"
#include "luaEditor.h"

#include "modulesInfoDialog.h"

ModulesInfo::ModulesInfo(QWidget* parent)
    :QTableWidget(parent), m_parent(parent)
{
    // setup module table header
    m_moduleInfo << tr("Enabled")
                 << tr("Module")
                 << tr("Type")
                 << tr("Description");

    setColumnCount(m_moduleInfo.size());
    setHorizontalHeaderLabels(m_moduleInfo);
    horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    setSelectionMode(QAbstractItemView::NoSelection);

    setWordWrap(true);

    setEditTriggers(QAbstractItemView::NoEditTriggers);

    verticalHeader()->setVisible(false);

    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(customContextMenuRequested(const QPoint &)));

}

ModulesInfo::~ModulesInfo()
{
    int rows = rowCount();
    for (int row = 0; row < rows; row++)
        delete cellWidget(0, row);
    clear();
}

void ModulesInfo::clean()
{
    int rows = rowCount();
    for (int row = 0; row < rows; row++)
        delete cellWidget(0, row);
    clear();
    setRowCount(0);
    m_modules.clear();
    m_rows.clear();

    setHorizontalHeaderLabels(m_moduleInfo);
}

void ModulesInfo::addModuleInfo(ModuleDescriptionRaw* module)
{
    int rows = rowCount();

    setRowCount(rows + 1);

    CheckModule* checkModule = new CheckModule(module);
    connect(checkModule, SIGNAL(moduleEnabled(ModuleDescriptionRaw*)),
            m_parent, SLOT(moduleEnabled(ModuleDescriptionRaw*)),
            Qt::DirectConnection);
    connect(checkModule, SIGNAL(moduleDisabled(ModuleDescriptionRaw*)),
            m_parent, SLOT(moduleDisabled(ModuleDescriptionRaw*)),
            Qt::DirectConnection);

    m_modules[module] = checkModule;
    m_rows[rows] = module;

    setCellWidget(rows, 0, checkModule);

    // FIXME: do it right
    setItem(rows, 1, new QTableWidgetItem(module->name));
    setItem(rows, 2, new QTableWidgetItem(module->type));
    setItem(rows, 3, new QTableWidgetItem(module->description));
}

void ModulesInfo::enableModuleInfo(ModuleDescriptionRaw* module)
{
    m_modules[module]->enabled(true);
}

void ModulesInfo::disableModuleInfo(ModuleDescriptionRaw* module)
{
    m_modules[module]->enabled(false);
}

void ModulesInfo::disableAllModules()
{
    foreach(ModuleDescriptionRaw* module, m_modules.keys())
        disableModuleInfo(module);
}

void ModulesInfo::customContextMenuRequested(const QPoint &p)
{
    QTableWidgetItem* ti_item = itemAt(p);
    if (ti_item != NULL) {

        QMenu menu(this);

        QAction* actionShowInfo = menu.addAction(tr("&Show info"));
        QAction* actionOpen = menu.addAction(tr("&Open"));
        QAction* actionOpenInExternalEditor = menu.addAction(tr("Open in &external editor"));
        QAction* actionRescan = menu.addAction(tr("Re&scan (unimplemented)"));
        QAction* actionRemove = menu.addAction(tr("&Remove module (unimplemented)"));

        QAction *a = menu.exec(mapToGlobal(p));

        ModuleDescriptionRaw* module = m_rows[row(ti_item)];

        if (a == actionShowInfo) {
            ModulesInfoDialog dialog(this);
            dialog.addModule(module);
            dialog.exec();
        }

        else if (a == actionOpen) {
            LuaEditor editor;
            editor.openModule(module->fileName);
            editor.exec();
        }

        else if (a == actionOpenInExternalEditor) {
            ModuleDescriptionRaw* module = m_rows[row(ti_item)];
            LuaEditor::openModuleInExternalEditor(module->fileName);
        }

        else if (a == actionRescan) {
        }
        else if (a == actionRemove) {
        }

    }
    else {
        QMenu menu(this);
        QAction* actionShowInfo = menu.addAction(tr("&Show all info"));

        QAction *a = menu.exec(mapToGlobal(p));

        if (a == actionShowInfo) {
            ModulesInfoDialog dialog(this);
            foreach(ModuleDescriptionRaw* module, m_rows.values())
                dialog.addModule(module);
            // dialog.adjustSize();
            dialog.exec();
        }
    }
}
