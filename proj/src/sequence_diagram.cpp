/**
  * @file sequence_diagram.cpp
  * @author Jakub Vaňo, Zuzana Hrkľová
  */

#include "sequence_diagram.h"
#include "ui_sequence_diagram.h"

#include <QPixmap>

int drawn = 0;

sequence_diagram::sequence_diagram(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sequence_diagram)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->fileName->setPlaceholderText("image name");

}

void sequence_diagram::display(everything *save, vector<QString> iClasses, vector<QString> iMethods, vector<bool> iRelations){
    vector<sequenceClass*> class_list;
    vector<QString> classes = save->sequenceClasses[drawn];
    createSequences *sptr;
    //chcecks if classes are consistent and displays on scene
    for (int i = 0; i < classes.size(); i++){
        bool isConsistent = true;
        for (QString it : iClasses){
            if (it == classes[i])
                isConsistent = false;
        }
        seqClass = new sequenceClass(classes[i], i, save->sequences[drawn].size(), isConsistent);
        scene->addItem(seqClass);
        class_list.push_back(seqClass);
    }
    //displays all sequences of diagram
    nSeq = new createSequences(class_list, iMethods, iRelations, save, scene);
    scene->addItem(nSeq);
    for (diagram_sequence it : save->sequences[drawn]){
        nSeq->add_sequence(it.from, it.where, it.name, it.type, it.activate, it.deactivate);
    }
    sptr = nSeq;
    save->drawnSequences.push_back(sptr);
    drawn += 1;
}


sequence_diagram::~sequence_diagram()
{
    delete ui;
}


void sequence_diagram::on_Save_clicked()
{
    //if given name saves png of scene
    if (!ui->fileName->text().isEmpty()){
        QString name = ui->fileName->text() + ".png";
        QPixmap pixMap = ui->graphicsView->grab(ui->graphicsView->sceneRect().toRect());
        pixMap.save(name);
        ui->label->setText("Saved");
    }
    else
        ui->label->setText("Missing file name");
}
