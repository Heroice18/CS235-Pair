//
//  bnode.h
//  Assignment 8
//
//  Created by Brett Mills on 2/26/19.
//  Copyright © 2019 Brett Mills. All rights reserved.
//

#ifndef bnode_h
#define bnode_h

#include <cstddef>
#include <iostream>

using namespace std;

template <class T>
class BNode
{
public:
    T data;
    BNode <T> *pLeft;
    BNode <T> *pRight;
    BNode <T> *pParent;
        
    BNode()
    {
        data    = NULL;
        pLeft   = NULL;
        pRight  = NULL;
        pParent = NULL;
    }
    BNode(T t)
    {
        data = t;
        pLeft   = NULL;
        pRight  = NULL;
        pParent = NULL;
    }
    BNode(const BNode <T> &rhs);
        
//    int size();
//    void addLeft(const T & t);
//    void addLeft(BNode <T> *left);
//    void addRight(const T &t);
//    void addRight(BNode <T> *right);
//
};

/*******************************************
 * Binary Tree :: Copy Constructor
 *******************************************/
template <class T>
BNode<T>::BNode(const BNode <T> &rhs)
{
    *this = rhs;
}

/*******************************************
 * Binary Tree :: Insertion Operator
 *******************************************/
template <class T>
ostream & operator <<(ostream & out, BNode <T> *pNode)
{
    if (pNode != NULL)
    {
        cout << pNode->pLeft;
        out  << pNode->data << " ";
        cout << pNode->pRight;
    }
    return out;
}

/*******************************************
 * Binary Tree :: Add Left
 *******************************************/
template <class T>
void addLeft(BNode <T> *pNode, BNode <T> *pAdd)
{
    if (pAdd != NULL)
    {
        pAdd->pParent = pNode;
    }
    pNode->pLeft = pAdd;
}

template <class T>
void addLeft(BNode <T> *pNode, const T & t)
{
    BNode <T> *pAdd = new BNode<T>(t);
    pAdd->pParent = pNode;
    pNode->pLeft = pAdd;
}

/*******************************************
 * Binary Tree :: Add Right
 *******************************************/
template <class T>
void addRight(BNode <T> *pNode, BNode <T> *pAdd)
{
    if (pAdd != NULL)
    {
        pAdd->pParent = pNode;
    }
    pNode->pRight = pAdd;
}

template <class T>
void addRight(BNode <T> *pNode, const T & t)
{
    BNode <T> *pAdd = new BNode<T>(t);
    pAdd->pParent = pNode;
    pNode->pRight = pAdd;
}

/*******************************************
 * Binary Tree :: Copy Binary Tree
 *******************************************/
template <class T>
BNode <T> * copyBTree(const BNode <T> *pSrc) throw (const char *)
{
    // check if source is NULL
    if (pSrc == NULL)
    {
        return NULL;
    }

    // create destination node
    BNode <T> *pDes = new BNode <T>(pSrc->data);
    
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
 * Binary Tree :: Delete Binary Tree
 *******************************************/
template <class T>
void deleteBTree(BNode <T> *pNode)
{
    // probably some issues here
    // need to free up memory?
    if (pNode == NULL)
    {
        return;
    }
    deleteBTree(pNode->pLeft);
    deleteBTree(pNode->pRight);
    delete pNode;
//    pNode->pParent = NULL;
//    pNode->pLeft = NULL;
//    pNode->pRight = NULL;


}

/*******************************************
 * Binary Tree :: Size of Binary Tree
 *******************************************/
template <class T>
int sizeBTree(BNode <T> *pNode)
{
    if (pNode == NULL)
    {
        return 0;
    }
    else
    {
        return sizeBTree(pNode->pLeft) + 1 + sizeBTree(pNode->pRight);
    }
}



#endif /* bnode_h */
