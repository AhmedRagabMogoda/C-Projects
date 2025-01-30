#include <stdio.h>
#include <stdlib.h>
#include "stack_linkedlist.h"

node_t *top_t=NULL;
int count=0;

int is_stack_linkedlist_empty(void)
{
    int x;
    if(top_t<=0)
    {
        x=1;
    }
    else
    {
        x=0;
    }
    return x;
}

void push_stack(int data)
{
    node_t *temp=(node_t*)malloc(sizeof(node_t));
    temp->val=data;
    temp->next=top_t;
    top_t=temp;
    count++;
}

int pop_stack(void)
{
    int x;
    node_t *temp=top_t->next;
    x=top_t->val;
    free(top_t);
    top_t=temp;
    count--;
    return x;
}

void display_stack_elements(void)
{
    node_t* temp=top_t;
    while(temp!=NULL)
    {
        printf("%d \n",temp->val);
        temp=temp->next;
    }
}

int top_element_stack(void)
{
    return top_t->val;
}

int number_of_elements_stack(void)
{
    return count;
}









