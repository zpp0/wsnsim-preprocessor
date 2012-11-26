/**
 *
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 * File: modulePage.h
 *
 **/

#ifndef MODULEPAGE_H
#define MODULEPAGE_H 1

#include "paramsPage.h"
#include "dependenciesPage.h"

namespace Ui {
    class ModulePage;
}

class ModulePage : public QGroupBox
{
    Q_OBJECT
public:
    ModulePage();
    virtual ~ModulePage();

    QMap<ModuleParamRaw*, QVariant> getParams();
    QMap<QString, ModuleDescriptionRaw*> getDependencies();

public slots:
    void moduleEnabled(ModuleDescriptionRaw* module);
    void moduleDisabled(ModuleDescriptionRaw* module);

    void setModuleParam(ModuleParamRaw* param, QVariant value);
    void setModuleDependence(ModuleDependRaw* dependence, ModuleDescriptionRaw* depModule);

private:
    void createParamsPage(ModuleDescriptionRaw* module);
    void deleteParamsPage(ModuleDescriptionRaw* module);

    void createDependenciesPage(ModuleDescriptionRaw* module);
    void deleteDependenciesPage(ModuleDescriptionRaw* module);

    ParamsPage* m_param;
    DependenciesPage* m_dependencies;

    Ui::ModulePage *m_ui;
};

#endif // MODULEPAGE_H
