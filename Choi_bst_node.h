/****************************************************************************************
 * FILE: Choi_bst_node.h
 * NAME: Choi_bst_node.h
 *
 * DESCRIPTION
 * This header file defines a node class for the templated binary-search-tree (BST) data structure.
 * The node class uses friend class for Choi_BEST class to access private and protected members of
 * Choi_BST. The node class is defined by a constructor and an accessor as public member functions
 * and by left pointer, tree node data, and right pointer as private data members.
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

#ifndef CHOI_BST_NODE_H_
#define CHOI_BST_NODE_H_

/**
 * Prototype for the class.
 */
template < typename NODETYPE > class Choi_BST;
/**
 * tree node class-template definition.
 */
template < typename NODETYPE >
class Choi_BSTnode
{
	// The Choi_BST class can access private members of Choi_BSTnode.
	friend class Choi_BST < NODETYPE >;
public:
	// Constructor
	Choi_BSTnode ( const NODETYPE &pData ) : leftPtr( 0 ), // left pointer to left subtree
		 	 	 	 	 	 	 	 	 data ( pData ), // tree node data
										 rightPtr( 0 ) // pointer to right subtree
	{
		// empty body
	}
	// Accessor
	NODETYPE getData() const
	{
		return data;
	}

private:
	// Private members of Choi_BSTnode: left pointer, tree node data, right pointer
	Choi_BSTnode < NODETYPE > *leftPtr;
	NODETYPE data;
	Choi_BSTnode < NODETYPE > *rightPtr;
};

#endif /* CHOI_BST_NODE_H_ */
