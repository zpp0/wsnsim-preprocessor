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

class ModulesInfo : public QTableWidget
{
    Q_OBJECT

public:
    ModulesInfo(QObject* parent = 0);
    virtual ~ModulesInfo();

    void addModuleInfo(ModuleDescriptionRaw* module);

private:
    QStringList m_moduleInfo;
    QObject* m_parent;
};

#endif // MODULESINFO_H
