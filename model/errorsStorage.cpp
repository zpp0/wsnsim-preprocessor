/**
 *
 * File: errorsStorage.cpp
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "errorsStorage.h"

void ErrorsStorage::setPossibleError(QWidget* widget, bool error, QString message)
{
    if (error && !hasError(widget))
        addError(widget, message);
    else if (!error && hasError(widget))
        removeError(widget);
}

void ErrorsStorage::addError(QWidget* widget, QString message)
{
    m_errors[widget] = message;
    if (m_errors.size() == 1)
        emit hasErrors(true);

    emit errorAdded(widget, message);
}

void ErrorsStorage::removeError(QWidget* widget)
{
    m_errors.remove(widget);
    if (m_errors.isEmpty())
        emit hasErrors(false);

    emit errorRemoved(widget);
}

bool ErrorsStorage::hasError(QWidget* widget)
{
    return m_errors.contains(widget);
}
