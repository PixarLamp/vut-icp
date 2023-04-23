/**
  * @file class_diagram.h
  * @author Jakub Vaňo, Zuzana Hrkľová
  * @brief header file for main window that displays class diagram
  */
#ifndef CLASS_DIAGRAM_H
#define CLASS_DIAGRAM_H

#include "backend.h"
#include "new_class.h"
#include "new_line.h"
#include "createsequences.h"
#include "sequenceclass.h"
#include "sequence_diagram.h"

namespace Ui {
class class_diagram;
}

class class_diagram : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs main window
     *
     * @param parent
     */
    explicit class_diagram(QWidget *parent = 0);
    ~class_diagram();


private slots:

    /**
     * @brief on_pushButton_2_clicked displays class diagram from input path
     */
    void on_pushButton_2_clicked();

    /**
     * @brief on_NewClass_clicked opens new window for new sequence diagram
     */
    void on_NewClass_clicked();

    /**
     * @brief on_AddClass_clicked adds new class with given name into class diagram
     */
    void on_AddClass_clicked();

    /**
     * @brief on_DelClass_clicked deletes class with given name from class diagram
     */
    void on_DelClass_clicked();

    /**
     * @brief on_Save_clicked saves image of displayed class diagram with given name
     */
    void on_Save_clicked();

private:
    Ui::class_diagram *ui;
    sequence_diagram *seqWindow;
    QGraphicsScene *scene;
    newclass *nClass;
    newline *nLine;
    diagram_classes *nclass;
    sequenceClass *seqClass;
    createSequences* nSeq;
};

#endif // CLASS_DIAGRAM_H
