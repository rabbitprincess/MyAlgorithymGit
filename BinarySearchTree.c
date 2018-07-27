#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct tagNode {
	int element;
	struct tagNode *left;
	struct tagNode *right;
}Node;

Node* createNode(int element,Node *left,Node *right){
	Node *tmp = (Node*)malloc(sizeof(Node));
	tmp->element = element;
	tmp->left = left;
	tmp->right = right;
	return tmp;
}
Node* searchNode(int element,Node *tmp) {
	if (tmp == NULL) {
		printf("찾는 원소가 없습니다.\n");
		return NULL;
	}
	if (element == tmp->element) {
		printf("찾았습니다. 노드를 반환합니다\n");
		return tmp;
	}
	else if (tmp->element<element){
		searchNode(element, tmp->right);
	}
	else {
		searchNode(element, tmp->left);
	}
}
void appendNode(int element,Node *root) {
	Node *tmp;
	if(element>root->element){
		if (root->right == NULL)
		{
			tmp = createNode(element,NULL,NULL);
			root->right = tmp;
		}
		else appendNode(element, root->right);
	}
	else if (element < root->element) {
		if (root->left == NULL) {
			tmp = createNode(element, NULL, NULL);
			root->left = tmp;
		}
		else appendNode(element, root->left);
	}
	else printf("이미 그 원소가 트리 안에 있습니다.\n");
}
Node* deleteNode(int element,Node *parent,Node *tmp) {
	Node *Removed;
	if (tmp == NULL) printf("삭제할 노드가 없습니다");
	else {
		if (tmp->element > element) Removed = deleteNode(element,tmp, tmp->left);
		else if (tmp->element < element) Removed = deleteNode(element,tmp, tmp->right);
		else//목표를 찾았을 때
		{
			Removed = tmp;
			if (tmp->left == NULL && tmp->right == NULL) {
				if (parent->left == tmp) {
					parent->left = NULL;
				}
				else parent->right = NULL;
				free(tmp);
			}//no children
			else if (tmp->left != NULL && tmp->right != NULL) {
				Node *min = tmp->right;//오른쪽 노드중 가장 작은거.
				while (min->left != NULL) min = min->left;
				int x = min->element;
				Removed = deleteNode(min->element,NULL, tmp);
				tmp->element = x;
			}//two children
			else {
				Node *tmp2 = NULL;
				if(tmp->left != NULL)
					tmp2 = tmp->left;
				else tmp2 = tmp->right;
				if (parent->left == tmp) parent->left = tmp2;
				else parent->right = tmp2;//tmp의 외자식 노드를 부모노드에 연결 
				free(tmp);
			}//one child
		}
	}
	return Removed;
}
void printTree(Node *tmp) {
	
	if (tmp->left != NULL)
		printTree(tmp->left);
	printf("%d ", tmp->element);
	if (tmp->right != NULL)
		printTree(tmp->right);
}//중위순회로 출력

int main() {
	int i, x;
	Node *tmp;
	Node *root = createNode(-1,NULL,NULL);//루트 생성
	while(1){
		if(root->element == -1){
			printf("기준점 작성하세요:");
			scanf("%d",&root->element);
		}//첫 기준점 작성

		printf("1 : 트리 추가, 2 : 트리 삭제, 3 : 트리 검색, 4:트리 출력, 나머지 : 종료\n");
		scanf("%d", &x);

		switch (x) {
		case 1: {
			printf("추가할 트리의 element를 적어주세요:");
			scanf("%d", &i);
			appendNode(i,root);
			break;
		}
		case 2: {
			printf("삭제할 트리의 element를 적어주세요:");
			scanf("%d", &i);
			tmp = deleteNode(i,root,root);
			break;
		}
		case 3: {
			printf("찾을 트리의 element를 적어주세요:");
			scanf("%d", &i);
			tmp = searchNode(i, root);
			break;
		}
		case 4: {
			printf("트리 출력\n");
			printTree(root);
			printf("\n");
			break;
		}
		default: return;
		}
	}

	return 0;
}