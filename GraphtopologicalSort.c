#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 999999999;

typedef struct tagVertex {
	int vertNum;
	int level;//기준 범위에서 얼마나 비용이 필요한지
	struct tagEdge* parent;//트리에서 자신의 부모 간선
}Vert;

typedef struct tagEdge {
	int height;//가중치
	struct tagVertex* vert1;
	struct tagVertex* vert2;
}Edge;

Vert* opposite(Edge *edge, Vert* vert) {

	if (edge->vert1 == vert) return edge->vert2;
	else return edge->vert1;
}


Vert* removeMin(Vert** queue, int x) {
	int min = MAX, mini = 0, i;
	Vert* minVert;
	for (i = 0; i < x; i++) {
		if (min > queue[i]->level) {
			min = queue[i]->level;
			minVert = queue[i];
			mini = i;
		}
	}
	for (i = mini; i < x - 1; i++) {
		queue[i] = queue[i + 1];
	}
	return minVert;
}//왼쪽으로 갈 수록 큼.


int main() {
	int i, j, N, M;
	int **arr;
	Edge **edge;//간선과 가중치 포함하는 행렬
	Vert **vert;
	scanf("%d %d\n", &N, &M);
	arr = (int**)malloc(sizeof(int*)*N);
	edge = (Edge**)malloc(sizeof(Edge*)*M);//M개의 간선
	vert = (Vert**)malloc(sizeof(Vert*)*N);//N개의 정점


	for (i = 0; i < N; i++) {
		arr[i] = (int*)malloc(sizeof(int)*N);
		vert[i] = (Vert*)calloc(sizeof(Vert), N);
		vert[i]->level = 9999999;//max로 설정.
		vert[i]->parent = NULL;//부모는 NULL로 설정.
		vert[i]->vertNum = i + 1;
		for (j = 0; j < N; j++) {
			arr[i][j] = 0;//간선은 없는 것으로, 가중치는 0으로 초기화
		}
	}//정점 초기화
	for (i = 0; i < M; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		arr[x - 1][y - 1] = i + 1, arr[y - 1][x - 1] = i + 1;
		//i번째 edge라는 소리. edge[i]로 찾을수있음.
		edge[i] = (Edge*)malloc(sizeof(Edge));
		edge[i]->height = z;
		edge[i]->vert1 = vert[x - 1];
		edge[i]->vert2 = vert[y - 1];
	}//간선 초기화

	Vert** queue = (Vert**)malloc(sizeof(Vert*)*N);//N개를 넣을 수 있는 queue 설정
	int x = 0;//큐에 들어가 있는 원소가 몇개인지 알려줌. 한개도 없을 때 0
	vert[0]->level = 0;//0번 정점의 level은 0

	for (i = 0; i < N; i++) {
		queue[x] = vert[i];
		x++;
	}
	int result = 0;
	while (x > 0) {
		int flag = 0;
		Vert* u = removeMin(queue, x);
		printf(" %d", u->vertNum);
		x--;
		if (u->parent != NULL) {
			//			printf("%dㅇㅇㅇㅇㅇㅇ\n", u->parent->height);
			result += u->parent->height;
		}
		for (i = 0; i<N; i++) {
			if (arr[u->vertNum - 1][i] != 0) {
				Vert* tmp = opposite(edge[arr[u->vertNum - 1][i] - 1], u);

				flag = -1;
				for (j = 0; j < x; j++) {
					if (queue[j] == tmp) {
						flag = j;
						break;
					}
				}
				if (flag == -1) continue;
				if (tmp->level > edge[arr[u->vertNum - 1][i] - 1]->height) {
					tmp->level = edge[arr[u->vertNum - 1][i] - 1]->height;
					tmp->parent = edge[arr[u->vertNum - 1][i] - 1];
					queue[flag]->level = edge[arr[u->vertNum - 1][i] - 1]->height;
				}
			}
		}

	}
	printf("\n%d", result);
	scanf("%d", &i);
	return 0;
}