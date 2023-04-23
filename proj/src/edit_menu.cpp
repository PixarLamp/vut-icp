/**
  * @file edit_menu.cpp
  * @author Jakub Vaňo, Zuzana Hrkľová
  */

#include "edit_menu.h"
#include "ui_edit_menu.h"
#include <algorithm>
#include <vector>
#include <QLabel>

using namespace std;

edit_menu::edit_menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit_menu)
{
    ui->setupUi(this);
    ui->EditName->setPlaceholderText("new class name");
    ui->AddAttrib->setPlaceholderText("(+,-,~,#) + name");
    ui->AddMethod->setPlaceholderText("method name");
    ui->RemoveAttrib->setPlaceholderText("(+,-,~,#) + name");
    ui->RemoveMethod->setPlaceholderText("method name");
    ui->where->setPlaceholderText("dest class name");
    ui->type->setPlaceholderText("relation type");
    ui->whereR->setPlaceholderText("dest class name");
}

edit_menu::~edit_menu()
{
    delete ui;
}

void edit_menu::on_Submit_clicked()
{
    QString addA = ui->AddAttrib->text();
    //if add attribute is not empty and is correct, ads to class
    if (addA != ""){
        if (std::find(edited_class->attributes.begin(), edited_class->attributes.end(), addA) != edited_class->attributes.end()) {
            ui->label_5->setStyleSheet("QLabel {color: red;}");
            ui->label_5->setText("Already exists");
        }
          else {
            ui->label_5->setStyleSheet("QLabel {color: green;}");
            ui->label_5->setText("Saved");
            edited_class->attributes.push_back(addA);
        }
    }
    QString delA = ui->RemoveAttrib->text();
    //if del attribute is not empty and is in class, it is removed from class
    if (delA != ""){
        if (std::find(edited_class->attributes.begin(), edited_class->attributes.end(), delA) != edited_class->attributes.end()) {
            ui->label_5->setStyleSheet("QLabel {color: green;}");
            ui->label_5->setText("Saved");
            edited_class->attributes.erase(std::remove(edited_class->attributes.begin(), edited_class->attributes.end(), delA), edited_class->attributes.end());
        }
        else {
            ui->label_5->setStyleSheet("QLabel {color: red;}");
            ui->label_5->setText("Not existing attribute");
        }
    }
    QString addM = ui->AddMethod->text();
    //if add method is not empty and is correct, adds method in class
    if (addM != ""){
        if (std::find(edited_class->methods.begin(), edited_class->methods.end(), addM) != edited_class->methods.end()) {
            ui->label_5->setStyleSheet("QLabel {color: red;}");
            ui->label_5->setText("Already exists");
        }
        else {
            ui->label_5->setStyleSheet("QLabel {color: green;}");
            ui->label_5->setText("Saved");
            edited_class->methods.push_back(addM);
        }
    }
    QString delM = ui->RemoveMethod->text();
    //if del method is not empty and is in class, removes method from class
    if (delM != ""){
        if (std::find(edited_class->methods.begin(), edited_class->methods.end(), delM) != edited_class->methods.end()) {
            ui->label_5->setStyleSheet("QLabel {color: green;}");
            ui->label_5->setText("Saved");
            edited_class->methods.erase(std::remove(edited_class->methods.begin(), edited_class->methods.end(), delM), edited_class->methods.end());
        }
        else{
            ui->label_5->setStyleSheet("QLabel {color: red;}");
            ui->label_5->setText("Not existing method");
        }
    }
    QString editName = ui->EditName->text();
    QString old_name = edited_class->name;
    //if edit name is not empty, changes class name to given string
    if (editName != ""){
        for (createSequences* i : edited_class->data->drawnSequences){
            for (sequenceClass* j : i->classes){
                if (old_name == j->name)
                    j->name = editName;
                vector<QString> tmp;
                for (int j = 0; j < i->from.size(); j++){
                    if(i->from.at(j) == old_name)
                        tmp.push_back(editName);
                    else
                        tmp.push_back(i->from.at(j));
                }
                i->from = tmp;
                tmp.clear();
                for (int j = 0; j < i->to.size(); j++){
                    if(i->to.at(j) == old_name)
                        tmp.push_back(editName);
                    else
                        tmp.push_back(i->to.at(j));
                }
                i->to = tmp;
                tmp.clear();
                for (int j = 0; j < i->activate.size(); j++){
                    if(i->activate.at(j) == old_name)
                        tmp.push_back(editName);
                    else
                        tmp.push_back(i->activate.at(j));
                }
                i->activate = tmp;
                tmp.clear();
                for (int j = 0; j < i->deactivate.size(); j++){
                    if(i->deactivate.at(j) == old_name)
                        tmp.push_back(editName);
                    else
                        tmp.push_back(i->deactivate.at(j));
                }
                i->deactivate = tmp;
                tmp.clear();
            }
        }
        edited_class->name = editName;
        ui->label_5->setStyleSheet("QLabel {color: green;}");
        ui->label_5->setText("Saved");
    }

    QString newRelationTo = ui->where->text();
    QString newRelationType = ui->type->text();
    newclass *endClass;
    //if input is correct,creates new relation
    if ((newRelationTo != "") && (newRelationType !="")){
        bool found = false;
        for (newclass *y : edited_class->data->drawnClasses){
            if (y->name == newRelationTo){
                endClass = y;
                found = true;
            }
        }
        if (found){
            nLine = new newline(edited_class->classposition, endClass->classposition, newRelationType);
            edited_class->addlinetoclass(nLine, true);
            endClass->addlinetoclass(nLine, false);
            edited_class->data->classesscene->addItem(nLine);
        }
        else{
            ui->label_5->setStyleSheet("QLabel {color:red;}");
            ui->label_5->setText("class not found");
        }
    }
    QString delRelationTo = ui->whereR->text();
    newclass* delRelClass;
    //if input is correct and relation exists, its removed
    if (delRelationTo != ""){
        bool found = false;
        for(newclass* it : edited_class->data->drawnClasses){
            if (it->name == delRelationTo){
                delRelClass = it;
                found = true;
            }
        }
        if (found){
            if(delRelClass != edited_class){
                vector<int> indexFound;
                for(int i=0; i< edited_class->lines.size(); i++){
                    for (int j=0; j<delRelClass->lines.size(); j++){
                        if (edited_class->lines.at(i) == delRelClass->lines.at(j)){
                            delRelClass->lines.erase(delRelClass->lines.begin()+j);
                            delRelClass->line_startpoint.erase(delRelClass->line_startpoint.begin()+j);
                            indexFound.push_back(i);
                        }
                    }
                }
                for(int i = indexFound.size()-1; i>-1; i--){
                    int index = indexFound.at(i);
                    indexFound.pop_back();
                    newline* line = edited_class->lines.at(index);
                    edited_class->lines.erase(edited_class->lines.begin()+index);
                    edited_class->line_startpoint.erase(edited_class->line_startpoint.begin()+index);
                    edited_class->data->classesscene->removeItem(line);
                    delete(line);
                }
                edited_class->update();
                delRelClass->update();
                ui->label_5->setStyleSheet("QLabel {color:green;}");
                ui->label_5->setText("Saved");
            }
            else{
                ui->label_5->setStyleSheet("QLabel {color:red;}");
                ui->label_5->setText("action not possible");
            }
        }
        else{
            ui->label_5->setStyleSheet("QLabel {color:red;}");
            ui->label_5->setText("class not found");
        }
    }
}
