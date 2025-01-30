#include <stdio.h>
#include <stdlib.h>
#include "stack_array.h"

int top=-1;
int stack[SIZE];

int is_stack_array_empty(void)
{
    int x;
    if(top<=0)
    {
        x=1;
    }
    else
    {
        x=0;
    }
    return x;
}

int is_stack_array_full(void)
{
    int x;
    if(top>=SIZE)
    {
        x=1;
    }
    else
    {
        x=0;
    }
    return x;
}

void push(int data)
{
    top++;
    stack[top]=data;
}

int pop(void)
{
    int x;
    x=stack[top];
    top--;
    return x;
}

void display_stack_array_elements(void)
{
    int count;
    for(count=0;count<=top;count++)
    {
        printf("%d \n",stack[count]);
    }
}

int return_top_value(void)
{
    return stack[top];
}

int number_of_elements_stackarray(void)
{
    return (top+1);
}
