// Breadth First Search (BFS) on an undirected graph using adjacency matrix
#include <stdio.h>

#define MAX 20

int adj[MAX][MAX];      // adj[i][j] = 1 means an edge between i and j
int visited[MAX];
int queue[MAX], front = 0, rear = 0;

void bfs(int start, int n) {
    visited[start] = 1;
    queue[rear++] = start;               // put start into the queue

    while (front < rear) {
        int v = queue[front++];          // take the next vertex out
        printf("%d ", v);

        for (int i = 0; i < n; i++) {    // look at all neighbours of v
            if (adj[v][i] && !visited[i]) {
                visited[i] = 1;          // mark when added, so it is never added twice
                queue[rear++] = i;
            }
        }
    }
    printf("\n");
}

int main() {
    int n, e, u, v, start;

    printf("Enter number of vertices (0 to n-1): ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter each edge as two vertices (u v):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        adj[u][v] = adj[v][u] = 1;       // undirected: edge goes both ways
    }

    printf("Enter starting vertex: ");
    scanf("%d", &start);

    printf("BFS traversal: ");
    bfs(start, n);
    return 0;
}