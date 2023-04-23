/**
  * @file main.cpp
  * @author Jakub Vaňo, Zuzana Hrkľová
  */

#include "class_diagram.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    class_diagram w;
    w.showMaximized();

    return a.exec();
}
