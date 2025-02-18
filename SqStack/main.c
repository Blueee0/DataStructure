#include <stdio.h>
#include <stdlib.h>
#include "head.h"

#define MAXSTACK 100
typedef struct __SqStack {
	StackElemType* base;	// ջ��ָ��
	StackElemType* top;		// ջ��ָ��
	int stacksize;			// ջ�����������
} SqStack;

// ջ�ĳ�ʼ��
Status InitStack(SqStack* S) {	// ����һ����ջ
	S->base = (StackElemType*)malloc(MAXSTACK * sizeof(StackElemType));
	if (!S->base)
		exit(OVERFLOW);	//�洢����ʧ��
	S->top = S->base;	//ջ��ָ�����ջ��ָ��
	S->stacksize = MAXSTACK;
	return OK;
}

// �ж�ջΪ��
Status IsEmpty(SqStack S) {		//��ջΪ�գ�����TRUE�����򷵻�FALSE
	if (S.top == S.base)
		return TRUE;
	else
		return FALSE;
}

// ��ջ�ĳ���
int Get_length(SqStack S) {
	return S.top - S.base;
}

// ���˳��ջ
Status Clear(SqStack S) {
	if (S.base)
		S.top = S.base;
	return OK;
}

// ����˳��ջ
Status Destroy(SqStack* S) {
	if (S->base) {
		free(S->base);
		S->stacksize = 0;
		S->base = S->top = NULL;
	}
	return OK;
}

// ��ջPush
Status Push(SqStack* S,StackElemType e) {
	if (S->top - S->base == S->stacksize) {
		return OVERFLOW;	// ջ��
	}
	*(S->top++) = e;			// topָ���ڴ浥Ԫ���e����topָ����һ���ڴ浥Ԫ
	// �൱��
	// *S->top = e;
	// S->top++;
	return OK;
}

// ��ջPop
Status Pop(SqStack* S,StackElemType *e) {
	if (S->top == S->base)
		return OVERFLOW;	// ����
	*e = *(--(S->top));
	//�൱��
	//--(S->top);
	//*e = *S->top;
	return OK;
}

// ���¾�Ϊ���Ժ���
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