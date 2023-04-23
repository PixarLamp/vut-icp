/**
  * @file new_line.cpp
  * @author Jakub Vaňo, Zuzana Hrkľová
  */

#include "new_line.h"

#include <cmath>

newline::newline(QPointF start, QPointF end, QString relationtype)
{
    p1 = start;
    p2 = end;
    type = relationtype;
}

QRectF newline::boundingRect() const
{
    return QRectF(0, 0, 1750, 1000);
}

QPointF getendpointoavector(QPointF vec, QPointF startpoint, int x){
    //calculates end point of vector
    float veclen = sqrt(vec.x()*vec.x() + vec.y()*vec.y());
    float dx = static_cast<float>(vec.x()) / veclen;
    float dy = static_cast<float>(vec.y()) / veclen;
    QPointF unitv = QPointF(dx*x, dy*x);
    int endx = unitv.x() + startpoint.x();
    int endy = unitv.y() + startpoint.y();
    QPointF endpoint = QPointF(endx, endy);
    return endpoint;
}

void newline::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush(Qt::black);

    QPointF vec = QPointF(p2.x()-p1.x(), p2.y()-p1.y());
    QPointF endpoint = getendpointoavector(vec, p1, 20);

    int xx = p1.x() - endpoint.x();
    int yy = p1.y() - endpoint.y();

    QPointF unitshift = QPointF(xx, yy);
    QPointF normal1 = QPointF(-unitshift.y(), unitshift.x());
    QPointF point1 = getendpointoavector(normal1, endpoint, 10);

    QPointF normal2 = QPointF(unitshift.y(), -unitshift.x());
    QPointF point2 = getendpointoavector(normal2, endpoint, 10);

    QPointF point3 = getendpointoavector(vec, p1, 40);

    QPointF points[4] = {
        point1,
        p1,
        point2,
        point3
    };
    //draws line according to type of relation
    if (type == "association"){
        painter->drawLine(p1, p2);
    }
    if (type == "inheritance"){
        painter->drawPolygon(points, 3);
        painter->drawLine(endpoint, p2);
    }
    if (type == "aggregation"){
        painter->drawPolygon(points, 4);
        painter->drawLine(point3, p2);
    }
    if (type == "composition"){
        painter->setBrush(brush);
        painter->drawPolygon(points, 4);
        painter->drawLine(point3, p2);
    }

}


void newline::moveLine(QPointF newPos, bool isP1, int class_no) {

    int x_offset = class_no % 5 * 200;
    int y_offset = class_no/5 * 250;

    //resets starting and end point of line when class is moved
    if (isP1){
       p1 = QPointF(newPos.x() + x_offset, newPos.y() + y_offset);
    }
    else{
        p2 = QPointF(newPos.x() + x_offset, newPos.y() + y_offset);
    }
    update();

}
