/**
 *
 * File: dependenciesWidget.cpp
 * Description: Module dependencies widget
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "dependenciesWidget.h"
#include "ui_dependenciesWidget.h"

DependenciesWidget::DependenciesWidget(ModuleDescriptionRaw* module)
    : m_ui(new Ui::DependenciesWidget)
{
    m_ui->setupUi(this);

    m_selfModule = module;

    for (int i = 0; i < m_selfModule->dependencies.size(); i++)
        createDependence(&(m_selfModule->dependencies[i]));
}

void DependenciesWidget::createDependence(ModuleDependRaw* dependence)
{
    InterfaceInfo* interface = new InterfaceInfo(m_selfModule, dependence);

    m_dependencies[dependence] = interface;
    m_interfaces += interface;

    m_ui->layout->insertWidget(0, interface);
}

QList<ModuleDependence> DependenciesWidget::getDependencies()
{
    QList<ModuleDependence> dependencies;

    foreach(InterfaceInfo* interface, m_interfaces)
        dependencies += interface->getValue();

    return dependencies;
}

ModuleDependRaw* DependenciesWidget::getDependenceRaw(ModuleDependence dependence)
{
    ModuleDependRaw* depend = NULL;

    foreach(ModuleDependRaw* dep, m_dependencies.keys()) {
        if (dep->name == dependence.name) {
            depend = dep;
            break;
        }
    }

    return depend;
}

void DependenciesWidget::setDependencies(QList<ModuleDependence> dependencies)
{
    foreach(ModuleDependence dependence, dependencies) {
        ModuleDependRaw* depend = getDependenceRaw(dependence);
        if (!depend)
            // TODO: errors handling
            continue;
        m_dependencies[depend]->setValue(dependence);
    }
}

DependenciesWidget::~DependenciesWidget()
{
    foreach(InterfaceInfo* interface, m_interfaces)
        delete interface;

    delete m_ui;
}
