#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

/* ===Ԥ����=== */
#define MAX_VEX_NUM 10
#define INF 2147483647

typedef int VertexType;            //������������
typedef int EdgeType;               //��Ȩֵ
bool visited[MAX_VEX_NUM];      //ȫ������  ����BFS��DFSʱ�Ķ�����ʱ��
/* ===��������=== */
//�洢�ṹѭ������
typedef struct {
    int data[MAX_VEX_NUM];         //�ַ���
    int front;          //��ͷ
    int rear;           //��β
} SqQueue;
//��ʼ��
void InitQueue(SqQueue& q) {
    q.front = q.rear = 0;       //����һ ��ͷָ�����Ԫ�� ��βָ���βԪ����һλ�� === ������ٸ��¶�β  �ȳ����ٸ�ϸ��ͷ
    //q.front = q.rear = MAX_VEX_NUM - 1; //������ ��ͷָ�����Ԫ��ǰһλ�� ��βָ���βԪ�� === �ȸ��¶�β����� �ȸ��¶�ͷ�ٳ���
}
//���ݽṹ������Ԫ�ظ���������/���ݽṹ�����ӱ�ʶtag���ֿ���/����һ���洢λ��
//�п�һ ��������Ϊ(q.rear+1)%MAX_VEX_NUM==q.front
bool QueueEmpty(SqQueue q) {
    if (q.front == q.rear) {
        return true;
    }
    else {
        return false;
    }
}
//���
bool EnQueue(SqQueue& q, int x) {
    if ((q.rear + 1) % MAX_VEX_NUM == q.front) {        //��β��һλ�õ��ڶ�ͷ�� ����������һ���洢��Ԫ
        return false;
    }
    q.data[q.rear] = x;
    q.rear = (q.rear + 1) % MAX_VEX_NUM;        //�ƶ�����β
    return true;
}
//����
bool DeQueue(SqQueue& q, int& x) {
    if (q.front == q.rear) {
        return false;
    }
    x = q.data[q.front];
    q.front = (q.front + 1) % MAX_VEX_NUM;
    return true;
}
/* ===��������=== */

/* ===����ջ=== */
typedef struct {
    int data[MAX_VEX_NUM];
    int top;        //ջ��ָ��
} SqStack;
//��ʼ��
void InitStack(SqStack& s) {     //���������޷���ȷ��ʼ��������
    s.top = -1;     //ջ��ָ��ָ��ǰԪ�أ�����ʱ��++�ٲ���
}
//�жϿ�,ջ�շ���1�����շ���0
bool StackEmpty(SqStack s) {
    if (s.top == -1) {
        return true;
    }
    else {
        return false;
    }
}
//��ջ
bool Push(SqStack& s, int x) {
    if (s.top == MAX_VEX_NUM - 1) {
        return false;
    }
    s.data[++s.top] = x;      //�ȼӼ�
    return true;
}
//��ջ
bool Pop(SqStack& s, int& x) {
    if (s.top == -1) {
        return false;
    }
    x = s.data[s.top--];      //�ȳ�ջ�ټ�һ
    return true;
}
//ȡջ��Ԫ��
bool GetTop(SqStack s, int& x) {
    if (s.top == -1) {
        return false;
    }
    x = s.data[s.top];
    return true;
}
/* ===����ջ=== */

/*===�ڽӱ�ṹ===*/
//�߱���
typedef struct ArcNode {
    int adjvex;     //����һ��������ʼ�ı� ��ָ���β���� �ڶ�����е��±�
    EdgeType weight;        //��Ȩֵ
    struct ArcNode* nextarc;        //ָ��߱���һ�����
}ArcNode;
//�������
typedef struct VexNode {
    VertexType data;        //�����������
    int degree;     //����
    ArcNode* firstarc;       //ָ���һ������ Ҳ����ָ���һ���ڽӶ���
} VexNode, AdjList[MAX_VEX_NUM];       //�ṹ������    ��Ϊһ��˳��洢�Ķ����  �������涥����Ϣ
//�ڽӱ�
typedef struct AdjacentList {
    AdjList List;
    int vexnum;
    int edgenum;
}ALGraph, * AdjListGraph;

/* ===�����ڽӱ�=== */
void CreateGraph_AdjList(AdjListGraph& G) {
    int numV, numE;     //Ҫ����ͼ���ܶ����������
    //������ʼ�ṹ
    printf("����ͼ���ܶ������������ʹ�ÿո����: ");
    scanf_s("%d%d", &numV, &numE);
    if (numV > MAX_VEX_NUM) {
        printf("������������ƣ�\n");
        return;
    }
    G = (ALGraph*)malloc(sizeof(ALGraph));
    G->vexnum = numV;
    G->edgenum = numE;
    printf("\n");

    int i, j;       //����������
    int start, end;     //һ�����Ļ�β�뻡ͷ������
    int w;      //��Ȩֵ

    //���ö����List ���붥����Ϣ����list��data�򲢳�ʼ��firstarcָ����
    for (i = 0; i < G->vexnum; i++) {
        printf("�������%d��������Ϣ: ", i + 1);
        scanf_s("%d", &G->List[i].data);
        G->List[i].firstarc = NULL;     //��ʼ��firstarc��
        G->List[i].degree = -1;
    }
    printf("\n");

    //�����߱�����
    for (i = 0; i < G->edgenum; i++) {
        printf("���������%d���ߵ�'��ʼ�ڵ����start','����������end','Ȩֵw',ʹ�ÿո����(satrt��end��(1,...,n)ȡֵ)\n: ", i + 1);
        scanf_s("%d%d%d", &start, &end, &w);
        printf("������ͼG�н���ȨֵΪ%d�ı�(V%d,V%d)...\n", w, start, end);
        //ע������ͼ���� �ڽӱ��� ��Ҫ��¼����
        //������<satrt,end>
        ArcNode* arc1 = (ArcNode*)malloc(sizeof(ArcNode));
        arc1->adjvex = end - 1;      //�ߵĽ�������±�Ϊend-1
        arc1->weight = w;        //Ȩֵ
        /* ����ͷ�巨���߽����뵽������ͷ���֮�� */
        arc1->nextarc = G->List[start - 1].firstarc;
        G->List[start - 1].firstarc = arc1;
        /* ����ͷ�巨���߽����뵽������ͷ���֮�� */
        //������<end,start>,����������ͼ,�޴˲�
        ArcNode* arc2 = (ArcNode*)malloc(sizeof(ArcNode));
        arc2->adjvex = start - 1;      //�ߵĽ�������±�Ϊstart-1
        arc2->weight = w;          //Ȩֵ
        /* ����ͷ�巨���߽����뵽������ͷ���֮�� */
        arc2->nextarc = G->List[end - 1].firstarc;
        G->List[end - 1].firstarc = arc2;
        /* ����ͷ�巨���߽����뵽������ͷ���֮�� */
    }
}


//DFS
void DFS(AdjListGraph G, int v) {
    if (G->List[v].data != INF) {
        printf("%d->", G->List[v].data);      //�����ǰ������Ϣ
    }
    visited[v] = true;      //���ʱ��
    int w;      //w���𱣴�p���ڽӵ�
    for (ArcNode* p = G->List[v].firstarc; p != NULL; p = p->nextarc) {
        //w = p->adjvex;      //w����v���ڽӵ�
        if (!visited[p->adjvex]) {        //��δ���� ����
            DFS(G, p->adjvex);
        }
        /* if(!visited[w]){        //��δ���� ����
            DFS(G, w);
        } */
    }
}
//DFSTravese
void DFSTraverse(AdjListGraph G) {
    memset(visited, false, MAX_VEX_NUM);        //��ʼ���������
    int v;
    for (v = 0; v < G->vexnum; v++) {
        if (!visited[v]) {      //��������ѱ�ɾ�� ��ִ��
            DFS(G, v);
        }
    }
    printf("^\n");
}

/* ===��ȡ�����ڶ����λ��=== */
int GetVexPosition(AdjListGraph G, VertexType data) {
    int index = -1;         //���صĶ�����±�
    for (int i = 0; i < G->vexnum; i++) {
        if (G->List[i].data == data) {
            index = i;
            break;
        }
    }
    return index;
}

/* ===��ȡ����Ķ���=== */
int GetVexDegree_Index(AdjListGraph G, int index) {
    int degree = G->List[index].degree;
    return degree;
}

/* ===��ȡ��(start,end)��Ȩֵ=== */
int GetEdgeWeight_Index(AdjListGraph G, int start, int end) {
    int weight = INF;
    for (ArcNode* p = G->List[start].firstarc; p; p = p->nextarc) {     //��start���߱��ұ�
        if (p->adjvex == end) {
            weight = p->weight;
        }
    }
    return weight;
}


//�ڽӱ�ʵ�ֵϽ�˹����
/*
*startΪ��ʼ����
*path[i]Ϊ�������� ��ʾԴ��v0���յ�vi֮�����·���� vi��ǰ�����
*dist[i]��ʾ��ʼ���㵽i�������·������
 */
void Dijkstra_AdjList(AdjListGraph G, VertexType vs, VertexType path[], int dist[]) {
    int i, j, k;
    int min;        //��ȡ���·������ʱʹ��
    int index;      //�����Ѿ���������·�����ڶ�������±�
    int temp;       //���� �ж�·����ʱ��ֹ���
    int start = GetVexPosition(G, vs);      //��ȡ��ʼ�����±�
    bool flag[14];       //������� ��Ƕ����Ƿ��Ѿ�������·��

    /* 1.��ʼ���������� */
    for (k = 0; k < G->vexnum; k++) {
        flag[k] = false;            //��ʼ����������
        path[k] = -1;               //��ʼ��viǰ�����Ϊ-1
        dist[k] = GetEdgeWeight_Index(G, start, k);         //��ʼ��start�����������·������
    }
    // start���������dist��path����ҲҪ��ʼ��
    flag[start] = true;
    path[start] = -1;
    dist[start] = 0;

    /* 2.��̽����ȡ��������·  n-1��*/
    for (i = 0; i < G->vexnum - 1; i++) {
        //���start��index�����·
        min = INF;      //��ȡ��ǰ����start����Ķ���
        for (j = 0; j < G->vexnum; j++) {
            if (!flag[j] && dist[j] < min) {
                min = dist[j];      //���浱ǰһ������С��·������
                index = j;          //�����Ӧ���·�����ȵĶ����ڶ�������±�
            }
        }
        flag[index] = true;     //���index�±궥���Ѿ������ǰ�ֵ����·
        // ������ǰ���·����ǰ������
        // ���Ѿ����"����index�����·��"֮�󣬸���"δ��ȡ���·���Ķ�������·����ǰ������"
        for (j = 0; j < G->vexnum; j++) {
            //�����Ѿ�������·��index����ٽ�����̽ �Ա������һ�ֵ�dist��path
            temp = GetEdgeWeight_Index(G, index, j);
            temp = (temp == INF ? temp : min + temp);       //��ֹ���
            if (!flag[j] && temp < dist[j]) {
                dist[j] = temp;
                path[j] = index;
            }
        }
    }

    // ��ӡdijkstra���·���Ľ��
    printf("����V%d�����ඥ������·: \n", G->List[start].data);
    for (i = 0; i < G->vexnum; i++)
        printf("  shortest(V%d, V%d)=%d\n", G->List[start].data, G->List[i].data, dist[i]);
}