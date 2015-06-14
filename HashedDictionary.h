// Created by Frank M. Carrano and Tim Henry.
// Modified by: Rohan Uppuluri
// HashedDictionary.h: Header file for HashedDictionary class

#ifndef _HASHEDDICTIONARY
#define _HASHEDDICTIONARY

#include "LinkedList.h"
#include "Entry.h"


using namespace std;

template <class KeyType,class ItemType>

class HashedDictionary
{
private:

    LinkedList<Entry<KeyType,ItemType>*> **hashTable;

    int tableSize;
    int bucketSize;
    int itemCount;
	void deleteDictionary();


public:

	HashedDictionary(int,int);

    ~HashedDictionary()
    {
        deleteDictionary();
    }

    // accessor for ItemCount
    int getItemCount() const {return itemCount;}

	ItemType * getItem(const KeyType &searchKey) const;

    double getAverageNumofNodes();

    int getColissions();
    int getColissionsAtIndex(int index);

    int getNumOfEmptyBuckets();

    int getNumOfFullBuckets();

    void displayHashTableList(void visit(KeyType &k));

    void printHashTable(void visit(KeyType & k,int spaces,int index));

    double getLoadFactor();

    int getHashIndex(const KeyType& searchKey) const;
    bool add(const KeyType& searchKey, const ItemType& newItem);
};

// getHashIndex: hash function for the unique key, uses first 6 chars of string and sums the numerical equivalents of each character and
// uses modulo division with table size to produce index
template <class KeyType,class ItemType>
int HashedDictionary<KeyType,ItemType>::getHashIndex(const KeyType& searchKey) const
{
    int sum=0;
    for (int i = 0; i < searchKey.length() ;i++)
    {
        sum += searchKey[i];
    }
    sum = sum % tableSize;
    return sum;
}

// getLoadFactor: calculates load factor of hash table
template <class KeyType,class ItemType>
double HashedDictionary<KeyType,ItemType>::getLoadFactor()
{
    // Number of non-empty buckets/tablesize
    int num = tableSize-getNumOfEmptyBuckets();

    double loadFactor = ((num)/static_cast<double>(tableSize))*100;

    return loadFactor;
}

//printHashTable: prints hash table with indenting
template <class KeyType,class ItemType>
void HashedDictionary<KeyType,ItemType>::printHashTable(void visit(KeyType & k,int spaces,int index))
{

    for(int i=0;i<tableSize;i++)
    {
        int s = 0;
        KeyType key;
        if(hashTable[i] != 0)
            key = hashTable[i]->getHead()->next->value->getKey();

        visit(key,s,i);
        if(hashTable[i] != 0)
        {
            ListNode<Entry<KeyType,ItemType>*> *ptr = hashTable[i]->getHead()->next;

            //ptr = ptr->next; // we alraedy visited the first head node
            ptr = ptr->next;
            while(ptr != 0)
            {
                Entry<KeyType,ItemType>* entry = ptr->value;
                ItemType item = entry->getItem();
                KeyType k1;
                k1 = entry->getKey();
                visit(k1,key.length(),-1);
                ptr = ptr->next;
            }

        }

    }
}

//displayHashTableList: displays the items in hash table in a list
template <class KeyType,class ItemType>
void HashedDictionary<KeyType,ItemType>::displayHashTableList(void visit(KeyType &k))
{
    for(int i=0;i<tableSize;i++)
    {
        if(hashTable[i] != 0)
        {
            ListNode<Entry<KeyType,ItemType>*> *ptr = hashTable[i]->getHead();
            ptr = ptr->next;
            while(ptr != 0)
            {
                Entry<KeyType,ItemType>* entry = ptr->value;

                ItemType item = entry->getItem();
                KeyType k;
                k = entry->getKey();
                visit(k);
                ptr = ptr->next;
            }

        }
    }
}

// getNumOfFullBuckets: calculates number of buckets that are full
template <class KeyType,class ItemType>

int HashedDictionary<KeyType,ItemType>::getNumOfFullBuckets()
{
    int full = 0;
    for(int i=0;i<tableSize;i++)
    {
        if(hashTable[i] != 0 && hashTable[i]->getCount() >= 3)
        {
            full++;
        }
    }
    return full;
}

// getNumOfEmptyBuckets: calculates number of buckets that are empty
template <class KeyType,class ItemType>
int HashedDictionary<KeyType,ItemType>::getNumOfEmptyBuckets()
{
    int empty = 0;
    for(int i=0;i<tableSize;i++)
    {
        if(hashTable[i] == 0)
        {
            empty++;
        }
    }
    return empty;

}

//getColissions: calculates total number of colissions for hash table
template <class KeyType,class ItemType>
int HashedDictionary<KeyType,ItemType>::getColissions()
{
    int colissions = 0;
    for(int i=0;i<tableSize;i++)
    {
        if(hashTable[i] != 0)
        {
            int c = hashTable[i]->getCount();
            colissions += (c-1);
        }
    }
    return colissions;
}

//getColissionsAtIndex: calculates number of colissions for specific index
template <class KeyType,class ItemType>
int HashedDictionary<KeyType,ItemType>::getColissionsAtIndex(int index)
{
    int colissions = 0;

    if(hashTable[index] != 0)
    {
        int c = hashTable[index]->getCount();
        colissions += (c-1);
    }
    return colissions;
}

//getAverageNumofNodes: calculates average for the amount of items in a bucket
template <class KeyType,class ItemType>
double HashedDictionary<KeyType,ItemType>::getAverageNumofNodes()
{
    // sum / number of non-empty buckets
    double average;
    if(tableSize-getNumOfEmptyBuckets() != 0)
        average = itemCount/(tableSize-getNumOfEmptyBuckets());
    else
        average = 0.0;
    return average;
}

// add: adds the item and key to hash table
template <class KeyType,class ItemType>
bool HashedDictionary<KeyType,ItemType>::add(const KeyType& searchKey, const ItemType& newItem)
{

    int hashIndex = getHashIndex(searchKey);

    if(hashTable[hashIndex] == 0)
    {
        Entry<KeyType, ItemType> * entryToAddPtr = new Entry<KeyType, ItemType>(searchKey,newItem);
        hashTable[hashIndex] = new LinkedList<Entry<KeyType,ItemType>*>();


        hashTable[hashIndex]->insertNode(entryToAddPtr);
        itemCount++;
    }
    else
    {
        if(hashTable[hashIndex]->getCount() == bucketSize)
        {
            return false;
        }
        Entry<KeyType, ItemType> * entryToAddPtr = new Entry<KeyType, ItemType>(searchKey,newItem);
        hashTable[hashIndex]->insertNode(entryToAddPtr);
        itemCount++;
    }

    return true;
}

// constructor for HashedDictionary that accepts an integer size of hash table
template <class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary(int tablesize,int bucketsize)
{

	tableSize = tablesize;

	hashTable = new LinkedList<Entry<KeyType, ItemType>*> *[tableSize];
	for (int i = 0; i<tableSize; i++)
	{
		hashTable[i] = 0;
	}
	bucketSize = bucketsize;

}

// getItem: finds item by its unique key
template <class KeyType, class ItemType>
ItemType * HashedDictionary<KeyType, ItemType>::getItem(const KeyType &searchKey) const
{
	int hashCode = getHashIndex(searchKey);
	ItemType *found = 0;
	ListNode<Entry<KeyType, ItemType>*> *ptr = hashTable[hashCode]->getHead();
	ptr = ptr->next;
	bool success = false;
	while (ptr && !success)
	{
		Entry<KeyType, ItemType>* entry = ptr->value;
		ptr = ptr->next;
		ItemType item;
		item = entry->getItem();
		//item.print();
		if (entry->getKey() == searchKey)
		{
			found = new ItemType(entry->getItem());
			success = true;
		}
	}

	return found;

}

// destructor for HashedDictionary
template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::deleteDictionary()
{
	for (int i = 0; i<tableSize; i++)
	{
		if (hashTable[i])
			delete hashTable[i];
	}
	delete[] hashTable;

}


#endif
