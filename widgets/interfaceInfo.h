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

#include "projectParams.h"
#include "moduleParams.h"

namespace Ui {
    class InterfaceInfo;
}

class InterfaceInfo : public QFrame
{
    Q_OBJECT

public:
    InterfaceInfo(ModuleDescriptionRaw* module, ModuleDependRaw* dependence);
    virtual ~InterfaceInfo();

    void setValue(ModuleDependence dependence);
    ModuleDependence getValue();

public slots:
    void moduleEnabled(ModuleDescriptionRaw* module, bool enabled);

private:

    void isValidDependence(ModuleDescriptionRaw* module);

    void addValidDependence(QString moduleName);

    void setError(bool error);

    ModuleDescriptionRaw* m_module;
    ModuleDependRaw* m_dependence;

    QList<ModuleDescriptionRaw*> m_modules;

    Ui::InterfaceInfo* m_ui;
};

#endif // INTERFACEINFO_H
