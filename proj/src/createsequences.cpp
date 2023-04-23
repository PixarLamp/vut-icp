/**
  * @file createsequences.cpp
  * @author Jakub Vaňo, Zuzana Hrkľová
  */

#include "createsequences.h"
#include "seq_edit_menu.h"

createSequences::createSequences(vector<sequenceClass*> sequence_classes, vector<QString> inconsistentMethods, vector<bool> inconsistentRelations, everything* save, QGraphicsScene *seqscene)
{
    iMethods = inconsistentMethods;
    iRelations = inconsistentRelations;
    classes = sequence_classes;
    height = classes.front()->height;
    int size = classes.size();
    width = classes.at(size - 1)->position.x() + classes.at(size - 1)->width;
    data = save;
    scene = seqscene;
}


QRectF createSequences::boundingRect() const
{
    return QRectF(0, 0, width, height);
}

void createSequences::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen dashed(Qt::DashLine);
    QPen solid(Qt::SolidLine);
    QPen red(Qt::red);
    QPen black(Qt::black);
    QBrush brush(Qt::black);
    QBrush rbrush(Qt::red);

    int act_position = 80;
    sequenceClass* start_class;
    sequenceClass* end_class;

    //iterates through all starting classes
    for (int i=0; i < from.size() ;i++){
        //default color set to black
        dashed.setColor(Qt::black);
        solid.setColor(Qt::black);
        painter->setBrush(brush);
        for (sequenceClass* it : classes){
            if (from.at(i) == it->name){
                start_class = it;
            }
            if (to.at(i) == it->name){
                end_class = it;
            }
        }
        int x1 = start_class->position.x() + ((start_class->width)/2);
        int x2 = end_class->position.x() + ((end_class->width)/2);
        QPointF start = QPointF(x1, act_position);
        QPointF end = QPointF(x2, act_position);
        //finds out type of line
        if (type.at(i) == "response"){
            if(!iRelations.at(i))
                dashed.setColor(Qt::red);
            painter->setPen(dashed);
        }
        else{
            if(!iRelations.at(i))
                solid.setColor(Qt::red);
            painter->setPen(solid);
        }
        painter->drawLine(start, end);
        painter->setPen(solid);

        //sets red brush if incosistent
        if(!iRelations.at(i))
            painter->setBrush(rbrush);

        //setting points for the arrow
        QPointF p1 = QPointF(end.x()- 15, end.y()+5);
        QPointF p2 = QPointF(end.x()- 15, end.y()-5);
        QPointF p3 = QPointF(end.x(), end.y());
        QPointF points[3] = {p1,p2,p3};
        QPointF p4 = QPointF(end.x()+ 15, end.y()+5);
        QPointF p5 = QPointF(end.x()+ 15, end.y()-5);
        QPointF p6 = QPointF(end.x(), end.y());
        QPointF rpoints[3] = {p4, p5, p6};

        //drawing correct type of arrow
        if (type.at(i)=="asyn_request"){
            if (end.x() < start.x())
                painter->drawPolygon(rpoints, 3);
            else
                painter->drawPolygon(points, 3);
        }
        else{
            if(!iRelations.at(i))
                solid.setColor(Qt::red);
            painter->setPen(solid);
            if (end.x() > start.x()){
                painter->drawLine(end.x()- 15, end.y()+5, end.x()-5, end.y());
                painter->drawLine(end.x()- 15, end.y()-5, end.x()-5, end.y());
            }
            else{
                painter->drawLine(end.x()+ 15, end.y()+5, end.x()+5, end.y());
                painter->drawLine(end.x()+ 15, end.y()-5, end.x()+5, end.y());
            }
            solid.setColor(Qt::black);
        }
        painter->setBrush(brush);

        int text_start = start.x();
        if (end.x() < start.x()){
            text_start = end.x();
        }
        for (QString it : iMethods){
            if (it == method.at(i))
                painter->setPen(red);
        }
        painter->drawText(text_start + 20, act_position - 2, QString::number(i+1)+ ". " + method.at(i));
        painter->setPen(black);
        sequenceClass *activated_class;
        sequenceClass *deact_class;
        //drawing active rectangle
        if (activate.at(i) != ""){
            for (sequenceClass* it : classes){
                if (it->name == activate.at(i)){
                    activated_class = it;
                    activated_class->active = true;
                }
            }
        }
        for (sequenceClass* it : classes){
            if(it->active == true){
                int xx = it->position.x() + (it->width / 2);
                painter->drawRect(xx - 5, act_position-40, 10, 40);
            }
        }
        if (deactivate.at(i) != ""){
            for (sequenceClass* it : classes){
                if (it->name == deactivate.at(i)){
                    deact_class = it;
                    deact_class->active = false;
                }
            }
        }
        act_position += 40;
    }
    for (sequenceClass* it : classes){
        if(it->active == true){
            int xx = it->position.x() + (it->width / 2);
            painter->setBrush(brush);
            painter->drawRect(xx - 5, act_position-40, 10, 40);
        }
    }
}

void createSequences::add_sequence(QString from_class, QString to_class, QString class_method, QString sequence_type, QString activate_class, QString deactivate_class)
{
    from.push_back(from_class);
    to.push_back(to_class);
    method.push_back(class_method);
    type.push_back(sequence_type);
    activate.push_back(activate_class);
    deactivate.push_back(deactivate_class);
}

void createSequences::delete_last_sequence()
{
    from.pop_back();
    to.pop_back();
    method.pop_back();
    type.pop_back();
    activate.pop_back();
    deactivate.pop_back();
    iRelations.pop_back();

    update();
}

void createSequences::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if ( event->button() == Qt::RightButton)
        {
            seq_edit_menu openmenu;
            openmenu.edited_seq = this;
            openmenu.setModal(true);
            openmenu.exec();
        }

    QGraphicsItem::mouseDoubleClickEvent(event);
}

