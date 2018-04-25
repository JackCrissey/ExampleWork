//
//  HashTable.hpp
//  Incremental Rehash
//
//  Created by Jack Crissey on 5/3/17.
//  Copyright © 2017 Jack Crissey. All rights reserved.
//

#ifndef HashTable_h
#define HashTable_h

#include <stdio.h>
class HashTable
{
public:
    HashTable(int n=101);
   // HashTable();
    ~HashTable();
    HashTable(HashTable& other);
    const HashTable& operator=(HashTable& rhs);
    void insert(const char *str);
    void insertHelper(char table, int hash, char* newStr);
    bool Rehashing;
    int answer;
    char ** A;
    char ** B;
    char ** C;
    int ACapacity;
    int BCapacity;
    int CCapacity;
    int ASize;
    int BSize;
    int CSize;
    int AInserts;
    int BInserts;
    int CInserts;
    static char * const DELETED ;
    bool isRehashingToA;
    bool isRehashingToB;
    bool isRehashingToC;
    void primeNumSearch(int num, int lower_bound, int upper_bound);
    void startRehashingToA();
    void startRehashingToB();
    void startRehashingToC();
    void resortRehash(char table);
    unsigned int hashCode(const char *str);
    unsigned int hashCode(char *str);
    void reHash(int lowerBound, int upperBount);
    char * remove(const char *str);
    bool find(const char *str) ;
    int tableSize(int table=0);
    int size(int table=0);
    bool isRehashing();
    const char * at(int index, int table=0);
    void dump();
};
#endif /* HashTable_hpp */
