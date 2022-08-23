#include "t3.h"
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define NODE_SIZE 1024
#define NUM_NODES 8000
#define sizeOfElements 512

#define MAX_VERTICES 5000 // you can assume that the graph has at most 10 vertex
#define MAX_STRING_SIZE 1024

int matrix[MAX_VERTICES][MAX_VERTICES];


typedef struct Node {
    int stopId;
    char *name;
    char *latitude;
    char *longitude;
} Node;


typedef struct Edge{
    int weight;
    int startId;
    int endId;
} Edge;



Graph* graph;
Node *nodes[NUM_NODES];

Node *getNode(char buffer[]) {

    int col = 0;
    int isQuote = 0;
    char element[sizeOfElements];
    memset(element, 0, sizeOfElements); 


    Node *node = malloc(sizeof(Node));


    for (int i = 0; i < strlen(buffer); i++)
    {
        switch (buffer[i])
        {
        case ',':
            if (!isQuote)
            {
                switch (col)
                {
                case 0:
                    node->stopId = atoi(element);
                    break;
                case 1:
                    node->name = strdup(element);
                    break;
                case 2:
                    node->latitude = strdup(element);
                    break;
                case 3:
                    node->longitude = strdup(element);
                    break;
                default:
                    break;
                }
                col++;
                
                memset(element, 0, sizeOfElements); 
            }
            break;
        case '\"':
            isQuote = !isQuote;
            continue;
        default:
            strcat(element, (char[2]){buffer[i], '\0'});
            break;
        }
    }

    node->longitude = strdup(element);
    return node;
}

Edge *getDirection(char buffer[]) {

    int col = 0;
    int isQuote = 0;
    char element[sizeOfElements];
    memset(element, 0, sizeOfElements); 


    Edge *edge = malloc(sizeof(Edge));

    for (int i = 0; i < strlen(buffer); i++)
    {
        switch (buffer[i])
        {
        case ',':
            if (!isQuote)
            {
               
                switch (col)
                {
                case 0:

                    edge->startId = atoi(element);
                    break;
                case 1:

                    edge->endId = atoi(element);
                    break;
                case 2:

                    edge->weight = atoi(element);
                    break;
                default:
                    break;
                }
                col++;

                memset(element, 0, sizeOfElements); 
            }
            break;
        case '\"':
            isQuote = !isQuote;
            continue;
        default:
            strcat(element, (char[2]){buffer[i], '\0'});
            break;
        }
    }

    edge->weight = atoi(element);
    return edge;
}


int load_vertices ( char *fname ) {
    FILE *file = fopen(fname, "r");

    int numNodes = 0;
    if (!file)
        printf("Can not open the File\n");
    else {
        char buffer[NODE_SIZE];
        int isFirst = 1;

        while (fgets(buffer, 1024, file))
        {
            if (isFirst)
            {
                isFirst = 0;
                continue;
            }

            Node *node = getNode(buffer);
            nodes[node->stopId] = node;
            numNodes++;
        }
    }
    printf("Loaded %d vertices\n", numNodes);
    
    return numNodes;
}

int load_edges ( char *fname ) {


    // graph = (Graph*) malloc(sizeof(Graph));
    // graph->numNodes = NUM_NODES;
    
    // graph->matrix = malloc(NUM_NODES * sizeof(graph->matrix));
    // for (int i = 0; i < NUM_NODES; i++) {
    //     graph->matrix[i] =malloc(NUM_NODES * sizeof(graph->matrix[i]));
    


    for (int i = 0; i < NUM_NODES; i++)
        for (int j = 0; j < NUM_NODES; j++)
            matrix[i][j] = -1;
    

    for (int i = 0; i < NUM_NODES; i++)
            matrix[i][i] = 0;



    FILE *file = fopen(fname, "r");
    int numEdges = 0;
    if (!file)
        printf("Can not open the File\n");
    else {
        char buffer[NODE_SIZE];
        int isFirst = 1;

        while (fgets(buffer, 1024, file))
        {
            if (isFirst)
            {
                isFirst = 0;
                continue;
            }

            Edge *edge = getDirection(buffer);

            matrix[edge->startId][edge->endId] = edge->weight;
            matrix[edge->endId][edge->startId] = edge->weight;

            numEdges++;
        }
    }
    printf("Loaded %d edges\n", numEdges);

    return numEdges;
}


void smallPath(int *prevs, int start, int end) {
    int idx = 0;
    int reverseArr[NUM_NODES] = {0};

    int Current = end; 
    
    while (Current != start) {
        reverseArr[idx] = Current;
        Current = prevs[Current];
        idx++;
    }



    printf("%3d %15s %10s %10s\n", nodes[start]->stopId, nodes[start]->name, nodes[start]->latitude, nodes[start]->longitude);
    for (int i = idx - 1; i >= 0; i--) {
        int id = reverseArr[i];
        printf("%3d %15s %10s %10s\n", nodes[id]->stopId, nodes[id]->name, nodes[id]->latitude, nodes[id]->longitude);
    }
    printf("\n");
}


int minimumDist(int *d, int *v, int len) {  
    int min = INT_MAX, idx;
    for (int i = 0; i < len; i++) {
        if (v[i] == 0 && d[i] < min) {
            min = d[i];
            idx = i;
        }
    }

    return idx;
}


void shortest_path(int startNode, int endNode) {
    int *dist = (int*) malloc(NUM_NODES * sizeof(int));    
    int *visited = (int*) malloc(NUM_NODES * sizeof(int));
    int *prev = (int*) malloc(NUM_NODES * sizeof(int));    


    for (int i = 0; i < NUM_NODES; i++) {
        if (i != startNode)
            dist[i] = INT_MAX;
        visited[i] = 0;
        prev[i] = -1;
    }

    dist[startNode] = 0;


    for (int i = 0; i < NUM_NODES; i++) {
        int Current = minimumDist(dist, visited, NUM_NODES);
        visited[Current] = 1;  

        
        for (int i = 0; i < NUM_NODES; i++) {
            if (visited[i] == 0 && matrix[Current][i] != -1 && dist[Current] != INT_MAX && dist[Current] + matrix[Current][i] < dist[i]) {
                dist[i] = dist[Current] + matrix[Current][i];
                prev[i] = Current;
            }
        }
    }

    
    smallPath(prev, startNode, endNode);

    
    free(dist);
    free(visited);
    free(prev);
}

int main ( int argc, char *argv[] ) {

	if ( argc < 3 ) {
		printf("usage: ./bus VERTICES EDGES\n");
		return EXIT_FAILURE;
	}

	if ( !load_vertices( argv[1] ) ) {
		printf("Failed to load vertices\n");
		return EXIT_FAILURE;
	}

	if ( !load_edges( argv[2] ) ) {
		printf("Failed to load edges\n");		
		return EXIT_FAILURE;
	}

	


    
    printf("Please enter stating bus stop >\t\t");
    int startingNode;
    scanf("%d", &startingNode);
    printf("Please enter destination bus stop >\t");
    int endingNode;
    scanf("%d", &endingNode);

	shortest_path(startingNode, endingNode);
    

	
	return EXIT_FAILURE;
}