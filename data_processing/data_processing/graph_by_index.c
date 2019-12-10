#include<stdio.h>
#define MAX_VERTICES 50
typedef struct GraphType {
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;

void graph_init(GraphType* g) {
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; r++)
			g->adj_mat[r][c] = 0;
}
void instert_vertex(GraphType* g, int v) {
	if ((g->n) + 1) > MAX_VERTICES){
	fprintf(stderr, "그래프: 정점의 개수 초과");
	return;
}
g->n++;
}
void insert_edge(GraphType* g, int start, int end) {
	if (start - g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}
