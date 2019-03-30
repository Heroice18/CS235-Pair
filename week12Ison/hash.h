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

        Hash();
        Hash(const int &numBuckets);
        Hash(const Hash & rhs);
        ~Hash();

        Hash <T> & operator=(const Hash & rhs);//{ return *this; }
        int capacity() { return numBuckets; }
        bool empty()   { return numElements == 0; }
        bool find(T aValue, long (*h)(const T& aValue, long theBucketCount));// { return true; }
        void insert(T aValue, long (*h)(const T& valueToHash, long theBucketCount));// { ; }
        int size(){ return numElements; }


        list<T>** table;
        int numElements;
        int numBuckets;

        // for testing purposes




    };
    template<class T>
    Hash<T>::Hash(){
        numBuckets = 0;
        numElements = 0;
        cout << "construct " << endl;
        table = new list<T>*[numBuckets];
        //table = NULL;
    }

    /*******************************************
     * HASH :: Non-Default Constructor
     *******************************************/
    template <class T>
    Hash<T>::Hash(const int &Buckets)
    {
      int copy = Buckets;
       // cout << copy << " " << endl;
       // cout << " " << Buckets << endl;
       // cout << "construct " << endl;
       if (copy < 0)
       {
         //cout << "1" << endl;
        throw "Error: Hashes must have at least 1 bucket.";

       }
       else if (Buckets == 0)
       {
         //cout << "2" << endl;
            throw "Error: Hashes must have at least 1 bucket.";
       }

       numBuckets = Buckets;
       //cout << "buckets " << endl;
       table = new list<T>*[numBuckets];
       //cout << "new table " << endl;
       numElements = 0;
       for(int i = 0; i < Buckets; i++ )
       {
         table[i] = new list<T>;
       }

       /* try
        {
            this->numBuckets = numBuckets;
            numElements = 0;
            table = new list<T>*[numBuckets];
        }
        catch (std::bad_alloc)
        {
            throw "Error: Hashes must have at least 1 bucket.";
        }*/
    }

    /*******************************************
     * HASH :: Copy Constructor
     *******************************************/
    template<class T>
    Hash<T>::Hash(const Hash & rhs)
    {
      //cout << " copy construct " << endl;
      table = new list<T>*[rhs.numBuckets];
      for(int i = 0; i < rhs.numBuckets; i++)
      {
         table[i] = new list<T>(*rhs.table[i]);
      }
      numBuckets = rhs.numBuckets;
      numElements = rhs.numElements;

    }

     /*******************************************
     * HASH :: Dereference Constructor
     *******************************************/
     template<class T>
     Hash<T>::~Hash()
     {
//      cout << "destroy construct " << endl;

      for(int i = 0; i < numBuckets; i++)
      {
          table[i]->clear();
          delete table[i];

      }

     delete [] table;

     table = NULL;

     }


    /*******************************************
     * HASH :: Assignment Operator
     *******************************************/
     template<class T>
     Hash<T> & Hash<T>::operator=(const Hash & rhs)
     {

      for(int i = 0; i < numBuckets; i++)
      {
         table[i]->clear();
         delete table[i];
        // cout << "@0" << endl;
      }
      delete [] table;
      //cout << "@1" << endl;

      table = new list<T>*[rhs.numBuckets];
      for(int i = 0; i < rhs.numBuckets; i++)
      {
         table[i] = new list<T>(*rhs.table[i]);
      }
      numBuckets = rhs.numBuckets;
      numElements = rhs.numElements;

      // return *this;

     }

     /*******************************************
     * HASH :: Assignment Operator
     *******************************************/
     template<class T>
     void Hash<T>::insert(T aValue, long (*h)(const T& valueToHash, long theBucketCount))
     {
         table[h(aValue, numBuckets)]->push_back(aValue);
         numElements++;

     }

     template<class T>
     bool Hash<T>::find(T aValue, long (*h)(const T& aValue, long theBucketCount))
     {
         typename list<T>::iterator check = NULL;
         return check != table[h(aValue, numBuckets)]->find(aValue);
         //numElements++;

     }



     // template<class T>
     // Hash<T> & Hash<T>::operator=(const Hash & rhs)
     // {

     //  for(int i = 0; i < numBuckets; i++)
     //  {
     //     table[i]->clear();
     //     delete table[i];
     //     cout << "@0" << endl;
     //  }
     //  delete [] table;
     //  cout << "@1" << endl;

     //  table = new list<T>*[rhs.numBuckets];
     //  for(int i = 0; i < rhs.numBuckets; i++)
     //  {
     //     table[i] = new list<T>(*rhs.table[i]);
     //  }
     //  numBuckets = rhs.numBuckets;
     //  numElements = rhs.numElements;

     //  // return *this;

     // }

}


#endif /* hash_h */
