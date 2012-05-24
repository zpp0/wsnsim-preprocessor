#include "projectInfo.h"
#include "ui_projectInfo.h"

#include <QDateTime>

ProjectInfoPage::ProjectInfoPage () :
    m_ui(new Ui::ProjectInfo)
{
    m_ui->setupUi (this);
    m_revision = 1;
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
    params.revision = ++m_revision;
    
    params.modified = QDateTime().toTime_t();

    // возвращаем результат
    return params;
}

void ProjectInfoPage::setParams(ProjectInfo params)
{
    m_ui->author->clear();
    m_ui->title->clear();
    m_ui->comment->clear();
    m_ui->keywords->clear();
    m_revision = 1;

    m_ui->author->setText(params.projectAutor);
    m_ui->title->setText(params.projectTitle);
    m_ui->comment->setText(params.projectComment);
    m_ui->keywords->setText(params.keywords.join(" "));
    m_revision = params.revision;
}








