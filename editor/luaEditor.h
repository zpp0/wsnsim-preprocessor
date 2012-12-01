/**
 *
 * File: luaEditor.h
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef LUAEDITOR_H
#define LUAEDITOR_H

#include <QDialog>
#include <QPushButton>

#include "luaHighlighter.h"

#include "codeEditor.h"

namespace Ui {
    class LuaEditor;
}

class LuaEditor : public QDialog
{
    Q_OBJECT
public:
    LuaEditor(QString fileName, QWidget *parent = 0);
    virtual ~LuaEditor();

    static void openExternal(QString fileName);

private slots:
    void buttonClicked(QAbstractButton *button);

private:
    static QString getModuleFilePath(QString fileName);

    void saveFile();

    QString m_filePath;
    CodeEditor* m_editor;
    LuaHighlighter* m_luaHighlighter;

    QPushButton* b_save;
    QPushButton* b_saveAndExit;
    QPushButton* b_exit;

    Ui::LuaEditor* m_ui;
};

#endif // LUAEDITOR_H
