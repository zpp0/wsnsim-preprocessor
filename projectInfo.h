#ifndef PROJECTPAGE_H
#define PROJECTPAGE_H

#include <QGroupBox>

#include "projectParams.h"

namespace Ui {
    class ProjectInfo;
}

class ProjectInfoPage : public QGroupBox
{
    Q_OBJECT

public:
    ProjectInfoPage();
    virtual ~ProjectInfoPage();

    ProjectInfo getParams();
    
private:    
    Ui::ProjectInfo *m_ui;
};

#endif // PROJECTPAGE_H
