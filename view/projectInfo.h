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

private slots:
    void setAuthor(QString author);
    void setComment(QString comment);
    void setKeywords(QString keyword);
    void setTitle(QString title);

private:
    Ui::ProjectInfo *m_ui;
};

#endif // PROJECTPAGE_H
