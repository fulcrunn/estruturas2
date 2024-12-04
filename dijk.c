#include <stdio.h>
#include <limits.h>

#define NUM_CIDADES 5
#define INFINITO INT_MAX

int minDistancia(int dist[], int visitado[]) {
    int min = INFINITO, min_index;
    for (int v = 0; v < NUM_CIDADES; v++)
        if (visitado[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void dijkstra(int grafo[NUM_CIDADES][NUM_CIDADES], int src) {
    int dist[NUM_CIDADES];
    int visitado[NUM_CIDADES] = {0};

    for (int i = 0; i < NUM_CIDADES; i++)
        dist[i] = INFINITO;
    dist[src] = 0;

    for (int count = 0; count < NUM_CIDADES - 1; count++) {
        int u = minDistancia(dist, visitado);
        visitado[u] = 1;

        for (int v = 0; v < NUM_CIDADES; v++)
            if (!visitado[v] && grafo[u][v] && dist[u] != INFINITO && dist[u] + grafo[u][v] < dist[v])
                dist[v] = dist[u] + grafo[u][v];
    }

    printf("Cidade\tDistância da Cidade A\n");
    for (int i = 0; i < NUM_CIDADES; i++)
        printf("%c\t%d\n", 'A' + i, dist[i]);
}

int main() {
    int grafo[NUM_CIDADES][NUM_CIDADES] = {
        {0, 4, 2, 7, 0},
        {4, 0, 1, 0, 1},
        {2, 1, 0, 3, 3},
        {7, 0, 3, 0, 2},
        {0, 1, 3, 2, 0}
    };

    dijkstra(grafo, 0); // 0 representa a cidade A
    return 0;
}