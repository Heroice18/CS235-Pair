
#ifndef bnode_h
#define bnode_h
#include <iostream>
using namespace std;

#include <cassert>

/************************************************
 * Node
 * Basic class Node
 ***********************************************/
template <class T>
class BNode
{
public:
   // Member variables
   T data;
   BNode <T> *pLeft;
   BNode <T> *pRight;
   BNode <T> *pParent;



   //friend int sizeBtree(BinaryNode <T> * pAdd);

   int size();
   // Left data and nodes
   void addLeft (const T & t, int num) throw (const char *);
   void addLeft(BNode<T> * left, int num);
   // Add right data and nodes
   void addRight(const T & t) throw (const char *);
   void addRight(BNode<T> * right);
   //Default Constructor
   BNode() : data(), pLeft(NULL), pRight(NULL), pParent(NULL) {}
   //Non Default Constructor
   BNode(T t) : data(t), pLeft(NULL), pRight(NULL), pParent(NULL) {}
   //Copy Constructor
   BNode(const BNode<T> &rhs);
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

template<class T>
BNode<T>::BNode(const BNode<T>& rhs) : pRight(NULL), pLeft(NULL), pParent(NULL)
{

   *this = rhs;
}

// Add data to node
template <class T>
void BNode <T>::addLeft(const T & t, int num) throw (const char *)
{
   if (!t)
      return;
   BNode <T> * pAdd = new BNode <T>(t);
   pAdd->pParent = this;
   pLeft = pAdd;
}

// Add a node to a node
template <class T>
void BNode<T>::addLeft(BNode<T> * left, int num)
{
   pLeft = left;

   // NULL check, set parents
   if (NULL != left)
      pLeft->pParent = this;

}

// Add data to node
template <class T>
void BNode<T>::addRight(const T & t) throw(const char *)
{
   if (!t)
      return;
   BNode <T> * pAdd = new BNode<T>(t);
   pAdd->pParent = this;
   pRight = pAdd;
}

template <class T>
void BNode<T>::addRight(BNode<T> * right)
{
   pRight = right;

   // NULL Check, set parents
   if (NULL != right)
      pRight->pParent = this;
}

template <class T>
BNode <T> * copyBTree(const BNode <T> * pSrc) throw (const char *)
{
   if (pSrc == NULL)
      return NULL;

   BNode <T> * nDestination =  new BNode <T>(pSrc->data);

   nDestination->pLeft =  copyBTree(pSrc->pLeft);

   if(nDestination->pLeft != NULL)
      nDestination->pLeft.pParent = nDestination;

      nDestination->pRight = copyBTree(pSrc->pRight);
      if(nDestination->pRight != NULL)
         nDestination->pRight.pParent = nDestination;

         return nDestination;
}


template <class T>
int BNode <T>::size()
{

   if(NULL == this )
      return 0;
   else
      return (this->pLeft->size() + 1 + this->pRight->size());
}

template <class T>
void deleteBinaryTree(BNode <T> *  pNode)
{
   if(pNode == NULL)
      return;

   deleteBinaryTree(pNode->pLeft);
   deleteBinaryTree(pNode->pRight);
   delete pNode;

}


template <class T>
int addLeft(const BNode <T> * node)
{


}


 template <class T>
 int sizeBTree(const BNode <T> * node)
 {

 if(node == NULL)
 return 0;
 else
 return (sizeBTree(node->pLeft) + 1 + sizeBTree(node->pRight));
 }

#endif /* bnode_h */
