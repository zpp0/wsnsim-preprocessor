/**
 *
 * File: modulesInfoDialog.h
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef MODULESINFODIALOG_H
#define MODULESINFODIALOG_H

#include <QDialog>

#include "moduleParams.h"

namespace Ui {
    class ModulesInfoDialog;
}

class ModulesInfoDialog : public QDialog
{
    Q_OBJECT
public:
    ModulesInfoDialog(QWidget* parent = 0);
    virtual ~ModulesInfoDialog();

    void addModule(ModuleDescriptionRaw* module);

private:
    Ui::ModulesInfoDialog* m_ui;
};

#endif // MODULESINFODIALOG_H
