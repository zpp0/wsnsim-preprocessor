/**
 *
 * File: projectPage.cpp
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "projectPage.h"
#include "ui_projectPage.h"

ProjectPage::ProjectPage()
    : m_ui(new Ui::ProjectPage)
{
    m_ui->setupUi(this);
}

void ProjectPage::setParams(ProjectInfo params)
{
    m_ui->author->setText(params.projectAutor);
    m_ui->comment->setText(params.projectComment);
    m_ui->keywords->setText(params.keywords.join(" "));
    m_ui->title->setText(params.projectTitle);
}

ProjectInfo ProjectPage::getParams()
{
    ProjectInfo params;
    params.projectAutor = m_ui->author->text();
    params.projectComment = m_ui->comment->text();
    params.keywords = m_ui->keywords->text().split(" ");
    params.projectTitle = m_ui->title->text();
    return params;
}

void ProjectPage::clear()
{
    m_ui->author->setText("");
    m_ui->comment->setText("");
    m_ui->keywords->setText("");
    m_ui->title->setText("");
}

ProjectPage::~ProjectPage()
{
    delete m_ui;
}
