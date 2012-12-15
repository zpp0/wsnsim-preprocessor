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

    void setPossibleError(QWidget* page, QWidget* widget, bool error, QString message = "");

    void addError(QWidget* page, QWidget* widget, QString message);
    void removeError(QWidget* page, QWidget* widget);

    bool hasError(QWidget* page, QWidget* widget);

    void gotoError(QWidget* page, QWidget* widget);

signals:
    void errorAdded(QWidget* page, QWidget* widget, QString message);
    void errorRemoved(QWidget* page, QWidget* widget);
    void hasErrors(bool yes);

    void errorSelected(QWidget* page, QWidget* widget);

private:
    ErrorsStorage() {}
    ErrorsStorage(ErrorsStorage const&);
    void operator=(ErrorsStorage const&);

    QMap<QWidget*, QMap<QWidget*, QString> > m_errors;
};

#endif // ERRORSSTORAGE_H
