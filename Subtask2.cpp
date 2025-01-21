
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

//I used sorting methods from one of my past homeworks and modified them a little bit to 
// keep track of the indices as well

void convertLower(string &inputStr) {
    for (int i =0; i <inputStr.size(); i++) {
        if (inputStr[i] >= 'A' && inputStr[i] <= 'Z') {
            inputStr[i] = inputStr[i] + 32;
        }
    }
}

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

int main(int argc, char const *argv[]){

     freopen( argv[1], "r", stdin );
	if( argc > 2 ){
		freopen( argv[2], "w", stdout );
	}

    int patternNo;
    string* strings;
    int* counts;
    string inputStr;
    long long* hashes;
    int* originalIndices;
    long long* p_pow;
    
    ifstream file(argv[1]);

    stringstream buffer;
    buffer << file.rdbuf();

    file.close();


    string logFile = buffer.str();

    istringstream contentStream(logFile);

    string line;
    int i = 0;
    int numberOfLines = 0;
    while (getline(contentStream, line)) {

        istringstream lineStream(line);
        if(i==0){
            lineStream >> inputStr;
            convertLower(inputStr);
        }else if(i==1){
            lineStream >> patternNo;
            strings = new string[patternNo];
            counts = new int[patternNo];
            hashes = new long long[patternNo];
        }else{
            string temp;
            lineStream >> temp;
            convertLower(temp);
            strings[i-2] = temp;
            hashes[i-2] = hashingFunction(strings[i-2]);
            counts[i-2] = 0;
        }
        i++;
    }

    originalIndices = new int[patternNo];
    for (int i = 0; i < patternNo; ++i) {
         originalIndices[i] = i;
    }

    quickSort(hashes,originalIndices,0,patternNo-1);

    int min_length = strings[0].size();

    for (int i = 1; i < patternNo; ++i) {
        if(strings[i].size() < min_length) 
        min_length = strings[i].size();
    }

    int max_length = min_length+5;
    p_pow = new long long[max_length];

    
    long long p = 53;
    long long size = 1e9 + 9;


    p_pow[0] = 1;
    for (int i = 1; i < max_length; i++) {
        p_pow[i] = (p_pow[i - 1] * p) % size;
    }
    //this is the modular inverse for rolling hash I calculated it using the extended euclidean algorithm manually
    long long p_inv = 188679247;

    for(int i=0;i<=4;i++){
        int cnst = min_length+i;
        long long hash = hashingFunction(inputStr.substr(0,cnst));
        for(int j=0; j<=inputStr.size()-cnst;j++){

            if (j != 0) {
                hash = (hash - (inputStr[j - 1] - 'a' + 1))%size;
            if (hash < 0) {
                hash += size;
            }
                hash = (hash * p_inv) % size;
                hash = (hash + (inputStr[j + cnst - 1] - 'a' + 1) * p_pow[cnst - 1]) % size;
        }
                int idx = binarySearch(hashes,0,patternNo-1,hash);
            if(idx!=-1){
                int originalIndex = originalIndices[idx];
                counts[originalIndex]++;
            }
            }
        }
    


        for (int i = 0; i < patternNo; i++) {
            cout << counts[i] << endl;
        }

    delete [] p_pow;
    delete [] hashes;
    delete [] originalIndices;
    delete [] counts;
    delete [] strings;
    return 0;
}       