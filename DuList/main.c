#include <stdio.h>
#include <stdlib.h>
#include "head.h"

typedef struct DulNode {
	ElemType		data;
	struct DulNode* prior;
	struct DulNode* next;
}DuLNode, * DuLinkList;

// ��ʼ��������һ���յ�˫������
void InitDL(DuLinkList L) {
	L = (DuLinkList)malloc(sizeof(DuLNode));
	L->next = NULL;
	L->prior = NULL;
}


// ����˫������
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

// ����Ԫ�أ��ڴ�ͷ����˫��ѭ������L�У���position��λ��֮ǰ����Ԫ��e
Status Insert(DuLinkList L, int position, ElemType e) {
	DuLinkList p = L;
	int i = 0;
	while (p->next != NULL && i < position ) {
		i++;
		p = p->next;
	}
	if (p->next || i > position) {
		printf("����λ�÷Ƿ�");
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

// ɾ��Ԫ�أ��ڴ�ͷ����˫��ѭ������L�У���position��λ��ɾ��Ԫ��
Status Delete(DuLinkList L, int position) {
	DuLinkList p = L;
	int i = 0;
	while (p->next != NULL && i < position) {
		i++;
		p = p->next;
	}
	if (p->next || i > position) {
		printf("ɾ��λ�÷Ƿ�");
		return ERROR;
	}
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
	return OK;
}

 