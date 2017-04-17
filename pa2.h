//Name: Samantha Garcia
//Section: 1133
//TA: Kevin Neumann
//Project: pa2
//Description: Creates a Linked List that can add nodes, or pages, and delete them in a best fit or worst fit way

#ifndef PA2_H
#define PA2_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

class pa2
{

    public:

        //Creates a node object
        struct node {

            string item = "Free";
            node *next;


        };

        //Defines the Pointers to the Node Objects
        typedef struct node * nodePointer;
        nodePointer head;

        int pages;


        //Constructor
        pa2(int pagesNumber) {

            nodePointer curr = new node();
            nodePointer temp;

            head = NULL;

            pages = pagesNumber;

            for (int i = 0; i < pages; ++i) {
                if (i == 0)
                    head = curr;
                if (i != 0) {
                    temp = curr;
                    curr = new node();
                    temp->next = curr;
                }
                if (i == (pages - 1)) {
                    curr->next = nullptr;
                }
            }
    }


    //Adding Pages/Nodes to the Pages
    void addNode(string valueAdded, double programSize, int bestOrWorst) {

        nodePointer curr = head;
        //Check if Program is Already Running
        for (int i = 0; i < pages; ++i) {

            if (curr->item == valueAdded) {
                cout << "Error, Program " << valueAdded << " already running.\n\n ";
                return;
            }

            if (curr->next != nullptr)
                curr = curr->next;

        }

        //Check if Memory is Too Much to Add
        if (programSize > (pages*4)) {
            cout << "Error, Not enough memory for Program " << valueAdded << "\n\n";
            return;
        }

        curr = head;
        //How many pages to be used are calculated by rounding up after dividing by four
        double pagesToBeUsed = ceil(programSize / 4);

        int pagesUsed = 0;

        vector<int> fragmentIndex;
        vector<int> fragmentIndexEnd;
        vector<int> fragmentSize;

        //Declaring other loop iterator outside loop
        int j = 0;

        //Execute Best Fit
        for (int i = 0; i < pages; ++i) {
            //Index will be 0

            if (curr->item == "Free") {

                pagesUsed = 1;

                j = i;
                //Put the index where the fragment starts into the vector
                fragmentIndex.push_back(j);

                for (; j < pages;) {
                    //Go through the fragment
                    if (curr->next != nullptr)
                        curr = curr->next;
                    else {
                        fragmentIndexEnd.push_back(j);
                        break;
                    }
                    //If the current node is free then it will add another page to the pagesUsed variable
                    if (curr->item == "Free")
                        pagesUsed++;
                    if (curr->item != "Free") {
                        fragmentIndexEnd.push_back(j);
                        break;
                    }
                    j++;

                }
                fragmentSize.push_back(pagesUsed);

                pagesUsed = 0;
                i = j;

            }

            if (curr->next != nullptr) {
                curr = curr->next;
            }
            else
                break;

        }

    //Function to Add to Linked List
      fit(valueAdded, pagesToBeUsed, bestOrWorst, fragmentSize, fragmentIndex);


    }

    void fit(string valueAdded, double pagesToBeUsed, int bestOrWorst, vector<int>& fragmentSize, vector<int>& fragmentIndex) {

        //Execute best fit
        if (bestOrWorst == 1) {

            int index = 0;
            //Finding the minimum value in the vector and dereferencing the pointer
            int minFragment = *min_element(fragmentSize.begin(), fragmentSize.end());
            //Finding the index of the minimum element
            int minFragmentIndex = distance(fragmentSize.begin(), min_element(fragmentSize.begin(), fragmentSize.end()));
            //Making sure that the pages fit into the Fragment Size selected, if not it will reselect the data by setting those values that are too small to a big number
            //So that they may never be selected again.
            while (pagesToBeUsed > minFragment) {
                //Make sure the value isn't selected again
                fragmentSize[minFragmentIndex] = pages * 33;
                minFragment = *min_element(fragmentSize.begin(), fragmentSize.end());
                minFragmentIndex = distance(fragmentSize.begin(), min_element(fragmentSize.begin(), fragmentSize.end()));
                if (minFragment == (pages * 33)) {
                    cout << "Error, Not enough memory for Program " << valueAdded << endl;
                    return;
                }
            }
            //I find the index to start at by inputing the index I just found into my fragmentIndex vector
            index = fragmentIndex[minFragmentIndex];

            //Just in case it overrides the previous Index
            nodePointer tempNode = head;
            for (int i = 0; i < pages; ++i) {
                    if (i == index && tempNode->item != "Free")
                        index++;
                    if (tempNode->next != head)
                        tempNode = tempNode->next;
            }

            nodePointer curr = head;

            int tempPages = pagesToBeUsed;

            //Iterating through the Linked List to input the program into the smallest fragment possible (that it can still fit into)
            for (int i = 0; i < pages; ++i) {

                    if (i == index) {

                        while (tempPages != 0) {

                            curr->item = valueAdded;
                            tempPages--;

                            if (curr->next != nullptr)
                                curr = curr->next;
                            else
                                break;
                        }
                        break;
                    }

                    if (curr->next != nullptr)
                        curr = curr->next;
              }

            cout << "Program " << valueAdded << " added successfully: " << pagesToBeUsed << " page(s) used.\n";

        }
        //Execute Worst Fit
        else if (bestOrWorst == 2) {

            int index = 0;
            //Finding the maximum value in the vector and dereferencing the pointer
            int maxFragment = *max_element(fragmentSize.begin(), fragmentSize.end());
            //Finding the index of the maximum element
            int maxFragmentIndex = distance(fragmentSize.begin(), max_element(fragmentSize.begin(), fragmentSize.end()));

            //If the value doesn't fit into the maximum fragment then it is too big for the program
            while (pagesToBeUsed > maxFragment) {

                    cout << "Error, Not enough memory for Program " << valueAdded << endl;
                    return;

            }
            //I find the index to start at by inputing the index I just found into my fragmentIndex vector
            index = fragmentIndex[maxFragmentIndex];

            //Just in case it overrides the previous Index
            nodePointer tempNode = head;
            for (int i = 0; i < pages; ++i) {
                    if (i == index && tempNode->item != "Free")
                        index++;
                    if (tempNode->next != head)
                        tempNode = tempNode->next;
            }

            nodePointer curr = head;

            int tempPages = pagesToBeUsed;

            //Iterating through the Linked List to input the program into the smallest fragment possible (that it can still fit into)
            for (int i = 0; i < pages; ++i) {

                    if (i == index) {

                        while (tempPages != 0) {

                            curr->item = valueAdded;
                            tempPages--;

                            if (curr->next != nullptr)
                                curr = curr->next;
                            else
                                break;
                        }
                        break;
                    }

                    if (curr->next != nullptr)
                        curr = curr->next;
              }

            cout << "Program " << valueAdded << " added successfully: " << pagesToBeUsed << " page(s) used.\n";

        }
        else {
            cout << "Not a valid input\n";
            return;
        }

    }


    //Deleting Pages/Nodes from the List
    void deleteNode(string valueDeleted) {

        nodePointer curr = head;

        bool nodeFound = false;

        int pagesUsed = 0;
        //Iterate through the linked List until the correct value is found and set it to "Free"; it keeps on going until that value is not found anymore
        for (int i = 0; i < pages; ++i) {

                if (curr->item == valueDeleted) {
                    curr->item = "Free";
                    pagesUsed++;
                    nodeFound = true;
                }
                //Goes onto the next page if it is not pointing to null
                if (curr->next != nullptr)
                    curr = curr->next;

        }

        if (nodeFound == true)
            cout << "Program " << valueDeleted << " was successfully killed, " << pagesUsed << " page(s) reclaimed.\n";
        else
            cout << "Error Program " << valueDeleted << " was not found.\n";

    }
    void printNodes() {

        int count = 0;

        nodePointer curr = head;

        //Iterates through the Linked List and prints each string associated with the node struct
        for (int i = 0; i < pages; ++i) {

            cout << curr->item << "\t";

            if (curr->next != nullptr)
                curr = curr->next;

            count++;
            //When the row reaches 8 pages it puts the following information on the next line
            if (count % 8 == 0)
                cout << endl;

            }

    }
    void fragments() {
        //Sets current pointer to the head
        nodePointer curr = head;

        bool runningThroughFragment = false;

        int count = 0;
        //Iterated through the Linked List
        while (curr->next != nullptr)
        {
            //Will mark when the fragment starts
            if (curr->item == "Free") {
                runningThroughFragment = true;
                //Will iterate through the fragment until it ends
                while (runningThroughFragment) {
                    if (curr->next != nullptr && curr->item == "Free")
                        curr = curr->next;
                    else
                        runningThroughFragment = false;
                }
                count++;
            }

            if (curr->next != nullptr)
                curr = curr->next;

        }

        cout << "There are " << count << " fragment(s)\n";

    }

};




#endif // PA2_H
