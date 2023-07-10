#include "headers.h"

void printArvore(bTree *arvore)
{
    printf("nome do arquivo da árvore: %s\nponteiro para o arquivo da árvore: %p\nraíz: %i\npróxima posição: %i\n\n\n", arvore->fileName, arvore->fp, arvore->root, arvore->nextPos);
}

void printNo(recordNode *no)
{
    printf("é valido: %i\ncódigo do livro: %i\ntítulo: %s\nautor: %s\nano de publicação: %i\n\n\n", no->valid, no->codigoLivro, no->titulo, no->nomeCompletoPrimeiroAutor, no->anoPublicacao);
}

void printNoArvore(bTreeNode *no)
{
    printf("é valido: %i\nnúmero de registros: %i\né folha: %i\nposição: %i\n", no->valid, no->noOfRecs, no->isLeaf, no->pos);

    puts("keyRecArr:");
    for (int i = 0; i < 2 * t - 1; i++)
        printf("  %i", no->keyRecArr[i]);

    puts("");
    puts("posRecArr:");
    for (int i = 0; i < 2 * t - 1; i++)
        printf("  %i", no->posRecArr[i]);

    puts("");
    puts("children:");
    for (int i = 0; i < 2 * t; i++)
        printf("  %i", no->children[i]);

    printf("\n");
}

void printArqData()
{
    FILE *fptr = fopen("data.dat", "a+");
    if (fptr != NULL)
    {
        char caractere;
        puts("vou printar o data.dat");
        caractere = fgetc(fptr);
        while (caractere != EOF)
        {
            printf("%c", caractere);
            caractere = fgetc(fptr);
        }
    }
    fclose(fptr);
}

void printArqIndice()
{
    FILE *fptr = fopen("indice.dat", "r");
    if (fptr != NULL)
    {
        char caractere;
        puts("vou printar o indice.dat");
        caractere = fgetc(fptr);
        while (caractere != EOF)
        {
            printf("%c", caractere);
            caractere = fgetc(fptr);
        }
    }
    fclose(fptr);
}

void dispNode(bTreeNode *node)
{
    printf("Position in node:%d\n", node->pos);
    printf("Number of Records:%d\n", node->noOfRecs);
    printf("Is leaf?:%d\n", node->isLeaf);
    printf("CodigoLivro:\n");
    for (int i = 0; i < node->noOfRecs; i++)
    {
        printf("%d ", node->keyRecArr[i]);
    }
    printf("\n");
    printf("Links:\n");
    for (int i = 0; i < 2 * t; ++i)
    {
        printf("%d ", node->children[i]);
    }
    printf("\n");
    printf("\n");
}

// aparentemente, imprime a árvore completa
void traverse(bTree *tree, int root)
{

    if (-1 == root)
    {
        return;
    }

    bTreeNode *toPrint = malloc(sizeof(bTreeNode));
    readFile(tree, toPrint, root);
    dispNode(toPrint);

    for (int i = 0; i < 2 * t; i++)
    {
        traverse(tree, toPrint->children[i]);
    }

    free(toPrint);
}

// imprime o nó da árvore

void hardPrint(bTree *tree)
{
    bTreeNode *lido = (bTreeNode *)malloc(sizeof(bTreeNode));
    for (int i = 0; i < tree->nextPos; i++)
    {
        fseek(tree->fp, i * sizeof(bTreeNode), SEEK_SET);
        fread(lido, sizeof(bTreeNode), 1, tree->fp);

        if (lido->isLeaf <= 1)
            dispNode(lido);
        else
            printf("ERRO: isLeaf = %i\n\n", lido->isLeaf);
    }

    free(lido);
}

void doublePrint(bTree *tree)
{
    printf("=================");
    printf("\nTraverse\n");
    traverse(tree, tree->root);

    printf("=================");
    printf("\nHard print\n");
    hardPrint(tree);
}