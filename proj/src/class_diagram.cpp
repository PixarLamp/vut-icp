/**
  * @file class_diagram.cpp
  * @author Jakub Vaňo, Zuzana Hrkľová
  */
#include "class_diagram.h"
#include "ui_class_diagram.h"
#include "backend.h"

#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <QPixmap>

using namespace std;

everything *save = new everything;
vector<sequence_diagram*> windowList;
int cnt = 0;
bool isDrawn = false;

class_diagram::class_diagram(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::class_diagram)
{
    ui->setupUi(this);
    ui->AddName->setPlaceholderText("new class name");
    ui->DelName->setPlaceholderText("class name to delete");
    ui->imageName->setPlaceholderText("image name");
    ui->lineEdit->setPlaceholderText("path to class json");
    ui->lineEdit_2->setPlaceholderText("path to sequence json");

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
}

class_diagram::~class_diagram()
{
    delete ui;
}

void class_diagram::on_pushButton_2_clicked()
{
    //closes all sequence diagrams from previous class diagram
    for(sequence_diagram *it : windowList){
        it->close();
    }
    //clears all data from previous diagrams
    save->sequenceClasses.clear();
    save->sequences.clear();
    save->drawnClasses.clear();
    cnt = 0;
    scene->setSceneRect(0,0,1750,1000);
    save->classesscene = scene;
    //loads diagram from input path
    QJsonObject data = load_diagram(ui->lineEdit->text());
    //if well-formed displays on scene
    if (check_class_diagram(data)){
        scene->clear();
        ui->label_2->setText("correct");
        vector<diagram_classes> classList = save_classes(data);
        vector<diagram_relations> relationList = save_relations(data);
        int count = 0;
        newclass *cptr;
        for (diagram_classes i : classList){
            QString name = i.class_name;
            vector<QString> attrib = i.attributes;
            vector<QString> meth = i.methods;

            nClass = new newclass(name, attrib, meth, count, save);
            scene->addItem(nClass);
            cptr = nClass;
            save->drawnClasses.push_back(cptr);
            count += 1;
        }
        for (diagram_relations i : relationList){
            QString type = i.type;
            QString from = i.from;
            QString where = i.where;

            newclass *start;
            newclass *end;

            for (newclass *y : save->drawnClasses){
                if (y->name == from)
                    start = y;
                if (y->name == where)
                    end = y;
            }
            nLine = new newline(start->classposition, end->classposition, type);
            start->addlinetoclass(nLine, true);
            end->addlinetoclass(nLine, false);
            scene->addItem(nLine);
            isDrawn = true;
        }
    }
    else
        ui->label_2->setText("fail");

}

void class_diagram::on_NewClass_clicked(){
    //loads sequence diagram from input path
    QJsonObject data = load_diagram(ui->lineEdit_2->text());
    vector<QString> iClasses;
    vector<QString> iMethods;
    vector<bool> iRelations;
    //if well-formed creates new window and displays sequence diagram
    if (check_sequence_diagram(data)){
        ui->label_2->setText("correct");
        seqWindow = new sequence_diagram(this);
        seqWindow->show();
        seqWindow->drawn = cnt;
        windowList.push_back(seqWindow);
        save_sequence_diagram(data, save);
        iClasses = is_consistent_class(save, cnt);
        iMethods = is_consistent_method(save, cnt);
        iRelations = is_consistent_sequence(save, cnt);
        seqWindow->display(save, iClasses, iMethods, iRelations);
        cnt++;
    }
    else
        ui->label_2->setText("fail");
}

void class_diagram::on_AddClass_clicked()
{
    //if class diagram is displayed adds new class on scene
    if (isDrawn){
        QString name = ui->AddName->text();
        vector<QString> attribs;
        vector<QString> methods;
        bool found = false;

        for (newclass *it : save->drawnClasses){
            if (name == it->name)
                found = true;
        }

        if (found)
            ui->label_2->setText("Class already exists");
        else {
            newclass *cptr;
            nClass = new newclass(name, attribs, methods, 0, save);
            scene->addItem(nClass);
            cptr = nClass;
            save->drawnClasses.push_back(cptr);
            for (createSequences* actSequence : save->drawnSequences){
                for (sequenceClass* actClass : actSequence->classes){
                    if((actClass->name == name) && (actClass->consistent == false)){
                        actClass->updateConsistency(true);
                    }
                }
            }
        }
    }
    else
        ui->label_2->setText("Insert Class Diagram first");
}

void class_diagram::on_DelClass_clicked()
{
    QString name = ui->DelName->text();
    int x = 0;
    bool deleted = false;
    //deletes class from class diagram
    for (newclass *i : save->drawnClasses){
        if (name == i->name){
            for (newline* line : i->lines){
                scene->removeItem(line);
            }
            scene->removeItem(i);
            delete(i);
            save->drawnClasses.erase(save->drawnClasses.begin() + x);
            deleted = true;
            ui->label_2->setText("Class deleted");
        }
        else
            x++;
    }
    //chcecks consistency of sequence diagrams
    for (createSequences* actSequence : save->drawnSequences){
        for (sequenceClass* actClass : actSequence->classes){
            if(actClass->name == name){
                actClass->updateConsistency(false);
            }
        }
    }
    if (!deleted){
        ui->label_2->setText("Class not found");
    }
}

void class_diagram::on_Save_clicked()
{
    //if name provided saves png of scene
    if (!ui->imageName->text().isEmpty()){
        QString name = ui->imageName->text() + ".png";
        QPixmap pixMap = ui->graphicsView->grab(ui->graphicsView->sceneRect().toRect());
        pixMap.save(name);
    }
    else
        ui->label_2->setText("Missing file name");

}
