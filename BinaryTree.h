// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by:
 
#ifndef _BINARY_TREE
#define _BINARY_TREE


#include "BinaryNode.h"
#include "queue.h"
#include "stack.h"

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree() {rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<ItemType> & tree){ }
	virtual ~BinaryTree() { }
	BinaryTree & operator = (const BinaryTree & sourceTree);
   
	// common functions for all binary trees

	//checks if tree is empty
 	bool isEmpty() const	{return count == 0;}
	//returns size of tree
	int size() const	    {return count;}
	//deletes all nodes in tree
	void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
	//preorder traversal
	void preOrder(void visit(ItemType &)) const {_preorder(visit, rootPtr);}
	//inorder traversal
	void inOrder(void visit(ItemType &)) const  {_inorder(visit, rootPtr);}
	//postorder traversal
	void postOrder(void visit(ItemType &)) const{_postorder(visit, rootPtr);}
	//level order/breadth first traversal
	void levelOrder(void visit(ItemType &)) const{ _levelorder(visit, rootPtr); }


	// abstract functions to be implemented by derived class

	//inserts node into bst
	virtual bool insert(const ItemType & newData) = 0; 
	//removes node from bst
	virtual bool remove(const ItemType & data) = 0; 
	//finds and returns entry from bst
	virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;

	//iterative preorder traversal
	void preOrderiter(void visit(ItemType &)) const { _preorderiter(visit, rootPtr); }
	//iterative inorder traversal
	void inOrderiter(void visit(ItemType &)) const  { _inorderiter(visit, rootPtr); }
	//iterative postorder traversal
	void postOrderiter(void visit(ItemType &)) const{ _postorderiter(visit, rootPtr); }

private:   
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse

	//preorder traversal
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	//inorder traversal
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	//postorder traversal
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	//level order/breadth first traversal
	void _levelorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	//iterative preorder traversal
	void _preorderiter(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	//iterative inorder traversal
	void _inorderiter(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	//iterative postorder traversal
	void _postorderiter(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
   
}; 

//////////////////////////////////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr) 
{
	BinaryNode<ItemType>* newNodePtr = 0;
	if (nodePtr != 0)
	{
		newNodePtr = new BinaryNode<ItemType>(nodePtr->getItem());
		if (nodePtr->getLeftPtr() != 0)
		{
			newNodePtr->setLeftPtr(copyTree(nodePtr->getLeftPtr()));
		}
		if (nodePtr->getRightPtr() != 0)
		{
			newNodePtr->setRightPtr(copyTree(nodePtr->getRightPtr()));
		}
	}
    
   
    return newNodePtr;
}  

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr != 0)
	{
		if (nodePtr->getLeftPtr() != 0)
		{
			destroyTree(nodePtr->getLeftPtr());
		}
		if (nodePtr->getRightPtr() != 0)
		{
			destroyTree(nodePtr->getRightPtr());
		}
		
		ItemType item;
		item = nodePtr->getItem();
		delete nodePtr;
	}
}  

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	} 
}  

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		_inorder(visit, nodePtr->getLeftPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}  

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
	}
}  

template<class ItemType>
void BinaryTree<ItemType>:: _levelorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	Queue < BinaryNode<ItemType>* > q;
	q.enqueue(nodePtr);

	while (!q.isEmpty())
	{
		BinaryNode<ItemType> * tempnode;
		bool success = q.dequeue(tempnode);
		
		if (success)
		{
			if (tempnode->getLeftPtr() != 0)
			{
				q.enqueue(tempnode->getLeftPtr());
			}
			if (tempnode->getRightPtr() != 0)
			{
				q.enqueue(tempnode->getRightPtr());
			}
			
			ItemType item = tempnode->getItem();
			visit(item);
		}
	}

}

template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{
	if (this != &sourceTree)
	{
		destroyTree(rootPtr);
		rootPtr = copyTree(sourceTree.rootPtr);
	}

	return *this;
}  

template <class ItemType>
void BinaryTree<ItemType>::_preorderiter(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	Stack<BinaryNode<ItemType>*> s;
	s.push(rootPtr);
	while (!s.isEmpty())
	{
		bool success = s.pop(nodePtr);
		//s.pop();


		if (nodePtr->getRightPtr() != 0)
			s.push(nodePtr->getRightPtr());
		if (nodePtr->getLeftPtr() != 0)
			s.push(nodePtr->getLeftPtr());

		ItemType item = nodePtr->getItem();
		visit(item);
	}

}

template <class ItemType>

void BinaryTree<ItemType>::_inorderiter(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{

	BinaryNode<ItemType> *ptr;
	ptr = nodePtr;
	Stack<BinaryNode<ItemType>*> s;
	while (ptr != 0 || !s.isEmpty())
	{
		if (ptr != 0)
		{
			s.push(ptr);
			ptr = ptr->getLeftPtr();

		}// reached end of the left subtree
		else if (!s.isEmpty())
		{
			//ptr = s.top();
			s.pop(ptr);
			ItemType item = ptr->getItem();
			visit(item);
			ptr = ptr->getRightPtr();
			//s.pop(ptr);
		}

	}


}

template <class ItemType>
void BinaryTree<ItemType>::_postorderiter(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr == 0)
		return;
	BinaryNode<ItemType> *prev = 0;
	Stack<BinaryNode<ItemType>*> s;

	while (!s.isEmpty() || nodePtr != 0)
	{
		if (nodePtr != 0)
		{
			s.push(nodePtr);
			nodePtr = nodePtr->getLeftPtr();
		}
		else
		{
			BinaryNode<ItemType> *node;
			s.getTop(node);
			if (node->getRightPtr() != 0 && prev != node->getRightPtr())
			{
				nodePtr = node->getRightPtr();
			}
			else
			{
				ItemType item = node->getItem();
				visit(item);
				prev = node;
				s.pop(node);
			}
		}

	}


}

#endif
