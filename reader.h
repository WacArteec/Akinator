#ifndef READER_H
#define READER_H

#include <stdio.h>
#include <stdlib.h>

struct Reader
{
    char* text = NULL;

    unsigned int count_lines = 0;
    unsigned int count_elements = 0;

    FILE* file = NULL;
    const char* input_file = "DataBase.txt";
};

void Input(struct Reader* read);

#endif //READER_H