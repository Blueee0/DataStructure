#include <stdio.h>
#include <stdlib.h>
#include "head.h"

#define MAXSTACK 100
typedef struct __SqStack {
	StackElemType* base;	// 栈底指针
	StackElemType* top;		// 栈顶指针
	int stacksize;			// 栈可用最大容量
} SqStack;

// 栈的初始化
Status InitStack(SqStack* S) {	// 构建一个空栈
	S->base = (StackElemType*)malloc(MAXSTACK * sizeof(StackElemType));
	if (!S->base)
		exit(OVERFLOW);	//存储分配失败
	S->top = S->base;	//栈顶指针等于栈底指针
	S->stacksize = MAXSTACK;
	return OK;
}

// 判断栈为空
Status IsEmpty(SqStack S) {		//若栈为空，返回TRUE；否则返回FALSE
	if (S.top == S.base)
		return TRUE;
	else
		return FALSE;
}

// 求栈的长度
int Get_length(SqStack S) {
	return S.top - S.base;
}

// 清空顺序栈
Status Clear(SqStack S) {
	if (S.base)
		S.top = S.base;
	return OK;
}

// 销毁顺序栈
Status Destroy(SqStack* S) {
	if (S->base) {
		free(S->base);
		S->stacksize = 0;
		S->base = S->top = NULL;
	}
	return OK;
}

// 入栈Push
Status Push(SqStack* S,StackElemType e) {
	if (S->top - S->base == S->stacksize) {
		return OVERFLOW;	// 栈满
	}
	*(S->top++) = e;			// top指向内存单元存放e，且top指向下一个内存单元
	// 相当于
	// *S->top = e;
	// S->top++;
	return OK;
}

// 出栈Pop
Status Pop(SqStack* S,StackElemType *e) {
	if (S->top == S->base)
		return OVERFLOW;	// 下溢
	*e = *(--(S->top));
	//相当于
	//--(S->top);
	//*e = *S->top;
	return OK;
}

// 以下均为测试函数
int main()
{
	SqStack S;
	InitStack(&S);
	Push(&S, 'A');
	Push(&S, 'B');
	Push(&S, 'C');
	Push(&S, 'C');
	while (!IsEmpty(S))
	{
		StackElemType e;
		Pop(&S, &e);
		printf("%c ", e);
	}
	system("pause");
	return 0;
}