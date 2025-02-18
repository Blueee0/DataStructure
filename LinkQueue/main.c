#include <stdio.h>
#include <stdlib.h>
#include "HEAD.h"

#define MAXQSIZE 100	// �����г���
typedef struct Qnode {
	QElemType data;
	struct Qnode* next;
}QNode, * QueuePtr;

typedef struct {
	QueuePtr front;	//��ͷָ��
	QueuePtr rear;	//��βָ��
}LinkQueue;

// �����г�ʼ��
Status InitQueue(LinkQueue* Q) {
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front)
		exit(OVERFLOW);		//�ڴ����ʧ��
	Q->front->next = NULL;	//ʹ�ýڵ�next��ΪNULL
	return OK;
}

// �����е�����
Status Destroy(LinkQueue* Q) {
	while (Q->front) {
		QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
		p = Q->front->next;
		free(Q->front);
		Q->front = p;
	}
	return OK;
}

// ���
Status Entry(LinkQueue* Q, QElemType e) {
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
		exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
	return OK;
}

// ����
Status Out(LinkQueue* Q, QElemType* e) {
	if (Q->front == Q->rear)
		return ERROR;		// �ӿ�
	QueuePtr p = Q->front->next;
	*e = p->data;
	Q->front->next = p->next;
	if (Q->rear == p)		//���ɾ���Ľڵ�Ϊ��β����ô�ͷ�pfree֮��rearָ��δ֪�洢�ռ�
		Q->rear = Q->front;
	free(p);
	return OK;
}

// ȡ��ͷԪ��
Status GetHead(LinkQueue Q, QElemType* e) {
	if (Q.front == Q.rear)
		return ERROR;
	*e = Q.front->next->data;
	return OK;
}

// ���¾�Ϊ���Ժ���
int main()
{
	LinkQueue Q;
	InitQueue(&Q);
	Entry(&Q, 'A');
	Entry(&Q, 'B');
	Entry(&Q, 'N');
	Entry(&Q, 'M');
	printf("%d\n", LengthQueue(&Q));
	QElemType e;
	while (!(IsEmpty(&Q))) {
		Out(&Q, &e);
		printf("%c ", e);
	}
	system("pause");
	return 0;
}
