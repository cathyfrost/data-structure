#include <stdio.h>
#include <stdlib.h>

// 定义节点结构体
typedef struct Node {
    int data;            // 数据
    struct Node* next;   // 指向下一个节点的指针
} Node;

// 定义图结构体
typedef struct Graph {
    int numVertices;     // 图中顶点的数量
    Node** adjacencyList; // 邻接表，存储每个顶点的邻接链表
} Graph;

// 创建新节点
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 创建图
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;

    // 为邻接表分配内存
    graph->adjacencyList = (Node**)malloc(numVertices * sizeof(Node*));
    for (int i = 0; i < numVertices; i++) {
        graph->adjacencyList[i] = NULL;
    }

    return graph;
}

// 添加边
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;
}

// 深度优先搜索
void DFS(Graph* graph, int vertex, int* visited) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    Node* temp = graph->adjacencyList[vertex];
    while (temp != NULL) {
        int connectedVertex = temp->data;
        if (!visited[connectedVertex]) {
            DFS(graph, connectedVertex, visited);
        }
        temp = temp->next;
    }
}

// 广度优先搜索
void BFS(Graph* graph, int startVertex, int* visited) {
    int queue[graph->numVertices];
    int front = 0, rear = 0;

    visited[startVertex] = 1;
    printf("%d ", startVertex);
    queue[rear++] = startVertex;

    while (front < rear) {
        int currentVertex = queue[front++];
        Node* temp = graph->adjacencyList[currentVertex];

        while (temp != NULL) {
            int connectedVertex = temp->data;
            if (!visited[connectedVertex]) {
                printf("%d ", connectedVertex);
                visited[connectedVertex] = 1;
                queue[rear++] = connectedVertex;
            }
            temp = temp->next;
        }
    }
}

int main() {
    int numVertices = 10;
    Graph* graph = createGraph(numVertices);

    // 用户输入有向边
    printf("请输入有向边 (源顶点 目标顶点)，以 -1 -1 结束:\n");
    int src, dest;
    scanf("%d %d", &src, &dest);
    while (src != -1 && dest != -1) {
        addEdge(graph, src, dest);
        scanf("%d %d", &src, &dest);
    }

    int* visited = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = 0;
    }

    printf("\n深度优先搜索 (DFS): ");
    DFS(graph, 0, visited);

    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = 0;
    }

    printf("\n广度优先搜索 (BFS): ");
    BFS(graph, 0, visited);

    return 0;
}
