#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Mar  8 13:53:20 2018

@author: jcrissey4
"""
import random
import math
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import LinearLocator, FormatStrFormatter
def my_graph(x, y):
    zArray = []
    min = None
    max = None
    for i in range(len(x)):
        xRow = []
        for t in range(len(x[i])):
            val = my_func(x[i][t], y[i][t])
            if min == None:
                min = val
                max = val
            if min >= val:
                min = val
            if max <= val:
                max = val
            xRow.append(val)
        zArray.append(xRow)
    return np.array(zArray), max, min 
def graph(func, xmin, ymin, xmax, ymax, longestStep, points=[]):
    fig = plt.figure()
    ax = fig.gca(projection='3d')
    # Make data.
    X = np.arange(xmin, xmax, 0.25)
    Y = np.arange(ymin, ymax, 0.25)
    X, Y = np.meshgrid(X, Y)
    Z, max, min = func(X,Y)
    # Plot the surface.
    surf = ax.plot_surface(X, Y, Z, #cmap=cm.coolwarm,
    linewidth=0, antialiased=False)
    # Customize the z axis.
    ax.set_zlim(min, max)
    ax.zaxis.set_major_locator(LinearLocator(10))
    ax.zaxis.set_major_formatter(FormatStrFormatter('%.02f'))
    # Add a color bar which maps values to colors.
    #fig.colorbar(surf, shrink=0.5, aspect=5)
    for i in points:
        ax.plot([i[0]], [i[1]], [i[2]], '.', color=(i[3]/longestStep,0,0)) 
    plt.show()
input_string = input()
inputList = input_string.split(' ')
input_file = inputList[0]
xmin = int(inputList[1])
ymin = int(inputList[2])
xmax = int(inputList[3])
ymax = int(inputList[4])

f = open(input_file, 'r')
func = ''
for w in f:
    func = func + w 
f.close
exec(func)
paths = []
longestStep = 0;
bestX = 0
bestY = 0
bestHeight = my_func(bestX,0)
for x in range(0, 100):
    x = random.randint(xmin, xmax)
    y = random.randint(ymin, ymax)
    height = my_func(x,y)
    firstPoint = [x,y,height,0]
    paths.append(firstPoint)
    hasLarger = True
    largestStep = 0
    counter = 0;
    while hasLarger:
        hasLarger = False
        largestStep = 0
        nextX = 0
        nextY = 0
        nextHeight = 0
        if x+1 <= xmax:
            testHeight = my_func(x+1,y)
            if testHeight >= height:
                largestStep = testHeight - height 
                hasLarger = True
                nextX = x+1
                nextY = y
                nextHeight = testHeight
        if x-1 >= xmin:
            testHeight = my_func(x-1,y)
            if testHeight >= height:
                if largestStep < testHeight - height:
                    largestStep = testHeight - height
                    hasLarger = True
                    nextX = x-1
                    nextY = y
                    nextHeight = testHeight
        if y+1 <= ymax:
            testHeight = my_func(x,y+1)
            if testHeight >= height:
                if largestStep < testHeight - height:
                    largestStep = testHeight - height
                    hasLarger = True
                    nextX = x
                    nextY = y+1
                    nextHeight = testHeight
        if y-1 >= ymin:
            testHeight = my_func(x,y-1)
            if testHeight >= height:
                if largestStep < testHeight - height:
                    largestStep = testHeight - height
                    hasLarger = True
                    nextX = x
                    nextY = y-1
                    nextHeight = testHeight
        if hasLarger:
            x = nextX
            y = nextY
            step = nextHeight - height
            if longestStep < step:
                longestStep = step
            height = nextHeight
            point = [x,y,height,step]
            paths.append(point)
            counter = counter +1
    if height > bestHeight:
        bestX = x
        bestY = y
        bestHeight = height
tempArr = [bestX,bestY]
print(tempArr)
graph(my_graph, xmin, ymin, xmax, ymax, longestStep, paths)  
