/**
  * @file sequenceclass.h
  * @author Jakub Vaňo, Zuzana Hrkľová
  * @brief header for class used in sequence diagram
  */
#ifndef SEQUENCECLASS_H
#define SEQUENCECLASS_H


#include <QPainter>
#include <QGraphicsItem>

class sequenceClass :public QGraphicsItem
{
public:
    /**
     * @brief sequenceClass Constructs new class used in sequence diagram
     *
     * @param classname name of class
     * @param class_no serial number of class
     * @param sequences_no initial number of sequences from class
     * @param isConsistent true if class is consistent, false if inconsistent
     */
    sequenceClass(QString classname, int class_no, int sequences_no, bool isConsistent);

    QString name;
    int width;
    int height;
    QPointF position;
    bool active;
    bool consistent;

    /**
     * @brief boundingRect creates bounding rectangle for sequence class
     * @return bounding rectangle
     */
    QRectF boundingRect() const;

    /**
     * @brief paint draws class
     *
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * @brief updateSequenceNumber updates number of sequences
     * @param x difference of sequences
     */
    void updateSequenceNumber(int x);

    /**
     * @brief updateConsistency updates consistency after class name edit in class diagram
     * @param isConsistent true if consistent, else if inconsistent
     */
    void updateConsistency(bool isConsistent);
};

#endif // SEQUENCECLASS_H
