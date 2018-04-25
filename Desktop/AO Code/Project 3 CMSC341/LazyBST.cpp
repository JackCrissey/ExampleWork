//
//  LazyBST.cpp
//  Project 3 CMSC341
//
//  Created by Jack Crissey on 4/3/17.
//  Copyright © 2017 Jack Crissey. All rights reserved.
//

#include "LazyBST.h"
#include <iostream>
using namespace std;
//Creates a new Leaf and initializes all Leaf values
Leaf::Leaf(int values)
{
    value = values;
    parent = NULL;
    left = NULL;
    right = NULL;
    headNode = NULL;
    level = 0;
    left_count = 0;
    right_count = 0;
    isHeadNode = false;
    isLeftNode = false;
    isRightNode = false;
}
//Creates a new Leaf and initializes all Leaf values
Leaf::Leaf(int *temp)
{
    value = *temp;
    parent = NULL;
    left = NULL;
    right = NULL;
    headNode = NULL;
    level = 0;
    left_count = 0;
    right_count = 0;
    isHeadNode = false;
    isLeftNode = false;
    isRightNode = false;
}
//Constructor for LazyBST. Creates a dumby node and
LazyBST::LazyBST()
{
    dumby = new Leaf(0);
    levelCounter = 0;
    sorting = 0;
    startingLevel = 0;
    rebalLeaf = NULL;
    maxLevel=0;
    removeLevelLeft=0;
    removeLevelRight = 0;
    isDeleted = false;
    nodeAdded = false;
}
//Inserts a new node into the tree by calling a recursive insert function
//that finds the node on the tree that the new Leaf will be added too;
void LazyBST::insert(int key)
{
    //Creates a new node
    Leaf * node = new Leaf(key);
    //Checks if the dumby has a head node if not node is made the head node
    if(dumby->headNode == NULL)
    {
        dumby->headNode = node;
        node->isHeadNode = true;
    }
    else
    {
        //Sets temp to the root of the tree
        Leaf * temp = dumby->headNode;
        //Sets level counter to 0;
        levelCounter = 0;
        //Calls the binaryAdd function and send the node I want to add
        //and the root of the tree.
        binaryAdd(node, temp);
        nodeAdded = false;
        levelCounter++;//adds one to the level counter
        //If levelCounter is greater the temp->level set temp->level = to levelCounter
        if(temp->level < levelCounter)
        {
            temp->level = levelCounter;
        }
        
        //This part of the code checks if the tree needs to be rebalanced after the add
        //has been completed
        //This 2 lines convert the integer left_count and right_count values to float values
        //for rebalance checking
        float left = temp->left_count;
        float right = temp->right_count;
        //Checks to see if one side of the tree is twice as big as the other side of the tree
        if(left/2 > right || right/2 > left)
        {
            //Checks to make sure that temp's level is greater than 3 before it rebalances
            if(temp->level > 3)
            {
                //sets rebalLeaf to temp
                rebalLeaf = temp;
            }
        }
        //If rebalLeaf isnt null then the tree is rebalanced at rebalLeaf
        if(rebalLeaf != NULL)
        {
            rebalance(rebalLeaf);
            temp = dumby->headNode;
            rebalLeaf = NULL;
        }
    }
}
//The binary add function recurses through the tree and if it doesnt find the same value as the node
//I am trying to add it will go until it find it's slot on the Tree and then it will add itself to
//the tree.
void LazyBST::binaryAdd(Leaf *node, Leaf *temp)
{
    /*Checks to make sure that the node I am trying to insert isn't the same as a node
      already on the tree*/
    if(!find(node->value))
    {
        //If the node value is large then the current tree node that I am on
        if((node->value > temp->value) && nodeAdded == false)
        {
            //Adds on to the right count of the node on the tree.
            temp->right_count++;
            //If the node value is greater then the max level set max level equal to node level
            if(node->level > maxLevel)
            {
                maxLevel = node->level;
            }
            /*If the right child of the node on the tree is NULL it runs this to add the node*/
            if(temp->right == NULL)
            {
                //Sets node to the right child of the tree node
                temp->right = node;
                //Tells node that it is a right child
                node->isRightNode = true;
                //Tells the node that is parent is the node on the tree
                node->parent = temp;
                //Tells nodeAdded that a node was added
                nodeAdded = true;
            }
            /*If the right child of the node on the tree is not NULL it runs this recurse further through
             the function*/
            else
            {
                //Traverses to the right child of the node
                temp = temp->right;
                //recursively calls the add fuction again with the right child
                binaryAdd(node, temp);
                levelCounter++;//adds one to the level counter
                if(temp->level < levelCounter)
                {
                    //If levelCounter is greater the temp->level set temp->level = to levelCounter
                    temp->level = levelCounter;
                }
                /*This will set rebalLeaf equal to the node on the tree if that node is unbalance so
                  that it can be rebalanced after the node is added.*/
                if(temp->left_count/2 > temp->right_count || temp->right_count/2 > temp->left_count)
                {
                    if(temp->level > 3)
                    {
                        rebalLeaf = temp;
                    }
                }
            }
        }
        //If the node value is smaller then the current tree node that I am on
        if((node->value < temp->value) && nodeAdded == false)
        {
            //Adds on to the right count of the node on the tree.
            temp->left_count++;
            //If the node value is greater then the max level set max level equal to node level
            if(node->level > maxLevel)
            {
                maxLevel = node->level;
            }
            /*If the left child of the node on the tree is NULL it runs this to add the node*/
            if(temp->left == NULL)
            {
                //Sets node to the right child of the tree node
                temp->left = node;
                //Tells node that it is a left child
                node->isLeftNode = true;
                //Tells the node that is parent is the node on the tree
                node->parent = temp;
                //Tells nodeAdded that a node was added
                nodeAdded = true;
            }
            /*If the left child of the node on the tree is not NULL it runs this recurse further through
             the function*/
            else
            {
                //Traverses to the left child of the node
                temp = temp->left;
                //recursively calls the add fuction again with left child
                binaryAdd(node, temp);
                levelCounter++;//adds one to the level counter
                if(temp->level < levelCounter)
                {
                    //If levelCounter is greater the temp->level set temp->level = to levelCounter
                    temp->level = levelCounter;
                }
                /*This will set rebalLeaf equal to the node on the tree if that node is unbalance so
                 that it can be rebalanced after the node is added.*/
                if(temp->left_count/2 > temp->right_count || temp->right_count/2 > temp->left_count)
                {
                    if(temp->level > 3)
                    {
                        rebalLeaf = temp;
                    }
                }
            }
        }
    }
    else
    {
        //returns if the value is already on the tree to prevent it from adding
        return;
    }
}
/*This fuction removes the indicated node from the tree by calling a recursive remove fuction. If the node is removed
 then return true if the node wasnt found return false*/
bool LazyBST::remove(int key)
{
    //Sets temp equal to the headNode
    Leaf * temp = dumby->headNode;
    maxLevel = 0;
    //Calls the remove recursive fuction to find and remove the indicated node
    removeRecur(temp, key);
    //Initilazes the removeLevels
    removeLevelRight = 0;
    removeLevelLeft = 0;
    //If is deleted is true then remove will return true else it will return false
    if(isDeleted)
    {
        isDeleted = false;
        return true;
    }
    else
    {
        return false;
    }
}
/*This class searches the tree recursively until it either finds the node that it wants to delete and deletes it
 or if it doesnt find it then nothing will happen*/
void LazyBST::removeRecur(Leaf *temp, int node)
{
    //If the node is greater than node on the tree
    if(node > temp->value)
    {
        if(temp->right != NULL)
        {
            //Recersively calls the remove fuction with the tree nodes right child
            removeRecur(temp->right , node);
            removeLevelLeft++;//adds to removeLevelLeft
            relevel(temp);//relevels the tree
            //if the node was deleted then the nodes above it reduce their right count by one
            if(isDeleted == true)
            {
                temp->right_count--;
            }
            //This 2 lines convert the integer left_count and right_count values to float values
            //for rebalance checking
            float left = temp->left_count;
            float right = temp->right_count;
            //Checks to see if one side of the tree is twice as big as the other side of the tree
            if(left/2 > right || right/2 > left)
            {
                //Checks to make sure that temp's level is greater than 3 before it rebalances
                if(temp->level > 3)
                {
                    //sets rebalLeaf to temp
                    rebalLeaf = temp;
                }
            }
            //If rebalLeaf isnt null then the tree is rebalanced at rebalLeaf
            if(rebalLeaf != NULL)
            {
                rebalance(rebalLeaf);
                temp = dumby->headNode;
                rebalLeaf = NULL;
            }
        }
    }
    //If the node is less than node on the tree
    if(node < temp->value)
    {
        if(temp->left != NULL)
        {
            //Recersively calls the remove fuction with the tree nodes left child
            removeRecur(temp->left , node);
            removeLevelLeft++;//adds to removeLevelLeft
            relevel(temp);//relevels the tree
            //if the node was deleted then the nodes above it reduce their left count by one
            if(isDeleted == true)
            {
                temp->left_count--;
            }
            //This 2 lines convert the integer left_count and right_count values to float values
            //for rebalance checking
            float left = temp->left_count;
            float right = temp->right_count;
            //Checks to see if one side of the tree is twice as big as the other side of the tree
            if(left/2 > right || right/2 > left)
            {
                //Checks to make sure that temp's level is greater than 3 before it rebalances
                if(temp->level > 3)
                {
                    //sets rebalLeaf to temp
                    rebalLeaf = temp;
                }
            }
            //If rebalLeaf isnt null then the tree is rebalanced at rebalLeaf
            if(rebalLeaf != NULL)
            {
                rebalance(rebalLeaf);
                temp = dumby->headNode;
                rebalLeaf = NULL;
            }
        }
    }
    //If the node is equal to the node on the tree
    if(node == temp->value)
    {
        //Checks to see if the parent is the root of the tree
        if(temp->parent == NULL)
        {
            //Checks to see if the right and left children both exist
            if(temp->right != NULL && temp->left != NULL)
            {
                    //sets the headNode to the right value on the sub tree
                    dumby->headNode = temp->right;
                    //tells temp right that it is the head node
                    temp->right->isHeadNode = true;
                //rep to the new root
                    Leaf * rep = temp->right;
                //finds the left most node on the right subtree
                    while(rep->left != NULL)
                    {
                        rep = rep->left;
                    }
                //adds the left subtree to the right subtree
                    rep->left = temp->left;
                //set the left subtree root's parent equal to the left most node on the right subtree
                    temp->left->parent = rep;
                //sets temp rights left count equal to its current left count + the old roots left count
                    temp->right->left_count = temp->right->left_count + temp->left_count;
                //deletes the old root
                    delete temp;
                //sets is deleted to true
                    isDeleted = true;
                //all these next lines do it relevel all the height values of the tree
                    temp = dumby->headNode;
                    temp->parent = NULL;
                //checks if the left child level is less then the parents level
                    if(temp->left->level > temp->level)
                    {
                        temp->level = temp->left->level+1;
                    }
                    if(rep->left->level > rep->level)
                    {
                        rep->level = rep->left->level+1;
                        while(rep->parent != NULL)//loops up to the root of the tree and resets all the values on the way up
                        {
                            rep->left_count = rep->left->left_count+rep->left->right_count+1;
                            rep = rep->parent;
                            relevel(rep);
                        }
                    }
            }
            //If the root of the tree only has a right child
            else if(temp->right != NULL && temp->left == NULL)
            {
                //sets the headNode to the roots right value on the sub tree
                dumby->headNode = temp->right;
                //sets the right nodes parent value to null
                temp->right->parent = NULL;
                //tells the right node that it is now the head node
                temp->right->isHeadNode = true;
                //relevels the tree
                relevel(temp->right);
                //deletes the old root
                delete temp;
                isDeleted = true;
            }
            //If the root of the tree only has a left child
            else if(temp->right == NULL && temp->left != NULL)
            {
                //sets the headNode to the roots left value on the sub tree
                dumby->headNode = temp->left;
                //sets the left nodes parent value to null
                temp->left->parent = NULL;
                //tells the left node that it is now the head node
                temp->left->isHeadNode = true;
                //relevels the tree
                relevel(temp->left);
                //deletes the old root
                delete temp;
                isDeleted = true;
            }
            //If the root of the tree doesnt have any children
            else if(temp->right == NULL && temp->left == NULL)
            {
                //sets dumby's headNode value to NULL
                dumby->headNode = NULL;
                //sets the roots value to null;
                temp = NULL;
                //dumby->headNode = NULL;
                //deletes the old root
                delete temp;
                isDeleted = true;
            }
            if(dumby->headNode != NULL)
            {
                //This 2 lines convert the integer left_count and right_count values to float values
                //for rebalance checking
                float left = temp->left_count;
                float right = temp->right_count;
                //Checks to see if one side of the tree is twice as big as the other side of the tree
                if(left/2 > right || right/2 > left)
                {
                    //Checks to make sure that temp's level is greater than 3 before it rebalances
                    if(temp->level > 3)
                    {
                        //sets rebalLeaf to temp
                        rebalLeaf = temp;
                    }
                }
                //If rebalLeaf isnt null then the tree is rebalanced at rebalLeaf
                if(rebalLeaf != NULL)
                {
                    rebalance(rebalLeaf);
                    temp = dumby->headNode;
                    rebalLeaf = NULL;
                }
            }
        }
        //If the removed value has a parent
        else if(temp->parent != NULL)
        {
            //If the node being deleted has a greater value then it's parent
            if(temp->value > temp->parent->value)
            {
                //Checks to see if the right and left children both exist
                if(temp->right != NULL && temp->left != NULL)
                {
                    //sets the right node of the node being deleted to the deleted nodes parent
                    temp->parent->right = temp->right;
                    //sets the deleted nodes right child equal to it's parent
                    temp->right->parent = temp->parent;
                    //This set of lines are used to recurse to the left most node through the right subtree of the root node
                    Leaf * rep = temp->right;
                    while(rep->left != NULL)
                    {
                        rep = rep->left;
                    }
                    //These lines link the left most node on the right subtree to the root of the left subtree
                    rep->left = temp->left;
                    temp->left->parent = rep;
                    //deletes the node that needs to be removed
                    delete temp;
                    isDeleted = true;
                }
                //If the node being deleted only has a right child
                if(temp->right != NULL && temp->left == NULL)
                {
                    //sets parent of the node being deleted to the right child of the node being deleted
                    temp->parent->right = temp->right;
                    temp->right->parent = temp->parent;
                    //deletes the node
                    delete temp;
                    isDeleted = true;
                }
                //If the node being deleted only has a left child
                if(temp->right == NULL && temp->left != NULL)
                {
                    //sets parent of the node being deleted to the left child of the node being deleted
                    temp->parent->right = temp->left;
                    temp->left->parent = temp->parent;
                    //deletes the node
                    delete temp;
                    isDeleted = true;
                }
                //If the nod ebeing deleted doesnt have any children.
                if(temp->right == NULL && temp->left == NULL)
                {
                    //Sets the parent child pointer to NULL
                    temp->parent->right = NULL;
                    //deletes the node
                    delete temp;
                    isDeleted = true;
                }
            }
            //If the node being deleted has a lesser value then it's parent
            else
            {
                //Checks to see if the right and left children both exist
                if(temp->right != NULL && temp->left != NULL)
                {
                    //sets the right node of the node being deleted to the deleted nodes parent
                    temp->parent->left = temp->right;
                    //sets the deleted nodes right child equal to it's parent
                    temp->right->parent = temp->parent;
                    //This set of lines are used to recurse to the left most node through the right subtree of the root node
                    Leaf * rep = temp->right;
                    while(rep->left != NULL)
                    {
                        rep = rep->left;
                    }
                    //These lines link the left most node on the right subtree to the root of the left subtree
                    temp->left->parent = rep;
                    rep->left = temp->left;
                    //deletes the node
                    delete temp;
                    isDeleted = true;
                }
                //If the node being deleted only has a right child
                if(temp->right != NULL && temp->left == NULL)
                {
                    //sets parent of the node being deleted to the right child of the node being deleted
                    temp->parent->left = temp->right;
                    temp->right->parent = temp->parent;
                    //deletes the node
                    delete temp;
                    isDeleted = true;
                }
                if(temp->right == NULL && temp->left != NULL)
                {
                    //sets parent of the node being deleted to the left child of the node being deleted
                    temp->parent->left = temp->left;
                    temp->left->parent = temp->parent;
                    //deletes the node
                    delete temp;
                    isDeleted = true;
                }
                //If the nod ebeing deleted doesnt have any children.
                if(temp->right == NULL && temp->left == NULL)
                {
                    //Sets the parent child pointer to NULL
                    temp->parent->left = NULL;
                    //deletes the node
                    delete temp;
                    isDeleted = true;
                }
            }
        }
    }
}
/*This is the rebalance fuction, it takes in the root node of the tree of the the root node of an unbalanced subtree
  and rebalances it if one subtree is twice the size of the other subtree after the rebalance the two subtree should
  not be larger than twice the size of the other subtree*/
void LazyBST::rebalance(Leaf *temp)
{
    //If parent isnt null then the start level is set at the level of the roots parent
    if(temp->parent != NULL)
    {
        startingLevel = temp->parent->level;
    }
    else
    {
        startingLevel = (-1);
    }
    //Sets sorted equal to the number of subnodes of the root plus the root node
    sorted = new int[temp->right_count+temp->left_count+1];
    //Send it into the recursive fuction that sorts the tree out into an array
    inorderArray(temp);
    //Initializes values
    rightCount = 0;//used to count right nodes
    leftCount = 0;//used to cound left nodes
    maxLevel = 0;//level counter
    maxLevel = 0;
    //Checks to see if temp is the root node
    if(temp->isHeadNode)
    {
        //sets isHead node to false
        temp->isHeadNode = false;
        //deletes the old subtree
        destrRecur(dumby->headNode);
        //adds the new balanced subtree to the headnode
        dumby->headNode = inorderSort((sorting-1)/2, 0, sorting-1, startingLevel, sorting, -5, -5);
        //tells the head node that it is the headnode
        dumby->headNode->isHeadNode = true;
    }
    //Checks to if parent doesnt equal null
    else if(temp->parent != NULL)
    {
        //the roots value is greater than it's parents
        if(temp->value > temp->parent->value)
        {
            //reset the relevel value
            bool relevel = false;
            // check if left is null before doing this
            if(temp->parent->left != NULL)
            {
                if(temp->level > temp->parent->left->level)
                {
                    relevel = true;
                }
            }
            //set temp to the roots parent
            temp = temp->parent;
            //delete the old subtree
            destrRecur( temp->right);
            //add the new subtree to the right child of the roots parent
            temp->right = inorderSort((sorting-1)/2, 0, sorting -1, startingLevel, sorting, -5, -5);
            //tell the root that it is a right child
            temp->right->isRightNode = true;
            //set temp back to the root
            temp = temp->right;
            //these following lines are only used if the tree needs to be releveled
            Leaf * review = temp;
            if(relevel)
            {
                while(review->parent != NULL)
                {
                    if(review->parent->right->level < review->parent->left->level)
                    {
                        review->parent->level = review->parent->left->level+1;
                    }
                    if(review->parent->right->level > review->parent->left->level)
                    {
                        review->parent->level = review->parent->right->level+1;
                    }
                    review = review->parent;
                }
            }
        }
        //the roots value is less than it's parents
        else if(temp->value < temp->parent->value)
        {
            //reset the relevel value
            bool relevel = false;
            // check if left is null before doing this
            if(temp->parent->right != NULL)
            {
                if(temp->level > temp->parent->right->level)
                {
                    relevel = true;
                }
            }
            //set temp to the roots parent
            temp = temp->parent;
            //delete the old subtree
            destrRecur(temp->left);
            //add the new subtree to the left child of the roots parent
            temp->left = inorderSort((sorting-1)/2, 0, sorting-1, startingLevel, sorting, -5, -5);
            //tell the root that it is a right child
            temp->left->isLeftNode = true;
             //set temp back to the root
            temp = temp->left;
             //these following lines are only used if the tree needs to be releveled
            Leaf * review = temp;
            if(relevel)
            {
                while(review->parent != NULL)
                {
                    if(review->parent->right->level < review->parent->left->level)
                    {
                        review->parent->level = review->parent->left->level+1;
                    }
                    if(review->parent->right->level > review->parent->left->level)
                    {
                        review->parent->level = review->parent->right->level+1;
                    }
                    review = review->parent;
                }
            }
        }
    }
    //resets sorting to 0
    sorting = 0;
    //resets startLevel to 0;
    startingLevel = 0;
    //deallocates sorted
    delete sorted;
}
/*This fuction takes the root of the tree that needs to be rebalanced puts the value of each node of the
 subtree in order into an array*/
void LazyBST::inorderArray(Leaf *temp)
{
    //If the node's left child is not NULL
    if(temp->left != NULL)
    {
        //Recurse the fuction using the left child
        inorderArray(temp->left);
    }
    //Adds the nodes value to the array
    sorted[sorting]=temp->value;
    //Adds 1 to sorted
    sorting++;
    //If the node's right child is not NULL
    if(temp->right !=NULL)
    {
        //Recurse the fuction using the right child
        inorderArray(temp->right);
    }
}
/*This is a recursive fuction that creates a new subtree by recursively doing in essence a binary sort, so it starts in the
 middle of the array and recuses by reducing the array bounds*/
Leaf * LazyBST::inorderSort(int slot, int leftBound, int rightBound, int level, int sizes, int past1, int past2)
{
    //sets the array size by subracting 1 from the total amount of nodes in the subtree
    int size = sizes - 1;
    //creates a new leaf for the array value
    Leaf * newLeaf = new Leaf(sorted[slot]);
    //Sets the left gap
    int leftGap = slot - leftBound;
    //Sets the right gap
    int rightGap = rightBound - slot;
    //Sets the left and right count AKA the number of subnodes
    newLeaf->left_count = leftGap;
    newLeaf->right_count = rightGap;
    //Both of these if statements are used to make sure that the left and right count are correct
    if(past1 == leftBound || past2 == leftBound)
    {
        newLeaf->left_count--;
    }
    if(past1 == rightBound || past2 == rightBound)
    {
        newLeaf->right_count--;
    }
    //resets temps value
    int temp = 0;
    //Used for the left subnodes if their are no specific requirments that need to be meet
    if((leftGap > 3 || leftGap == 2))
    {
        //checks to see it it is adding the left most nodes in the array and if so it
        //adds them
        if(leftGap == 2 && leftBound == 0)
        {
            //creates the new nodes
            Leaf * one = new Leaf(sorted[0]);
            Leaf * two = new Leaf(sorted[1]);
            //Adds them to the left of newLeaf and sets the highs and number of subnodes
            newLeaf->left = two;
            if (newLeaf->level < 2)
            {
                newLeaf->level = 2;
            }
            if(2 > maxLevel)
            {
                maxLevel = 2;
            }
            two->left_count = 1;
            two->level = 1;
            two->left = one;
            two->parent = newLeaf;
            one->parent = two;
            one->level = 0;
        }
        //If not then it recurses to the half way point between sorted and the leftBound
        else
        {
            //sets the value of the slot value
            temp = ((slot - leftBound)/2)+leftBound;
            // recursively keeps going throught the aray
            newLeaf->left=inorderSort(temp, leftBound, slot,  level, sizes, slot, past1);
            //Sets the values onto the tree
            newLeaf->left->parent = newLeaf;
            maxLevel++;
            if(newLeaf->level < maxLevel)
            {
                newLeaf->level = maxLevel;
            }
            newLeaf->left->parent = newLeaf;
            newLeaf->left->isLeftNode = true;
        }
    }
    //Used for the right subnodes if their are no specific requirments that need to be meet
    if((rightGap > 3 || rightGap == 2))
    {
        //checks to see it it is adding the right most nodes in the array and if so it
        //adds them
        if(rightGap == 2 && rightBound == size)
        {
            //creates the new nodes
            Leaf * one = new Leaf(sorted[size-1]);
            Leaf * two = new Leaf(sorted[size]);
            //Adds them to the right of newLeaf and sets the highs and number of subnodes
            newLeaf->right = one;
            if (newLeaf->level < 2)
            {
                newLeaf->level = 2;
            }
            if(2 > maxLevel)
            {
                maxLevel = 2;
            }
            one->right = two;
            one->right_count = 1;
            one->level = 1;
            one->parent = newLeaf;
            two->parent = one;
            two->level = 0;
        }
        //If not then it recurses to the half way point between the Rightbound and slot
        else
        {
            //sets the value of the slot value
            temp = ((rightBound-slot)/2)+slot;
            maxLevel = 0;
            // recursively keeps going throught the aray
            newLeaf->right=inorderSort(temp, slot, rightBound, level, sizes, slot, past1);
            //Sets the values onto the tree
            newLeaf->right->parent=newLeaf;
            maxLevel++;
            if(newLeaf->level < maxLevel)
            {
                newLeaf->level = maxLevel;
            }
            newLeaf->right->parent = newLeaf;
            newLeaf->right->isRightNode = true;
        }
    }
    //If the recursion encounters the 4 left most nodes in the array
    if(leftBound == 0 && slot == 3)
    {
        //Creates new leaves for the left most values on the array
        Leaf * zero = new Leaf(sorted[0]);
        Leaf * one = new Leaf(sorted[1]);
        Leaf * two = new Leaf(sorted[2]);
        /*The next couple of lines just create a small subtree with leaf one as the 
         root and zero is the left child and two is the right child and then it adds
         one to the left child*/
        newLeaf->left = one;
        one->isLeftNode = true;
        newLeaf->left_count = 3;
        one->level = 1;
        one->left_count = 1;
        one->right_count = 1;
        one->left = zero;
        zero->isLeftNode = true;
        zero->level = 0;
        one->right = two;
        two->isRightNode = true;
        two->level = 0;
        one->parent = newLeaf;
        zero->parent = one;
        two->parent = one;
        if(2 > maxLevel)
        {
            maxLevel = 2;
        }
        if(newLeaf->level < 2)
        {
            newLeaf->level = 2;
        }
    }
    //If the recursion encounters the 4 right most nodes in the array
    if(slot == (size - 3) && rightBound == size)
    {
        //Creates new leaves for the right most values on the array
        Leaf * zero = new Leaf(sorted[size-2]);
        Leaf * one = new Leaf(sorted[size-1]);
        Leaf * two = new Leaf(sorted[size]);
        /*The next couple of lines just create a small subtree with leaf one as the
         root and zero is the left child and two is the right child and then it adds
         one to the right child*/
        newLeaf->right= one;
        newLeaf->right_count = 3;
        one->isRightNode = true;
        one->level = 1;
        one->left_count = 1;
        one->right_count = 1;
        one->left = zero;
        zero->isLeftNode = true;
        zero->level = 0;
        one->right = two;
        two->isRightNode = true;
        two->level = 0;
        one->parent = newLeaf;
        zero->parent = one;
        two->parent = one;
        if(2 > maxLevel)
        {
            maxLevel = 2;
        }
        if(newLeaf->level < 2)
        {
            newLeaf->level = 2;
        }
    }
    //If the left recursion ends up with the left and rightbound nodes being sperated by 2 nodes, but it is not on the
    //far left or right of the array
    if(leftGap == 3 && !(leftBound == 0 && slot == 3))
    {
        //create two new leaves for the middle nodes
        Leaf * one = new Leaf(sorted[leftBound+1]);
        Leaf * two = new Leaf(sorted[leftBound+2]);
        //It then adds two to the left child of the new node and one to the left child of two
        newLeaf->left = two;
        newLeaf->left_count = 2;
        two->level = 1;
        two->left = one;
        two->left_count = 1;
        one->level = 0;
        two->parent = newLeaf;
        one->parent = two;
        if(2 > maxLevel)
        {
            maxLevel = 2;
        }
        if(newLeaf->level < 2)
        {
            newLeaf->level = 2;
        }
    }
    //If the right recursion ends up with the left and rightbound nodes being sperated by 2 nodes, but it is not on the
    //far left or right of the array
    if(rightGap == 3 && !(slot == (size - 3) && rightBound == size))
    {
        //create two new leaves for the middle nodes
        Leaf * one = new Leaf(sorted[slot+1]);
        Leaf * two = new Leaf(sorted[slot+2]);
        //It then adds one to the left child of the new node and two to the left child of one
        newLeaf->right = one;
        newLeaf->right_count = 2;
        one->level = 1;
        one->right = two;
        one->right_count = 1;
        two->level = 0;
        one->parent = newLeaf;
        two->parent = one;
        if(2 > maxLevel)
        {
            maxLevel = 2;
        }
        if(newLeaf->level < 2)
        {
            newLeaf->level = 2;
        }
    }
    //returns the new leaf so it can be added onto the subtree
    return newLeaf;
}
/*As long as their is a head node the in order fuction calls the inorderSearch recursive fuction
 that outputs the entire tree*/
void LazyBST::inorder()
{
    Leaf *temp = dumby->headNode;
    if(temp != NULL)
    {
        inorderSearch(temp);
    }
}
/*This is the recursive fuction that works a lot like inorderArray, but instead of sticking everything
 in an array I am couting it with the VALUE:LEVEL:# OF SUBNODES*/
void LazyBST::inorderSearch(Leaf *temp)
{
    cout<<"(";
    if(temp->left != NULL)
    {
        inorderSearch(temp->left);
    }
    int subSize = temp->right_count + temp->left_count;
    cout<<temp->value<<":"<<temp->level<<":"<<subSize;
    if(temp->right !=NULL)
    {
        inorderSearch(temp->right);
    }
    cout<<")";
}
//This fuctions only purpous it to call findRecur and then return whether findRecur found the node that
//it was looking for
bool LazyBST::find(int key)
{
    return findRecur(key, dumby->headNode);
}
//This does a recursive binary search and will either stop recursing if it has found the value and return true
//if it hasn't and it reaches a NULL child it will return false
bool LazyBST::findRecur(int key, Leaf *temp)
{
    //if the key is greater the temps value
    if(key>temp->value)
    {
        if(temp->right != NULL)
        {
            return findRecur(key, temp->right);
        }
        else
        {
            return false;
        }
    }
    //if the key is less the temps value
    else if(key<temp->value)
    {
        if(temp->left != NULL)
        {
            return findRecur(key, temp->left);
        }
        else
        {
            return false;
        }
    }
    else if(key == temp->value)
    {
        return true;
    }
    return false;
}
//This value locates a node on the tree based off of letter values that have been sent into
//the locate fuction L to go to the left child R to go to the right child if thier is a node
//in the location given then it will return true. Otherwise it will return false
bool LazyBST::locate(const char *position, int& key)
{
    const char *i = position;
    int counter = 0;
    Leaf * temp = dumby->headNode;
    while(i[counter] != '\0')
    {
        if(i[counter] == 'L')
        {
            if(temp->left != NULL)
            {
                temp = temp->left;
            }
            else
            {
                return false;
            }
        }
        else if(i[counter] == 'R')
        {
            if(temp->right != NULL)
            {
                temp = temp->right;
            }
            else
            {
                return false;
            }
        }
        counter++;
    }
    key = temp->value;
    return true;
}
/*This is the copy constructor it creates a new dumby and then adds calls copyRecur
 to copy the tree with new nodes*/
LazyBST::LazyBST(const LazyBST& other)
{
    dumby = new Leaf(0);
    dumby->headNode = copyRecur(other.dumby->headNode);
}
/*This is the core recusive fuction in the copy constructor and it recusively adds brand new newly
 allocated nodes to the subtree. It works very similarly to a lot of my other binary search functions*/
Leaf * LazyBST::copyRecur(Leaf *temp)
{
    Leaf * leftHolder = NULL;
    if(temp->left != NULL)
    {
        leftHolder = copyRecur(temp->left);
    }
    //creates a new node and sets the values
    Leaf * newNode = new Leaf(temp->value);
    newNode->left_count = temp->left_count;
    newNode->right_count = temp->right_count;
    newNode->level = temp->level;
    newNode->value = temp->value;
    newNode->isLeftNode = temp->isLeftNode;
    newNode->isRightNode = temp->isRightNode;
    newNode->isHeadNode = temp->isHeadNode;
    if(leftHolder != NULL)
    {
        newNode->left = leftHolder;
        leftHolder->parent = newNode;
    }
    if(temp->right != NULL)
    {
        newNode->right = copyRecur(temp->right);
        newNode->right->parent=newNode;
    }
    return newNode;
}
/*This is the destructor that is used to deallocate the nodes in the tree for each lazyBST function*/
LazyBST::~LazyBST()
{
    //Checks to make sure it has a headnode
    if(dumby->headNode)
    {
        destrRecur(dumby->headNode);
        delete dumby;
    }
}
/* This is just a recursive function that goes to the lowest node and deletes the entire tree from
 the bottom up*/
void LazyBST::destrRecur(Leaf *temp)
{
    //goes all the way to the bottom left node
    if(temp->left != NULL)
    {
       destrRecur(temp->left);
    }
    //goes all the way to the bottom right node
    if(temp->right != NULL)
    {
        destrRecur(temp->right);
    }
    //the deletes the value
    delete temp;
}
/*This is the overloaded operator it first deletes all of the pointer in LazyBST and then deep copies
 another tree to that operator*/
const LazyBST& LazyBST::operator=(const LazyBST& rhs)
{
    delete this->dumby;
    dumby = new Leaf(0);
    dumby->headNode = copyRecur(rhs.dumby->headNode);
    return *this;
}
/*This fuctions sole perpose it to be called after resorts and removes to relevel the values
 so that the each node hase the correct level*/
void LazyBST::relevel(Leaf *temp)
{
    if(temp->right != NULL && temp->left != NULL)
    {
        if(temp->right->level > temp->left->level)
        {
            temp->level = temp->right->level +1;
        }
        else if(temp->right->level < temp->left->level)
        {
            temp->level = temp->left->level +1;
        }
    }
    else if(temp->right == NULL && temp->left != NULL)
    {
        temp->level = temp->left->level+1;
    }
    else if(temp->left == NULL && temp->right != NULL)
    {
        temp->level = temp->right->level+1;
    }
}


