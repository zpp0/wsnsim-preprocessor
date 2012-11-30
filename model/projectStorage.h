/**
 *
 * File: projectStorage.h
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#ifndef PROJECTSTORAGE_H
#define PROJECTSTORAGE_H

#include <QString>

#include "projectParams.h"

class ProjectStorage : public QObject
{
    Q_OBJECT
public:
    static ProjectStorage& instance() {
        static ProjectStorage instance;
        return instance;
    }

    void saveXML(QString file);
    ProjectParams& loadXML(QString file);

    ProjectParams& getProject();

signals:

    void libLoadingError(QString errorString);

    void savingProjectError(QString errorString);
    void loadingProjectError(QString errorString);

private:
    ProjectStorage();
    ProjectStorage(ProjectStorage const&);
    void operator=(ProjectStorage const&);

    bool loaded;

    typedef void(*projectDataSave) (QString& projectFileName, QString* errorMessage, ProjectParams params);
    typedef ProjectParams(*projectDataLoad) (QString& projectFileName, QString* errorMessage);

    projectDataSave m_saveFun;
    projectDataLoad m_loadFun;

    ProjectParams m_project;
};

#endif // PROJECTSTORAGE_H
