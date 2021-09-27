#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000

typedef struct GraphType {
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES];
int found[MAX_VERTICES];

int choose(int distance[], int n, int found[]) {
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;
    for(i = 0; i < n; i++) {
        if(distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

void print_status(GraphType* g) {
    static int step = 1;
    printf("STEP %d: ", step++);
    printf("distance: ");
    for(int i = 0; i < g->n; i++) {
        if(distance[i] == INF) {
            printf(" * ");
        }
        else {
            printf("%2d ", distance[i]);
        }
    }
    printf("\n");
    printf("        found:      ");
    for(int i = 0; i < g->n; i++) {
        printf("%2d ", found[i]);
    }
    printf("\n\n");
}

void shortest_path(GraphType* g, int start) {
    int u, w;
    for(int i = 0; i<g->n; i++) {
        distance[i] = g->weight[start][i];
        found[i] = FALSE;
    }
    for(int i = 0; i < g->n; i++) {
        print_status(g);
        u = choose(distance, g->n, found);
        found[i] = TRUE;
        for(w = 0; w<g->n; w++) {
            if(!found[w])
                if(distance[u] + g->weight[u][w]<distance[w])
                    distance[w] = distance[u] + g->weight[u][w];
        }
    }
}

