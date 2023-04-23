/**
  * @file backend.cpp
  * @author Jakub Vaňo, Zuzana Hrkľová
  */
#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include "backend.h"
#include <algorithm>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

using namespace std;

diagram_classes::diagram_classes(QString name, vector<QString> attribute, vector<QString> method){
    //assign variables
    class_name = name;
    attributes = attribute;
    methods = method;
}

diagram_relations::diagram_relations(QString rel_type, QString rel_from, QString rel_where){
    //assign variables
    type = rel_type;
    from = rel_from;
    where = rel_where;
}

diagram_sequence::diagram_sequence(QString seq_from, QString seq_where, QString seq_type, QString seq_name, QString class_activ, QString class_deactiv){
    //assign variables
    from = seq_from;
    where = seq_where;
    type = seq_type;
    name = seq_name;
    activate = class_activ;
    deactivate = class_deactiv;
}

QJsonObject load_diagram(QString path){
    //opens file
    QFile inFile(path);
    inFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray data = inFile.readAll();
    inFile.close();

    QJsonParseError errorPtr;
    QJsonDocument doc = QJsonDocument::fromJson(data, &errorPtr);
    QJsonObject root = doc.object();
    return root;
}

bool check_class_diagram(QJsonObject data){
    vector<QString> names;

    //checks if JSON contains two arrays with correct names
    if (data.size() != 2)
        return false;
    if (data.value("classes").isUndefined())
        return false;
    if (data.value("relations").isUndefined())
        return false;
    if (!data.value("classes").isArray())
        return false;
    if (!data.value("relations").isArray())
        return false;

    //checks if classes array contains correct values
    QJsonArray allClasses = data.value("classes").toArray();
    for (int i = 0; i < allClasses.size(); i++){
        QJsonObject parseClass = allClasses[i].toObject();
        QJsonValue name = parseClass.value("name");
        names.push_back(name.toString());
        if (parseClass.empty())
            return false;
        if (parseClass.size() > 1 && parseClass.size() < 4){
            if (parseClass.value("name").isUndefined())
                return false;
            if (parseClass.value("attributes").isUndefined())
                return false;
            if (parseClass.size() == 3){
                if (parseClass.value("methods").isUndefined())
                    return false;
                if (!parseClass.value("attributes").isArray())
                    return false;
                if (!parseClass.value("methods").isArray())
                    return false;
            }
        }
        else
            return false;

        //checks if attributes array contains correct values
        QJsonArray attributes = parseClass.value("attributes").toArray();
        for (int y = 0; y < attributes.size(); y++){
            QJsonValue attribute = attributes[y];
            QString tmp = attribute.toString();
            if (tmp[0] != '-' && tmp[0] != '+' && tmp[0] != '~' && tmp[0] != '#')
                return false;
        }
    }

    //checks if relations array contains correct values
    QJsonArray relations = data.value("relations").toArray();
    for (int i = 0; i < relations.size(); i++){
        QJsonObject rel = relations[i].toObject();
        if (rel.size() == 3){
            if (rel.value("type").isUndefined())
                return false;
            if (rel.value("from").isUndefined())
                return false;
            if (rel.value("where").isUndefined())
                return false;
        }
        else
            return false;

        QJsonValue from = rel.value("from");
        QJsonValue where = rel.value("where");
        QJsonValue type = rel.value("type");
        if (type.toString() != "association" && type.toString() != "composition" && type.toString() != "inheritance" && type.toString() != "aggregation")
            return false;
        if (find(names.begin(), names.end(), from.toString()) != names.end() && find(names.begin(), names.end(), where.toString())!= names.end()){
        }
        else
            return false;
    }
    return true;
}

vector<diagram_classes> save_classes(QJsonObject data){
    vector<diagram_classes> ret;
    QJsonArray allClasses = data.value("classes").toArray();
    //iterates through every class and saves its values
    for (int i = 0; i < allClasses.size(); i++){
        vector<QString>classAttributes;
        vector<QString>classMethods;
        QJsonObject parseClass = allClasses[i].toObject();
        QJsonValue name = parseClass.value("name");
        QJsonArray attributes = parseClass.value("attributes").toArray();
        //iterates through all attributes
        for (int y = 0; y < attributes.size(); y++){
            QJsonValue attribute = attributes[y];
            classAttributes.push_back(attribute.toString());
        }
        QJsonArray methods = parseClass.value("methods").toArray();
        //iterates through all methods
        for (int x = 0; x < methods.size(); x++){
            QJsonValue method = methods[x];
            classMethods.push_back(method.toString());
        }
        diagram_classes nclass(name.toString(), classAttributes, classMethods);
        ret.push_back(nclass);
    }
    return ret;
}

vector<diagram_relations> save_relations(QJsonObject data){
    vector<diagram_relations> ret;
    QJsonArray relations = data.value("relations").toArray();
    //iterates through every relation and saves its values
    for (int i = 0; i < relations.size(); i++){
        QJsonObject rel = relations[i].toObject();
        QJsonValue type = rel.value("type");
        QJsonValue from = rel.value("from");
        QJsonValue where = rel.value("where");
        diagram_relations nrelation(type.toString(), from.toString(), where.toString());
        ret.push_back(nrelation);
    }
    return ret;
}

bool check_sequence_diagram(QJsonObject data){
    //checks if JSON contains correct number and names of arrays
    if (data.size() != 2)
        return false;
    if (data.value("classes").isUndefined())
        return false;
    if (data.value("sequences").isUndefined())
        return false;
    if (!data.value("classes").isArray())
        return false;
    if (!data.value("sequences").isArray())
        return false;

    //checks if list of classes contains string only
    vector<QString> seq_classes;
    QJsonArray allClasses = data.value("classes").toArray();
    for (int i = 0; i < allClasses.size(); i++){
        if (allClasses[i].isString())
            seq_classes.push_back(allClasses[i].toString());
        else
            return false;
    }

    //iterates through all sequences and checks them
    QJsonArray allSequences = data.value("sequences").toArray();
    for (int i = 0; i < allSequences.size(); i++){
        QJsonObject parseSequence = allSequences[i].toObject();
        QString activ;
        QString deactiv;
        QString from;
        QString where;
        QString type;
        //checks if sequence isnt empty
        if (parseSequence.isEmpty())
            return false;
        //checks if sequence has correct number of arguments and if they have right name and type
        if (parseSequence.size() > 3 && parseSequence.size() < 7){
            if (parseSequence.value("from").isUndefined())
                return false;
            if (parseSequence.value("where").isUndefined())
                return false;
            if (parseSequence.value("type").isUndefined())
                return false;
            if (parseSequence.value("name").isUndefined())
                return false;

            if (parseSequence.value("from").isString())
                from = parseSequence.value("from").toString();
            else
                return false;
            if (parseSequence.value("where").isString())
                where = parseSequence.value("where").toString();
            else
                return false;
            if (parseSequence.value("type").isString())
                type = parseSequence.value("type").toString();
            else
                return false;

            if (!from.isEmpty()){
                if (find(seq_classes.begin(), seq_classes.end(), from) != seq_classes.end()){
                }
                else
                    return false;
            }
            if (!where.isEmpty()){
                if (find(seq_classes.begin(), seq_classes.end(), where) != seq_classes.end()){
                }
                else
                    return false;
            }
            if (type != "syn_request" && type != "response" && type != "asyn_request")
                return false;

            if (parseSequence.size() == 5){
                if (!parseSequence.value("activate").isUndefined() && parseSequence.value("activate").isString())
                    activ = parseSequence.value("activate").toString();
                else if (!parseSequence.value("deactivate").isUndefined() && parseSequence.value("deactivate").isString())
                    deactiv = parseSequence.value("deactivate").toString();
                else
                    return false;
                if (!activ.isEmpty()){
                    if (find(seq_classes.begin(), seq_classes.end(), activ) != seq_classes.end()){
                    }
                    else
                        return false;
                }
                if (!deactiv.isEmpty()){
                    if (find(seq_classes.begin(), seq_classes.end(), deactiv) != seq_classes.end()){
                    }
                    else
                        return false;
                }
            }

            if (parseSequence.size() == 6){
                if (!parseSequence.value("activate").isUndefined() && parseSequence.value("activate").isString() && !parseSequence.value("deactivate").isUndefined() && parseSequence.value("deactivate").isString()){
                    activ = parseSequence.value("activate").toString();
                    deactiv = parseSequence.value("deactivate").toString();
                }
                else
                    return false;
                if (!activ.isEmpty()){
                    if (find(seq_classes.begin(), seq_classes.end(), activ) != seq_classes.end()){
                    }
                    else
                        return false;
                }
                if (!deactiv.isEmpty()){
                    if (find(seq_classes.begin(), seq_classes.end(), deactiv) != seq_classes.end()){
                    }
                    else
                        return false;
                }
            }
        }
        else
            return false;

    }
    return true;
}

void save_sequence_diagram(QJsonObject data, everything *save){
    vector<QString> tmp;
    vector<diagram_sequence> tmpClass;
    QJsonArray classList = data.value("classes").toArray();
    //saves classes used in sequence diagram into one vector
    for (int i = 0; i < classList.size(); i++){
        QString name = classList[i].toString();
        tmp.push_back(name);
    }
    save->sequenceClasses.push_back(tmp);

    //iterates through every sequence and save its values
    QJsonArray allSequences = data.value("sequences").toArray();
    for (int i = 0; i < allSequences.size(); i++){
        QString name = "";
        QString type = "";
        QString from = "";
        QString where = "";
        QString activ = "";
        QString deactiv = "";
        QJsonObject parseSequence = allSequences[i].toObject();
        name = parseSequence.value("name").toString();
        type = parseSequence.value("type").toString();
        from = parseSequence.value("from").toString();
        where = parseSequence.value("where").toString();
        if (!parseSequence.value("activate").isUndefined())
            activ = parseSequence.value("activate").toString();
        if (!parseSequence.value("deactivate").isUndefined())
            deactiv = parseSequence.value("deactivate").toString();
        diagram_sequence nSeq(from, where, type, name, activ, deactiv);
        tmpClass.push_back(nSeq);
    }
    save->sequences.push_back(tmpClass);
}

vector<QString> is_consistent_class(everything *data, int cnt){
    vector<QString> iClass;
    bool found;

    //checks if classes used in sequence diagram are consistent with class diagram
    for (QString i : data->sequenceClasses[cnt]){
        found = false;
        for (newclass* j : data->drawnClasses){
            if (i == j->name)
                found = true;
        }
        if (!found)
            iClass.push_back(i);
    }
    return iClass;
}

vector<QString> is_consistent_method(everything *data, int cnt){
    vector<QString> iMethod;
    bool found;
    QString name;
    QString method;

    //checks if methods used in sequence diagram are consistent with class diagram
    for(diagram_sequence i : data->sequences[cnt]){
        found = false;
        name = i.from;
        method = i.name;
        for (newclass* j : data->drawnClasses){
            if (name == j->name){
                for (QString k : j->methods){
                     if (method == k)
                        found = true;
                }
            }
        }
        if (!found)
            iMethod.push_back(i.name);
    }
    return iMethod;
}

vector<bool> is_consistent_sequence(everything *data, int cnt){
    vector<bool> iRelation;
    QString from;
    QString where;
    bool found;

    //checks if sequences used in sequence diagram are consistent with class diagram
    for (diagram_sequence i : data->sequences[cnt]){
        found = false;
        from = i.from;
        where = i.where;
        vector<newline*> lineF;
        vector<newline*> lineW;

        for (newclass* j : data->drawnClasses){
            if (from == j->name){
                lineF = j->lines;
            }
        }

        for (newclass* j : data->drawnClasses){
            if (where == j->name){
                lineW = j->lines;
            }
        }

        for (newline* j : lineF){
            for (newline* k :lineW){
                if (j == k){
                    found = true;
                }
            }
        }

        if (found)
            iRelation.push_back(true);
        else
            iRelation.push_back(false);
    }
    return iRelation;
}
