/**
  * @file seq_edit_menu.h
  * @author Jakub Vaňo, Zuzana Hrkľová
  * @brief header for sequence diagram editing window
  */
#ifndef SEQ_EDIT_MENU_H
#define SEQ_EDIT_MENU_H

#include "createsequences.h"
#include <QDialog>

namespace Ui {
class seq_edit_menu;
}

class seq_edit_menu : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief seq_edit_menu Constructs editor window
     *
     * @param parent
     */
    explicit seq_edit_menu(QWidget *parent = 0);
    ~seq_edit_menu();
    createSequences *edited_seq;

private slots:
    /**
     * @brief on_Submit_clicked applies given changes
     */
    void on_Submit_clicked();

    /**
     * @brief on_deleteLast_clicked calls for deletion of last sequence and removes from displayed sequence diagram
     */
    void on_deleteLast_clicked();

private:
    Ui::seq_edit_menu *ui;
    QGraphicsScene *scene;
};

#endif // SEQ_EDIT_MENU_H
