/**
  * @file sequence_diagram.h
  * @author Jakub Vaňo, Zuzana Hrkľová
  * @brief header for sequence diagram window
  */
#ifndef SEQUENCE_DIAGRAM_H
#define SEQUENCE_DIAGRAM_H

#include <QDialog>
#include "backend.h"
#include "createsequences.h"
#include "sequenceclass.h"

namespace Ui {
class sequence_diagram;
}

class sequence_diagram : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief sequence_diagram Constructs new sequence diagram window
     *
     * @param parent
     */
    explicit sequence_diagram(QWidget *parent = 0);
    ~sequence_diagram();

    int drawn;

    /**
     * @brief display displays sequence diagram
     *
     * @param save structure with class diagram and all sequence diagrams
     * @param iClasses vector of inconsistent classes used in sequence diagram
     * @param iMethods vector of inconsistent methods used in sequence diagram
     * @param iRelations vector of inconsistent relations used in sequence diagram
     */
    void display(everything *save, vector<QString> iClasses, vector<QString> iMethods, vector<bool> iRelations);

private slots:
    /**
     * @brief on_Save_clicked aves image of displayed sequence diagram with given name
     */
    void on_Save_clicked();

private:
    Ui::sequence_diagram *ui;
    QGraphicsScene *scene;
    sequenceClass *seqClass;
    createSequences* nSeq;
};




#endif // SEQUENCE_DIAGRAM_H
