#include "headers.h"

void writeFile(bTree *tree, bTreeNode *p, int pos)
{
    if (pos == -1)
    {
        pos = tree->nextPos++;
    }

    puts("=================write File===================");
    printNoArvore(p);
    puts("==============================================");

    fseek(tree->fp, pos * sizeof(bTreeNode), SEEK_SET);
    fwrite(p, sizeof(bTreeNode), 1, tree->fp);
}

void writeFileRecord(bTree *tree, int codigoLivro, char titulo[], char nomeCompletoPrimeiroAutor[], int anoPublicacao, int pos)
{
    if (pos == -1)
    {
        pos = tree->nextPos++;
    }

    FILE *fData = fopen("data.dat", "w");
    recordNode *registry = malloc(sizeof(recordNode));

    registry->valid = true;
    registry->codigoLivro = codigoLivro;
    registry->anoPublicacao = anoPublicacao;
    strcpy(registry->titulo, titulo);
    strcpy(registry->nomeCompletoPrimeiroAutor, nomeCompletoPrimeiroAutor);

    printNo(registry);
    puts("=================write file record===================");
    printf("código do livro: %i\ntítulo: %s\nautor: %s\nano de publicação: %i\npos: %i\n", codigoLivro, titulo, nomeCompletoPrimeiroAutor, anoPublicacao, pos);
    puts("=============================================");

    if (fseek(fData, pos * sizeof(recordNode), SEEK_SET) == 0)
    {
        puts("deu certo o writeFileRecord");
        fwrite(registry, sizeof(recordNode), 1, fData);
    }
}

void readFile(bTree *tree, bTreeNode *p, int pos)
{
    puts("entrei no readFile");
    fseek(tree->fp, pos * sizeof(bTreeNode), SEEK_SET);
    fread(p, sizeof(bTreeNode), 1, tree->fp);
}
