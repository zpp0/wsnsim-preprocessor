/**
 *
 * File: projectTree.h
 * Description:  QTreeWidget widget API for modules pages
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#ifndef PROJECTTREE_H
#define PROJECTTREE_H

#include <QTreeWidget>

class ProjectTree : public QTreeWidget
{
    Q_OBJECT
public:
    ProjectTree();
    virtual ~ProjectTree();

    // добавление страницы в список страниц
    void addPage(QString p_name, QWidget *page, QTreeWidgetItem* parent = 0);
    void addPage(QTreeWidgetItem* ti_page, QWidget *page);

    void removePage(QTreeWidgetItem* ti_page);
    void removePage(QWidget *page);

    // создание элемента дерева
    QTreeWidgetItem* addTiWidget(QString name, QTreeWidgetItem* parent = 0);

signals:
    void newPage(QWidget *page);
    void delPage(QWidget *page);
    void pageSelected(QWidget *page);

private slots:
    // пользователь перешел на другую страницу
    void changePage(QTreeWidgetItem *current, QTreeWidgetItem *previous);

private:
    // массив страниц
    QHash <QTreeWidgetItem*, QWidget*> m_h_pages;
};

#endif // PROJECTTREE_H
