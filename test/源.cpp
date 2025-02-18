#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

/* ===预定义=== */
#define MAX_VEX_NUM 10
#define INF 2147483647

typedef int VertexType;            //顶点数据类型
typedef int EdgeType;               //边权值
bool visited[MAX_VEX_NUM];      //全局数组  负责BFS与DFS时的顶点访问标记
/* ===辅助队列=== */
//存储结构循环队列
typedef struct {
    int data[MAX_VEX_NUM];         //字符型
    int front;          //队头
    int rear;           //队尾
} SqQueue;
//初始化
void InitQueue(SqQueue& q) {
    q.front = q.rear = 0;       //做法一 队头指向队首元素 队尾指向队尾元素下一位置 === 先入队再更新队尾  先出队再更细队头
    //q.front = q.rear = MAX_VEX_NUM - 1; //做法二 队头指向队首元素前一位置 队尾指向队尾元素 === 先更新队尾再入队 先更新队头再出队
}
//数据结构中增加元素个数计数器/数据结构中增加标识tag区分空满/牺牲一个存储位置
//判空一 队满条件为(q.rear+1)%MAX_VEX_NUM==q.front
bool QueueEmpty(SqQueue q) {
    if (q.front == q.rear) {
        return true;
    }
    else {
        return false;
    }
}
//入队
bool EnQueue(SqQueue& q, int x) {
    if ((q.rear + 1) % MAX_VEX_NUM == q.front) {        //队尾下一位置等于队头了 本方法牺牲一个存储单元
        return false;
    }
    q.data[q.rear] = x;
    q.rear = (q.rear + 1) % MAX_VEX_NUM;        //移动队列尾
    return true;
}
//出队
bool DeQueue(SqQueue& q, int& x) {
    if (q.front == q.rear) {
        return false;
    }
    x = q.data[q.front];
    q.front = (q.front + 1) % MAX_VEX_NUM;
    return true;
}
/* ===辅助队列=== */

/* ===辅助栈=== */
typedef struct {
    int data[MAX_VEX_NUM];
    int top;        //栈顶指针
} SqStack;
//初始化
void InitStack(SqStack& s) {     //不加引用无法正确初始化！！！
    s.top = -1;     //栈顶指针指向当前元素，插入时先++再插入
}
//判断空,栈空返回1，不空返回0
bool StackEmpty(SqStack s) {
    if (s.top == -1) {
        return true;
    }
    else {
        return false;
    }
}
//入栈
bool Push(SqStack& s, int x) {
    if (s.top == MAX_VEX_NUM - 1) {
        return false;
    }
    s.data[++s.top] = x;      //先加加
    return true;
}
//出栈
bool Pop(SqStack& s, int& x) {
    if (s.top == -1) {
        return false;
    }
    x = s.data[s.top--];      //先出栈再减一
    return true;
}
//取栈顶元素
bool GetTop(SqStack s, int& x) {
    if (s.top == -1) {
        return false;
    }
    x = s.data[s.top];
    return true;
}
/* ===辅助栈=== */

/*===邻接表结构===*/
//边表结点
typedef struct ArcNode {
    int adjvex;     //以上一个顶点起始的边 所指向结尾顶点 在顶点表中的下标
    EdgeType weight;        //边权值
    struct ArcNode* nextarc;        //指向边表下一个结点
}ArcNode;
//顶点表结点
typedef struct VexNode {
    VertexType data;        //顶点的数据域
    int degree;     //度数
    ArcNode* firstarc;       //指向第一条出边 也就是指向第一个邻接顶点
} VexNode, AdjList[MAX_VEX_NUM];       //结构体数组    即为一个顺序存储的顶点表  用来保存顶点信息
//邻接表
typedef struct AdjacentList {
    AdjList List;
    int vexnum;
    int edgenum;
}ALGraph, * AdjListGraph;

/* ===建立邻接表=== */
void CreateGraph_AdjList(AdjListGraph& G) {
    int numV, numE;     //要创建图的总顶点数与边数
    //建立初始结构
    printf("输入图的总顶点数与边数，使用空格隔开: ");
    scanf_s("%d%d", &numV, &numE);
    if (numV > MAX_VEX_NUM) {
        printf("结点数超出限制！\n");
        return;
    }
    G = (ALGraph*)malloc(sizeof(ALGraph));
    G->vexnum = numV;
    G->edgenum = numE;
    printf("\n");

    int i, j;       //遍历控制器
    int start, end;     //一条弧的弧尾与弧头结点序号
    int w;      //弧权值

    //设置顶点表List 输入顶点信息存入list的data域并初始化firstarc指针域
    for (i = 0; i < G->vexnum; i++) {
        printf("请输入第%d个结点的信息: ", i + 1);
        scanf_s("%d", &G->List[i].data);
        G->List[i].firstarc = NULL;     //初始化firstarc域
        G->List[i].degree = -1;
    }
    printf("\n");

    //创建边表数据
    for (i = 0; i < G->edgenum; i++) {
        printf("依次输入第%d条边的'起始节点序号start','结束结点序号end','权值w',使用空格隔开(satrt与end在(1,...,n)取值)\n: ", i + 1);
        scanf_s("%d%d%d", &start, &end, &w);
        printf("在无向图G中建立权值为%d的边(V%d,V%d)...\n", w, start, end);
        //注意无向图特性 邻接表中 边要记录两次
        //建立边<satrt,end>
        ArcNode* arc1 = (ArcNode*)malloc(sizeof(ArcNode));
        arc1->adjvex = end - 1;      //边的结束结点下标为end-1
        arc1->weight = w;        //权值
        /* 采用头插法将边结点插入到顶点表表头结点之后 */
        arc1->nextarc = G->List[start - 1].firstarc;
        G->List[start - 1].firstarc = arc1;
        /* 采用头插法将边结点插入到顶点表表头结点之后 */
        //建立边<end,start>,若建立有向图,无此步
        ArcNode* arc2 = (ArcNode*)malloc(sizeof(ArcNode));
        arc2->adjvex = start - 1;      //边的结束结点下标为start-1
        arc2->weight = w;          //权值
        /* 采用头插法将边结点插入到顶点表表头结点之后 */
        arc2->nextarc = G->List[end - 1].firstarc;
        G->List[end - 1].firstarc = arc2;
        /* 采用头插法将边结点插入到顶点表表头结点之后 */
    }
}


//DFS
void DFS(AdjListGraph G, int v) {
    if (G->List[v].data != INF) {
        printf("%d->", G->List[v].data);      //输出当前顶点信息
    }
    visited[v] = true;      //访问标记
    int w;      //w负责保存p的邻接点
    for (ArcNode* p = G->List[v].firstarc; p != NULL; p = p->nextarc) {
        //w = p->adjvex;      //w保存v的邻接点
        if (!visited[p->adjvex]) {        //若未访问 访问
            DFS(G, p->adjvex);
        }
        /* if(!visited[w]){        //若未访问 访问
            DFS(G, w);
        } */
    }
}
//DFSTravese
void DFSTraverse(AdjListGraph G) {
    memset(visited, false, MAX_VEX_NUM);        //初始化标记数组
    int v;
    for (v = 0; v < G->vexnum; v++) {
        if (!visited[v]) {      //如果顶点已被删除 不执行
            DFS(G, v);
        }
    }
    printf("^\n");
}

/* ===获取顶点在顶点表位置=== */
int GetVexPosition(AdjListGraph G, VertexType data) {
    int index = -1;         //返回的顶点表下标
    for (int i = 0; i < G->vexnum; i++) {
        if (G->List[i].data == data) {
            index = i;
            break;
        }
    }
    return index;
}

/* ===获取顶点的度数=== */
int GetVexDegree_Index(AdjListGraph G, int index) {
    int degree = G->List[index].degree;
    return degree;
}

/* ===获取边(start,end)的权值=== */
int GetEdgeWeight_Index(AdjListGraph G, int start, int end) {
    int weight = INF;
    for (ArcNode* p = G->List[start].firstarc; p; p = p->nextarc) {     //在start出边表找边
        if (p->adjvex == end) {
            weight = p->weight;
        }
    }
    return weight;
}


//邻接表实现迪杰斯特拉
/*
*start为起始顶点
*path[i]为辅助数组 表示源点v0到终点vi之间最短路径中 vi的前驱结点
*dist[i]表示起始顶点到i顶点最短路径长度
 */
void Dijkstra_AdjList(AdjListGraph G, VertexType vs, VertexType path[], int dist[]) {
    int i, j, k;
    int min;        //求取最短路径长度时使用
    int index;      //保存已经求出的最短路顶点在顶点表中下标
    int temp;       //缓存 判定路径长时防止溢出
    int start = GetVexPosition(G, vs);      //获取起始顶点下标
    bool flag[14];       //标记数组 标记顶点是否已经求出最短路径

    /* 1.初始化三个数组 */
    for (k = 0; k < G->vexnum; k++) {
        flag[k] = false;            //初始化访问数组
        path[k] = -1;               //初始化vi前驱结点为-1
        dist[k] = GetEdgeWeight_Index(G, start, k);         //初始化start到各个顶点的路径长度
    }
    // start顶点自身的dist与path数组也要初始化
    flag[start] = true;
    path[start] = -1;
    dist[start] = 0;

    /* 2.试探并求取顶点间最短路  n-1趟*/
    for (i = 0; i < G->vexnum - 1; i++) {
        //求出start到index的最短路
        min = INF;      //求取当前距离start最近的顶点
        for (j = 0; j < G->vexnum; j++) {
            if (!flag[j] && dist[j] < min) {
                min = dist[j];      //保存当前一轮中最小的路径长度
                index = j;          //保存对应最短路径长度的顶点在顶点表中下标
            }
        }
        flag[index] = true;     //标记index下标顶点已经求出当前轮的最短路
        // 修正当前最短路径和前驱顶点
        // 当已经求得"顶点index的最短路径"之后，更新"未获取最短路径的顶点的最短路径和前驱顶点"
        for (j = 0; j < G->vexnum; j++) {
            //加入已经求出最短路的index结点再进行试探 以便更新下一轮的dist与path
            temp = GetEdgeWeight_Index(G, index, j);
            temp = (temp == INF ? temp : min + temp);       //防止溢出
            if (!flag[j] && temp < dist[j]) {
                dist[j] = temp;
                path[j] = index;
            }
        }
    }

    // 打印dijkstra最短路径的结果
    printf("顶点V%d到其余顶点的最短路: \n", G->List[start].data);
    for (i = 0; i < G->vexnum; i++)
        printf("  shortest(V%d, V%d)=%d\n", G->List[start].data, G->List[i].data, dist[i]);
}