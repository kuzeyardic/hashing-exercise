
/**
* Title: Hash Table
* Author : Berke Kuzey Ardıç
* ID: 22103340
* Section : 1
* Homework : 3
* Description : a hashtable class that uses seperate chaining */


#ifndef HashTable_h
#define HashTable_h
#include <string>
#include "LinkedList.h"
using namespace std;
class HashTable{
public:
    bool isEmpty();
    void insert(string key);
    void remove(string key);
    bool isExists(string key);
    bool isExists(string& key, long index);
    long hashFunction(string key);   
    long getSize(); 
    HashTable();
    ~HashTable();

private:
    LinkedList<string>* table;    
    long size;
    long totalSize;
    long* sizeOfEachBucket;
};
#endif /* HashTable_h */
