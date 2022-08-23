
#ifndef T3_H_
#define T3_H_

#define MAX_VERTICES 5000 // you can assume that the graph has at most 10 vertex
#define MAX_STRING_SIZE 1024

typedef struct Graph
{
    int numNodes;
    //int matrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

typedef struct Stops
{
    int stopID;
    char name[MAX_STRING_SIZE];
    char latitude[MAX_STRING_SIZE];
    char longitude[MAX_STRING_SIZE];
    // Stops *next;
} Stops;

typedef struct Edges
{
    int src;
    int dest;
    int cost;
    // Edges *next;
} Edges;

Graph *create_graph(int num_nodes);                    // creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
void add_edge(Graph *g, int from, int to, int weight); // adds an undirected weighted edge between from and to
void dijkstra(Graph *g, int origin);                   // implements the dijkstra algorithm and prints the order in which the nodes are made permanent, and the length of the shortest path between the origin node and all the other nodes
void delete_graph(Graph *g);

int load_edges(char *fname);                    //loads the edges from the CSV file of name fname
int load_vertices(char *fname);                 //loads the vertices from the CSV file of name fname
void shortest_path(int startNode, int endNode); // prints the shortest path between startNode and endNode, if there is any
void free_memory(void);                         // frees any memory that was used

#endif