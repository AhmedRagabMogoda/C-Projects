#include <stdio.h>
#include <stdlib.h>
#include "queue_array.h"

int front=0,rear=0;
int counter=0;
int queue[SIZE];

int is_queue_array_empty(void)
{
    int x;
    if(counter==0)
    {
        x=1;
    }
    else
    {
        x=0;
    }
    return x;
}

int is_queue_array_full(void)
{
    int x;
    if(counter==SIZE)
    {
        x=1;
    }
    else
    {
        x=0;
    }
    return x;
}

void enqueue_array(int data)
{
    queue[rear]=data;
    rear=(rear+1)%SIZE;
    counter++;
}

int dequeue_array(void)
{
    int x;
    x=queue[front];
    front=(front+1)%SIZE;
    counter--;
    return x;
}

void display_queue_array_elements(void)
{
    int i;
    int front_t=front;
    for(i=0;i<counter;i++)
    {
        printf("%d \n",queue[front_t]);
        front_t=(front_t+1)%SIZE;
    }
}

int number_of_element_queue_array(void)
{
    return counter;
}
