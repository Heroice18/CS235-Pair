/***********************************************************************
 * Header:
 *    bst.h
 *
 * Author
 *    Brandon Ison, Brett Mills
 ************************************************************************/

#ifndef bst_h
#define bst_h
#include <iostream>
using namespace std;

#include <cassert>

/************************************************
 * Node
 * Basic class Node
 ***********************************************/
template <class T>
class BST
{
public:
   // Member variables
   BNode <T> *pRoot;
   int numElements;



   //friend int sizeBtree(BinaryNode <T> * pAdd);

   int size();

   //Default Constructor
   BST() : pRoot(NULL), numElements(0)
   {

   }

   //Non Default Constructor
   BST(T t) : data(t), pLeft(NULL), pRight(NULL), pParent(NULL)
   {

   }

   //Copy Constructor
   BST(const BNode<T> &rhs);
};

//outstream insertion operator
template <class T>
ostream & operator << (ostream & out, BNode<T> * pNode)
{
   if (NULL != pNode)
   {
      cout << pNode->pLeft;
      out << pNode->data << " ";
      cout << pNode->pRight;
   }
   return out;
}

//Copy Constructor
template<class T>
BNode<T>::BNode(const BNode<T>& rhs)
{

   *this = rhs;
}

/*
Add Left
*/
template <class T>
void addLeft(BNode <T> *pNode, BNode <T> *pAdd)
{
    if (pAdd != NULL)
    {
        pAdd->pParent = pNode;
    }
    pNode->pLeft = pAdd;
}

// Add a node to a node
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

template <class T>
BNode <T> * copyBTree(const BNode <T> * pSrc) throw (const char *)
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


template <class T>
int BNode <T>::size()
{

   if(NULL == this )
      return 0;
   else
      return (this->pLeft->size() + 1 + this->pRight->size());
}

/*******************************************
 * Binary Tree :: Delete Binary Tree
 *******************************************/
template <class T>
void deleteBTree(BNode <T> *&pNode)
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
    pNode = NULL;
//    pNode->pParent = NULL;
//    pNode->pLeft = NULL;
//    pNode->pRight = NULL;


}



 template <class T>
 int sizeBTree(const BNode <T> * pNode)
 {

    if(pNode == NULL)
    {
      return 0;
    }
    else
    {
      return (sizeBTree(pNode->pLeft) + 1 + sizeBTree(pNode->pRight));
    }
 }

#endif /* bnode_h */
