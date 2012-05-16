#include "simulatorParams.h"
#include "ui_simulatorParams.h"

SimulatorParamsPage::SimulatorParamsPage () :
    m_ui(new Ui::SimulatorParams)
{
    m_ui->setupUi (this);
}

SimulatorParamsPage::~SimulatorParamsPage ()
{
    delete m_ui;
}

SimulatorParams SimulatorParamsPage::getParams()
{
    SimulatorParams params;
    params.maxTime = m_ui->maxTime->text().toULong(); 
    params.logFile = m_ui->logFile->text();

    // возвращаем результат
    return params;
}
