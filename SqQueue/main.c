#include <stdio.h>
#include <stdlib.h>
#include "head.h"

#define MAXQSIZE 100	// �����г���
typedef struct __SqQueue {
	QElemType* base;	// ��ʼ����̬����洢�ռ�
	int front;			// ͷָ��
	int rear;			// βָ��(rear�±��λ�ò����Ԫ��)
} SqQueue;

// ˳����г�ʼ��
Status InitQueue(SqQueue* Q) {
	Q->base = (QElemType*)malloc(sizeof(QElemType) * MAXQSIZE);	// ��������ռ�
	if (!Q->base)
		exit(OVERFLOW);			// �洢����ʧ��
	Q->front = Q->rear = 0;		// ͷָ��βָ����Ϊ�㣬����Ϊ��
	return OK;
}

// ����г���
int LengthQueue(SqQueue* Q) {
	return ((Q->rear - Q->front + MAXQSIZE) % MAXQSIZE );
}

// �ж�Ϊ��
Status IsEmpty(SqQueue* Q) {
	if (Q->front == Q->rear)
		return TRUE;
	else
		return FALSE;
}

// ���Entry
Status Entry(SqQueue* Q,QElemType e) {
	if ((Q->rear + 1) % MAXQSIZE == Q->front) 
		return OVERFLOW;				//��ʾ����
	Q->base[Q->rear] = e;				//��Ԫ�ؼ����β
	Q->rear = (Q->rear + 1) % MAXQSIZE;	//��βָ��+1
	return OK;
}

// ����Out
Status Out(SqQueue* Q,QElemType *e) {
	if (Q->front == Q->rear) 
		return ERROR;						//�ӿ�
	*e = Q->base[Q->front];					//�����ͷԪ��
	Q->front = (Q->front + 1) % MAXQSIZE;	//��ͷָ��+1
	return OK;
}

// ȡ��ͷԪ��
QElemType GetHead(SqQueue Q) {
	if (Q.front != Q.rear)		//���в�Ϊ��
		return Q.base[Q.front];	//���ض�ͷԪ�ص�ֵ
}

// ���¾�Ϊ���Ժ���
int main() 
{
	SqQueue Q;
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

