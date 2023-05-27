#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "conversor.h"

#define vertex int

static int cnt, pre[1000];
static int cntt, post[1000];
static vertex vv[1000];

// A lista de adjacência de um vértice v é composta por nós do tipo node. Cada nó da lista corresponde a um arco e contém um vizinho w de v e o endereço do nó seguinte da lista. Um link é um ponteiro para um node.
typedef struct node *link;
struct node
{
    vertex w;
    link next;
};

// A estrutura graph representa um grafo. O campo adj é um ponteiro para o vetor de listas de adjacência, o campo V contém o número de vértices e o campo A contém o número de arcos do grafo.
struct graph
{
    int V;
    int A;
    link *adj;
};
typedef struct graph *Graph;

// A função NEWnode() recebe um vértice w e o endereço next de um nó e devolve o endereço a de um novo nó tal que a->w == w e a->next == next.
static link NEWnode(vertex w, link next)
{
    link a = malloc(sizeof(struct node));
    a->w = w;
    a->next = next;
    return a;
}

// A função GRAPHinsertArc() insere um arco v - w no grafo G.A função supõe que v e w são distintos, positivos e menores que G->V.Se o grafo já tem um arco v - w, a função não faz nada.
void GRAPHinsertArc(Graph G, vertex v, vertex w)
{
    for (link a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w)
            return;
    G->adj[v] = NEWnode(w, G->adj[v]);
    G->A++;
}

// A função GRAPHinit() constrói um grafo com vértices 0 1 .. V-1 e nenhum arco.
Graph GRAPHinit(int V)
{
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = malloc(V * sizeof(link));

    for (vertex v = 0; v < V; ++v)
        G->adj[v] = NULL;

    return G;
}

void dfsR(Graph G, vertex v)
{
    link t;
    pre[v] = cnt++;

    for (t = G->adj[v]; t != NULL; t = t->next)
        if (pre[t->w] == -1)
            dfsR(G, t->w);

    post[v] = cntt++;
    vv[cntt - 1] = v;
}

Graph GRAPHreverse(Graph G)
{
    Graph GR = GRAPHinit(G->V);
    for (vertex v = 0; v < G->V; ++v)
        for (link a = G->adj[v]; a != NULL; a = a->next)
            GRAPHinsertArc(GR, a->w, v);
    return GR;
}

static void dfsRstrongCompsK(Graph G, vertex v, int *sc, int k)
{
    sc[v] = k;
    for (link a = G->adj[v]; a != NULL; a = a->next)
        if (sc[a->w] == -1)
            dfsRstrongCompsK(G, a->w, sc, k);
}

void printGraph(Graph g)
{
    if (g->V == 1)
        puts("Sim");
    else
        puts("Não");

    printf("%d\n", g->V);
    char letra;

    for (int i = 0; i < g->V; i++)
    {
        letra = desconversorC(g->adj[i]->w);
        printf("%c ", letra);
    }
    puts("");
    for (int i = 0; i < g->V; i++)
    {
        letra = desconversorC(g->adj[i]->w);
        printf("%c: ", letra);

        for (link aux = g->adj[i]; aux != NULL; aux = aux->next)
        {
            letra = desconversorC(aux->w);
            printf("%c; ", letra);
        }
        puts("");
    }
}

void GRAPHstrongCompsK(Graph G, int *sc)
{
    // fase 1:
    Graph GR = GRAPHreverse(G);
    cnt = cntt = 0;
    vertex v;
    for (v = 0; v < GR->V; ++v)
        pre[v] = -1;
    for (v = 0; v < GR->V; ++v)
        if (pre[v] == -1)
            dfsR(GR, v);
    for (v = 0; v < GR->V; ++v)
        vv[post[v]] = v;
    // vv[0..V-1] é permutação de GR em pós-ordem

    // fase 2:
    for (v = 0; v < G->V; ++v)
        sc[v] = -1;
    int k = 0;
    for (int i = G->V - 1; i >= 0; --i)
    {
        v = vv[i];
        if (sc[v] == -1)
        { // nova etapa
            dfsRstrongCompsK(G, v, sc, k);
            k++;
        }
    }
    printf("%i\n", k); // Número de scc
    printGraph(GR);
}

// Constrói um grafo aleatório com vértices 0..V-1 e número esperado de arcos igual a A. A função supõe que V >= 2 e A <= V*(V-1).
Graph GRAPHrandER(int V, int A)
{
    double prob = (double)A / (V * (V - 1));
    Graph G = GRAPHinit(V);
    for (vertex v = 0; v < V; ++v)
        for (vertex w = 0; w < V; ++w)
            if (v != w)
                if (rand() < prob * (RAND_MAX + 1.0))
                    GRAPHinsertArc(G, v, w);
    return G;
}

int main()
{
    char resposta[4];
    Graph g;

    puts("Deseja gerar um grafo aleatório? [yes\\no] ");
    scanf("%s", &resposta);
    puts("\n");

    if (strcmp(resposta, "yes") == 0)
    {

        int *scY = (int *)malloc((499) * sizeof(int));
        g = GRAPHrandER(30, 500);
        GRAPHstrongCompsK(g, scY);

        return 0;
    }
    else if (!strcmp(resposta, "no"))
    {
        int V, A, posToken = 1, lenLine;
        char vertexV, vertexW, *token;
        char line[V * 3];

        printf("Digite o número de vértices: ");
        scanf("%d", &V);
        g = GRAPHinit(V);

        for (vertex v = 0; v < V; ++v)
        {
            for (int i = 0; i < V * 3; i++)
                line[i] = 0;

            puts("\nDigite uma posição da lista de adjacência: ");
            scanf(" %[^\n]", &line);

            lenLine = strlen(line);
            token = strtok(line, ":");
            vertexV = conversorC(token[0]);

            while (posToken < lenLine)
            {

                if (token[posToken] != 0 && token[posToken] != 10 && token[posToken] != 32 && token[posToken] != 58 && token[posToken] != 59)
                {
                    vertexW = conversorC(token[posToken]);
                    GRAPHinsertArc(g, vertexV, vertexW);
                }
                posToken++;
            }

            posToken = 1;
        }
        printf("\nGRAFO UM\n");
        printGraph(g);
        printf("\nGRAFO UM - FIM \n");

        int *scN = (int *)malloc((V - 1) * sizeof(int));
        GRAPHstrongCompsK(g, scN);
        return 0;
    }
    else
    {
        puts("Não entendi a resposta! Cancelando...");
        return 0;
    }
}