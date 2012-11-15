/**
 *
 * File: moduleStorage.h
 * Description: modules storage
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#ifndef MODULESSTORAGE_H
#define MODULESSTORAGE_H

#include <QObject>
#include <QString>
#include <QList>

#include "moduleParams.h"

class ModulesStorage : public QObject
{
    Q_OBJECT
public:
    static ModulesStorage& instance() {
        static ModulesStorage instance;
        return instance;
    }

signals:
    void registerModule(ModuleDescriptionRaw* module);
    
public slots:
    void moduleScanSuccess(QString file, ModuleDescriptionRaw module);
    
private:
    ModulesStorage() {}
    ModulesStorage(ModulesStorage const&);
    void operator=(ModulesStorage const&);

    QList<ModuleDescriptionRaw> m_modules;
};

#endif // MODULESSTORAGE_H
