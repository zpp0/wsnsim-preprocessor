/**
 *
 * File: projectPage.h
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef PROJECTPAGE_H
#define PROJECTPAGE_H

#include <QGroupBox>

#include "projectParams.h"

namespace Ui {
    class ProjectPage;
}

class ProjectPage : public QGroupBox
{
    Q_OBJECT

public:
    ProjectPage();
    virtual ~ProjectPage();

    ProjectInfo getParams();
    void setParams(ProjectInfo params);

    void clear();

private:
    Ui::ProjectPage *m_ui;
};

#endif // PROJECTPAGE_H
