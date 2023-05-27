#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100000

typedef struct node
{
    int vertex;
    struct node *next;
} node;

node *graph[MAX];
node *reverse_graph[MAX];
bool visited[MAX];
int stack[MAX], top = -1;

void add_edge(int, int);
void DFS(int);
void DFS_util(int, int[]);
void kosaraju(int);

int main()
{
    int vertices, edges, i, u, v;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    printf("Enter the number of edges: ");
    scanf("%d", &edges);
    for (i = 0; i < edges; i++)
    {
        printf("Enter the start and end vertices of edge %d: ", i + 1);
        scanf("%d%d", &u, &v);
        add_edge(u, v);
    }
    kosaraju(vertices);
    return 0;
}

void add_edge(int u, int v)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->vertex = v;
    new_node->next = graph[u];
    graph[u] = new_node;

    node *new_reverse_node = (node *)malloc(sizeof(node));
    new_reverse_node->vertex = u;
    new_reverse_node->next = reverse_graph[v];
    reverse_graph[v] = new_reverse_node;
}

void DFS(int vertex)
{
    visited[vertex] = true;
    node *ptr = graph[vertex];
    while (ptr != NULL)
    {
        if (!visited[ptr->vertex])
            DFS(ptr->vertex);
        ptr = ptr->next;
    }
    stack[++top] = vertex;
}

void DFS_util(int vertex, int scc[])
{
    visited[vertex] = true;
    scc[vertex] = 1;
    node *ptr = reverse_graph[vertex];
    while (ptr != NULL)
    {
        if (!visited[ptr->vertex])
            DFS_util(ptr->vertex, scc);
        ptr = ptr->next;
    }
}

void kosaraju(int vertices)
{
    int i, scc[MAX], scc_count = 0;
    for (i = 1; i <= vertices; i++)
        visited[i] = false;
    for (i = 1; i <= vertices; i++)
        if (!visited[i])
            DFS(i);
    for (i = 1; i <= vertices; i++)
        visited[i] = false;
    while (top >= 0)
    {
        int vertex = stack[top--];
        if (!visited[vertex])
        {
            int scc[MAX], count = 0, j;
            DFS_util(vertex, scc);
            printf("Strongly Connected Component %d: ", ++scc_count);
            for (j = 1; j <= vertices; j++)
            {
                if (scc[j] == 1)
                {
                    printf("%d ", j);
                    count++;
                }
            }
            printf("\n");
        }
    }
}

/*
Nesta implementação, nós usamos uma lista de adjacẽncia para representar o grafo e seu grafo reverso
    * A função add_edge() adiciona arestas para ambos os grafos
    * A função DFS() faz uma depth-first search no grafo e adiciona os vértices a uma pilha.
    * A função DFS_util() executa uma depth-first searh no grafo reverso, commeçando de uma vértice no topo da pilha e encontra o componente fortemente conectado.
    * Por fim, kosaraju() chama DFS() no grafo que chama DFS_util()
===============================================================================================================================================
In this implementation, we use an adjacency list to represent the graph and its reverse graph.
    * The add_edge() function adds edges to both graphs.
    * The DFS() function performs depth-first search on the graph and adds the vertices to a stack.
    * The DFS_util() function performs depth-first search on the reverse graph, starting from a vertex at the top of the stack, and finds the strongly connected component.
    * Finally, kosaraju() calls DFS() on the graph, then calls `DFS_util
*/