//
//  LazyBST.h
//  Project 3 CMSC341
//
//  Created by Jack Crissey on 4/3/17.
//  Copyright © 2017 Jack Crissey. All rights reserved.
//

#ifndef LazyBST_h
#define LazyBST_h
#include <iostream>
class Leaf {
public:
    Leaf(int values);
    Leaf(int *temp);
    int left_count;
    int right_count;
    int level;
    int value;
    bool isLeftNode;
    bool isRightNode;
    bool isHeadNode;
    Leaf * parent;
    Leaf * left;
    Leaf * right;
    Leaf * headNode;
};
class LazyBST {
public:
    LazyBST();
    void insert(int key);
    bool remove(int key);
    bool find(int key);
    void inorder();
    bool locate(const char *position, int& key);
    LazyBST(const LazyBST& other);
    ~LazyBST();
    const LazyBST& operator=(const LazyBST& rhs);
private:
    void rebalance(Leaf *temp);
    Leaf* rebalanceHelper(Leaf *parent, int *sortedList, int length);
    void removeRecur(Leaf *temp, int node);
    void binaryAdd(Leaf *node, Leaf *temp);
    void inorderArray(Leaf *temp);
    bool findRecur(int key, Leaf *temp);
    void relevel(Leaf *temp);
    Leaf * copyRecur(Leaf *temp);
    void destrRecur(Leaf *temp);
    Leaf * inorderSort(int slot, int leftBound, int rightBound, int level, int size, int past1, int past2);
    void inorderSearch(Leaf *temp);
    int levelCounter;
    Leaf * dumby;
    int *sorted;
    Leaf **sortedLeafs;
    int sorting;
    int startingLevel;
    Leaf * rebalLeaf;
    int maxLevel;
    int leftCount;
    int rightCount;
    int removeLevelLeft;
    int removeLevelRight;
    bool isDeleted;
    bool nodeAdded;
};
#endif /* LazyBST_h */
