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
    int overflow;
	void deleteDictionary();


public:

	HashedDictionary(int,int);

    ~HashedDictionary()
    {
        deleteDictionary();
    }

    // accessor for ItemCount
    int getItemCount() const {return itemCount;}

    HashedDictionary<KeyType,ItemType>* reHash(const HashedDictionary<KeyType,ItemType>*,int newSize,int newBucketSize);

	ItemType * getItem(const KeyType &searchKey) const;

    double getAverageNumofNodes();

    int getColissions();
    int getColissionsAtIndex(int index);

    int getNumOfEmptyBuckets();

    int getNumOfFullBuckets();
    int getOverflow() const {return overflow;}
    void setOverflow(int input) {overflow = input;}

    void displayHashTableList(void visit(KeyType &k,ItemType &item)) const;

    void printHashTable(void visit(KeyType & k,int spaces,int index,ItemType &item)) const;

    void updateTableSize(int tz){ tableSize = tz;}

    double getLoadFactor();

    int getHashIndex(const KeyType& searchKey) const;
    bool add(const KeyType& searchKey, const ItemType& newItem);

    int getBucketSize(){return bucketSize;}
    int getTableSize(){ return tableSize;}

    LinkedList<Entry<KeyType,ItemType>*> ** getHashTable() const {return hashTable;}

	bool remove(const KeyType &target, ItemType& removeItem);

};

// getHashIndex: hash function for the unique key, uses first 6 chars of string and sums the numerical equivalents of each character and
// uses modulo division with table size to produce index
/*template <class KeyType,class ItemType>
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
*/

// getHashIndex: hash function for the unique key, uses first 6 chars of string and sums the numerical equivalents of each character and
// uses modulo division with table size to produce index
template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getHashIndex(const KeyType& searchKey) const{
	int sum = 0;
	int zeroes = 0;
	int ones = 0;
	for ( int i = 0; i < searchKey.length(); i++ ){
		if ( searchKey[i] == '0' ) zeroes++;
		if ( searchKey[i] == '1' ) ones++;
		if( i != 0 ) sum += ( searchKey[i] * searchKey[i] * searchKey[i] ) * i;
		else sum += ( searchKey[i] * searchKey[i] * searchKey[i] );
	}
	if ( zeroes != 0 ) sum *= zeroes;
	if ( ones != 0 ) sum *= ones;
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
void HashedDictionary<KeyType,ItemType>::printHashTable(void visit(KeyType & k,int spaces,int index,ItemType& item)) const
{

    for(int i=0;i<tableSize;i++)
    {
        int s = 0;
        KeyType key;
        ItemType item;
        if(hashTable[i] != 0)
        {
            key = hashTable[i]->getHead()->next->value->getKey();
            item = hashTable[i]->getHead()->next->value->getItem();
            //visit(key,s,i,item);

        }

        visit(key,s,i,item);
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
                visit(k1,10,-1,item);
                ptr = ptr->next;
            }

        }

    }
}

//displayHashTableList: displays the items in hash table in a list
template <class KeyType,class ItemType>
void HashedDictionary<KeyType,ItemType>::displayHashTableList(void visit(KeyType &k,ItemType& item)) const
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
                visit(k,item);
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
        if(hashTable[i] != 0 && hashTable[i]->getCount() >= bucketSize)
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
            overflow++;
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
    itemCount=0;
    overflow = 0;

}

// getItem: finds item by its unique key
template <class KeyType, class ItemType>
ItemType * HashedDictionary<KeyType, ItemType>::getItem(const KeyType &searchKey) const
{
    int hashCode = getHashIndex(searchKey);
    ItemType *found = 0;
    if(hashTable[hashCode] != 0)
    {
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

template <class KeyType,class ItemType>
HashedDictionary<KeyType,ItemType>* HashedDictionary<KeyType,ItemType>::reHash(const HashedDictionary<KeyType,ItemType>* oldHashTable,int newSize,int newBucketSize)
{
    HashedDictionary<KeyType,ItemType> *newTable = new HashedDictionary<KeyType,ItemType>(newSize,newBucketSize);

    LinkedList<Entry<KeyType,ItemType>*> **oldTable = oldHashTable->getHashTable();

    int oldOverflow = oldHashTable->getOverflow();

    newTable->setOverflow(oldOverflow);

    for(int i=0;i<oldHashTable->tableSize;i++)
    {
        if(oldTable[i] != NULL)
        {
            ListNode<Entry<KeyType,ItemType>*> *ptr = oldTable[i]->getHead()->next;

            //ptr = ptr->next;
            while(ptr != 0)
            {
                Entry<KeyType,ItemType>* entry = ptr->value;
                ItemType item = entry->getItem();
                KeyType k1;
                k1 = entry->getKey();
                if(!newTable->add(k1,item))
                {
                    //cout<<"Rejected"<<endl;
                }
                ptr = ptr->next;
            }

        }

    }

    return newTable;
}


template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::remove(const KeyType &target, ItemType& removeItem)
{

	int hashIndex = getHashIndex(target);
	if (hashTable[hashIndex] != 0)
	{
		ItemType *found = 0;
		LinkedList<Entry<KeyType, ItemType>*> *ptr = hashTable[hashIndex];
		Entry<KeyType, ItemType> *entry = new Entry<KeyType, ItemType>;
		entry->setKey(target);
		entry->setItem(removeItem);

		bool success = ptr->deleteNode(entry);
		if (success) {
			itemCount--;
			if (ptr->getCount() == 0)
			{
				delete ptr;
				hashTable[hashIndex] = 0;
			}
			return true;
		}



	}
	else
	{
		// HashTable empty at the index
		return false;

	}

	return false;
}


#endif
