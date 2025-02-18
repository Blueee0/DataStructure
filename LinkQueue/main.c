#include <stdio.h>
#include <stdlib.h>
#include "HEAD.h"

#define MAXQSIZE 100	// 最大队列长度
typedef struct Qnode {
	QElemType data;
	struct Qnode* next;
}QNode, * QueuePtr;

typedef struct {
	QueuePtr front;	//队头指针
	QueuePtr rear;	//队尾指针
}LinkQueue;

// 链队列初始化
Status InitQueue(LinkQueue* Q) {
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front)
		exit(OVERFLOW);		//内存分配失败
	Q->front->next = NULL;	//使该节点next域为NULL
	return OK;
}

// 链队列的销毁
Status Destroy(LinkQueue* Q) {
	while (Q->front) {
		QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
		p = Q->front->next;
		free(Q->front);
		Q->front = p;
	}
	return OK;
}

// 入队
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

// 出队
Status Out(LinkQueue* Q, QElemType* e) {
	if (Q->front == Q->rear)
		return ERROR;		// 队空
	QueuePtr p = Q->front->next;
	*e = p->data;
	Q->front->next = p->next;
	if (Q->rear == p)		//如果删除的节点为队尾，那么释放pfree之后，rear指向未知存储空间
		Q->rear = Q->front;
	free(p);
	return OK;
}

// 取队头元素
Status GetHead(LinkQueue Q, QElemType* e) {
	if (Q.front == Q.rear)
		return ERROR;
	*e = Q.front->next->data;
	return OK;
}

// 以下均为测试函数
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
