#include "headers.h"

void insert(bTree *tree, int codigoLivro, char titulo[], char nomeCompletoPrimeiroAutor[], int anoPublicacao)
{
    if (tree->nextPos == 0)
    {
        puts("entrei no if (nextPos == 0)\n");
        tree->root = tree->nextPos;
        bTreeNode *firstNode = malloc(sizeof(bTreeNode));
        nodeInit(firstNode, true, tree);

        firstNode->keyRecArr[0] = codigoLivro;
        (firstNode->noOfRecs)++;

        writeFileRecord(tree, codigoLivro, titulo, nomeCompletoPrimeiroAutor, anoPublicacao, firstNode->pos);
        writeFile(tree, firstNode, firstNode->pos);

        free(firstNode);
    }
    else
    {
        puts("entrei no else (nextPos != 0)\n");
        bTreeNode *rootCopy = malloc(sizeof(bTreeNode));
        readFile(tree, rootCopy, tree->root);

        writeFileRecord(tree, codigoLivro, titulo, nomeCompletoPrimeiroAutor, anoPublicacao, rootCopy->pos);

        puts("vou printar o último nó (bTreeNode) do indice.dat");
        printNoArvore(rootCopy);
        if (rootCopy->noOfRecs == (2 * t - 1))
        {
            puts("entrei no if (nó está cheio)");
            bTreeNode *newRoot = malloc(sizeof(bTreeNode));
            nodeInit(newRoot, false, tree);
            newRoot->children[0] = tree->root;

            splitChild(tree, newRoot, 0, rootCopy);

            int i = 0;
            if (newRoot->keyRecArr[0] < codigoLivro)
            {
                i++;
            }

            bTreeNode *childAtPosi = malloc(sizeof(bTreeNode));
            readFile(tree, childAtPosi, newRoot->children[i]);
            insertNonFull(tree, childAtPosi, codigoLivro);

            tree->root = newRoot->pos;

            free(newRoot);
            free(childAtPosi);
        }
        else
        {
            puts("entrei no if (nó não está cheio)");
            insertNonFull(tree, rootCopy, codigoLivro);
        }
        free(rootCopy);
    }
}

recordNode *search(bTree *tree, int codigoLivro)
{
    if (tree == NULL)
        puts("tree null");
    printf("código livro a ser buscado: %i", codigoLivro);

    bTreeNode *root = malloc(sizeof(bTreeNode));
    readFile(tree, root, tree->root);

    recordNode *result = searchRecursive(tree, codigoLivro, root);
    free(root);
    return result;
}

void removeNode(bTree *tree, bTreeNode *node, int k)
{

    int idx = findKey(node, k);
    recordNode *res = search(tree, k);
    if (idx < node->noOfRecs && res->codigoLivro == k)
    {
        if (node->isLeaf)
        {
            removeFromLeaf(tree, node, idx);
            res->valid = false;
        }
        else
        {
            removeFromNonLeaf(tree, node, idx);
            res->valid = false;
        }

        writeFile(tree, node, node->pos);
    }
    else
    {

        if (node->isLeaf)
        {
            return false;
        }

        bool flag = idx == node->noOfRecs;

        bTreeNode *childAtPosi = malloc(sizeof(bTreeNode));
        readFile(tree, childAtPosi, node->children[idx]);

        if (childAtPosi->noOfRecs < t)
        {
            fill(tree, node, idx);
            readFile(tree, childAtPosi, node->children[idx]);
        }

        if (flag && idx > node->noOfRecs)
        {
            bTreeNode *sibling = malloc(sizeof(bTreeNode));
            readFile(tree, sibling, node->children[idx - 1]);
            removeNode(tree, sibling, k);

            writeFile(tree, sibling, sibling->pos);
            free(sibling);
        }
        else
        {
            removeNode(tree, childAtPosi, k);
        }

        writeFile(tree, childAtPosi, childAtPosi->pos);
        free(childAtPosi);
    }
}

recordNode *getPred(bTree *tree, bTreeNode *node, int idx)
{
    bTreeNode *curr = malloc(sizeof(bTreeNode));
    readFile(tree, curr, node->children[idx]);

    while (!curr->isLeaf)
    {
        readFile(tree, curr, curr->children[curr->noOfRecs]);
    }

    recordNode *result = curr->keyRecArr[curr->noOfRecs - 1];
    free(curr);
    return result;
}

recordNode *getSucc(bTree *tree, bTreeNode *node, int idx)
{

    bTreeNode *curr = malloc(sizeof(bTreeNode));
    readFile(tree, curr, node->children[idx + 1]);
    while (!curr->isLeaf)
    {
        readFile(tree, curr, curr->children[0]);
    }

    recordNode *result = curr->keyRecArr[0];
    free(curr);
    return result;
}

void fill(bTree *tree, bTreeNode *node, int idx)
{
    bTreeNode *cPrev = malloc(sizeof(bTreeNode));
    bTreeNode *cSucc = malloc(sizeof(bTreeNode));

    readFile(tree, cPrev, node->children[idx - 1]);
    readFile(tree, cSucc, node->children[idx + 1]);

    if (idx != 0 && cPrev->noOfRecs >= t)
    {
        borrowFromPrev(tree, node, idx);
    }

    else if (idx != node->noOfRecs && cSucc->noOfRecs >= t)
    {
        borrowFromNext(tree, node, idx);
    }

    else
    {
        if (idx != node->noOfRecs)
            merge(tree, node, idx);
        else
            merge(tree, node, idx - 1);
    }

    free(cPrev);
    free(cSucc);

    return;
}

void borrowFromPrev(bTree *tree, bTreeNode *node, int idx)
{
    bTreeNode *child = malloc(sizeof(bTreeNode));
    bTreeNode *sibling = malloc(sizeof(bTreeNode));

    readFile(tree, child, node->children[idx]);
    readFile(tree, sibling, node->children[idx - 1]);

    for (int i = child->noOfRecs - 1; i >= 0; --i)
        child->keyRecArr[i + 1] = child->keyRecArr[i];

    if (!child->isLeaf)
    {
        for (int i = child->noOfRecs; i >= 0; --i)
            child->children[i + 1] = child->children[i];
    }

    child->keyRecArr[0] = node->keyRecArr[idx - 1];

    if (!node->isLeaf)
    {
        child->children[0] = sibling->children[sibling->noOfRecs];
        sibling->children[sibling->noOfRecs] = -1;
    }

    node->keyRecArr[idx - 1] = sibling->keyRecArr[sibling->noOfRecs - 1];

    child->noOfRecs += 1;
    sibling->noOfRecs -= 1;

    writeFile(tree, node, node->pos);
    writeFile(tree, child, child->pos);
    writeFile(tree, sibling, sibling->pos);

    free(child);
    free(sibling);

    return;
}

void borrowFromNext(bTree *tree, bTreeNode *node, int idx)
{

    bTreeNode *child = malloc(sizeof(bTreeNode));
    bTreeNode *sibling = malloc(sizeof(bTreeNode));

    readFile(tree, child, node->children[idx]);
    readFile(tree, sibling, node->children[idx + 1]);

    child->keyRecArr[(child->noOfRecs)] = node->keyRecArr[idx];

    if (!(child->isLeaf))
        child->children[(child->noOfRecs) + 1] = sibling->children[0];

    node->keyRecArr[idx] = sibling->keyRecArr[0];

    for (int i = 1; i < sibling->noOfRecs; ++i)
        sibling->keyRecArr[i - 1] = sibling->keyRecArr[i];

    if (!sibling->isLeaf)
    {
        for (int i = 1; i <= sibling->noOfRecs; ++i)
            sibling->children[i - 1] = sibling->children[i];

        sibling->children[sibling->noOfRecs] = -1; // RESPOSTA:
    }

    child->noOfRecs += 1;
    sibling->noOfRecs -= 1;

    writeFile(tree, node, node->pos);
    writeFile(tree, child, child->pos);
    writeFile(tree, sibling, sibling->pos);

    free(child);
    free(sibling);

    return;
}

bTreeNode *merge(bTree *tree, bTreeNode *node, int idx)
{

    bTreeNode *child = malloc(sizeof(bTreeNode));
    bTreeNode *sibling = malloc(sizeof(bTreeNode));

    readFile(tree, child, node->children[idx]);
    readFile(tree, sibling, node->children[idx + 1]);

    child->keyRecArr[t - 1] = node->keyRecArr[idx];

    for (int i = 0; i < sibling->noOfRecs; ++i)
        child->keyRecArr[i + t] = sibling->keyRecArr[i];

    if (!child->isLeaf)
    {
        for (int i = 0; i <= sibling->noOfRecs; ++i)
            child->children[i + t] = sibling->children[i];
    }

    for (int i = idx + 1; i < node->noOfRecs; ++i)
        node->keyRecArr[i - 1] = node->keyRecArr[i];

    for (int i = idx + 2; i <= node->noOfRecs; ++i)
        node->children[i - 1] = node->children[i];
    node->children[node->noOfRecs] = -1;
    child->noOfRecs += sibling->noOfRecs + 1;
    node->noOfRecs--;

    if (node->noOfRecs == 0)
    {
        tree->root = node->children[0];
    }

    writeFile(tree, node, node->pos);
    writeFile(tree, child, child->pos);
    writeFile(tree, sibling, sibling->pos);

    free(sibling);

    return child;
}

bool removeFromTree(bTree *tree, int key)
{
    bTreeNode *root = malloc(sizeof(bTreeNode));
    readFile(tree, root, tree->root);

    bool found = search(tree, key);
    if (found)
        removeNode(tree, root, key); // modificado. a verificar

    free(root);
    return found;
}