/**
 *
 * File: checkModule.h
 * Description: QCheckBox Widget with link to ModuleDescriptionRaw
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#ifndef CHECKMODULE_H
#define CHECKMODULE_H

#include <QCheckBox>
#include "modulesParams.h"

class CheckModule : public QCheckBox
{
    Q_OBJECT

public:
    CheckModule(ModuleDescriptionRaw* module);
    virtual ~CheckModule() {}

signals:
    void moduleEnabled(ModuleDescriptionRaw* module);
    void moduleDisabled(ModuleDescriptionRaw* module);

public slots:
    void enabled(bool enable);

private:
    ModuleDescriptionRaw* m_module;
};

#endif // CHECKMODULE_H
