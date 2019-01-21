/***********************************************************************
* Header:
*    INFIX
* Summary:
*    This will contain just the prototype for the convertInfixToPostfix()
*    function
* Author
*    <your names here>
************************************************************************/

#ifndef stack_h
#define stack_h

#include <cstddef>
#include<iostream>

#ifdef UNIT_TESTING
int main(int argc, const char* argv[]);
#endif

namespace custom
{

template <class T>
class stack
{
private:
    T * buffer;
    int numElements;
    int numCapacity;




public:
    // for testing purposes (stack tests)
    #ifdef UNIT_TESTING
        friend int ::main(int argc, const char* argv[]);
    #endif

    // constructors and destructor
    stack();
    stack(int numCapacity);
    stack(const stack & rhs);
    ~stack();

    // assignment operator
    stack & operator = (const stack & rhs);

    // standard container interfaces
    int  size()     const { return numElements; }
    int  capacity() const { return numCapacity; }
    void clear()          { numElements = 0; }
    bool empty()
    {
        if (size() == 0)
            return true;
        else
            return false;
    }

    void push(T t);
    void pop();
    void resize(int cap) throw (const char*);
    // top setter (changes w/ pass by reference)
    //T    top() throw (const char *);
    // top getter
    T  &  top() const;
};

    /*******************************************
     * VECTOR :: DEFAULT CONSTRUCTOR
     *******************************************/
    template <class T>
    stack<T>::stack()
    {

        buffer = NULL;
        numElements = 0;
        numCapacity = 0;
    }


    template <class T>
    void stack<T>::resize(int cap) throw (const char*)
    {
         //std::cout << cap;
      if(cap >= 0)
      {
         T * Temp = NULL;

         //std::cout << cap;
         try{

            if(cap > 0)
            {
            Temp = new T[cap];
            }
            //std::cout << cap;
            if(cap < numElements)
            {
                numElements = cap;
            }


            numCapacity = cap;

            //std::cout << cap;
            if (buffer != NULL && Temp != NULL)
	       {

                   for (int i = 0; i < cap; ++i)
                   {
                     Temp[i] = buffer[i];
                   }
                   delete [] buffer;
	       }
            buffer = Temp;
         }

         catch(std::bad_alloc){
            throw "new cannot be done";
         }
      }
    }

      /**********************************************
     * STACK : NON-DEFAULT CONSTRUCTOR
     * Preallocate the array to "capacity"
     **********************************************/
    template<class T>
    stack<T>::stack(int numCapacity)
    {
        // do nothing if there is nothing to do.
        if (numCapacity == 0)
        {
            this->numCapacity = this->numElements = 0;
            this->buffer = NULL;
            return;
        }

        // attempt to allocate
        try
        {
            buffer = new T[numCapacity];
        }
        catch (std::bad_alloc)
        {
            throw "ERROR: Unable to allocate buffer";
        }


        // copy over the stuff
        this->numCapacity = numCapacity;
        this->numElements = 0;

        for (int i = 0; i < numCapacity; i++)
        {
            buffer[i] = T();
        }
    }

    /*******************************************
     * STACK :: COPY CONSTRUCTOR
     *******************************************/
    template<class T>
    stack<T>::stack(const stack & rhs)
    {
        // set to NULL to prevent assignment operator from deleting data
        buffer = NULL;
        // copy contents
        *this = rhs;
    }

    /*******************************************
     * VECTOR :: DESTRUCTOR
     *******************************************/
    template<class T>
    stack<T>::~stack()
    {
        clear();
    }

    /*******************************************
     * STACK :: Assignment
     *******************************************/
    template <class T>
    stack<T> & stack<T> :: operator = (const stack<T> &rhs)
    {
        // check if its the same thing
        if (this == &rhs)
        {
            return *this;
        }

        // check to see if the size
        if (numCapacity < rhs.size())
        {
            delete [] buffer;
            // set size and cap
            numElements = rhs.numElements;
            numCapacity = rhs.numCapacity;
            // allocate memory to new array
            buffer = new T[numCapacity];
        }

        // copy data
        for (int i = 0; i <= rhs.size(); i++)
        {
            buffer[i] = rhs.buffer[i];
        }

        return *this;
    }

    /*******************************************
     * VECTOR :: Push
     *******************************************/
    template <class T>
    void stack<T>::push(T t)
    {

        if (size() == capacity())
        {
            if(capacity() == 0)
            {
                resize(1);
            }
            else
            {
               resize(capacity() * 2);
            }
            //int cap = numCapacity == 0 ? 1 : numCapacity * 2;
            //resize(cap);
        }

        buffer[numElements++] = t;
    }

    /*******************************************
     * VECTOR :: Pop
     *******************************************/
    template <class T>
    void stack<T>::pop()
    {
        if (!empty())
        {
            --numElements;
        }
    }

    /*******************************************
     * VECTOR :: Top
     *******************************************/
    /*template <class T>
    T stack<T>::top() throw(const char *)
    {
        if (!empty())
        {
            return buffer[size() - 1];
        }
        else
            throw "ERROR";
    }

    /*******************************************
     * VECTOR :: Top CONST
     *******************************************/
    template <class T>
    T &stack<T>::top() const
    {
        return buffer[numCapacity];
    }


}
#endif /* stack_h */
