#ifndef SIMULATORPARAMS_H
#define SIMULATORPARAMS_H

#include <QGroupBox>

#include "projectParams.h"

namespace Ui {
    class SimulatorParams;
}

class SimulatorParamsPage : public QGroupBox
{
    Q_OBJECT

public:
    SimulatorParamsPage();
    virtual ~SimulatorParamsPage();

public slots:
    void setNewFileName(QString fileName);
    void setNewTimeValue(int time);
    void setNewTimeUnits(int units);

private slots:
    void setFileName(QString fileName);
    void setTimeValue(quint64 time);
    void timeUnitsActivated(TimeUnits units);

private:
    Ui::SimulatorParams *m_ui;
};

#endif // SIMULATORPARAMS_H
