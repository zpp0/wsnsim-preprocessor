#include "projectInfo.h"
#include "ui_projectInfo.h"

#include <QDateTime>

ProjectInfoPage::ProjectInfoPage () :
    m_ui(new Ui::ProjectInfo)
{
    m_ui->setupUi (this);
}

ProjectInfoPage::~ProjectInfoPage ()
{
    delete m_ui;
}

ProjectInfo ProjectInfoPage::getParams()
{

    ProjectInfo params;
    params.projectAutor = m_ui->author->text();
    params.projectTitle = m_ui->title->text();
    params.projectComment = m_ui->comment->text();
    params.keywords = m_ui->keywords->text().split(" ");
    params.revision = 1;

    params.modified = QDateTime().toTime_t();

    // возвращаем результат
    return params;
}
