#include <stdio.h>
#include <stdlib.h>
#include "head.h"

#define MAXQSIZE 100	// 最大队列长度
typedef struct __SqQueue {
	QElemType* base;	// 初始化动态分配存储空间
	int front;			// 头指针
	int rear;			// 尾指针(rear下标的位置不存放元素)
} SqQueue;

// 顺序队列初始化
Status InitQueue(SqQueue* Q) {
	Q->base = (QElemType*)malloc(sizeof(QElemType) * MAXQSIZE);	// 分配数组空间
	if (!Q->base)
		exit(OVERFLOW);			// 存储分配失败
	Q->front = Q->rear = 0;		// 头指针尾指针置为零，队列为空
	return OK;
}

// 求队列长度
int LengthQueue(SqQueue* Q) {
	return ((Q->rear - Q->front + MAXQSIZE) % MAXQSIZE );
}

// 判断为空
Status IsEmpty(SqQueue* Q) {
	if (Q->front == Q->rear)
		return TRUE;
	else
		return FALSE;
}

// 入队Entry
Status Entry(SqQueue* Q,QElemType e) {
	if ((Q->rear + 1) % MAXQSIZE == Q->front) 
		return OVERFLOW;				//表示队满
	Q->base[Q->rear] = e;				//新元素加入队尾
	Q->rear = (Q->rear + 1) % MAXQSIZE;	//队尾指针+1
	return OK;
}

// 出队Out
Status Out(SqQueue* Q,QElemType *e) {
	if (Q->front == Q->rear) 
		return ERROR;						//队空
	*e = Q->base[Q->front];					//保存队头元素
	Q->front = (Q->front + 1) % MAXQSIZE;	//队头指针+1
	return OK;
}

// 取队头元素
QElemType GetHead(SqQueue Q) {
	if (Q.front != Q.rear)		//队列不为空
		return Q.base[Q.front];	//返回队头元素的值
}

// 以下均为测试函数
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

