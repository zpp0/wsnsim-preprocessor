/**
 *
 * File: modulesInfo.h
 * Description: Display module parameters widget
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#ifndef MODULESINFO_H
#define MODULESINFO_H

#include <QtGui>

#include "moduleParams.h"
#include "checkModule.h"

class ModulesInfo : public QTableWidget
{
    Q_OBJECT

public:
    ModulesInfo(QWidget* parent);
    virtual ~ModulesInfo();

    void addModuleInfo(ModuleDescriptionRaw* module);

    void enableModuleInfo(ModuleDescriptionRaw* module);
    void disableModuleInfo(ModuleDescriptionRaw* module);

    void disableAllModules();

private slots:
    void customContextMenuRequested(const QPoint &p);

private:
    QStringList m_moduleInfo;
    QMap<ModuleDescriptionRaw*, CheckModule*> m_modules;
    QMap<int, ModuleDescriptionRaw*> m_rows;

    QWidget* m_parent;
};

#endif // MODULESINFO_H
