
/**
* Title: Hash Table
* Author : Berke Kuzey Ardıç
* ID: 22103340
* Section : 1
* Homework : 3
* Description : a linkedlist class that is necessary for the implementation of hashtable */



#ifndef LinkedList_cpp
#define LinkedList_cpp
#include "LinkedList.h"

template <class ItemType>
LinkedList<ItemType>::LinkedList(){
    itemCount=0;
    headPtr=nullptr;
}

template <class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& aList){
    itemCount = aList.itemCount;
    headPtr = nullptr;
    Node<ItemType> * temp = aList.headPtr;

    if(aList.headPtr){
        headPtr = new Node<ItemType>(temp->getItem());
        temp = temp->getNext();
        Node<ItemType>* newChain = headPtr;
        while(temp!=nullptr){
            newChain->setNext(new Node<ItemType>(temp->getItem()));
            newChain = newChain->getNext();
            temp = temp->getNext();
        }
        newChain->setNext(nullptr);
    }
}

template <class ItemType>
LinkedList<ItemType>::~LinkedList(){
    
        while(!isEmpty())
        {
            remove(1);
        }
}

template <class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const{
    Node<ItemType>* temp = getNodeAt(position);
    return (temp->getItem());
}

template <class ItemType>
void LinkedList<ItemType>::insert(const ItemType newEntry) {
    Node<ItemType>* newNode = new Node<ItemType>(newEntry);

    if(headPtr==nullptr){
        headPtr = newNode;
    }
    else{
        Node<ItemType>* temp = headPtr;
        while(temp->getNext()!=nullptr){
            temp = temp->getNext();
        }
        temp->setNext(newNode);
    }

    itemCount++;
}



template <class ItemType>
int LinkedList<ItemType>::getPosition(const ItemType& anEntry) const{
    Node<ItemType>* temp = headPtr;
    int position = 1;
    while(temp!=nullptr){
        if(temp->getItem()==anEntry){
            return position;
        }
        position++;
        temp = temp->getNext();
    }
    return -1;
}



template <class ItemType>
bool LinkedList<ItemType>::remove(int position){
    if(position>0&&position<=itemCount){
        Node<ItemType>* temp = getNodeAt(position);
        if(position==1){
            headPtr = headPtr->getNext();
        }
        else{
            Node<ItemType>* prev =  getNodeAt(position-1);
            prev->setNext(temp->getNext());
        }
        temp->setNext(nullptr);
        delete temp;
        itemCount--;
        return true;
    }
    return false;
}

template <class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const{
    if(position>=1&&position<=itemCount){
            Node<ItemType>* temp = headPtr;
            for(int i=1; i<position; i++){
                temp = temp->getNext();
            }
            return temp;
    }
    return nullptr;
    }


template <class ItemType>
bool LinkedList<ItemType>::isEmpty() const{
    if(itemCount)
    return false;
    
    return true;
}

template <class ItemType>
int LinkedList<ItemType>::getLength() const{
    return itemCount;
}


#endif
