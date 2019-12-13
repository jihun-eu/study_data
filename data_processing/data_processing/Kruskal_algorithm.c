#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100  // �׷����� ������ ����
#define INF 1000      // ��ΰ� �������� ������ ����
#define MAX_ELEMENT 100   // ������ �ִ�ũ��

/* union find*/
int parent[MAX_VERTICES]; // �� ������ �θ� ���
int num[MAX_VERTICES];    // �� ������ ũ��

// �ʱ�ȭ
void set_init(int n)
{
	int i;

	// 0 ~ n-1 �ε������� �θ��� �迭�� ��� -1��
	// ������ ũ�� �迭�� ��� 1�� �ʱ�ȭ�Ѵ�.
	for (i = 0; i < n; i++)
	{
		parent[i] = -1;
		num[i] = 1;
	}
}

// ����(vertex)�� ���ϴ� ������ ��ȯ�Ѵ�.
int set_find(int vertex)
{
	int p, s, i = -1; // p: �θ���

	// ��Ʈ������ �ݺ��Ѵ�. p�� -1�� �Ǹ� �ݺ����� �����Ѵ�.
	// p�� -1�̶�� �� ���� ���(i)�� ��Ʈ��� ���̴�.
	// �츮�� ������ ��Ʈ����� �θ�� -1�� �����ߴ�.
	for (i = vertex; (p = parent[i]) >= 0; i = p);

	s = i;  // ��Ʈ��� ������ s�� ����

	// vertex�� ��������� s(��Ʈ ���)�� ���ϰԲ� �����Ѵ�.
	for (i = vertex; (p = parent[i]) >= 0; i = p)
		parent[i] = s;

	return s; // ��� ����� �θ��� ��Ʈ�� ��ȯ�Ѵ�.
}

// �� ���� ������ ũ�� ���� s1, s2�� �޾� �� ������ ��ģ��.
void set_union(int s1, int s2)
{
	// �� ū ���� �������� ������ ��ģ��.
	if (num[s1] < num[s2])
	{
		// ���� s2�� �� ũ�ٸ�
		parent[s1] = s2;  // s1�� �θ� s2�� ����
		num[s2] += num[s1]; // s2�� ũ�⸦ s1��ŭ �����ش�.
	}
	else
	{
		parent[s2] = s1;
		num[s1] += num[s2];
	}
}

typedef struct
{
	int key;  // ������ ����ġ
	int u;    // ���� 1
	int v;    // ���� 2
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

	/* Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ���� */
	// i�� ��Ʈ�� �ƴϰ� �Է����� ���� item�� key���� i�� �θ��� Ű ������ ������
	while ((i != 1) && (item.key < h->heap[i / 2].key))
	{
		// �Ž����ö󰡾� �ϹǷ� �����带 �θ���� �����ϰ�
		h->heap[i] = h->heap[i / 2];

		// �ε����� �θ����� �ε����� �����Ѵ�.
		i /= 2;
	}
	// Ż���ߴٴ� �� ���̻� �Ž��� �ö� ���� ���ٴ� ���̹Ƿ�
	// ���� �ε����� ��ġ�� item�� �����Ѵ�.
	h->heap[i] = item;
}

element delete_min_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	// �ּ������� Ư���� ��Ʈ��忡 �ִ� ���� ���� �������̹Ƿ�
	// ��ȯ�� ��Ʈ����� ���� item�� �����صд�.
	item = h->heap[1];

	// �� �������� �ִ� ����� ���� temp�� �����ϰ�
	// ��Ʈ����� ������ ������ �������Ƿ� ������� 1 ���δ�.
	temp = h->heap[(h->heap_size)--];

	/* �� ������ ��尪 (temp)�� �̿��� �񱳰��� */
	// temp�� �ϴ� ��Ʈ�� �ξ��ٰ� �����ϰ� �Ʒ� ������ �����Ѵ�.
	// �ּ����� ������ ��Ʈ������ �������� ���� ���ʴ�� ���Ͽ�
	// ������ ��ġ�� ã�� �����ϴ� �۾��̴�.

	parent = 1; // �� ù ������ �θ��带 ��Ʈ�� �д�.
	child = 2; // �׸��� �� ���� �ڽ��� �ڽĳ��� �д�.

	// child�� �� ������� ũ�� ���� ��� ���̹Ƿ� ������ �ȵȴ�.
	// ���� child�� �� ������� �۰ų� ���� �� �񱳰� �Ͼ��.
	while (child <= h->heap_size)
	{
		// �� ���� �ڳ� �� �� ���� �ڳฦ �񱳱������� ��� ���� �Ʒ��� if�� ����
		if (
			// ������ �ڳడ �ִٰ� �����ϸ�, child�� ��������� �۾ƾ� �Ѵ�.
			// ���� �ڳడ ��������� ������ ������ �ڳడ �ִٸ� + 1�� ����� �ϴµ�
			// �׷��� �Ǹ� ������� �Ѿ�� ������ child�� ��������� �۾ƾ� �Ѵ�.
			(child < h->heap_size) &&
			// ������ �ڳ� (child + 1)�� �� �۱� ������ ���ο� �������� ������ֱ� ����
			// child++ �� ���ش�.
			(h->heap[child].key) > h->heap[child + 1].key
			)
			child++;

		// �� ����� child�� ���������� ��Ʈ��忡 ��ġ ���� temp�� ���Ѵ�.
		// temp�� �� �۴ٸ� ��ġ�̵��� �� �ʿ䰡 �����Ƿ� �� �ݺ����� ����������.
		// ���ڸ��� �ִٴ� ���̴�. �ּ������� ���� ���� �θ�� �־�� �Ѵ�.
		if (temp.key <= h->heap[child].key)
			break;

		// ������� �Դٴ� �� temp�� �ڸ���ȯ�� �ʿ��ϴٴ� ���̴�.
		// temp�� ���� ���� ã�� ���� �񱳴���� �� �ܰ� �Ʒ��� �̵��Ѵ�.
		h->heap[parent] = h->heap[child]; // �ڳ��� ���� ���ο� �� �������� �ȴ�.
		parent = child; // �ڳడ �θ�� �ȴ�. (���� �񱳸� ����)
		child *= 2; // 2�� ���Ͽ� ���� �ڳ�� �ȴ�.
	}
	// �� �ݺ����� ����������, parent�� temp�� ��ġ�� ���� �Ǿ� ���� ���̴�.
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

void insert_all_edges(HeapType* h) // ���� �׸��� �׷����� ���ϴ�.
{
	// �ּ������̹Ƿ� ���� ���� ��尡 ��Ʈ���� ��ġ�ϰ� �ȴ�.
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

// kruskal�� �ּ� ��� ���� Ʈ�� �˰���
void kruskal(int n)
{
	int edge_accepted = 0;  // ������� ���õ� ������ ��
	HeapType h;       // �ּ� ����
	int uset, vset;     // ���� u�� ���� v�� ���� ��ȣ
	element e;        // ���� ���

	init(&h);       // ���� �ʱ�ȭ
	insert_all_edges(&h); // ������ �������� ����
	set_init(n);      // ���� �ʱ�ȭ

	while (edge_accepted < (n - 1)) // ������ �� < (n - 1)
	{
		e = delete_min_heap(&h);  // ���� ���� ����ġ�� ���� ȹ��
		// ȹ��ʰ� ���ÿ� �ش� ������ �������� ���ŵȴ�.
		uset = set_find(e.u);   // ���� u�� ���� ��ȣ
		vset = set_find(e.v);   // ���� v�� ���� ��ȣ

		// �� ������ ���� �ٸ� ���տ� ���Ѵٸ�
		if (uset != vset)
		{
			printf("(%d, %d) %d \n", e.u, e.v, e.key);
			edge_accepted++;
			set_union(uset, vset);  // �� ���� ������ ��ģ��.
		}
	}
}

void main()
{
	kruskal(7);
}