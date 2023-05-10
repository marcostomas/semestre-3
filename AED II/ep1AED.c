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

static void freelist(link lst)
{
    if (lst != NULL)
    {
        freelist(lst->next);
        free(lst);
    }
}

// Esta é uma função-invólucro (= wrapper function). O serviço pesado é executado por freelist().
void GRAPHdestroy(Graph G)
{
    for (int v = 0; v < G->V; ++v)
        freelist(G->adj[v]);

    free(G->adj);
    free(G);
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

int GRAPHstrongCompsK(Graph G, int *sc)
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
    GRAPHdestroy(GR);
    return k;
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

void printGraph(Graph graph)
{
    for (int i = 0; i < graph->V; ++i)
    {
        link temp = graph->adj[i];
        printf("\n%d: ", temp->w); // Segmentation fault
        while (temp)
        {
            printf("%d; ", temp->w);
            temp = temp->next;
        }
    }
}

// bool createArcs(Graph g, int *LFpositions, int LFposintionsLivre, char *string)
// {
//     char verticesVizinhos[g->V][12];
//     int vvColLivre = 0, vvPosLivre = 0;
//     int caractere, caractereIndice;

//     // Colocamos cada nó em uma posição da matriz. Cada coluna da matriz representa um nó. Todos as linhas de cada coluna representam os vizinhos. No pior dos casos, isto é, o grafo é denso, então gastamos O(n²).
//     for (int j = 0; j < LFposintionsLivre; j++)
//     {
//         for (int n = LFpositions[j] + 4; n < LFpositions[j + 1]; n++)
//         {
//             if (string[n] != 10 && string[n] != 32 && string[n] != 58 && string[n] != 59)
//             {
//                 verticesVizinhos[vvColLivre][vvPosLivre] = string[n];
//                 (vvPosLivre) = (vvPosLivre) + 1;
//                 caractereIndice = conversorC(string[LFpositions[j] + 1]);
//                 caractere = conversorC(string[n]);
//                 GRAPHinsertArc(g, caractereIndice, caractere);
//             }
//         }
//         vvColLivre++;
//         vvPosLivre = 0;
//     }

//     for (int a = 0; a < vvColLivre; a++)
//     {
//         for (int b = 0; b < 12; b++)
//             if (verticesVizinhos[a][b])
//                 printf("%c\t", verticesVizinhos[a][b]);

//         printf("\n");
//     }

//     return true;
// }

int main()
{
    int V, A, posToken = 1, lenLine;
    char *aleatorio = "random";

    printf("Digite o número de vértices: ");
    scanf("%d", &V);

    Graph G = GRAPHinit(V);

    char vertexV, vertexW, line[V * 3], *token;

    for (vertex v = 0; v < V; ++v)
    {
        puts("\nDigite uma posição da lista de adjacência. Se quiser um grafo aleatório, digite: random \n");
        scanf(" %[^\n]", line);
        puts("\n");

        if (strcmp(line, aleatorio) == 0)
        {
            puts("Você digitou 'random'. Agora, digite um número de vértices ");
            scanf("%d", &A);

            G = GRAPHrandER(V, A);

            printGraph(G);
            return 0;
        }
        else
        {
            lenLine = strlen(line);
            token = strtok(line, ":");
            vertexV = conversorC(token[0]);

            while (posToken < lenLine)
            {

                /*
                    TABELA DE CONVERSÂO DE CARACTERES
                    0: (\000) ~poderia substituir por NULL tb
                    10: (\n)
                    32: ( )
                    58: (:)
                    59: (;)
                */
                // Tá passando /000
                if (token[posToken] != 0 && token[posToken] != 10 && token[posToken] != 32 && token[posToken] != 58 && token[posToken] != 59 && token[posToken] != NULL)
                {
                    vertexW = conversorC(token[posToken]);
                    GRAPHinsertArc(G, vertexV, vertexW);
                }
                posToken++;
            }

            posToken = 1;
        }
    }

    int sc[V - 1];
    int numSC = GRAPHstrongCompsK(G, sc);

    printf("%d\n", numSC);
    printGraph(G);

    return 0;
}