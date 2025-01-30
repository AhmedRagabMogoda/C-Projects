#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "queue_linkedlist.h"

node *head=NULL;
int count_t=0;

int is_queue_empty(void)
{
    int x;
    if(head==NULL)
    {
        x=1;
    }
    else
    {
        x=0;
    }
    return x;
}

void enqueue(int data)
{
    push_end(&head,head,data);
    count_t++;
}

int dequeue(void)
{
    count_t--;
    return pop_head(&head);
}

void display_queue(void)
{
    print_list(head);
}

int number_of_element_queue(void)
{
    return count_t;
}
