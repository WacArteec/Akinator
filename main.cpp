#include <stdio.h>

#include "tree.h"
#include "reader.h"
#include "recovery.h"
#include "akinator.h"

int main()
{
    /*struct Reader read = {};
    printf("input_file = %s \n", read.input_file);

    Input(&read);*/

    struct Tree tree = {};
    
//    tree.root = RecoverNode(&read, tree.root);

//    Akinator(&tree);

    char *tutu = "12345";

    Ctor(&tree, tutu);
    GraphDump(&tree);

    PrintNode(stdout, tree.root);
    printf("\n");

    GraphDump(&tree);

    SaveTree(&tree);

    PrintNode(stdout, tree.root);
    printf("\n");

    Dtor(&tree);

    return 0;
}