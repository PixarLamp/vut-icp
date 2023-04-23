ICP Project - editace diagramu trid a sekvencnych diagramu

Authors:
Jakub Vaňo - xvanoj00
Zuzana Hrkľová - xhrklo00

Help:
make - compiles program and creates executable in bin folder
make run - compiles and runs program
make doxygen - creates doxygen documentation in doc folder
make clean - deletes all files and folders created with make
make pack - creates zip of all project files 

Usage:
To display class diagram insert path to JSON input file and press "Insert Class Diagram" button.
Displayed classes can be moved by dragging with mouse.
Class edit menu can be opened by right mouse button double clicking on class you wish to edit.
To display sequence diagram insert path to JSON input file and press "Insert Sequence Diagram" button, this opens new window displaying sequence diagram.
Sequence diagram edit menu can be opened by right mouse button double clicking on sequence diagram.
To add new sequence in edit menu you need to correctly fill first four text boxes.
Activation/deactivation is optional in adding new sequence.
To save picture of diagram put desired name in text box e.g. image.

Implementation:
Initial display of class diagram and sequence diagrams is functional.
Color distinguishing of inconsistencies in sequence diagram is functional.
Saving image of diagrams is functional and saves png of diagram.
Editing of class diagram from edit menu window is functional.
Adding and deleting class in class diagram is functional.
Editing of sequence diagram in edit menu window is functional except for deleting last sequence which distorts activate axis.
Undo functionality is not implemented.
Color distinguishing of generalized class methods is not implemented.
