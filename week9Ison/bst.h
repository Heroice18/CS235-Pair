/***********************************************************************
 * Header:
 *    bst.h
 *
 * Author
 *    Brandon Ison, Brett Mills
 ************************************************************************/

#ifndef bst_h
#define bst_h

#include <cstddef>
#include <iostream>

using namespace std;

#ifdef UNIT_TESTING
int main(int argc, const char* argv[]);
#endif

namespace custom
{
    template <class T>
    class BST
    {
    private:
        /*******************************************
         * BNode Class
         *******************************************/
        class BNode
        {
            friend BST;
        private:
//            void verifyRB(int depth);
//            void verifyBST();
//            void balance();
        public:
            #ifdef UNIT_TESTING
                friend int ::main(int argc, const char* argv[]);
            #endif
            T data;
            BNode *pLeft;
            BNode *pRight;
            BNode *pParent;
            bool  isRed;
            BNode()
            {
                data    = NULL;
                pLeft   = NULL;
                pRight  = NULL;
                pParent = NULL;
                isRed   = false;
            }
            BNode(T t)
            {
                data = t;
                pLeft   = NULL;
                pRight  = NULL;
                pParent = NULL;
                isRed   = false;
            }

        };
        // BST private member data
        BNode * root;
        int numElements;

        // private functions
//        void deleteNode(BNode deleteNode, bool right);
        void    deleteBTree(BNode *&deleteBST);
        BNode * copyBTree  (BNode *pSrc);

    public:
        // for testing purposes
        #ifdef UNIT_TESTING
            friend int ::main(int argc, const char* argv[]);
        #endif

        //constructors
        BST()  { root = NULL; numElements = 0; }
        BST(const BST & rhs);
        ~BST() { clear(); }
        // operator
        //BST <T> & operator=(const BST & rhs);
        // standard interface containers
        class iterator;
        int  size()        { return numElements; }
        bool empty() const { return numElements == 0; }
        void clear();
        void insert(const T &t);
        void erase(iterator it);
        iterator find(const T &t);
        iterator begin();
//        iterator rbegin();
        iterator end();
        iterator rend() { return iterator(NULL); }

        /*******************************************
         * Iterator Class
         *******************************************/
        class iterator
        {
            friend BST;
            friend BNode;
        private:
            typename BST <T> :: BNode * ptr;

        public:
            friend BST;

            // for testing purposes
            #ifdef UNIT_TESTING
                friend int ::main(int argc, const char* argv[]);
            #endif

            // constructors, destructors, and assignment operator
            iterator()            : ptr(NULL)       {              }
            iterator(BNode * ptr) : ptr(ptr)        {              }
            iterator(const iterator & rhs)          { *this = rhs; }
            iterator & operator = (const iterator & rhs)
            {
                this->ptr = rhs.ptr;
                return *this;
            }
            // equals, not equals operator
            bool operator != (const iterator & rhs) const { return rhs.ptr != this->ptr; }
            bool operator == (const iterator & rhs) const { return rhs.ptr == this->ptr; }
            // dereference operator
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
            // Increment & Decrement operators
            // check line 1172
            iterator & operator--()
            {
                return *this;
            }
            iterator & operator--(int postfix);
            iterator & operator++()
            {
                return *this;
            }
            iterator & operator++(int postfix);
            // END of iterator class
        };

        // END of BST class
    };

 /*******************************************
     * BST :: Copy Constructor
     *******************************************/
  template<class T>
  BST<T>::BST(const BST & rhs)
  {
      if(rhs.root == NULL)
      {
         root = NULL;
         numElements = 0;
        // *this = rhs;

      }
      else
      {
            numElements = 0;
         copyBTree(rhs.root);
         //cout << "HI";
      }
  }

/*******************************************
     * BST :: Clear
     *******************************************/
    template <class T>
    void BST<T>::clear()
    {
        if (root)
        {
            deleteBTree(root);
        }
        root = NULL;
    }

    /*******************************************
     * BST :: Insert
     *******************************************/
    template <class T>
    void BST<T>::insert(const T &t)
    {
       BNode *newNode = new BNode(t);
       BNode *parentNode = root;
       BNode *destinationNode = root;

      while(destinationNode != NULL)
       {
         if(t < destinationNode->data)
            {
                  parentNode = destinationNode;
                  destinationNode = destinationNode->pLeft;
            }
         else
         {
               parentNode = destinationNode;
               destinationNode = destinationNode->pRight;
         }

      }

      if(parentNode !=NULL)
      {
         if(t < parentNode->data)
            {
               newNode->pParent = parentNode;
               parentNode->pLeft = newNode;
            }
         else
            {
               newNode->pParent = parentNode;
               parentNode->pRight = newNode;
            }
      }
      else
      {
         root = newNode;
      }
      numElements++;

    }

    /*******************************************
     * BST :: Erase
     *******************************************/
    template <class T>
    void BST<T>::erase(iterator it)
    {

    }

    /*******************************************
     * BST :: Begin
     *******************************************/
    template <class T>
    typename BST<T>:: iterator BST<T>::begin()
    {
       //BNode *newNode = new BNode(t);
       BNode *parentNode = root;
       BNode *destinationNode = root;
       while(destinationNode != NULL)
       {
          parentNode = destinationNode;
          destinationNode = destinationNode -> pLeft;
       }

        return parentNode; // temporary, not final
    }

    /*******************************************
     * BST :: End
     *******************************************/
    template <class T>
    typename BST<T>:: iterator BST<T>::end()
    {
       //BNode *newNode = new BNode(t);
       BNode *parentNode = root;
       BNode *destinationNode = root;
       while(destinationNode != NULL)
       {
          parentNode = destinationNode;
          destinationNode = destinationNode -> pRight;
       }

        return parentNode; // temporary, not final
    }

    /*******************************************
     * BST :: find
     *******************************************/
    template <class T>
    typename BST<T>:: iterator BST<T>::find(const T &t)
    {
       BNode *newNode = new BNode(t);
       BNode *parentNode = root;
       BNode *destinationNode = root;
       while(destinationNode != NULL)
       {
         if(t < destinationNode->data)
            {
                  parentNode = destinationNode;
                  destinationNode = destinationNode->pLeft;
            }
         else if(t > destinationNode->data)
         {
               parentNode = destinationNode;
               destinationNode = destinationNode->pRight;
         }
         else
         {
            return destinationNode;
         }


       }
       /*

       if(parentNode !=NULL)
      {
         if(t < parentNode->data)
            {
               newNode->pParent = parentNode;
               parentNode->pLeft = newNode;
            }
         else
            {
               newNode->pParent = parentNode;
               parentNode->pRight = newNode;
            }
      }
      else
      {
         root = newNode;
      }*/

        return destinationNode; // temporary, not final
    }

    /*******************************************
     * BST :: rBegin
     *******************************************/
//    typename BST<T>:: iterator BST<T>::rbegin()
//    {
//
//    }

    /*******************************************
     * BST :: Delete Binary Tree
     *******************************************/
    template <class T>
    void BST<T>::deleteBTree(BNode *&deleteBST)
    {
        // recursion
        if (deleteBST == NULL)
        {
            return;
        }
        deleteBTree(deleteBST->pRight);
        deleteBTree(deleteBST->pLeft);
        delete deleteBST;
        deleteBST = NULL;
    }

    /*******************************************
     * BST :: Copy Binary Tree
     *******************************************/
    template <class T>
    typename BST<T>::BNode * BST<T>::copyBTree(BNode *pSrc)
    {

        // check if source is NULL
        if (pSrc == NULL)
        {
            return NULL;
        }

        // create destination node
        BNode *pDes = new BNode(pSrc->data);
        numElements++;
        if(root == NULL)
         {
          root = pDes;
         }

        pDes->pLeft = copyBTree(pSrc->pLeft);
        if (pDes->pLeft != NULL)
        {
            pDes->pLeft->pParent = pDes;
        }

        pDes->pRight = copyBTree(pSrc->pRight);
        if (pDes->pRight != NULL)
        {
            pDes->pRight->pParent = pDes;
        }

        return pDes;
    }

    /*******************************************
     * Iterator :: Increment
     *******************************************/

    /*******************************************
     * Iterator :: Decrement
     *******************************************/

}
#endif /* bnode_h */
