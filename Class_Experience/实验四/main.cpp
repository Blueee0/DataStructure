#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Search.h"

// 定义无序线性表的数据类型
const int Table_Length = 1000;	// 含有1000个随机元素
typedef int KeyType;			// 定义关键字类型为int
typedef struct {
	KeyType key;				// 存储关键字
} SSTElemType;
typedef struct {
	SSTElemType* base;			// 存放数组的首地址(0号位置不存放关键字，预留给guard)
	int length;					// 当前表长(数组的长度)
} SSTable;

// 构造哈希表
#define HASH_TABLE_SIZE 1001	// 哈希表大小
typedef struct {
	int key;
	bool exists; // 标记该位置是否已经存储了元素
} HashTableItem;
HashTableItem hashTable[HASH_TABLE_SIZE];

// 函数声明
Status CreateRandomSSTable(SSTable* ST, int size);		// 创建并填充随机无序线性表
Status Search_SS(SSTable ST, KeyType key);				// 顺序查找
Status Search_BS(SSTable ST, KeyType key);				// 二分查找

int Hash(int key);										// 哈希函数：除留余数法
Status HashInsert(int key);								// 哈希表插入操作
Status InitHash(SSTable ST);							// 初始化哈希表
Status HashSearch(int key);								// 哈希表查找操作

void InsertSort(SSTable* ST);							// 简单插入排序
void ShellSort(SSTable* ST, int dt[], int t);			// 希尔排序
void BubbleSort(SSTable* ST);							// 冒泡排序
void SelectionSort(SSTable* ST);						// 简单选择排序
int Partition(SSTable* ST, int left, int right);		// 寻找基准
void QuickSort(SSTable* ST, int left, int right);		// 快速排序算法
void MSort(SSTElemType* R, SSTElemType* Temp, int left, int right);				// 归并排序
void Merge(SSTElemType* R, SSTElemType* Temp, int left, int mid, int right);	// 合并函数
void MergeSort(SSTable* ST);							// 归并排序函数封装


// 以下均为测试函数
int main() {
	// 创建一个含有1000个随机元素的表
	SSTable ST;
	CreateRandomSSTable(&ST, Table_Length);
	InitHash(ST);				// 初始化哈希表

	// 测试查找操作
	int aim = 0;
	printf("请输入你要查找的数：");
	scanf_s("%d", &aim);
	Search_SS(ST, aim);			// 顺序查找
	HashSearch(aim);			// 哈希查找

	// 测试排序操作
	printf("排序前的数组：\n");
	for (int i = 1; i <= ST.length; i++) {
		printf("%d ", ST.base[i].key);
	}
	printf("\n");

	InsertSort(&ST);				// 测试简单插入排序
	BubbleSort(&ST);				// 测试冒泡排序
	SelectionSort(&ST);				// 测试简单选择排序
	MergeSort(&ST);					// 测试归并排序

	printf("现在测试快速排序算法\n");
	QuickSort(&ST, 1, ST.length);	// 测试快速排序
	
	int dt[] = { 5, 3, 1 };			// 定义增量序列
	int t = sizeof(dt) / sizeof(dt[0]);
	ShellSort(&ST, dt, t);			// 测试希尔排序
	
	printf("排序后的数组：\n");
	for (int i = 1; i <= ST.length; i++) {
		printf("%d ", ST.base[i].key);
	}
	printf("\n");

	// 测试二分查找
	int des = 0;
	printf("请输入你要查找的数：");
	scanf_s("%d", &des);
	Search_BS(ST, des);

	// 释放分配的内存
	free(ST.base);

	return 0;
}

// 创建并填充随机无序线性表
Status CreateRandomSSTable(SSTable* ST, int size) {
	ST->length = size;
	ST->base = (SSTElemType*)malloc((size + 1) * sizeof(SSTElemType)); // 分配内存（+1为预留guard位置）
	if (ST->base == NULL) {
		printf("空间分配失败");
		return OVERFLOW;
	}
	srand(time(NULL)); // 设置随机数种子
	for (int i = 1; i <= size; i++) {			// 从1开始填充，0位置预留
		(*ST).base[i].key = rand()%1001;		// 随机生成关键字0-1000
	}
	return OK;
}

// 顺序查找
Status Search_SS(SSTable ST, KeyType key) {
	printf("现在使用顺序查找\n");
	for (int i = ST.length; i > 0; i--) {
		if (key == ST.base[i].key) {
			printf("找到了关键字%d，是第%d个元素\n", key,i);
			return OK;
		}
	}
	printf("查找失败\n");
	return FALSE;
}

// 哈希查找
int Hash(int key) {					// 哈希函数：除留余数法
	return key % 277;
}
Status HashInsert(int key) {		// 哈希表插入操作
	int index = Hash(key);
	int originalIndex = index;
	do {
		if (!hashTable[index].exists) {
			hashTable[index].key = key;
			hashTable[index].exists = true;
			return OK;
		}
		index = (index + 1) % HASH_TABLE_SIZE;	// 线性探测解决冲突
	} while (index != originalIndex);			// 防止无限循环

	printf("哈希表已满，无法插入更多元素。\n");
	return OVERFLOW;							// 哈希表已满
}
Status InitHash(SSTable ST) {		// 初始化哈希表
	// 初始化哈希表
	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		hashTable[i].exists = false;
	}
	// 插入操作
	for (int i = 1; i <= Table_Length; i++) {
		HashInsert((ST.base[i].key));			// 插入0-1000内的随机数
	}
	return OK;

}
Status HashSearch(int key) {		// 哈希表查找操作
	printf("现在使用哈希查找\n");
	int flag = -1;			// 设置标记
	int index = Hash(key);	// 查找元素对应的哈希值
	int count = 0;			// 防止无限循环

	while (hashTable[index].exists && count < HASH_TABLE_SIZE) {
		if (hashTable[index].key == key) {
			printf("找到了关键字%d，在哈希表的索引为%d\n", key, index);
			flag = 1;
			return OK; // 找到返回OK
		}
		index = (index + 1) % HASH_TABLE_SIZE;
		count++;
	}
	if (flag == -1) {
		printf("关键字 %d 未在哈希表中找到\n", key);
		return -1; // 未找到返回-1
	}
}

// 简单插入排序
void InsertSort(SSTable* ST) {
	printf("现在测试简单插入排序\n");
	for (int i = 2; i <= ST->length; i++) {
		if (ST->base[i].key < ST->base[i - 1].key) {
			ST->base[0] = ST->base[i]; // 设置guard
			int j;
			for (j = i - 1; ST->base[0].key < ST->base[j].key; j--) {
				ST->base[j + 1] = ST->base[j];
			}
			ST->base[j + 1] = ST->base[0];
		}
	}
}

// 希尔排序
void ShellSort(SSTable* ST, int dt[], int t) {
	printf("现在测试希尔排序\n");
	for (int k = 0; k < t; k++) {
		int dk = dt[k];
		for (int i = dk + 1; i <= ST->length; i++) {
			if (ST->base[i].key < ST->base[i - dk].key) {
				ST->base[0] = ST->base[i]; // 设置guard
				int j;
				for (j = i - dk; j > 0 && ST->base[0].key < ST->base[j].key; j -= dk) {
					ST->base[j + dk] = ST->base[j];
				}
				ST->base[j + dk] = ST->base[0];
			}
		}
	}
}

// 简单选择排序
void SelectionSort(SSTable* ST) {
	printf("现在测试简单选择排序\n");
	for (int i = 1; i < ST->length; i++) {
		int k = i; // k记录最小值的位置
		for (int j = i + 1; j <= ST->length; j++) {
			if (ST->base[k].key > ST->base[j].key) {
				k = j; // 更新最小值的位置
			}
		}
		if (k != i) { // 如果找到更小的值
			SSTElemType temp = ST->base[i];
			ST->base[i] = ST->base[k];
			ST->base[k] = temp;
		}
	}
}

// 冒泡排序
void BubbleSort(SSTable* ST) {
	printf("现在测试冒泡排序\n");
	bool flag = true;
	for (int i = 1; i < ST->length && flag; i++) {
		flag = false;
		for (int j = 1; j <= ST->length - i; j++) {
			if (ST->base[j].key > ST->base[j + 1].key) {
				flag = true;
				SSTElemType temp = ST->base[j];
				ST->base[j] = ST->base[j + 1];
				ST->base[j + 1] = temp;
			}
		}
	}
}

// 快速排序算法
int Partition(SSTable* ST, int left, int right) {	// 寻找基准
	SSTElemType pivot = ST->base[left];
	while (left < right) {
		while (left < right && pivot.key <= ST->base[right].key) right--;
		ST->base[left] = ST->base[right];
		while (left < right && pivot.key >= ST->base[left].key) left++;
		ST->base[right] = ST->base[left];
	}
	ST->base[left] = pivot;
	return left;
}
void QuickSort(SSTable* ST, int left, int right) {	// 快速排序
	if (left < right) {
		int pivot = Partition(ST, left, right);
		QuickSort(ST, left, pivot - 1);
		QuickSort(ST, pivot + 1, right);
	}
}

// 归并排序
void MSort(SSTElemType* R, SSTElemType* Temp, int left, int right) {	// 归并排序递归函数
	if (left >= right) return;
	int mid = (left + right) / 2;
	MSort(R, Temp, left, mid);
	MSort(R, Temp, mid + 1, right);
	Merge(R, Temp, left, mid, right);

	for (int i = left; i <= right; i++) {
		R[i] = Temp[i];
	}
}
void Merge(SSTElemType* R, SSTElemType* Temp, int left, int mid, int right) {	// 合并函数
	int i = left, j = mid + 1, k = left;
	while (i <= mid && j <= right) {
		if (R[i].key <= R[j].key) Temp[k++] = R[i++];
		else Temp[k++] = R[j++];
	}
	while (i <= mid) Temp[k++] = R[i++];
	while (j <= right) Temp[k++] = R[j++];
}
void MergeSort(SSTable* ST) {	// 归并排序
	printf("现在测试归并排序算法\n");
	SSTElemType* Temp = (SSTElemType*)malloc((ST->length + 1) * sizeof(SSTElemType));
	MSort(ST->base, Temp, 1, ST->length);
	free(Temp);
}

// 二分查找
Status Search_BS(SSTable ST, KeyType key) {
	printf("现在使用二分查找\n");
	int left = 1;			//确定左区间
	int right = ST.length;	//确定又区间
	int mid = (left + right) / 2;
	while (left <= right) {
		if (key == ST.base[mid].key) {
			printf("找到了关键字%d，是第%d个元素\n", key, mid);
			return OK;
		}
		else if (key > ST.base[mid].key) { //如果搜索元素大于中间位置元素
			left = mid + 1;
			mid = (left + right) / 2;
		}
		else { //如果搜索元素小于中间位置
			right = mid - 1;
			mid = (left + right) / 2;
		}
	}
	return 0;
}

