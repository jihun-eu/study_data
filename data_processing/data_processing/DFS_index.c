#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTICES 20
#define TRUE 1
#define FALSE 0

int visited[MAX_VERTICES];
typedef struct GraphType {
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;
void dfs_mat(GraphType* g, int v)
{
	int w;
	visited[v] = TRUE;
	printf("%d", v);
	for (w = 0; w < g->n; w++)
		if (g->adj_mat[v][w] && !visited[w])
			dfs_mat(g, w);
}