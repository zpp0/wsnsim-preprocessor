/**
 *
 * File: errorsPanel.cpp
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include <QMenu>

#include "errorsPanel.h"
#include "ui_errorsPanel.h"

ErrorsPanel::ErrorsPanel(QWidget* parent)
    :QFrame(parent), m_ui(new Ui::ErrorsPanel)
{
    m_ui->setupUi(this);

    m_ui->b_menu->setIcon(QIcon(":/icons/attention"));

    connect(m_ui->b_menu, SIGNAL(clicked()),
            this, SLOT(showMenu()));

    m_ui->b_ok->setVisible(false);
    m_ui->b_menu->setVisible(false);
}

void ErrorsPanel::errorAdded(QWidget* page, QWidget* widget, QString message)
{
    m_actions += new ErrorAction(page, widget, message, this);
    m_widgets += widget;
    m_pages[widget] = page;
    setErrorsCount();
}

void ErrorsPanel::errorRemoved(QWidget* page, QWidget* widget)
{
    int index = m_widgets.indexOf(widget);
    if (index != -1) {
        m_actions.removeAt(index);
        m_widgets.removeAt(index);
        m_pages.remove(widget);

        setErrorsCount();
    }
}

void ErrorsPanel::hasErrors(bool yes)
{
    if (yes) {
        m_ui->b_ok->setVisible(false);
        m_ui->b_menu->setVisible(true);
    }
    else {
        m_ui->b_ok->setVisible(true);
        m_ui->b_menu->setVisible(false);
    }
}

void ErrorsPanel::setErrorsCount()
{
    int errors = m_actions.size();
    m_ui->b_menu->setText(QString::number(errors) + " " + tr("error(s)"));
}

void ErrorsPanel::showMenu()
{
    QList<QAction*> actions;
    foreach(ErrorAction* action, m_actions)
        actions += action;

    QAction* action = QMenu::exec(actions, mapToGlobal(m_ui->b_menu->pos()));
    if (action)
        ((ErrorAction*)action)->gotoError();
}

ErrorsPanel::~ErrorsPanel()
{
    foreach(ErrorAction* action, m_actions)
        delete action;
    delete m_ui;
}
