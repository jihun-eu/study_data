#include<stdio.h>
#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 7
#define INF 1000L

int weight[MAX_VERTICES][MAX_VERTICES] = {
{0,29,INF,INF,INF,10,INF},
{29,0,16,INF,INF,INF,15},
{INF,16,0,12,INF,INF,INF},
{INF,INF,12,0,22,INF,18},
{INF,INF,INF,22,0,27,25},
{10,INF,INF,INF,27,0,INF},
{INF,15,INF,18,25,INF,0} };

int selected[MAX_VERTICES];
int dist[MAX_VERTICES];

int get_min_vertex(int n) {
	int v, i;
	for(i=0;i<n;i++)
		if (!selected[i]) {
			v = i;
				break;
		}
	for (i = 0; i < n; i++)
		if (!selected[i] && (dist[i] < dist[v]))v = i;
	return v;
}
void prim(int s, int n) {
	int i, u, v;

	for (u = 0; u < n; u++) {
		dist[u] = INF;
		selected[u] = FALSE;
	}
	dist[s] = 0;
	for (i = 0; i < n; i++) {
		u = get_min_vertex(n);
		selected[u] = TRUE;
		if (dist[u] == INF)return;
		printf("%d ", u);
		for (v = 0; v < n; v++) {
			if (weight[u][v] != INF)
				if (!selected[v] && weight[u][v] < dist[v])
					dist[v] = weight[u][v];
		}
	}
	for(i=0;i<n;i++)
		printf("[%d]", dist[i]);
}
int main() {
	prim(0, MAX_VERTICES);
}
//dist의 의미는 weight[u][v]에서 u가 증가할때마다 u행의 v열에서 가장 작은 연결된 인덱스값을 찾아 dist의 인덱스에 넣어주는 것이다.
//해당 노드에 연결되어있는 최소 간선을 dist에 저장시켜주는것
/*
의미를 보자
1) dist값을 INF로, select값을 false로 모두 init
2) dist[s]가 0인 이유는 자기자신을 순회하는 경로는 없음을 의미하는것
3) u=get_min_vertex(n)으로 해당경로에서 최솟값을 지정한다.
4) 처음에는 dist[s]외에 전부 INF로 되어있기에 dist[s]는 시작노드를 명시해주는것을 의미하기도 함
5) select[u]를 TRUE로 해주는 것으로 노드에서 가장 최소 가중값을 가진 엣지를 방문표시하여 중복방문을 방지
6) weight[u][v]에서 u행의 v열들을 모두 접근하여 최솟값을 찾음(u노드에서 최소경로를 찾아 dist[v]에 저장)
#dist[v]에 저장하는 이유는 같은 v노드를 가리키는 가중값중에서 더 작은 값을 가진 경로가 있을경우 바꿔주기 위함
*/