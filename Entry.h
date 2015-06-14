// Created by Frank M. Carrano and Tim Henry.
// Modified by: Rohan Uppuluri
// Entry.h: Header file for Entry class

#ifndef _ENTRY
#define _ENTRY

template <class KeyType, class ItemType>
class Entry
{
private:
    ItemType item;
    KeyType searchKey;
    
	//mutators
	void setItem(const ItemType& newEntry)
	{
		item = newEntry;
	}
    void setKey(const KeyType& key)
    {
        searchKey = key;
	}
    
public:
    Entry() {};
    Entry(ItemType newEntry, KeyType key)
    {
        item = newEntry;
        searchKey = key;
    }
    Entry(KeyType key,ItemType newEntry)
    {
        item = newEntry;
        searchKey = key;
    }
	//accessors
    ItemType getItem() const{return item;};
    KeyType getKey() const {return searchKey;};

    bool operator==(const Entry<KeyType, ItemType>& rightHandItem) const;
    
}; 

//overloads operator ==
template <class KeyType, class ItemType>
bool Entry<KeyType, ItemType>::operator==(const Entry<KeyType, ItemType>& rightHandItem) const
{
    return (searchKey == rightHandItem.getKey());
}  

#endif
