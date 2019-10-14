/****************************************************************************************
 * FILE: Choi_bst_node.h
 * NAME: Choi_bst_node.h
 *
 * DESCRIPTION
 * This header file defines the templated binary-search-tree (BST) data structure.
 * The header file is built with functions of constructor Choi_BST(), destructor ~Choi_BST(),
 * insertNode( const NODETYPE & ), remove( const NODETYPE & ), elementExists( const NODETYPE & )
 * Find (const NODETYPE &), toArray (int), empty(), length(), and additional functions that are
 * needed for the BST structure. Since the BST class is templated, the file can be globally
 * reusable.
 *
 * Created by Jaehyuk Choi on 4/07/19. (jchoi154@asu.edu)
 *
 * COURSE INFO
 * CSE240 Spring 2019
 * Homework5 04-07-2019 / Time: 2:00pm - 2:50pm MWF
 *
 * Copyright © 2019 Jaehyuk Choi. All rights reserved.
 *
 * **************************************************************************************/

#ifndef CHOI_BST_H_
#define CHOI_BST_H_

#include <iostream>
#include "Choi_bst_node.h"

//using namespace std;

/**
 * Binary Search Tree class-template definition for Choi_BST.
 */
template < typename NODETYPE >
class Choi_BST
{
public:
	Choi_BST(); // constructor
	~Choi_BST(); // destructor
	void insertNode( const NODETYPE & );
	Choi_BSTnode < NODETYPE > * findSmallest();
	void remove( const NODETYPE & );
	void removeRootMatch();
	bool elementExists( const NODETYPE & );
	Choi_BSTnode < NODETYPE > * Find (const NODETYPE &);
	NODETYPE * toArray (int);
	void empty();
	int length();
	void preOrderTraversal() const;
	void inOrderTraversal() const;
	void postOrderTraversal() const;
private:
	Choi_BSTnode < NODETYPE > *rootPtr;
	// utility functions
	void destroyHelper( Choi_BSTnode < NODETYPE > * );
	void insertNodeHelper( Choi_BSTnode < NODETYPE > **, const NODETYPE & );
	Choi_BSTnode < NODETYPE > * findSmallestHelper( Choi_BSTnode < NODETYPE > * );
	void removeHelper( Choi_BSTnode < NODETYPE > *, const NODETYPE & );
	void removeMatch( Choi_BSTnode < NODETYPE > *, Choi_BSTnode < NODETYPE > *, bool);
	void elementExistsHelper( Choi_BSTnode < NODETYPE > *, const NODETYPE & );
	Choi_BSTnode < NODETYPE > * FindHelper ( Choi_BSTnode < NODETYPE > *, const NODETYPE & );
	void toArrayHelper (Choi_BSTnode < NODETYPE > *, NODETYPE *, int*);
	int lengthHelper(Choi_BSTnode < NODETYPE > *);
	void preOrderHelper( Choi_BSTnode < NODETYPE > * ) const;
	void inOrderHelper( Choi_BSTnode < NODETYPE > * ) const;
	void postOrderHelper( Choi_BSTnode < NODETYPE > * ) const;
};
/**
 * constructor
 */
template < typename NODETYPE >
Choi_BST < NODETYPE > :: Choi_BST()
{
	rootPtr = NULL; // same as rootPtr = 0;
}
/**
 * destructor
 */
template < typename NODETYPE >
Choi_BST < NODETYPE > :: ~Choi_BST()
{
	destroyHelper(rootPtr);
}
/**
 * The destroyHelper() helps the destructor ~Choi_BST() to delete all the nodes in the tree.
 */
template < typename NODETYPE >
void Choi_BST < NODETYPE > :: destroyHelper( Choi_BSTnode < NODETYPE > *ptr )
{
	if (ptr != NULL)
	{
		destroyHelper(ptr->leftPtr);
		destroyHelper(ptr->rightPtr);
		delete ptr;
	}
}
/**
 * The insertNode() inserts the data from the user's desires in the tree.
 */
template < typename NODETYPE >
void Choi_BST < NODETYPE > :: insertNode( const NODETYPE &pValue )
{
	insertNodeHelper( &rootPtr, pValue );
}
template < typename NODETYPE >
void Choi_BST < NODETYPE > :: insertNodeHelper( Choi_BSTnode < NODETYPE > **ptr, const NODETYPE &pValue )
{
	if (*ptr == NULL) // case1: no node in the tree.
	{
		*ptr = new Choi_BSTnode < NODETYPE > (pValue);
	}
	else
	{
		if (pValue < (*ptr)->data) // case2: the data inserted is less than the data of a parent node.
		{
			insertNodeHelper(&((*ptr)->leftPtr), pValue);
		}
		else if ( pValue > (*ptr)->data ) // case3: the data inserted is greater than the data of a parent node.
		{
			insertNodeHelper(&((*ptr)->rightPtr),pValue);
		}
		else if ( pValue == (*ptr)->data ) // case2: the data inserted is equal to the data of a parent node.
		{
			//std::cout << pValue << " duplicate" << std::endl;
		}
	}
}
/**
 * The findSmallest() finds the smallest data in the a subtree and returns the pointer to the node.
 */
template < typename NODETYPE >
Choi_BSTnode < NODETYPE > * Choi_BST < NODETYPE > :: findSmallest()
{
	return findSmallestHelper(rootPtr);
}
template < typename NODETYPE >
Choi_BSTnode < NODETYPE > * Choi_BST < NODETYPE > :: findSmallestHelper( Choi_BSTnode < NODETYPE > * ptr)
{
	if (rootPtr == NULL) // case1: no node in the tree.
	{
		std::cout << "The tree is empty" << std::endl;
		return ptr;
	}
	else
	{
		if(ptr->leftPtr != NULL) // case2: the node is not the most left leaf: go left as further as it can.
		{
			return findSmallestHelper(ptr->leftPtr);
		}
		else // case2: the node is already at the most left leaf: the current node is the node contains minimum.
		{
			return ptr;
		}
	}
}
/**
 * The remove() removes a specific node that contains the data that a user want to remove.
 */
template < typename NODETYPE >
void Choi_BST < NODETYPE > :: remove( const NODETYPE & pValue)
{
	removeHelper(rootPtr, pValue);
}
template < typename NODETYPE >
void Choi_BST < NODETYPE > :: removeHelper( Choi_BSTnode < NODETYPE > * parent, const NODETYPE & pValue)
{
	if (rootPtr != NULL) // case 1: the tree is not empty
	{
		if (rootPtr->data == pValue) // case 1-1) the data to be removed is at the root.
		{
			removeRootMatch();
		}
		else
		{
			if( (pValue < parent->data) && (parent->leftPtr != NULL) ) // case 1-2) the data to be removed is in the left subtree.
			{
				pValue == parent->leftPtr->data ? removeMatch(parent, parent->leftPtr, true) : removeHelper(parent->leftPtr, pValue);
			}
			else if( (pValue > parent->data) && (parent->rightPtr != NULL) ) // case 1-3) the data to be removed is in the right subtree.
			{
				pValue == parent->rightPtr->data ? removeMatch(parent, parent->rightPtr, false) : removeHelper(parent->rightPtr, pValue);
			}
			else // case 1-4) the data to be removed is not in the tree.
			{
				std::cout << "The data " << pValue << " is not found in the tree" << std::endl;
			}
		}
	}
	else // case 2: the tree is empty.
	{
		std::cout << "The tree is empty." << std::endl;
	}
}
/**
 * The removeRootMatch() rebuilds the tree in the case that root is removed.
 */
template < typename NODETYPE >
void Choi_BST < NODETYPE > :: removeRootMatch()
{
	if (rootPtr != NULL) // case 1: the tree is not empty
	{
		Choi_BSTnode < NODETYPE > * delPtr = rootPtr;
		NODETYPE rootData = rootPtr->data;
		NODETYPE smallestInRightSubtree;
		// case 1-1) no child node
		if ( rootPtr->leftPtr == NULL && rootPtr->rightPtr == NULL)
		{
			rootPtr = NULL;
			delete delPtr;
		}
		// case 1-2) 1 right child node
		else if ( rootPtr->leftPtr == NULL && rootPtr->rightPtr != NULL)
		{
			rootPtr = rootPtr->rightPtr;
			delPtr->rightPtr = NULL;
			delete delPtr;
			std::cout << "The root node with data " << rootData << " is deleted. "
					<< "The new root contains data " << rootPtr->data << std::endl;
		}
		// case 1-3) 1 left child node
		else if ( rootPtr->leftPtr != NULL && rootPtr->rightPtr == NULL)
		{
			rootPtr = rootPtr->leftPtr;
			delPtr->leftPtr = NULL;
			delete delPtr;
			std::cout << "The root node with data " << rootData << " is deleted. "
					<< "The new root contains data " << rootPtr->data << std::endl;
		}
		// case 1-4) 2 children nodes
		else
		{
			smallestInRightSubtree = findSmallestHelper(rootPtr->rightPtr)->getData();
			removeHelper(rootPtr, smallestInRightSubtree);
			rootPtr->data = smallestInRightSubtree;
			std::cout << "The root data containing data " << rootData << " is overwritten with data "
					<< rootPtr->data << std::endl;
		}
	}
	else // case 2: the tree is empty
	{
		std::cout << "The tree is empty: cannot remove root" << std::endl;
	}
}
/**
 * The removeMatch() rebuilds the tree in the case that a node which is not root is removed.
 */
template < typename NODETYPE >
void Choi_BST < NODETYPE > :: removeMatch( Choi_BSTnode < NODETYPE > * parent, Choi_BSTnode < NODETYPE > * match, bool leftPtr)
{
	if (rootPtr != NULL) // case 1: the tree is not empty
	{
		Choi_BSTnode < NODETYPE > * delPtr;
		NODETYPE matchData = match->data;
		NODETYPE smallestInRightSubtree;
		// case 1-1) no child node
		if ( match->leftPtr == NULL && match->rightPtr == NULL )
		{
			delPtr = match;
			leftPtr == true ? parent->leftPtr = NULL : parent->rightPtr = NULL;
			delete delPtr;
			std::cout << "The node containing the data " << matchData << " is removed." << std::endl;
		}
		// case 1-2) 1 right child node
		else if ( match->leftPtr == NULL && match->rightPtr != NULL )
		{
			leftPtr == true ? parent->leftPtr = match->rightPtr : parent->rightPtr = match->rightPtr;
			match->rightPtr = NULL;
			delPtr = match;
			delete delPtr;
			std::cout << "The node containing the data " << matchData << " is removed." << std::endl;
		}
		// case 1-3) 1 left child node
		else if ( match->leftPtr != NULL && match->rightPtr == NULL )
		{
			leftPtr == true ? parent->leftPtr = match->leftPtr : parent->rightPtr = match->leftPtr;
			match->leftPtr = NULL;
			delPtr = match;
			delete delPtr;
			std::cout << "The node containing the data " << matchData << " is removed." << std::endl;
		}
		// case 1-4) 2 children nodes
		else
		{
			smallestInRightSubtree = findSmallestHelper(match->rightPtr)->getData();
			removeHelper(match, smallestInRightSubtree);
			match->data = smallestInRightSubtree;
		}
	}
	else // case 2: the tree is empty
	{
		std::cout << "The tree is empty: cannot remove root" << std::endl;
	}
}
/**
 * The elementExists() returns boolean true or false whether the tree contains the data for which a user
 * looks. It use the Find() that created later.
 */
template < typename NODETYPE >
bool Choi_BST < NODETYPE > :: elementExists( const NODETYPE & pValue )
{
	bool result;
	if (Find(pValue) != NULL)
	{
		std::cout << "The item exists in the tree." << std::endl;
		result = true;
	}
	else
	{
		std::cout << "The item does not exist in the tree." << std::endl;
		result = false;
	}
	return result;
}
/**
 * The Find() returns a pointer that points to the data for which a user looks.
 */
template < typename NODETYPE >
Choi_BSTnode < NODETYPE > * Choi_BST < NODETYPE > :: Find ( const NODETYPE & pValue )
{
	return FindHelper(rootPtr, pValue);
}
template < typename NODETYPE >
Choi_BSTnode < NODETYPE > * Choi_BST < NODETYPE > :: FindHelper ( Choi_BSTnode < NODETYPE > * ptr, const NODETYPE & pValue )
{
	if(ptr != NULL) // case 1: the tree is not empty
	{
		// case 1-1) the data is at the node
		if(ptr->data == pValue)
		{
			return ptr;
		}
		else
		{
			if (pValue < ptr->data) // case 1-2) the data is in the left subtree.
			{
				return FindHelper(ptr->leftPtr, pValue);
			}
			else // case 1-2) the data is in the right subtree.
			{
				return FindHelper(ptr->rightPtr, pValue);
			}
		}
	}
	else // case 2: the tree is empty
	{
		return NULL;
	}
}
/**
 * The toArray() returns an array of the data in the tree. NOTE: to use the function toArray(), the size
 * of the array should be known. Thus, before using the toArray(), to verify the length of the tree is
 * required by using the length() function.
 */
template < typename NODETYPE >
NODETYPE * Choi_BST < NODETYPE > :: toArray (int pSize)
{
	NODETYPE* pArray = new NODETYPE[pSize];
	int count = 0;
	toArrayHelper(rootPtr, pArray, &count);
	return pArray;
}
template < typename NODETYPE >
void Choi_BST < NODETYPE > :: toArrayHelper (Choi_BSTnode < NODETYPE > * ptr, NODETYPE *pArray, int* count)
{
	if (ptr != NULL)
	{
		toArrayHelper(ptr->leftPtr, pArray, count ); // stores in order.
		pArray[*count] = ptr->data;
		*count += 1;
		toArrayHelper( ptr->rightPtr, pArray, count );
	}
}
/**
 * The empty() deletes all the nodes in the tree by using the function destroyHelper().
 */
template < typename NODETYPE >
void Choi_BST < NODETYPE > :: empty()
{
	destroyHelper(rootPtr);
}
/**
 * The length() returns integer value of total nodes in the tree.
 */
template < typename NODETYPE >
int Choi_BST < NODETYPE > :: length()
{
	return lengthHelper( rootPtr );
}
template < typename NODETYPE >
int Choi_BST < NODETYPE > :: lengthHelper(Choi_BSTnode < NODETYPE > *ptr)
{
	if (ptr==NULL)
		return 0;
	else
		return (lengthHelper(ptr->leftPtr)+1+lengthHelper(ptr->rightPtr));
}
/**
 * The preOrderTraversal() prints the data in the tree in preorder.
 */
template < typename NODETYPE >
void Choi_BST < NODETYPE > :: preOrderTraversal() const
{
	preOrderHelper ( rootPtr );
}
template < typename NODETYPE >
void Choi_BST < NODETYPE > :: preOrderHelper ( Choi_BSTnode < NODETYPE > *ptr ) const
{
	if (ptr != NULL)
	{
		std::cout << ptr->data << " ";
		preOrderHelper( ptr->leftPtr );
		preOrderHelper( ptr->rightPtr );
	}
}
/**
 * The inOrderTraversal() prints the data in the tree in order.
 */
template < typename NODETYPE >
void Choi_BST < NODETYPE > :: inOrderTraversal () const
{
	inOrderHelper ( rootPtr );
}
template < typename NODETYPE >
void Choi_BST < NODETYPE > :: inOrderHelper( Choi_BSTnode < NODETYPE > *ptr ) const
{
	if (ptr != NULL)
	{
		inOrderHelper( ptr->leftPtr );
		std::cout << ptr->data << " ";
		inOrderHelper( ptr->rightPtr );
	}
}
/**
 * The postOrderTraversal() prints the data in the tree in postorder.
 */
template < typename NODETYPE >
void Choi_BST < NODETYPE > :: postOrderTraversal () const
{
	postOrderHelper ( rootPtr );
}
template < typename NODETYPE >
void Choi_BST < NODETYPE > :: postOrderHelper ( Choi_BSTnode < NODETYPE > *ptr ) const
{
	if (ptr != NULL)
	{
		postOrderHelper( ptr->leftPtr );
		postOrderHelper( ptr->rightPtr );
		std::cout << ptr->data << " ";
	}
}

#endif /* CHOI_BST_H_ */
