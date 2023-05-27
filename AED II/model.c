#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

bool createArcs(Graph g, int *LFpositions, int LFposintionsLivre, char *string)
{
    char verticesVizinhos[g->V][g->V];
    int vvColLivre = 0, vvPosLivre = 0;

    // Colocamos cada nó em uma posição da matriz. Cada coluna da matriz representa um nó. Todos as linhas de cada coluna representam os vizinhos. No pior dos casos, isto é, o grafo é denso, então gastamos O(n²).
    for (int j = 0; j < LFposintionsLivre; j++)
    {
        for (int n = LFpositions[j] + 4; n < LFpositions[j + 1]; n++)
        {
            if (string[n] != 10 && string[n] != 32 && string[n] != 58 && string[n] != 59)
            {
                verticesVizinhos[vvColLivre][vvPosLivre] = string[n];
                vvPosLivre++;
                GRAPHinsertArc(g, string[LFpositions[j] + 1], string[n]);
            }
        }
        vvColLivre++;
        vvPosLivre = 0;
    }

    return true;
}

int main()
{
    FILE *stream;
    char *string = (char *)malloc(70 * sizeof(char));

    stream = fopen("entradaModel.txt", "r");

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
    return 0;
}