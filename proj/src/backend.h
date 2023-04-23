/**
  * @file backend.h
  * @author Jakub Vaňo, Zuzana Hrkľová
  * @brief Header file for backend
  */

#ifndef BACKEND
#define BACKEND
#include "new_class.h"
#include "createsequences.h"

#include <QString>
#include <list>
#include <vector>
#include <QJsonObject>

using namespace std;

class newclass;
class createSequences;

class diagram_classes{
    public:
        /**
         * @brief Constructs parsed JSON class diagram input
         *
         * @param name name of a class
         * @param attribute vector of class attributes
         * @param method vector of class methods
         */
        diagram_classes(QString name, vector<QString> attribute, vector<QString> method);

        QString class_name;
        vector<QString>attributes;
        vector<QString>methods;
};

class diagram_relations{
    public:
        /**
         * @brief Constructs parsed JSON class relations input
         *
         * @param rel_type type of relation (association, inheritence, aggregation, composition)
         * @param rel_from relation starting class
         * @param rel_where relation ending class
         */
         diagram_relations(QString rel_type, QString rel_from, QString rel_where);

        QString type;
        QString from;
        QString where;      
};

class diagram_sequence{
    public:
        /**
         * @brief Construts parsed JSON sequence diagram input
         *
         * @param from sequence start class
         * @param where sequence end class
         * @param type type of sequence (syn_request, asyn_request, response)
         * @param name name of used method
         * @param activate name of activated class (optional)
         * @param deactivate name of deactivated class (optional)
         */
        diagram_sequence(QString from, QString where, QString type, QString name, QString activate, QString deactivate);

        QString activate;
        QString deactivate;
        QString from;
        QString where;
        QString type;
        QString name;       
};

/**
 * @brief The everything struct holds data pointers so they are accesible where needed
 */
struct everything {
    /**
     * @brief sequences from JSON input used for creating sequence diagrams
     */
    vector<vector<diagram_sequence>> sequences;
    /**
     * @brief sequenceClasses from JSON input used for creating sequence diagrams
     */
    vector<vector<QString>> sequenceClasses;
    /**
     * @brief drawnClasses holds pointers to all displayed class diagram classes
     */
    vector<newclass*> drawnClasses;
    /**
     * @brief drawnSequences holds pointers to all displayed sequence diagrams
     */
    vector<createSequences*> drawnSequences;
    /**
     * @brief classesscene is a pointer to class diagram scene
     */
    QGraphicsScene *classesscene;
};

/**
 * @brief load_diagram processes input path
 *
 * @param path path to the JSON input file
 * @return unparsed JSON file if opened successfully
 */
QJsonObject load_diagram(QString path);

/**
 * @brief check_class_diagram checks form of input JSON file
 *
 * @param data JSON file
 * @return True if well-formed
 * @return False if not well-formed
 */
bool check_class_diagram(QJsonObject data);

/**
 * @brief save_classes saves parsed class
 *
 * @param data JSON file
 * @return vector of saved classes
 */
vector<diagram_classes> save_classes(QJsonObject data);

/**
 * @brief save_relations saves parsed class relations
 *
 * @param data JSON file
 * @return vector of saved class relations
 */
vector<diagram_relations> save_relations(QJsonObject data);

/**
 * @brief check_sequence_diagram checks form of input JSON file
 *
 * @param data JSON file
 * @return True if well-formed
 * @return False if not well-formed
 */
bool check_sequence_diagram(QJsonObject data);

/**
 * @brief save_sequence_diagram saves parsed sequence diagram
 *
 * @param data JSON file
 * @param save struct where sequence diagram is saved
 */
void save_sequence_diagram(QJsonObject data, everything *save);

/**
 * @brief is_consistent_class finds inconsistent classes in sequence diagram
 *
 * @param data structure with class diagram and sequence diagrams
 * @param cnt is index of checked sequence diagram
 * @return vector of inconsistent classes in sequence diagram
 */
vector<QString> is_consistent_class(everything *data, int cnt);

/**
 * @brief is_consistent_method finds inconsistent methods used in sequence diagram
 *
 * @param data structure with class diagram and sequence diagrams
 * @param cnt is index of checked sequence diagram
 * @return vector of incosistent methods used in sequence diagram
 */
vector<QString> is_consistent_method(everything *data, int cnt);

/**
 * @brief is_consistent_sequence finds inconsistent sequences used in sequence diagram
 *
 * @param data structure with class diagram and sequence diagram
 * @param cnt is index of checked sequence diagram
 * @return vector of bool values, true if sequence is consistent and false if inconsistent
 */
vector<bool> is_consistent_sequence(everything *data, int cnt);

#endif // BACKEND

