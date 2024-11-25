/*#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "akinator.h"
#include "tree.h"

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

void Guess(struct Node* leaf)
{
    printf("is it %s?\n", leaf->data);

    char* agree = NULL;
    scanf("%s", &agree);

    agree = LowString(agree);

    if(strncmp(agree, "yes", sizeof("yes")/sizeof(char)) == 0)
    {
        Guess(leaf->left);
    }

    else if(strncmp(agree, "no", sizeof("no")/sizeof(char)) == 0)
    {
        if(leaf->right != NULL)
            Guess(leaf->right);

        else
        {
            printf("Sorry, my database not as good as you need :(\n So, help me please, what it was?\n");

            char* newdata = GetLine();

            InsertNode(leaf->right, NO, LowString(newdata));

        }
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


    char* newdata = NULL;
    scanf("%ms", &newdata);


    return str;
}

void Guess(struct Tree* tree)
{

}*/