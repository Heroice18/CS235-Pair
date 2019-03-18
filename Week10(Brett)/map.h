//
//  map.h
//  Assignment 10
//
//  Created by Brett Mills on 3/12/19.
//  Copyright © 2019 Brett Mills. All rights reserved.
//

#ifndef map_h
#define map_h

#include <cstddef>
#include <iostream>
#include <stack>

#include "pair.h"
#include "bst.h"

using namespace std;

#ifdef UNIT_TESTING
int main(int argc, const char* argv[]);
#endif

namespace custom
{
    template <class K, class V>
    class map
    {
    private:
        BST <pair<K, V>> bst;
        
    public:
        // for testing purposes
        #ifdef UNIT_TESTING
            int main(int argc, const char* argv[]);
        #endif
        
        // constructors
        map() { bst = NULL; }
        map(map<K, V> &rhs) { *this = rhs; }
        ~map() { clear(); }
        
        // index operator
        V & operator[](const K &k);
        
        // assignment operator
        map<K, V> & operator=(map<K, V> &rhs);
        
        // standard interface functions
        int  size()  const { return bst.size();  }
        bool empty() const { return bst.empty(); }
        void clear()       { this->bst.clear();  }
        
        // technical functions
//        friend mapIterator;
        class mapIterator;
        
        mapIterator begin() { return bst.begin(); }
        mapIterator end()   { return bst.end();   }
        mapIterator find(K k);
        void insert(K k, V v);

    };
    
    template <class K, class V>
    class mapIterator
    {
    private:
        typename BST<pair<K, V>>::iterator it;
        
    public:
        // constructors
        mapIterator() { it = NULL; }
        mapIterator(typename BST<pair<K, V>>::BNode *x)   { it = x; }
        mapIterator(typename BST<pair<K, V>>::iterator x) { it = 0, it = x; }
        mapIterator(const mapIterator<K, V> &rhs)         { it = rhs.it; }
        // copy constructor
        mapIterator(mapIterator<K, V> &copy)              { *this = copy; }
        
        // operators
        bool operator==(const mapIterator<K, V> &rhs) { return rhs.it == this->it; }
        bool operator!=(const mapIterator<K, V> &rhs) { return rhs.it != this->it; }
        
        // decrement
        const mapIterator<K, V> &operator --()
        {
            --(this->it);
            return *this;
        }
        // increment
        const mapIterator<K, V> &operator ++()
        {
            ++(this->it);
            return *this;
        }
        // dereference
        const V &operator *()
        {
            return this->it.operator*().getSecond();
        }
    };
    
    /*******************************************
     * Map :: Assignment Operator
     *******************************************/
    template <class K, class V>
    map<K, V> & map<K, V> :: operator=(map<K, V> &rhs)
    {
        clear();
        if(rhs.bst.begin() != NULL)
        {
            this->bst = rhs.bst;
            this->numElements = rhs.numElements;
        }
        return *this;
    }
    
    /*******************************************
     * Map :: Index Operator
     *******************************************/
    template <class K, class V>
    V & map<K, V>::operator[](const K &k)
    {
        pair<K, V> pair(k,V());
    }
    
    /*******************************************
     * Map :: Insert
     *******************************************/
    template <class K, class V>
    void map<K, V>::insert(K k, V v)
    {
        
    }
}


#endif /* map_h */
