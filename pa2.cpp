//Name: Samantha Garcia
//Section: 1133
//TA: Kevin Neumann
//Project: pa2
//Description: Creates a Linked List that can add nodes, or pages, and delete them in a best fit or worst fit way

#include "pa2.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctype.h>

int main (int argc, char* argv[]) {

    string algorithmChoice;

    //Making sure the command line will take in the appropriate arguments
    if (argc != 2) {
        cout << argv[0];
    }
    else {
        //Takes in command line argument
        algorithmChoice = argv[1];

    }

    int bestOrWorst = 0;

    //Sees which command line argument was passed in and determines which fit algorithm to use
    if (algorithmChoice == "best") {
        cout << "Best argument passed\n\n";
        bestOrWorst = 1;
    }
    else if (algorithmChoice =="worst") {
        cout << "Worst argument passed\n\n";
        bestOrWorst = 2;
    }
    else {
        cout << "Invalid arguments\n\n";
        return 0;
    }

    //Creates a new object Linked List
    pa2* obj = new pa2(32);

    cout << "1. Add program\n";
    cout << "2. Kill Program\n";
    cout << "3. Fragmentation\n";
    cout << "4. Print memory\n";
    cout << "5. Exit\n";


    int choice;
    string programName;
    double programSize;

    //Menu While Loop; exits when user presses 5
    while (choice != 5) {

        cout << "\nchoice - ";
        cin >> choice;

        if (!cin.good()) {
            cout << "Error: Not an integer\n";
            return 0;
        }

        //Choice for adding a program/node
        if (choice == 1) {
                cout << "\nProgram name - ";
                cin >> programName;
                    if (!cin.good()) {
                        cout << "Error: Not a string\n";
                        return 0;
                    }
                cout << "\nProgram size (KB) - ";
                cin >> programSize;
                 if (!cin.good()) {
                        cout << "Error: Not an integer\n";
                        return 0;
                    }
                cout << endl;
                obj->addNode(programName, programSize, bestOrWorst);
        }
        //Choice for removing/killing a program/node
         if (choice == 2) {
                cout << "\nProgram name - ";
                cin >> programName;
                 if (!cin.good()) {
                        cout << "Error: Not a string\n";
                        return 0;
                    }
                cout << endl;
                obj->deleteNode(programName);
         }
         //Prints the number of fragments in the node
        if (choice == 3) {
                cout << endl;
                obj->fragments();
        }

        //Prints the nodes
        if (choice == 4) {
            cout << endl;
            obj->printNodes();
        }

    }

    return 0;
}
