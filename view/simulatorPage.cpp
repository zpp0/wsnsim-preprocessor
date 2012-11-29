/**
 *
 * File: simulatorPage.cpp
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "simulatorPage.h"
#include "ui_simulatorPage.h"

SimulatorPage::SimulatorPage()
    : m_ui(new Ui::SimulatorPage)
{
    m_ui->setupUi(this);
}

SimulatorParams SimulatorPage::getParams()
{
    SimulatorParams params;
    params.logFile = m_ui->logFile->text();
    params.maxTime = m_ui->maxTime->value();
    params.timeUnits = (TimeUnits)m_ui->cb_timeUnits->currentIndex();

    return params;
}

void SimulatorPage::setParams(SimulatorParams params)
{
    m_ui->logFile->setText(params.logFile);
    m_ui->maxTime->setValue(params.maxTime);
    m_ui->cb_timeUnits->setCurrentIndex(params.timeUnits);
}

void SimulatorPage::clear()
{
    m_ui->logFile->setText("");
    m_ui->maxTime->setValue(0);
    m_ui->cb_timeUnits->setCurrentIndex(0);
}

SimulatorPage::~SimulatorPage()
{
    delete m_ui;
}
