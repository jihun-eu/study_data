#include<stdio.h>
#define MAX_VERTICES 20
#define TRUE 1
#define FALSE 0
int visited[MAX_VERTICES];
typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
}GraphNode;

typedef struct GraphType {
	int n;
	GraphNode* adj_list[MAX_VERTICES];
}GraphType;
void dfs_list(GraphType* g, int v) {
	GraphNode* w;
	visited[v] = TRUE;
	printf("%d ", v);
	for (w = g->adj_list[v]; w;w = w->link)
		if (!visited[w->vertex])
			dfs_list(g, w->vertex);
}