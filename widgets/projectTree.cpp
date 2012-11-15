/**
 *
 * File: projectTree.cpp
 * Description:  QTreeWidget widget API for modules pages
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#include "projectTree.h"

#include <QHeaderView>

ProjectTree::ProjectTree()
{
    header()->setVisible(false);

    // сигнал о нажатии на элемент дерева обрабатывает основное окно
    connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)),
            this, SLOT(changePage(QTreeWidgetItem*, QTreeWidgetItem*)));
}

ProjectTree::~ProjectTree()
{
}

// добавление страницы в список страниц
void ProjectTree::addPage(QString p_name, QWidget *page, QTreeWidgetItem* parent)
{
    // создаем новый элемент дерева для этой страницы
    QTreeWidgetItem *ti_page = addTiWidget(p_name, parent);

    // запоминаем связь между этими страницами
    m_h_pages.insert(ti_page, page);

    emit newPage(page);
}

void ProjectTree::addPage(QTreeWidgetItem* ti_page, QWidget *page)
{
    // запоминаем связь между переданным элементом дерева и новой страницой
    m_h_pages.insert(ti_page, page);

    emit newPage(page);
}

// создание элемента дерева
QTreeWidgetItem* ProjectTree::addTiWidget(QString name, QTreeWidgetItem* parent)
{
    // добавляем элемент дерева
    QTreeWidgetItem *ti_widget;

    // если указан родитель
    if (parent)
        // то новый элемент дерева будет дочерним от родительского
        ti_widget = new QTreeWidgetItem(parent);
    else
        // иначе новый элемент будет на верхнем уровне дерева
        ti_widget = new QTreeWidgetItem(this);

    // выставляем имя элементу
    ti_widget->setText(0, name);

    // возвращаем его
    return ti_widget;
}

// пользователь перешел на другую страницу
void ProjectTree::changePage(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    // нажат элемент дерева - надо показать соответствующую страницу

    // если элемент дерева нажат повторно, то просто выходим
    if (current == previous)
        return;

    emit pageSelected(m_h_pages.value(current));
}

void ProjectTree::removePage(QTreeWidgetItem* ti_page)
{
    QWidget* page = m_h_pages.value(ti_page);
    removeItemWidget(ti_page, 0);
    delete ti_page;

    emit delPage(page);
}

void ProjectTree::removePage(QWidget* page)
{
    QTreeWidgetItem* ti_page = m_h_pages.key(page);
    removeItemWidget(ti_page, 0);
    delete ti_page;

    emit delPage(page);
}
