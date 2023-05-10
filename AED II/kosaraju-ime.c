#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "conversor.h"

#define vertice int

static int cnt, pre[1000];
static int cntt, post[1000];
// static vertex vv[1000];
static vertice vvc[1000];

// A lista de adjacência de um vértice v é composta por nós do tipo node. Cada nó da lista corresponde a um arco e contém um vizinho w de v e o endereço do nó seguinte da lista. Um link é um ponteiro para um node.
struct node
{
    vertice w;
    struct node *next;
};
typedef struct node *link;

// A estrutura graph representa um grafo. O campo adj é um ponteiro para o vetor de listas de adjacência, o campo V contém o número de vértices e o campo A contém o número de arcos do grafo.
struct graph
{
    int V;
    int A;
    link *adj; // Lista dinâmica dos vértices. Cada vértice é um nó que aponta (se conecta) a outros nós. Aqui temos uma lista dinâmica, porque não sabemos previamente o número de vértices que nosso grafo terá
};
typedef struct graph *Graph;

// A função GRAPHinit() constrói um grafo com vértices 0 1 .. V-1 e nenhum arco.
Graph GRAPHinit(int V)
{
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = malloc(V * sizeof(link));
    for (int v = 0; v < V; ++v)
        G->adj[v] = NULL;
    return G;
}

// A função NEWnode() recebe um vértice w e o endereço next de um nó e devolve o endereço a de um novo nó tal que a->w == w e a->next == next.
link NEWnode(vertice w, link next)
{
    link a = (link)malloc(sizeof(struct node));

    a->w = w;
    a->next = next;
    return a;
}

// A função GRAPHinsertArc() insere um arco v - w no grafo G.A função supõe que v e w são distintos, positivos e menores que G->V.Se o grafo já tem um arco v - w, a função não faz nada.
void GRAPHinsertArc(Graph G, vertice v, vertice w)
{
    for (link a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w)
            return;
    G->adj[v] = NEWnode(w, G->adj[v]);
    G->A++;
}

// Constrói o reverso do grafo G.
Graph GRAPHreverse(Graph G)
{
    Graph GR = GRAPHinit(G->V);
    for (int v = 0; v < G->V; ++v)
        for (link a = G->adj[v]; a != NULL; a = a->next)
            GRAPHinsertArc(GR, a->w, v);
    return GR;
}

// Armazena no vetor post[] uma numeração em pós - ordem do grafo GR.O vetor pre[] marca os vértices já descobertos.
static void dfsR(Graph GR, vertice v)
{
    pre[v] = cnt++;
    for (link a = GR->adj[v]; a != NULL; a = a->next)
        if (pre[a->w] == -1)
            dfsR(GR, a->w);
    post[v] = cntt++;
}

// Atribui o rótulo k a todo vértice w ao alcance de v que ainda não foi rotulado. Os rótulos são armazenados no vetor sc[].
static void dfsRstrongCompsK(Graph G, vertice v, int *sc, int k)
{
    sc[v] = k;
    for (link a = G->adj[v]; a != NULL; a = a->next)
        if (sc[a->w] == -1)
            dfsRstrongCompsK(G, a->w, sc, k);
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

// Constrói um grafo aleatório com vértices 0..V-1 e número esperado de arcos igual a A. A função supõe que V >= 2 e A <= V*(V-1).
Graph GRAPHrandER(int V, int A)
{
    double prob = (double)A / (V * (V - 1));
    Graph G = GRAPHinit(V);
    for (int v = 0; v < V; ++v)
        for (int w = 0; w < V; ++w)
            if (v != w)
                if (rand() < prob * (RAND_MAX + 1.0))
                    GRAPHinsertArc(G, v, w);
    return G;
}

/* Esta função atribui um rótulo sc[v] (os rótulos são 0,1,2,...) a cada vértice v do grafo G de modo que dois vértices tenham o mesmo rótulo se e somente se os dois pertencem à mesma componente forte. A função devolve o número (quantidade) de componentes fortes de G. (A função implementa o algoritmo de Kosaraju. O código é adaptado do Programa 19.10 de Sedgewick.) */
int GRAPHstrongCompsK(Graph G, int *sc)
{
    // fase 1:
    Graph GR = GRAPHreverse(G);
    cnt = cntt = 0;
    vertice v;
    for (v = 0; v < GR->V; ++v)
        pre[v] = -1;
    for (v = 0; v < GR->V; ++v)
        if (pre[v] == -1)
            dfsR(GR, v);
    for (v = 0; v < GR->V; ++v)
        vvc[post[v]] = v;
    // vv[0..V-1] é permutação de GR em pós-ordem

    // fase 2:
    for (v = 0; v < G->V; ++v)
        sc[v] = -1;
    int k = 0;
    for (int i = G->V - 1; i >= 0; --i)
    {
        v = vvc[i];
        if (sc[v] == -1)
        { // nova etapa
            dfsRstrongCompsK(G, v, sc, k);
            k++;
        }
    }
    GRAPHdestroy(GR);
    return k;
}

bool createArcs(Graph g, int *LFpositions, int LFposintionsLivre, char *string)
{
    char verticesVizinhos[g->V][12];
    int vvColLivre = 0, vvPosLivre = 0;
    int caractere, caractereIndice;

    // Colocamos cada nó em uma posição da matriz. Cada coluna da matriz representa um nó. Todos as linhas de cada coluna representam os vizinhos. No pior dos casos, isto é, o grafo é denso, então gastamos O(n²).
    for (int j = 0; j < LFposintionsLivre; j++)
    {
        for (int n = LFpositions[j] + 4; n < LFpositions[j + 1]; n++)
        {
            if (string[n] != 10 && string[n] != 32 && string[n] != 58 && string[n] != 59)
            {
                verticesVizinhos[vvColLivre][vvPosLivre] = string[n];
                (vvPosLivre) = (vvPosLivre) + 1;
                caractereIndice = conversorC(string[LFpositions[j] + 1]);
                caractere = conversorC(string[n]);
                GRAPHinsertArc(g, caractereIndice, caractere);
            }
        }
        vvColLivre++;
        vvPosLivre = 0;
    }

    for (int a = 0; a < vvColLivre; a++)
    {
        for (int b = 0; b < 12; b++)
            if (verticesVizinhos[a][b])
                printf("%c\t", verticesVizinhos[a][b]);

        printf("\n");
    }

    return true;
}

void printGraph(Graph graph)
{
    for (int i = 0; i < graph->V; ++i)
    {
        link temp = graph->adj[i];
        printf("\n Adjacency list of vertex %d\n ", i);
        while (temp)
        {
            printf("%d -> ", temp->w);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        char nVerticesC = *argv[1];
        int nVertices = nVerticesC - '0'; // Convertendo de Char para int

        GRAPHinit(nVertices);
    }
    else
    {
        FILE *stream;
        char *string = (char *)malloc(70 * sizeof(char));

        stream = fopen("entrada.txt", "r");

        if (!stream)
        {
            printf("Arquino não encontrado!\n");
            return 1;
        }

        int nVertices = fgetc(stream) - '0'; // Convertendo de Char para int

        fread(string, 68 * sizeof(char), 1, stream);
        fclose(stream);

        char tipoAlgoritmoC;
        int tipoAlgoritmo, strLen = strlen(string);

        tipoAlgoritmoC = string[strLen - 1];
        tipoAlgoritmo = tipoAlgoritmoC - '0';

        Graph grafo = GRAPHinit(nVertices);
        printGraph(grafo);

        /*
            TABELA DE CONVERSÂO DE CARACTERES
            10: (\n)
            32: ( )
            58: (:)
            59: (;)
        */

        int *LFpositions = (int *)malloc(sizeof(int));
        int livre = 0;

        // Percorremos toda a string para encontrar as posições do caractere (\n). Gastamos O(n).
        for (int i = 0; i < strlen(string); i++)
            if (string[i] == 10)
            {
                LFpositions[livre] = i;
                livre++;
            }

        bool ret = createArcs(grafo, LFpositions, livre, string);
    }
    return 0;
}