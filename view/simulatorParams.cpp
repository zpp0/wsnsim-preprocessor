#include "simulatorParams.h"
#include "ui_simulatorParams.h"

#include "projectStorage.h"

SimulatorParamsPage::SimulatorParamsPage() :
    m_ui(new Ui::SimulatorParams)
{
    m_ui->setupUi (this);

    connect(m_ui->logFile, SIGNAL(textChanged(QString)),
            this, SLOT(setFileName(QString)));

    connect(m_ui->maxTime, SIGNAL(valueChanged(int)),
            this, SLOT(setTimeValue(int)));
    connect(m_ui->cb_timeUnits, SIGNAL(currentIndexChanged(int)),
            this, SLOT(timeUnitsActivated(int)));
}

SimulatorParamsPage::~SimulatorParamsPage()
{
    delete m_ui;
}

void SimulatorParamsPage::setTimeValue(int time)
{
    ProjectStorage& storage = ProjectStorage::instance();
    storage.setMaxTime(time);
}

void SimulatorParamsPage::timeUnitsActivated(int units)
{
    ProjectStorage& storage = ProjectStorage::instance();
    storage.setTimeUnits((TimeUnits)units);
}

void SimulatorParamsPage::setFileName(QString value)
{
    ProjectStorage& storage = ProjectStorage::instance();
    storage.setFileName(value);
}

void SimulatorParamsPage::setNodesTotal(int number)
{
    m_ui->sb_nodes->setValue(number);
}

void SimulatorParamsPage::setNewFileName(QString fileName)
{
    m_ui->logFile->setText(fileName);
}

void SimulatorParamsPage::setNewTimeValue(int time)
{
    m_ui->maxTime->setValue(time);
}

void SimulatorParamsPage::setNewTimeUnits(int units)
{
    m_ui->cb_timeUnits->setCurrentIndex(units);
}
