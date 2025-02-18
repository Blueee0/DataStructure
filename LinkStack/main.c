#include<stdio.h>
#include<stdlib.h>
#include "head.h"

typedef struct StackNode {
	StackElemType data;
	struct StackNode* next;
}StackNode, * LinkStack;

// ��ջ�ĳ�ʼ��
Status InitStack(LinkStack* S) {
	*S = NULL;
	return OK;
}

// �ж���ջΪ��
Status IsEmpty(LinkStack* S) {
	if (*S == NULL)
		return TRUE;
	else
		return FALSE;
}

// ��ջPush
Status Push(LinkStack* S, StackElemType e) {
	LinkStack pnew = (LinkStack)malloc(sizeof(StackNode));
	pnew->data = e;		// ���½�����������Ϊe
	pnew->next = *S;	// ���½�����ջ��
	*S = pnew;			// �޸�ջ��ָ��
	return OK;
}

// ��ջPop
Status Pop(LinkStack* S, StackElemType* e) {
	LinkStack p = *S;	//��ʱ����ջ���ڵ�S
	*e = (*S)->data;
	*S = (*S)->next;
	free(p);			//��ջ���ͷ�
	return OK;
}

// ��ȡջ��Ԫ��
StackElemType GetTop(LinkStack* S) {
	if (*S)
		return (*S)->data;
}


// ���¾�Ϊ���Ժ���
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