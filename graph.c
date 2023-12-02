#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjacencyList;
} Graph;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;

    graph->adjacencyList = (Node**)malloc(numVertices * sizeof(Node*));
    for (int i = 0; i < numVertices; i++) {
        graph->adjacencyList[i] = NULL;
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;
}

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

    // User input for directed edges
    printf("Enter directed edges (source destination), end with -1 -1:\n");
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

    printf("\nDepth First Search (DFS): ");
    DFS(graph, 0, visited);

    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = 0;
    }

    printf("\nBreadth First Search (BFS): ");
    BFS(graph, 0, visited);

    return 0;
}
