/**
 *
 * File: luaEditor.h
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef LUAEDITOR_H
#define LUAEDITOR_H

#include <QDialog>

#include "luaHighlighter.h"

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

private:
    static QString getModuleFilePath(QString fileName);

    QString m_fileName;
    QPlainTextEdit* m_editor;
    LuaHighlighter* m_luaHighlighter;

    Ui::LuaEditor* m_ui;
};

#endif // LUAEDITOR_H
