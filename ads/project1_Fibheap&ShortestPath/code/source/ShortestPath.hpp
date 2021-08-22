#ifndef ShortestPath_Hpp
#define ShortestPath_Hpp

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "FibonacciHeap.hpp"
#include "PriorityQueue.hpp"
#define INF 2147483647
typedef int Dis;

/*
Adjacency list is used to describe the graph
*/
typedef int AdjVertex; //the index of vertexes. Notice that the index should begin as 0
/*
The struct storing the edges in the adjacency list.
*/
typedef struct AdjEdgeStruct *PAdjEdge;
typedef struct AdjEdgeStruct
{
    Dis dis;                        //the length of the edge
    AdjVertex fromVertex, toVertex; //the vertexes the edge connects
    PAdjEdge nextEdge;              //the following edges whose FROM VERTEX is the same
} AdjEdge;                          //the struct and the pointer to an edge

typedef PAdjEdge *AdjList; //the adjacency list

typedef struct GraphStruct
{
    int sumVertexes; //the sum of all the vertexes in the graph;
    int sumEdges;    //the sum of all the edges in the graph;
    AdjList HeadList;
} * PGraph;

//The declarations of the functions
PGraph BuildAGraph(int sumVertexes, int sumEdges);                        //build an empty adjacency list with sumVertexes vertexes
void AddEdge(PGraph G, AdjVertex fromV, AdjVertex toV, Dis dis);          // add an edge from fromV to toV
Dis DijkstraUsingFibonacciHeap(PGraph G, AdjVertex start, AdjVertex end); //Dijkstra algorithm using fibonacci heap
Dis DijkstraUsingPriorityQueue(PGraph G, AdjVertex start, AdjVertex end); //Dijkstra algorithm using priority queue

//The definitions of the functions
PGraph BuildAGraph(int sumVertexes, int sumEdges)
{
    PGraph Graph = (PGraph)malloc(sizeof(struct GraphStruct));
    Graph->sumVertexes = sumVertexes;
    Graph->sumEdges = sumEdges;
    Graph->HeadList = (AdjList)malloc(sizeof(PAdjEdge) * sumVertexes);
    for (int i = 0; i < sumVertexes; i++)
    {
        Graph->HeadList[i] = NULL;
    }
    return Graph;
}

void AddEdge(PGraph G, AdjVertex fromV, AdjVertex toV, Dis dis)
{
    PAdjEdge edge = (PAdjEdge)malloc(sizeof(AdjEdge));
    edge->fromVertex = fromV;
    edge->toVertex = toV;
    edge->dis = dis;
    edge->nextEdge = G->HeadList[fromV];
    G->HeadList[fromV] = edge;
}

Dis DijkstraUsingFibonacciHeap(PGraph G, AdjVertex start, AdjVertex end)
{
    PFibonacciHeap FibHeap = BuildAFibonacciHeap();
    Dis *dis = (Dis *)malloc(sizeof(Dis) * G->sumVertexes); //The temporary dis from the start to the node
    bool *visit = (bool *)malloc(sizeof(bool) * G->sumVertexes);
    for (int i = 0; i < G->sumVertexes; i++)
    {
        dis[i] = INF;
        visit[i] = 0;
    }

    dis[start] = 0;
    PFibonacciNode FibNode = CreateAFibonacciNode(0, start);
    InsertToFibonacciHeap(FibHeap, FibNode); // Insert the startNode into the fibonacci heap
    while (FibHeap->minTree)
    {
        PFibonacciNode tmpNode = PopMinFibonacciHeap(FibHeap);
        AdjVertex tmpV = tmpNode->index; //Get the node which has the min dis from startNode
        if (visit[tmpV])
            continue;                                            //Skip it if the node has been visited
        visit[tmpV] = true;                                      //Mark the node
        for (PAdjEdge i = G->HeadList[tmpV]; i; i = i->nextEdge) //Use the tmpV to relax all the advancency nodes
        {
            AdjVertex to = i->toVertex;
            if (!visit[to] && dis[tmpV] + i->dis < dis[to])
            {
                dis[to] = dis[tmpV] + i->dis;
                FibNode = CreateAFibonacciNode(dis[to], to);
                InsertToFibonacciHeap(FibHeap, FibNode); //Insert the node that is been relaxed into the heap
            }
        }
    }
    Dis ret = dis[end];
    free(FibNode);
    free(dis);
    free(visit);
    free(FibHeap);
    return ret;
}
Dis DijkstraUsingPriorityQueue(PGraph G, AdjVertex start, AdjVertex end)
{
    Dis *dis = (Dis *)malloc(sizeof(Dis) * G->sumVertexes);
    bool *visit = (bool *)malloc(sizeof(bool) * G->sumVertexes);
    for (int i = 0; i < G->sumVertexes; i++)
    {
        dis[i] = INF;
        visit[i] = 0;
    }
    dis[start] = 0;
    PriorityQueue heap = BuildAHeap(G->sumVertexes + G->sumEdges);
    HeapNode newNode;
    newNode.index = start;
    newNode.key = 0;
    InsertToPriorityQueue(newNode, heap); // Insert the startNode into the fibonacci heap
    while (!IsEmptyPriorityQueue(heap))
    {
        HeapNode tmpNode = PopMinPriorityQueue(heap);
        AdjVertex tmpV = tmpNode.index;
        if (visit[tmpV])
            continue;                                            //Skip it if the node has been visited
        visit[tmpV] = true;                                      //Mark the node
        for (PAdjEdge i = G->HeadList[tmpV]; i; i = i->nextEdge) //Use the tmpV to relax all the advancency nodes
        {
            AdjVertex to = i->toVertex;
            if (!visit[to] && dis[tmpV] + i->dis < dis[to])
            {
                dis[to] = dis[tmpV] + i->dis;
                newNode.index = to;
                newNode.key = dis[to];
                InsertToPriorityQueue(newNode, heap); //Insert the node that is been relaxed into the heap
            }
        }
    }
    Dis ret = dis[end];
    free(dis);
    free(visit);
    free(heap);
    return ret;
}

#endif