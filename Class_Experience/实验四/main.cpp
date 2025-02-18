#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Search.h"

// �����������Ա����������
const int Table_Length = 1000;	// ����1000�����Ԫ��
typedef int KeyType;			// ����ؼ�������Ϊint
typedef struct {
	KeyType key;				// �洢�ؼ���
} SSTElemType;
typedef struct {
	SSTElemType* base;			// ���������׵�ַ(0��λ�ò���Źؼ��֣�Ԥ����guard)
	int length;					// ��ǰ��(����ĳ���)
} SSTable;

// �����ϣ��
#define HASH_TABLE_SIZE 1001	// ��ϣ���С
typedef struct {
	int key;
	bool exists; // ��Ǹ�λ���Ƿ��Ѿ��洢��Ԫ��
} HashTableItem;
HashTableItem hashTable[HASH_TABLE_SIZE];

// ��������
Status CreateRandomSSTable(SSTable* ST, int size);		// �������������������Ա�
Status Search_SS(SSTable ST, KeyType key);				// ˳�����
Status Search_BS(SSTable ST, KeyType key);				// ���ֲ���

int Hash(int key);										// ��ϣ����������������
Status HashInsert(int key);								// ��ϣ��������
Status InitHash(SSTable ST);							// ��ʼ����ϣ��
Status HashSearch(int key);								// ��ϣ����Ҳ���

void InsertSort(SSTable* ST);							// �򵥲�������
void ShellSort(SSTable* ST, int dt[], int t);			// ϣ������
void BubbleSort(SSTable* ST);							// ð������
void SelectionSort(SSTable* ST);						// ��ѡ������
int Partition(SSTable* ST, int left, int right);		// Ѱ�һ�׼
void QuickSort(SSTable* ST, int left, int right);		// ���������㷨
void MSort(SSTElemType* R, SSTElemType* Temp, int left, int right);				// �鲢����
void Merge(SSTElemType* R, SSTElemType* Temp, int left, int mid, int right);	// �ϲ�����
void MergeSort(SSTable* ST);							// �鲢��������װ


// ���¾�Ϊ���Ժ���
int main() {
	// ����һ������1000�����Ԫ�صı�
	SSTable ST;
	CreateRandomSSTable(&ST, Table_Length);
	InitHash(ST);				// ��ʼ����ϣ��

	// ���Բ��Ҳ���
	int aim = 0;
	printf("��������Ҫ���ҵ�����");
	scanf_s("%d", &aim);
	Search_SS(ST, aim);			// ˳�����
	HashSearch(aim);			// ��ϣ����

	// �����������
	printf("����ǰ�����飺\n");
	for (int i = 1; i <= ST.length; i++) {
		printf("%d ", ST.base[i].key);
	}
	printf("\n");

	InsertSort(&ST);				// ���Լ򵥲�������
	BubbleSort(&ST);				// ����ð������
	SelectionSort(&ST);				// ���Լ�ѡ������
	MergeSort(&ST);					// ���Թ鲢����

	printf("���ڲ��Կ��������㷨\n");
	QuickSort(&ST, 1, ST.length);	// ���Կ�������
	
	int dt[] = { 5, 3, 1 };			// ������������
	int t = sizeof(dt) / sizeof(dt[0]);
	ShellSort(&ST, dt, t);			// ����ϣ������
	
	printf("���������飺\n");
	for (int i = 1; i <= ST.length; i++) {
		printf("%d ", ST.base[i].key);
	}
	printf("\n");

	// ���Զ��ֲ���
	int des = 0;
	printf("��������Ҫ���ҵ�����");
	scanf_s("%d", &des);
	Search_BS(ST, des);

	// �ͷŷ�����ڴ�
	free(ST.base);

	return 0;
}

// �������������������Ա�
Status CreateRandomSSTable(SSTable* ST, int size) {
	ST->length = size;
	ST->base = (SSTElemType*)malloc((size + 1) * sizeof(SSTElemType)); // �����ڴ棨+1ΪԤ��guardλ�ã�
	if (ST->base == NULL) {
		printf("�ռ����ʧ��");
		return OVERFLOW;
	}
	srand(time(NULL)); // �������������
	for (int i = 1; i <= size; i++) {			// ��1��ʼ��䣬0λ��Ԥ��
		(*ST).base[i].key = rand()%1001;		// ������ɹؼ���0-1000
	}
	return OK;
}

// ˳�����
Status Search_SS(SSTable ST, KeyType key) {
	printf("����ʹ��˳�����\n");
	for (int i = ST.length; i > 0; i--) {
		if (key == ST.base[i].key) {
			printf("�ҵ��˹ؼ���%d���ǵ�%d��Ԫ��\n", key,i);
			return OK;
		}
	}
	printf("����ʧ��\n");
	return FALSE;
}

// ��ϣ����
int Hash(int key) {					// ��ϣ����������������
	return key % 277;
}
Status HashInsert(int key) {		// ��ϣ��������
	int index = Hash(key);
	int originalIndex = index;
	do {
		if (!hashTable[index].exists) {
			hashTable[index].key = key;
			hashTable[index].exists = true;
			return OK;
		}
		index = (index + 1) % HASH_TABLE_SIZE;	// ����̽������ͻ
	} while (index != originalIndex);			// ��ֹ����ѭ��

	printf("��ϣ���������޷��������Ԫ�ء�\n");
	return OVERFLOW;							// ��ϣ������
}
Status InitHash(SSTable ST) {		// ��ʼ����ϣ��
	// ��ʼ����ϣ��
	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		hashTable[i].exists = false;
	}
	// �������
	for (int i = 1; i <= Table_Length; i++) {
		HashInsert((ST.base[i].key));			// ����0-1000�ڵ������
	}
	return OK;

}
Status HashSearch(int key) {		// ��ϣ����Ҳ���
	printf("����ʹ�ù�ϣ����\n");
	int flag = -1;			// ���ñ��
	int index = Hash(key);	// ����Ԫ�ض�Ӧ�Ĺ�ϣֵ
	int count = 0;			// ��ֹ����ѭ��

	while (hashTable[index].exists && count < HASH_TABLE_SIZE) {
		if (hashTable[index].key == key) {
			printf("�ҵ��˹ؼ���%d���ڹ�ϣ�������Ϊ%d\n", key, index);
			flag = 1;
			return OK; // �ҵ�����OK
		}
		index = (index + 1) % HASH_TABLE_SIZE;
		count++;
	}
	if (flag == -1) {
		printf("�ؼ��� %d δ�ڹ�ϣ�����ҵ�\n", key);
		return -1; // δ�ҵ�����-1
	}
}

// �򵥲�������
void InsertSort(SSTable* ST) {
	printf("���ڲ��Լ򵥲�������\n");
	for (int i = 2; i <= ST->length; i++) {
		if (ST->base[i].key < ST->base[i - 1].key) {
			ST->base[0] = ST->base[i]; // ����guard
			int j;
			for (j = i - 1; ST->base[0].key < ST->base[j].key; j--) {
				ST->base[j + 1] = ST->base[j];
			}
			ST->base[j + 1] = ST->base[0];
		}
	}
}

// ϣ������
void ShellSort(SSTable* ST, int dt[], int t) {
	printf("���ڲ���ϣ������\n");
	for (int k = 0; k < t; k++) {
		int dk = dt[k];
		for (int i = dk + 1; i <= ST->length; i++) {
			if (ST->base[i].key < ST->base[i - dk].key) {
				ST->base[0] = ST->base[i]; // ����guard
				int j;
				for (j = i - dk; j > 0 && ST->base[0].key < ST->base[j].key; j -= dk) {
					ST->base[j + dk] = ST->base[j];
				}
				ST->base[j + dk] = ST->base[0];
			}
		}
	}
}

// ��ѡ������
void SelectionSort(SSTable* ST) {
	printf("���ڲ��Լ�ѡ������\n");
	for (int i = 1; i < ST->length; i++) {
		int k = i; // k��¼��Сֵ��λ��
		for (int j = i + 1; j <= ST->length; j++) {
			if (ST->base[k].key > ST->base[j].key) {
				k = j; // ������Сֵ��λ��
			}
		}
		if (k != i) { // ����ҵ���С��ֵ
			SSTElemType temp = ST->base[i];
			ST->base[i] = ST->base[k];
			ST->base[k] = temp;
		}
	}
}

// ð������
void BubbleSort(SSTable* ST) {
	printf("���ڲ���ð������\n");
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

// ���������㷨
int Partition(SSTable* ST, int left, int right) {	// Ѱ�һ�׼
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
void QuickSort(SSTable* ST, int left, int right) {	// ��������
	if (left < right) {
		int pivot = Partition(ST, left, right);
		QuickSort(ST, left, pivot - 1);
		QuickSort(ST, pivot + 1, right);
	}
}

// �鲢����
void MSort(SSTElemType* R, SSTElemType* Temp, int left, int right) {	// �鲢����ݹ麯��
	if (left >= right) return;
	int mid = (left + right) / 2;
	MSort(R, Temp, left, mid);
	MSort(R, Temp, mid + 1, right);
	Merge(R, Temp, left, mid, right);

	for (int i = left; i <= right; i++) {
		R[i] = Temp[i];
	}
}
void Merge(SSTElemType* R, SSTElemType* Temp, int left, int mid, int right) {	// �ϲ�����
	int i = left, j = mid + 1, k = left;
	while (i <= mid && j <= right) {
		if (R[i].key <= R[j].key) Temp[k++] = R[i++];
		else Temp[k++] = R[j++];
	}
	while (i <= mid) Temp[k++] = R[i++];
	while (j <= right) Temp[k++] = R[j++];
}
void MergeSort(SSTable* ST) {	// �鲢����
	printf("���ڲ��Թ鲢�����㷨\n");
	SSTElemType* Temp = (SSTElemType*)malloc((ST->length + 1) * sizeof(SSTElemType));
	MSort(ST->base, Temp, 1, ST->length);
	free(Temp);
}

// ���ֲ���
Status Search_BS(SSTable ST, KeyType key) {
	printf("����ʹ�ö��ֲ���\n");
	int left = 1;			//ȷ��������
	int right = ST.length;	//ȷ��������
	int mid = (left + right) / 2;
	while (left <= right) {
		if (key == ST.base[mid].key) {
			printf("�ҵ��˹ؼ���%d���ǵ�%d��Ԫ��\n", key, mid);
			return OK;
		}
		else if (key > ST.base[mid].key) { //�������Ԫ�ش����м�λ��Ԫ��
			left = mid + 1;
			mid = (left + right) / 2;
		}
		else { //�������Ԫ��С���м�λ��
			right = mid - 1;
			mid = (left + right) / 2;
		}
	}
	return 0;
}

