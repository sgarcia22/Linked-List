///Name: Samantha Garcia
///Section: 1133
///TA: Kevin Neumann
///Project: pa3
///Description: Creates a stack and uses lexical analysis for the inputed code

#include "pa3.h"
#include <iostream>
#include <string>

int main () {

    string fileName;

    cout << "Please enter the name of the input file: \n";
    cin >> fileName;


    //Creates an object and executes appropriate functions
    pa3* obj = new pa3(fileName);
    obj->seperateCode();
    obj->printFields();

    return 0;
}

