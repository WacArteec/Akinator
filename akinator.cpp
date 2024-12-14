#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#include "akinator.h"
#include "tree/tree.h"
#include "stack.h"

// akinator_run

// guess
// define(stack)
// compare
// print_data_base
// exit_with_save
// default_exit

void Guess(struct Node* leaf);
char* LowString(char* str);
char* GetLine();
Node* FindNode(struct Node* leaf, char* str);
void NodeDescription(struct Node* leaf, Stacks num);
void DefineNode(struct Node* leaf, Stacks num);

int Akinator(struct Tree* tree)
{
    assert(tree);

    printf("Hello, i'm Akinator \n",
           "I can:\n",
           "guess your choise in music field (print: g)\n",
           "descripte an musician (print: d)\n",
           "compare two musicians (print: compare)\n",
           "print database for you (print: print database)\n",
           "or finish it all by the damn grandmother(print exit)\n");

    while(true)
    {
        printf("");

        char* comand = LowString(GetLine());

        if(strncmp(comand, "guess", sizeof("guess")/sizeof(char)) == 0)
            Guess(tree->root);

        else if(strncmp(comand, "describe", sizeof("describe")/sizeof(char)) == 0)
        {
            printf("Who should i describe?\n");

            char* need_leaf = GetLine();
            Node* found = FindNode(tree->root, need_leaf);

            DefineNode(found, first_stack);
            NodeDescription(found, first_stack);
        }

        else if(strncmp(comand, "compare", sizeof("compare")/sizeof(char)) == 0)
        {
            printf("Tell me which musicians you want to compare\n");

            char* str1 = LowString(GetLine());
            char* str2 = LowString(GetLine());

            Node* node1 = FindNode(tree->root, str1);
            DefineNode(node1, first_stack);

            Node* node2 = FindNode(tree->root, str2);
            DefineNode(node2, second_stack);

            CompareNodes(tree, str1, str2);
        }

        else if(strncmp(comand, "print database", sizeof("print database")/sizeof(char)) == 0)
        {
            GraphDump(tree);
        }

        else if(strncmp(comand, "exit", sizeof("exit")/sizeof(char)) == 0)
        {
            SaveTree(tree);
            break;
        }

        else
            printf("I don't understand you :(");
    }
}

void Guess(struct Node* leaf)
{
    assert(leaf);

    printf("is it %s?\n", leaf->data);

    char* agree = NULL;
    scanf("%s", &agree);

    agree = LowString(agree);

    badenter:

    if(strncmp(agree, "yes", sizeof("yes")/sizeof(char)) == 0)
    {
        if(leaf->left != NULL)
            Guess(leaf->left);

        else
        {
            printf("Yeeee, i won!!! I'm winner in that life!");
        }
    }

    else if(strncmp(agree, "no", sizeof("no")/sizeof(char)) == 0)
    {
        if(leaf->right != NULL)
            Guess(leaf->right);

        else
        {
            printf("Sorry, my database not as good as you need :(\n So, help me please, what is difference with %s?\n",
                                                                                                                leaf->data);

            char* new_question = GetLine();

            InsertNode(leaf->right, NO, LowString(new_question));

            printf("And what it was?\n");

            char* new_data = GetLine();

            InsertNode(leaf->right->left, YES, LowString(new_data));
        }
    }
    
    else
    {
        system("BadEnter.jpg");
        goto badenter;
    }
}

char* LowString(char* str)
{
    unsigned int str_len = sizeof(str)/sizeof(char);

    for(int i = 0; i < str_len; i++)
    {
        *(str + i) = tolower(*(str + i));
    }

    return str;
}

char* GetLine()
{
    char* str = (char*) calloc(16, sizeof(char));

    unsigned int shift = 0;

    while(*(str + shift) != EOF)
    {
        *(str + shift) = getchar();
        shift++;
    }

/*    char* newdata = NULL;
    scanf("%ms", &newdata);*/

    return str;
}

void NodeDescription(struct Node* leaf, Stacks num)
{
    if(stack[num].size == 0)
        return;

    int side = SPull(num);

    switch (side)
    {
        case YES:
        {
            printf("%s ", leaf->data);
            NodeDescription(leaf->left, num);
            break;
        }

        case NO:
        {
            printf("not %s ", leaf->data);
            NodeDescription(leaf->right, num);
            break;
        }
    
        default:
            printf("PROBLEMS IN DESCRIPTION: %d\n", side);
            exit(1);
            break;
    }
}

void DefineNode(struct Node* leaf, Stacks num)
{
    if(leaf->parent !=  NULL)
    {
        if(leaf->parent->left == leaf)
            SPush(num, YES);
        
        else
            SPush(num, NO);
    }
}

Node* FindNode(struct Node* leaf, char* str)
{
    Node* need_node = NULL;

    if(strncmp(leaf->data, str, sizeof(str)/sizeof(char)) == 0)
        return leaf;

    need_node = FindNode(leaf->left, str);

    if(need_node != NULL)
        return need_node;

    need_node = FindNode(leaf->right, str);

    if(need_node != NULL)
        return need_node;
    
    else
        return NULL;;;;;;;
}

void CompareNodes(struct Tree* tree, char* data1, char* data2)
{
    printf("They are: ");

    PrintCompare(tree->root, data1, data2);
}

void PrintCompare(struct Node* leaf, char* data1, char* data2)
{
    printf("%s, ", leaf->data);

    int side1 = SPull(first_stack);
    int side2 = SPull(second_stack);

    if(side1 == side2 && stack[first_stack].size != 0 && stack[second_stack].size != 0)
    {
        if(side1 == YES)
            PrintCompare(leaf->left, data1, data2);

        else
            PrintCompare(leaf->right, data1, data2);
    }

    else if(stack[first_stack].size == 0)
    {
        printf("\nAnd %s is: ", data2);
        NodeDescription(leaf, second_stack);
    }

    else if(stack[second_stack].size == 0)
    {
        printf("\nAnd %s is: ", data1);
        NodeDescription(leaf, first_stack);
    }

    else
    {
        printf("\nBut %s is: ", data1);
        NodeDescription(leaf, first_stack);
        
        printf("\nBut %s is: ", data2);
        NodeDescription(leaf, second_stack);
    }
}