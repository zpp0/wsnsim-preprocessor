/**
 *
 * File: paramsWidget.h
 * Description: Module params widget
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef PARAMSWIDGET_H
#define PARAMSWIDGET_H

#include <QMap>
#include <QString>
#include <QLineEdit>

#include "modulesParams.h"
#include "projectParams.h"

#include "generalParam.h"

namespace Ui {
    class ParamsWidget;
}

class ParamsWidget : public QGroupBox
{
    Q_OBJECT

public:
    ParamsWidget(ModuleDescriptionRaw* module);
    virtual ~ParamsWidget();

    QList<ModuleParam> getParams();
    void setParams(QList<ModuleParam> params);

private:
    ModuleParamRaw* getParamRaw(ModuleParam param);
    void createParam(ModuleParamRaw* paramRaw);

    ModuleDescriptionRaw* m_selfModule;

    QMap<ModuleParamRaw*, ModuleParamGeneral*> m_params;

    Ui::ParamsWidget *m_ui;
};

#endif // PARAMSWIDGET_H
