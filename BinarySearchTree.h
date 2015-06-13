// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Rohan Uppuluri
 
#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{   
private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
   
	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);
   
	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
   
	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);
   
	// search for target node
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const;

	// prints indented tree
	void _print(BinaryNode<ItemType>* n, int level, void visit(ItemType &, int level)) const;
	// finds nodes within a given inclusive range
	void _findNodesInRange(BinaryNode<ItemType>* treePtr, const ItemType & min, const ItemType & max, void visit(ItemType &)) const;
   
public:  
	// insert a node at the correct location
    bool insert(const ItemType & newEntry);
	// remove a node if found
	bool remove(const ItemType & anEntry);
	// find a target node
	bool getEntry(const ItemType & target, ItemType & returnedItem) const;
	// prints indented tree
	void print(void visit(ItemType &, int level)) const
	{
		_print(this->rootPtr, 0, visit);
	}
	// finds the node with the largest key in tree
	ItemType findLargest() const;
	// finds the node with the smallest key in tree
	ItemType findSmallest() const;
	// finds the nodes within a given inclusive range
	void findNodesInRange(const ItemType & min, const ItemType & max, void visit(ItemType &)) const;
 
};


///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	this->rootPtr = _insert(this->rootPtr, newNodePtr);
	this->count++;
	return true;
}  

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
	bool isSuccessful = false;
	this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
	return isSuccessful; 
}  

template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, ItemType & returnedItem) const
{
	if (this->rootPtr == 0)
	{
		return false;
	}

	BinaryNode<ItemType> * node = findNode(this->rootPtr, anEntry);

	if (node != 0)
	{
		returnedItem = node->getItem();
		return true;
	}

	else
	{
		return false;
	}
}  



//////////////////////////// private functions ////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                        BinaryNode<ItemType>* newNodePtr)
{
	if (nodePtr == 0)
	{
		nodePtr = newNodePtr;
		return nodePtr;
	}

	if (newNodePtr->getItem() < nodePtr->getItem())
	{
		if (nodePtr->getLeftPtr() == 0)
		{
			nodePtr->setLeftPtr(newNodePtr);
		}

		else
		{
			_insert(nodePtr->getLeftPtr(), newNodePtr);
		}
	}

	if (newNodePtr->getItem() > nodePtr->getItem())
	{
		if (nodePtr->getRightPtr() == 0)
		{
			nodePtr->setRightPtr(newNodePtr);
		}

		else
		{
			_insert(nodePtr->getRightPtr(), newNodePtr);
		}
	}

	return nodePtr;
}  

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                          const ItemType target,
                                                          bool & success)

{
	if (nodePtr == 0)                   
	{
		success = false;
		return 0;
	}
	if (nodePtr->getItem() > target)		 
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (nodePtr->getItem() < target)	 
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else		
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}      
	return nodePtr;   
}  

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())				
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)  
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0) 
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;      
	}
	else                                  
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}  
}  

template<class ItemType> 
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else 
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}       
}



template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
	const ItemType & target) const
{
	if (nodePtr == 0)
	{
		return 0;
	}

	else if (nodePtr->getItem() == target)
	{
		return nodePtr;
	}

	else if (nodePtr->getItem() > target)
	{
		return findNode(nodePtr->getLeftPtr(), target);
	}

	else
	{
		return findNode(nodePtr->getRightPtr(), target);
	}

}

template <class ItemType>

void BinarySearchTree<ItemType>::_print(BinaryNode<ItemType>* n, int level, void visit(ItemType &, int level)) const 
{
	if (n == NULL) {

		return;
	}
	_print(n->getRightPtr(), level + 1, visit);
	ItemType item;
	item = n->getItem();

	visit(item, level);
	_print(n->getLeftPtr(), level + 1, visit);
}


template <class ItemType>
ItemType BinarySearchTree<ItemType>::findSmallest() const
{
	BinaryNode<ItemType> *nodePtr = this->rootPtr;
    BinaryNode<ItemType> *prevNodePtr = nodePtr;
	while (nodePtr->getLeftPtr())
	{
        prevNodePtr = nodePtr;
		nodePtr = nodePtr->getLeftPtr();
	}
    
	//return nodePtr->getItem();
    return prevNodePtr->getItem();
}

template <class ItemType>
ItemType BinarySearchTree<ItemType>::findLargest() const
{

	BinaryNode<ItemType> *nodePtr = this->rootPtr;
	while (nodePtr->getRightPtr())
	{
		nodePtr = nodePtr->getRightPtr();
	}

	return nodePtr->getItem();
}

template <class ItemType>
void BinarySearchTree<ItemType>::findNodesInRange(const ItemType & min, const ItemType & max, void visit(ItemType &)) const
{
	_findNodesInRange(this->rootPtr, min, max, visit);

}


template <class ItemType>
void BinarySearchTree<ItemType>::_findNodesInRange(BinaryNode<ItemType>* nodePtr, const ItemType & min, const ItemType & max, void visit(ItemType &)) const
{

	if (nodePtr != 0 && nodePtr->getItem() > min)
		_findNodesInRange(nodePtr->getLeftPtr(), min, max, visit);

	if (nodePtr != 0 && (nodePtr->getItem() >= min && nodePtr->getItem() <= max))
	{
		ItemType item;
		item = nodePtr->getItem();
		visit(item);
	}


	if (nodePtr != 0 && nodePtr->getItem() < max)
		_findNodesInRange(nodePtr->getRightPtr(), min, max, visit);

}



#endif
