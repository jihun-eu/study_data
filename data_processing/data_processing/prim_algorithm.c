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
//dist�� �ǹ̴� weight[u][v]���� u�� �����Ҷ����� u���� v������ ���� ���� ����� �ε������� ã�� dist�� �ε����� �־��ִ� ���̴�.
//�ش� ��忡 ����Ǿ��ִ� �ּ� ������ dist�� ��������ִ°�
/*
�ǹ̸� ����
1) dist���� INF��, select���� false�� ��� init
2) dist[s]�� 0�� ������ �ڱ��ڽ��� ��ȸ�ϴ� ��δ� ������ �ǹ��ϴ°�
3) u=get_min_vertex(n)���� �ش��ο��� �ּڰ��� �����Ѵ�.
4) ó������ dist[s]�ܿ� ���� INF�� �Ǿ��ֱ⿡ dist[s]�� ���۳�带 ������ִ°��� �ǹ��ϱ⵵ ��
5) select[u]�� TRUE�� ���ִ� ������ ��忡�� ���� �ּ� ���߰��� ���� ������ �湮ǥ���Ͽ� �ߺ��湮�� ����
6) weight[u][v]���� u���� v������ ��� �����Ͽ� �ּڰ��� ã��(u��忡�� �ּҰ�θ� ã�� dist[v]�� ����)
#dist[v]�� �����ϴ� ������ ���� v��带 ����Ű�� ���߰��߿��� �� ���� ���� ���� ��ΰ� ������� �ٲ��ֱ� ����
*/