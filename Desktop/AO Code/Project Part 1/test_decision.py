#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Apr  5 18:11:20 2018

@author: jcrissey4
"""
import math
"""Node class is used to create and store nodes on the decision tree"""
class nodes:
    childArray = []
    #Stores value of leaf
    def __init__ (self, value):
        self.value = value
    #Child List for multiple children
    def setChildren(self, childArray):
        self.childArray = childArray
    #Tells the program if the node is a leaf or not
    def setIsLeaf(self, isLeaf):
        self.isLeaf = isLeaf
    #The value of the leaf if the node is a leaf    
    def setLeafValue(self, leafValue):
        self.leafValue = leafValue

#Used to caluculate the entropy of a column in the training set
def entropy(column, array):
    #Parallel Array for the value and the number of times it appears
    valueArray = []
    counterArray = []
    totalCount = len(array)
    #Loop calculated the number of times the value appears
    for t in array:
        #If value isnt in the array yet stores it and creates a new value in the counter array
        if valueArray.count(t[column]) == 0:
            valueArray.append(t[column])
            counterArray.append(1)
        #Adds one to the index associated with the value array slot
        else:
            index = valueArray.index(t[column])
            counterArray[index] = counterArray[index] +1
    thisEntropy = 0
    #Actual Entrophy calculation
    for t in counterArray:
        thisEntropy = thisEntropy + (t/totalCount)*math.log2(t/totalCount)
    thisEntropy = -thisEntropy
    return thisEntropy

#Used to Calculate the information Gained for a column in the test set
def infoGain(column, array):
    totalLen = len(array)
    setLen = len(array[0])
    #Creates parallel arrays that store the value and the labels assocated with those values
    infoValueArray = []
    labelArray = []
    #Fills the arrays with the values and the labels associated with them
    for t in array:
        if infoValueArray.count(t[column]) == 0:
            infoValueArray.append(t[column])
            setArray = []
            setArray.append(t[setLen-1])
            labelArray.append(setArray)
        else:
            labelArray[infoValueArray.index(t[column])].append(t[setLen-1])
    #The actual information gained is calculated first gets entrophy of the Column then 
    #subtracts it by the weighted sum of the entropy associated with the values
    infoGained = entropy(column, array)
    tempMinus = 0
    for t in labelArray:
        tempMinus = tempMinus + ((len(t)/totalLen)*entropy(0, t))
    infoGained = infoGained - tempMinus
    return infoGained
#The trainer class does the actual training and develops the decision tree
def trainer(trainSet, value):
    #Creates a node and stores the value of the node in the node
    node = nodes(value)
    """Tests to see if the labels associated with that nodes have an entropy of zero
    if they do then set that node as a leaf and assign the value of the label as it's
    leaf value."""
    if len(trainSet[0]) == 2:
        """if value == "1":
            print(trainSet)"""
        if entropy(len(trainSet[0])-1,trainSet) == 0:
            node.setIsLeaf(True)
            node.setLeafValue(trainSet[0][len(trainSet[0])-1])
        #If their are only 2 columns left in the training set start calculating the leaves
        else:    
            #Parent of leaves
            node.setIsLeaf(False)
            """Create an array for the children, the array of the leaf values and the labels 
            associated with those leaves"""
            children = []
            leafArray = []
            labelArray = []
            #Finds the leaves and the labels associated with them
            for t in range(len(trainSet)):
                if leafArray.count(trainSet[t][0]) == 0:
                    leafArray.append(trainSet[t][0])
                    setArray = []
                    setArray.append(trainSet[t][1])
                    labelArray.append(setArray)
                else:
                    labelArray[leafArray.index(trainSet[t][0])].append(trainSet[t][1])
            """Loops through the leaves and finds the label best associated with it.
            If the labels arent all the same then the once that occurs the most is used"""
            for t in range(len(leafArray)):
                leaf = nodes(leafArray[t])
                leaf.setIsLeaf(True)
                #again using parallel arrays for the count of the labels
                valueArray = []
                countArray = []
                mostOccur = ''
                mostOccurNum = -1
                #Counts the occurents of the labels
                for m in labelArray[t]:
                    if valueArray.count(m) == 0:
                        valueArray.append(m)
                        countArray.append(1)
                    else:
                        index = valueArray.index(m)
                        countArray[index] = countArray[index] + 1
                        if countArray[index] > mostOccurNum:
                            mostOccur = valueArray[index]
                            mostOccurNum = countArray[index]
                #Sets the leafs label value(leafValue) to the label that occurs the most
                leaf.setLeafValue(mostOccur)
                children.append(leaf)
            #Pass the children to the parent node
            node.setChildren(children)
    else:
        node.setIsLeaf(False)
            #Initializing an int that will always be written over
        currBestGain = -10000
        mostLearned = 0
            #Finds the Column with the most information gain
        for w in range(len(trainSet[0])-1):
            gain = infoGain(w, trainSet)
            if gain > currBestGain:
                currBestGain = gain
                mostLearned = w
        if entropy(mostLearned,trainSet) == 0:
            node.setIsLeaf(True)
            node.setLeafValue(trainSet[0][len(trainSet[0])-1])
        else:
            #The node isnt a leaf
            
            """Using Parallel lists to store the split children values from the column with the 
            most information gain. Also storing the sub training sets for each value with the
            remaining column in it""" 
            splitArray = []
            labelsArray = []
            for t in trainSet:
                if splitArray.count(t[mostLearned]) == 0:
                    splitArray.append(t[mostLearned])
                    #copying to so that I can delete the column that I am spliting the decision at
                    setArray = t.copy()
                    setArray.pop(mostLearned)
                    labelsArray.append([])
                    labelsArray[splitArray.index(t[mostLearned])].append(setArray)
                else:
                    setArray = t.copy()
                    setArray.pop(mostLearned)
                    labelsArray[splitArray.index(t[mostLearned])].append(setArray)
            children = []
            #Setting the children for the node
            for t in range(len(labelsArray)):
                children.append(trainer(labelsArray[t], splitArray[t]))
            node.setChildren(children)
    return node

def printTree(root):
    print(root.value)
    if root.isLeaf == False:
        for w in root.childArray:
            printTree(w)
    else:
        print("Leaf: "+root.leafValue)
    print("Back")

#Inputs
input_string = input()
inputList = input_string.split(' ')
training = inputList[0]
test = inputList[1]

f = open(training, 'r')
train = ''
counter = 0
trainingSet = []
for w in f:
    train = train + w 
    w = w.rstrip('\n')
    line = w.split(",")
    trainingSet.append(line)
    counter = counter +1
f.close
f = open(test, 'r')
test = ''
testSet = []
for w in f:
    test = test + w
    w = w.rstrip('\n')
    testSet = w.split(",")
f.close

#Run the trainer and generate decision tree
trainedTree = trainer(trainingSet, "start")
#Set value found to false
valueFound = False
#printTree(trainedTree)
#Search through the training set to find the label associated with the decision test
#Count use recursion later just so that it runs cleaner
for k in testSet:
    #If the value is found before reaching the end of the test set break the look
    if valueFound == True:
        break
    else:
        #Iterates throught the children of the node
        for m in trainedTree.childArray:
            #Goes to the child that has the same value as the next value in the test set
            if m.value == k:
                #If it is a leaf node then it has found the end and returns the label value
                if m.isLeaf == True:
                    valueFound = True
                    print(m.leafValue)
                #Otherwise it just sets the child as the next node to test.
                else:
                    trainedTree = m