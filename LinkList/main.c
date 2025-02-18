#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// 单链表的定义
typedef struct Lnode {	//声明结点的类型和指向结点的指针类型
	ElemType data;		//结点的数据域
	struct Lnode* next;	//结点的指针域
}Lnode, * LinkList;		//LinkList为指向结构体Lnode的指针类型

// 顺序表的函数声明
Status InitList_L(LinkList *L);	// 创建一个空链表
int IsEmpty(LinkList L);		// 判断链表是否为空
Status Destroy(LinkList* L);	// 单链表销毁（释放所有结点）
Status Clear(LinkList* L);		// 清空单链表（成为空链表，保留头指针和头结点
int Get_Length(LinkList L);		// 求链表长度
void PrintList(LinkList L, int length);						// 打印当前线性表 
Status Get_Elem(LinkList L, int position, ElemType* e);		// 取值：取单链表中第i个元素的内容
Status Search(LinkList L, ElemType e);						// 查找：按值查找（第几个元素
Status Insert(LinkList* L, ElemType e, int position);		// 插入：在第i个结点之前插入值为e的新结点
Status Delete(LinkList* L, int position);					// 删除：删除第i个结点
Status Delete_SameElem(LinkList* L);						// 删除：删除相邻的重复的结点
Status Init_L_head(LinkList *L, int length);				// 创建链表（头插法）——倒位序输入n个元素的值
Status Init_L_tail(LinkList *L, int length);				// 创建链表（尾插法）——正位序输入n个元素的值
void MergeList_L(LinkList* La, LinkList* Lb, LinkList* Lc);	// 应用：有序表的合并

/*
A.编写初始化函数，初始化一个空链表。
B.编写单链表生成算法，生成一个带头结点的单链表。
C.编写函数统计单链表的长度。
D.编写查找函数，实现在单链表中查找值为x的结点，若查找成功则返回结点序号（若查找失败则返回 -1）。
E.编写函数实现对单链表中相邻重复结点的删除，如原链表中元素为{1-2-2-3-4-6-6-6-2}，则删除后链表变为 {1-2-3-4-6-2}。
F.编写插入函数，在单链表的第i个位置插入一个值为x的元素。
G.编写打印函数依次打印单链表中的各个结点元素。

编写主函数main，调用上述函数依次完成：
初始化一个空链表
调用单链表生成函数，建立一个的单链表
打印各结点元素
统计表长（数据结点个数）
在表中查找数据为3的结点，打印查找结果
在表中查找数据为7的结点，打印查找结果
对当前单链表执行删除相邻重复结点的操作
打印各结点元素
在表中第i个位置插入值为x的元素
打印各结点元素。
*/

// 以下均为测试函数
int main() {
	
	//-----------------------------------------------------------------------------
	// 初始化
	LinkList L = NULL;
	int length = 0;
	printf("请输入表长");
	scanf_s("%d", &length);
	printf("接下来使用尾插法正序输入链表\n");

	Init_L_tail(&L, length);
	length = Get_Length(L);
	PrintList(L, length);

	// 查找元素
	int e = 0, position = 0;
	printf("\n请输入你要查找的元素：");
	scanf_s("%d", &e);
	Search(L, e);

	// 查找元素
	e = 0, position = 0;
	printf("\n请输入你要查找的元素：");
	scanf_s("%d", &e);
	Search(L, e);

	// 插入元素
	e = 0, position = 0;
	printf("请输入你要插入的元素：");
	scanf_s("%d", &e);
	printf("请输入你要插入的位置：");
	scanf_s("%d", &position);
	Insert(&L, e, position); 
	length = Get_Length(L);
	PrintList(L, length);

	// 删除元素
	printf("现在执行程序，删除重复的元素\n");
	Delete_SameElem(&L);
	length = Get_Length(L);
	PrintList(L,length);
	Destroy(&L);

	/*
	//-----------------------------------------------------------------------------
	// 应用：有序表的合并
	LinkList La = NULL;
	int length = 0;
	printf("请输入表长");
	scanf_s("%d", &length);
	printf("接下来使用头插法输入链表\n");
	Init_L_head(&La, length);
	length = Get_Length(La);
	PrintList(La, length);

	LinkList Lb = NULL;
	printf("请输入表长");
	scanf_s("%d", &length);
	printf("接下来使用头插法输入链表\n");
	Init_L_head(&Lb, length);
	length = Get_Length(Lb);
	PrintList(Lb, length);

	LinkList Lc = NULL;
	InitList_L(&Lc);
	MergeList_L(&La, &Lb, &Lc);
	length = Get_Length(Lc);
	PrintList(Lc, length);
	*/

	return 0;
}


// 创建一个空链表
Status InitList_L(LinkList *L) {
	*L = (LinkList)malloc(sizeof(Lnode));
	if (*L == NULL) {
		return ERROR;		// 分配内存失败
	}
	(*L)->data = 0;
	(*L)->next = NULL;
	return OK;
}

// 创建链表（头插法）——倒位序输入n个元素的值
Status Init_L_head(LinkList *L, int length) {
	*L = (LinkList)malloc(sizeof(Lnode));
	if (*L == NULL)
		return ERROR;
	(*L)->data = 0;
	(*L)->next = NULL;		//先建立一个带头结点的单链表
	for (int i = 0; i<length ; i++) {
		Lnode* p = (Lnode*)malloc(sizeof(Lnode));	//生成新的结点
		printf("请输入第%d个元素值", length - i);
		scanf_s("%d", &p->data);					//输入元素值
		p->next = (*L)->next;						//插入到表头
		(*L)->next = p;
	}
	return OK;
}

// 创建链表（尾插法）——正位序输入n个元素的值
Status Init_L_tail(LinkList* L, int length) {
	(*L) = (LinkList)malloc(sizeof(Lnode));
	if (*L == NULL)
		return ERROR;
	(*L)->next = NULL;		//先建立一个带头结点的单链表
	(*L)->data = 0;
	Lnode* r = *L;
	for (int i = length; i > 0 ; i--) {
		Lnode* p = (Lnode*)malloc(sizeof(Lnode));	//生成新的结点
		printf("现在输入第%d个元素的值", length - i + 1);
		scanf_s("%d", &p->data);					//输入元素值
		p->next = NULL;
		r->next = p;								//插入到表尾
		r = p;										//r指向新的尾结点
	}
	return OK;
}

// 打印当前线性表 
void PrintList(LinkList L, int length) {
	printf("打印当前线性表为：");
	Lnode* p = L->next;
	for (int i = 0; i < length; i++) {
		printf("%d,", p->data);
		p = p->next;
		if (i == length-1)
			printf("\n");
	}
}

// 判断链表是否为空
int IsEmpty(LinkList L) {	//若L为空表，则返回1，否则返回0
	if (L->next)
		return 0;
	else
		return 1;
}

// 单链表销毁（释放所有结点）
Status Destroy(LinkList* L) {
	Lnode* p = NULL;		//存储要销毁的结点
	while (*L != NULL) {
		p = *L;
		*L = (*L)->next;
		free(p);
	}
	return OK;
}

// 清空单链表（成为空链表，保留头指针和头结点
Status Clear(LinkList* L) {
	Lnode* p = (*L)->next;	//由于头指针保留，所以要再开两个指针变量来轮流删除
	Lnode* q = NULL;
	while (p != NULL) {		//没到表尾
		q = p->next;
		free(p);
		p = q;
	}
	(*L)->next = NULL;		//头结点指针域为空
	return OK;
}

// 求链表长度
int Get_Length(LinkList L) {	//返回L中数据元素的个数
	Lnode* p;
	p = L->next;		//p指向第一个结点
	int i = 0;			//记录元素个数
	while (p) {			//遍历单链表
		i++;
		p = p->next;
	}
	printf("当前线性表的长度为：%d\n", i);
	return i;
}

// 取值：取单链表中第i个元素的内容
Status Get_Elem(LinkList L, int position, ElemType* e) {	//获取线性表中某个数据元素的内容，通过变量e返回
	Lnode* p;
	p = L->next;
	int j = 1;								//初始化计数器
	while (p != NULL && j < position) {		//向后扫描，直到p指向第i个元素，或者p为空
		p = p->next;
		j++;
	}
	if (p == NULL || j > position)
		return ERROR;						//第i个元素不存在
	*e = p->data;
	return OK;
}

// 查找：按值查找（第几个元素
Status Search(LinkList L, ElemType e) {
	Lnode* p;
	p = L->next;
	int i = 1;
	int flag = 0;
	while (p != NULL) {
		if (p->data == e) {
			printf("查找成功，是第%d个元素\n", i);
			flag = 1;
		}
		p = p->next;
		i++;
	}
	if (flag == 0) {
		printf("查找失败\n");
		return -1;		//查找失败返回-1
	}
}

// 插入：在第i个结点之前插入值为e的新结点
Status Insert(LinkList* L, ElemType e, int position) {
	Lnode* p;
	p = *L;
	int j = 0;
	while (p != NULL && j < position - 1) {		//寻找第position-1个结点，p指向position-1个结点
		p = p->next;
		++j;
	}
	if (p == NULL || j > position - 1 || position < 1) {
		printf("插入位置不合法\n");
		return ERROR;							//position大于表长+1，或者position<1，插入位置非法
	}
	Lnode *s = (Lnode*)malloc(sizeof(Lnode));
	(*s).data = e;
	(*s).next = p->next;
	p->next = s;
	return OK;
}

// 删除：删除第i个结点
Status Delete(LinkList* L, int position) {
	Lnode* p;
	p = *L;
	int j = 0;
	while (p != NULL && j < position - 1) {		//寻找第position-1个结点，p指向position-1个结点
		p = p->next;
		++j;
	}
	if (p == NULL || p->next == NULL || j > position - 1 || position < 1) {
		return ERROR;							//position大于表长+1，或者position<1，删除位置非法
	}
	Lnode* q = p->next;
	p->next = (p->next)->next;
	free(q);
	return OK;
}

// 删除：删除相邻的重复的结点
Status Delete_SameElem(LinkList* L) {
	Lnode* p;
	p = (*L)->next;			// 定义指针p指向第一个元素
	int i = 1;				// 标记删除元素的位置
	while (p->next != NULL) {		// 检测到元素相同，则删除重复元素
		if (p->data == p->next->data) {	
			p = p->next;			// 重新定义指针p
			Delete(L, i);
		}
		else {
			p = p->next;
			i++;
		}
	}
	return OK;
}

// 循环链表：带尾指针的循环链表的合并
LinkList Connect(LinkList Ta, LinkList Tb) {
	LinkList p;					//假设Ta，Tb都是非空的单循环链表
	p = Ta->next;				//①p存表的头结点
	Ta->next = Tb->next->next;	//②Tb表头连接到Ta表尾
	free(Tb->next);				//③释放Tb头结点
	Tb->next = p;				//④将Tb的尾节点接到Ta的头。
	return Tb;
}

// 应用：有序表的合并
void MergeList_L(LinkList* La, LinkList* Lb, LinkList* Lc) {
	Lnode* pa = (*La)->next;
	Lnode* pb = (*Lb)->next;
	Lnode* pc = *Lc= *La;			//用La的头结点作为Lc的头结点
	while (pa && pb) {
		if (pa->data <= pb->data) {
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else {
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb;	//插入剩余段落
}