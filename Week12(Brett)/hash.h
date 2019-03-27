//
//  hash.h
//  Assignment 12
//
//  Created by Brett Mills on 3/26/19.
//  Copyright © 2019 Brett Mills. All rights reserved.
//

#ifndef hash_h
#define hash_h

#include <cstddef>
#include <iostream>

#include "list.h"

using namespace std;

#ifdef UNIT_TESTING
int main(int argc, const char* argv[]);
#endif

namespace custom
{
    template <class T>
    class Hash
    {
    public:
        // for testing purposes
        #ifdef UNIT_TESTING
            friend int ::main(int argc, const char* argv[]);
        #endif
        
        Hash(int numBuckets);
        Hash(const Hash & rhs);
        ~Hash();
        
        Hash <T> & operator=(const Hash & rhs) { return *this; }
        int capacity() { ; }
        bool empty()   { return true; }
        bool find(T t) { return true; }
        void insert(T t) { ; }

        
    private:
        // for testing purposes
        #ifdef UNIT_TESTING
            friend int ::main(int argc, const char* argv[]);
        #endif
        
        list<T> * table;
        int numElements;
        int numBuckets;
        
    };
    
    /*******************************************
     * HASH :: Non-Default Constructor
     *******************************************/
    template <class T>
    Hash<T>::Hash(int numBuckets)
    {
        try
        {
            this->numBucket = numBuckets;
            numElements = 0;
            table = new list<T>[numBuckets];
        }
        catch (std::bad_alloc)
        {
            throw "Error: Hashes must have at least 1 bucket.";
        }
    }
    
    /*******************************************
     * HASH :: Copy Constructor
     *******************************************/
    
    /*******************************************
     * HASH :: Assignment Operator
     *******************************************/
}


#endif /* hash_h */
