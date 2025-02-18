#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// ��������洢�ṹ
typedef struct BiTNode {
	TElemType data;						//�������
	struct BiTNode* lchild, * rchild;	//���Һ���ָ��
} BiTNode, *BiTree;

// ��������
void Create_BiTree_Pre(BiTree* T);		// ������������
void visit(BiTree T);					// ���ʽ������
void PreOrder(BiTree T);				// �������
void InOrder(BiTree T);					// �������
void PostOrder(BiTree T);				// �������
void Degree_one(BiTree T);				// �����Ϊ1�Ľڵ�
int Depth(BiTree T);					// ��������������

// ���Ժ���
int main() {
	// ��ʼ��������������
	BiTree T = NULL;
	printf("��ǰ�����������������������ʹ��'#'��ʾ�սڵ�\n");
	Create_BiTree_Pre(&T);	// ������������ķ�ʽ����������

	printf("��ǰ��������������������\n");
	InOrder(T);				// ��������������
	printf("\n");

	printf("��ǰ���ú���������������\n");
	PostOrder(T);			// ���ú���������
	printf("\n");

	printf("��ǰ�������У���Ϊ1�Ľ����\n");
	Degree_one(T);
	printf("\n");

	int depth = Depth(T);
	printf("��ǰ�����������Ϊ��%d",depth);
	printf("\n");

	return 0;
}

// ������������
void Create_BiTree_Pre(BiTree* T) {
	TElemType e = NULL;
	scanf_s("%c", &e);      // �������ֵ
	if (e == '#')           // ��"#"��ʾ�սڵ�
		*T = NULL;
	else {
		*T = (BiTree)malloc(sizeof(BiTNode));
		(*T)->data = e;
		Create_BiTree_Pre(&(*T)->lchild);
		Create_BiTree_Pre(&(*T)->rchild);
	}
}

// ���ʽ������
void visit(BiTree T) {
	if (T->data=='#')
		return;
	else {
		printf("%c", T->data);
		return;
	}
}

// �������
void PreOrder(BiTree T) {
	if (T != NULL) {
		visit(T);				//���ʸ��ڵ�
		PreOrder(T->lchild);	//�ݹ����������
		PreOrder(T->rchild);	//�ݹ����������
	}
}

// �������
void InOrder(BiTree T) {
	if (T != NULL) {
		InOrder(T->lchild);	//�ݹ����������
		visit(T);			//���ʸ����
		InOrder(T->rchild);	//�ݹ����������
	}
}

// �������
void PostOrder(BiTree T) {
	if (T != NULL) {
		PostOrder(T->lchild);	//�ݹ����������
		PostOrder(T->rchild);	//�ݹ����������
		visit(T);				//���ʸ����
	}
}


// �����Ϊ1�Ľڵ�
void Degree_one(BiTree T) {
	if (T == NULL) {
		return;
	}
	if ((T->lchild == NULL && T->rchild != NULL) || (T->lchild != NULL && T->rchild == NULL)) {
		printf("%c ",T->data);
	}
	Degree_one(T->lchild);
	Degree_one(T->rchild);
}

// ������������
int Depth(BiTree T) {
	if (!T)
		return 0;
	else {
		return Depth(T->lchild) > Depth(T->rchild) ? Depth(T->lchild) + 1 : Depth(T->rchild) + 1;
	}
}