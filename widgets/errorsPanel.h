/**
 *
 * File: errorsPanel.h
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef ERRORSPANEL_H
#define ERRORSPANEL_H

#include <QFrame>
#include <QString>

#include "errorAction.h"

namespace Ui {
    class ErrorsPanel;
}

class ErrorsPanel : public QFrame
{
    Q_OBJECT
public:
    ErrorsPanel(QWidget* parent = 0);
    virtual ~ErrorsPanel();

public slots:
    void errorAdded(QWidget* page, QWidget* widget, QString message);
    void errorRemoved(QWidget* page, QWidget* widget);

    void hasErrors(bool yes);

private slots:
    void showMenu();

private:
    void setErrorsCount();

    QList<ErrorAction*> m_actions;
    QList<QWidget*> m_widgets;
    QMap<QWidget*, QWidget*> m_pages;

    Ui::ErrorsPanel* m_ui;
};

#endif // ERRORSPANEL_H
