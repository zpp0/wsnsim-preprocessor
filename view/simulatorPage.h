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
    SimulatorPage(QWidget* parent = 0);
    virtual ~SimulatorPage();

    SimulatorParams getParams();
    void setParams(SimulatorParams params);

    void clear();

private slots:
    void setFileName(QString fileName);
    void setTimeValue(int time);
    void setNodesTotal(int number);

private:
    void setTimeError(bool error);
    void setLogError(bool error);
    void setNodesError(bool error);

    Ui::SimulatorPage *m_ui;
};

#endif // SIMULATORPAGE_H
