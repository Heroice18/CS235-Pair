//
//  bst.h
//  Assignment 9
//
//  Created by Brett Mills on 3/4/19.
//  Copyright © 2019 Brett Mills. All rights reserved.
//

#ifndef bst_h
#define bst_h

#include <cstddef>
#include <iostream>
#include <stack>

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
        BST <T> & operator=(const BST & rhs);
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
        iterator end() ;
//        iterator rend() { return iterator(NULL); }
        
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
            iterator & operator--(int postfix)
            {
                if (ptr != NULL)
                {
                    if (ptr->pLeft)
                    {
                        ptr = ptr->pLeft;
                        while (ptr->pRight)
                        {
                            ptr = ptr->pLeft;
                        }
                        }
                        else if ((ptr->pLeft == NULL) && (ptr->pParent->pRight == ptr))
                        {
                            ptr = ptr->pParent;
                        }
                        else if ((ptr->pLeft == NULL) && (ptr->pParent->pLeft == ptr))
                        {
                            while ((ptr->pParent) && (ptr->pParent->pLeft == ptr))
                            {
                                ptr = ptr->pParent;
                            }
                            ptr = ptr->pParent;
                        }
                        }
                        else
                            throw "Error: incrementing null node.";
                        
                        return *this;
            }
            iterator & operator++()
            {
                if (ptr != NULL)
                {
                    ptr->pRight = NULL;
                    if (ptr->pRight)
                    {
                        ptr = ptr->pRight;
                        while (ptr->pLeft)
                        {
                            ptr = ptr->pLeft;
                        }
                    }
                    else if ((ptr->pRight == NULL) && (ptr->pParent->pLeft == ptr))
                    {
                        ptr = ptr->pParent;
                    }
                    else if ((ptr->pRight == NULL) && (ptr->pParent->pRight == ptr))
                    {
                        while ((ptr->pParent) && (ptr->pParent->pRight == ptr))
                        {
                            ptr = ptr->pParent;
                        }
                        ptr = ptr->pParent;
                    }
                }
                else
                    throw "Error: incrementing null node.";
                
                return *this;
            }
            iterator & operator++(int postfix)
            {
                if (ptr != NULL)
                {
                    if (ptr->pRight)
                    {

                        ptr = ptr->pRight;
                        while (ptr->pLeft)
                        {
                            ptr = ptr->pLeft;
                        }
                    }
                    else if ((ptr->pRight == NULL) && (ptr->pParent->pLeft == ptr))
                    {
                        ptr = ptr->pParent;
                    }
                    else if ((ptr->pRight == NULL) && (ptr->pParent->pRight == ptr))
                    {
                        while ((ptr->pParent) && (ptr->pParent->pRight == ptr))
                        {
                            ptr = ptr->pParent;
                        }
                        ptr = ptr->pParent;
                    }
                }
                else
                    throw "Error: incrementing null node.";
                
                return *this;
            }
            // END of iterator class
        };
        
        // END of BST class
    };
    
    /*******************************************
     * BST :: Copy Constructor
     *******************************************/
    template <class T>
    BST<T>::BST(const BST & rhs)
    {
        if (rhs.root == NULL)
        {
            root = NULL;
            numElements = 0;
//            *this = rhs;
        }
        else
        {
            numElements = 0;
            copyBTree(rhs.root);
        }
    }
    
    /*******************************************
     * BST :: Assignment Operator
     *******************************************/
    template <class T>
    BST<T> & BST<T>::operator=(const BST<T> &rhs)
    {
        if (rhs.root != NULL)
        {
            try
            {
                root = new BNode(rhs.root->data);
                root->pLeft = copyBTree(rhs.root->pLeft);
                if (root->pLeft != NULL)
                {
                    root->pLeft->pParent = root;
                }
                root->pRight = copyBTree(rhs.root->pRight);
                if (root->pRight != NULL)
                {
                    root->pRight->pParent = root;
                }
            }
            catch (bad_alloc)
            {
                throw "errrrrror";
            }
            numElements++;
        }
        else
            root = rhs.root;
        
        return *this;
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
        
        while (destinationNode != NULL)
        {
            if (t < destinationNode->data)
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
        
        if (parentNode != NULL)
        {
            if (t < parentNode->data)
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
//    template <class T>
//    void BST<T>::erase(iterator it)
//    {
//        // CASE 1: no children
//        if (it.ptr->pRight == NULL && it.ptr->pLeft == NULL)
//        {
//            if (it.ptr->pParent != NULL && it.ptr->pParent->pRight == it.ptr)
//            {
//                it.ptr->pParent->pRight = NULL;
//            }
//            if (it.ptr->pParent != NULL && it.ptr->pParent->pLeft == it.ptr)
//            {
//                it.ptr->pParent->pLeft = NULL;
//            }
//            delete it.ptr;
//        }
//        
//        // CASE 2: no child
//        // no left child
//        if (it.ptr->pRight == NULL && it.ptr->pLeft != NULL)
//        {
//            it.ptr->pLeft->pParent = it.ptr->pParent;
//            if (it.ptr->pParent != NULL && it.ptr->pParent->pRight == it.ptr)
//            {
//                it.ptr->pParent->pRight = it.ptr->pLeft;
//            }
//            if (it.ptr->pParent != NULL && it.ptr->pParent->pLeft == it.ptr)
//            {
//                it.ptr->pParent->pLeft = it.ptr->pLeft;
//            }
//            delete it.ptr;
//        }
//        // no right child
//        if (it.ptr->pLeft == NULL && it.ptr->pRight != NULL)
//        {
//            it.ptr->pRight->pParent = it.ptr->pParent;
//            if (it.ptr->pParent != NULL && it.ptr->pParent->pRight == it.ptr)
//            {
//                it.ptr->pParent->pRight = it.ptr->pRight;
//            }
//            if (it.ptr->pParent != NULL && it.ptr->pParent->pLeft == it.ptr)
//            {
//                it.ptr->pParent->pLeft = it.ptr->pRight;
//            }
//            delete it.ptr;
//        }
//        
//        // CASE 3: two children
//        if (it.ptr->pRight != NULL && it.ptr->pLeft != NULL)
//        {
//            // This code is probably not good in the long run, but it works for now
//            // It kinda works, but some of it is hard coded
//            BNode *temp = it.ptr->pRight;
//            while (temp->pLeft != NULL)
//            {
//                temp = temp->pLeft;
//            }
//            iterator *tempIt = new iterator(temp);
//            it.ptr->data = temp->data;
//            temp->pRight = it.ptr->pRight;
//            temp->pRight->pLeft = NULL;
//            temp->pLeft = it.ptr->pLeft;
//            erase(*tempIt);
//            root = temp;
//            numElements++;
            
//            iterator deleteIt(it++);
//
//            if (it.ptr->pRight)
//            {
//                cout << "im inside first if statement" << endl;
//
//                it.ptr->pRight->pParent = it.ptr->pParent;
//                it.ptr->pParent->pLeft = it.ptr->pRight;
//            }
//            else
//            {
//                it.ptr->pParent->pLeft = NULL;
//            }
//
//            if (deleteIt.ptr->pParent != NULL)
//            {
//                if (deleteIt.ptr->pParent->pLeft == deleteIt.ptr)
//                {
//                    cout << "im here 2" << endl;
//
//                    deleteIt.ptr->pParent->pLeft = it.ptr;
//                    it.ptr->pParent = deleteIt.ptr->pParent;
//                }
//                else if (deleteIt.ptr->pParent->pRight == deleteIt.ptr)
//                {
//                    cout << "im here 3" << endl;
//
//                    cout << it.ptr->data << " inside erase function (before)" << endl;
//
//
//                    deleteIt.ptr->pParent->pRight = it.ptr;
//                    it.ptr->pParent = deleteIt.ptr->pParent;
//                    it.ptr->pParent = NULL;
//                    root = it.ptr;
//                    cout << root->data << " inside erase function (after)" << endl;
//                }
//                else
//                {
//                    it.ptr->pParent = NULL;
//                    root = it.ptr;
//                }
//            }
//
//            deleteIt.ptr->pLeft->pParent = it.ptr;
//            it.ptr->pLeft = deleteIt.ptr->pLeft;
//
//            deleteIt.ptr->pRight->pParent = it.ptr;
//            it.ptr->pRight = deleteIt.ptr->pRight;
//
//            delete deleteIt.ptr;
//        }
//        numElements--;
        template <class T>
        void BST <T> :: erase(iterator it)
        {
            if (it.ptr->pRight == NULL && it.ptr->pLeft == NULL)
            {
                if (it.ptr->pParent != NULL && it.ptr->pParent->pRight == it.ptr)
                    it.ptr->pParent->pRight = NULL;
                if (it.ptr->pParent != NULL && it.ptr->pParent->pLeft == it.ptr)
                    it.ptr->pParent->pLeft = NULL;
                delete it.ptr;
            }
            else if (it.ptr->pRight == NULL && it.ptr->pLeft != NULL)
            {
                it.ptr->pLeft->pParent = it.ptr->pParent;
                if (it.ptr->pParent != NULL && it.ptr->pParent->pRight == it.ptr)
                    it.ptr->pParent->pRight = it.ptr->pLeft;
                if (it.ptr->pParent != NULL && it.ptr->pParent->pLeft == it.ptr)
                    it.ptr->pParent->pLeft = it.ptr->pLeft;
                delete it.ptr;
            }
            else if (it.ptr->pRight != NULL && it.ptr->pLeft == NULL)
            {
                it.ptr->pRight->pParent = it.ptr->pParent;
                if (it.ptr->pParent != NULL && it.ptr->pParent->pRight == it.ptr)
                    it.ptr->pParent->pRight = it.ptr->pRight;
                if (it.ptr->pParent != NULL && it.ptr->pParent->pLeft == it.ptr)
                    it.ptr->pParent->pLeft = it.ptr->pRight;
                delete it.ptr;
            }
            else if (it.ptr->pRight != NULL && it.ptr->pLeft != NULL)
            {
                iterator deleteIt(it++);
                
                // replace's right child
                if (it.ptr->pRight)
                {
                    it.ptr->pRight->pParent = it.ptr->pParent;
                    it.ptr->pParent->pLeft = it.ptr->pRight;
                }
                else
                    it.ptr->pParent->pLeft = NULL;
                
                // delete's parent
                if(deleteIt.ptr->pParent != NULL)
                {
                    if(deleteIt.ptr->pParent->pLeft == deleteIt.ptr)
                    {
                        deleteIt.ptr->pParent->pLeft = it.ptr;
                        it.ptr->pParent = deleteIt.ptr->pParent;
                    }
                    else if(deleteIt.ptr->pParent->pRight == deleteIt.ptr)
                    {
                        deleteIt.ptr->pParent->pRight = it.ptr;
                        it.ptr->pParent = deleteIt.ptr->pParent;
                    }
                }
                else
                {
                    it.ptr->pParent = NULL;
                    root = it.ptr;
                }
                
                
                // delete's children
                deleteIt.ptr->pLeft->pParent = it.ptr;
                it.ptr->pLeft = deleteIt.ptr->pLeft;
                
                deleteIt.ptr->pRight->pParent = it.ptr;
                it.ptr->pRight = deleteIt.ptr->pRight;
                
                delete deleteIt.ptr;
            }
            
            numElements--;
        }
    
    /*******************************************
     * BST :: Begin
     *******************************************/
    template <class T>
    typename BST<T>:: iterator BST<T>::begin()
    {
        BNode *parentNode = root;
        BNode *destinationNode = root;
        while (destinationNode != NULL)
        {
            parentNode = destinationNode;
            destinationNode = destinationNode->pLeft;
        }
        return parentNode;
    }
    
    /*******************************************
     * BST :: End
     *******************************************/
    template <class T>
    typename BST<T>:: iterator BST<T>::end()
    {
        BNode *parentNode = root;
        BNode *destinationNode = root;
        while (destinationNode != NULL)
        {
            parentNode = destinationNode;
            destinationNode = destinationNode->pRight;
        }
        return parentNode;
    }
    
    /*******************************************
     * BST :: Find
     *******************************************/
    template <class T>
    typename BST<T>:: iterator BST<T>::find(const T &t)
    {
        BNode *newNode = new BNode(t);
        BNode *parentNode = root;
        BNode *destinationNode = root;
        
        while (destinationNode != NULL)
        {
            if (t < destinationNode->data)
            {
                parentNode = destinationNode;
                destinationNode = destinationNode->pLeft;
            }
            else if (t > destinationNode->data)
            {
                parentNode = destinationNode;
                destinationNode = destinationNode->pRight;
            }
            else
            {
                return destinationNode;
            }
        }
        return destinationNode;
    }
    
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
        if (root == NULL)
        {
            root = pDes;
        }
        
        // left
        pDes->pLeft = copyBTree(pSrc->pLeft);
        if (pDes->pLeft != NULL)
        {
            pDes->pLeft->pParent = pDes;
        }
        
        // right
        pDes->pRight = copyBTree(pSrc->pRight);
        if (pDes->pRight != NULL)
        {
            pDes->pRight->pParent = pDes;
        }
        return pDes;
    }
}


#endif /* bst_h */
