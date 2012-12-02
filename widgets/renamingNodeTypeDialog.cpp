/**
 *
 * File: renamingNodeTypeDialog.cpp
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "renamingNodeTypeDialog.h"
#include "ui_renamingNodeTypeDialog.h"

RenamingNodeTypeDialog::RenamingNodeTypeDialog(QString nodeType, QWidget* parent)
    : QDialog(parent), m_ui(new Ui::RenamingNodeTypeDialog)
{
    m_ui->setupUi(this);

    m_name = nodeType;

    m_ui->l_name->setText(m_name);

    m_ui->lineEdit->setText(m_name);
    m_ui->lineEdit->selectAll();

    connect(m_ui->buttonBox, SIGNAL(clicked(QAbstractButton*)),
            this, SLOT(buttonClicked(QAbstractButton*)));
}

RenamingNodeTypeDialog::~RenamingNodeTypeDialog()
{
    delete m_ui;
}

QString RenamingNodeTypeDialog::getNewName()
{
    return m_ui->lineEdit->text();
}

void RenamingNodeTypeDialog::buttonClicked(QAbstractButton *button)
{
    if(m_ui->buttonBox->buttonRole(button) == QDialogButtonBox::AcceptRole)
        done(QDialog::Accepted);

    else if(m_ui->buttonBox->buttonRole(button) == QDialogButtonBox::RejectRole)
        done(QDialog::Rejected);
}
