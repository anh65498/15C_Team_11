/**~*~*
Queue template
*~**/
#ifndef DYNAMICQueue_H
#define DYNAMICQueue_H
#include <iostream>
using namespace std;

template <class T>
class Queue
{
private:
	// Structure for the stach nodes
	struct QueueNode
	{
		T value;          // Value in the node
		QueueNode *next;  // Pointer to next node
	};

	QueueNode *top;     // Pointer to the Queue top
	QueueNode *back;
	int count;

public:
	//Constructor
	Queue(){ top = NULL; back = NULL; count = 0; }

	// Destructor
	~Queue();

	// Queue operations
	bool enqueue(T);
	bool dequeue(T &);
	bool isEmpty();

	int getCount(){
		return count;
	}
	bool getTop(T);
};

/**~*~*
Destructor
*~**/
template <class T>
Queue<T>::~Queue()
{
	QueueNode *currNode, *nextNode;

	// Position nodePtr at the top of the Queue.
	currNode = top;

	// Traverse the list deleting each node.
	while (currNode) //while (currNode != NULL)
	{
		nextNode = currNode->next;
		delete currNode;
		currNode = nextNode;
	}
}

/**~*~*
Member function enqueue enqueuees the argument onto
the Queue.
*~**/
template <class T>
bool Queue<T>::enqueue(T item)
{
	QueueNode *newNode; // Pointer to a new node

	// Allocate a new node and store num there.
	newNode = new QueueNode;
	if (!newNode)
		return false;
	newNode->value = item;

	// Update links and counter
	if (top == NULL && back == NULL)
	{
		// inserting first item
		newNode->next = NULL;
		top = newNode;
		back = top;

	}
	else{
		newNode->next = NULL;
		back->next = newNode;
		back = newNode;
	}

	count++;

	return true;
}

/**~*~*
Member function dequeue dequeues the value at the top
of the Queue off, and copies it into the variable
passed as an argument.
*~**/
template <class T>
bool Queue<T>::dequeue(T &item)
{
	QueueNode *temp; // Temporary pointer

	// empty Queue
	if (count == 0)
		return false;

	// dequeue value off top of Queue
	item = top->value;
	temp = top->next;
	delete top;
	if (temp == 0)
	{
		top = temp;
		back = temp;
	}
	else
		top = temp;
	count--;

	return true;
}

template <class T>
bool Queue<T>::getTop(T item)
{
	// empty Queue
	if (count == 0)
		return false;

	// dequeue value off top of Queue
	item = top->value;
	return true;
}

/**~*~*
Member function isEmpty returns true if the Queue
is empty, or false otherwise.
*~**/
template <class T>
bool Queue<T>::isEmpty()
{
	return count == 0;
}



#endif
