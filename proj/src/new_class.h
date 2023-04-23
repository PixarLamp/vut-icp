/**
  * @file new_class.h
  * @author Jakub Vaňo, Zuzana Hrkľová
  * @brief header for class class
  */
#ifndef NEW_CLASS_H
#define NEW_CLASS_H

#include <QPainter>
#include <QGraphicsItem>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QPaintDevice>
#include <QBrush>
#include <QGraphicsSceneEvent>

#include <list>
#include "new_line.h"
#include "backend.h"

using namespace std;

struct everything;

class newclass : public QGraphicsItem
{
public:
    /**
     * @brief newclass Constructs and displays new class in class diagram
     *
     * @param classname name of class
     * @param classattributes vector of class attributes
     * @param classmethods vector of class methods
     * @param class_number serial number of class
     * @param save structure with all classes and sequence diagrams
     */
    newclass(QString classname, vector<QString> classattributes, vector<QString> classmethods, int class_number, everything *save);

    QString name;
    vector<QString> attributes;
    vector<QString> methods;
    //number of the class
    int class_no;
    QPointF classposition;
    int no_of_lines;
    vector<newline*> lines;
    vector<bool> line_startpoint;
    QPointF point;
    bool released;
    everything *data;

    /**
     * @brief boundingRect creates bounding rectangle of new class
     * @return bounding rectangle
     */
    QRectF boundingRect() const;

    /**
     * @brief paint displays class on main window
     *
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * @brief addlinetoclass adds new relation
     *
     * @param line pointer to added relation line
     * @param isP1 true if starting class, false if ending class
     */
    void addlinetoclass(newline *line, bool isP1);

    /**
     * @brief mouseReleaseEvent updates line when class is moved
     *
     * @param event release of left mouse button
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    /**
     * @brief mouseDoubleClickEvent opens class diagram editor
     *
     * @param event righ mouse button double click
     */
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // NEW_CLASS_H

