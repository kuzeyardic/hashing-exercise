
/**
* Title: Hash Table
* Author : Berke Kuzey Ardıç
* ID: 22103340
* Section : 1
* Homework : 3
* Description : a hashtable class that uses seperate chaining */




#include "HashTable.h"

HashTable::HashTable(){
    size = 12582917;
    table = new LinkedList<string>[size];
    totalSize=0;
    sizeOfEachBucket = new long[size];
    for(int i = 0; i < size; i++){
        sizeOfEachBucket[i] = 0;
    }
}

HashTable::~HashTable() {
    delete[] table;
    delete[] sizeOfEachBucket;
}

bool HashTable::isEmpty(){
      return totalSize == 0; 
}

long HashTable::hashFunction(string key){
    long hashVal = 0; long p_pow = 1;
    for (int i=0;i<key.size();i++) {
        hashVal = (hashVal + (key[i] - 'a' + 1) * p_pow) % size;
        p_pow = (p_pow * 31) % size;
    }
    return hashVal;
}

bool HashTable::isExists(string&  key, long index){
    return table[index].getPosition(key) != -1;
}

void HashTable::insert(string key){
    long index = hashFunction(key);
    table[index].insert(key);
    sizeOfEachBucket[index]++;
    totalSize++;

}

void HashTable::remove(string key){

    long index = hashFunction(key);
    if(table[index].remove(table[index].getPosition(key))){
        sizeOfEachBucket[index]--;
        totalSize--;
    }
  
}

bool HashTable::isExists(string key){
    long index = hashFunction(key);
    return table[index].getPosition(key) != -1;
}

long HashTable::getSize(){
        return totalSize;    
}




