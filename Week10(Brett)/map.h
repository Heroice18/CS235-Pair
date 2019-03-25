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
        
    public:
        // for testing purposes
        #ifdef UNIT_TESTING
        friend int ::main(int argc, const char* argv[]);
        #endif
        
        /*******************************************
         * Map :: Pair Class
         *******************************************/
        class pair
        {
        public:
            #ifdef UNIT_TESTING
                int main(int argc, const char* argv[]);
            #endif
            
            // constructors
            pair() {}
            pair(const K & first, const V & second) : first(first), second(second) {}
            pair(const pair & rhs) : first(rhs.first), second(rhs.second) {}
            
            // copy the values
            pair & operator = (const pair & rhs)
            {
                first  = rhs.first;
                second = rhs.second;
                return *this;
            }
            
            // constant fetchers
            const K & getFirst()  const { return first;  }
            const V & getSecond() const { return second; }
            
            // compare Pairs.  Only first will be compared!
            bool operator >  (const pair & rhs) const { return first >  rhs.first; }
            bool operator >= (const pair & rhs) const { return first >= rhs.first; }
            bool operator <  (const pair & rhs) const { return first <  rhs.first; }
            bool operator <= (const pair & rhs) const { return first <= rhs.first; }
            bool operator == (const pair & rhs) const { return first == rhs.first; }
            bool operator != (const pair & rhs) const { return first != rhs.first; }
            
            // these are public.  We cannot validate!
            K first;
            V second;
            
            // END of Pair class
        };
        
        /*******************************************
         * Map :: Iterator Class
         *******************************************/
        class iterator
        {
        public:
            #ifdef UNIT_TESTING
                int main(int argc, const char* argv[]);
            #endif
            friend pair;
            
            typename BST<pair>::iterator it;
            
            // constructors
            iterator() { it = NULL; }
            iterator(typename BST<pair>::BNode *x)   { it = x; }
            iterator(typename BST<pair>::iterator x) { it = 0, it = x; }
            iterator(const iterator &rhs)            { it = rhs.it; }
            // copy constructor
            iterator(iterator &copy)                 { *this = copy; }
            
            // operators
            bool operator==(const iterator &rhs) { return rhs.it == this->it; }
            bool operator!=(const iterator &rhs) { return rhs.it != this->it; }
            
            // decrement
            iterator operator--()
            {
                if (it == NULL)
                {
                    throw "Error: decrementing null node.";
                }
                --it;
                return *this;
            }
            iterator operator--(int postfix)
            {
                return iterator(it--);
            }
            // increment
            iterator operator++()
            {
                if (it == NULL)
                {
                    throw "Error: incrementing null node.";
                }
                ++it;
                return *this;
            }
            iterator operator++(int postfix)
            {
                return iterator(it++);
            }
            
            // dereference
            pair &operator *() // this is not supposed to be "const"
            {
                if (it == NULL)
                {
                    throw "Error: dereferencing null node.";
                }
                return *it;
            }
            
            // END of Iterator class
        };
    
        // constructors
        map() {}
        map(map<K, V> &rhs) { *this = rhs; }
        ~map() { clear(); }
        
        // index operator
        V & operator[](const K &k);
        
        // assignment operator
        map<K, V> & operator=(map<K, V> &rhs);
        
        // standard interface functions
        int  size()        { return bst.size();  }
        bool empty() const { return bst.empty(); }
        void clear()       { this->bst.clear();  }
        
        // technical functions
        iterator begin() { return bst.begin(); }
        iterator end()   { return bst.end();   }
        iterator find(const K &k)
        {
            pair pair(k, V());
            iterator it = bst.find(pair);
            return iterator(it);
        }
        void insert(K k, V v);

    private:
        BST <pair> bst;
        
        // END of Map class
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
        }
        return *this;
    }
    
    /*******************************************
     * Map :: Index Operator
     *******************************************/
    template <class K, class V>
    V & map<K, V>::operator[](const K& k)
    {
        // from Bro Manley
        
        pair pair(k, V());
        iterator it = bst.find(pair);
        if (it == NULL)
        {
            bst.insert(pair);
            it = bst.find(pair);
        }
        return (*it).second;
    }
    
    /*******************************************
     * Map :: Insert
     *******************************************/
    template <class K, class V>
    void map<K, V>::insert(K k, V v)
    {
        pair pair(k, V());
        iterator it = bst.find(pair);
        if (it == NULL)
        {
            *it = pair;
        }
        else
            bst.insert(pair);
    }
}


#endif /* map_h */


