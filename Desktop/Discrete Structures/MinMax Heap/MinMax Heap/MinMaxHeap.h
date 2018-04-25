//
//  MinMaxHeap.h
//  MinMax Heap
//
//  Created by Jack Crissey on 4/17/17.
//  Copyright © 2017 Jack Crissey. All rights reserved.
//

#ifndef MinMaxHeap_h
#define MinMaxHeap_h

#include <stdio.h>
#include <string>

template <typename T>
class HeapObject
{
public:
    HeapObject(T input);
    HeapObject<T>* other;
    T data;
    int arrayLocation;
};

template <typename T>
class Heap
{
public:
    Heap(int input);
    //friend void MinMaxHeap<T>();
    HeapObject<T>** heap;
    int size;
    //Heap<T>* other;
    //int arrayLocation;
    //int compareValuesMax(T data1, T data2);
    //int compareValuesMin(T data1, T data2);
    void bubbleUp(HeapObject<T>* object, int(*pf)(T,T));
    void trickleDown(HeapObject<T>* object, int size, int(*pf)(T,T));
    ~Heap();
    //void bubbleUp(Heap<T>* heap, int (Heap<T>::*compare)(T data1, T data2));
    //void trickleDown(Heap<T>* heap, int (Heap<T>::*compare)(T data1, T data2));
    //int parentLoc;
};

template <typename T>
class MinMaxHeap
{
public:
    MinMaxHeap(int capacity);
    void insert(const T& data);
    T deleteMin();
    T deleteMax();
    void dump();
    int size();
    void locateMin(int pos, T& data, int& index);
    void locateMax(int pos, T& data, int& index);
    ~MinMaxHeap();
    MinMaxHeap(const MinMaxHeap<T>& other);
    const MinMaxHeap<T>& operator=(const MinMaxHeap<T>& rhs);
    Heap<T>* high;
    Heap<T>* low;
    int sizes;
    int capacity;
};
template <typename T>
int compareValuesMax(T data1, T data2);

template <typename T>
int compareValuesMin(T data1, T data2);

#include "MinMaxHeap.cpp"/* MinMaxHeap_h */
#endif
