#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// 二叉链表存储结构
typedef struct BiTNode {
	TElemType data;						//结点数据
	struct BiTNode* lchild, * rchild;	//左右孩子指针
} BiTNode, *BiTree;

// 函数声明
void Create_BiTree_Pre(BiTree* T);		// 创建二叉链表
void visit(BiTree T);					// 访问结点数据
void PreOrder(BiTree T);				// 先序遍历
void InOrder(BiTree T);					// 中序遍历
void PostOrder(BiTree T);				// 后序遍历
void Degree_one(BiTree T);				// 输出度为1的节点
int Depth(BiTree T);					// 求二叉链树的深度

// 测试函数
int main() {
	// 初始化创建二叉链树
	BiTree T = NULL;
	printf("当前采用先序遍历创建二叉树，使用'#'表示空节点\n");
	Create_BiTree_Pre(&T);	// 采用先序遍历的方式创建二叉树

	printf("当前采用中序遍历输出二叉树\n");
	InOrder(T);				// 采用中序遍历输出
	printf("\n");

	printf("当前采用后序遍历输出二叉树\n");
	PostOrder(T);			// 采用后序遍历输出
	printf("\n");

	printf("当前二叉树中，度为1的结点有\n");
	Degree_one(T);
	printf("\n");

	int depth = Depth(T);
	printf("当前二叉树的深度为：%d",depth);
	printf("\n");

	return 0;
}

// 创建二叉链表
void Create_BiTree_Pre(BiTree* T) {
	TElemType e = NULL;
	scanf_s("%c", &e);      // 输入结点的值
	if (e == '#')           // 用"#"表示空节点
		*T = NULL;
	else {
		*T = (BiTree)malloc(sizeof(BiTNode));
		(*T)->data = e;
		Create_BiTree_Pre(&(*T)->lchild);
		Create_BiTree_Pre(&(*T)->rchild);
	}
}

// 访问结点数据
void visit(BiTree T) {
	if (T->data=='#')
		return;
	else {
		printf("%c", T->data);
		return;
	}
}

// 先序遍历
void PreOrder(BiTree T) {
	if (T != NULL) {
		visit(T);				//访问根节点
		PreOrder(T->lchild);	//递归遍历左子树
		PreOrder(T->rchild);	//递归遍历右子树
	}
}

// 中序遍历
void InOrder(BiTree T) {
	if (T != NULL) {
		InOrder(T->lchild);	//递归遍历左子树
		visit(T);			//访问根结点
		InOrder(T->rchild);	//递归遍历右子树
	}
}

// 后序遍历
void PostOrder(BiTree T) {
	if (T != NULL) {
		PostOrder(T->lchild);	//递归遍历左子树
		PostOrder(T->rchild);	//递归遍历右子树
		visit(T);				//访问根结点
	}
}


// 输出度为1的节点
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

// 求二叉树的深度
int Depth(BiTree T) {
	if (!T)
		return 0;
	else {
		return Depth(T->lchild) > Depth(T->rchild) ? Depth(T->lchild) + 1 : Depth(T->rchild) + 1;
	}
}