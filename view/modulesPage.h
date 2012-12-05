/**
 *
 * File: modulesPage.h
 * Description: Page of choosing modules from list
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#ifndef MODULESPAGE_H
#define MODULESPAGE_H

#include <QtGui>

#include "modulesInfo.h"
#include "projectTree.h"

#include "modulePage.h"

#include "modulesParams.h"
#include "projectParams.h"

#include "projectStorage.h"

namespace Ui {
    class ModulesPage;
}

class ModulesPage : public QGroupBox
{
    Q_OBJECT

public:
    ModulesPage(QTreeWidgetItem* treeElement = 0, ProjectTree* projectTree = 0);
    virtual ~ModulesPage();

    QList<ModuleData> getModules();
    void setModules(QList<ModuleData> modules);
    void activateModules(QList<ModuleData> modules);

    QList<EventParams> getEvents();
    void setEvents(QList<EventParams> events);

    void clear();
    void clean();

public slots:
    void registerModule(ModuleDescriptionRaw* module);
    void moduleScanError(QString file, QString error);

    void moduleEnabled(ModuleDescriptionRaw* module);
    void moduleDisabled(ModuleDescriptionRaw* module);

private:
    void createModulePage(ModuleDescriptionRaw* module);
    void deleteModulePage(ModuleDescriptionRaw* module);

    void setModulesError(bool error);

    ModuleDescriptionRaw* getModuleRaw(ModuleData moduleData);

    ModulesInfo* m_modulesInfo;
    QTableWidget* m_t_warnings;

    QMap<ModuleDescriptionRaw*, ModulePage*> m_modules;

    QTreeWidgetItem* m_selfTreeElement;

    ProjectTree* m_projectTree;

    Ui::ModulesPage *m_ui;
};

#endif // MODULESPAGE_H
