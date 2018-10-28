#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct tagNode {
	int element;
	struct tagNode *nextNode;
}Node;

typedef struct SingleLinkedList {
	Node *Head;
	Node *Tail;
}List;

List* createList() {
	List *tmp = (List*)malloc(sizeof(List));
	tmp->Head = NULL;
	tmp->Tail = NULL;
	return tmp;
}

Node* createNode(int element) {
	Node *tmp = (Node*)malloc(sizeof(Node));
	tmp->element = element;
	tmp->nextNode = NULL;
	return tmp;
}

void addLast(List *L, Node *node) {
	if (L->Head == NULL) {
		L->Head = node;
		L->Tail = node;
	}
	else {
		L->Tail->nextNode = node;
		L->Tail = L->Tail->nextNode;
	}
}
Node* deleteFirst(List *L) {
	Node *tmp = L->Head;
	if (L->Head->nextNode == NULL) L->Head = NULL;
	else {
		L->Head = L->Head->nextNode;
	}
	return tmp;
}

void printList(List *L) {
	Node* tmp = L->Head;
	while (tmp != NULL) {
		printf("%d ", tmp->element);
		tmp = tmp->nextNode;
	}
}

List* mergeList(List *L1, List *L2) {
	List *L = createList();
	while (L1->Head != NULL && L2->Head != NULL) {
		if (L1->Head->element <= L2->Head->element) {
			addLast(L, deleteFirst(L1));
		}
		else {
			addLast(L, deleteFirst(L2));
		}
	}
	while (L1->Head != NULL) {
		addLast(L, deleteFirst(L1));
	}
	while (L2->Head != NULL) {
		addLast(L, deleteFirst(L2));
	}
	return L;
}

List* PartitionAndMerge(List *L, int k) {
	if (k > 1)
	{
		int i;
		List *L1 = createList();
		List *L2 = createList();
		L1->Head = L->Head;//처음원소.
		L1->Tail = L->Head;//처음원소.
		for (i = 0; i < k / 2 - 1; i++) {
			L1->Tail = L1->Tail->nextNode;
		}
		L2->Head = L1->Tail->nextNode;//두번째
		L1->Tail->nextNode = NULL;
		//=======partition=======//
		L1 = PartitionAndMerge(L1, k / 2);
		L2 = PartitionAndMerge(L2, k - k / 2);
		L = mergeList(L1, L2);
		//========merge========//
		free(L1), free(L2);
	}
	return L;
}

int main() {
	int n, i;
	scanf("%d", &n);
	List *list = createList();
	for (i = 0; i < n; i++) {
		int x;
		scanf("%d", &x);
		Node *tmp = createNode(x);
		addLast(list, tmp);
	}//입력
	List *L = PartitionAndMerge(list, n);
	printf("답 : ");
	printList(L);
	scanf("%d", &i);

	return 0;
}
