#ifndef T2_H_
#define T2_H_
#include <stdio.h>
#include <stdlib.h>
#define sizeMax 10 

typedef struct Graph{
    int countN;
    int value[sizeMax][sizeMax];
} Graph;


Graph* create_graph(int num_nodes); // creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
void add_edge(Graph *g, int from, int to, int weight); // adds an undirected weighted edge between from and to
void dijkstra(Graph* g, int origin); // implements the dijkstra algorithm and prints the order in which the nodes are made permament, and the length of the shortest path between the origin node and all the other nodes
void delete_graph(Graph* g);

#endif
