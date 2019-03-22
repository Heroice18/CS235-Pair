/*******************
Map header file
by Brandon Ison, Brett Mills
*****************/
#ifndef map_h
#define map_h

#include <cstddef>
#include <iostream>
#include <stack>

//#include "pair.h"
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

       // template <class K, class V>
          class iterator
        {
        public:
        typename BST<pair>::iterator it;


        #ifdef UNIT_TESTING
            int main(int argc, const char* argv[]);
        #endif

        // constructors
        iterator() { it = NULL; }
        iterator(typename BST<pair>::BNode *x)   { it = x; }
        iterator(typename BST<pair>::iterator x) { it = 0, it = x; }
        iterator(const iterator &rhs)         { it = rhs.it; }
        // copy constructor
        iterator(iterator &copy)              { *this = copy; }

        // operators
        bool operator==(const iterator &rhs) { return rhs.it == this->it; }
        bool operator!=(const iterator &rhs) { return rhs.it != this->it; }

        // decrement
        const iterator &operator --()
        {
            --(this->it);
            return *this;
        }
        // increment
        const iterator &operator ++()
        {
            ++it;
            return *this;
        }
        // dereference
        const pair &operator *()
        {
            if(it == NULL)
            {
                throw "Error: dereferencing null node.";
            }
            return *it;
        }
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
        int  size()  { return bst.size();  }
        bool empty() const { return bst.empty(); }
        void clear()       { this->bst.clear();  }

        // technical functions
        class iterator;

        iterator begin() { return bst.begin(); }
        iterator end()   { return bst.end();   }
        iterator find(K k){

            // pair test(k, V());
            // BST<pair> check = bst.find(test);

            // if(check == NULL){
            //     bst.insert(test);
            //     check = bst.find(check);
            // }

            // return (*check).second;

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
    V & map<K, V>::operator[](const K &k)
    {
        pair pair(k,V());
    }

    /*******************************************
     * Map :: Insert
     *******************************************/
    template <class K, class V>
    void map<K, V>::insert(K k, V v)
    {

    }

//    /*****************************************************
//     * PAIR INSERTION
//     * Display a pair for debug purposes
//     ****************************************************/
//    template <class K, class V>
//    inline std::ostream & operator << (std::ostream & out, const pair & rhs)
//    {
//        out << '(' << rhs.first << ", " << rhs.second << ')';
//        return out;
//    }
//
//    /*****************************************************
//     * PAIR EXTRACTION
//     * input a pair
//     ****************************************************/
//    template <class K, class V>
//    inline std::istream & operator >> (std::istream & in, pair & rhs)
//    {
//        in >> rhs.first >> rhs.second;
//        return in;
//    }
}


#endif /* map_h */