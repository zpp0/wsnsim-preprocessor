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

ModuleParamFile::ModuleParamFile(ModuleParamRaw* paramRaw, ModuleParam* param)
    :m_ui(new Ui::FileParam), ModuleParamGeneral(paramRaw, param)
{
    m_ui->setupUi(this);

    m_ui->l_info->setText(paramRaw->info);

    connect(m_ui->b_file, SIGNAL(clicked()),
            this, SLOT(browseFile()));

    connect(m_ui->lineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(setParamValue(QString)));
}

ModuleParamFile::~ModuleParamFile()
{
    delete m_ui;
}

void ModuleParamFile::browseFile()
{
    QString text = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                // TODO: add filters from params
                                                "", "");
    if (text != "")
        m_ui->lineEdit->setText(text);
}

void ModuleParamFile::setParamValue(QString value)
{
    m_param->value = value;
}
