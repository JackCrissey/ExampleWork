// File: test1.cpp
//
// CMSC 341 Spring 2017 Project 4
//
// Check insert with MinMaxHeap instantiated with int.
//
// Should compile with: g++ test1.cpp
//

#include <iostream>
#include <string>
#include "MinMaxHeap.h"
using namespace std ;


int main() {
    MinMaxHeap<int> H(25);
    H.insert(7);
    H.insert(10);
    H.insert(14);
    H.insert(1);
    H.insert(5);
    H.insert(2);
    H.insert(25);
    H.insert(18);
    H.insert(15);
    H.insert(12);
    H.insert(20);
    H.insert(22) ;
    
    cout << "Initial MinMaxHeaps"<<endl;
    H.dump();
    
    H.insert(11);
    cout<<endl;
    cout<<endl;
    cout << "After inserting 11"<<endl;
    H.dump();
    
    int answer;
    answer = H.deleteMin();
    cout << "\n\nMin item " << answer << " removed from MinMax Heap"<<endl;
    cout<<"Should remove 1."<<endl;
    
    H.dump();
    
    answer = H.deleteMax();
    cout << "\n\nMax item " << answer << " removed from MinMax Heap"<<endl;
    cout<<"Should remove 25"<<endl;
    H.dump();
    
    //Now testing Strings
    MinMaxHeap<string> S(25);
    S.insert("ij") ;
    S.insert("xy") ;
    S.insert("ab") ;
    S.insert("km") ;
    S.insert("vw") ;
    S.insert("pq") ;
    S.insert("gh") ;
    S.insert("z_") ;
    S.insert("cd") ;
    S.insert("ef") ;
    S.insert("rs") ;
    S.insert("no") ;
    S.insert("tu") ;
    
    string stringAnswer;
    stringAnswer = S.deleteMin();
    cout << "\n\nMin item " << stringAnswer << " removed from MinMax Heap"<<endl;
    cout<<"Should remove ab."<<endl;
    
    S.dump();
    
    stringAnswer = S.deleteMax();
    cout << "\n\nMax item " << stringAnswer << " removed from MinMax Heap"<<endl;
    cout<<"Should remove z_"<<endl;
    S.dump();
    
    int minPos, maxPos;
    string minKey, maxKey;
    S.locateMin(1, minKey, maxPos);
    cout<<endl;
    cout<<"Return values of  locateMin: (1,"<<minKey<<","<<maxPos<<")"<<endl;
    
    S.locateMax(1, maxKey, maxPos);
    cout<<"Return values of  locateMax: (1,"<<minKey<<","<<maxPos<<")"<<endl;
    
    cout<<endl;
    cout<<endl;
    
    //Now testing a large number of values. Then delete a couple and get the Min and Max.
    MinMaxHeap<int> Big(100);
    //Adds 100 values to the heap
    for(int i = 1; i <= 100; i++)
    {
        Big.insert(i);
    }
    int intMinKey, intMaxKey;
    cout<<"Created a Heap of 100 elements";
    Big.locateMin(1, intMinKey, maxPos);
    cout << "\nMin item " << intMinKey<<endl;
    cout<<"Min should be 1."<<endl;
    
    Big.locateMax(1, intMaxKey, minPos);
    cout << "\nMax item " << intMaxKey<<endl;
    cout<<"Max should be 100"<<endl;
    //Deletes the top 10 and bottom 10 items off the heap
    for(int i= 1; i < 10; i++)
    {
        Big.deleteMax();
        Big.deleteMin();
    }
    cout<<endl;
    cout<<endl;
    cout<<"Deleted the top and bottom 10 items from the heap";
    Big.locateMin(1, intMinKey, maxPos);
    cout << "\nMin item " << intMinKey<<endl;
    cout<<"Min should be 10."<<endl;
    
    Big.locateMax(1, intMaxKey, minPos);
    cout << "\nMax item " << intMaxKey<<endl;
    cout<<"Max should be 91"<<endl;
    
    cout<<endl;
    cout<<endl;
    //For the copy constructor and the overloaded operator I am going to use H again
    cout<<"Initial MinMax Heap"<<endl;
    H.dump();
    cout<<endl;
    MinMaxHeap<int> *ptr = new MinMaxHeap<int>(H) ;
    cout << "Copied MinMax Heap"<<endl;
    ptr->dump();
    
    delete ptr;
    MinMaxHeap<int> H2(4) ;
    H2.insert(43) ;
    H2.insert(42) ;
    H2.insert(44) ;
    H2.insert(41) ;
    cout<<endl;
    cout<<endl;
    cout<<"Dumping H"<<endl;
    cout<<endl;
    H.dump();
    cout<<endl;
    cout<<endl;
    cout<<"Dumping H2"<<endl;
    cout<<endl;
    H2.dump();
    
    H2 = H;
    cout<<endl;
    cout<<endl;
    cout<<"Dumping H2 after calling the overloaded operator"<<endl;
    cout<<endl;
    H.dump();
}
