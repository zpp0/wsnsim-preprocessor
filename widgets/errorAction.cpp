/**
 *
 * File: errorAction.cpp
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "errorAction.h"

ErrorAction::ErrorAction(QWidget* author, QString text, QWidget* parent)
    : QAction(text, parent)
{
    m_author = author;
}

void ErrorAction::gotoError()
{
    m_author->setFocus(Qt::OtherFocusReason);
}
