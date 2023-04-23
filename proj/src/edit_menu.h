/**
  * @file edit_menu.h
  * @author Jakub Vaňo, Zuzana Hrkľová
  * @brief header for class diagram editing window
  */
#ifndef EDIT_MENU_H
#define EDIT_MENU_H

#include <QDialog>
#include "new_class.h"
#include "backend.h"

namespace Ui {
class edit_menu;
}

class edit_menu : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief edit_menu Constructs editor window
     * @param parent
     */
    explicit edit_menu(QWidget *parent = 0);
    ~edit_menu();

    newclass *edited_class;

private slots:
    /**
     * @brief on_Submit_clicked applies given changes
     */
    void on_Submit_clicked();

private:
    Ui::edit_menu *ui;
    QGraphicsScene *scene;
    newline *nLine;
};

#endif // EDIT_MENU_H
