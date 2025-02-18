#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// 顺序表的存储结构
#define List_Max_Size 100		//线性表存储空间的最大分配量
typedef struct _Sql{
	ElemType base[List_Max_Size];
	int length;	//当前长度
}SqList;

// 顺序表的函数声明
Status InitSL(SqList* L, int length);					// 初始化操作，建立一个线性表
void DestroyList(SqList* L);							// 销毁线性表
void ClearList(SqList* L);								// 清空线性表
int Get_length(SqList* L);								// 求线性表L的长度
int IsEmpty(SqList* L);									// 判断线性表是否为空
Status Get_Elem(SqList* L, int position, ElemType* e);	// 获取元素
int Search_Elem(SqList L, ElemType e);					// 查找元素（按值查找）
Status Insert_Elem(SqList* L, ElemType e, int position);// 插入元素
Status Delete_Elem(SqList* L, int position);			// 删除元素
Status Delete_minus_zeros(SqList* L);					// 删除小于0的元素
void PrintList(SqList L);								// 打印当前线性表 
void L_Union(SqList *La, SqList Lb);					// 应用：线性表的合并
void L_MergeList(SqList La, SqList Lb, SqList* Lc);		// 应用：有序表的合并

/*
A.编写初始化函数，初始化一个空的顺序表；
B.编写函数实现对一个空的顺序表赋值，各数据元素的值从键盘依次获取；
C.编写删除函数，实现删除顺序表中第i个元素的操作；
D.编写打印函数，实现对顺序表中各个元素依次打印；
E.编写插入函数，在顺序表中的第i个位置插入一个元素x。
F.编写函数，删除顺序表中所有值为负的元素。
编写主函数main，调用上述函数依次完成：
调用A，初始化顺序表
调用B，对该顺序表赋值
调用D，打印顺序表的中各个元素

调用C，删除表中的第i个元素（i的值从键盘输入
调用D，打印顺序表的中各个元素

调用E，在顺序表的第i个位置插入一个元素x（i和x的值从键盘输入）
调用D，打印顺序表的中各个元素

调用F，删除小于0的元素
调用D，打印顺序表的中各个元素。
*/

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
	int e = 0,position = 0 ;
	printf("\n请输入你要增加的元素：");
	scanf_s("%d", &e);
	printf("\n请输入你要增加的位置：");
	scanf_s("%d", &position);
	Insert_Elem(&L, e, position);
	PrintList(L);

	/*
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
	*/

	/*
	//-------------------------------------------------------------------------------
	// 测试应用：线性表的合并
	printf("测试应用：线性表的合并");
	int length = 0;
	printf("\n请输入表长：");
	scanf_s("%d", &length);
	SqList La;
	InitSL(&La, length);
	PrintList(La);

	printf("\n请输入表长：");
	scanf_s("%d", &length);
	SqList Lb;
	InitSL(&Lb, length);
	PrintList(Lb);

	printf("现在开始合并\n");
	L_Union(&La, Lb);
	PrintList(La);


	//-------------------------------------------------------------------------------
	// 测试应用：有序表的合并
	printf("测试应用：线性表的合并");
	int length = 0;
	printf("\n请输入表长：");
	scanf_s("%d", &length);
	SqList La;
	InitSL(&La, length);
	PrintList(La);

	printf("\n请输入表长：");
	scanf_s("%d", &length);
	SqList Lb;
	InitSL(&Lb, length);
	PrintList(Lb);

	SqList Lc;
	InitSL(&Lc, 0);

	printf("现在开始合并\n");
	L_MergeList(La, Lb,&Lc);
	PrintList(Lc);

	return 0;
	*/
	return 0;
}

// 应用：线性表的合并
void L_Union(SqList *La, SqList Lb) {
	int La_len = Get_length(La);
	int Lb_len = Get_length(&Lb);
	ElemType *e = 0;
	for (int i = 1; i <= Lb_len; i++) {
		Get_Elem(&Lb, i, e);			// 获取线性表Lb中第i个位置存储的元素e
		if (!Search_Elem(*La, e))		// 如果在线性表La中没找到元素e
			Insert_Elem(La, e, ++La_len);
	}
}

// 应用：有序表的合并
void L_MergeList(SqList La, SqList Lb,SqList *Lc) {
	int* pa = La.base;				// 将指针pa和pb的值指向两个表的第一个元素
	int* pb = Lb.base;

	int La_len = Get_length(&La);
	int Lb_len = Get_length(&Lb);
	int Lc_len = La_len + Lb_len;	// 新表的长度为待合并的两表的长度之和
	(*Lc).length = Lc_len;
	int* pc = (*Lc).base;			// 指针pc为指向新表的第一个元素
	
	int* pa_last = La.base + La_len - 1;	//指针pa_last 指向 La表的最后一个元素
	int* pb_last = Lb.base + Lb_len - 1;	//指针pb_last 指向 Lb表的最后一个元素
	
	while (pa <= pa_last && pb <= pb_last) {	// 如果两个表都非空
		if (*pa <= *pb)
			*pc++ = *pa++;
		else
			*pc++ = *pb++;
	}
	while (pa <= pa_last)
		*pc++ = *pa++;			//Lb已经到达表尾，将La中的剩余元素加入Lc
	while (pb <= pb_last)
		*pc++ = *pb++;			//La已经到达表尾，将Lb中的剩余元素加入Lc
}

// 初始化操作，建立一个线性表
Status InitSL(SqList* L, int length) {

	for (int i = 0; i < length; i++) {
		ElemType e;
		printf("请输入元素");
		scanf_s("%d",&e);
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

// 销毁线性表
void DestroyList(SqList* L) {
	free(&L);		//释放存储空间
}

// 清空线性表
void ClearList(SqList* L) {
	L->length = 0;			//将线性表的长度置为0
}

// 求线性表L的长度
int Get_length(SqList* L) {
	return ((*L).length);
}

// 判断线性表是否为空
int IsEmpty(SqList* L) {
	if ((*L).length == 0)
		return 1;
	else 
		return 0;
}

// 获取元素
Status Get_Elem(SqList* L, int position, ElemType * e) {
	if (position < 1 || position > L->length)	//判断位置是否合理，若不合理，返回ERROR
		return ERROR;
	*e = (*L).base[position - 1];				//第position-1个单元存储着第position个元素
	return OK;
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
	if(flag == 0)
		printf("找不到该元素\n");
	return 0;						//查找失败，返回0
}

// 插入元素
Status Insert_Elem(SqList* L, ElemType e, int position) {
	if (position < 1 || position >(*L).length + 1) {
		printf("插入位置不合法");
		return ERROR;						//插入位置不合法，返回ERROR
	}
	if ((*L).length == List_Max_Size) {
		printf("存储空间已满，返回OVERFLOW");
		return OVERFLOW;					//存储空间已满，返回OVERFLOW
	}
	int i = 0;
	for (i = (*L).length; i >= position - 1 ; i-- )
		(*L).base[i + 1] = (*L).base[i];	//插入位置及之后的元素后移
	(*L).base[i+1] = e;					//将新元素e放入第i个位置
	(*L).length++;							//表长增1
	return OK;
}

// 删除元素
Status Delete_Elem(SqList* L, int position) {
	if (position < 1 || position >(*L).length) {
		printf("删除位置不合法\n");
		return ERROR;					//删除位置不合法，返回ERROR
	}
	for (int i = position ; i < (*L).length; i++)
		(*L).base[i-1] = (*L).base[i];		//删除位置及之后的元素前移
	(*L).length--;						//表长减1
	return OK;
}

Status Delete_minus_zeros(SqList* L) {
	for (int i = 0; i < (*L).length; i++)
		if ((*L).base[i] < 0) {
			Delete_Elem(L, i + 1);
			i--;
			continue;
		}
	return OK;
}