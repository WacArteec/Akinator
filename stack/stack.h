#ifndef STACK_H
#define STACK_H

#define stk_default_value 0

enum Stacks
{
    first_stack  = 1,
    second_stack = 2
};

struct Stack_Struct
{
    int* record  = NULL;
    size_t point = stk_default_value;
    size_t size  = stk_default_value;
};

Stack_Struct stack[2] = {};

void SPush(Stacks num, int in);
int SPull(Stacks num);

#endif // STACK_H