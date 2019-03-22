/*
 * main.cpp
 *
 *  Created by Lee Barney on 11/14/18.
 *  Copyright (c) 2018 Lee Barney
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation the
 *  rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:

 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

/* !!!!GRADING INSTRUCTIONS!!!!
 *
 * When you report your score for this test set, report
 * the percentage of asserts found in this test code that
 * your data structure code passed.
 */
#define UNIT_TESTING

#include <iostream>
#include <cstring>
#include <cassert>
#include "unit_testing_delete.h"
#include "map.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;
using std::ios;
using namespace custom;

int main(int argc, const char * argv[]) {

    /*------------------------------------------------------------------
     * WARNING: THIS TEST HAS A DEPENDENCY ON THE BST TEST.
     * THE BST TEST MUST PASS WITHOUT FAILURE BEFORE THIS TEST IS RUN.
     *------------------------------------------------------------------
     */



    /*
     * Testing pair constructors
     */


    map<char,int>::pair defaultPair;
    //not really anything that can be tested here. Unset default values could be anything.

    map<char,int>::pair pairToCopy;
    pairToCopy.first = 'a';
    pairToCopy.second = 97;

    map<char,int>::pair copiedPair(pairToCopy);
    assert(copiedPair.first == 'a');
    assert(copiedPair.second == 97);
    cout<<"Passed Constructor Tests"<<endl;

    /*
     * Testing pair operators
     */
    map<char, int>::pair assignedToPair = pairToCopy;
    assert(assignedToPair.first == 'a');
    assert(assignedToPair.second == 97);


    assignedToPair = defaultPair;
    assert(assignedToPair.first == defaultPair.first);
    assert(assignedToPair.second == defaultPair.second);

    cout<<"Passed Assignment Operator Tests"<<endl;


    //for all comparison operators, only the key is used for the comparison.


    /*
     * Testing == operator
     */

    //testing comparing to self
    assert(defaultPair == defaultPair);
    assert(assignedToPair == assignedToPair);
    //testing comparing to others
    assert(assignedToPair == defaultPair);
    assert(copiedPair == pairToCopy);
    assert(!(assignedToPair == pairToCopy));
    //testing key matches value doesn't
    copiedPair.second = 5;
    assert(copiedPair == pairToCopy);
    //testing key doesn't match, value does
    copiedPair.second = 97;
    copiedPair.first = 'b';
    assert(!(copiedPair == pairToCopy));

    cout<<"Passed == Operator Tests"<<endl;

    /*
     * Testing > operator
     */
    map<char, int>::pair lesserPair;
    lesserPair.first = ' ';//ascii value is 32
    lesserPair.second = 18;
    map<char, int>::pair greaterPair;
    greaterPair.first = '~';//ascii value is 176
    greaterPair.second = 18;

    //testing key doesn't match, value does
    assert(greaterPair > lesserPair);
    //testing key matches, values don't
    lesserPair.first = '~';
    greaterPair.second = 100;
    assert(!(greaterPair > lesserPair));
    //testing comparing to self
    assert(!(greaterPair > greaterPair));
    assert(!(defaultPair > defaultPair));

    cout<<"Passed > Operator Tests"<<endl;

    /*
     * Testing < operator
     */
    //resetting lesser and greater pairs
    lesserPair.first = ' ';
    lesserPair.second = 18;
    greaterPair.first = '~';//ascii value is 176
    greaterPair.second = 100;

    assert(lesserPair < greaterPair);
    //testing against self
    assert(!(lesserPair < lesserPair));
    assert(!(greaterPair < greaterPair));
    assert(!(defaultPair < defaultPair));
    assert(!(greaterPair < lesserPair));
    //testing keys don't match, values do
    greaterPair.second = lesserPair.second;
    assert(lesserPair < greaterPair);
    //testing keys match values don't
    greaterPair.second = 200;
    lesserPair.first = greaterPair.first;
    assert(!(lesserPair < greaterPair));

    cout<<"Passed < Operator Tests"<<endl;

    /*
     * Testing >= operator
     */

    //resetting lesser and greater pairs
    lesserPair.first = ' ';
    lesserPair.second = 18;
    greaterPair.first = '~';//ascii value is 176
    greaterPair.second = 100;

    assert(greaterPair >= lesserPair);
    //testing against self
    assert(lesserPair >= lesserPair);
    assert(greaterPair >= greaterPair);
    assert(defaultPair >= defaultPair);
    assert(!(lesserPair >= greaterPair));
    //testing keys don't match, values do;
    greaterPair.second = lesserPair.second;
    assert(greaterPair >= lesserPair);
    assert(!(lesserPair >= greaterPair));
    //testing keys match values don't
    greaterPair.second = 200;
    lesserPair.first = greaterPair.first;
    assert(greaterPair >= lesserPair);
    assert(lesserPair >= greaterPair);

    cout<<"Passed >= Tests"<<endl;

    /*
     * Testing <= operator
     */

    //resetting lesser and greater pairs
    lesserPair.first = ' ';
    lesserPair.second = 18;
    greaterPair.first = '~';//ascii value is 176
    greaterPair.second = 100;

    assert(lesserPair <= greaterPair);
    //testing against self
    assert(lesserPair <= lesserPair);
    assert(greaterPair <= greaterPair);
    assert(defaultPair <= defaultPair);
    //testing keys don't match values do
    greaterPair.second = lesserPair.second;
    assert(lesserPair <= greaterPair);
    assert(!(greaterPair <= lesserPair));
    //testing keys match values don't
    greaterPair.second = 200;
    lesserPair.first = greaterPair.first;
    assert(lesserPair <= greaterPair);
    assert(greaterPair <= lesserPair);

    cout<<"Passed <= Operator Tests"<<endl;

    /*
     * Testing map constructors
     */
    map<char,int> defaultMap;
    assert(defaultMap.bst.numElements == 0);
    assert(defaultMap.bst.root == NULL);

    map<char, int> copiedMap(defaultMap);
    assert(copiedMap.bst.numElements == 0);
    assert(copiedMap.bst.root == NULL);

    //Generating small BST with the values                              |
    //                                                            ----<f,7>------
    //                                                            |              |
    //                                                       ---<c,21>--     --<g,10>------
    //                                                       |               |             |
    //                                                     <b,3>           <s,-5>        <z,0>

    map<char, int> builtMap;
    //BST<map<char,int>::pair<char,int>> builtMap.bst;
    builtMap.bst.numElements = 6;
    builtMap.bst.root = new BST<map<char,int>::pair>::BNode();
    map<char,int>::pair fPair;
    fPair.first = 'f';
    fPair.second = 7;
    builtMap.bst.root->data = fPair;


    BST<map<char,int>::pair>::BNode* insertRootRight = new BST<map<char,int>::pair>::BNode();
    map<char,int>::pair gPair;
    gPair.first = 'g';
    gPair.second = 10;
    insertRootRight->data = gPair;
    insertRootRight->pParent = builtMap.bst.root;// <f,7>
    builtMap.bst.root->pRight = insertRootRight;// <g,10>

    BST<map<char,int>::pair>::BNode* insertRootRightRight = new BST<map<char,int>::pair>::BNode();
    map<char,int>::pair zPair;
    zPair.first = 'z';
    zPair.second = 0;
    insertRootRightRight->data = zPair;
    insertRootRightRight->pParent = insertRootRight;// <g,10>
    insertRootRight->pRight = insertRootRightRight;// <z,0>

    BST<map<char,int>::pair>::BNode* insertRootRightLeft = new BST<map<char,int>::pair>::BNode();
    map<char,int>::pair sPair;
    sPair.first = 's';
    sPair.second = -5;
    insertRootRightLeft->data = sPair;
    insertRootRightLeft->pParent = insertRootRight;// <g,10>
    insertRootRight->pLeft = insertRootRightLeft;// <s,-5>

    BST<map<char,int>::pair>::BNode* insertRootLeft = new BST<map<char,int>::pair>::BNode();
    map<char,int>::pair cPair;
    cPair.first = 'c';
    cPair.second = 21;
    insertRootLeft->data = cPair;
    insertRootLeft->pRight = NULL;
    insertRootLeft->pParent = builtMap.bst.root;// <f,7>
    builtMap.bst.root->pLeft = insertRootLeft;// <c,21>
    insertRootLeft->pRight = NULL;


    BST<map<char,int>::pair>::BNode* insertRootLeftLeft = new BST<map<char,int>::pair>::BNode();
    map<char,int>::pair bPair;
    bPair.first = 'b';
    bPair.second = 3;
    insertRootLeftLeft->data = bPair;
    insertRootLeftLeft->pRight = NULL;
    insertRootLeftLeft->pLeft = NULL;
    insertRootLeftLeft->pParent = insertRootLeft;// <c,21>
    insertRootLeft->pLeft = insertRootLeftLeft;// <b,3>


    map<char,int> copiedBuiltMap(builtMap);

    //copy should be                                                    |
    //                                                            ----<f,7>------
    //                                                            |              |
    //                                                       ---<c,21>--     --<g,10>------
    //                                                       |               |             |
    //                                                     <b,3>           <s,-5>        <z,0>

    assert(copiedBuiltMap.bst.root != NULL);
    assert(copiedBuiltMap.bst.root != builtMap.bst.root);
    assert(copiedBuiltMap.bst.root->data.first == 'f');
    assert(copiedBuiltMap.bst.root->data.second == 7);
    assert(copiedBuiltMap.bst.root->pParent == NULL);
    assert(copiedBuiltMap.bst.root->pRight != NULL);
    assert(copiedBuiltMap.bst.root->pLeft != NULL);

    //testing right sub-tree
    assert(copiedBuiltMap.bst.root->pRight != builtMap.bst.root->pRight);
    assert(copiedBuiltMap.bst.root->pRight->data.first == 'g');
    assert(copiedBuiltMap.bst.root->pRight->data.second == 10);
    assert(copiedBuiltMap.bst.root->pRight->pParent == copiedBuiltMap.bst.root);
    assert(copiedBuiltMap.bst.root->pRight != NULL);
    assert(copiedBuiltMap.bst.root->pLeft != NULL);

    assert(copiedBuiltMap.bst.root->pRight->pRight != builtMap.bst.root->pRight->pRight);
    assert(copiedBuiltMap.bst.root->pRight->pRight->data.first == 'z');
    assert(copiedBuiltMap.bst.root->pRight->pRight->data.second == 0);
    assert(copiedBuiltMap.bst.root->pRight->pRight->pParent == copiedBuiltMap.bst.root->pRight);
    assert(copiedBuiltMap.bst.root->pRight->pRight->pRight == NULL);
    assert(copiedBuiltMap.bst.root->pRight->pRight->pLeft == NULL);

    assert(copiedBuiltMap.bst.root->pRight->pLeft != builtMap.bst.root->pRight->pLeft);
    assert(copiedBuiltMap.bst.root->pRight->pLeft->data.first == 's');
    assert(copiedBuiltMap.bst.root->pRight->pLeft->data.second == -5);
    assert(copiedBuiltMap.bst.root->pRight->pLeft->pParent == copiedBuiltMap.bst.root->pRight);
    assert(copiedBuiltMap.bst.root->pRight->pLeft->pRight == NULL);
    assert(copiedBuiltMap.bst.root->pRight->pLeft->pLeft == NULL);


    //testing left sub-tree
    assert(copiedBuiltMap.bst.root->pLeft != builtMap.bst.root->pLeft);
    assert(copiedBuiltMap.bst.root->pLeft->data.first == 'c');
    assert(copiedBuiltMap.bst.root->pLeft->data.second == 21);
    assert(copiedBuiltMap.bst.root->pLeft->pParent == copiedBuiltMap.bst.root);
    assert(copiedBuiltMap.bst.root->pLeft->pLeft != NULL);
    assert(copiedBuiltMap.bst.root->pLeft->pRight == NULL);

    assert(copiedBuiltMap.bst.root->pLeft->pLeft != builtMap.bst.root->pLeft->pLeft);
    assert(copiedBuiltMap.bst.root->pLeft->pLeft->data.first == 'b');
    assert(copiedBuiltMap.bst.root->pLeft->pLeft->data.second == 3);
    assert(copiedBuiltMap.bst.root->pLeft->pLeft->pParent == copiedBuiltMap.bst.root->pLeft);
    assert(copiedBuiltMap.bst.root->pLeft->pLeft->pLeft == NULL);
    assert(copiedBuiltMap.bst.root->pLeft->pLeft->pRight == NULL);


    cout<<"Passed Map Constructor Tests"<<endl;


    /* Testing map size */

    // assert(defaultMap.size() == 0);
    assert(builtMap.size() == 6);
    builtMap.bst.numElements = 243;
    assert(builtMap.size() == 243);
    //resetting builtMap
    builtMap.bst.numElements = 6;

    cout<<"Passed Size Tests"<<endl;

//     /*
//      * Testing map empty
//      */
    assert(defaultMap.empty() == true);
    assert(builtMap.empty() == false);
    builtMap.bst.numElements = 0;
    assert(builtMap.empty() == true);
    //resetting builtMap
    builtMap.bst.numElements = 6;

    cout<<"Passed Empty Tests"<<endl;

//     /*
//      * Testing map clear
//      *
    unit_testing_delete_call_counter = 0;
    defaultMap.clear();
    assert(defaultMap.bst.numElements == 0);
    assert(defaultMap.bst.root == NULL);
    assert(unit_testing_delete_call_counter == 0);

    builtMap.clear();
    assert(builtMap.bst.numElements == 0);
    assert(builtMap.bst.root == NULL);
    assert(unit_testing_delete_call_counter == 6);

    cout<<"Passed Clear Tests"<<endl;


//     /*
//      * Testing iterator constructors
//      *

    map<char,int>::iterator emptyIterator;
    assert(emptyIterator.it.ptr == NULL);

    map<char, int>::iterator emptyIteratorCopy(emptyIterator);
    assert(emptyIteratorCopy.it.ptr == NULL);

//     // MM: changed specification of iterMap to following (swapped e and i nodes)
//     //                                                                     |
//     //                                                            ----<j,32>------
//     //                                                            |              |
//     //                                                       ---<e,8>----     <q,1000>------
//     //                                                       |            |                  |
//     //                                                     <a,100>      <i,-1>              <y,-3>
//     // This has ramifications for all subsequent tests depending on the position
//     // of these nodes (iterMap is used frequently). I won't comment each of
//     // those changes as they are fairly numerous.

//     //Generating small BST with the values                              |
//     //                                                            ----<j,32>------
//     //                                                            |              |
//     //                                                       ---<i,-1>----     <q,1000>------
//     //                                                       |            |                  |
//     //                                                     <a,100>      <e,8>              <y,-3>
    map<char, int> iterMap;
    iterMap.bst.numElements = 5;
    iterMap.bst.root = new BST<map<char,int>::pair>::BNode();
    map<char,int>::pair jPair;
    jPair.first = 'j';
    jPair.second = 32;
    iterMap.bst.root->data = jPair;

    //right subtree
    //reusing insert pointers
    insertRootRight = new BST<map<char,int>::pair>::BNode();
    map<char,int>::pair qPair;
    qPair.first = 'q';
    qPair.second = 1000;
    insertRootRight->data = qPair;
    insertRootRight->pParent = iterMap.bst.root;// <j,32>
    iterMap.bst.root->pRight = insertRootRight;// <q,1000>
    insertRootRight->pLeft = NULL;

    insertRootRightRight = new BST<map<char,int>::pair>::BNode();
    map<char,int>::pair yPair;
    yPair.first = 'y';
    yPair.second = -3;
    insertRootRightRight->data = yPair;
    insertRootRightRight->pParent = insertRootRight;// <q,1000>
    insertRootRight->pRight = insertRootRightRight;// <y,-3>
    insertRootRight->pLeft = NULL;


    //left subtree
    insertRootLeft = new BST<map<char,int>::pair>::BNode();
    map<char,int>::pair ePair;
    ePair.first = 'e';
    ePair.second = 8;
    insertRootLeft->data = ePair;
    insertRootLeft->pParent = iterMap.bst.root;// <j,32>
    iterMap.bst.root->pLeft = insertRootLeft;// <e,8>

    insertRootLeftLeft = new BST<map<char,int>::pair>::BNode();
    map<char,int>::pair aPair;
    aPair.first = 'a';
    aPair.second = 100;
    insertRootLeftLeft->data = aPair;
    insertRootLeftLeft->pRight = NULL;
    insertRootLeftLeft->pLeft = NULL;
    insertRootLeftLeft->pParent = insertRootLeft;// <e,8>
    insertRootLeft->pLeft = insertRootLeftLeft;// <a,100>

    BST<map<char,int>::pair>::BNode* insertRootLeftRight = new BST<map<char,int>::pair>::BNode();
    map<char,int>::pair iPair;
    iPair.first = 'i';
    iPair.second = -1;
    insertRootLeftRight->data = iPair;
    insertRootLeftRight->pRight = NULL;
    insertRootLeftRight->pLeft = NULL;
    insertRootLeftRight->pParent = insertRootLeft;// <e,8>
    insertRootLeft->pRight = insertRootLeftRight;// <i,-1>
    cout << "Passed Iterator Constructor" << endl;

//     // BST with the values                                              |
//     //                                                            ----<j,32>------
//     //                                                            |              |
//     //                                                       ---<e,8>----     <q,1000>------
//     //                                                       |            |                  |
//     //                                                     <a,100>      <i,-1>              <y,-3>

//     /*
//      * Testing map begin
//      *
    assert(defaultMap.begin().it.ptr == NULL);
    assert(iterMap.begin().it.ptr->data.first == 'a');
    assert(iterMap.begin().it.ptr->data.second == 100);

    cout<<"Passed Map Begin Test"<<endl;

//     /*
//      * Testing map end
//      *
    assert(defaultMap.end().it.ptr == NULL);
    assert(iterMap.end().it.ptr->data.first == 'y');
    assert(iterMap.end().it.ptr->data.second == -3);

    cout<<"Passed Map End Test"<<endl;

//     /*
//      * Testing iterator equality operator
//      *

    map<char,int>::iterator nullNodeIterator;
    map<char,int>::iterator otherNullNodeIterator;

    // MM: changed test as equality is ultimately based on comparison of
    // pointers underlying the wrapped BST iterator ...which are both NULL
    // in this case

    // assert(nullNodeIterator == nullNodeIterator);
    // assert(otherNullNodeIterator == otherNullNodeIterator);
    assert(nullNodeIterator == otherNullNodeIterator);


    map<char,int>::iterator nonNullNodeIterator;
    map<char,int>::pair somePair;
    somePair.first = '!';
    somePair.second = 567;
    BST<custom::map<char, int>::pair>::BNode commonNode;
    commonNode.data = somePair;
    nonNullNodeIterator.it.ptr = &commonNode;


    map<char,int>::iterator otherNonNullNodeIterator;
    otherNonNullNodeIterator.it.ptr = &commonNode;
    assert(nonNullNodeIterator == otherNonNullNodeIterator);

    cout<<"Passed Iterator == Tests"<<endl;

//     /*
//      * Testing iterator not-equal operator
//      *

    //reusing nullNodeIterator, nonNullNodeIterator, and otherNonNullNodeIterator

    map<char,int>::pair someOtherPair;
    someOtherPair.first = '$';
    someOtherPair.second = 567;
    BST<custom::map<char, int>::pair>::BNode someOtherNode;
    someOtherNode.data = someOtherPair;
    otherNonNullNodeIterator.it.ptr = &someOtherNode;
    assert(otherNonNullNodeIterator != nonNullNodeIterator);
    assert(!(nullNodeIterator != nullNodeIterator));
    assert(!(nonNullNodeIterator != nonNullNodeIterator));
    //resetting
    otherNonNullNodeIterator.it.ptr = nonNullNodeIterator.it.ptr;
    assert(!(otherNonNullNodeIterator != nonNullNodeIterator));

    cout<<"Passed Iterator != Operator Tests"<<endl;

//     /*
//      * Testing iterator assignment operator
//      *

    //reusing nonNullNodeIterator
    map<char,int>::iterator assignedTo = nonNullNodeIterator;
    assert(assignedTo.it.ptr != NULL);
    assert(assignedTo.it.ptr == nonNullNodeIterator.it.ptr);

    assignedTo = emptyIterator;
    assert(assignedTo.it.ptr == NULL);

    cout<<"Passed Iterator = Operator Tests"<<endl;

//     /*
//      * Testing iterator dereference operator
//      *

    try {
        *emptyIterator;
        assert(false);
    } catch (const char* message) {
        // MM: Changed assertion to check for identical result (== 0)
        assert(strcmp(message, "Error: dereferencing null node.") == 0);
    }
    map<char,int>::pair retrievedPair = *nonNullNodeIterator;
    assert(retrievedPair.first == nonNullNodeIterator.it.ptr->data.first);
    assert(retrievedPair.second == nonNullNodeIterator.it.ptr->data.second);

    cout<<"Passed Iterator * Tests"<<endl;


//     /*
//      * Testing iterator pre-increment operator
//      *
//     // BST with the values                                              |
//     //                                                            ----<j,32>------
//     //                                                            |              |
//     //                                                       ---<i,-1>----     <q,1000>------
//     //                                                       |            |                  |
//     //                                                     <a,100>      <e,8>              <y,-3>

    //reusing iterMap
    // map<char, int>::iterator incrementIterator;
    // incrementIterator.it.ptr = NULL;
    // try {
    //     ++incrementIterator;
    //     assert(false);
    // } catch (const char* message) {
    //     assert(strcmp(message, "Error: incrementing null node.") == 0);
    // }
    // //beginning of tree test
    // incrementIterator.it.ptr = insertRootLeftLeft;// <a,100>
    // assert((++incrementIterator).it.ptr == insertRootLeft);// <e,8>
    // //end of tree test
    // incrementIterator.it.ptr = insertRootRightRight;// <y,-3>
    // assert((++incrementIterator).it.ptr == NULL);
    // //middle of tree test
    // incrementIterator.it.ptr = insertRootLeft;// <e,8>
    // assert((++incrementIterator).it.ptr == insertRootLeftRight); // <i,-1>;

    // cout<<"Passed Iterator Pre-Increment Test"<<endl;

//     /*
//      * Testing iterator post increment operator
//      *


//     // BST with the values                                              |
//     //                                                            ----<j,32>------
//     //                                                            |              |
//     //                                                       ---<e,8>----     <q,1000>------
//     //                                                       |            |                  |
//     //                                                     <a,100>      <i,-1>              <y,-3>

//     //reusing iterMap
//     incrementIterator.it.ptr = NULL;
//     try {
//         incrementIterator++;
//         assert(false);
//     } catch (const char* message) {
//         assert(strcmp(message, "Error: incrementing null node.") == 0);
//     }
//     //reusing iterMap
//     //beginning of tree test
//     incrementIterator.it.ptr = insertRootLeftLeft;// <a,100>
//     assert((incrementIterator++).it.ptr == insertRootLeftLeft);// <a,100>
//     assert(incrementIterator.it.ptr == insertRootLeft);// <e,8>
//     //end of tree test
//     incrementIterator.it.ptr = insertRootRightRight;// <y,-3>
//     assert((incrementIterator++).it.ptr == insertRootRightRight);// <y,-3>
//     assert(incrementIterator.it.ptr == NULL);
//     //middle of tree test
//     incrementIterator.it.ptr = insertRootLeft;// <e,8>
//     assert((incrementIterator++).it.ptr == insertRootLeft);// <e,8>
//     assert(incrementIterator.it.ptr == insertRootLeftRight);// <i,-1>

//     cout<<"Passed Iterator Post Increment Test"<<endl;

//     /*
//      * Testing iterator pre-decrement operator
//      *
//     // BST with the values                                              |
//     //                                                            ----<j,32>------
//     //                                                            |              |
//     //                                                       ---<e,8>----     <q,1000>------
//     //                                                       |            |                  |
//     //                                                     <a,100>      <i,-1>              <y,-3>

//     //reusing iterMap
//     map<char, int>::iterator decrementIterator;
//     decrementIterator.it.ptr = NULL;
//     try {
//         --decrementIterator;
//         assert(false);
//     } catch (const char* message) {
//         assert(strcmp(message, "Error: decrementing null node.") == 0);
//     }
//     //beginning of tree test
//     decrementIterator.it.ptr = insertRootLeftLeft;// <a,100>
//     assert((--decrementIterator).it.ptr == NULL);
//     //end of tree test
//     decrementIterator.it.ptr = insertRootRightRight;// <y,-3>
//     assert((--decrementIterator).it.ptr == insertRootRight);
//     //middle of tree test
//     decrementIterator.it.ptr = insertRootLeftRight;//(12)
//     assert((--decrementIterator).it.ptr == insertRootLeft);

//     cout<<"Passed Iterator Pre-Decrement Tests"<<endl;

//     /*
//      * Testing iterator post decrement operator
//      *
//     // BST with the values                                              |
//     //                                                            ----<j,32>------
//     //                                                            |              |
//     //                                                       ---<i,-1>----     <q,1000>------
//     //                                                       |            |                  |
//     //                                                     <a,100>      <e,8>              <y,-3>

//     //reusing iterMap
//     decrementIterator.it.ptr = NULL;
//     try {
//         decrementIterator--;
//         assert(false);
//     } catch (const char* message) {
//         assert(strcmp(message, "Error: decrementing null node.") == 0);
//     }
//     //beginning of tree test
//     decrementIterator.it.ptr = insertRootLeftLeft;// <a,100>
//     assert((decrementIterator--).it.ptr == insertRootLeftLeft);// <a,100>
//     assert(decrementIterator.it.ptr == NULL);
//     //end of tree test
//     decrementIterator.it.ptr = insertRootRightRight;// <y,-3>
//     assert((decrementIterator--).it.ptr == insertRootRightRight);
//     //middle of tree test
//     decrementIterator.it.ptr = insertRootLeftRight;// <e,8>
//     assert((decrementIterator--).it.ptr == insertRootLeftRight);// <e,8>
//     assert(decrementIterator.it.ptr == insertRootLeft);// <i,-1>

//     cout<<"Passed Iterator Post Decrement Tests"<<endl;

//     /*
//      * Testing map find
//      *

//     // MM: changed these assertions to reflect what is actually in the map, not
//     // sure where these came from
    cout << "Here";
    //problem in here
    //check it over
    assert((*iterMap.find('z')).second == 35);
    assert((*iterMap.find(';')).second == 95);
    assert((*iterMap.find('e')).second == 25);
    assert((*iterMap.find('@')).second == 901);
    assert((*iterMap.find('q')).second == 10000);

    assert((*iterMap.find('j')).second == 32);
    assert((*iterMap.find('i')).second == -1);
    assert((*iterMap.find('a')).second == 100);
    assert((*iterMap.find('e')).second == 8);
    assert((*iterMap.find('q')).second == 1000);
    assert((*iterMap.find('y')).second == -3);

    // for fun
    assert((*iterMap.find('j')).first == 'j');
    assert(iterMap.find('*').it.ptr == NULL); // * is not in tree
    cout<<"Passed Find Tests\n";

//    /*
//      * Testing square bracket operator
//      *
//     // MM: removing these tests because they expect a different behavior than
//     // the tests on lines 800-805. That is, if a key is not found it should be
//     // automagically inserted and a reference to the value returned. This is the
//     // original Helfrich implementation anyway.

//     // map<char, int> emptyMap;
//     // try {
//     //     emptyMap['j'];
//     //     assert(false);
//     // } catch (const char* message) {
//     //     assert(strcmp(message, "Error: no value associated with the key 'j'"));
//     // }
//     // try {
//     //     emptyMap['$'];
//     //     assert(false);
//     // } catch (const char* message) {
//     //     assert(strcmp(message, "Error: no value associated with the key '$'"));
//     // }

//     //reusing iterMap

//     // BST should be                                                    |
//     //                                                            ----<j,32>------
//     //                                                            |              |
//     //                                                       ---<e,8>----     <q,1000>------
//     //                                                       |            |                  |
//     //                                                     <a,100>      <i,-1>              <y,-3>
//     //beginning square bracket operator accessor test
//     assert(iterMap['j'] == 32);
//     assert(iterMap['i'] == -1);
//     assert(iterMap['a'] == 100);
//     assert(iterMap['e'] == 8);
//     assert(iterMap['q'] == 1000);
//     assert(iterMap['y'] == -3);

//     // MM: ... same for this test
//     // try {
//     //     iterMap['$'];
//     //     assert(false);
//     // } catch (const char* message) {
//     //     assert(strcmp(message, "Error: no value associated with the key '$'"));
//     // }
//     cout<<"Passed Map Square Bracket Operator Access Value Tests"<<endl;

//     // beginning square bracket operator mutator test
//     iterMap['j'] = 15;
//     iterMap['i'] = 45;
//     iterMap['a'] = 75;
//     iterMap['e'] = 25;
//     iterMap['q'] = 10000;
//     iterMap['y'] = -300;
//     assert(iterMap.bst.root->data.second == 15);
//     assert(iterMap.bst.root->pLeft->data.second == 25);
//     assert(iterMap.bst.root->pLeft->pLeft->data.second == 75);
//     assert(iterMap.bst.root->pLeft->pRight->data.second == 45);
//     assert(iterMap.bst.root->pRight->data.second == 10000);
//     assert(iterMap.bst.root->pRight->pRight->data.second == -300);
//     cout<<"Passed Map Square Bracket Operator Mutate Values Tests"<<endl;

//     // beginning square bracket operator insert test
//     iterMap['z'] = 35;
//     iterMap[';'] = 95;
//     assert(iterMap.bst.root->pRight->pRight->pRight->data.first == 'z');
//     assert(iterMap.bst.root->pRight->pRight->pRight->data.second == 35);
//     assert(iterMap.bst.root->pLeft->pLeft->pLeft->data.first == ';');
//     assert(iterMap.bst.root->pLeft->pLeft->pLeft->data.second == 95);

//     cout<<"Passed Square Bracket Operator Tests\n";


//     // ToDo: Write string test.
//     // MM: No need, I'm satisfied it works


 }