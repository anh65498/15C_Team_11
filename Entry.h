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
    
public:
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
    ItemType getItem() const{return item;};
    KeyType getKey() const {return searchKey;};
    void setItem(const ItemType& newEntry)
    {
        item = newEntry;
    };
    bool operator==(const Entry<KeyType, ItemType>& rightHandItem) const;
    bool operator==( Entry<KeyType, ItemType> * &rightHandItem) ;
    
}; // end Entry

template <class KeyType, class ItemType>
bool Entry<KeyType, ItemType>::operator==(const Entry<KeyType, ItemType>& rightHandItem) const
{
    return (searchKey == rightHandItem.getKey());
}  // end operator==

template <class KeyType, class ItemType>
bool Entry<KeyType, ItemType>::operator==( Entry<KeyType, ItemType>* &rightHandItem)
{
    return (searchKey == rightHandItem->getKey());
}

#endif