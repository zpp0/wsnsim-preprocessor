/**
 *
 * File: errorAction.cpp
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "errorAction.h"

#include "errorsStorage.h"

ErrorAction::ErrorAction(QWidget* page, QWidget* author, QString text, QWidget* parent)
    : QAction(text, parent)
{
    m_author = author;
    m_page = page;
}

void ErrorAction::gotoError()
{
    ErrorsStorage::instance().gotoError(m_page, m_author);
}
