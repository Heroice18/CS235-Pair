/*
 * main.cpp
 *
 *  Created by Lee Barney on 11/10/18.
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
#include "hash.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;
using std::ios;
using std::string;
using namespace custom;

/*
 * What you will be implementing by conforming to these unit
 * tests is a hash set.
 */


/*
 * Hashing Functions to Use
 */
long hashInt(const int& aValue, long theBucketCount)
{
    return abs(aValue) % theBucketCount;
}

//This string hashing function was first reported by Dan Bernstein in the news group comp.lang.c
//this string hashing function is often called djb2.
long hashString(const string& aValue, long theBucketCount)
{
    const char* str = aValue.c_str();
    unsigned long hash = 5381;//seed value
    int accumulator;
    while ((accumulator = *str++))
    {
        hash = ((hash << 5) + hash) + accumulator; /* hash * 32 + accumulator */
    }
    return hash % theBucketCount;
}

int main(int argc, const char * argv[])
{
    /*
     * Testing constructors
     */
    
    try {
        Hash<int> badParameterHash(-2);
        assert(false);
    } catch (const char* message) {
        cout<<message<<endl;
        assert(strcmp(message, "Error: Hashes must have at least 1 bucket.") == 0);
    }
    
    try {
        Hash<int> badParameterHash(0);
        assert(false);
    } catch (const char* message) {
        assert(strcmp(message, "Error: Hashes must have at least 1 bucket.") == 0);
    }
    
    Hash<int>degenerateHash(1);//same behavior as a list
    assert(degenerateHash.numBuckets == 1);
    assert(degenerateHash.numElements == 0);
    assert(degenerateHash.table != NULL);
    assert(degenerateHash.table[0]->numElements == 0);
    assert(degenerateHash.table[0]->pHead == NULL);
    assert(degenerateHash.table[0]->pTail == NULL);
    
    Hash<int> tenHash(10);
    assert(tenHash.numBuckets == 10);
    assert(tenHash.numElements == 0);
    assert(tenHash.table != NULL);
    assert(tenHash.table[0]->numElements == 0);
    assert(tenHash.table[0]->pHead == NULL);
    assert(tenHash.table[0]->pTail == NULL);
    assert(tenHash.table[1]->numElements == 0);
    assert(tenHash.table[1]->pHead == NULL);
    assert(tenHash.table[1]->pTail == NULL);
    assert(tenHash.table[2]->numElements == 0);
    assert(tenHash.table[2]->pHead == NULL);
    assert(tenHash.table[2]->pTail == NULL);
    assert(tenHash.table[3]->numElements == 0);
    assert(tenHash.table[3]->pHead == NULL);
    assert(tenHash.table[3]->pTail == NULL);
    assert(tenHash.table[4]->numElements == 0);
    assert(tenHash.table[4]->pHead == NULL);
    assert(tenHash.table[4]->pTail == NULL);
    assert(tenHash.table[5]->numElements == 0);
    assert(tenHash.table[5]->pHead == NULL);
    assert(tenHash.table[5]->pTail == NULL);
    assert(tenHash.table[6]->numElements == 0);
    assert(tenHash.table[6]->pHead == NULL);
    assert(tenHash.table[6]->pTail == NULL);
    assert(tenHash.table[7]->numElements == 0);
    assert(tenHash.table[7]->pHead == NULL);
    assert(tenHash.table[7]->pTail == NULL);
    assert(tenHash.table[8]->numElements == 0);
    assert(tenHash.table[8]->pHead == NULL);
    assert(tenHash.table[8]->pTail == NULL);
    assert(tenHash.table[9]->numElements == 0);
    assert(tenHash.table[9]->pHead == NULL);
    assert(tenHash.table[9]->pTail == NULL);
    
    cout<<"Passed Hash Constructor Tests"<<endl;
    
    /*
     * Testing Hash Destructor
     */
    
    Hash<int>* singleBucketNoValuesHash = new Hash<int>(1);
    unit_testing_delete_call_counter = 0;
    delete singleBucketNoValuesHash;
    assert(unit_testing_delete_call_counter == 3);//also deletes the Hash and the single list
    
    Hash<int>* multipleBucketsMultipleValuesHash = new Hash<int>(3);
    //simulate inserting 8, 7, 3, 9.
    multipleBucketsMultipleValuesHash->table[2]->pHead = new list<int>::node(8);
    multipleBucketsMultipleValuesHash->table[2]->pTail = multipleBucketsMultipleValuesHash->table[2]->pHead;
    multipleBucketsMultipleValuesHash->table[1]->pHead = new list<int>::node(7);
    multipleBucketsMultipleValuesHash->table[1]->pTail = multipleBucketsMultipleValuesHash->table[1]->pHead;
    multipleBucketsMultipleValuesHash->table[0]->pHead = new list<int>::node(3);
    multipleBucketsMultipleValuesHash->table[0]->pHead->pNext = new list<int>::node(9);
    multipleBucketsMultipleValuesHash->table[0]->pTail = multipleBucketsMultipleValuesHash->table[0]->pHead->pNext;
    multipleBucketsMultipleValuesHash->table[0]->pTail->pPrev = multipleBucketsMultipleValuesHash->table[0]->pHead;
    unit_testing_delete_call_counter = 0;
    delete multipleBucketsMultipleValuesHash;
    //The list implementation you did is a shallow copy.
    assert(unit_testing_delete_call_counter == 9);//also deletes the Hash, 3 lists, and 4 nodes but not the data in the nodes.
    
    cout<<"Passed Hash Destructor Tests"<<endl;
    
    /*
     * Testing hash size
     */
    
    Hash<int>simpleHash(1);
    simpleHash.numElements = 15;
    assert(simpleHash.size() == 15);
    
    cout<<"Passed Hash Size Tests"<<endl;
    
    /*
     * Testing hash empty
     */
    assert(simpleHash.empty() == false);
    //resetting simpleHash
    simpleHash.numElements = 0;
    assert(simpleHash.empty() == true);
    
    cout<<"Passed Hash Empty Tests"<<endl;
    
    /*
     * Testing hash capacity
     */
    //resetting simpleHash
    simpleHash.numElements = 0;
    simpleHash.numBuckets = 0;
    assert(simpleHash.capacity() == 0);
    simpleHash.numBuckets = 1000;
    assert(simpleHash.capacity() == 1000);
    simpleHash.numBuckets = 1;
    cout<<"Passed Hash Capacity Tests"<<endl;
    
    /*
     * Testing copy constructor
     */
    
    Hash<int>emptyHashToCopy(1);
    Hash<int>copyOfEmptyHash(emptyHashToCopy);
    assert(copyOfEmptyHash.numElements == 0);
    assert(copyOfEmptyHash.numBuckets == 1);
    assert(copyOfEmptyHash.table[0]->pTail == NULL);
    assert(copyOfEmptyHash.table[0]->pHead == NULL);
    
    Hash<int> hashToCopy(5);
    delete hashToCopy.table[0];
    delete hashToCopy.table[1];
    delete hashToCopy.table[2];
    delete hashToCopy.table[3];
    delete hashToCopy.table[4];
    delete [] hashToCopy.table;
    
    //resetting
    hashToCopy.table = new list<int>*[5];
    hashToCopy.table[0] = new list<int>();
    hashToCopy.table[1] = new list<int>();
    hashToCopy.table[2] = new list<int>();
    hashToCopy.table[3] = new list<int>();
    hashToCopy.table[4] = new list<int>();
    hashToCopy.numBuckets = 5;
    hashToCopy.numElements = 4;
    //simulate inserting 8, 7, 3, 9.
    hashToCopy.table[3]->pHead = new list<int>::node(8);
    hashToCopy.table[3]->pHead->pNext = new list<int>::node(3);
    hashToCopy.table[3]->pTail = hashToCopy.table[3]->pHead->pNext;
    hashToCopy.table[3]->pTail->pPrev = hashToCopy.table[3]->pHead;
    hashToCopy.table[2]->pHead = new list<int>::node(7);
    hashToCopy.table[2]->pTail = hashToCopy.table[2]->pHead;
    hashToCopy.table[4]->pHead = new list<int>::node(9);
    hashToCopy.table[4]->pTail = hashToCopy.table[4]->pHead;
    
    /* hash array with lists is now (with <> meaning empty list)
     *                       [
     *                          <>,
     *                          <>,
     *                          <7>,
     *                          <8,3>,
     *                          <9>
     *                       ]
     */
    
    Hash<int> copiedHash(hashToCopy);
    assert(copiedHash.numBuckets == 5);
    assert(copiedHash.numElements == 4);
    assert(copiedHash.table[0]->pHead == NULL);
    assert(copiedHash.table[0]->pTail == NULL);
    assert(copiedHash.table[1]->pHead == NULL);
    assert(copiedHash.table[1]->pTail == NULL);
    assert(*(copiedHash.table[2]->pHead->data) = 7);
    assert(*(copiedHash.table[2]->pTail->data) = 7);
    assert(*(copiedHash.table[3]->pHead->data) = 8);
    assert(*(copiedHash.table[3]->pTail->data) = 3);
    assert(*(copiedHash.table[4]->pHead->data) = 9);
    assert(*(copiedHash.table[4]->pTail->data) = 9);
    
    cout<<"Passed Copy Constructor Tests"<<endl;
    
    /*
     * Testing assignment operator
     */
    Hash<int> assignFrom(3);
    assignFrom.numBuckets = 3;
    assignFrom.numElements = 4;
    //simulate inserting 8, 7, 3, 9.
    assignFrom.table[2]->pHead= new list<int>::node(8);
    assignFrom.table[2]->pTail = assignFrom.table[2]->pHead;
    assignFrom.table[1]->pHead = new list<int>::node(7);
    assignFrom.table[1]->pTail = assignFrom.table[1]->pHead;
    assignFrom.table[0]->pHead = new list<int>::node(3);
    assignFrom.table[0]->pHead->pNext = new list<int>::node(9);
    assignFrom.table[0]->pTail = assignFrom.table[0]->pHead->pNext;
    assignFrom.table[0]->pTail->pPrev = assignFrom.table[0]->pHead;
    /* hash array with lists is now (with <> meaning empty list)
     *                       [
     *                          <3,9>,
     *                          <7>,
     *                          <8>
     *                       ]
     */
    
    Hash<int>emptyAssignTo(5);
    unit_testing_delete_call_counter = 0;
    emptyAssignTo = assignFrom;
    assert(unit_testing_delete_call_counter == 6);
    assert(emptyAssignTo.numElements == 4);
    assert(emptyAssignTo.numBuckets == 3);
    assert(emptyAssignTo.table[0] != NULL);
    assert(*(emptyAssignTo.table[0]->pHead->data) == 3);
    assert(emptyAssignTo.table[0]->pHead->pNext != NULL);
    assert(*(emptyAssignTo.table[0]->pHead->pNext->data) == 9);
    
    assert(emptyAssignTo.table[1] != NULL);
    assert(*(emptyAssignTo.table[1]->pHead->data) == 7);
    
    assert(emptyAssignTo.table[2] != NULL);
    assert(*(emptyAssignTo.table[2]->pHead->data) == 8);

    Hash<int>emptyToAssign(1);
    
    Hash<int> filledAssignTo(3);
    //simulate inserting 8, 7, 3, 9.
    filledAssignTo.numBuckets = 3;
    filledAssignTo.numElements = 4;
    //simulate inserting 8, 7, 3, 9.
    filledAssignTo.table[2]->pHead= new list<int>::node(8);
    filledAssignTo.table[2]->pTail = filledAssignTo.table[2]->pHead;
    filledAssignTo.table[1]->pHead = new list<int>::node(7);
    filledAssignTo.table[1]->pTail = filledAssignTo.table[1]->pHead;
    filledAssignTo.table[0]->pHead = new list<int>::node(3);
    filledAssignTo.table[0]->pHead->pNext = new list<int>::node(9);
    filledAssignTo.table[0]->pTail = filledAssignTo.table[0]->pHead->pNext;
    filledAssignTo.table[0]->pTail->pPrev = filledAssignTo.table[0]->pHead;
    /* hash array with lists is now (with <> meaning empty list)
     *                       [
     *                          <3,9>,
     *                          <7>,
     *                          <8>
     *                       ]
     */
    unit_testing_delete_call_counter = 0;
    filledAssignTo = emptyToAssign;
    assert(unit_testing_delete_call_counter == 8);
    assert(filledAssignTo.numElements == 0);
    assert(filledAssignTo.numBuckets == 1);
    assert(filledAssignTo.table[0]->pHead == NULL);
    assert(filledAssignTo.table[0]->pTail == NULL);
    
    cout<<"Passed Assignment Operator Tests"<<endl;
    
    
    /*
     * Testing insert
     */
    
    //inserting into empty Hash
    Hash<int> emptyInsertHash(1);
    delete emptyInsertHash.table[0];
    delete[] emptyInsertHash.table;
    emptyInsertHash.table = NULL;
    emptyInsertHash.table = new list<int>*[7];
    emptyInsertHash.table[0] = new list<int>();
    emptyInsertHash.table[1] = new list<int>();
    emptyInsertHash.table[2] = new list<int>();
    emptyInsertHash.table[3] = new list<int>();
    emptyInsertHash.table[4] = new list<int>();
    emptyInsertHash.table[5] = new list<int>();
    emptyInsertHash.table[6] = new list<int>();
    emptyInsertHash.numBuckets = 7;
    emptyInsertHash.numElements = 0;
    emptyInsertHash.insert(12, hashInt);
    /* hash array with lists is now (with <> meaning empty list)
     *                       [
     *                          <>,
     *                          <>,
     *                          <>,
     *                          <>,
     *                          <>,
     *                          <12>,
     *                          <>
     *                       ]
     */
    assert(emptyInsertHash.numBuckets == 7);
    assert(emptyInsertHash.table[0]->pHead == NULL);
    assert(emptyInsertHash.table[0]->pTail == NULL);
    assert(emptyInsertHash.table[1]->pHead == NULL);
    assert(emptyInsertHash.table[1]->pTail == NULL);
    assert(emptyInsertHash.table[2]->pHead == NULL);
    assert(emptyInsertHash.table[2]->pTail == NULL);
    assert(emptyInsertHash.table[3]->pHead == NULL);
    assert(emptyInsertHash.table[3]->pTail == NULL);
    assert(emptyInsertHash.table[4]->pHead == NULL);
    assert(emptyInsertHash.table[4]->pTail == NULL);
    assert(*(emptyInsertHash.table[5]->pHead->data) == 12);
    assert(*(emptyInsertHash.table[5]->pTail->data) == 12);
    assert(emptyInsertHash.table[6]->pHead == NULL);
    assert(emptyInsertHash.table[6]->pTail == NULL);
    
    //inserting into prebuilt Hash
    
    //reusing multipleBucketsMultipleValuesHash
    //prebuilding as if inserted 8, 7, 9, 6.
    Hash<int>nonEmptyInsertHash(1);
    //resetting the Hash to have 3 buckets
    delete nonEmptyInsertHash.table[0];
    delete [] nonEmptyInsertHash.table;
    nonEmptyInsertHash.table = new list<int>*[3];
    nonEmptyInsertHash.table[0] = new list<int>();
    nonEmptyInsertHash.table[1] = new list<int>();
    nonEmptyInsertHash.table[2] = new list<int>();
    nonEmptyInsertHash.numBuckets = 3;
    nonEmptyInsertHash.numElements = 4;
    nonEmptyInsertHash.table[2]->pHead = new list<int>::node(8);
    nonEmptyInsertHash.table[2]->pTail = nonEmptyInsertHash.table[2]->pHead;
    nonEmptyInsertHash.table[1]->pHead = new list<int>::node(7);
    nonEmptyInsertHash.table[1]->pTail = nonEmptyInsertHash.table[1]->pHead;
    nonEmptyInsertHash.table[0]->pHead = new list<int>::node(9);
    nonEmptyInsertHash.table[0]->pHead->pNext = new list<int>::node(6);
    nonEmptyInsertHash.table[0]->pTail = nonEmptyInsertHash.table[0]->pHead->pNext;
    nonEmptyInsertHash.table[0]->pTail->pPrev = nonEmptyInsertHash.table[0]->pHead;
    /* hash array with lists is now (with <> meaning empty list)
     *                       [
     *                          <9,6>,
     *                          <7>,
     *                          <8>
     *                       ]
     */
    
    nonEmptyInsertHash.insert(22, hashInt);
    
    /* hash array with lists is now (with <> meaning empty list)
     *                       [
     *                          <9,6>,
     *                          <7,22>,
     *                          <8>
     *                       ]
     */
    assert(nonEmptyInsertHash.numBuckets == 3);
    assert(nonEmptyInsertHash.numElements == 5);
    assert(*(nonEmptyInsertHash.table[0]->pHead->data) == 9);
    assert(*(nonEmptyInsertHash.table[0]->pTail->data) == 6);
    assert(*(nonEmptyInsertHash.table[1]->pHead->data) == 7);
    assert(*(nonEmptyInsertHash.table[1]->pTail->data) == 22);
    assert(*(nonEmptyInsertHash.table[2]->pHead->data) == 8);
    assert(*(nonEmptyInsertHash.table[2]->pTail->data) == 8);
    
    
    nonEmptyInsertHash.insert(2, hashInt);
    /* hash array with lists is now (with <> meaning empty list)
     *                       [
     *                          <9,6>,
     *                          <7,22>,
     *                          <8,2>
     *                       ]
     */
    assert(nonEmptyInsertHash.numBuckets == 3);
    assert(nonEmptyInsertHash.numElements == 6);
    assert(*(nonEmptyInsertHash.table[0]->pHead->data) == 9);
    assert(*(nonEmptyInsertHash.table[0]->pTail->data) == 6);
    assert(*(nonEmptyInsertHash.table[1]->pHead->data) == 7);
    assert(*(nonEmptyInsertHash.table[1]->pTail->data) == 22);
    assert(*(nonEmptyInsertHash.table[2]->pHead->data) == 8);
    assert(*(nonEmptyInsertHash.table[2]->pTail->data) == 2);
    
    /* hash array with lists is now (with <> meaning empty list)
     *                       [
     *                          <9,6>,
     *                          <7,22>,
     *                          <8,2,11>
     *                       ]
     */
    nonEmptyInsertHash.insert(11, hashInt);
    assert(nonEmptyInsertHash.numBuckets == 3);
    assert(nonEmptyInsertHash.numElements == 7);
    assert(*(nonEmptyInsertHash.table[0]->pHead->data) == 9);
    assert(*(nonEmptyInsertHash.table[0]->pTail->data) == 6);
    assert(*(nonEmptyInsertHash.table[1]->pHead->data) == 7);
    assert(*(nonEmptyInsertHash.table[1]->pTail->data) == 22);
    assert(*(nonEmptyInsertHash.table[2]->pHead->data) == 8);
    assert(*(nonEmptyInsertHash.table[2]->pHead->pNext->data) == 2);
    assert(*(nonEmptyInsertHash.table[2]->pTail->data) == 11);
    
    cout<<"Passed Hash Insert Tests"<<endl;
    
    
    
    /*
     * Testing find
     */
    
    Hash<int> emptyFindHash(1);
    //resetting
    delete emptyFindHash.table[0];
    delete [] emptyFindHash.table;
    emptyFindHash.table = new list<int>*[1];
    emptyFindHash.table[0] = new list<int>();
    
    /* hash array with lists is now (with <> meaning empty list)
     *                       [
     *                          <>
     *                       ]
     */
    assert(emptyFindHash.find(31, hashInt) == false);
    
    Hash<int> nonEmptyFindHash(1);
    //resetting the Hash to have 3 buckets
    delete [] nonEmptyFindHash.table;
    nonEmptyFindHash.table = new list<int>*[3];
    nonEmptyFindHash.table[0] = new list<int>();
    nonEmptyFindHash.table[1] = new list<int>();
    nonEmptyFindHash.table[2] = new list<int>();
    nonEmptyFindHash.numBuckets = 3;
    nonEmptyFindHash.numElements = 4;
    nonEmptyFindHash.table[2]->pHead = new list<int>::node(8);
    nonEmptyFindHash.table[2]->pTail = nonEmptyFindHash.table[2]->pHead;
    nonEmptyFindHash.table[1]->pHead = new list<int>::node(7);
    nonEmptyFindHash.table[1]->pTail = nonEmptyFindHash.table[1]->pHead;
    nonEmptyFindHash.table[0]->pHead = new list<int>::node(9);
    nonEmptyFindHash.table[0]->pHead->pNext = new list<int>::node(6);
    nonEmptyFindHash.table[0]->pTail = nonEmptyFindHash.table[0]->pHead->pNext;
    nonEmptyFindHash.table[0]->pTail->pPrev = nonEmptyFindHash.table[0]->pHead;
    /* hash array with lists is now (with <> meaning empty list)
     *                       [
     *                          <9,6>,
     *                          <7>,
     *                          <8>
     *                       ]
     */
    
    assert(nonEmptyFindHash.find(8, hashInt) == true);
    assert(nonEmptyFindHash.find(7, hashInt) == true);
    assert(nonEmptyFindHash.find(9, hashInt) == true);
    assert(nonEmptyFindHash.find(6, hashInt) == true);
    
    assert(nonEmptyFindHash.find(-1, hashInt) == false);
    assert(nonEmptyFindHash.find(31, hashInt) == false);
    
    
    cout<<"Passed Hash Find Tests"<<endl;
    
    /*
     * Testing Hash for Non-Integer Behavior (just to see if it works for other types)
     */
    
    Hash<string> nameHash(12);
    nameHash.insert("",hashString);
    nameHash.insert(" ",hashString);
    nameHash.insert("~",hashString);
    nameHash.insert("Bob",hashString);
    nameHash.insert("bob",hashString);
    nameHash.insert("boB",hashString);
    nameHash.insert("Sue",hashString);
    nameHash.insert("sue",hashString);
    nameHash.insert("Suzy",hashString);
    nameHash.insert("Sven",hashString);
    nameHash.insert("Gunhilda",hashString);
    nameHash.insert("gunhilda",hashString);
    nameHash.insert("gunHilda",hashString);
    nameHash.insert("gunhildA",hashString);
    /* hash array with lists is now (with <> meaning empty list)
     *                       [
     *                          <boB>,
     *                          <Gunhilda,gunhilda,gunHilda>,
     *                          <Sue,sue>,
     *                          <~>,
     *                          <Suzy>,
     *                          <""," ",Sven,gunhildA>,
     *                          <>,
     *                          <>,
     *                          <>,
     *                          <>,
     *                          <>,
     *                          <>
     *                       ]
     */
    
    
    
    
    assert(*(nameHash.table[0]->pHead->data) == "boB");
    assert(*(nameHash.table[0]->pTail->data) == "boB");
    assert(*(nameHash.table[1]->pHead->data) == "Gunhilda");
    assert(*(nameHash.table[1]->pHead->pNext->data) == "gunhilda");
    assert(*(nameHash.table[1]->pHead->pNext->pNext->data) == "gunHilda");
    assert(*(nameHash.table[2]->pHead->data) == "Sue");
    assert(*(nameHash.table[2]->pTail->data) == "sue");
    assert(*(nameHash.table[3]->pHead->data) == "~");
    assert(*(nameHash.table[3]->pTail->data) == "~");
    assert(*(nameHash.table[4]->pHead->data) == "Suzy");
    assert(*(nameHash.table[4]->pTail->data) == "Suzy");
    assert(*(nameHash.table[5]->pHead->data) == "");
    assert(*(nameHash.table[5]->pHead->pNext->data) == " ");
    assert(*(nameHash.table[5]->pHead->pNext->pNext->data) == "Sven");
    assert(*(nameHash.table[5]->pHead->pNext->pNext->pNext->data) == "gunhildA");
    
    cout << "This Hash can hold strings!!!!" << endl;
    
}
