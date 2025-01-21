
/**
* Title: Hash Table
* Author : Berke Kuzey Ardıç
* ID: 22103340
* Section : 1
* Homework : 3
* Description : a linkedlist class that is necessary for the implementation of hashtable */


#ifndef LinkedList_h
#define LinkedList_h
#include "Node.h"
#include <string>
#include <stdio.h>
template <class ItemType>
class LinkedList {
public:
    LinkedList();
    LinkedList(const LinkedList<ItemType>& aList);
    ~LinkedList();
    bool isEmpty() const;
    int getLength() const;
    void insert(const ItemType newEntry);
    bool remove(int position);
    int getPosition(const ItemType& anEntry) const;
    ItemType getEntry (int position) const;
    Node<ItemType>* getNodeAt(int position) const;
    Node<ItemType>* headPtr;
    int itemCount;
};
#include "LinkedList.cpp"
#endif /* LinkedList_h */