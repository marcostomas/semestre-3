#include "headers.h"
bTree *createTree(char *fileName, char *recordFileName, bool mode)
{
    bTree *tree = (bTree *)malloc(sizeof(bTree));

    if (!mode) // new file
    {
        strcpy(tree->fileName, fileName);
        tree->fp = fopen(fileName, "w");
        fclose(tree->fp);

        strcpy(tree->recordFileName, recordFileName);
        tree->fData = fopen(fileName, "w");
        fclose(tree->fData);

        tree->root = 0;
        tree->nextPos = 0;
        tree->nextRecPos = 0;
    }
    else
    {
        FILE *existingFile = fopen(fileName, "r");
        fread(tree, sizeof(bTree), 1, existingFile);
        fclose(existingFile);
    }

    // tree->fp = fopen(fileName, "r+");          // era r+. no contexto do trabalho, talvez a seja melhor
    // tree->fData = fopen(recordFileName, "r+"); // era r+. no contexto do trabalho, talvez a seja melhor

    return tree;
}

bTreeNode *nodeInit(bTreeNode *node, bool isLeaf, bTree *tree)
{
    node->valid = true;
    node->isLeaf = isLeaf;
    node->noOfRecs = 0;
    node->pos = tree->nextPos;
    (tree->nextPos)++;

    for (int i = 0; i < 2 * t - 1; ++i)
    {
        node->keyRecArr[i] = -1;
        node->posRecArr[i] = -1;
    }
    for (int i = 0; i < 2 * t; ++i)
    {
        node->children[i] = -1;
    }
    return node;
}

int findKey(bTreeNode *node, int k)
{
    int idx = 0;
    while (idx < node->noOfRecs && node->keyRecArr[idx] < k)
        ++idx;
    return idx;
}

void enterData(recordNode *record, bool valid, int id_num, char titulo[], char nomeCompletoPrimeiroAutor[], int anoPublicacao)
{
    record->valid = valid;
    record->codigoLivro = id_num;
    strcpy(record->titulo, titulo);
    strcpy(record->nomeCompletoPrimeiroAutor, nomeCompletoPrimeiroAutor);
    record->anoPublicacao = anoPublicacao;
}

void removeFromLeaf(bTree *tree, bTreeNode *node, int idx)
{
    for (int i = idx + 1; i < node->noOfRecs; ++i)
    {
        node->keyRecArr[i - 1] = node->keyRecArr[i];
    }
    node->noOfRecs--;
    writeFile(tree, node, node->pos);
}

void splitChild(bTree *tree, bTreeNode *x, int i, bTreeNode *y)
{
    bTreeNode *z = malloc(sizeof(bTreeNode));
    nodeInit(z, y->isLeaf, tree);
    z->noOfRecs = t - 1;

    int j;
    for (j = 0; j < t - 1; j++)
    {
        z->keyRecArr[j] = y->keyRecArr[j + t];
    }

    if (!y->isLeaf)
    {
        for (j = 0; j < t; j++)
        {
            z->children[j] = y->children[j + t];
            y->children[j + t] = -1;
        }
    }
    y->noOfRecs = t - 1;

    for (j = (x->noOfRecs); j >= i + 1; j--)
    {
        x->children[j + 1] = x->children[j];
    }

    x->children[i + 1] = z->pos;

    for (j = (x->noOfRecs) - 1; j >= i; j--)
    {
        x->keyRecArr[j + 1] = x->keyRecArr[j];
    }
    x->keyRecArr[i] = y->keyRecArr[t - 1];
    x->noOfRecs++;

    writeFile(tree, x, x->pos);
    writeFile(tree, y, y->pos);
    writeFile(tree, z, z->pos);
    free(z);
}

void insertNonFull(bTree *tree, bTreeNode *x, recordNode *record)
{
    int i = (x->noOfRecs) - 1;
    // printf("noOfRecs: %i\n", x->noOfRecs);
    // printf("codigo livro: %i\n", record->codigoLivro);
    if (x->isLeaf == true)
    {
        // puts("entrei no noh eh folha do insertNonFull");
        while ((i >= 0) && (record->codigoLivro < x->keyRecArr[i]))
        {
            // printf("keyRecArr[%i]: %i\n", i, x->keyRecArr[i]);
            x->keyRecArr[i + 1] = x->keyRecArr[i];
            i--;
        }
        x->keyRecArr[i + 1] = record;
        (x->noOfRecs)++;

        writeFile(tree, x, x->pos);
    }

    else
    {
        while ((i >= 0) && (record->codigoLivro < x->keyRecArr[i]))
        {
            i = i - 1;
        }
        bTreeNode *childAtPosi = malloc(sizeof(bTreeNode));
        readFile(tree, childAtPosi, x->children[i + 1]);

        if (childAtPosi->noOfRecs == (2 * t - 1))
        {
            splitChild(tree, x, i + 1, childAtPosi);
            if (x->keyRecArr[i + 1] < record->codigoLivro)
            {
                i++;
            }
        }

        readFile(tree, childAtPosi, x->children[i + 1]);
        insertNonFull(tree, childAtPosi, record);

        free(childAtPosi);
    }
}

void removeFromNonLeaf(bTree *tree, bTreeNode *node, int idx)
{

    int k = node->keyRecArr[idx];

    bTreeNode *child = malloc(sizeof(bTreeNode));
    bTreeNode *sibling = malloc(sizeof(bTreeNode));

    readFile(tree, child, node->children[idx]);
    readFile(tree, sibling, node->children[idx + 1]);

    if (child->noOfRecs >= t)
    {
        recordNode *pred = getPred(tree, node, idx);
        node->keyRecArr[idx] = pred;
        removeNode(tree, child, pred->codigoLivro);
    }

    else if (sibling->noOfRecs >= t)
    {
        recordNode *succ = getSucc(tree, node, idx);
        node->keyRecArr[idx] = succ;
        removeNode(tree, sibling, succ->codigoLivro);
    }

    else
    {
        child = merge(tree, node, idx);
        removeNode(tree, child, k);
        return;
    }

    writeFile(tree, child, child->pos);
    writeFile(tree, sibling, sibling->pos);

    free(child);
    free(sibling);
}

recordNode *getData(char *filepath, int len)
{

    recordNode *keyRecArr = malloc(sizeof(recordNode) * len); // array de recordNode*

    char titulo[30], autor[30], valid[6];
    int codigoLivro, anoPublicacao;
    char delim = ';';

    int file_no = 0;
    FILE *inpFile = fopen(filepath, "r");

    while (fscanf(inpFile, "%[^;];%i;%[^;];%[^;];%i\n", &valid, &codigoLivro, &titulo, &autor, &anoPublicacao) != EOF)
    {
        if (strcmp(valid, "true") == 0)
            enterData(&keyRecArr[file_no], true, codigoLivro, titulo, autor, anoPublicacao);
        else
            enterData(&keyRecArr[file_no], false, codigoLivro, titulo, autor, anoPublicacao);

        file_no++;
    }
    fclose(inpFile);
    return keyRecArr;
}

recordNode *searchRecursive(bTree *tree, int codigoLivro, bTreeNode *root)
{
    int i = 0;

    while (i < root->noOfRecs && codigoLivro > root->keyRecArr[i])
        i++;

    if (i < root->noOfRecs && codigoLivro == root->keyRecArr[i])
        return root->keyRecArr[i];

    else if (root->isLeaf)
    {
        return NULL;
    }
    else
    {
        bTreeNode *childAtPosi = malloc(sizeof(bTreeNode));
        readFile(tree, childAtPosi, root->children[i]);

        recordNode *found = searchRecursive(tree, codigoLivro, childAtPosi);
        free(childAtPosi);
        return found;
    }
}