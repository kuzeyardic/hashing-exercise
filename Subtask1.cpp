


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
#include <cctype>


 long hashFunction(string key){
    long hashVal = 0; long p_pow = 1;
    for (int i=0;i<key.size();i++) {
        hashVal = (hashVal + (key[i] - 'a' + 1) * p_pow) % 12582917;
        p_pow = (p_pow * 31) % 12582917;
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


int main(int argc, char const *argv[]){
    freopen( argv[1], "r", stdin );
	if( argc > 2 ){
		freopen( argv[2], "w", stdout );
	}
    
    HashTable myHashTable;
    int inputNo;
    string* strings;
    int count=0;
    string inputStr;
    
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

    for(int i=0;i<inputNo;i++){
        getline(contentStream, line);
        istringstream lineStream(line);
        lineStream >> inputStr;
        convertLower(inputStr);
        strings[i] = inputStr;  
        myHashTable.insert(inputStr);
    }

    long maxLength=0;

    for(int i=0;i<inputNo;i++){
        if(strings[i].size()>maxLength){
            maxLength = strings[i].size();
        }
    }

    long p_pow[maxLength];
    long size = 12582917;

    p_pow[0] = 1;

    for(int i=1;i<maxLength;i++){
        p_pow[i] = p_pow[i-1]*31%size;
    }


  for(int i = 0;i<inputNo;i++){
        int currStrSize = strings[i].size();
        long hash1 =0;
        long hash2 = hashFunction(strings[i]);

    for(int j=0;j<strings[i].size();j++){
        string t1 = strings[i].substr(0,j);
        hash1 += (strings[i][j]-'a'+1)*p_pow[j]%size;
        string t2 = strings[i].substr(j,currStrSize);
        if(j!=0)
        hash2 = ((hash2-(strings[i][j-1]-'a'+1)*p_pow[j-1])+size)%size;
        if(j==currStrSize-1||j==0){
        if(myHashTable.isExists(t1,hash1)){
        count++;
        }
        if(myHashTable.isExists(t2,hash2)){
        count++;
        }
        }
    }
}

cout<<count<<endl;

    delete[] strings;
    return 0;
}  