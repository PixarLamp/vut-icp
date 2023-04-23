/**
  * @file sequenceclass.cpp
  * @author Jakub Vaňo, Zuzana Hrkľová
  */

#include "sequenceclass.h"


sequenceClass::sequenceClass(QString classname, int class_no, int sequences_no, bool isConsistent)
{
    name = classname;
    width = name.size()*10 + 20;
    height = (sequences_no + 2) * 40;
    position = QPointF(class_no * 200, 0);
    active = false;
    consistent = isConsistent;
}

QRectF sequenceClass::boundingRect() const
{
    return QRectF(position.x(), position.y(), width, height);
}

void sequenceClass::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen red(Qt::red);
    //if not consistent draws red
    if (!consistent)
        painter->setPen(red);
    //displays class name
    painter->drawText(position.x()+10, position.y()+18, name);
    painter->drawRect(position.x(), position.y(), width, 20);

    int x_offset = width / 2;
    //draws vertical dashed line from class
    QPen pen(Qt::DashLine);
    painter->setPen(pen);
    painter->drawLine(position.x() + x_offset, position.y()+20, position.x() + x_offset, height);
}

void sequenceClass::updateSequenceNumber(int x)
{
    //changes vertical line according to number of sequences
    height += 40*x;
    update();
}

void sequenceClass::updateConsistency(bool isConsistent)
{
    //changes color of class according to consistency
    consistent = isConsistent;
    update();
}
