/**
 *
 * File: simulatorPage.cpp
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "simulatorPage.h"
#include "ui_simulatorPage.h"

#include "nodesStorage.h"
#include "errorsStorage.h"

SimulatorPage::SimulatorPage(QWidget* parent)
    : m_ui(new Ui::SimulatorPage), QGroupBox(parent)
{
    m_ui->setupUi(this);

    connect(m_ui->logFile, SIGNAL(textChanged(QString)),
            this, SLOT(setFileName(QString)));
    connect(m_ui->maxTime, SIGNAL(valueChanged(int)),
            this, SLOT(setTimeValue(int)));

    NodesStorage& storage = NodesStorage::instance();
    connect(&storage, SIGNAL(nodesTotalChanged(int)),
            this, SLOT(setNodesTotal(int)));

    setLogError(true);
    setTimeError(true);
    setNodesError(true);
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

void SimulatorPage::setTimeValue(int time)
{
    if (time == 0)
        setTimeError(true);
    else
        setTimeError(false);
}

void SimulatorPage::setFileName(QString value)
{
    if (value == "")
        setLogError(true);
    else
        setLogError(false);
}

void SimulatorPage::setNodesTotal(int number)
{
    if (number > 0)
        setNodesError(false);
    else
        setNodesError(true);
}

void SimulatorPage::setTimeError(bool error)
{
    ErrorsStorage::instance().setPossibleError(m_ui->maxTime,
                                               error,
                                               title() + ": " + tr("unbinded virtual time"));
}

void SimulatorPage::setLogError(bool error)
{
    ErrorsStorage::instance().setPossibleError(m_ui->logFile,
                                               error,
                                               title() + ": " + tr("unbinded log file name"));
}

void SimulatorPage::setNodesError(bool error)
{
    ErrorsStorage::instance().setPossibleError(m_ui->sb_nodes,
                                               error,
                                               tr("No nodes chosen"));
}

SimulatorPage::~SimulatorPage()
{
    delete m_ui;
}
