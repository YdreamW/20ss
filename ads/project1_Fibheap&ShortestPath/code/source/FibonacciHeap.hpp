#ifndef FibonacciHeap_Hpp
#define FibonacciHeap_Hpp

typedef int Dis;
typedef int AdjVertex;

/*
The struct for the nodes in the Fibonacci Heap
*/
typedef struct FibonacciNodeStruct *PFibonacciNode;
typedef struct FibonacciNodeStruct
{
    Dis key; //The temporary distance from the start node to the node.
    PFibonacciNode left, right, child;
    AdjVertex index;
    int degree;
} FibonacciNode;

/*
The struct for the Fibonacci Heap
*/
typedef struct FibonacciHeapStruct *PFibonacciHeap;
typedef struct FibonacciHeapStruct
{
    int sumNodes;           //the sum of the nodes
    PFibonacciNode minTree; //the pointer to the tree whose top node is min
} FibonacciHeap;

//The declarations of the functions
PFibonacciHeap BuildAFibonacciHeap(); //Build an empty fibonacci heap
void InsertToFibonacciHeap(PFibonacciHeap FibHeap, PFibonacciNode FibNode);  //insert the FibNode into the FibHeap
PFibonacciNode CreateAFibonacciNode(Dis key, AdjVertex index);  // create a fibonacci node with key and index
PFibonacciNode PopMinFibonacciHeap(PFibonacciHeap FibHeap);  //Return the min Node in the FibHeap and delete it
void AddNodeToList(PFibonacciNode rootNode, PFibonacciNode FibNode); // Insert FibNode to the right of rootNode in the doubly linked list 
void RemoveNodeFromList(PFibonacciNode FibNode); //Remove the FibNode from the doubly list it exists in
void UpdateFibonacciHeap(PFibonacciHeap FibHeap); //After deleting the min node, update the heap structure

//The definitions of the functions
PFibonacciHeap BuildAFibonacciHeap()
{
    PFibonacciHeap FibHeap = (PFibonacciHeap)malloc(sizeof(FibonacciHeap));
    FibHeap->minTree = NULL;
    FibHeap->sumNodes = 0;
    return FibHeap;
}
PFibonacciNode CreateAFibonacciNode(Dis key, AdjVertex index)
{
    PFibonacciNode FibNode = (PFibonacciNode)malloc(sizeof(FibonacciNode));
    FibNode->key = key;
    FibNode->child = NULL;
    FibNode->left = FibNode->right = FibNode;
    FibNode->degree = 0;
    FibNode->index = index;
    return FibNode;
}
void AddNodeToList(PFibonacciNode rootNode, PFibonacciNode FibNode)
{
    FibNode->right = rootNode->right;
    rootNode->right->left = FibNode;
    rootNode->right = FibNode;
    rootNode->right = FibNode;
    FibNode->left = rootNode;
}
void RemoveNodeFromList(PFibonacciNode FibNode)
{
    if (FibNode->right == FibNode)
        return;
    FibNode->right->left = FibNode->left;
    FibNode->left->right = FibNode->right;
    FibNode->left = FibNode->right = FibNode;
}
void InsertToFibonacciHeap(PFibonacciHeap FibHeap, PFibonacciNode FibNode)
{
    FibHeap->sumNodes++;
    if (!FibHeap->minTree)  //Empty heap
        FibHeap->minTree = FibNode;
    else
    {
        AddNodeToList(FibHeap->minTree, FibNode);  //Lazy insertion
        if (FibNode->key < FibHeap->minTree->key)  //Update the min node
            FibHeap->minTree = FibNode;
    }
}
PFibonacciNode PopMinFibonacciHeap(PFibonacciHeap FibHeap)
{
    PFibonacciNode minNode = FibHeap->minTree;
    PFibonacciNode tmpNode = minNode->child;
    PFibonacciNode t;
    //Add the children of the minNode into the Root List
    while (tmpNode)
    {
        if (tmpNode->right == tmpNode)
            t = NULL;
        else
            t = tmpNode->right;
        RemoveNodeFromList(tmpNode);  //Remove the child from its origin doubly list
        minNode->child = t;
        AddNodeToList(minNode, tmpNode); //Add the child into the root list
        tmpNode = t;
    }
    if (minNode->right == minNode)
        t = NULL;
    else
        t = minNode->right;
    RemoveNodeFromList(minNode); //Remove the minNode
    FibHeap->minTree = t;
    UpdateFibonacciHeap(FibHeap);  //Update the FibHeap Structure
    FibHeap->sumNodes--;
    return minNode;
}
void UpdateFibonacciHeap(PFibonacciHeap FibHeap)
{
    if (!FibHeap->minTree)
        return;
    int hashTableSize = ceil(log2(FibHeap->sumNodes)) + 1;  //Use a hashTable to obtain the trees with the same degree
    PFibonacciNode *hashTable = new PFibonacciNode[hashTableSize];
    for (int i = 0; i < hashTableSize; i++)
        hashTable[i] = NULL;
    //Re-aggregate the trees on the Root List into the hashtable. We will link those trees with the same degree
    while (FibHeap->minTree)  
    {
        PFibonacciNode minNode = FibHeap->minTree, t;
        int degree = minNode->degree;
        if (minNode->right == minNode)
            t = NULL;
        else
            t = minNode->right;
        RemoveNodeFromList(minNode);
        while (hashTable[degree]) //Aggregate trees until there doesn't exist any trees having the same degree
        {
            PFibonacciNode eNode = hashTable[degree];
            //we always set the tree in the hash table as the child of the tree from the Root List
            //So we should make it sure that the eNode->key is larger than the minNode->key
            if (eNode->key < minNode->key)
            {
                PFibonacciNode t = eNode;
                eNode = minNode;
                minNode = t;
            }
            if (!minNode->child)
                minNode->child = eNode;
            else
                AddNodeToList(minNode->child, eNode);
            minNode->degree++;
            hashTable[degree++] = NULL;  //The degree has been enlarged after aggregating two trees
        }
        hashTable[degree] = minNode; 
        FibHeap->minTree = t;
    }
    //Move the trees in the hash table to the root list
    for (int i = 0; i < hashTableSize; i++)
    {
        if (hashTable[i])
        {
            if (FibHeap->minTree)
            {
                AddNodeToList(FibHeap->minTree, hashTable[i]);
                if (hashTable[i]->key < FibHeap->minTree->key)
                    FibHeap->minTree = hashTable[i];
            }
            else
                FibHeap->minTree = hashTable[i];
        }
    }
   delete [] hashTable;
}

#endif