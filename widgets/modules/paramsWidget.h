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
    ParamsPage(ModuleDescriptionRaw* module, ModuleData* moduleData, bool withParams);
    virtual ~ParamsPage();

    void createParam(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw, ModuleParam* param);

private:


    ModuleDescriptionRaw* m_module;
    ModuleData* m_moduleData;

    QList<ModuleParamGeneral*> m_params;

    Ui::ParamsPage *m_ui;
};

#endif // PARAMSPAGE_H
