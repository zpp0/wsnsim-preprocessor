/**
 *
 * File: errorsStorage.h
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef ERRORSSTORAGE_H
#define ERRORSSTORAGE_H

#include <QWidget>
#include <QWidget>
#include <QMap>

class ErrorsStorage : public QWidget
{
    Q_OBJECT
public:
    static ErrorsStorage& instance() {
        static ErrorsStorage instance;
        return instance;
    }

    void setPossibleError(QWidget* widget, bool error, QString message = "");

    void addError(QWidget* widget, QString message);
    void removeError(QWidget* widget);

    bool hasError(QWidget* widget);

signals:
    void errorAdded(QWidget* widget, QString message);
    void errorRemoved(QWidget* widget);
    void hasErrors(bool yes);

private:
    ErrorsStorage() {}
    ErrorsStorage(ErrorsStorage const&);
    void operator=(ErrorsStorage const&);

    QMap<QWidget*, QString> m_errors;
    QMap<QWidget*, QString> m_warnings;
};

#endif // ERRORSSTORAGE_H
