/**
 *
 * File: projectStorage.h
 * Description: projects storage
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#ifndef PROJECTSSTORAGE_H
#define PROJECTSSTORAGE_H

#include <QString>
#include <QList>

#include "projectParams.h"
#include "moduleParams.h"

class ProjectStorage : public QObject
{
    Q_OBJECT
public:
    void saveXML(ProjectParams project, QString file);

signals:

    void savingFileError(QString errorString);
};

#endif // PROJECTSSTORAGE_H
