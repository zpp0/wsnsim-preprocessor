#include "projectInfo.h"
#include "ui_projectInfo.h"


ProjectPage::ProjectPage () :
    m_ui(new Ui::ProjectPage)
{
    m_ui->setupUi (this);
}

ProjectPage::~ProjectPage ()
{
    delete m_ui;
}

QMap<QString, QString> ProjectPage::getParams()
{

    QMap<QString, QString> params;
    params["author"] = m_ui->author->text();
    params["title"] = m_ui->title->text();
    params["comment"] = m_ui->comment->text();
    params["keyrowds"] = m_ui->comment->text();

    // возвращаем результат
    return params;
}
