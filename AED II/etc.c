/*
int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        int nVertices = fgetc(argv[1]) - '0'; // Convertendo de Char para int
        char tipoAlgoritmoC = argv[-1];
        int tipoAlgoritmo = tipoAlgoritmoC - '0';
        for (int i = 0; i < argc; i++)
        {
            printf("%c", argv[i]);
        }

        Graph grafo = GRAPHinit(nVertices);
    }


    return 0;

    // if (argc > 1 && !(strcmp(argv[1], "random")))
    // {
    //     Graph g;
    //     int V, A;
    //     puts("Digite um número de vértices: ");
    //     scanf("%i\n", &V);
    //     puts("Digite um número de arestas: ");
    //     scanf("%i\n", &A);
    //     g = GRAPHrandER(V, A);
    //     printGraph(g);
    // }
    // else
    // {
    //     FILE *stream;
    //     char *string = (char *)malloc(70 * sizeof(char));

    //     stream = fopen("entrada.txt", "r");

    //     if (!stream)
    //     {
    //         printf("Arquino não encontrado!\n");
    //         return 1;
    //     }

    //     int nVertices = fgetc(stream) - '0'; // Convertendo de Char para int

    //     fread(string, 68 * sizeof(char), 1, stream);
    //     fclose(stream);

    //     char tipoAlgoritmoC;
    //     int tipoAlgoritmo, strLen = strlen(string);

    //     tipoAlgoritmoC = string[strLen - 1];
    //     tipoAlgoritmo = tipoAlgoritmoC - '0';

    //     Graph grafo = GRAPHinit(nVertices);
    //     // printGraph(grafo);

    //     /*
    //         TABELA DE CONVERSÂO DE CARACTERES
    //         10: (\n)
    //         32: ( )
    //         58: (:)
    //         59: (;)
    //     */

//     int *LFpositions = (int *)malloc(sizeof(int));
//     int livre = 0;
//     // Percorremos toda a string para encontrar as posições do caractere (\n). Gastamos O(n).
//     for (int i = 0; i < strlen(string); i++)
//         if (string[i] == 10)
//         {
//             LFpositions[livre] = i;
//             livre++;
//         }

//     bool ret = createArcs(grafo, LFpositions, livre, string);
// }
return 0;
}
* /