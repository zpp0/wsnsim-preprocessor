/**
 *
 * File: errorsStorage.cpp
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "errorsStorage.h"

void ErrorsStorage::setPossibleError(QWidget* page, QWidget* widget, bool error, QString message)
{
    if (error && !hasError(page, widget))
        addError(page, widget, message);
    else if (!error && hasError(page, widget))
        removeError(page, widget);
}

void ErrorsStorage::addError(QWidget* page, QWidget* widget, QString message)
{
    m_errors[page][widget] = message;
    if (m_errors.size() == 1)
        emit hasErrors(true);

    emit errorAdded(page, widget, message);
}

void ErrorsStorage::removeError(QWidget* page, QWidget* widget)
{
    m_errors[page].remove(widget);
    if (m_errors[page].isEmpty())
        m_errors.remove(page);

    if (m_errors.isEmpty())
        emit hasErrors(false);

    emit errorRemoved(page, widget);
}

bool ErrorsStorage::hasError(QWidget* page, QWidget* widget)
{
    return m_errors[page].contains(widget);
}

void ErrorsStorage::gotoError(QWidget* page, QWidget* widget)
{
    emit errorSelected(page, widget);
}
