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

#include "luaEditor.h"
#include "ui_luaEditor.h"

LuaEditor::LuaEditor(QString fileName, QWidget *parent)
    : QDialog(parent), m_ui(new Ui::LuaEditor)
{
    m_ui->setupUi(this);

    m_fileName = fileName;
    m_ui->l_file->setText(m_fileName);

    m_editor = new QPlainTextEdit(this);
    m_ui->layout->addWidget(m_editor);

    m_luaHighlighter = new LuaHighlighter(m_editor->document());

    QString filePath = LuaEditor::getModuleFilePath(fileName);

    QFile file(filePath);
    if (file.open(QFile::ReadOnly | QFile::Text))
        m_editor->setPlainText(file.readAll());
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
