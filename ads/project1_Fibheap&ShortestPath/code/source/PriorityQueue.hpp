#ifndef PriorityQueue_Hpp
#define PriorityQueue_Hpp

typedef int Dis;
typedef int AdjVertex;
typedef struct HeapNodeStruct
{
    Dis key;         //the dis from the start node to this node
    AdjVertex index; //the index of vertexes
} HeapNode, *PHeapNode;
typedef struct HeapStruct
{
    int size; //Current size of the heap
    int space; //Current space of the heap
    PHeapNode nodeList;
} Heap;
typedef struct HeapStruct *PriorityQueue;

//The declarations of the functions
PriorityQueue BuildAHeap(int sumVertexes);  //Build an empty heap with sumVertexes nodes
void InsertToPriorityQueue(HeapNode x, PriorityQueue H); // insert an node x into the heap H. You should create the node yourself
HeapNode PopMinPriorityQueue(PriorityQueue H); //Return the min node in the heap H and delete it.
bool IsEmptyPriorityQueue(PriorityQueue H); //Check the heap whether empty or not

//The definitions of the functions
PriorityQueue BuildAHeap(int sumVertexes)
{
    PriorityQueue H = (PriorityQueue)malloc(sizeof(HeapStruct));
    H->size = 0;
    H->nodeList=(PHeapNode)malloc(sizeof(HeapNode) * (sumVertexes + 1));
    H->nodeList[0].key = -1;
    return H;
}
void InsertToPriorityQueue(HeapNode x, PriorityQueue H)
{
    int i;
    //Add the node to the tail of the list and percolate up it
    for (i = ++H->size; H->nodeList[i / 2].key > x.key; i /= 2) 
        H->nodeList[i] = H->nodeList[i / 2];
    H->nodeList[i] = x;
}
HeapNode PopMinPriorityQueue(PriorityQueue H)
{
    int i, child;
    HeapNode minNode = H->nodeList[1],
             LastNode = H->nodeList[H->size--];  //Delete the node at the tail of the list, and replace it with the top node    
    //percolate down the LastNode    
    for (i = 1; i * 2 <= H->size; i = child)  
    {
        child = i * 2;
        if (child != H->size && H->nodeList[child + 1].key < H->nodeList[child].key)
            child++;
        if (LastNode.key > H->nodeList[child].key)
            H->nodeList[i] = H->nodeList[child];
        else
            break;
    }
    H->nodeList[i] = LastNode;
    return minNode;
}
bool IsEmptyPriorityQueue(PriorityQueue H)
{
    return H->size == 0 ? true : false;
}

#endif