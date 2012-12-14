/**
 *
 * File: renamingNodeTypeDialog.h
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef RENAMINGNODETYPEDIALOG_H
#define RENAMINGNODETYPEDIALOG_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
    class RenamingNodeTypeDialog;
}

class RenamingNodeTypeDialog : public QDialog
{
    Q_OBJECT
public:
    RenamingNodeTypeDialog(QString nodeType, QList<QString> existingNames, QWidget* parent = 0);
    virtual ~RenamingNodeTypeDialog();

    QString getNewName();

private slots:
    void buttonClicked(QAbstractButton *button);
    void isNewNodeTypeName(QString name);

private:
    QString m_name;
    QList<QString> m_existingNames;
    Ui::RenamingNodeTypeDialog* m_ui;
};

#endif // RENAMINGNODETYPEDIALOG_H
