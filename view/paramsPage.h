/**
 *
 * File: paramsPage.h
 * Description: Module params widget
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef PARAMSPAGE_H
#define PARAMSPAGE_H

#include <QMap>
#include <QString>
#include <QLineEdit>

#include "moduleParams.h"
#include "projectParams.h"

#include "generalParam.h"

namespace Ui {
    class ParamsPage;
}

class ParamsPage : public QGroupBox
{
    Q_OBJECT

public:
    ParamsPage(ModuleDescriptionRaw* module, ModuleData* moduleData);
    virtual ~ParamsPage();

private:
    bool createParam(ModuleParamRaw* paramRaw, ModuleParam* param);

    ModuleDescriptionRaw* m_module;
    ModuleData* m_moduleData;

    QList<ModuleParamGeneral*> m_params;

    Ui::ParamsPage *m_ui;
};

#endif // PARAMSPAGE_H