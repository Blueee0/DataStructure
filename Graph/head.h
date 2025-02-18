#pragma once
// �������״̬����
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

// ������
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

// Status �Ǻ��������ͣ���ֵ�Ǻ������״̬����
typedef int Status;

// �������ݽṹ
#define MaxWeight 99999             // ���Ȩֵ
#define MaxVertex 20                // ��󶥵���
#define MaxDistance 99999           // �·��
typedef char VertexType;            // �����������ַ���ʾ
typedef char QElemType;             // ����Ԫ�����ַ���ʾ

// ʹ���ڽӱ���ͼ�����ݽṹ
typedef struct _EdgeNode {
    int adjvertex;                  // ����vi���ڽӵ��λ��
    _EdgeNode* next;                // ����ָ����һ���ڽӵ��ָ��
    int weight;                     // ����Ȩֵ
}EdgeNode;

typedef struct _ALGNode {
    VertexType name;                // ���嶥�������
    EdgeNode* first;                // ����ָ�����һ���ڽӵ��ָ��
}ALGNode;

typedef struct _ALGraph {
    ALGNode vertex[MaxVertex];      // �����ڽӱ�
    int edges, vertices;            // ���嶥�����ͱ���
}ALGraph;

// ������е����ݽṹ
#define QMAXSIZE 100
typedef char QElemType;
typedef struct __SqQueue {
    QElemType* base;
    int front, rere; //frontΪ��ͷ�±꣬rereΪ��β�±�(rere�±��λ�ò����Ԫ��)
} SqQueue;

// Prim�㷨�ĸ����㼯
struct Uset {
    int adjvertex;  //�±�Ϊi�ĵ���ڽӵ�
    int weight;     //��ǰȨֵ
};

// Kruskal�㷨�ĸ����߼�
struct Eset {
    int start;  //���
    int end;    //�յ�
    int weight;
};

// ��������
void Creat_unALGraph_weighted(ALGraph* G);                      // ���������Ȩͼ
int Locate_vertex(const ALGraph* G, char v1);                   // ��λ������������Ӧ���±�

Status InitQueue(SqQueue* Q);                                   // ˳��ӳ�ʼ��
Status EntryQ(SqQueue* Q, QElemType e);                         // ˳������
Status OutQ(SqQueue* Q, QElemType* e);                          // ˳��ӳ���
Status IsEmpty(SqQueue* Q);                                     // ˳����ж�Ϊ��

void DFS_AL(ALGraph* G, int v, bool* visit);                    // ������ȱ�����ʵ�ֺ�����
void DFS_ALGraph(ALGraph* G, VertexType v);                     // ������ȱ�������װ������

void BFS_AL(ALGraph* G, int v, bool* visit);                    // ������ȱ�����������װ��
void BFS_ALGraph(ALGraph* G, VertexType v);                     // ������ȱ�����������װ��

int Min_Uset(Uset* U, int n);                                   // ��С�㼯
void MST_Prime(ALGraph* G, VertexType v);                       // Prim�㷨��С������

void Sort_Eset(Eset* E, int length);                            // ð������
void InitEset(Eset* E, ALGraph* G);                             // ��ʼ���߼�
void MST_Kruskal(ALGraph* G);                                   // Kruskal�㷨��С������

void Dijkstra(ALGraph* G, VertexType start);                    // ���·��Dijkstra�㷨
void PrintPath(ALGraph* G, int prev[], int start, int end);     // ��ӡ���·��