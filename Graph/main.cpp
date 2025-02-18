#include "head.h"

// ���¾�Ϊ���Ժ���
int main() {

    // ����ͼ
    ALGraph G;
    Creat_unALGraph_weighted(&G);

    // ����ͼ
    DFS_ALGraph(&G,'A');        // ������ȱ���
    BFS_ALGraph(&G,'A');        // ������ȱ���

    // ��С������
    MST_Prime(&G, 'A');             // Prime�㷨
    MST_Kruskal(&G);                // Kruskal�㷨

    // ���·��
    Dijkstra(&G,'A');

    return 0;
}

// ���������Ȩͼ
void Creat_unALGraph_weighted(ALGraph* G) {

    //��ʼ������ͱ߸���
    printf("�����붥��ĸ���:");
    scanf_s(" %d", &(*G).vertices);
    printf("������ߵĸ���:");
    scanf_s(" %d", &(*G).edges);

    //����������������
    printf("�����������������֣��������롰A B C��:");
    for (int i = 0; i < (*G).vertices; ++i) {
        scanf_s(" %c", &((*G).vertex[i].name));
        G->vertex[i].first = NULL;
    }

    // ���������
    VertexType v1, v2;          // һ���ߵĶ��������
    int index_v1, index_v2;     // �ߵĶ�����±�
    int weight;                 // Ȩֵ
    printf("������ߺ�Ȩֵ���������롰A B 10��������A��BΪ��������֣�10Ϊ�˱ߵ�Ȩֵ\n");

    for (int i = 0; i < G->edges; ++i) {
        printf("���ڵ�%d���ߣ�������ߺ�Ȩֵ��", i + 1);
        scanf_s(" %c", &v1);
        scanf_s(" %c", &v2);
        scanf_s(" %d", &weight);
        index_v1 = Locate_vertex(G, v1);
        index_v2 = Locate_vertex(G, v2);

        // ʹ��ͷ�巨�����½��
        // �����½ڵ�1
        EdgeNode* pnew1 = (EdgeNode*)malloc(sizeof(EdgeNode));
        pnew1->adjvertex = index_v2;
        pnew1->weight = weight;
        pnew1->next = G->vertex[index_v1].first;
        G->vertex[index_v1].first = pnew1;

        // �����½ڵ�2
        EdgeNode* pnew2 = (EdgeNode*)malloc(sizeof(EdgeNode));
        pnew2->adjvertex = index_v1;
        pnew2->weight = weight;
        pnew2->next = G->vertex[index_v2].first;
        G->vertex[index_v2].first = pnew2;
    }
}

// ��λ������������Ӧ���±�
int Locate_vertex(const ALGraph* G, char v1) {
    int flag = 0;
    for (int i = 0; i < G->vertices; ++i) {
        if (v1 == G->vertex[i].name) {
            flag = 1;
            return i;
        }
    }
    if (flag == 0) {
        printf("δ�ҵ���λ������������Ӧ���±�");
        return ERROR;
    }
    else {
        printf("������δ֪����");
        return ERROR;
    }
}

// ������ȱ�����������װ��
void DFS_ALGraph(ALGraph* G, VertexType v) {
    bool* visit = (bool*)malloc(sizeof(bool) * G->vertices);
    memset(visit, false, sizeof(bool) * G->vertices);   // ��ʼ��Ϊfalse
    int index = Locate_vertex(G, v);                    // �ҵ�������±�
    printf("��ͼ��������ȱ�������Ϊ��\n");
    DFS_AL(G, index, visit);                            // �Դ��±�Ϊ���㿪ʼ����
    printf("\n");
    free(visit);                                        // �ͷ��ڴ�
}
// ������ȱ�����ʵ�ֺ�����
void DFS_AL(ALGraph* G, int v, bool* visit) {
    printf("%c ", G->vertex[v].name);                   // ���ʶ���
    visit[v] = true;                                    // ���Ϊ�ѷ���
    EdgeNode* p = G->vertex[v].first;
    while (p) {
        int adj = p->adjvertex;
        if (!visit[adj]) {                              // ���δ���ʹ�
            DFS_AL(G, adj, visit);                      // �ݹ����
        }
        p = p->next;                                    // ������һ���ڽӵ�
    }
}

// ������ȱ�����������װ��
void BFS_ALGraph(ALGraph* G, VertexType v) {
    bool* visit = (bool*)malloc(sizeof(bool) * G->vertices);    // Ϊvisit����ռ�
    memset(visit, false, sizeof(bool) * G->vertices);           // ��ʼ��Ϊfalse
    int index = Locate_vertex(G, v);                            // �ҵ��±�
    printf("��ͼ�Ĺ�����ȱ�������Ϊ��\n");                     
    BFS_AL(G, index, visit);                                    // �Դ��±�Ϊ�������������
    free(visit);                                                // �ͷ�visit����
}
// ������ȱ�����ʵ�ֺ�����
void BFS_AL(ALGraph* G, int v, bool* visit) {
    SqQueue Q;
    InitQueue(&Q);
    EdgeNode* p;        // ���ڱ����ڽӱ�
    EntryQ(&Q, v);      // ��Ӷ���
    visit[v] = true;    // ���ö���visit����״̬
    char pop;           // ���ڽ��ն��е�������
    while (!IsEmpty(&Q)) {
        OutQ(&Q, &pop);
        printf("%c ", G->vertex[pop].name); // ���Ӻ��ӡ
        p = G->vertex[pop].first;           // ����p����

        while (p) {
            if (!visit[p->adjvertex]) {         // �ж�p�����е��ڽӵ��Ƿ񱻱�����
                EntryQ(&Q, p->adjvertex);       // ���û�б������������
                visit[p->adjvertex] = true;     // ͬʱ����visit״̬
            }
            p = p->next;
        }
    }
}

// ˳��ӳ�ʼ��
Status InitQueue(SqQueue* Q) {
    if (!(Q->base = (QElemType*)malloc(sizeof(QElemType) * QMAXSIZE)))
        exit(OVERFLOW);
    Q->front = Q->rere = 0;
    return OK;
}

// ˳������
Status EntryQ(SqQueue* Q, QElemType e) {
    if ((Q->rere + 1) % QMAXSIZE == Q->front) //�ж��Ƿ����
        return ERROR;
    Q->base[Q->rere] = e;
    Q->rere = (Q->rere + 1) % QMAXSIZE;
    return OK;
}

// ˳��ӳ���
Status OutQ(SqQueue* Q, QElemType* e) {
    if (Q->rere == Q->front) //�ж��Ƿ����
        return ERROR;
    *e = Q->base[Q->front];
    Q->front = (Q->front + 1) % QMAXSIZE; // Q->front++; Ϊ����д��
    return OK;
}

// ˳����ж�Ϊ��
Status IsEmpty(SqQueue* Q) {
    if (Q->front == Q->rere)
        return TRUE;
    else
        return FALSE;
}

// ��С������Prim�㷨
int Min_Uset(Uset* U, int n) {// �ҵ�Ȩֵ��С�ı߶�Ӧ��V-U�еĶ���
    int min = INT_MAX;          // ��ʼ����СȨֵΪ�������
    int pos = 0;                // ��¼Ȩֵ��С�ı߶�Ӧ�Ķ�����±�
    for (int i = 0; i < n; ++i) {
        if (U[i].weight != 0 && U[i].weight < min) {    // ������㻹���ڼ���U�У�����ȨֵС�ڵ�ǰ��СȨֵ�������
            min = U[i].weight;  // ������СȨֵ
            pos = i;            // ������СȨֵ�߶�Ӧ�Ķ����±�
        }
    }
    return pos;
}
void MST_Prime(ALGraph* G, VertexType v) {
    // ��ʼ����СȨֵ����U
    int u = Locate_vertex(G, v);    // ��λ��ʼ������ͼ�е��±�
    Uset* U = (Uset*)malloc(sizeof(Uset) * G->vertices);
    for (int i = 0; i < G->vertices; ++i) {
        U[i].weight = MaxWeight;
        U[i].adjvertex = u;
    }

    // ��ʼ������뼯��U��Ȩֵ����Ϊ0
    U[u].weight = 0;

    // ������ʼ������ڽӱ�
    EdgeNode* p = G->vertex[u].first;
    while (p) {
        U[p->adjvertex].weight = p->weight;
        p = p->next;
    }

    // �������ඥ�㣬������С������
    printf("�������Prime�㷨����С������\n");
    for (int i = 1; i < G->vertices; ++i) {

        // �ҵ�����V-U���뼯��UȨֵ��С�ı߶�Ӧ�Ķ��㲢��ӡ
        int min = Min_Uset(U, G->vertices);
        int u_0 = U[min].adjvertex;
        printf("%c->%c ", G->vertex[u_0].name, G->vertex[min].name);

        // �����ҵ��Ķ���
        U[min].weight = 0;  
        // ������СȨֵ����
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

// ��С������Kruskal�㷨
void Sort_Eset(Eset* E, int length) {   // ð��������
    bool flag = true;   // ���ñ�־
    for (int i = 0; i < length - 1 && flag; ++i) {
        flag = false;   // ����δ����
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
void InitEset(Eset* E, ALGraph* G) {    // ��ʼ���߼�����
    Eset* p_E = E; 
    // ����ͼ�е�ÿ������
    for (int i = 0; i < G->vertices; ++i) {
        EdgeNode* p = G->vertex[i].first;

        // �����ڽӱ���ӱߵ��߼�����
        while (p) {
            if (i < p->adjvertex) { // ȷ��ÿ����ֻ���һ�Σ������ظ�
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
    // ����ռ䲢��ʼ���߼�����
    Eset* E = (Eset*)malloc(sizeof(Eset) * G->edges*2);
    InitEset(E, G);             // ��ʼ���߼�����
    Sort_Eset(E, G->edges);     // �Ա߼����鰴Ȩ������

    printf("�������Kruskal�㷨����С������\n");
    int V[MaxVertex];       // ���ڱ�ʾ���������ڵ���ͨ����
    // ��ʼ����ͨ��������
    for (int i = 0; i < G->vertices; ++i)
        V[i] = i;

    // �����߼������е�ÿ����
    for (int j = 0; j < G->edges; ++j) {
        int v_1 = E[j].start;       
        int v_2 = E[j].end;    
        int component_v_1 = V[v_1];
        int component_v_2 = V[v_2];

        // ������������ڲ�ͬ����ͨ�����У������
        if (component_v_1 != component_v_2) {
            printf("%c->%c ", G->vertex[v_1].name, G->vertex[v_2].name); 
            // �ϲ�������ͨ����
            for (int k = 0; k < G->vertices; ++k) {
                if (V[k] == component_v_2)
                    V[k] = component_v_1;
            }
        }
    }
    printf("\n");
    free(E);
}

// ���·��Dijkstra�㷨
void Dijkstra(ALGraph* G, VertexType start) {

    int dist[MaxVertex]; // �洢���·������
    int prev[MaxVertex]; // �洢���·����ǰһ������
    bool S[MaxVertex];   // ����Ƿ��Ѿ��ҵ����·��
    int start_p = Locate_vertex(G, start); // ��ʼ���������

    // ��ʼ��
    for (int i = 0; i < G->vertices; i++) {
        dist[i] = MaxWeight; // ��ʼ��Ϊ���Ȩֵ
        prev[i] = -1;        // ��ʼ��ǰ������Ϊ-1
        S[i] = false;        // ��ʼ��Ϊδ�ҵ����·��
    }
    dist[start_p] = 0;            // ��ʼ���㵽��������·��Ϊ0

    for (int i = 0; i < G->vertices; i++) {
        int minDist = MaxWeight;
        int v = -1;
        // �ҳ���ǰδ�����ʵ�����Ķ���
        for (int j = 0; j < G->vertices; j++) {
            if (!S[j] && dist[j] < minDist) {
                v = j;
                minDist = dist[j];
            }
        }

        if (v == -1) break; // ���ж��㶼�ѷ���
        S[v] = true;        // ��Ƕ���v�ѷ���

        // ���µ�ǰ����������ڽӵ�
        for (EdgeNode* p = G->vertex[v].first; p != NULL; p = p->next) {
            if (!S[p->adjvertex] && dist[v] + p->weight < dist[p->adjvertex]) {
                dist[p->adjvertex] = dist[v] + p->weight;
                prev[p->adjvertex] = v;
            }
        }
    }

    // ������·����Ϣ
    printf("��%c��ʼ����������·��Ϊ��\n", start);
    for (int i = 1; i < G->vertices; i++) {
        if (dist[i] == MaxWeight) {
            printf("�� %c �� %c û��·���ɴ�\n", start, G->vertex[i].name);
        }
        else {
            printf("%c��%c�����·������Ϊ��%d, ·��Ϊ��", start, G->vertex[i].name, dist[i]);
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

    // ��ӡ·��
    while (top > 0) {
        printf("%c -> ", G->vertex[stack[top--]].name);
    }
    printf("%c\n", G->vertex[stack[top]].name);
}