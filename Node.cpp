
/**
* Title: Hash Table
* Author : Berke Kuzey Ardıç
* ID: 22103340
* Section : 1
* Homework : 3
* Description : a node class that is necessary for the implementation of linkedlist */

#ifndef Node_cpp
#define Node_cpp
#include "Node.h"
template <class ItemType>
Node<ItemType>::Node(){
    next = nullptr;
}

template <class ItemType>
Node<ItemType>::Node(const ItemType anItem){
    item = anItem;
    next = nullptr;
}

template <class ItemType>
Node<ItemType>::Node(const ItemType anItem, Node<ItemType>* nextNodePtr){
    item = anItem;
    next = nextNodePtr;
}

template <class ItemType>
ItemType& Node<ItemType>::getItem(){
    return item;
}
template <class ItemType>
Node<ItemType>*& Node<ItemType>::getNext(){
    return next;
}
template <class ItemType>
void Node<ItemType>::setItem(const ItemType anItem){
    item = anItem;
}
template <class ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr){
    next = nextNodePtr;
}
#endif
