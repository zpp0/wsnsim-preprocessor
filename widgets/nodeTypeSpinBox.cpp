/**
 *
 * File: nodeTypeSpinBox.cpp
 * Description: The Spin Box widget with nodeType link
 * Author: Yarygin Alexander <yarygin.alexander@gmail.com>
 *
 **/

#include "nodeTypeSpinBox.h"

NodeTypeSpinBox::NodeTypeSpinBox(QString nodeType)
    : m_nodeType(nodeType)
{
    connect(this, SIGNAL(valueChanged(int)),
            this, SLOT(setNodes(int)));

    setMinimum(0);
}

void NodeTypeSpinBox::setNodes(int number)
{
    emit setNodesNum(m_nodeType, number);
}
