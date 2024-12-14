#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "tree.h"
#include "reader.h"
#include "recovery.h"

char* GetString(struct Reader* read);

Node* RecoverNode(struct Reader* read, struct Node* parent, struct Tree* tree)
{
    struct Node* node = (Node*) calloc(1, sizeof(Node));
    assert(node);
$$$ printf("\t%d\n", __LINE__);

    if(*(read->text) == '(')
    {
        read->text += 1;

        node->data = GetString(read);

        node->parent = parent;
        node->root_tree = tree;

        node->left  = RecoverNode(read, node, tree);
        node->right = RecoverNode(read, node, tree);

        read->text++;
    }

    else if(strncmp(read->text, "nil", sizeof("nil")/sizeof(char)) == 0)
    {
        read->text += 3;
        
        return NULL;
    }

    else
    {
        fprintf(stderr, "\tYOUR DATABASE HAS BROKEN: %s\n", read->text);
        exit(1);
    }

    return node;
}

char* GetString(struct Reader* read)
{
    while(isalpha(*read->text) == 0 && *read->text != '\0')
        read->text++;

    char* buffer = (char*) calloc(16, sizeof(char));

    unsigned int shift = 0;

    while(isalpha(*(read->text + shift)) != 0)
    {
        buffer[shift] = *(read->text + shift);

        shift += 1;

        if(shift >= (sizeof(buffer)/sizeof(char)))
            realloc(buffer, 2*(sizeof(buffer)/sizeof(char)));
    }

$$$ printf("\t%s on line %d\n", read->text, __LINE__);
    read->text += shift;
$$$ printf("\t%s on line %d\n", read->text, __LINE__);

    realloc(buffer, shift * sizeof(char));

    return buffer;
}