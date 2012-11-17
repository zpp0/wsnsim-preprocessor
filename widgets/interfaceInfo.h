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

public slots:
    void moduleEnabled(ModuleDescriptionRaw* module);
    void moduleDisabled(ModuleDescriptionRaw* module);

private slots:
    void setDependence(int moduleID);

private:

    void isValidDependence(ModuleDescriptionRaw* module);

    // TODO: implement this
    // void removeDependence(QString moduleName, quint16 moduleID);
    void addValidDependence(QString moduleName, quint16 moduleID);

    QList<ModuleDescriptionRaw*> m_possibleDependencies;

    ModuleDependence* m_dependence;
    ModuleDescriptionRaw* m_module;

    QMap<int, int> m_dependencies;

    Ui::InterfaceInfo* m_ui;
};

#endif // INTERFACEINFO_H
