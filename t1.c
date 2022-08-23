#include <stdio.h>
#include <stdlib.h>
#include "t1.h"
#define SIZE 40

struct Graph* create_graph(int num_nodes); 
void add_edge(struct Graph *g, int from, int to); 
void bfs(struct Graph* g, int origin); 
void dfs(struct Graph* g, int origin); 
void print_graph(struct Graph* g); 

int convert2char(int value){
	value = value+65;
	return value;
}

struct queue {
	int value[SIZE];
	int initial;
	int final;
};
	

struct queue* makeQueue() {
	struct queue* queue = malloc(sizeof(struct queue));
	queue->initial = -1;
	queue->final = -1;
	return queue;
}
	
int EmptyQ(struct queue* queue) {
	if (queue->final == -1)
	{
		return 1;
	}

	else
	{
		return 0;
	}
}	

void enqueue(struct queue* queue, int value) {
	if (queue->final == SIZE - 1)
	{
		printf("\nFull Queue");
	}
    	
	else {
    	if (queue->initial == -1)
    	{
    		queue->initial = 0;
		}
      		
    	queue->final++;
    	queue->value[queue->final] = value;

	}
}

int dequeue(struct queue* queue) {
	int element;
	if (EmptyQ(queue)) 
	{
    	printf("Empty queue");
    	element = -1;
	} 
	else 
	{
		element = queue->value[queue->initial];
		queue->initial++;
    	if (queue->initial > queue->final) 
		{//We reset the Queue

      		queue->initial = queue->final = -1;
    	}
	}
	return element;
}


void printQueue(struct queue* queue) {
	int i = queue->initial;

	if (EmptyQ(queue)) 
	{
    	printf("Queue is empty");
	} 
	else 
	{

    	for (i = queue->initial; i < queue->final + 1; i++) 
		{
      		printf("%c ", convert2char(queue->value[i]));
    	}
    }
}




Graph* create_graph(int num_nodes) 
{
	Graph* g = (struct Graph*) malloc(sizeof(Graph));
    g->num_of_nodes = num_nodes;

    g->array = malloc(num_nodes * sizeof(struct AdjListNode*));
	g->visited = malloc(num_nodes * sizeof(int));
    int i;
    for (i = 0; i < num_nodes; i++)
	{
    	g->array[i] = NULL;
        g->visited[i] = 0;
  
	}

    return g;
}


AdjListNode* newAdj(int var)
{
    struct AdjListNode* make_node = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    make_node->final = var;
    make_node->next = NULL;
    return make_node;
};

void add_edge(Graph *g, int from, int to) 
{
	AdjListNode* make_node = newAdj(to);
    make_node->next = g->array[from];
    g->array[from] = make_node;
  

}

void bfs(Graph* g, int origin)
{
	struct queue* queue = makeQueue();
	printf("\n");
	printf("BFS ");
	g->visited[origin] = 1;
	enqueue(queue, origin);
	
	while (!EmptyQ(queue)) 
	{
		
		int currentVertex = dequeue(queue);	
		printf(" %c ", convert2char(currentVertex));
		struct AdjListNode* buf = g->array[currentVertex];
		
		while (buf) 
		{
			int VertexAdj = buf->final;
			
			if (g->visited[VertexAdj] == 0) 
			{
				g->visited[VertexAdj] = 1;
				enqueue(queue, VertexAdj);
			}
			buf = buf->next;
		}
	}
	int j;
	for(j=0; j<g->num_of_nodes; j++){
		g->visited[j]=0;
	}
	free(queue);

}

int counter(Graph* g, int origin){
	
	struct queue* queue = makeQueue();
	
	g->visited[origin] = 1;
	int x = 0;
	x++;
	
	while (!EmptyQ(queue)) 
	{
		
		int currentVertex = dequeue(queue);		
		struct AdjListNode* buf = g->array[currentVertex];
		
		while (buf) 
		{
			int VertexAdj = buf->final;
			
			if (g->visited[VertexAdj] == 0) 
			{
				g->visited[VertexAdj] = 1;
				x++;
			}
			buf = buf->next;
		}
	}
	free(queue);
	return x;
}

void dfs(Graph* g, int origin) 
{	
	static int curr_temp = 0;
	static int currtemp2 = 0;
	
	struct AdjListNode* arrays  = g->array[origin];
	struct AdjListNode* buf = arrays;
	if(currtemp2 == 0){
		printf("DFS:");
		currtemp2++;
	}
	
	g->visited[origin] = 1;

	printf(" %c ", convert2char(origin));

	while (buf != NULL) {
    int Node_f = buf->final;

    if (g->visited[Node_f] == 0) 
	{
		dfs(g, Node_f);
		curr_temp++;
    }
	buf = buf->next;
	}
	if(curr_temp+1 == g->num_of_nodes){
		int j;
		for(j=0; j<g->num_of_nodes; j++){
			g->visited[j]=0;
		}	
	}
	

}

void print_graph(Graph* g) 
{	
	printf("\n");
	int i;
    for (i = 0; i < g->num_of_nodes; i++)
    {
        struct AdjListNode* p = g->array[i];
		printf("%c ", convert2char(i));
        while (p)
        {
			printf(" -> %c ", convert2char(p->final));
        	p = p->next;
  
        }
		printf("\n");
    }

}

void delete_graph(Graph* g) 
{
	int i;
    for (i = 0; i < g->num_of_nodes; i++)
    {
        struct AdjListNode* p = g->array[i];

        while (p)
        {	
        	struct AdjListNode* buf;
        	buf = p;
        	p = p->next;
            free(buf);
        }

    }
    free(g->array);
    free(g->visited);
    free(g);

}


