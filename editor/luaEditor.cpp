/**
 *
 * File: luaEditor.cpp
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include <QDesktopServices>
#include <QUrl>
#include <QSettings>
#include <QFile>
#include <QTextStream>

#include "luaEditor.h"
#include "ui_luaEditor.h"

LuaEditor::LuaEditor(QString fileName, QWidget *parent)
    : QDialog(parent), m_ui(new Ui::LuaEditor)
{
    m_ui->setupUi(this);

    b_save = new QPushButton(tr("&Save"));
    b_saveAndExit = new QPushButton(tr("&Save and Exit"));
    b_exit = new QPushButton(tr("&Exit without saving"));

    m_ui->buttonBox->addButton(b_save, QDialogButtonBox::ApplyRole);
    m_ui->buttonBox->addButton(b_saveAndExit, QDialogButtonBox::AcceptRole);
    m_ui->buttonBox->addButton(b_exit, QDialogButtonBox::RejectRole);

    connect(m_ui->buttonBox, SIGNAL(clicked(QAbstractButton*)),
            this, SLOT(buttonClicked(QAbstractButton*)));

    m_filePath = LuaEditor::getModuleFilePath(fileName);

    m_ui->l_file->setText(fileName + " (" + m_filePath + ")");

    m_editor = new CodeEditor(this);
    m_ui->layout->addWidget(m_editor);

    m_luaHighlighter = new LuaHighlighter(m_editor->document());

    QFile file(m_filePath);
    if (file.open(QFile::ReadOnly | QFile::Text))
        m_editor->setPlainText(file.readAll());
    file.close();
}

LuaEditor::~LuaEditor()
{
    delete m_ui;
}

void LuaEditor::openExternal(QString fileName)
{
    QString filePath = LuaEditor::getModuleFilePath(fileName);
    // FIXME: get it works on Windows
    QDesktopServices::openUrl(QUrl(filePath));
}

QString LuaEditor::getModuleFilePath(QString fileName)
{
    QString modulesDir = QSettings("wsnsim", "simulator").value("Modules/Directory").toString();
    return modulesDir + "/" + fileName;
}

void LuaEditor::saveFile()
{
    QString text = m_editor->toPlainText();
    QFile file(m_filePath);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        out << text;
    }

    file.close();
}

void LuaEditor::buttonClicked(QAbstractButton *button)
{
    if(m_ui->buttonBox->buttonRole(button) == QDialogButtonBox::ApplyRole)
        saveFile();

    else if(m_ui->buttonBox->buttonRole(button) == QDialogButtonBox::AcceptRole) {
        saveFile();
        done(QDialog::Accepted);
    }

    else if(m_ui->buttonBox->buttonRole(button) == QDialogButtonBox::RejectRole)
        done(QDialog::Rejected);
}
