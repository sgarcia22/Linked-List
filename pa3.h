///Name: Samantha Garcia
///Section: 1133
///TA: Kevin Neumann
///Project: pa3
///Description: Creates a stack and uses lexical analysis for the inputed code

#ifndef PA3_H
#define PA3_H

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

//Implementing a stack
class stackImplementation {

public:

       static void push(string input, vector<string>& vectorType) {

            vectorType.push_back(input);

        }

        //Removes the last element in the vector
        static string pop(vector<string>& vectorType) {

            string item = vectorType.back();
            vectorType.pop_back();
            return item;

         }

};

class pa3
{

    public:

        //Vector to put all of the words in the file
        vector<string> totalFile;

        //Vectors to put all the separate categories of code
        vector<string> keywords;
        vector<string> identifiers;
        vector<string> constants;
        vector<string> operators;
        vector<string> delimeters;
        vector<string> wrongInput;
        vector<string> parenthesis;

        //Constructor
        pa3 (string fileName) {

            string word;

            ifstream userFile;

            string fullFileName = "\"" + fileName + "\"";

            userFile.open(fileName);

            if (userFile) {

                while (userFile >> word) {

                    stackImplementation::push(word, totalFile);

                }


            }
            //If the file does not exist
            else {
                cout << "Not a valid file\n";
                return;
            }

        }

        void seperateCode() {


        vector<string> seperatedCode;

            //Using an iterator to go through the vector
            for (vector<string>::iterator it = totalFile.begin(); it != totalFile.end(); ++it) {

                //Check for Keywords
                if (*it == "BEGIN" || *it == "END" || *it == "FOR") {
                    stackImplementation::push(*it,  keywords);
                }

                //Checks for Invalid input: Syntax Error
                else {

                    tokenizeString(*it);
                }
            }
        }

        //Method to tokenize string to make sure there aren't any other elements inside of the string
        //If there is an element that is not common to the string class then I will stackImplementation::push it to the top of the
        //Stack/Vector in which it belongs
        void tokenizeString(string input) {

            //String to temporarily store the character/string
            string tempConstant;

            //Boolean to determine if the string is a syntax error
            bool parsed = false;

            for (unsigned int i = 0; i < input.size(); ++i) {

                //Checks for operators, delimeters, and constants by comparing each character to the alphabet
                if ((input[i] != ('a')) || (input[i] != ('b')) || (input[i] != ('c')) || (input[i] != ('d')) || (input[i] != ('e'))
                    || (input[i] != ('f')) || (input[i] != ('g')) || (input[i] != ('h')) || (input[i] != ('i')) || (input[i] != ('j'))
                    || (input[i] != ('k')) || (input[i] != ('l')) || (input[i] != ('m')) || (input[i] != ('n')) || (input[i] != ('o'))
                    || (input[i] != ('p')) || (input[i] != ('q')) || (input[i] != ('r')) || (input[i] != ('s')) || (input[i] != ('t'))
                    || (input[i] != ('u')) || (input[i] != ('v')) || (input[i] != ('w')) || (input[i] != ('x')) || (input[i] != ('y'))
                    || (input[i] != ('z'))) {

                    if (input[i] == '+' && input[i + 1] == '+') {

                        tempConstant = input.substr(i, 2);
                        stackImplementation::push(tempConstant, operators);
                        tempConstant.clear();
                        parsed = true;
                        i++;

                    }

                    if (((input[i] == '+')  && (input[i-1] != '+')) || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '=') {

                        tempConstant = input.substr(i, 1);
                        stackImplementation::push(tempConstant,  operators);
                        tempConstant.clear();
                        parsed = true;

                    }

                    if(input[i] == ',' || input[i] == ';') {
                        tempConstant = input.substr(i, 1);
                        stackImplementation::push(tempConstant,  delimeters);
                        tempConstant.clear();
                        parsed = true;

                    }

                    //Checks for parenthesis
                    if (input[i] == '(' || input[i] == ')') {
                        tempConstant = input.substr(i, 1);
                        stackImplementation::push(tempConstant, parenthesis);
                        tempConstant.clear();
                        parsed = true;
                    }

                    //Checks for constants
                    if (isdigit(input[i])) {

                        tempConstant = input[i];
                        while (i < input.size()) {

                            i++;
                            if (isdigit(input[i]) == 1) {
                                tempConstant += input[i];
                            }
                            else {
                                i--;
                                break;
                            }

                        }
                        if (!(tempConstant.empty())) {

                            stackImplementation::push(tempConstant,  constants);

                        }

                        tempConstant.clear();
                        parsed = true;

                    }
                }

                //Checks for identifiers
                if ((input[i] == ('a')) || (input[i] == ('b')) || (input[i] == ('c')) || (input[i] == ('d')) || (input[i] == ('e'))
                    || (input[i] == ('f')) || (input[i] == ('g')) || (input[i] == ('h')) || (input[i] == ('i')) || (input[i] == ('j'))
                    || (input[i] == ('k')) || (input[i] == ('l')) || (input[i] == ('m')) || (input[i] == ('n')) || (input[i] == ('o'))
                    || (input[i] == ('p')) || (input[i] == ('q')) || (input[i] == ('r')) || (input[i] == ('s')) || (input[i] == ('t'))
                    || (input[i] == ('u')) || (input[i] == ('v')) || (input[i] == ('w')) || (input[i] == ('x')) || (input[i] == ('y'))
                    || (input[i] == ('z'))) {

                    tempConstant = input[i];
                    while (i < input.size()) {

                        i++;
                        if (islower(input[i])) {
                            tempConstant += input[i];
                        }
                        else {
                            i--;
                            break;
                        }

                    }
                    if (!(tempConstant.empty())) {

                        stackImplementation::push(tempConstant,  identifiers);
                        tempConstant.clear();
                        parsed = true;

                    }
               }
            }
            if (parsed == false) {
                stackImplementation::push(input, wrongInput);
            }

        }

        void printFields() {



            //Storing values in a temporary vector to check them so as to not print out duplicates
            vector<string> temp;

            cout << "\nThe depth of the nested loop(s) is " << fieldDepth();

            cout << "\n\nKeywords: ";
            removeDuplicates(temp, keywords);
            for (vector<string>::iterator it = temp.begin(); it != temp.end(); ++it) {

                cout << *it << " ";
            }

            cout << "\nIdentifier: ";
            removeDuplicates(temp, identifiers);
            for (vector<string>::iterator it = temp.begin(); it != temp.end(); ++it) {
                cout << *it << " ";
            }

            cout << "\nConstant: ";
            removeDuplicates(temp, constants);
            for (vector<string>::iterator it = temp.begin(); it != temp.end(); ++it) {
                cout << *it << " ";
            }

            cout << "\nOperators: ";
            removeDuplicates(temp, operators);
            for (vector<string>::iterator it = temp.begin(); it != temp.end(); ++it) {
                cout << *it << " ";
            }

            cout << "\nDelimiter: ";
            removeDuplicates(temp, delimeters);
            for (vector<string>::iterator it = temp.begin(); it != temp.end(); ++it) {
               cout << *it << " ";
            }

            syntaxErrors();

            cout << "\n\nSyntax Error(s): ";
            removeDuplicates(temp, wrongInput);
            if (temp.empty()) {
                cout << "NA";
            }
            else {
                for (vector<string>::iterator it = temp.begin(); it != temp.end(); ++it) {
                   cout << *it << " ";
                }
            }

        }

        //Method to remove the duplicates
        void removeDuplicates(vector<string>& temp, vector<string>& choice) {

            temp.clear();
            size_t distanceMeasured;

            //Removes duplicates by popping the last element in the stack if it was already found before using the vector find function (and distance to determine it's position)
            for (vector<string>::iterator it = choice.begin(); it != choice.end(); ++it) {
                stackImplementation::push(*it, temp);
                distanceMeasured = distance(temp.begin(),(find(temp.begin(), temp.end(), *it)));
                if ((find(temp.begin(), temp.end(), *it) != temp.end()) && (distanceMeasured != (temp.size() - 1)))
                    stackImplementation::pop(temp);
            }

        }

        //This calculates the for loop field depth
        void syntaxErrors() {

            int forLoops = 0;
            int beginStatements = 0;
            int endStatements = 0;

            //Temporary String
            string tempConstant;
            //Keeps a counter
            unsigned int counter = 0;

            string nextValue;
            string prevValue;

            //This vector will remove elements that are used
            vector<string> tempKeywords = keywords;

            counter = 0;

            //Checks for valid keyword use
            for (vector<string>::iterator it = keywords.begin(); it != keywords.end(); ++it) {

                if (counter < (keywords.size() - 1)) {

                    if (*it == "FOR" && *next(it) != "BEGIN") {
                        forLoops++;
                    }
                    else if (*it == "FOR" && *next(it) == "BEGIN") {
                        forLoops++;
                        beginStatements++;
                    }

                }

                else if (counter == (keywords.size() - 1))
                    if (*it == "FOR")
                        forLoops++;

                if (*it == "END")
                    endStatements++;

                counter++;

            }
            //Checks if the number of begin and end statements exceeds twice the for loop statements.
            if ((2 * forLoops) != (beginStatements + endStatements)) {
                if (beginStatements > endStatements)
                    stackImplementation::push("END", wrongInput);
                if (beginStatements < endStatements) {
                    stackImplementation::push("BEGIN", wrongInput);
                }
                if (beginStatements == 0 && endStatements == 0 && (forLoops > 0)) {
                    for (int i = 0; i < forLoops; ++i) {
                        stackImplementation::push("BEGIN", wrongInput);
                        stackImplementation::push("END", wrongInput);
                    }
                }
            }



            counter = 0;
            //Checks for parenthesis matches

            for (vector<string>::iterator it = parenthesis.begin(); it != parenthesis.end(); ++it) {

                 if (counter == 0) {
                    if ((*it == "(") && (*next(it) != ")"))
                        stackImplementation::push (*it, wrongInput);
                    if (*it == ")")
                        stackImplementation::push (*it, wrongInput);
                 }
                 else if (counter == (parenthesis.size() - 1)) {
                    if ((*it == ")") && (*prev(it) != "("))
                        stackImplementation::push (*it, wrongInput);
                    if (*it == "(")
                        stackImplementation::push (*it, wrongInput);
                 }
                 else {
                    if ((*it == "(") && (*next(it) != ")"))
                        stackImplementation::push (*it, wrongInput);

                     if ((*it == ")") && (*prev(it) != "("))
                        stackImplementation::push (*it, wrongInput);
                }
                counter++;
           }

           counter = 0;
        }

        //This function shows if something is missing from the code that would not make it compile normally
        int fieldDepth() {

            unsigned int counter = 0;

            //Counts the depth of the floor loop
            int forLoopDepthCounter = 0;

            //Temp vector so that I can remove "END" keyword without it reflecting on the actual keywords vector
            vector<string> keywordsTemp = keywords;
            //Calculates the loop depth through an iterator and the temporary vector
            for (vector<string>::iterator it = keywordsTemp.begin(); it != keywordsTemp.end(); ++it) {
                //Make sure there is no out of bounds error
                if (counter < (keywordsTemp.size() - 1)) {
                    //If there is a FOR and then a BEGIN, the for loop depth counter will increment.
                    if (*it == "FOR" && *next(it) == "BEGIN") {
                        counter++;
                        forLoopDepthCounter++;

                        for (vector<string>::iterator it2 = keywordsTemp.begin() + counter; it2 != keywordsTemp.end(); ++it2) {

                            if (counter < (keywordsTemp.size() - 1)) {
                                //This calculates the loops inside of the initial for loop
                                //I made sure the previous iterator value did not equal END so as to not double count when the loops are not nested
                                if (*it2 == "FOR" && *next(it2) == "BEGIN" && *prev(it2) != "END") {
                                        forLoopDepthCounter++;
                                      //  break;
                                }
                            }
                            //Erases the END keyword from the temporary vector to keep track of the depth loops
                            else if (*it2 == "END") {
                                keywordsTemp.erase(it2);
                                break;
                            }
                            else  {
                                forLoopDepthCounter--;
                                break;
                            }
                            counter++;
                        }
                    }
                }
                counter++;
            }
            return forLoopDepthCounter;
      }



};


#endif // PA3_H
