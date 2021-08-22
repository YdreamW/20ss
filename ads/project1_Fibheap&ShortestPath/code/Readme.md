####How to build the exectable file:
    Open the folder ./source/ and compile the file source.cpp
    The amount of data is huge, so it is best to use the release version for compilation.

####How to run the exectable file:
    You need to put a data.in file and this .exe file in the same folder. 
    Then run the exe, it will generate two files named FibonacciHeap.out and ProrityQueue.out.
    They represent the results generated using Fibonacci and Binary Heaps, respectively.
    One recommended method is to put the .exe file in the ./data/testi folder
####Description of input format:
    We changed the input format. We read in the original .gz file and constructed a new input file data.in.
    The first row of the input data consists of three integers V, E and Q, representing the number of vertices, the number of edges, and the number of queries, respectively.
    In the following E rows, three integers a_i, b_i, c_i, in each line, represents an arrow from a_i to b_i and the weights of this arrow is c_i.
    The last Q rows of the input data contains two integers in each row, indicating the label of the starting point and the label of the terminal point of a group of queries.

**Notice that the amount of data is huge, so your memory may not be enough.**