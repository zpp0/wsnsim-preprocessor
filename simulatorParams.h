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

    SimulatorParams getParams();
    
private:    
    Ui::SimulatorParams *m_ui;
};

#endif // SIMULATORPARAMS_H
