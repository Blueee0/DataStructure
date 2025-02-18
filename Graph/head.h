#pragma once
// 函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

// 函数库
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

// Status 是函数的类型，其值是函数结果状态代码
typedef int Status;

// 定义数据结构
#define MaxWeight 99999             // 最大权值
#define MaxVertex 20                // 最大顶点数
#define MaxDistance 99999           // 最长路径
typedef char VertexType;            // 顶点名字用字符表示
typedef char QElemType;             // 队列元素用字符表示

// 使用邻接表定义图的数据结构
typedef struct _EdgeNode {
    int adjvertex;                  // 定义vi的邻接点的位置
    _EdgeNode* next;                // 定义指向下一个邻接点的指针
    int weight;                     // 定义权值
}EdgeNode;

typedef struct _ALGNode {
    VertexType name;                // 定义顶点的名字
    EdgeNode* first;                // 定义指向其第一个邻接点的指针
}ALGNode;

typedef struct _ALGraph {
    ALGNode vertex[MaxVertex];      // 定义邻接表
    int edges, vertices;            // 定义顶点数和边数
}ALGraph;

// 定义队列的数据结构
#define QMAXSIZE 100
typedef char QElemType;
typedef struct __SqQueue {
    QElemType* base;
    int front, rere; //front为队头下标，rere为队尾下标(rere下标的位置不存放元素)
} SqQueue;

// Prim算法的辅助点集
struct Uset {
    int adjvertex;  //下标为i的点的邻接点
    int weight;     //当前权值
};

// Kruskal算法的辅助边集
struct Eset {
    int start;  //起点
    int end;    //终点
    int weight;
};

// 函数声明
void Creat_unALGraph_weighted(ALGraph* G);                      // 创建无向带权图
int Locate_vertex(const ALGraph* G, char v1);                   // 定位顶点名字所对应的下标

Status InitQueue(SqQueue* Q);                                   // 顺序队初始化
Status EntryQ(SqQueue* Q, QElemType e);                         // 顺序队入队
Status OutQ(SqQueue* Q, QElemType* e);                          // 顺序队出队
Status IsEmpty(SqQueue* Q);                                     // 顺序队判断为空

void DFS_AL(ALGraph* G, int v, bool* visit);                    // 深度优先遍历（实现函数）
void DFS_ALGraph(ALGraph* G, VertexType v);                     // 深度优先遍历（封装函数）

void BFS_AL(ALGraph* G, int v, bool* visit);                    // 广度优先遍历（函数封装）
void BFS_ALGraph(ALGraph* G, VertexType v);                     // 广度优先遍历（函数封装）

int Min_Uset(Uset* U, int n);                                   // 最小点集
void MST_Prime(ALGraph* G, VertexType v);                       // Prim算法最小生成树

void Sort_Eset(Eset* E, int length);                            // 冒泡排序
void InitEset(Eset* E, ALGraph* G);                             // 初始化边集
void MST_Kruskal(ALGraph* G);                                   // Kruskal算法最小生成树

void Dijkstra(ALGraph* G, VertexType start);                    // 最短路径Dijkstra算法
void PrintPath(ALGraph* G, int prev[], int start, int end);     // 打印最短路径