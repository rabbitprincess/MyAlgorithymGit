#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct tagVertex {
	int num;
	int fresh;//방문했던 노드였는지 확인하기 위함
	int height;
	struct tagNode *head;
}Vert;//정점

typedef struct tagNode {
	struct tagNode* nextNode;
	struct tagEdge* edge;
	struct tagVertex* vert;
}Node;

typedef struct tagEdge {
	int weight;//간선의 우선순위. 지금은 의미없음.
	int fresh;//방문했던 노드였는지 확인하기 위함
	Vert* vert1;
	Vert* vert2;
}Edge;//간선


void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
Node* makeNode(Vert* vert, Edge* edge) {
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->edge = edge;
	tmp->vert = vert;
	tmp->nextNode = NULL;
	return tmp;
}
Vert* opposite(Edge *edge, Vert* vert) {
	if (edge->vert1 != vert) return edge->vert1;
	else return edge->vert2;
}
void insertNode(Vert* vert, Edge* edge) {
	Node* tmp = vert->head;
	Vert* x = opposite(edge,vert);
	while (tmp->nextNode != NULL) {
		Vert* x2 = opposite(tmp->nextNode->edge, vert);
		if (x->num < x2->num) break;
		tmp = tmp->nextNode;
	}
	Node *tmp2 = makeNode(vert, edge);
	tmp2->nextNode = tmp->nextNode;
	tmp->nextNode = tmp2;
}


Vert** makeVertex(int N) {
	Vert** tmp = (Vert**)calloc(sizeof(Vert*), (N + 1));
	int i;
	for (i = 0; i < N; i++) {
		tmp[i] = (Vert*)malloc(sizeof(Vert));
		tmp[i]->num = i + 1;
		tmp[i]->fresh = 0;
		tmp[i]->height = 0;
		tmp[i]->head = makeNode(tmp[i], NULL);//dummy head Node 추가
	}
	return tmp;
}

Edge* makeEdgeNode(int a, int b, Vert** vert) {
	Edge* edge = (Edge*)malloc(sizeof(Edge));
	if (a < b) swap(&a, &b);//a는 b와 같거나 작음.
	edge->vert1 = vert[a - 1];
	edge->vert2 = vert[b - 1];
	edge->fresh = 0;//아직 방문하지 않음
	edge->weight = 0; //dummy
	return edge;
}

Edge** makeEdge(Vert** vert, int M) {
	int i;
	Edge** edge = (Edge**)malloc(sizeof(Edge*)*M);

	for (i = 0; i < M; i++) {
		int a, b;

		scanf("%d %d", &a, &b);
		edge[i] = makeEdgeNode(a, b, vert);
		insertNode(vert[a - 1], edge[i]);
		if (edge[i]->vert1 != edge[i]->vert2) insertNode(vert[b - 1], edge[i]);
	}//간선과 노드의 초기화.
	return edge;
}



void DFS(Vert* vert) {
	printf("%d\n", vert->num);
	vert->fresh = 1;//노드가 사용되었다는 것을 표시.
	Node* tmp = vert->head;
	while (tmp->nextNode != NULL) {
		tmp = tmp->nextNode;
		if (tmp->edge->fresh == 0)
		{
			tmp->edge->fresh = 1;
			Vert* op = opposite(tmp->edge, tmp->vert);
			if(op->fresh == 0) DFS(op);
		}
	}
}
void DepthFirstSearch(Vert** vert, Edge** edge, int N, int M, int S) {
	int i;
	for (i = 0; i < N; i++) {
		vert[i]->fresh = 0;
	}//vert initialization
	for (i = 0; i < M; i++) {
		edge[i]->fresh = 0;
	}//edge initialization
	DFS(vert[S - 1]);
	for (i = 0; i < N; i++) {
		if(vert[i]->fresh == 0) DFS(vert[i]);
	}//동떨어져 있는 노드가 있는지 확인
}



void BFS(Vert* vert, int N) {
	vert->fresh = 1;
	Vert** Queue = (Vert**)calloc(sizeof(Vert*), N);
	int start = 0, end = 0;//힙 노드 배열에 노드를 추가하기 위한 변수. 처음에는 한개 들어있음.
	Queue[end] = vert;//처음 초기화.
	end++;
	while (start < end) {	
		Node* tmp = Queue[start]->head;
		start++;
		printf("%d\n", tmp->vert->num);
		while (tmp->nextNode != NULL) {
			tmp = tmp->nextNode;
			if (tmp->edge->fresh == 1) continue;
			Vert* op = opposite(tmp->edge,tmp->vert);
			if (op->fresh == 0) {
				tmp->edge->fresh = 1;
				op->fresh = 1;
				Queue[end] = op;
				end++;
			}
		}
	}
	free(Queue);
}
void BreadthFirstSearch(Edge** edge, Vert** vert, int N, int M, int S) {
	int i;
	for (i = 0; i < N; i++) {
		vert[i]->fresh = 0;
	}//vert initialization
	for (i = 0; i < M; i++) {
		edge[i]->fresh = 0;
	}//edge initialization
	BFS(vert[S - 1],N);
	for (i = 0; i < N; i++) {
		if (vert[i]->fresh == 0) BFS(vert[i], N);
	}
}

void printEdge(Vert** vert) {
	int n;
	scanf("%d", &n);
	Node *tmp = vert[n]->head->nextNode;
	while (tmp != NULL) {
		int result;
		if (tmp->edge->vert1->num == vert[n]->num) result = tmp->edge->vert2->num;
		else result = tmp->edge->vert1->num;
		printf(" %d 가중치: %d\n", result, tmp->edge->weight);
		tmp = tmp->nextNode;
	}
}

int main() {
	int N, M, S, i;
	printf("노드 숫자와 간선 숫자, 순회를 시작할 숫자를 입력해주세요:\n");//리스트 형식으로도 만들 수 있다.
	scanf("%d %d %d", &N, &M, &S);//노드 숫자,간선 숫자,시작하는 노드의 숫자
	Vert** vert = makeVertex(N);
	Edge** edge = makeEdge(vert,M);

	printf("DepthFirstSearch\n");
	DepthFirstSearch(vert,edge, N, M, S);
	printf("\nBreadthFirstSearch\n");
	BreadthFirstSearch(edge, vert, N, M, S);
	return 0;
}
