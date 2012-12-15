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

#include "modulesParams.h"

class ModulesStorage : public QObject
{
    Q_OBJECT
public:
    static ModulesStorage& instance() {
        static ModulesStorage instance;
        return instance;
    }

    void enableModule(ModuleDescriptionRaw* module, bool enable);

    ModuleDescriptionRaw* getModule(QString fileName);

    ModuleDescriptionRaw* getModule(quint16 moduleID);
    quint16 getModule(ModuleDescriptionRaw* module);

    QList<ModuleDescriptionRaw*> getEnabled();

    QString getModuleFilePath(QString fileName);

    void clean();

signals:
    void registerModule(ModuleDescriptionRaw* module);

    void moduleEnabled(ModuleDescriptionRaw* module, bool enabled);

public slots:
    void moduleScanSuccess(QString file, ModuleDescriptionRaw module);

private:
    ModulesStorage() {}
    ModulesStorage(ModulesStorage const&);
    void operator=(ModulesStorage const&);

    QList<ModuleDescriptionRaw*> m_enabled;
    QList<ModuleDescriptionRaw> m_modules;
};

#endif // MODULESSTORAGE_H
