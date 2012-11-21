/**
 *
 * File: projectScanner.h
 * Description: API for scan projects files
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef PROJECTSCANNER_H
#define PROJECTSCANNER_H

#include <QString>
#include <QStringList>
#include <QObject>

#include "moduleParams.h"
#include "projectParams.h"

class ProjectScanner : public QObject
{
    Q_OBJECT
public:
    ProjectScanner(QObject* parent = 0);
    void scanFile(QString& file);

signals:
    void setVersion(QString version);
    void setUuid(QString uuid);

    void setLogFileName(QString fileName);
    void setMaxTime(int time);
    void setTimeUnits(int units);

    void setAuthor(QString author);
    void setComment(QString comment);
    void setKeywords(QString keyword);
    void setTitle(QString title);

    void addModule(ModuleData module);
    void addNodeType(NodeTypeData module);

private:
    ProjectParams m_project;
};

#endif // PROJECTSCANNER_H
