#ifndef list_h
#define list_h

#include <cstddef>
#include <iostream>

using namespace std;

#ifdef UNIT_TESTING
int main(int argc, const char* argv[]);
#endif

namespace custom
{
    template <class T>
    class list
    {
    public:
            /*******************************************
         * Node Class
         *******************************************/
        class node
        {
            friend list;
        private:
            #ifdef UNIT_TESTING
                friend int ::main(int argc, const char* argv[]);
            #endif

            T data;
            node * pNext;
            node * pPrev;
            friend class iterator;
            node()
            {
                data  = NULL;
                pNext = NULL;
                pPrev = NULL;
            }
            node(T t)
            {
                data  = t;
                pNext = NULL;
                pPrev = NULL;
            }
        };

        // list private data
        node * pHead;
        node * pTail;
        int    numElements;


        // for testing purposes
        #ifdef UNIT_TESTING
            friend int ::main(int argc, const char* argv[]);
        #endif

        // constructors
        list();
        list(const T &t);
        list(const list & rhs);
        ~list();

        // operators
        list <T> & operator=(const list & rhs);

        // standard container interfaces
        int  size()  { return numElements; }
        bool empty() { return pHead == NULL; }
        void clear();

        // list specific
        void push_front(const T t);
        void push_back (const T t);
        void pop_front();
        void pop_back();

        T & front()       throw(const char *); // might not need
        T   front() const throw(const char *);

        T & back()        throw(const char *); // might not need
        T   back()  const throw(const char *);

        // iterator stuff
        class iterator;
        iterator erase(iterator it);
        iterator insert(iterator & it, const T & data) throw(const char *);
        iterator find(T t);

        iterator begin() { return iterator(pHead); }
        iterator end()   { return iterator(NULL);  }

        /*******************************************
         * Iterator Class
         *******************************************/
        class iterator
        {
            friend list;
            friend node;
        private:
            typename list <T> :: node * ptr;

        public:
            friend list;

            // for testing purposes
            #ifdef UNIT_TESTING
                friend int ::main(int argc, const char* argv[]);
            #endif

            // constructors, destructors, and assignment operator
            iterator()           : ptr(NULL)        {              }
            iterator(node * ptr) : ptr(ptr)         {              }
            iterator(const iterator & rhs) { *this = rhs; }
            iterator & operator = (const iterator & rhs)
            {
                this->ptr = rhs.ptr;
                return *this;
            }
            // equals, not equals operator
            bool operator != (const iterator & rhs) const { return rhs.ptr != this->ptr; }
            bool operator == (const iterator & rhs) const { return rhs.ptr == this->ptr; }

            T & operator * ()
            {
                if (NULL != this->ptr)
                {
                    if(this->ptr->data == NULL)
                    {
                        throw "Error: dereferencing null data";
                    }

                    return this->ptr->data;
                }
                else
                    throw "Error: dereferencing null node.";
            }

            const T & operator * () const
            {
                if (this->ptr != NULL)
                {
                    if(this->ptr->data != NULL)
                    {
                        return this->ptr->data;
                    }
                }
                else
                    throw "Error: dereferencing null data.";
            }

            // prefix increment
            iterator & operator ++ ()
            {
                // check if ptr is NULL
                if (ptr)
                {
                    if(ptr->pNext == NULL)
                    {
                        return *this;
                    }
                    ptr = ptr->pNext;
                    return *this;
                }
                else
                    throw "Error: incrementing null node.";
            }
            // postfix increment
            iterator operator ++ (int postfix)
            {
                // check if ptr is NULL
                if (ptr != NULL)
                {
                    if(ptr->pNext == NULL)
                    {
                        return ptr;
                    }
                    iterator tmp(*this);
                    ptr = ptr->pNext;
                    return tmp;
                }
                else
                    throw "Error: incrementing null node.";

            }
            // prefix decrement
            iterator & operator -- ()
            {
                // check if ptr is NULL
                if (ptr)
                {
                    if(ptr->pPrev == NULL)
                    {
                        return *this;
                    }
                    ptr = ptr->pPrev;
                }
                else
                    throw "Error: decrementing null node.";
                return *this;
            }
            // postfix decrement
            iterator operator -- (int postfix)
            {
                // check if ptr is NULL
                if (ptr)
                {
                    if(ptr->pPrev == NULL)
                    {
                        return ptr;
                    }
                    iterator tmp(*this);
                    ptr = ptr->pPrev;
                    return tmp;
                }
                else
                    throw "Error: decrementing null node.";
                return *this;
            }

            friend iterator list<T>::insert(iterator & it, const T & data) throw(const char *);
            friend iterator list<T>::erase(iterator it);
        };


    };

    /*******************************************
     * LIST :: Default Constructor
     *******************************************/
    template <class T>
    list<T>::list()
    {
        pHead = NULL;
        pTail = NULL;
        numElements = 0;
    }

    /*******************************************
     * LIST :: Non-Default Constructor
     *******************************************/
    template <class T>
    list<T>::list(const T &t)
    {
        numElements = 0;
        try
        {
            pHead = new node(t);
            pTail = pHead;
            numElements++;
        }
        catch (bad_alloc)
        {
            throw "ERROR: unable to allocate a new node for a list";
        }
    }

    /*******************************************
     * LIST :: Copy Constructor
     *******************************************/
    template <class T>
    list<T>::list(const list & rhs)
    {
        numElements = 0;
       // cerr << " @0" << endl;

        if (rhs.pHead != NULL)
        {
           // cerr << " @1" << endl;
            try
            {
               // cerr << " @2" << endl;
                pHead = new node(rhs.pHead->data);
                numElements++;

                node * pCurrent = pHead;
                node * pSource = rhs.pHead;

                while (pSource->pNext)
                {
                  //  cerr << " @3" << endl;
                    pSource = pSource->pNext;
                    pCurrent->pNext = new node(pSource->data);
                    pCurrent->pPrev = pSource->pPrev;
                    pCurrent = pCurrent->pNext;
                    numElements++;
                }
                // didn't need this line of code
                // not sure why though
//                pCurrent->pPrev = pSource->pPrev;
               // cerr << " @4" << endl;
                pTail = pCurrent;
            }
            catch (bad_alloc)
            {
                throw "ERROR: unable to allocate a new node for a list";
            }
        }
        else
        {
            pHead = NULL;
            pTail = NULL;
        }
    }

    /*******************************************
     * LIST :: Destructor
     *******************************************/
    template <class T>
    list<T>::~list()
    {
        while (pHead != NULL)
        {
            node *pDelete = pHead;
            pHead = pHead->pNext;
            delete pDelete;
        }
    }

    /*******************************************
     * LIST :: Assignment Operator
     *******************************************/
    template <class T>
    list<T> & list<T>::operator=(const list<T> &rhs)
    {
        // erase existing elements
        clear();

        // allocate new elements
        for (node * p = rhs.pHead; p; p = p->pNext)
        {
            push_back(p->data);
        }

        return *this;
    }

    /*******************************************
     * LIST :: Clear
     *******************************************/
    template <class T>
    void list<T>::clear()
    {
        //  NOTE TO SELF
        // pHead when clear() is called is NULL the first time

//        cout << "outside if statement " << pHead << endl;

//        if (pHead)
//        {
//            // iterate throught every node of linked list
////            cout << pHead << endl;
//            while (pHead != NULL)
//            {
//                node *pDelete = pHead;
////                pHead = pHead->pNext;
//
//                pDelete = NULL;
//                delete pDelete;
//            }
////            cout << "while loop once" << endl;
//            pTail = pHead;
//            numElements = 0;
//        }

        while (pHead != NULL)
        {
            //cerr << " list delete" << endl;
            node *pDelete = pHead;
            pHead = pHead->pNext;
            delete pDelete;
        }

        pTail = pHead;
        numElements = 0;

    }

    /*******************************************
     * LIST :: Push Front
     *******************************************/
    template <class T>
    void list<T>::push_front(const T t)
    {
        try
        {
            // create new node with user input data
            node *pNew = new node(t);

            // check if container is empty
            if (pHead == NULL)
            {
                pHead = pNew;
                pTail = pNew;
                numElements++;
            }
            else
            {
                pHead->pPrev = pNew;
                pNew->pNext = pHead;
                pHead = pNew;
                numElements++;
            }
        }
        catch (bad_alloc)
        {
            throw "ERROR: unable to allocate a new node for a list";
        }
    }

    /*******************************************
     * LIST :: Push Back
     *******************************************/
    template <class T>
    void list<T>::push_back(const T t)
    {
        try
        {
            // create new node with user input data
            node *pNew = new node(t);

            // check if container is empty
            if (pHead == NULL)
            {
                pHead = pNew;
                pTail = pNew;
                numElements++;
            }
            else
            {
                pTail->pNext = pNew;
                pNew->pPrev = pTail;
                pTail = pNew;
                numElements++;
            }
        }
        catch (bad_alloc)
        {
            throw "ERROR: unable to allocate a new node for a list";
        }
    }

    /*******************************************
     * LIST :: Pop Front
     *******************************************/
    template <class T>
    void list<T>::pop_front()
    {
        if (pHead)
        {
            // new node to keep track of pHead
            node *pDelete = pHead;

            pHead = pHead->pNext;
            // if more than one node
            if (pHead && pHead->pNext)
            {
                pHead = pHead->pNext->pPrev;
            }
            pDelete = pHead->pPrev;
            delete pDelete;

            // free up the space
            pHead->pPrev = NULL;
            pDelete = NULL;

            numElements--;

            if (pHead == NULL)
            {
                pTail = pHead;
            }
        }
    }

    /*******************************************
     * LIST :: Pop Back
     *******************************************/
    template <class T>
    void list<T>::pop_back()
    {
        if (pTail)
        {
            // new node to keep track of pTail
            node *pDelete = pTail;

            pTail = pTail->pPrev;
            // if more than one node
            if (pTail && pTail->pPrev)
            {
                pTail->pPrev->pNext = pTail;
            }
            pDelete = pTail->pNext;
            delete pDelete;

            // free up the space
            pTail->pNext = NULL;
            pDelete = NULL;

            numElements--;

            if (pTail == NULL)
            {
                pHead = pTail;
            }
        }
    }

    /*******************************************
     * LIST :: Front
     *******************************************/
    template <class T>
    T & list<T>::front() throw(const char *)
    {
        if (empty())
        {
            throw "Error: calling front on empty list.";
        }
        else
        {
            return pHead->data;
        }
    }

    /*******************************************
     * LIST :: Back
     *******************************************/
    template <class T>
    T & list<T>::back() throw(const char *)
    {
        if (empty())
        {
            throw "Error: calling back on empty list.";
        }
        else
        {
            return pTail->data;
        }
    }

    /*******************************************
     * LIST :: Insert
     *******************************************/
    template <class T>
    typename list<T>:: iterator list<T>::insert(iterator &it, const T & data) throw(const char *)
    {
        if (empty())
        {
            pHead = new node(data);
            pTail = pHead;
            return begin();
        }

        try
        {
            node *pNode = new node(data);

            if (it == end())
            {
                pTail->pNext = pNode;
                pNode->pPrev = pTail;
                pTail = pNode;
                it = pNode;
            }
            else
            {
                pNode->pNext = it.ptr;
                pNode->pPrev = it.ptr->pPrev;

                // check tail
                if (pNode->pNext)
                {
                    pNode->pNext->pPrev = pNode;
                }
                else
                {
                    pTail = pNode;
                }

                // check head
                if (pNode->pPrev)
                {
                    pNode->pPrev->pNext = pNode;
                }
                else
                {
                    pHead = pNode;
                }

                it = pNode;
            }
            numElements++;

            return it;
        }
        catch (bad_alloc)
        {
            throw "ERROR: unable to allocate a new node for a list";
        }
    }

    /*******************************************
     * LIST :: Erase
     *******************************************/
    template <class T>
    typename list<T>:: iterator list<T>::erase(iterator it)
    {
        iterator itReturn = end();

        if (it == end())
        {
            return end();
        }

        // next
        if (it.ptr->pNext)
        {
            it.ptr->pNext->pPrev = it.ptr->pPrev;
            itReturn = it.ptr->pNext;
        }
        else
        {
            pTail = pTail->pPrev;
        }

        // prev
        if (it.ptr->pPrev)
        {
            it.ptr->pPrev->pNext = it.ptr->pNext;
            itReturn = it.ptr->pPrev;
        }
        else
        {
            pHead = pHead->pNext;
        }

//        if (it.ptr->pPrev)
//        {
//            it.ptr->pPrev->pNext = it.ptr->pNext;
//        }
//        if (it.ptr->pNext)
//        {
//            it.ptr->pNext->pPrev = it.ptr->pPrev;
//        }
//
//        if (it.ptr->pPrev)
//        {
//            itReturn = it.ptr->pPrev;
//        }
//        else
//        {
//            itReturn = it.ptr->pNext;
//        }

        delete it.ptr;
        it.ptr = NULL;
        numElements--;

        return itReturn;
    }

    /*******************************************
     * LIST :: Find
     *******************************************/
    template <class T>
    typename list<T>:: iterator list<T>::find(T t)
    {
        for (node *p = pHead; p; p = p->pNext)
        {
            if (p->data == t)
            {
                return p;
            }
        }
        return end();
    }


}
#endif /* list_h */
