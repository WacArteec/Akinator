#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tree.h"

const char* blue = "#87cefa";
const char* yellow = "#FFFFE0";
const char* green = "#177245";


// add verificator and dump
// write MyAssert

Node* CreateNode(struct Node* leaf, char* data);
void PrintNode( FILE* stream, struct Node* leaf);
int DotNode(FILE* dot_file, struct Node* leaf, Side agree, int parent_num);

// add asserts

void Ctor(struct Tree* tree)
{
    assert(tree);

    tree->root = (Node*) calloc(1, sizeof(Node));

    tree->root->data = NULL;

    tree->root->parent = NULL;
    tree->root->root_tree = tree;

    tree->root->right = NULL;
    tree->root->left  = NULL;
}

// char *data, left, right, parent

// separate funcs for add node left or right

void InsertNode(struct Node* leaf, Side agree, char* data)
{
    switch (agree)
    {
        case YES:
        {
            leaf->left = CreateNode(leaf, data);
            break;
        }
        case NO:
        {
            leaf->right = CreateNode(leaf, data);
            break;
        }
        default:
            break;
    }

    leaf->root_tree->size++;
}

Node* CreateNode(struct Node* leaf, char* data)
{
    assert(leaf);
    assert(data);

    struct Node* node = (Node*) calloc(1, sizeof(Node));
    assert(node);

    node->data = data;

    node->left  = NULL;
    node->right = NULL;

    node->parent = leaf;
    node->root_tree = leaf->root_tree;

    return node;
}

void SaveTree(struct Tree* tree)
{
    assert(tree);

    FILE* database = fopen("DataBase.txt", "wb");
    assert(database);

    PrintNode(database, tree->root);

    fclose(database);
}

void PrintNode(FILE* stream, struct Node* leaf)
{
    assert(stream);

    if(leaf != NULL)
    {
        fprintf(stream, "(%s", leaf->data);

        PrintNode(stream, leaf->left);
        PrintNode(stream, leaf->right);

        fprintf(stream, ")");
    }

    else
    {
        fprintf(stream, "nil");
    }

}

void DeleteNode(struct Node* leaf)
{
    if(leaf == NULL)
        return;

    if(leaf->parent != NULL)
    {
        if(leaf->parent->right == leaf)
            leaf->parent->right  = NULL;

        else if(leaf->parent->left == leaf)
            leaf->parent->left  = NULL;
    }

    DeleteNode(leaf->right);
    DeleteNode(leaf->left);

    free(leaf);
    leaf = NULL;
}

void Dtor(struct Tree* tree)
{
    assert(tree);

    tree->size = 0;

    DeleteNode(tree->root);
}

void GraphDump(struct Tree* tree)
{
    assert(tree);

$$$ printf("\n\n%d\n\n", __LINE__);
    FILE* dot_file = fopen("Tree.dot", "wb");
    assert(dot_file);

    fprintf(dot_file, "digraph G{\n\trankdir=HR;\n");

    fprintf(dot_file, "\tbgcolor = \"#FFF0DB\";\n"); //\tnode[shape=plaintext];\n\tedge[color=white];\n instead of

	fprintf(dot_file, "\tnode0 [shape = Mrecord, style = filled, fillcolor = \"#FFB02E\", label = \"Tree_addres: %p | root: %p | size: %u\"];\n", 
                                                                                                            tree,      tree->root,tree->size);

    DotNode(dot_file, tree->root, ZERO, 0);

    fprintf(dot_file, "\tnode0 -> node1 [color = \"#000000\"]\n");

//    fprintf(dot_file, "\tAll [shape = Mrecord, style = filled, fillcolor = \"#8B00FF\", label = \"size = %u \"];"\n}", tree->size);

    fprintf(dot_file, "}");

    fclose(dot_file);

    system("dot -Tpng -O Tree.dot");
    system("Tree.dot.png");
}

int DotNode(FILE* dot_file, struct Node* leaf, Side agree, int parent_num)
{
    const char* color = "#000000";
    int current_num = parent_num + 1;

    if(leaf == NULL)
        return 0;

    switch (agree)
    {
        case YES:
        {
            color = blue;
            break;
        }
        
        case NO:
        {
            color = yellow;
            break;
        }

        case ZERO:
        {
            color = green;
            break;
        }
        
        default:
            break;
    }
    
	fprintf(dot_file, "\tnode%d [shape = Mrecord, style = filled, fillcolor = \"%s\", label = \"addres: %p | data: %s | left(yes): %p | right(no): %p | parent: %p \"];\n", 
                       parent_num + 1,                                          color,                  leaf,      leaf->data,     leaf->left,     leaf->right, leaf->parent);

    int left_child_num = DotNode(dot_file, leaf->left, YES, current_num);

    if(left_child_num != 0)
        fprintf(dot_file, "\tnode%d -> node%d [color = \"#000000\"\"]\n\n", current_num, left_child_num);

    int right_child_num = DotNode(dot_file, leaf->right, NO, left_child_num);
    
    if(right_child_num != 0)
        fprintf(dot_file, "\tnode%d -> node%d [color = \"#000000\"\"]\n\n", current_num, right_child_num);

    return current_num;
}
