/**
 *
 * File: nodeTypeSpinBox.h
 * Description: The Spin Box widget with nodeType link
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef NODETYPESPINBOX_H
#define NODETYPESPINBOX_H

#include <QSpinBox>
#include <QString>

class NodeTypeSpinBox : public QSpinBox
{
    Q_OBJECT
public:
    NodeTypeSpinBox(QString nodeType);
    virtual ~NodeTypeSpinBox();

signals:
    void setNodesNum(QString nodeType, int number);

private slots:
    void setNodes(int number);

private:
    // int m_nodesNumber;
    QString m_nodeType;
};

#endif // NODETYPESPINBOX_H
