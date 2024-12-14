#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#include "stack.h"

enum SizeChanger
{
    MORE_SIZE,
    LESS_SIZE
};

void SCreate(Stacks num);
void SDestroy(Stacks num);
void SPush(Stacks num, int in);
int SPull(Stacks num);
void ChangeSize(Stacks num, SizeChanger mode);

void SCreate(Stacks num)
{
    int* make_stack = (int*) calloc(0, sizeof(int));
    assert(make_stack);

    stack[num].record = make_stack;

    stack[num].point = 0;

    stack[num].size = 1;
}

void SDestroy(Stacks num)
{
    free(stack[num].record);

    stack[num].record = NULL;
    stack[num].point = 0;
    stack[num].size  = 0;
}

void SPush(Stacks num, int in)
{
    if(stack[num].record == NULL) SCreate(num);

    if(stack[num].point == stack[num].size)
        ChangeSize(num, MORE_SIZE);

    stack[num].record[stack[num].point] = in;
    stack[num].point++;
}

int SPull(Stacks num)
{
    stack[num].point--;
    int out = stack[num].record[stack[num].point];

    stack[num].record[stack[num].point] = 0;

    if(4 * (stack[num].point + 1) <= stack[num].size && stack[num].size > 20)
        ChangeSize(num, LESS_SIZE);

    if(stack[num].point == 0) SDestroy(num);

    return out;
}

void ChangeSize(Stacks num, SizeChanger mode)
{
    switch(mode)
    {
        case MORE_SIZE:

                stack[num].size *= 2;

                stack[num].record = (int*) realloc(stack[num].record, (stack[num].size)* sizeof(int));
                assert(stack[num].record);

                memset(stack[num].record + stack[num].point,
                       0,
                       (stack[num].size - stack[num].point)*sizeof(int));
            break;

        case LESS_SIZE:
        {
                stack[num].size = (stack[num].size)/2;

                stack[num].record = (int *) realloc(stack[num].record, (stack[num].size + 4) * sizeof(int));
                assert(stack[num].record);

            break;
        }

        default:
            break;
    }
}