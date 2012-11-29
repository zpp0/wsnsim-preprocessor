/**
 *
 * File: simulatorPage.h
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef SIMULATORPAGE_H
#define SIMULATORPAGE_H

#include <QGroupBox>

#include "projectParams.h"

namespace Ui {
    class SimulatorPage;
}

class SimulatorPage : public QGroupBox
{
    Q_OBJECT

public:
    SimulatorPage();
    virtual ~SimulatorPage();

    SimulatorParams getParams();
    void setParams(SimulatorParams params);

    void clear();

private:
    Ui::SimulatorPage *m_ui;
};

#endif // SIMULATORPAGE_H
