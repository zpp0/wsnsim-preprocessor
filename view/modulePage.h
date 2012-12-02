/**
 *
 * File: modulePage.h
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef MODULEPAGE_H
#define MODULEPAGE_H

#include "projectParams.h"
#include "moduleParams.h"

#include "infoWidget.h"
#include "paramsWidget.h"
#include "dependenciesWidget.h"

namespace Ui {
    class ModulePage;
}

class ModulePage : public QGroupBox
{
    Q_OBJECT
public:
    ModulePage(ModuleDescriptionRaw* module);
    virtual ~ModulePage();

    ModuleData getModule();
    void setModule(ModuleData module);

    QList<EventParams> getEvents();
    void setEvents(QList<EventParams>);

private:
    ModuleDescriptionRaw* m_module;

    InfoWidget* m_info;
    ParamsWidget* m_param;
    DependenciesWidget* m_dependencies;

    Ui::ModulePage *m_ui;
};

#endif // MODULEPAGE_H
