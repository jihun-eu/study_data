#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100  // 그래프의 정점의 개수
#define INF 1000      // 경로가 존재하지 않음을 뜻함
#define MAX_ELEMENT 100   // 히프의 최대크기

/* union find*/
int parent[MAX_VERTICES]; // 각 정점의 부모 노드
int num[MAX_VERTICES];    // 각 집합의 크기

// 초기화
void set_init(int n)
{
	int i;

	// 0 ~ n-1 인덱스까지 부모노드 배열은 모두 -1로
	// 집합의 크기 배열은 모두 1로 초기화한다.
	for (i = 0; i < n; i++)
	{
		parent[i] = -1;
		num[i] = 1;
	}
}

// 정점(vertex)이 속하는 집합을 반환한다.
int set_find(int vertex)
{
	int p, s, i = -1; // p: 부모노드

	// 루트노드까지 반복한다. p가 -1이 되면 반복문은 종료한다.
	// p가 -1이라는 건 현재 노드(i)가 루트라는 뜻이다.
	// 우리는 위에서 루트노드의 부모는 -1로 설정했다.
	for (i = vertex; (p = parent[i]) >= 0; i = p);

	s = i;  // 루트노드 정보를 s에 저장

	// vertex의 조상노드들이 s(루트 노드)를 향하게끔 설정한다.
	for (i = vertex; (p = parent[i]) >= 0; i = p)
		parent[i] = s;

	return s; // 모든 노드의 부모인 루트를 반환한다.
}

// 두 개의 원소의 크기 정보 s1, s2를 받아 두 집합을 합친다.
void set_union(int s1, int s2)
{
	// 더 큰 쪽을 기준으로 집합을 합친다.
	if (num[s1] < num[s2])
	{
		// 집합 s2가 더 크다면
		parent[s1] = s2;  // s1의 부모를 s2로 설정
		num[s2] += num[s1]; // s2의 크기를 s1만큼 더해준다.
	}
	else
	{
		parent[s2] = s1;
		num[s1] += num[s2];
	}
}

typedef struct
{
	int key;  // 간선의 가중치
	int u;    // 정점 1
	int v;    // 정점 2
} element;

typedef struct
{
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

void init(HeapType* h)
{
	h->heap_size = 0;
}

int is_empty(HeapType* h)
{
	if (h->heap_size == 0)
		return TRUE;
	else
		return FALSE;
}

void insert_min_heap(HeapType* h, element item)
{
	int i = ++(h->heap_size);

	/* 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정 */
	// i가 루트가 아니고 입력으로 받은 item의 key값이 i의 부모의 키 값보다 작으면
	while ((i != 1) && (item.key < h->heap[i / 2].key))
	{
		// 거슬러올라가야 하므로 현재노드를 부모노드로 설정하고
		h->heap[i] = h->heap[i / 2];

		// 인덱스를 부모노드의 인덱스로 설정한다.
		i /= 2;
	}
	// 탈출했다는 건 더이상 거슬러 올라갈 곳이 없다는 것이므로
	// 현재 인덱스의 위치에 item을 삽입한다.
	h->heap[i] = item;
}

element delete_min_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	// 최소히프의 특성상 루트노드에 있는 값이 가장 작은값이므로
	// 반환할 루트노드의 값을 item에 저장해둔다.
	item = h->heap[1];

	// 맨 마지막에 있는 노드의 값을 temp에 저장하고
	// 루트노드의 정보를 위에서 빼냈으므로 힙사이즈를 1 줄인다.
	temp = h->heap[(h->heap_size)--];

	/* 맨 마지막 노드값 (temp)를 이용한 비교과정 */
	// temp를 일단 루트에 두었다고 가정하고 아래 과정을 시작한다.
	// 최소히프 삭제는 루트노드부터 말단으로 가며 차례대로 비교하여
	// 적절한 위치를 찾아 삽입하는 작업이다.

	parent = 1; // 맨 첫 실행의 부모노드를 루트로 둔다.
	child = 2; // 그리고 그 왼쪽 자식을 자식노드로 둔다.

	// child가 힙 사이즈보다 크면 힙을 벗어난 비교이므로 실행이 안된다.
	// 따라서 child가 힙 사이즈보다 작거나 같을 때 비교가 일어난다.
	while (child <= h->heap_size)
	{
		// 두 개의 자녀 중 더 작은 자녀를 비교기준으로 삼기 위해 아래의 if문 실행
		if (
			// 오른쪽 자녀가 있다고 생각하면, child는 힙사이즈보다 작아야 한다.
			// 왼쪽 자녀가 힙사이즈와 같은데 오른쪽 자녀가 있다면 + 1을 해줘야 하는데
			// 그렇게 되면 힙사이즈를 넘어서기 때문에 child는 힙사이즈보다 작아야 한다.
			(child < h->heap_size) &&
			// 오른쪽 자녀 (child + 1)이 더 작기 때문에 새로운 기준점을 만들어주기 위해
			// child++ 을 해준다.
			(h->heap[child].key) > h->heap[child + 1].key
			)
			child++;

		// 비교 대상인 child를 설정했으니 루트노드에 위치 중인 temp와 비교한다.
		// temp가 더 작다면 위치이동을 할 필요가 없으므로 이 반복문을 빠져나간다.
		// 제자리에 있다는 뜻이다. 최소히프는 작은 값이 부모로 있어야 한다.
		if (temp.key <= h->heap[child].key)
			break;

		// 여기까지 왔다는 건 temp의 자리교환이 필요하다는 뜻이다.
		// temp가 있을 곳을 찾기 위해 비교대상을 한 단계 아래로 이동한다.
		h->heap[parent] = h->heap[child]; // 자녀의 값이 새로운 비교 기준점이 된다.
		parent = child; // 자녀가 부모로 된다. (다음 비교를 위해)
		child *= 2; // 2를 곱하여 다음 자녀로 된다.
	}
	// 위 반복문을 빠져나오면, parent가 temp가 위치할 곳이 되어 있을 것이다.
	h->heap[parent] = temp;
	return item;
}

void insert_heap_edge(HeapType* h, int u, int v, int weight)
{
	element e;
	e.u = u;
	e.v = v;
	e.key = weight;
	insert_min_heap(h, e);
}

void insert_all_edges(HeapType* h) // 직접 그림을 그려보면 편하다.
{
	// 최소히프이므로 가장 작은 노드가 루트노드로 위치하게 된다.
	insert_heap_edge(h, 0, 1, 29);
	insert_heap_edge(h, 1, 2, 16);
	insert_heap_edge(h, 2, 3, 12);
	insert_heap_edge(h, 3, 4, 22);
	insert_heap_edge(h, 4, 5, 27);
	insert_heap_edge(h, 5, 0, 10);
	insert_heap_edge(h, 6, 1, 15);
	insert_heap_edge(h, 6, 3, 18);
	insert_heap_edge(h, 6, 4, 25);
}

// kruskal의 최소 비용 신장 트리 알고리즘
void kruskal(int n)
{
	int edge_accepted = 0;  // 현재까지 선택된 간선의 수
	HeapType h;       // 최소 히프
	int uset, vset;     // 정점 u와 정점 v의 집합 번호
	element e;        // 히프 요소

	init(&h);       // 히프 초기화
	insert_all_edges(&h); // 히프에 간선들을 삽입
	set_init(n);      // 집합 초기화

	while (edge_accepted < (n - 1)) // 간선의 수 < (n - 1)
	{
		e = delete_min_heap(&h);  // 가장 작은 가중치의 간선 획득
		// 획득됨과 동시에 해당 간선은 히프에서 제거된다.
		uset = set_find(e.u);   // 정점 u의 집합 번호
		vset = set_find(e.v);   // 정점 v의 집합 번호

		// 두 집합이 서로 다른 집합에 속한다면
		if (uset != vset)
		{
			printf("(%d, %d) %d \n", e.u, e.v, e.key);
			edge_accepted++;
			set_union(uset, vset);  // 두 개의 집합을 합친다.
		}
	}
}

void main()
{
	kruskal(7);
}