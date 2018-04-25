# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
input_string = input()
inputList = input_string.split(' ')
input_file = inputList[0]
start_node = int(inputList[1])
end_node = int(inputList[2])
search_type = inputList[3]
f = open(input_file, 'r')
nodes = []
for w in f:
    lineList = w.split(' ')
    lineList[0] = int(lineList[0])
    lineList[1] = int(lineList[1])
    lineList[2] = int(lineList[2])
    nodes.append(lineList)
f.close
from collections import deque
if search_type == 'BFS':
    direction = []
    queue = deque([]) #declaring the queue
    nodeFound = False #used for the while loop
    for start in nodes:
        if start[0] == start_node:
           queue.append(start)
    while nodeFound == False:
        topNode = queue[0]
        alreadyIn = False
        for p in queue:
            if p[0] == topNode[1]:
                alreadyIn = True
        if alreadyIn == False:
            for k in nodes:
                if k[0] == topNode[1]:
                    k.append(topNode[0])
                    for a in range(3, len(topNode)):
                        k.append(topNode[a])
                    if(k[1] == end_node):
                        nodeFound = True
                        for a in range(3, len(k)):
                            direction = [k[a]] + direction
                        direction.append(k[0])
                        direction.append(k[1])
                        break
                    queue.append(k)
        queue.popleft()
    print(direction)
    queue.clear()
elif search_type == 'DFS':
    direction = []
    stack = []
    nodeFound = False
    for start in nodes:
        if start[0] == start_node:
           stack.append(start)
    while nodeFound == False:
        topStack = stack[len(stack)-1]
        for k in nodes:
            if k[0] == topStack[1]:
                k.append(topStack[0])
                for a in range(3, len(topStack)):
                    k.append(topStack[a])
                if(k[1] == end_node):
                    nodeFound = True
                    for a in range(3, len(k)):
                        direction = [k[a]] + direction
                    direction.append(k[0])
                    direction.append(k[1])
                    break
                stack.append(k)
        stack.pop
    print(direction)
    stack.clear
elif search_type == 'UCS':
    direction=[]#Final Directions go here
    visited=[]#The list of already visited nodes
    paths=[]#The list of all open paths
    nodeFound = False #Sets whether the final node was found to falls
    for start in nodes:#Find the start node and adds its paths to the list
        if start[0] == start_node:
           paths.append(start)
           visited.append(start[0])
    while nodeFound == False:#While the final node hasnt been found yet
        for n in paths:#Loops through the paths to remove paths with higher costs to already searched nodes
            for k in visited:
                if n[1] == k:
                    paths.remove(n)
        nextSearch = paths[0]#Sets next search to the first path in the list
        for n in paths:#Loops through the paths looking for the path with the least cost
            if nextSearch[2] > n[2]:
                nextSearch = n
        #print('The Paths')#Testing
        #print(paths)#Testing
        #print('Next Search')#Testing
        #print(nextSearch)#Testing
        paths.remove(nextSearch)#Removes the path that is being searched next from the list
        visited.append(nextSearch[1])#Adds the node that is being searched next to the visited list
        if nextSearch[1] == end_node:#If the next node with the shortest path is the end node then record the 
            #path and weight and break the loop
            nodeFound = True
            for a in range(3, len(nextSearch)):
                direction = [nextSearch[a]] + direction
            direction.append(nextSearch[0])
            direction.append(nextSearch[1])
            break
        for n in nodes:#Searches the paths off the node that you are on and adds them to the list. 
            #Also totals the running cost of the path so far
            if n[0] == nextSearch[1]:
                addNode = n
                addNode[2] = addNode[2] + nextSearch[2]
                addNode.append(nextSearch[0])
                for a in range(3, len(nextSearch)):
                    addNode.append(nextSearch[a])
                paths.append(addNode)
                #print('Added Node')#Testing
                #print(addNode)#Testing
    print(direction)#Prints the final directions
    paths.clear
    visited.clear
    
    
    
    
    
    
    






