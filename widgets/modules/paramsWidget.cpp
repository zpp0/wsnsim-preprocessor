/**
 * File: paramsPage.cpp
 * Description: Module params widget
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "paramsPage.h"
#include "ui_paramsPage.h"

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

ParamsPage::ParamsPage(ModuleDescriptionRaw* module, ModuleData* moduleData, bool withParams)
    : m_ui(new Ui::ParamsPage)
{
    m_ui->setupUi(this);

    m_module = module;
    m_moduleData = moduleData;

    setTitle(m_module->name);
    m_ui->l_description->setText(m_module->description);

    m_ui->paramsList->setDirection(QBoxLayout::BottomToTop);

    if (withParams == true) {
        ProjectStorage& storage = ProjectStorage::instance();

        foreach(ModuleParamRaw paramRaw, module->params) {
            ModuleParam* param = storage.addModuleParam(moduleData);
            param->name = paramRaw.name;
            param->type = paramRaw.type;
            createParam(module, &paramRaw, param);
        }
    }
}

void ParamsPage::createParam(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw, ModuleParam* moduleParam)
{
    ModuleParamGeneral* param = NULL;

    if (paramRaw->type == "double")
        param = (ModuleParamGeneral*)new ModuleParamDouble(module, paramRaw, moduleParam);
    if (paramRaw->type == "int")
        param = (ModuleParamGeneral*)new ModuleParamInt(module, paramRaw, moduleParam);
    if (paramRaw->type == "uint")
        param = (ModuleParamGeneral*)new ModuleParamUint(module, paramRaw, moduleParam);
    if (paramRaw->type == "string")
        param = (ModuleParamGeneral*)new ModuleParamString(module, paramRaw, moduleParam);
    if (paramRaw->type == "file")
        param = (ModuleParamGeneral*)new ModuleParamFile(module, paramRaw, moduleParam);
    if (paramRaw->type == "time")
        param = (ModuleParamGeneral*)new ModuleParamTime(module, paramRaw, moduleParam);
    if (paramRaw->type == "nodes")
        param = (ModuleParamGeneral*)new ModuleParamNodes(module, paramRaw, moduleParam);
    if (paramRaw->type == "bool")
        param = (ModuleParamGeneral*)new ModuleParamBool(module, paramRaw, moduleParam);
    if (paramRaw->type == "table")
        param = (ModuleParamGeneral*)new ModuleParamTable(module, paramRaw, moduleParam);

    if (param != NULL) {
        m_params += param;
        m_ui->paramsList->insertWidget(1, param);
    }
}

ParamsPage::~ParamsPage()
{
    delete m_ui;
}
