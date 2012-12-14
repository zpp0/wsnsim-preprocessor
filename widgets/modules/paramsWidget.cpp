/**
 * File: paramsWidget.cpp
 * Description: Module params widget
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "paramsWidget.h"
#include "ui_paramsWidget.h"

#include "doubleParam.h"
#include "intParam.h"
#include "uintParam.h"
#include "stringParam.h"
#include "boolParam.h"
#include "timeParam.h"
#include "fileParam.h"
#include "nodesParam.h"
#include "tableParam.h"

#include "projectStorage.h"

ParamsWidget::ParamsWidget(ModuleDescriptionRaw* module)
    : m_ui(new Ui::ParamsWidget)
{
    m_ui->setupUi(this);

    m_selfModule = module;

    for (int i = 0; i < m_selfModule->params.size(); i++)
        createParam(&(m_selfModule->params[i]));
}

void ParamsWidget::createParam(ModuleParamRaw* paramRaw)
{
    ModuleParamGeneral* param = NULL;

    if (paramRaw->type == "double")
        param = (ModuleParamGeneral*)new ModuleParamDouble(m_selfModule, paramRaw);
    if (paramRaw->type == "int")
        param = (ModuleParamGeneral*)new ModuleParamInt(m_selfModule, paramRaw);
    if (paramRaw->type == "uint")
        param = (ModuleParamGeneral*)new ModuleParamUint(m_selfModule, paramRaw);
    if (paramRaw->type == "string")
        param = (ModuleParamGeneral*)new ModuleParamString(m_selfModule, paramRaw);
    if (paramRaw->type == "file")
        param = (ModuleParamGeneral*)new ModuleParamFile(m_selfModule, paramRaw);
    if (paramRaw->type == "time")
        param = (ModuleParamGeneral*)new ModuleParamTime(m_selfModule, paramRaw);
    if (paramRaw->type == "nodes")
        param = (ModuleParamGeneral*)new ModuleParamNodes(m_selfModule, paramRaw);
    if (paramRaw->type == "bool")
        param = (ModuleParamGeneral*)new ModuleParamBool(m_selfModule, paramRaw);
    if (paramRaw->type == "table")
        param = (ModuleParamGeneral*)new ModuleParamTable(m_selfModule, paramRaw);

    if (param != NULL) {
        m_params[paramRaw] = param;
        m_ui->paramsList->addWidget(param);
    }
}

ModuleParamRaw* ParamsWidget::getParamRaw(ModuleParam param)
{
    ModuleParamRaw* paramRaw = NULL;
    foreach(ModuleParamRaw* raw, m_params.keys()) {
        if (raw->name == param.name) {
            paramRaw = raw;
            break;
        }
    }

    return paramRaw;
}

QList<ModuleParam> ParamsWidget::getParams()
{
    QList<ModuleParam> params;

    foreach(ModuleParamGeneral* param, m_params.values())
        params += param->getParam();

    return params;
}

void ParamsWidget::setParams(QList<ModuleParam> params)
{
    foreach(ModuleParam param, params) {
        ModuleParamRaw* paramRaw = getParamRaw(param);
        if (!paramRaw)
            // TODO: errors handling
            continue;

        m_params[paramRaw]->setParam(param);
    }
}

ParamsWidget::~ParamsWidget()
{
    delete m_ui;
}
