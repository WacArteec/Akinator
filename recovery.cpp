#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "tree.h"
#include "reader.h"
#include "recovery.h"

char* GetString(char* str);

Node* RecoverNode(struct Reader* read, struct Node* parent)
{
    struct Node* node = (Node*) calloc(1, sizeof(Node));

    if(*(read->text) == '(')
    {
        read->text += 1;
        node->data = GetString(read->text);

        node->parent = parent;

        node->right = RecoverNode(read, node);
        node->left  = RecoverNode(read, node);

        read->text++;
    }

    else if(strncmp(read->text, "nil", sizeof("nil")/sizeof(char)) == 0)
    {
        read->text += 3;
        
        return NULL;
    }

    else
    {
        fprintf(stderr, "\tYOUR DATABASE HAS BROKEN: %c\n", read->text);
        exit(1);
    }

    return node;
}

char* GetString(char* str)
{
    while(isalpha(*str) == 0 && *str != '\0')
        str++;

    char* buffer = (char*) calloc(16, sizeof(char));

    unsigned int shift = 0;

    while(isalpha(*(str + shift)) != 0)
    {
        buffer[shift] = *(str+shift);

        shift += 1;

        if(shift >= (sizeof(buffer)/sizeof(char)))
            realloc(buffer, 2*(sizeof(buffer)/sizeof(char)));
    }

    str += shift;

    realloc(buffer, shift*sizeof(char));

    return buffer;
}