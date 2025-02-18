/*
#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// 顺序表的存储结构
#define List_Max_Size 100		//线性表存储空间的最大分配量
typedef struct _Sql {
	ElemType base[List_Max_Size];
	int length;	//当前长度
}SqList;

// 顺序表的函数声明
Status InitSL(SqList* L, int length);					// 初始化操作，建立一个线性表
int Get_length(SqList* L);								// 求线性表L的长度
int Search_Elem(SqList L, ElemType e);					// 查找元素（按值查找）
Status Insert_Elem(SqList* L, ElemType e, int position);// 插入元素
Status Delete_Elem(SqList* L, int position);			// 删除元素
Status Delete_minus_zeros(SqList* L);					// 删除小于0的元素
void PrintList(SqList L);								// 打印当前线性表 
void L_Union(SqList* La, SqList Lb);					// 应用：线性表的合并
void L_MergeList(SqList La, SqList Lb, SqList* Lc);		// 应用：有序表的合并

//以下均为测试函数
int main() {

	//-------------------------------------------------------------------------------
	// 初始化
	int length = 0;
	printf("\n请输入表长：");
	scanf_s("%d", &length);
	SqList L;
	InitSL(&L, length);
	PrintList(L);

	// 增加元素
	int e = 0, position = 0;
	printf("\n请输入你要增加的元素：");
	scanf_s("%d", &e);
	printf("\n请输入你要增加的位置：");
	scanf_s("%d", &position);
	Insert_Elem(&L, e, position);
	PrintList(L);

	// 删除元素
	e = 0, position = 0;
	printf("\n请输入你要删除的位置：");
	scanf_s("%d", &position);
	Delete_Elem(&L, position);
	PrintList(L);


	
	// 查找元素
	e = 0, position = 0;
	printf("\n请输入你要查找的元素：");
	scanf_s("%d", &e);
	Search_Elem(L, e);
	
	// 删除小于0的元素
	printf("\n现在执行程序，删除小于0的元素\n");
	Delete_minus_zeros(&L);
	PrintList(L);


	return 0;
}

// 初始化操作，建立一个线性表
Status InitSL(SqList* L, int length) {

	for (int i = 0; i < length; i++) {
		ElemType e;
		printf("请输入元素");
		scanf_s("%d", &e);
		(*L).base[i] = e;
	}
	(*L).length = length;
	return OK;
}

// 打印当前线性表 
void PrintList(SqList L) {
	printf("打印当前的线性表为：");
	for (int i = 0; i < L.length; i++) {
		printf("%d,", L.base[i]);
	}
}

// 求线性表L的长度
int Get_length(SqList* L) {
	return ((*L).length);
}

// 查找元素（按值查找）
Status Search_Elem(SqList L, ElemType e) {
	int flag = 0;
	//在线性表L中查找值为e的数据元素，返回其序号（是第几个元素）
	for (int i = 0; i < L.length; i++) {
		if (L.base[i] == e) {
			printf("找到了，是第%d个元素\n", i + 1);
			flag = 1;
		}
	}
	if (flag == 0)
		printf("找不到该元素\n");
	return 0;						//查找失败，返回0
}

// 插入元素
Status Insert_Elem(SqList* L, ElemType e, int position) {
	if (position < 1 || position >(*L).length + 1) {
		printf("插入位置不合法\n");
		return ERROR;						//插入位置不合法，返回ERROR
	}
	if ((*L).length == List_Max_Size) {
		printf("存储空间已满，返回OVERFLOW\n");
		return OVERFLOW;					//存储空间已满，返回OVERFLOW
	}
	int i = 0;
	for (i = (*L).length; i >= position - 1; i--)
		(*L).base[i + 1] = (*L).base[i];	//插入位置及之后的元素后移
	(*L).base[i + 1] = e;					//将新元素e放入第i个位置
	(*L).length++;							//表长增1
	return OK;
}

// 删除元素
Status Delete_Elem(SqList* L, int position) {
	if (position < 1 || position >(*L).length) {
		printf("删除位置不合法\n");
		return ERROR;					//删除位置不合法，返回ERROR
	}
	for (int i = position; i < (*L).length; i++)
		(*L).base[i - 1] = (*L).base[i];		//删除位置及之后的元素前移
	(*L).length--;						//表长减1
	return OK;
}

// 删除小于0的元素。
Status Delete_minus_zeros(SqList* L) {
	for (int i = 0; i < (*L).length; i++)
		if ((*L).base[i] < 0) {
			Delete_Elem(L, i + 1);
			i--;
			continue;
		}
	return OK;
}

*/