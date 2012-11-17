/**
 *
 * File: dependenciesPage.h
 * Description: Page of choosing dependencies of the modules
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef DEPENDENCIESPAGE_H
#define DEPENDENCIESPAGE_H

#include <QtGui>

#include "moduleParams.h"
#include "projectParams.h"

#include "interfaceInfo.h"

namespace Ui {
    class DependenciesPage;
}

class DependenciesPage : public QGroupBox
{
    Q_OBJECT

public:
    DependenciesPage(ModuleDescriptionRaw* module, ModuleData* moduleData, bool withDeps);
    virtual ~DependenciesPage();

    void moduleEnabled(ModuleDescriptionRaw* module);
    void moduleDisabled(ModuleDescriptionRaw* module);

    void createDependence(ModuleDescriptionRaw* module, ModuleDependence* dependence);

private:
    ModuleDescriptionRaw* m_module;
    ModuleData* m_moduleData;

    QList<InterfaceInfo*> m_interfaces;

    Ui::DependenciesPage *m_ui;
};

#endif // DEPENDENCIESPAGE_H
