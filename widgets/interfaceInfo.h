/**
 *
 * File: interfaceinfo.h
 * Description: Dependencies widget with link to ModuleDescriptionRaw
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#ifndef INTERFACEINFO_H
#define INTERFACEINFO_H

#include <QCheckBox>
#include <QFrame>

#include "moduleParams.h"
#include "projectParams.h"

namespace Ui {
    class InterfaceInfo;
}

class InterfaceInfo : public QFrame
{
    Q_OBJECT

public:
    InterfaceInfo(ModuleDescriptionRaw* module, ModuleDependence* dependence);
    virtual ~InterfaceInfo();

    void setValue(quint16 moduleID);

public slots:
    void moduleEnabled(ModuleDescriptionRaw* module);
    void moduleDisabled(ModuleDescriptionRaw* module);

private slots:
    void setDependence(int moduleID);

private:

    void isValidDependence(ModuleDescriptionRaw* module);

    void addValidDependence(QString moduleName);

    ModuleDependence* m_dependence;
    ModuleDescriptionRaw* m_module;

    bool m_valueFromProject;

    QList<int> m_dependencies;
    QList<ModuleDescriptionRaw*> m_modules;

    Ui::InterfaceInfo* m_ui;
};

#endif // INTERFACEINFO_H
