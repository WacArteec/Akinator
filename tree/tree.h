#ifndef TREE_H
#define TREE_H
#define $$$

#include <stdlib.h>
#include <stdio.h>

enum Side
{
    ZERO,
    YES,
    NO
};

struct Tree;

struct Node
{
    char* data = NULL;

    Node* left = NULL;
    Node* right = NULL;

    Node* parent = NULL;

    Tree* root_tree = NULL;
};

struct Tree
{
    Node* root = NULL;
    unsigned int size = 0;      // add file_name for dump(dot and default), FILE*?
};

void InsertNode(struct Node* leaf, Side agree, char* data);
void DeleteNode(struct Node* leaf);
void SaveTree(struct Tree* tree);
void PrintNode( FILE* stream, struct Node* leaf);
void Ctor(struct Tree* tree);
void Dtor(struct Tree* tree);
void GraphDump(struct Tree* tree);

#endif //TREE_H