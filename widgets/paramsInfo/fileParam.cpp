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

ModuleParamFile::ModuleParamFile(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw, ModuleParam* param)
    :ModuleParamGeneral(module, paramRaw, param), m_ui(new Ui::FileParam)
{
    m_ui->setupUi(this);

    m_ui->l_info->setText(paramRaw->info);

    if (!m_param->value.isNull())
        setParamValue(m_param->value);

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

void ModuleParamFile::setParamValue(QVariant value)
{
    QString param = value.toString();
    m_ui->lineEdit->setText(param);
}

void ModuleParamFile::setParamValue(QString value)
{
    m_param->value = value;
}
