/**
 *
 * File: renamingNodeTypeDialog.cpp
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include <QPushButton>

#include "renamingNodeTypeDialog.h"
#include "ui_renamingNodeTypeDialog.h"

RenamingNodeTypeDialog::RenamingNodeTypeDialog(QString nodeType,
                                               QList<QString> existingNames,
                                               QWidget* parent)
    : QDialog(parent), m_ui(new Ui::RenamingNodeTypeDialog)
{
    m_ui->setupUi(this);

    m_name = nodeType;
    m_existingNames = existingNames;

    m_ui->l_name->setText(m_name);

    m_ui->lineEdit->setText(m_name);
    m_ui->lineEdit->selectAll();

    m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    connect(m_ui->lineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(isNewNodeTypeName(QString)));

    connect(m_ui->buttonBox, SIGNAL(clicked(QAbstractButton*)),
            this, SLOT(buttonClicked(QAbstractButton*)));
}

RenamingNodeTypeDialog::~RenamingNodeTypeDialog()
{
    delete m_ui;
}

void RenamingNodeTypeDialog::isNewNodeTypeName(QString name)
{
    if (name == "")
        m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    else if (m_existingNames.contains(name))
        m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    else if ((!m_existingNames.contains(name))
             && (!m_ui->buttonBox->button(QDialogButtonBox::Ok)->isEnabled()))
        m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
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
