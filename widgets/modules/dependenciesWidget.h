/**
 *
 * File: dependenciesWidget.h
 * Description: Widget of choosing dependencies of the modules
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef DEPENDENCIESWIDGET_H
#define DEPENDENCIESWIDGET_H

#include <QtGui>

#include "modulesParams.h"
#include "projectParams.h"

#include "interfaceInfo.h"

namespace Ui {
    class DependenciesWidget;
}

class DependenciesWidget : public QGroupBox
{
    Q_OBJECT

public:
    DependenciesWidget(ModuleDescriptionRaw* module);
    virtual ~DependenciesWidget();

    QList<ModuleDependence> getDependencies();
    void setDependencies(QList<ModuleDependence> dependencies);

private:
    void createDependence(ModuleDependRaw* dependence);
    ModuleDependRaw* getDependenceRaw(ModuleDependence dependence);

    ModuleDescriptionRaw* m_selfModule;

    QList<InterfaceInfo*> m_interfaces;

    QMap<ModuleDependRaw*, InterfaceInfo*> m_dependencies;

    Ui::DependenciesWidget* m_ui;
};

#endif // DEPENDENCIESWIDGET_H
