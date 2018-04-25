//
//  MinMaxHeap.cpp
//  MinMax Heap
//
//  Created by Jack Crissey on 4/17/17.
//  Copyright © 2017 Jack Crissey. All rights reserved.
//
#ifdef MinMaxHeap_h
#include <iostream>
#include <string>
#include "MinMaxHeap.h"
using namespace std;

/*This is the constructor for the MinMaxHeap Class it creates 2 Heaps one for the minHeap and one for the maxHeap
 it also sets the capacity of the heaps and initializes size to 0*/
template <typename T>
MinMaxHeap<T>::MinMaxHeap(int capacitys)
{
    capacity = capacitys;
    high = new Heap<T>(capacitys+1);
    low = new Heap<T>(capacitys+1);
    sizes = 0;
}

/*This is the constructor for the heap class. It creates an object array of HeapObjects.
 This is the acutal heap*/
template <typename T>
Heap<T>::Heap(int input)
{
    heap = new HeapObject<T>*[input];
}

/*This is the constructor for the heap objects. The heap object holds it's data value where it is in the array
 and a pointer to the identical object in the other heap. This allows me to very easily locate the other 
 HeapObject in the other heap so that I dont have to do any complex alogrithms and it makes the search time to
 find the other object very short.*/
template <typename T>
HeapObject<T>::HeapObject(T input)
{
    data = input;
    //Initialized at negitive one so that if any errors occured it would throw an error
    arrayLocation = -1;
    //Pointer to the HeapObject witht he same data in the other heap.
    other = NULL;
}

/*This is the bubbleUp function that will bubble up the HeapObject after an insert or bubble up the replacement
 HeapObject when an Object is deleted in the middle of the array. It accepts a HeapObject that I use to locate 
 where the object is that I am going to be bubbling up. It also accepts a comparitor function that I implement
 with a function pointer. The function that I pass in is what determines whether this function bubbles up like
 it should for a Min Heap or for a Max Heap*/
template <typename T>
void Heap<T>::bubbleUp(HeapObject<T>* object, int(*pf)(T,T))
{
    //Checks to make sure that the object isnt the first node in the heap
    if(object->arrayLocation > 1)
    {
        //Calls the function pointer to check to see if the Min Heap or the Max Heap should bubble up
        if(-2 == (*pf)(heap[(object->arrayLocation)/2]->data, object->data))
        {
            //Sets parent to the parent of the HeapObject
            HeapObject<T>* parent = heap[(object->arrayLocation)/2];
            //Stores the location of each of the HeapObjects
            int parentLocation = parent->arrayLocation;
            int childLocation = object->arrayLocation;
            //Sets the new arrayLocation for each HeapObject
            object->arrayLocation = parentLocation;
            parent->arrayLocation = childLocation;
            //Swaps the objects in the array
            heap[parentLocation] = object;
            heap[childLocation] = parent;
            //Checks to make sure that the object isnt the first node in the heap
            if(object->arrayLocation > 1)
            {
                //Recursively calls bubble up
                bubbleUp(object, pf);
            }
        }
    }
}

/*Trickle down works in much the same way as bubble up but is used souly after deleting a HeapObject from the array. 
 It accepts the HeapObject that is going to be trickled down, the size of the heap, and the comparitor fuction that
 is sent in depending on whether of not it is the MinHeap or the MaxHeap. It has multiple determinants based on the 
 number of child objects the HeapObject has and the location of those child objects.*/
template <typename T>
void Heap<T>::trickleDown(HeapObject<T>* object, int size, int(*pf)(T,T))
{
    //Checks to see if the Object has a right child object
    if(heap[(object->arrayLocation)*2] != NULL)
    {
        //Checks to see if the Object has a right child object and left child object
        if(heap[(object->arrayLocation)*2] != NULL && heap[((object->arrayLocation *2) + 1)] != NULL)
        {
            /*Uses to the comparitors to either see if the right child is larger the the left in the case of a max heap
             or to see if the right child is smaller the the left in the case of a min heap it then checks to see if the
             right child is larger than the parent in the case of a max heap or the right child is smaller than the parent
             in the case of a min heap*/
            if(2 == (*pf)(heap[(object->arrayLocation)*2]->data, heap[((object->arrayLocation)*2) + 1]->data ) && 2 == (*pf)(heap[(object->arrayLocation)*2]->data, object->data))
            {
                //Stores the object and right child location
                int childLocation = (object->arrayLocation)*2;
                int objectLocation = object->arrayLocation;
                //Sets the child HeapObject equal to an object of HeapObject called child
                HeapObject<T>* child = heap[childLocation];
                //Sets objects arrayLocation equal to its new arrayLocation
                child->arrayLocation =objectLocation;
                object->arrayLocation =childLocation;
                //Swaps and stores the objects into their new respective location in the array
                heap[childLocation] = object;
                heap[objectLocation] = child;
                //Makes sure that the object will still have a child object
                if((object->arrayLocation)*2 < size)
                {
                    //Recursively calls tricle down again passing back in the object the size and the function pointer
                    trickleDown(object, size, pf);
                }
            }
            /*Uses to the comparitors to either see if the left child is larger the the right in the case of a max heap
             or to see if the left child is smaller the the right in the case of a min heap it then checks to see if the
             left child is larger than the parent in the case of a max heap or the left child is smaller than the parent
             in the case of a min heap*/
            else if(-2 == (*pf)(heap[(object->arrayLocation)*2]->data, heap[((object->arrayLocation)*2) + 1]->data) && 2 == (*pf)(heap[((object->arrayLocation)*2)+1]->data, object->data))
            {
                //Stores the object and left child location
                int childLocation = ((object->arrayLocation)*2)+1;
                int objectLocation = object->arrayLocation;
                //Sets the child HeapObject equal to an object of HeapObject called child
                HeapObject<T>* child = heap[childLocation];
                //Sets objects arrayLocation equal to its new arrayLocation
                child->arrayLocation =objectLocation;
                object->arrayLocation =childLocation;
                //Swaps and stores the objects into their new respective location in the array
                heap[childLocation] = object;
                heap[objectLocation] = child;
                //Makes sure that the object will still have a child object
                if((object->arrayLocation)*2 < size)
                {
                    //Recursively calls tricle down again passing back in the object the size and the function pointer
                    trickleDown(object, size, pf);
                }
            }
            /*Uses to the comparitors to either see if the right child is equal to the the left for both heaps it then checks to see if the
             right child is larger than the parent in the case of a max heap or the right child is smaller than the parent
             in the case of a min heap*/
            else if(0 == (*pf)(heap[(object->arrayLocation)*2]->data, heap[((object->arrayLocation)*2) + 1]->data) && 2 == (*pf)(heap[(object->arrayLocation)*2]->data, object->data))
            {
                //Stores the object and right child location
                int childLocation = (object->arrayLocation)*2;
                int objectLocation = object->arrayLocation;
                //Sets the child HeapObject equal to an object of HeapObject called child
                HeapObject<T>* child = heap[childLocation];
                //Sets objects arrayLocation equal to its new arrayLocation
                child->arrayLocation =objectLocation;
                object->arrayLocation =childLocation;
                //Swaps and stores the objects into their new respective location in the array
                heap[childLocation] = object;
                heap[objectLocation] = child;
                //Makes sure that the object will still have a child object
                if((object->arrayLocation)*2 < size)
                {
                    //Recursively calls tricle down again passing back in the object the size and the function pointer
                    trickleDown(object, size, pf);
                }
            }
        }
        else
        {
            /*If parent only has a right child it will check to see if the right child is larger than the parent in the case of a maxHeap
             or it will see if the right child is smaller than the parent in the case of a minHeap*/
            if(2 == (*pf)(heap[(object->arrayLocation)*2]->data, object->data))
            {
                //Stores the object and right child location
                int childLocation = (object->arrayLocation)*2;
                int objectLocation = object->arrayLocation;
                //Sets the child HeapObject equal to an object of HeapObject called child
                HeapObject<T>* child = heap[childLocation];
                //Sets objects arrayLocation equal to its new arrayLocation
                child->arrayLocation =objectLocation;
                object->arrayLocation =childLocation;
                //Swaps and stores the objects into their new respective location in the array
                heap[childLocation] = object;
                heap[objectLocation] = child;
                //Makes sure that the object will still have a child object
                if((object->arrayLocation)*2 < size)
                {
                    //Recursively calls tricle down again passing back in the object the size and the function pointer
                    trickleDown(object, size, pf);
                }
            }
        }
    }
    /*This is only used it their is only a left child. It works in the same way as the example above, but with a left child*/
    else
    {
        if(2 == (*pf)(heap[((object->arrayLocation)*2)+1]->data, object->data))
        {
            //Stores the object and left child location
            int childLocation = ((object->arrayLocation)*2)+1;
            int objectLocation = object->arrayLocation;
            //Sets the child HeapObject equal to an object of HeapObject called child
            HeapObject<T>* child = heap[childLocation];
            //Sets objects arrayLocation equal to its new arrayLocation
            child->arrayLocation =objectLocation;
            object->arrayLocation =childLocation;
            //Swaps and stores the objects into their new respective location in the array
            heap[childLocation] = object;
            heap[objectLocation] = child;
            //Makes sure that the object will still have a child object
            if((object->arrayLocation)*2 < size)
            {
                //Recursively calls tricle down again passing back in the object the size and the function pointer
                trickleDown(object, size, pf);
            }
        }
    }
}

/*This function deletes the max value, so it deletes the top value off the Max heap. It does this by deleting the top values off
 the MaxHeap and then using the pointer that I stored in the HeapObject that links object in the max heap with the object in the 
 min heap. It then determines whether to bubbleUp of trickle down*/
template <typename T>
T MinMaxHeap<T>::deleteMax()
{
    //Sets the min and max heap objects to objects so they are easier to call
    HeapObject<T>* maxHeapObject = high->heap[1];
    //Sets the data return value early just make sure that I dont accidently try to call for it after I delete the maxHeapObject
    T data = maxHeapObject->data;
    HeapObject<T>* minHeapObject = maxHeapObject->other;
    //Sets the min and max heap object replacements to objects so they are easier to call
    HeapObject<T>* maxReplacement = high->heap[sizes];
    HeapObject<T>* minReplacement = low->heap[sizes];
    //Sets the replacement objects old array spaces to NULL
    high->heap[sizes] = NULL;
    low->heap[sizes] = NULL;
    
    //maxHeap sort
    //Stores the MaxHeapObject in array space zero just in case I needed it later
    high->heap[0] = maxHeapObject;
    //Sets the replacements array location to 1
    maxReplacement->arrayLocation = 1;
    //Place the replacement node in the first position
    high->heap[1] = maxReplacement;
    //Trickle the node down to its right position
    high->trickleDown(maxReplacement, sizes, compareValuesMax);
    
    //minHeap sort
    //Sets the arrayLocation of the object that is getting deleted;
    int minArrayLocation = minHeapObject->arrayLocation;
    //Puts the object getting deleted in the 0 array slot
    low->heap[0] = minHeapObject;
    //Puts the replacement object in the array space of the deleted object
    low->heap[minArrayLocation] = minReplacement;
    //Sets the replacement nodes object location
    minReplacement->arrayLocation = minArrayLocation;
    //Checks to make 100 persent sure that my program will not seg fault
    if(low->heap[minArrayLocation/2] != NULL)
    {
        if(low->heap[minArrayLocation/2]->data >  minReplacement->data)
        {
            //the node will bubble up
            low->bubbleUp(minReplacement, compareValuesMin);
        }
    }
    else
    {
        //The node will trickle down
        low->trickleDown(minReplacement, sizes, compareValuesMin);
    }
    //Reduces the size by 1
    sizes--;
    //Sets the zero array spaces to NULL
    high->heap[0] = NULL;
    low->heap[0] = NULL;
    //Sets the size int value of the heaps
    high->size = sizes;
    low->size = sizes;
    //Deletes the old heap objects that where to be deleted
    delete maxHeapObject;
    delete minHeapObject;
    //Returns the value of the max value that was deleted
    return data;
}

template <typename T>
T MinMaxHeap<T>::deleteMin()
{
    //Sets the min and max heap objects to objects so they are easier to call
    HeapObject<T>* minHeapObject = low->heap[1];
    //Sets the data return value early just make sure that I dont accidently try to call for it after I delete the maxHeapObject
    T data = minHeapObject->data;
    HeapObject<T>* maxHeapObject = minHeapObject->other;
    //Sets the min and max heap object replacements to objects so they are easier to call
    HeapObject<T>* maxReplacement = high->heap[sizes];
    HeapObject<T>* minReplacement = low->heap[sizes];
    //Sets the replacement objects old array spaces to NULL
    high->heap[sizes] = NULL;
    low->heap[sizes] = NULL;
    
    //minHeap sort
    //Stores the MinHeapObject in array space zero just in case I needed it later
    low->heap[0] = minHeapObject;
    //Sets the replacements array location to 1
    minReplacement->arrayLocation = 1;
    //Place the replacement node in the first position
    low->heap[1] = minReplacement;
    //Trickle the node down to its right position
    low->trickleDown(minReplacement, sizes, compareValuesMin);
    
    //maxHeap sort
    //Sets the arrayLocation of the object that is getting deleted;
    int maxArrayLocation = maxHeapObject->arrayLocation;
    //Puts the object getting deleted in the 0 array slot
    high->heap[0] = maxHeapObject;
    //Puts the replacement object in the array space of the deleted object
    high->heap[maxArrayLocation] = maxReplacement;
    //Sets the replacement nodes objects location
    maxReplacement->arrayLocation = maxArrayLocation;
    if(high->heap[maxArrayLocation/2] != NULL)
    {
        if(high->heap[maxArrayLocation/2]->data <  maxReplacement->data)
        {
            //the node will bubble up
            high->bubbleUp(maxReplacement, compareValuesMax);
        }
    }
    else
    {
        //The node will trickle down
        high->trickleDown(maxReplacement, sizes, compareValuesMax);
    }
    //Reduces the size by 1
    sizes--;
    //Sets the zero array spaces to NULL
    high->heap[0] = NULL;
    low->heap[0] = NULL;
    //Sets the size int value of the heaps
    high->size = sizes;
    low->size = sizes;
    //Deletes the old heap objects that where to be deleted
    delete maxHeapObject;
    delete minHeapObject;
    //Returns the value of the min value that was deleted
    return data;
}
/*This is the insert function. It will insert the value in the last array slot in the heap and then will call bubble up
 fuction that will bubble up the inserted value if it needs to be bubbled up.*/
template <typename T>
void MinMaxHeap<T>::insert(const T& data)
{
    //Creates the new objects for the Min Heap and Max Heap
    HeapObject<T>* minObject = new HeapObject<T>(data);
    HeapObject<T>* maxObject = new HeapObject<T>(data);
    //Sets the pointers value of one object to the other object
    maxObject->other = minObject;
    minObject->other = maxObject;
    //If the size of the array is less than the capacity
    if(sizes < capacity)
    {
        //Increase the array size
        sizes++;
        //Sets the arrayLocation of the new objects to the size of the array, because
        //I am inserting them into the first open slot which is the size
        minObject->arrayLocation = sizes;
        maxObject->arrayLocation = sizes;
        //If you are inserting the first object
        if(sizes == 1)
        {
            high->heap[sizes] = maxObject;
            low->heap[sizes] = minObject;
        }
        else
        {
            //Inserts the objects into the heap
            high->heap[sizes] = maxObject;
            low->heap[sizes] = minObject;
            //Bubbles up the new objects
            high->bubbleUp(maxObject, compareValuesMax);
            low->bubbleUp(minObject, compareValuesMin);
        }
    }
    //If the user tries to insert more objects then they are allowed to then the program throws this error
    else{
        throw out_of_range("You are trying to insert more objects then the array has capacity to hold");
    }
    //Sets int data value of sizes in the heap objects
    high->size = sizes;
    low->size = sizes;
}

/*This dumps the heaps and prints out values that are in both of them*/
template <typename T>
void MinMaxHeap<T>::dump()
{
    cout<<"------------Min Heap------------"<<endl;
    cout<<"Size = "<<sizes<<", Capacity = "<<capacity<<endl;
    for(int i = 1; i <= sizes; i++)
    {
        HeapObject<T>* max = low->heap[i]->other;//used to much more cleanly call the other objects possition
        cout<<"Heap["<<i<<"] = ("<<low->heap[i]->data<<","<<max->arrayLocation<<")"<<endl;
    }
    cout<<endl;
    cout<<"------------Max Heap------------"<<endl;
    cout<<"Size = "<<sizes<<", Capacity = "<<capacity<<endl;
    for(int i = 1; i <= sizes; i++)
    {
        HeapObject<T>* min = high->heap[i]->other;//used to much more cleanly call the other objects possition
        cout<<"Heap["<<i<<"] = ("<<high->heap[i]->data<<","<<min->arrayLocation<<")"<<endl;
    }
}

//Return the size of the heaps
template <typename T>
int MinMaxHeap<T>::size()
{
    return sizes;
}

//Locates and stores the data value of the object in the indicated minHeap location and also returns the location
//of the object in the maxHeap
template <typename T>
void MinMaxHeap<T>::locateMin(int pos, T& data, int& index)
{
    HeapObject<T>* max = low->heap[pos]->other;
    data = low->heap[pos]->data;
    index = max->arrayLocation;
}

//Locates and stores the data value of the object in the indicated maxHeap location and also returns the location
//of the object in the minHeap
template <typename T>
void MinMaxHeap<T>::locateMax(int pos, T& data, int& index)
{
    HeapObject<T>* min = high->heap[pos]->other;
    data = high->heap[pos]->data;
    index = min->arrayLocation;
}

//Destructor for MinMaxHeap individual calls the destructors for the max and min heap
template <typename T>
MinMaxHeap<T>::~MinMaxHeap()
{
    delete high;
    delete low;
}

//Heap class destructor deletes all of the nodes in the HeapObject array and then deletes the array.
template <typename T>
Heap<T>::~Heap()
{
    for(int i = 1; i <= size; i++)
    {
        HeapObject<T>* temp =heap[i];//Deletest the objects in the array
        delete temp;
    }
    delete [] heap;//Deletes the array
}

/*Copy constructor hard copys the heaps from one MinMaxHeap object to another object*/
template <typename T>
MinMaxHeap<T>::MinMaxHeap(const MinMaxHeap<T>& other)
{
    //Creates new Heap objects and passes in the capacity
    high = new Heap<T>(other.capacity+1);
    low = new Heap<T>(other.capacity+1);
    //Sets the capacity
    capacity = other.capacity;
    //Sets the size
    sizes = other.sizes;
    //hard copys the objects from the other heap to the new heap
    for(int i = 1; i<=sizes; i++)
    {
        //Creates new objects
        HeapObject<T>* highObject = new HeapObject<T>(other.high->heap[i]->data);
        HeapObject<T>* lowObject = new HeapObject<T>(other.high->heap[i]->other->data);
        //Sets their arrayLocations
        highObject->arrayLocation = other.high->heap[i]->arrayLocation;
        lowObject->arrayLocation = other.high->heap[i]->other->arrayLocation;
        //Sets the pointer to the other object in the other array
        lowObject->other = highObject;
        highObject->other = lowObject;
        //Stores the objects in their respective arrays
        low->heap[lowObject->arrayLocation] = lowObject;
        high->heap[highObject->arrayLocation] = highObject;
    }
}

template <typename T>
const MinMaxHeap<T>& MinMaxHeap<T>::operator=(const MinMaxHeap<T>& rhs)
{
    //Deletes the old heaps
    delete high;
    high = NULL;
    delete low;
    low = NULL;
    //Creates new Heap objects and passes in the capacity
    high = new Heap<T>(rhs.capacity +1);
    low = new Heap<T>(rhs.capacity+1);
    //Sets the capacity
    capacity = rhs.capacity;
    //Sets the size
    sizes = rhs.sizes;
    //hard copys the objects from the other heap to the new heap
    for(int i = 1; i <= sizes; i++)
    {
        //Creates new objects
        HeapObject<T>* highObject = new HeapObject<T>(rhs.high->heap[i]->data);
        HeapObject<T>* lowObject = new HeapObject<T>(rhs.high->heap[i]->other->data);
        //Sets their arrayLocations
        highObject->arrayLocation = rhs.high->heap[i]->arrayLocation;
        lowObject->arrayLocation = rhs.high->heap[i]->other->arrayLocation;
        //Sets the pointer to the other object in the other array
        lowObject->other = highObject;
        highObject->other = lowObject;
        //Stores the objects in their respective arrays
        low->heap[lowObject->arrayLocation] = lowObject;
        high->heap[highObject->arrayLocation] = highObject;
    }
    //Returns a pointer to the current MinMaxHeap
    return *this;
}

/*This is used the comparitor that is passed into the max function pointers during bubble up and trickle down
 it accepts 2 data values of the generic type T and compares them depending on what they compare to they will
 pass back either 2, 0, or -2*/
template <typename T>
int compareValuesMax(T data1, T data2)
{
    if(data1 > data2)
    {
        return 2;
    }
    else if(data1 == data2)
    {
        return 0;
    }
    else if(data1 < data2)
    {
        return -2;
    }
    return -3;
}
/*This is used the comparitor that is passed into the max function pointers during bubble up and trickle down
 it accepts 2 data values of the generic type T and compares them depending on what they compare to they will
 pass back either 2, 0, or -2*/
template <typename T>
int compareValuesMin(T data1, T data2)
{
    if(data1 < data2)
    {
        return 2;
    }
    else if(data1 == data2)
    {
        return 0;
    }
    else if(data1 > data2)
    {
        return -2;
    }
    return -3;
}
#endif
