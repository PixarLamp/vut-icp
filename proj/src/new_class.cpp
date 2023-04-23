/**
  * @file new_class.cpp
  * @author Jakub Vaňo, Zuzana Hrkľová
  */

#include "new_class.h"
#include "new_line.h"
#include "edit_menu.h"
#include <QLabel>

newclass::newclass(QString classname, vector<QString> classattributes, vector<QString> classmethods, int class_number, everything *save)
{
    //sets variables
    setFlag(ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    name = classname;
    attributes = classattributes;
    methods = classmethods;
    class_no = class_number;

    point = this->pos();

    int x = class_no % 5 * 200;
    int y = class_no/5 * 250;
    classposition = QPointF(x, y);

    released = false;
    data = save;
}

QRectF newclass::boundingRect() const
{
    //creates bounding rectangle for class according to number of attributes and methods
    int attrib_no = attributes.size();
    int methods_no = methods.size();
    if (methods_no == 0){
        methods_no = 1;
    }
    int height = 20 + attrib_no*20 + methods_no*20;
    int x = class_no % 5 * 200;
    int y = class_no/5 * 250;
    return QRectF(x, y, 120, height);
}

void newclass::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::white);

    int x = class_no % 5 * 200;
    int y = class_no/5 * 250;

    //drawing class rectangles and adds text into them
    painter->fillRect(rec, brush);
    painter->drawRect(rec);
    painter->drawText(x+2, y+18, name);
    int position = 0;
    int i = 0;
    for (QString it : attributes){
        position = 38 + i*20;
        painter->drawText(x+2, y+position, it);
        i++;
    }
    painter->drawRect(x, y+20, 120, 20*attributes.size());
    for (QString it : methods){
        position = position + 20;
        painter->drawText(x+2, y+position, it);
    }

    int lines_no = lines.size();
    if ((lines_no > 0) &&(released == true)){
        QPointF newPos = this->pos();
        for (int i = 0; i < lines_no; i++){
            lines.at(i)->moveLine(newPos, line_startpoint.at(i), class_no);
        }
        released = false;
    }

}

void newclass::addlinetoclass(newline *line, bool isP1){
    //adds new relation to class
    newline *ptr;
    ptr = line;
    lines.push_back(ptr);
    line_startpoint.push_back(isP1);
}

void newclass::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //updates position after class is moved
    released = true;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void newclass::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    //opens edit menu
    if ( event->button() == Qt::RightButton)
        {
            edit_menu openmenu;
            openmenu.edited_class = this;
            openmenu.setModal(true);
            openmenu.exec();
        }
    QGraphicsItem::mouseDoubleClickEvent(event);
}
