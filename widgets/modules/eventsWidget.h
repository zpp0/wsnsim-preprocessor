/**
 *
 * File: eventsWidget.h
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef EVENTSWIDGET_H
#define EVENTSWIDGET_H


#include <QtGui>

#include "modulesParams.h"
#include "projectParams.h"

namespace Ui {
    class EventsWidget;
}

class EventsWidget : public QGroupBox
{
    Q_OBJECT

public:
    EventsWidget(ModuleDescriptionRaw* module);
    virtual ~EventsWidget();

    QList<EventParams> getEvents();
    void setEvents(QList<EventParams> events);

private:
    ModuleDescriptionRaw* m_module;

    QMap<QString, QCheckBox*> m_events;

    Ui::EventsWidget* m_ui;
};

#endif // EVENTSWIDGET_H
