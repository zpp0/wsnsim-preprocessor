/**
 *
 * File: fileParam.cpp
 * Description: module param with file type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include <QFileDialog>

#include "fileParam.h"
#include "ui_fileParam.h"

ModuleParamFile::ModuleParamFile(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw)
    :ModuleParamGeneral(module, paramRaw), m_ui(new Ui::FileParam)
{
    m_ui->setupUi(this);

    m_ui->l_info->setText(m_param->info);

    connect(m_ui->b_file, SIGNAL(clicked()),
            this, SLOT(browseFile()));
}

void ModuleParamFile::browseFile()
{
    QString text = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                // TODO: add filters from params
                                                "", "");
    if (text != "")
        m_ui->lineEdit->setText(text);
}

void ModuleParamFile::setParam(ModuleParam param)
{
    QString value = param.value.toString();
    m_ui->lineEdit->setText(value);
}

ModuleParam ModuleParamFile::getParam()
{
    ModuleParam param;
    param.name = m_param->name;
    param.type = m_param->type;
    param.value = m_ui->lineEdit->text();

    return param;
}

ModuleParamFile::~ModuleParamFile()
{
    delete m_ui;
}
