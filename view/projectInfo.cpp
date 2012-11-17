#include "projectInfo.h"
#include "ui_projectInfo.h"

#include "projectStorage.h"

#include <QDateTime>

ProjectInfoPage::ProjectInfoPage() :
    m_ui(new Ui::ProjectInfo)
{
    m_ui->setupUi (this);

    connect(m_ui->author, SIGNAL(textChanged(QString)),
            this, SLOT(setAuthor(QString)));
    connect(m_ui->comment, SIGNAL(textChanged(QString)),
            this, SLOT(setComment(QString)));
    connect(m_ui->keywords, SIGNAL(textChanged(QString)),
            this, SLOT(setKeywords(QString)));
    connect(m_ui->title, SIGNAL(textChanged(QString)),
            this, SLOT(setTitle(QString)));
}

ProjectInfoPage::~ProjectInfoPage()
{
    delete m_ui;
}

void ProjectInfoPage::setAuthor(QString author)
{
    ProjectStorage& storage = ProjectStorage::instance();
    storage.setAuthor(author);
}

void ProjectInfoPage::setComment(QString comment)
{
    ProjectStorage& storage = ProjectStorage::instance();
    storage.setComment(comment);
}

void ProjectInfoPage::setKeywords(QString keyword)
{
    ProjectStorage& storage = ProjectStorage::instance();
    storage.setKeywords(keyword.split(" "));
}

void ProjectInfoPage::setTitle(QString title)
{
    ProjectStorage& storage = ProjectStorage::instance();
    storage.setTitle(title);
}

void ProjectInfoPage::setNewAuthor(QString author)
{
    m_ui->author->setText(author);
}

void ProjectInfoPage::setNewComment(QString comment)
{
    m_ui->comment->setText(comment);
}

void ProjectInfoPage::setNewKeywords(QString keywords)
{
    m_ui->keywords->setText(keywords);
}

void ProjectInfoPage::setNewTitle(QString title)
{
    m_ui->title->setText(title);
}
