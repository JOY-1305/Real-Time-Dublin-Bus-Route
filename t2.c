#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "t2.h"

//Global Declarations


Graph* create_graph(int num_nodes); 
void add_edge(Graph *g, int from, int to, int weight); 
void dijkstra(Graph* g, int origin); 
void delete_graph(Graph* g); 

struct Graph* create_graph(int num_nodes) 
{
    Graph* g = (struct Graph*) malloc(sizeof( Graph));
    g->countN = num_nodes;

    int i,j;
    for (i = 0; i < sizeMax; i++)
    {
        for(j = 0; j<sizeMax;j++ ){
            (g->value[i][j] = 999999);
        }  
    }

    return g;
}

void add_edge(Graph *g, int from, int to, int weight) 
{
    g->value[from][to] = weight;
    g->value[to][from] = weight;  
}



void dijkstra(Graph* g, int origin){
    int i;
    int numberval = g->countN;
    int CountD[numberval], Visit_yes[numberval], curr, min, nextval;
    

    for (i = 0; i < numberval; i++) {
    CountD[i] = g->value[origin][i];

    Visit_yes[i] = 0;

    }
    Visit_yes[origin] = 1;
    CountD[origin] = 0;
    curr = 1;  

    while (curr < numberval-1) {
        
        min = 999999;
    
        for (i = 0; i < numberval; i++)
        {
            if (CountD[i] < min && Visit_yes[i] != 1) {
            min = CountD[i];
            nextval = i;
            }
        }
           
    
        Visit_yes[nextval] = 1;
        for (i = 0; i < numberval; i++){
            if (Visit_yes[i] != 1){
                if (min + g->value[nextval][i] < CountD[i]) {
                    CountD[i] = min + g->value[nextval][i];

                }
            }
        }
        curr++;
    }

    int select[numberval];
    int u,v;
    for(u=0;u<numberval;u++){
        select[u]=CountD[u]; 
    }
    
    int tot_temp[numberval];
    
    for(u=0;u<numberval;u++){
        tot_temp[u]=u; 
    }
    
    for( i = 1; i < numberval; i++){
        
        for( v = i-1; v>=0; v--){
            if(select[i] < select[v]){

                int x1,x2;
                x2 = tot_temp[i];
                x1 = select[i];
                tot_temp[i] = tot_temp[v];
                tot_temp[v] = x2;
                select[i] = select[v];
                select[v] = x1;
                i = i-1;
            }
        }
    }
        
    for(i=0;i<numberval;i++){
        printf("%c ",'A'+tot_temp[i]);
    }

    printf("\n");

    for(i=0; i<numberval; i++){
        printf("The length of the shortest path between %c and %c is %d\n",'A'+origin,'A'+i,CountD[i]);
    }
}

void delete_graph(Graph* g) 
{
    
    int i,v;
    for(i=0; i<g->countN; i++){
        for(v=0; v<g->countN; v++){
            g->value[i][v]=0;
        }
    }
    free(g);
}
