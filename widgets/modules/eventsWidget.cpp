/**
 *
 * File: eventsWidget.cpp
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "eventsWidget.h"
#include "ui_eventsWidget.h"

#include "modulesStorage.h"

EventsWidget::EventsWidget(ModuleDescriptionRaw* module)
    : m_ui(new Ui::EventsWidget)
{
    m_ui->setupUi(this);

    m_module = module;

    QList<ModuleEventRaw> eventsRaw = m_module->interface.events;
    for (int i = 0; i < eventsRaw.size(); i++) {
        QCheckBox* event = new QCheckBox(eventsRaw[i].name);
        event->setCheckState(Qt::Checked);
        m_events[eventsRaw[i].name] = event;
        m_ui->events->addWidget(event);
    }
}

EventsWidget::~EventsWidget()
{
    delete m_ui;
}

QList<EventParams> EventsWidget::getEvents()
{
    QList<EventParams> events;
    QList<ModuleEventRaw> eventsRaw = m_module->interface.events;
    for (int i = 0; i < eventsRaw.size(); i++) {
        EventParams event;
        event.eventInfo["name"] = eventsRaw[i].name;
        event.eventInfo["moduleID"] = QString::number(ModulesStorage::instance().getModule(m_module));
        event.eventInfo["recordable"] = (m_events[eventsRaw[i].name]->checkState() == Qt::Checked
                                         ? "true"
                                         : "false");

        QList<ModuleEventParamRaw> arguments = eventsRaw[i].params;
        for (int j = 0; j < arguments.size(); j++) {
            EventArgument arg;
            arg["ID"] = QString::number(arguments[j].ID);
            arg["type"] = arguments[j].type;
            arg["name"] = arguments[j].name;

            event.arguments += arg;
        }
        events += event;
    }

    return events;
}

void EventsWidget::setEvents(QList<EventParams> events)
{
    // WARNING: these events has global ID number!
    foreach(EventParams event, events) {
        QCheckBox* check = m_events[event.eventInfo["name"]];
        if (check) {
            if (event.eventInfo["recordable"] == "true")
                check->setCheckState(Qt::Checked);
            else
                check->setCheckState(Qt::Unchecked);
        }
        else {
            // TODO: error handling
        }
    }
}
