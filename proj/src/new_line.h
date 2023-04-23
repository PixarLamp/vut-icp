/**
  * @file new_line.h
  * @author Jakub Vaňo, Zuzana Hrkľová
  * @brief header for relation line class
  */
#ifndef NEW_LINE_H
#define NEW_LINE_H


#include <QPainter>
#include <QGraphicsItem>
#include <list>

using namespace std;

class newline :public QGraphicsItem
{
public:
    /**
     * @brief newline Consturcts new relation line in class diagram
     *
     * @param start starting class of relation
     * @param end ending class of relation
     * @param relationtype type of relation
     */
    newline(QPointF start, QPointF end, QString relationtype);

    QPointF p1;
    QPointF p2;
    QString type;

    /**
     * @brief boundingRect creates bounding rectangle for new line
     * @return bounding rectangle
     */
    QRectF boundingRect() const;

    /**
     * @brief paint displays new relation line
     *
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * @brief moveLine moves line to new position when connected class moves
     *
     * @param newPos coordinates of moved class new position
     * @param isP1 true if starting class moved, false if ending class moved
     * @param class_no serial number of moved class used for offset calculation
     */
    void moveLine(QPointF newPos, bool isP1, int class_no);

private:
    QGraphicsLineItem *line;
};

#endif // NEW_LINE_H
