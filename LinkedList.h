// A class template for holding a linked list.
// The node type is also a class template.

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <string>
#include <iostream>
#include <fstream>

//*********************************************
// The ListNode class creates a type used to  *
// store a node of the linked list.           *
//*********************************************

template <class T>
class ListNode
{
public:
    T value;           // Node value
    ListNode<T> *next; // Pointer to the next node
    ListNode<T> *prev;
    
    ListNode() {
        
        //value = NULL;
        next = NULL;
        prev = NULL;}
    
    // Constructor
    ListNode(T nodeValue){ value = nodeValue; next = NULL; prev = NULL; }
    
    
};

//*********************************************
// LinkedList class                           *
//*********************************************

template <class T>
class LinkedList
{
private:
    ListNode<T> *head;   // List head pointer
    ListNode<T> *tail;
    int count;
    
public:
    // Constructor
    LinkedList(){
        
        head = new ListNode <T> ();
        //head = new ListNode<T>();
        tail = NULL;
        count = 0; }
    
    // Destructor
    ~LinkedList();
    
    // Linked list operations
    int getCount() {return count;}
    void insertNode(T);
    void insertFront(T);
    bool deleteNode(T nodeValue);
    // delete
    // search
    // other linked list operations ...
    // ...
    void displayList() const;
    void displayReverseList(std::ostream & out);
    
    ListNode <T> * getHead() { return head; }
    ListNode <T> * getTail() { return tail; }
    
};

//**************************************************
// The insertNode function inserts a node with     *
// newValue copied to its value member.            *
//**************************************************

template <class T>
void LinkedList<T>::insertNode(T newValue)
{
    ListNode<T> *newNode;             // A new node
    //ListNode<T> *nodePtr;             // To traverse the list
    //ListNode<T> *previousNode = NULL; // The previous node
    
    newNode = new ListNode<T>(newValue); // Allocate a new node and store newValue there.
    // nodePtr = head;                      // Position nodePtr at the head of list.
    //previousNode = NULL;                 // Initialize previousNode to NULL.
    
    // If the new node is to be the 1st in the list,
    // insert it before all other nodes.
    if (head->next == NULL)
    {
        
        newNode->next = NULL;
        head->next = newNode;
        newNode->prev = head;
        tail = newNode;
        
    }
    else  // Otherwise insert after the previous node.
    {
        newNode->prev = tail;
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
    }
    //newNode->next = nodePtr;
    count++;
}

template <class T>
void LinkedList<T>::insertFront(T newValue)
{
    ListNode<T> *newNode;             // A new node
    //ListNode<T> *nodePtr;             // To traverse the list
    //ListNode<T> *previousNode = NULL; // The previous node
    
    newNode = new ListNode<T>(newValue); // Allocate a new node and store newValue there.
    // nodePtr = head;                      // Position nodePtr at the head of list.
    //previousNode = NULL;                 // Initialize previousNode to NULL.
    
    // If the new node is to be the 1st in the list,
    // insert it before all other nodes.
    if (head->next == NULL)
    {
        
        newNode->next = NULL;
        head->next = newNode;
        newNode->prev = head;
        tail = newNode;
        
    }
    else  // Otherwise insert after the previous node.
    {
        newNode->prev = head;
        newNode->next = head->next;
        head->next->prev = newNode;
        head->next = newNode;
    }
    //newNode->next = nodePtr;
    count++;
}

//**************************************************
// displayList shows the value stored in each node *
// of the linked list pointed to by head.          *
//**************************************************

template <class T>
void LinkedList<T>::displayList() const
{
    ListNode<T> *nodePtr;  // To move through the list
    
    // Position nodePtr at the head of the list.
    nodePtr = head->next;
    
    // While nodePtr points to a node, traverse
    // the list.
    while (nodePtr)
    {
        std::cout << nodePtr->value << std::endl;  // Display the value in this node.
        nodePtr = nodePtr->next;         // Move to the next node.
    }
}


template <class T>
void LinkedList<T>::displayReverseList(std::ostream & out)
{
    ListNode<T> *nodePtr;  // To move through the list
    
    // Position nodePtr at the head of the list.
    nodePtr = tail;
    
    // While nodePtr points to a node, traverse
    // the list.
    while (nodePtr && nodePtr != head)
    {
        out<< nodePtr->value;  // Display the value in this node.
        nodePtr = nodePtr->prev;         // Move to the next node.
    }
    
    
}

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
//**************************************************

template <class T>
LinkedList<T>::~LinkedList()
{
    ListNode<T> *nodePtr;   // To traverse the list
    ListNode<T> *nextNode;  // To point to the next node
    
    // Position nodePtr at the head of the list.
    nodePtr = head;
    
    // While nodePtr is not at the end of the list...
    while (nodePtr != NULL)
    {
        // Save a pointer to the next node.
        nextNode = nodePtr->next;
        
        // Delete the current node.
        delete nodePtr;
        
        // Position nodePtr at the next node.
        nodePtr = nextNode;
    }
}

/*
 Deletes the node from the list
 */

template <class T>
bool LinkedList<T>::deleteNode(T nodeValue)

{
    ListNode<T> *nodePtr;   // To traverse the list
    ListNode<T> *nextNode;  // To point to the next node
    
    // Position nodePtr at the head of the list.
    nodePtr = head->next;
    
    // While nodePtr is not at the end of the list...
    
    while (nodePtr != NULL)
    {
        
        //if(nodePtr->value == nodeValue)
        T val = nodePtr->value;
        if(val->operator==(nodeValue))
        {
            // Item found can proceed to delete
            ListNode<T> *delNode = nodePtr;
            ListNode<T> *prevNode = nodePtr->prev;
            if(delNode == tail)
            {
                tail = delNode->prev;
                
            }
            if(nodePtr->next != 0)
                nodePtr->next->prev = prevNode;
            prevNode->next = nodePtr->next;
            
            
            delete delNode;
            count--;
            return true;
            
        }
        // Save a pointer to the next node.
        nodePtr = nodePtr->next;
        
    }
    return false;
    
}
#endif