/**
  * @file createsequences.h
  * @author Jakub Vaňo, Zuzana Hrkľová
  * @brief header file for saving and maintaining sequence diagram
  */
#ifndef CREATESEQUENCES_H
#define CREATESEQUENCES_H

#include <QPainter>
#include <QGraphicsItem>

#include <QGraphicsSceneEvent>
#include "sequenceclass.h"
#include "backend.h"
#include <vector>

using namespace std;

struct everything;

class createSequences :public QGraphicsItem
{
public:
    /**
     * @brief createSequences Constructs new sequence diagram
     *
     * @param sequence_classes classes included in sequence diagram
     * @param inconsistentMethods vector of inconsistent methods used in sequence diagram
     * @param inconsistentRelations vector of inconsistent relations used in sequence diagram
     * @param save structure containing all diagrams
     * @param seqscene sequence diagram scene
     */
    createSequences(vector<sequenceClass*> sequence_classes, vector<QString> inconsistentMethods, vector<bool> inconsistentRelations, everything *save, QGraphicsScene *seqscene);

    vector<sequenceClass*> classes;
    vector<QString> iMethods;
    vector<bool> iRelations;

    int width;
    int height;
    int cnt;

    vector<QString> from;
    vector<QString> to;
    vector<QString> method;
    vector<QString> type;
    vector<QString> activate;
    vector<QString> deactivate;
    everything *data;
    QGraphicsScene *scene;

    /**
     * @brief boundingRect creates bounding rectangle for sequences
     * @return bounding rectangle
     */
    QRectF boundingRect() const;

    /**
     * @brief paint draws all sequences in sequence diagram
     *
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * @brief add_sequence adds new sequence to diagram
     *
     * @param from_class starting class of sequence
     * @param to_class ending class of sequence
     * @param class_method used method
     * @param sequence_type type of sequence
     * @param activate_class activation of class ("" if no activation wanted)
     * @param deactivate_class deactivation of class ("" if no deactivation wanted)
     */
    void add_sequence(QString from_class, QString to_class, QString class_method, QString sequence_type, QString activate_class, QString deactivate_class);

    /**
     * @brief mouseDoubleClickEvent opens sequence diagram editor
     *
     * @param event right mouse button double click
     */
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    /**
     * @brief delete_last_sequence deletes last sequence
     */
    void delete_last_sequence();
};

#endif // CREATESEQUENCES_H
