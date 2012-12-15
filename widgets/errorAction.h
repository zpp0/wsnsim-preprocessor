/**
 *
 * File: errorAction.h
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef ERRORACTION_H
#define ERRORACTION_H

#include <QAction>
#include <QString>

class ErrorAction : public QAction
{
    Q_OBJECT
public:
    ErrorAction(QWidget* page, QWidget* author, QString text, QWidget* parent = 0);
    virtual ~ErrorAction() {}

    void gotoError();

private:
    QWidget* m_page;
    QWidget* m_author;
};

#endif // ERRORACTION_H
