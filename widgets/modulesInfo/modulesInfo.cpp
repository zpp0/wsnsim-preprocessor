/**
 *
 * File: modulesInfo.cpp
 * Description: Display module parameters widget
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#include "modulesInfo.h"

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
}

ModulesInfo::~ModulesInfo()
{
    int rows = rowCount();
    for (int row = 0; row < rows; row++)
        delete cellWidget(0, row);
    clear();
}

void ModulesInfo::addModuleInfo(ModuleDescriptionRaw* module)
{
    int rows = rowCount();

    setRowCount(rows + 1);

    CheckModule* checkModule = new CheckModule(module);
    connect(checkModule, SIGNAL(moduleEnabled(ModuleDescriptionRaw*)),
            m_parent, SLOT(moduleEnabled(ModuleDescriptionRaw*)));
    connect(checkModule, SIGNAL(moduleDisabled(ModuleDescriptionRaw*)),
            m_parent, SLOT(moduleDisabled(ModuleDescriptionRaw*)));

    m_modules[module] = checkModule;

    setCellWidget(rows, 0, checkModule);

    // FIXME: do it right
    setItem(rows, 1, new QTableWidgetItem(module->name));
    setItem(rows, 2, new QTableWidgetItem(module->type));
    setItem(rows, 3, new QTableWidgetItem(module->shortDescription));
}

void ModulesInfo::enableModuleInfo(ModuleDescriptionRaw* module)
{
    m_modules[module]->enabled(true);
}

void ModulesInfo::disableModuleInfo(ModuleDescriptionRaw* module)
{
    m_modules[module]->enabled(false);
}
