/**
  * @file seq_edit_menu.cpp
  * @author Jakub Vaňo, Zuzana Hrkľová
  */

#include "seq_edit_menu.h"
#include "ui_seq_edit_menu.h"
#include <QFrame>

seq_edit_menu::seq_edit_menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::seq_edit_menu)
{
    ui->setupUi(this);
    ui->from->setPlaceholderText("start class");
    ui->where->setPlaceholderText("destination class");
    ui->type->setPlaceholderText("type of sequence");
    ui->method->setPlaceholderText("method");
    ui->activate->setPlaceholderText("class to activate");
    ui->deactivate->setPlaceholderText("class to deactivate");
    ui->addName->setPlaceholderText("class to add");
    ui->delName->setPlaceholderText("class to delete");
}

seq_edit_menu::~seq_edit_menu()
{
    delete ui;
}

void seq_edit_menu::on_Submit_clicked()
{
    QString from = ui->from->text();
    QString where = ui->where->text();
    QString type = ui->type->text();
    QString method = ui->method->text();
    QString activate = ui->activate->text();
    QString deactivate = ui->deactivate->text();
    QString addClass = ui->addName->text();
    QString delClass = ui->delName->text();

    //if input is correct creates new sequence
    if (from != "" && where != "" && method != "" && type != "") {
        bool foundFrom = false;
        bool foundWhere = false;
        bool foundMethod = false;
        bool correctType = false;
        bool foundActiv = false;
        bool foundDeactiv = false;
        bool foundRel = false;
        for (sequenceClass* i : edited_seq->classes){
            if (from == i->name)
                foundFrom = true;
            if (where == i->name)
                foundWhere = true;
            if (activate != ""){
                if (activate == i->name)
                    foundActiv = true;
            }
            if (deactivate != ""){
                if (deactivate == i->name)
                    foundDeactiv = true;
            }
        }
        if (type == "syn_request" || type == "asyn_request" || type == "response")
            correctType = true;

        for (newclass* i : edited_seq->data->drawnClasses){
            if (from == i->name){
                for (QString j : i->methods){
                    if (method == j)
                        foundMethod = true;
                }
                for (newclass* j : edited_seq->data->drawnClasses){
                    if (where == j->name){
                        for (newline* k : i->lines){
                            for (newline* l : j->lines){
                                if (k == l)
                                   foundRel = true;
                            }
                        }
                    }
                }
            }
        }

        if (activate != "" && !foundActiv){
            ui->label->setStyleSheet("QLabel {color: red;}");
            ui->label->setText("activate class does not exist");
        }
        else if (deactivate != "" && !foundDeactiv){
            ui->label->setStyleSheet("QLabel {color: red;}");
            ui->label->setText("deactivate class does not exist");
        }
        else if (!foundFrom){
            ui->label->setStyleSheet("QLabel {color: red;}");
            ui->label->setText("start class does not exist");
        }
        else if (!foundWhere){
            ui->label->setStyleSheet("QLabel {color: red;}");
            ui->label->setText("destination class does not exist");
        }
        else if (!correctType){
            ui->label->setStyleSheet("QLabel {color: red;}");
            ui->label->setText("error type use: syn_request/asyn_request/response");
        }
        else{
            for (sequenceClass* i : edited_seq->classes)
                i->updateSequenceNumber(1);
            edited_seq->add_sequence(from, where, method, type, activate, deactivate);
            ui->label->setStyleSheet("QLabel {color: green;}");
            ui->label->setText("sequence added");       
        }

        if (!foundMethod){
            edited_seq->iMethods.push_back(method);
        }
        if (!foundRel){
            edited_seq->iRelations.push_back(false);
        }
        else
            edited_seq->iRelations.push_back(true);
    }

    //if input is correct, checks for consistency and adds class
    if (addClass != ""){
        bool cons = false;
        bool found = false;
        for (newclass *i : edited_seq->data->drawnClasses){
            if (addClass == i->name)
                cons = true;
        }
        for (sequenceClass *i : edited_seq->classes){
                if (addClass == i->name)
                    found = true;
            }
        if (cons && !found){
            sequenceClass *seqClass = new sequenceClass(addClass, edited_seq->classes.size(), edited_seq->from.size(), true);
            edited_seq->classes.push_back(seqClass);
            edited_seq->scene->addItem(seqClass);
            ui->label->setStyleSheet("QLabel {color: green;}");
            ui->label->setText("class added");
        }
        else if (!cons && !found){
            sequenceClass *seqClass = new sequenceClass(addClass, edited_seq->classes.size(), edited_seq->from.size(), false);
            edited_seq->scene->addItem(seqClass);
            edited_seq->classes.push_back(seqClass);
            ui->label->setStyleSheet("QLabel {color: green;}");
            ui->label->setText("class added");
        }

        if (found){
            ui->label->setStyleSheet("QLabel {color: red;}");
            ui->label->setText("class already exists");
        }
    }

    //if input is correct, deletes class together with all sequences coming from or to the class
    if (delClass != ""){
        vector<int>deleteIndex;
        int noRemoved = 0;
        for (int x=0; x< edited_seq->from.size(); x++){
            if (edited_seq->from.at(x) == delClass)
                deleteIndex.push_back(x);
        }
        for (int i=deleteIndex.size() - 1; i>-1; i--){
            int x = deleteIndex.at(i);
            deleteIndex.pop_back();
            edited_seq->from.erase(edited_seq->from.begin()+x);
            edited_seq->to.erase(edited_seq->to.begin()+x);
            edited_seq->method.erase(edited_seq->method.begin()+x);
            edited_seq->type.erase(edited_seq->type.begin()+x);
            edited_seq->iRelations.erase(edited_seq->iRelations.begin()+x);
            noRemoved++;
        }
        for (int x=0; x< edited_seq->to.size(); x++){
            if (edited_seq->to.at(x) == delClass)
                deleteIndex.push_back(x);
        }
        for (int i=deleteIndex.size() - 1; i>-1; i--){
            int x = deleteIndex.at(i);
            deleteIndex.pop_back();
            edited_seq->from.erase(edited_seq->from.begin()+x);
            edited_seq->to.erase(edited_seq->to.begin()+x);
            edited_seq->method.erase(edited_seq->method.begin()+x);
            edited_seq->type.erase(edited_seq->type.begin()+x);
            edited_seq->iRelations.erase(edited_seq->iRelations.begin()+x);
            noRemoved++;
        }

        for (sequenceClass* i : edited_seq->classes){
            i->updateSequenceNumber(-noRemoved);
        }

        bool found = false;
        int x = 0;
        for (sequenceClass *i : edited_seq->classes){
            if (delClass == i->name){
                delete(i);
                edited_seq->classes.erase(edited_seq->classes.begin() + x);
                found = true;
            }
            x++;
        }
        if (found){
            ui->label->setStyleSheet("QLabel {color: green;}");
            ui->label->setText("class removed");
        }
        else {
            ui->label->setStyleSheet("QLabel {color: red;}");
            ui->label->setText("failed to delete class");
        }
    }
}

void seq_edit_menu::on_deleteLast_clicked()
{
    //if there are any sequences, deletes last
    if (edited_seq->from.size() > 0){
        edited_seq->delete_last_sequence();
        for (sequenceClass* i : edited_seq->classes)
            i->updateSequenceNumber(-1);
        ui->label->setStyleSheet("QLabel {color: green;}");
        ui->label->setText("sequence removed");
    }
    else{
        ui->label->setStyleSheet("QLabel {color: red;}");
        ui->label->setText("cannot delete sequence");
    }
}
