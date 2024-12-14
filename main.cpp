#include <stdio.h>

#include "tree/tree.h"
#include "readrecover/reader.h"
#include "readrecover/recovery.h"
#include "akinator.h"


/*
СПРОСИТЬ ПРО МЭЙКФАЙЛ И ФАЙЛЫ ИЗ ДРУГИХ ПАПОК
*/

int main()
{
    struct Reader read = {};
$$$ printf("input_file = %s \n", read.input_file);

    Input(&read);

    struct Tree tree = {};
    Ctor(&tree);
    
    tree.root = RecoverNode(&read, NULL, &tree);

   Akinator(&tree);

//    char *tutu = "asser";

//    Ctor(&tree, tutu);
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