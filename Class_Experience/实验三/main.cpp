#include "head.h"

// 以下均为测试函数
int main() {

    // 创建图
    ALGraph G;
    Creat_unALGraph_weighted(&G);

    // 遍历图
    DFS_ALGraph(&G,'A');        // 深度优先遍历
    BFS_ALGraph(&G,'A');        // 广度优先遍历

    // 最小生成树
    MST_Prime(&G, 'A');             // Prime算法
    MST_Kruskal(&G);                // Kruskal算法

    // 最短路径
    Dijkstra(&G,'A');

    return 0;
}

// 创建无向带权图
void Creat_unALGraph_weighted(ALGraph* G) {

    //初始化顶点和边个数
    printf("请输入顶点的个数:");
    scanf_s(" %d", &(*G).vertices);
    printf("请输入边的个数:");
    scanf_s(" %d", &(*G).edges);

    //输入各个顶点的名字
    printf("请输入各个顶点的名字，例如输入“A B C”:");
    for (int i = 0; i < (*G).vertices; ++i) {
        scanf_s(" %c", &((*G).vertex[i].name));
        G->vertex[i].first = NULL;
    }

    // 输入各个边
    VertexType v1, v2;          // 一条边的顶点的名字
    int index_v1, index_v2;     // 边的顶点的下标
    int weight;                 // 权值
    printf("请输入边和权值，例如输入“A B 10”，其中A和B为顶点的名字，10为此边的权值\n");

    for (int i = 0; i < G->edges; ++i) {
        printf("对于第%d条边，请输入边和权值：", i + 1);
        scanf_s(" %c", &v1);
        scanf_s(" %c", &v2);
        scanf_s(" %d", &weight);
        index_v1 = Locate_vertex(G, v1);
        index_v2 = Locate_vertex(G, v2);

        // 使用头插法创建新结点
        // 创造新节点1
        EdgeNode* pnew1 = (EdgeNode*)malloc(sizeof(EdgeNode));
        pnew1->adjvertex = index_v2;
        pnew1->weight = weight;
        pnew1->next = G->vertex[index_v1].first;
        G->vertex[index_v1].first = pnew1;

        // 创造新节点2
        EdgeNode* pnew2 = (EdgeNode*)malloc(sizeof(EdgeNode));
        pnew2->adjvertex = index_v1;
        pnew2->weight = weight;
        pnew2->next = G->vertex[index_v2].first;
        G->vertex[index_v2].first = pnew2;
    }
}

// 定位顶点名字所对应的下标
int Locate_vertex(const ALGraph* G, char v1) {
    int flag = 0;
    for (int i = 0; i < G->vertices; ++i) {
        if (v1 == G->vertex[i].name) {
            flag = 1;
            return i;
        }
    }
    if (flag == 0) {
        printf("未找到定位顶点名字所对应的下标");
        return ERROR;
    }
    else {
        printf("发生了未知错误");
        return ERROR;
    }
}

// 深度优先遍历（函数封装）
void DFS_ALGraph(ALGraph* G, VertexType v) {
    bool* visit = (bool*)malloc(sizeof(bool) * G->vertices);
    memset(visit, false, sizeof(bool) * G->vertices);   // 初始化为false
    int index = Locate_vertex(G, v);                    // 找到顶点的下标
    printf("该图的深度优先遍历序列为：\n");
    DFS_AL(G, index, visit);                            // 以此下标为顶点开始遍历
    printf("\n");
    free(visit);                                        // 释放内存
}
// 深度优先遍历（实现函数）
void DFS_AL(ALGraph* G, int v, bool* visit) {
    printf("%c ", G->vertex[v].name);                   // 访问顶点
    visit[v] = true;                                    // 标记为已访问
    EdgeNode* p = G->vertex[v].first;
    while (p) {
        int adj = p->adjvertex;
        if (!visit[adj]) {                              // 如果未访问过
            DFS_AL(G, adj, visit);                      // 递归遍历
        }
        p = p->next;                                    // 访问下一个邻接点
    }
}

// 广度优先遍历（函数封装）
void BFS_ALGraph(ALGraph* G, VertexType v) {
    bool* visit = (bool*)malloc(sizeof(bool) * G->vertices);    // 为visit分配空间
    memset(visit, false, sizeof(bool) * G->vertices);           // 初始化为false
    int index = Locate_vertex(G, v);                            // 找到下标
    printf("该图的广度优先遍历序列为：\n");                     
    BFS_AL(G, index, visit);                                    // 以此下标为顶点出发，遍历
    free(visit);                                                // 释放visit数组
}
// 广度优先遍历（实现函数）
void BFS_AL(ALGraph* G, int v, bool* visit) {
    SqQueue Q;
    InitQueue(&Q);
    EdgeNode* p;        // 用于遍历邻接表
    EntryQ(&Q, v);      // 入队顶点
    visit[v] = true;    // 设置顶点visit数组状态
    char pop;           // 用于接收队列弹出数据
    while (!IsEmpty(&Q)) {
        OutQ(&Q, &pop);
        printf("%c ", G->vertex[pop].name); // 出队后打印
        p = G->vertex[pop].first;           // 利用p遍历

        while (p) {
            if (!visit[p->adjvertex]) {         // 判断p遍历中的邻接点是否被遍历过
                EntryQ(&Q, p->adjvertex);       // 如果没有被遍历过，入队
                visit[p->adjvertex] = true;     // 同时设置visit状态
            }
            p = p->next;
        }
    }
}

// 顺序队初始化
Status InitQueue(SqQueue* Q) {
    if (!(Q->base = (QElemType*)malloc(sizeof(QElemType) * QMAXSIZE)))
        exit(OVERFLOW);
    Q->front = Q->rere = 0;
    return OK;
}

// 顺序队入队
Status EntryQ(SqQueue* Q, QElemType e) {
    if ((Q->rere + 1) % QMAXSIZE == Q->front) //判断是否队满
        return ERROR;
    Q->base[Q->rere] = e;
    Q->rere = (Q->rere + 1) % QMAXSIZE;
    return OK;
}

// 顺序队出队
Status OutQ(SqQueue* Q, QElemType* e) {
    if (Q->rere == Q->front) //判断是否队满
        return ERROR;
    *e = Q->base[Q->front];
    Q->front = (Q->front + 1) % QMAXSIZE; // Q->front++; 为错误写法
    return OK;
}

// 顺序队判断为空
Status IsEmpty(SqQueue* Q) {
    if (Q->front == Q->rere)
        return TRUE;
    else
        return FALSE;
}

// 最小生成树Prim算法
int Min_Uset(Uset* U, int n) {// 找到权值最小的边对应的V-U中的顶点
    int min = INT_MAX;          // 初始化最小权值为最大整数
    int pos = 0;                // 记录权值最小的边对应的顶点的下标
    for (int i = 0; i < n; ++i) {
        if (U[i].weight != 0 && U[i].weight < min) {    // 如果顶点还不在集合U中，并且权值小于当前最小权值，则更新
            min = U[i].weight;  // 更新最小权值
            pos = i;            // 更新最小权值边对应的顶点下标
        }
    }
    return pos;
}
void MST_Prime(ALGraph* G, VertexType v) {
    // 初始化最小权值数组U
    int u = Locate_vertex(G, v);    // 定位起始顶点在图中的下标
    Uset* U = (Uset*)malloc(sizeof(Uset) * G->vertices);
    for (int i = 0; i < G->vertices; ++i) {
        U[i].weight = MaxWeight;
        U[i].adjvertex = u;
    }

    // 起始顶点加入集合U，权值设置为0
    U[u].weight = 0;

    // 遍历起始顶点的邻接表
    EdgeNode* p = G->vertex[u].first;
    while (p) {
        U[p->adjvertex].weight = p->weight;
        p = p->next;
    }

    // 遍历其余顶点，构建最小生成树
    printf("下面输出Prime算法的最小生成树\n");
    for (int i = 1; i < G->vertices; ++i) {

        // 找到集合V-U中与集合U权值最小的边对应的顶点并打印
        int min = Min_Uset(U, G->vertices);
        int u_0 = U[min].adjvertex;
        printf("%c->%c ", G->vertex[u_0].name, G->vertex[min].name);

        // 更新找到的顶点
        U[min].weight = 0;  
        // 更新最小权值数组
        EdgeNode* p_min = G->vertex[min].first; 
        while (p_min) {
            if (p_min->weight < U[p_min->adjvertex].weight) {
                U[p_min->adjvertex].adjvertex = min;
                U[p_min->adjvertex].weight = p_min->weight;
            }
            p_min = p_min->next;
        }
    }
    printf("\n");
    free(U);
}

// 最小生成树Kruskal算法
void Sort_Eset(Eset* E, int length) {   // 冒泡排序函数
    bool flag = true;   // 设置标志
    for (int i = 0; i < length - 1 && flag; ++i) {
        flag = false;   // 假设未排序
        for (int j = 0; j < length - 1 - i; ++j) {
            if (E[j].weight > E[j + 1].weight) {
                flag = true;
                Eset temp = E[j];
                E[j] = E[j + 1];
                E[j + 1] = temp;
            }
        }
    }
}
void InitEset(Eset* E, ALGraph* G) {    // 初始化边集数组
    Eset* p_E = E; 
    // 遍历图中的每个顶点
    for (int i = 0; i < G->vertices; ++i) {
        EdgeNode* p = G->vertex[i].first;

        // 遍历邻接表，添加边到边集数组
        while (p) {
            if (i < p->adjvertex) { // 确保每条边只添加一次，避免重复
                p_E->start = i;
                p_E->end = p->adjvertex;
                p_E->weight = p->weight;
                ++p_E;
            }
            p = p->next;
        }
    }
}
void MST_Kruskal(ALGraph* G) {
    // 分配空间并初始化边集数组
    Eset* E = (Eset*)malloc(sizeof(Eset) * G->edges*2);
    InitEset(E, G);             // 初始化边集数组
    Sort_Eset(E, G->edges);     // 对边集数组按权重排序

    printf("下面输出Kruskal算法的最小生成树\n");
    int V[MaxVertex];       // 用于表示各顶点所在的连通分量
    // 初始化连通分量数组
    for (int i = 0; i < G->vertices; ++i)
        V[i] = i;

    // 遍历边集数组中的每条边
    for (int j = 0; j < G->edges; ++j) {
        int v_1 = E[j].start;       
        int v_2 = E[j].end;    
        int component_v_1 = V[v_1];
        int component_v_2 = V[v_2];

        // 如果两个顶点在不同的连通分量中，则输出
        if (component_v_1 != component_v_2) {
            printf("%c->%c ", G->vertex[v_1].name, G->vertex[v_2].name); 
            // 合并两个连通分量
            for (int k = 0; k < G->vertices; ++k) {
                if (V[k] == component_v_2)
                    V[k] = component_v_1;
            }
        }
    }
    printf("\n");
    free(E);
}

// 最短路径Dijkstra算法
void Dijkstra(ALGraph* G, VertexType start) {

    int dist[MaxVertex]; // 存储最短路径长度
    int prev[MaxVertex]; // 存储最短路径的前一个顶点
    bool S[MaxVertex];   // 标记是否已经找到最短路径
    int start_p = Locate_vertex(G, start); // 起始顶点的索引

    // 初始化
    for (int i = 0; i < G->vertices; i++) {
        dist[i] = MaxWeight; // 初始化为最大权值
        prev[i] = -1;        // 初始化前驱顶点为-1
        S[i] = false;        // 初始化为未找到最短路径
    }
    dist[start_p] = 0;            // 起始顶点到自身的最短路径为0

    for (int i = 0; i < G->vertices; i++) {
        int minDist = MaxWeight;
        int v = -1;
        // 找出当前未被访问的最近的顶点
        for (int j = 0; j < G->vertices; j++) {
            if (!S[j] && dist[j] < minDist) {
                v = j;
                minDist = dist[j];
            }
        }

        if (v == -1) break; // 所有顶点都已访问
        S[v] = true;        // 标记顶点v已访问

        // 更新当前顶点的所有邻接点
        for (EdgeNode* p = G->vertex[v].first; p != NULL; p = p->next) {
            if (!S[p->adjvertex] && dist[v] + p->weight < dist[p->adjvertex]) {
                dist[p->adjvertex] = dist[v] + p->weight;
                prev[p->adjvertex] = v;
            }
        }
    }

    // 输出最短路径信息
    printf("从%c开始到各点的最短路径为：\n", start);
    for (int i = 1; i < G->vertices; i++) {
        if (dist[i] == MaxWeight) {
            printf("从 %c 到 %c 没有路径可达\n", start, G->vertex[i].name);
        }
        else {
            printf("%c到%c的最短路径长度为：%d, 路径为：", start, G->vertex[i].name, dist[i]);
            PrintPath(G,prev, Locate_vertex(G, start), i);
        }
    }
}
void PrintPath(ALGraph* G,int prev[], int start, int end) {
    int stack[MaxVertex];
    int top = -1;
    int v = end;

    while (v != start) {
        stack[++top] = v;
        v = prev[v];
    }
    stack[++top] = start;

    // 打印路径
    while (top > 0) {
        printf("%c -> ", G->vertex[stack[top--]].name);
    }
    printf("%c\n", G->vertex[stack[top]].name);
}