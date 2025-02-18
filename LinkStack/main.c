#include<stdio.h>
#include<stdlib.h>
#include "head.h"

typedef struct StackNode {
	StackElemType data;
	struct StackNode* next;
}StackNode, * LinkStack;

// 链栈的初始化
Status InitStack(LinkStack* S) {
	*S = NULL;
	return OK;
}

// 判断链栈为空
Status IsEmpty(LinkStack* S) {
	if (*S == NULL)
		return TRUE;
	else
		return FALSE;
}

// 入栈Push
Status Push(LinkStack* S, StackElemType e) {
	LinkStack pnew = (LinkStack)malloc(sizeof(StackNode));
	pnew->data = e;		// 将新结点的数据域置为e
	pnew->next = *S;	// 将新结点插入栈顶
	*S = pnew;			// 修改栈顶指针
	return OK;
}

// 出栈Pop
Status Pop(LinkStack* S, StackElemType* e) {
	LinkStack p = *S;	//临时保存栈顶节点S
	*e = (*S)->data;
	*S = (*S)->next;
	free(p);			//出栈后释放
	return OK;
}

// 获取栈顶元素
StackElemType GetTop(LinkStack* S) {
	if (*S)
		return (*S)->data;
}


// 以下均为测试函数
int main(void)
{
	LinkStack S;
	InitStack(&S);
	Push(&S, 'E');
	Push(&S, 'A');
	Push(&S, 'C');
	Push(&S, 'H');
	Push(&S, 'R');
	while (!IsEmpty(&S))
	{
		StackElemType e;
		Pop(&S, &e);
		printf("%c ", e);
	}
	system("pause");
	return 0;
}