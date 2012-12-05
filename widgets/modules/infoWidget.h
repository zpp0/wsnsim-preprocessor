/**
 *
 * File: infoWidget.h
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QFrame>

#include "modulesParams.h"

namespace Ui {
    class InfoWidget;
}

class InfoWidget : public QFrame
{
    Q_OBJECT
public:
    InfoWidget(ModuleDescriptionRaw* module);
    virtual ~InfoWidget();

private:
    ModuleDescriptionRaw* m_module;

    Ui::InfoWidget* m_ui;
};

#endif // INFOWIDGET_H
