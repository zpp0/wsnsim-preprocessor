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
#include "moduleParams.h"
#include "projectTree.h"

#include "projectStorage.h"

#include "paramsPage.h"

namespace Ui {
    class ModulesPage;
}

class ModulesPage : public QGroupBox
{
    Q_OBJECT

public:
    ModulesPage(QTreeWidgetItem* treeElement = 0, ProjectTree* projectTree = 0);
    virtual ~ModulesPage();


    void clean();
public slots:
    void registerModule(ModuleDescriptionRaw* module);
    void moduleScanError(QString file, QString error);

    void moduleEnabled(ModuleDescriptionRaw* module);
    void moduleDisabled(ModuleDescriptionRaw* module);

private:
    void createParamsPage(ModuleDescriptionRaw* module);
    void deleteParamsPage(ModuleDescriptionRaw* module);

    ModulesInfo* m_modulesInfo;
    QTableWidget* m_t_warnings;

    QList<ModuleDescriptionRaw*> m_modules;
    QList<ModuleDescriptionRaw*> m_enabledModules;

    QMap<ModuleDescriptionRaw*, ParamsPage*> m_params;

    QTreeWidgetItem* m_treeElement;
    ProjectTree* m_projectTree;

    QList<ModuleData*> m_modulesData;

    Ui::ModulesPage *m_ui;
};

#endif // MODULESPAGE_H
