#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "ShortestPath.hpp"
using namespace std;
typedef struct QueryPairStruct
{
    int start, end;
} QueryPair;
int main()
{
	char filename[30];
    FILE* PFileIn =  fopen("data.in", "r");
    clock_t begin, finish;
    int n, m, q;
    fscanf(PFileIn,"%d %d %d",&n,&m,&q);
    PGraph G = BuildAGraph(n, m);
    QueryPair *QueryPairs = (QueryPair *)malloc(sizeof(QueryPair) * q);
    for (int i = 0; i < m; i++)
    {
        int f, t, d;
        fscanf(PFileIn,"%d %d %d",&f,&t,&d);
        AddEdge(G, f - 1, t - 1, d);
    }
    for (int i = 0; i < q; i++)
    {
        int s, e;
        fscanf(PFileIn,"%d %d",&s,&e);
        QueryPairs[i].start = s - 1;
        QueryPairs[i].end = e - 1;
    }
    fclose(PFileIn);
	
	sprintf(filename, "PriorityQueue.out");
    FILE *PFileOut=fopen(filename, "w");
    fprintf(PFileOut,"The result using Priority Queue is: \n");
    begin = clock();
    for (int i = 0; i < q; i++)
    {
        Dis ans = DijkstraUsingPriorityQueue(G, QueryPairs[i].start, QueryPairs[i].end);
        fprintf(PFileOut,"%d\n", ans);
    }
    finish = clock();
    fprintf(PFileOut,"The time using Priority Queue is: %d", (finish - begin) / CLOCKS_PER_SEC);
    fclose(PFileOut);
    cout << "The function using Priority Queue completed!" << endl;

	sprintf(filename, "FibonacciHeap.out");
    PFileOut=fopen(filename, "w");
    fprintf(PFileOut,"The result using Fibonacci Heap is: \n");
    begin = clock();
    for (int i = 0; i < q; i++)
    {
        Dis ans = DijkstraUsingFibonacciHeap(G, QueryPairs[i].start, QueryPairs[i].end);
        fprintf(PFileOut,"%d\n", ans);
    }
    finish = clock();
    fprintf(PFileOut,"The time using Fibonacci Heap is: %d", (finish - begin) / CLOCKS_PER_SEC);
    fclose(PFileOut);
    printf("The function using Priority Queue completed!");
    return 0;
}
