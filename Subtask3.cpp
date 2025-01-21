/**
* Title: Hash Table
* Author : Berke Kuzey Ardıç
* ID: 22103340
* Section : 1
* Homework : 3
* Description : it is explained in report pdf */


#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <stdio.h>




void swap(long long& num1, long long& num2, int& idx1, int& idx2);
void quickSort(long long* arr, int* indices, long long first, long long last);
void partition(long long* arr, int* indices, long long first, long long last, long long& pivotIndex);

void quickSort(long long* arr, int* indices, long long first, long long last){
    if((last - first) < 1)
        return ;
    
    long long pivotIndex;
    partition(arr, indices, first, last, pivotIndex);
    
    quickSort(arr, indices, first, pivotIndex - 1);
    quickSort(arr, indices, pivotIndex + 1, last);
}

void partition(long long* arr, int* indices, long long first, long long last, long long& pivotIndex){
    pivotIndex = first;
    long long pivot = arr[pivotIndex];
    
    long long lastS1 = first;
    long long firstUnknown = first + 1;
    
    while(firstUnknown <= last){
        if (arr[firstUnknown] < pivot) {
            lastS1++;
            swap(arr[firstUnknown], arr[lastS1], indices[firstUnknown], indices[lastS1]);
        }
        firstUnknown++;
    }
    
    swap(arr[first], arr[lastS1], indices[first], indices[lastS1]);
    pivotIndex = lastS1;
}

void swap(long long& num1, long long& num2, int& idx1, int& idx2){
    long long temp = num1;
    num1 = num2;
    num2 = temp;

    int tempIdx = idx1;
    idx1 = idx2;
    idx2 = tempIdx;
}

long long binarySearch  (long long* arr, long long l, long long r, long long x) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x)
            return mid;
        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);
        return binarySearch(arr, mid + 1, r, x);
    }
    return -1;
}


long long hashingFunction(string key){
    long long size = 1e9+9;
    long long hashVal = 0; long long p_pow = 1;
    for (int i=0;i<key.size();i++) {
        hashVal = (hashVal + (key[i] - 'a' + 1) * p_pow) % size;
        p_pow = (p_pow * 53) % size;
    }
    return hashVal;
}

void convertLower(string &inputStr) {
    for (int i = 0; i < inputStr.size(); i++) {
        if (inputStr[i] >= 'A' && inputStr[i] <= 'Z') {
            inputStr[i] = inputStr[i] + 32;
        }
    }
}


int main(int argc, char const *argv[])
{

     freopen( argv[1], "r", stdin );
	if( argc > 2 ){
		freopen( argv[2], "w", stdout );
	}
    
    int inputNo;
    string* strings;
    long long* hashes;
    int* originalIndices;
    
    ifstream file(argv[1]);

    stringstream buffer;
    buffer << file.rdbuf();

    file.close();


    string logFile = buffer.str();

    istringstream contentStream(logFile);

    string line;
    getline(contentStream, line);
    istringstream lineStream(line);
    lineStream >> inputNo;
    strings = new string[inputNo];
    hashes = new long long[inputNo];

    string temp;

    int reverseNo = 0;
    int minSubset = 0;


    for(int i=0;i<inputNo;i++){
        getline(contentStream, line);
        istringstream lineStream(line);
        lineStream >> temp;
        convertLower(temp);
        strings[i] = temp;  
        hashes[i] = hashingFunction(temp);
    }

    originalIndices = new int[inputNo];
    for (int i = 0; i < inputNo; ++i) {
         originalIndices[i] = i;
    }

    quickSort(hashes, originalIndices, 0, inputNo - 1);
    minSubset = inputNo;

    string* reverseStrings = new string[inputNo];
    long long* reverseHashes = new long long[inputNo];

    for (int i= 0; i<inputNo;  i++) {
        string reverseStr = strings[i];
        reverse(reverseStr.begin(), reverseStr.end());
        reverseStrings[i] = reverseStr;
        reverseHashes[i] = hashingFunction(reverseStr);
    }


    long long size = 1e9+9;
    long long p = 53;
    long long p_inv = 188679247;
   


    for (int i = 1; i < inputNo; i++) {

       long long currHash = hashes[i];
       bool foundOriginal = false;

       if(binarySearch(hashes, 0, i-1, currHash) != -1) {
            minSubset--;
            foundOriginal = true;
       }
       int aSize = strings[originalIndices[i]].size();
        long long p_pow =1;

               for(int k=1;k<aSize;k++){
                p_pow = (p_pow * p) % size;
            }
     
        if (!foundOriginal) {
            string key = strings[originalIndices[i]];
            int orgSize = key.size();
            string keyDouble = key + key;
            long long hashDouble = 0;
          

            for (int j=1;j<=key.size();j++) {
                currHash = (currHash - (keyDouble[j - 1] - 'a' + 1))%size;
                if (currHash < 0) {
                    currHash += size;
                }
                    currHash = (currHash * p_inv) % size;
                    currHash = (currHash + (keyDouble[j+orgSize - 1] - 'a' + 1) * p_pow) % size;
                if(binarySearch(hashes, 0, i-1, currHash) != -1) {
                    minSubset--;
                    foundOriginal = true;
                    break;
                }
            } 

        if(!foundOriginal){
            currHash = reverseHashes[originalIndices[i]];
            string key = reverseStrings[originalIndices[i]];
            int orgSize = key.size();
            string keyDouble = key + key;
            long long hashDouble = 0;
            int dex =binarySearch(hashes, 0, i-1, currHash);

            if(dex != -1) {
                minSubset--;
                reverseNo++;
                hashes[i] = currHash;
                quickSort(hashes, originalIndices, dex, i);
                foundOriginal = true;
            }
            
            if(!foundOriginal){
                for (int j=1;j<=key.size();j++) {
                currHash = (currHash - (keyDouble[j - 1] - 'a' + 1))%size;
                if (currHash < 0) {
                    currHash += size;
                }
                    currHash = (currHash * p_inv) % size;
                    currHash = (currHash + (keyDouble[j+orgSize - 1] - 'a' + 1) * p_pow) % size;

                int dex =binarySearch(hashes, 0, i-1, currHash);
                if(dex != -1) {
                    minSubset--;
                    reverseNo++;
                    hashes[i] = currHash;
                    quickSort(hashes, originalIndices, dex, i);
                    break;
                }
            }
        }
   }
 }
      }

    std::cout << reverseNo << endl;
    std::cout << minSubset<<endl;   


    delete[] strings;
    delete[] hashes;
    delete[] originalIndices;
    delete[] reverseStrings;
    delete[] reverseHashes;
    

    return 0;
}       