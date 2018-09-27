#!/usr/bin/env python3
"""Display the result of a run of the queues c++ program as a scatterplot

Opens a file one directory up reads in the comma seperated list of rows
Each row represents the ticcount and the process currently running

It then displays these points in a scatterplot where each processes
mark is the same color (ie all of process 8's points are blue)

Any points that are associated with process 0 are bogus, it really means
uninitialized
"""
import numpy as np
import matplotlib.pyplot as plt
import random

#super cheesy to hardcode this
LOG_FILE_2_NO_IO = '../2_noIO_results.txt'
LOG_FILE_2_IO = '../2_IO_results.txt'
LOG_FILE_MANY_MIXED = '../MANY_MIXED_results.txt'

C_LOG_FILE_2_NO_IO = '../sampleruns/2_noIO_results.txt'
C_LOG_FILE_2_IO = '../sampleruns/2_IO_results.txt'
C_LOG_FILE_MANY_MIXED = '../sampleruns/MANY_MIXED_results.txt'

def read_datafile(file_name):
    """loads the file data and converts it into a n,2 numpy array"""
    data = np.loadtxt(file_name, delimiter=',')
    return data

def generate_plot(file_name,fignum,heading):
    #pull points into an array
    data = read_datafile(file_name)

    #filter x and y out into 1 dimensional array
    x= data[:,0]
    y= data[:,1]

    #set negative values=0 (a negative value means UNINITIALIZED)
    x[x<0]=0
    y[y<0]=0

    #how many ticks?
    numvals = x.size

    plt.subplot(2,3,fignum)
    plt.xlim(0, np.amax(x)+1)   #set range of plot
    plt.ylim(0, np.amax(y)+1)
    plt.grid(True)              #show a grid
    plt.title(heading)
    plt.xlabel('tickcount')
    plt.ylabel('process number')

    #want the same color scheme every time
    random.seed(0)

    #want 1 unique color per unique process number
    numb_unique_colors = int(np.amax(y))
    colors = []
    for i in range(numb_unique_colors+1):
        colors.append('#%06X' % random.randint(0, 0xFFFFFF))

    #build an array of colors, 1 for each plot point
    #points with the same process number will have the same color
    all_y_colors=[colors[int(val)] for val in y]

    #create and show
    plt.scatter(x,y,s=70, c=all_y_colors)

if __name__ == "__main__":
    generate_plot(C_LOG_FILE_2_NO_IO, 1, "2 process, no IO")
    generate_plot(C_LOG_FILE_2_IO, 2, "2 processes, both IO")
    generate_plot(C_LOG_FILE_MANY_MIXED, 3, "4-3-2-1 (1-IO 3-IO)")

    generate_plot(LOG_FILE_2_NO_IO, 4, "STUDENT 2 process, no IO")
    generate_plot(LOG_FILE_2_IO, 5, "STUDENT 2 processes, both IO")
    generate_plot(LOG_FILE_MANY_MIXED, 6, "STUDENT 4-3-2-1 (1-IO 3-IO)")

    plt.show()

