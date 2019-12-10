#include<stdio.h>
#define MAX_VERTICES 20
#define TRUE 1
#define FALSE 0
int visited[MAX_VERTICES];

void dfs_list(GraphType* g, int v) {
	GraphNode* w;
	visited[v] = TRUE;
	printf("%d ", v);
	for (w = g->adj_list[v]; w;w = w->link)
		if (!visited[w->vertex])
			dfs_list(g, w->vertex);
}