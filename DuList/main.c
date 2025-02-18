#include <stdio.h>
#include <stdlib.h>
#include "head.h"

typedef struct DulNode {
	ElemType		data;
	struct DulNode* prior;
	struct DulNode* next;
}DuLNode, * DuLinkList;

// 初始化：创建一个空的双向链表
void InitDL(DuLinkList L) {
	L = (DuLinkList)malloc(sizeof(DuLNode));
	L->next = NULL;
	L->prior = NULL;
}


// 创建双向链表
Status CreateDL(DuLinkList L, int length) {
	
	for (int i = 0; i < length; i++) {
		DuLinkList pnew = (DuLinkList)malloc(sizeof(DuLNode));
		int data;
		printf("(for %d)Please input the data:", i + 1);
		scanf_s("%d", &data);
		pnew->data = data;
		pnew->next = L->next;
		pnew->prior = L;
		L->next = pnew;
	}
}
void CreatDL_R(DuLinkList L, int length) {
	DuLinkList ptail = L;
	for (int i = 0; i < length; i++) {
		DuLinkList pnew = (DuLinkList)malloc(sizeof(DuLNode));
		int data;
		printf("(for %d)Please input the data:", i + 1);
		scanf("%d", &data);
		pnew->data = data;
		pnew->next = NULL;
		pnew->prior = ptail;
		ptail->next = pnew;
		ptail = pnew;
	}
}

// 插入元素：在带头结点的双向循环链表L中，第position个位置之前插入元素e
Status Insert(DuLinkList L, int position, ElemType e) {
	DuLinkList p = L;
	int i = 0;
	while (p->next != NULL && i < position ) {
		i++;
		p = p->next;
	}
	if (p->next || i > position) {
		printf("插入位置非法");
		return ERROR;
	}
	DuLinkList pnew = (DuLinkList)malloc(sizeof(DuLNode));
	pnew->data = e;
	pnew->prior = p->prior;
	p->prior->next = pnew;
	pnew->next = p;
	p->prior=pnew;
	return OK;
}

// 删除元素：在带头结点的双向循环链表L中，第position个位置删除元素
Status Delete(DuLinkList L, int position) {
	DuLinkList p = L;
	int i = 0;
	while (p->next != NULL && i < position) {
		i++;
		p = p->next;
	}
	if (p->next || i > position) {
		printf("删除位置非法");
		return ERROR;
	}
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
	return OK;
}

 