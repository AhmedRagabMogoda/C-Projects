#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

void print_list(node *head)
{
    if(head==NULL)
    {
        printf("linked list empty \n");
    }
    else
    {
        while(head!=NULL)
        {
            printf("%d \n",head->val);
            head=head->next;
        }
    }
}

void push_head(node **head,int data)
{
    node *temp=NULL;
    temp=(node*)malloc(sizeof(node));
    temp->val=data;
    temp->next=*head;
    *head=temp;
}

void push_end(node **head_adr,node *head,int data)
{
    if(head==NULL)
    {
        push_head(head_adr,data);
    }
    else
    {
        while(head->next!=NULL)
        {
            head=head->next;
        }
        head->next=(node*)malloc(sizeof(node));
        head->next->val=data;
        head->next->next=NULL;
    }
}

int pop_head(node **head)
{
    if(*head!=NULL)
    {
        int ret_val;
        node *temp=NULL;
        temp=(*head)->next;
        ret_val=(*head)->val;
        free(*head);
        *head=temp;
        return ret_val;
    }
}

int pop_last(node **head_adr,node *head)
{
    if(head!=NULL)
    {
        int ret_val=0;
        if(head->next==NULL)
        {
            ret_val=pop_head(head_adr);
        }
        else
        {
            while(head->next->next!=NULL)
            {
                head=head->next;
            }
            ret_val=head->next->val;
            free(head->next);
            head->next=NULL;
        }
        return ret_val;
    }
}

void insert_by_index(node **head_adr,node *head,int data,int index)
{
    node *temp;
    int count;
    if(index<0)
    {
        printf("index must be positive number");
    }
    else
    {
        if(head==NULL)
        {
            push_head(head_adr,data);
        }
        else
        {
            for(count=0;count<index-1;count++)
            {
                head=head->next;
            }
            temp=(node*)malloc(sizeof(node));
            temp->val=data;
            temp->next=head->next;
            head->next=temp;
        }
    }
}

int remove_by_index(node **head,int index)
{
    node *temp=NULL;
    node *current=*head;
    int ret_val=0;
    int count=0;
    if(index<0)
    {
        printf("index must be positive number");
    }
    else if(*head==NULL)
    {
        printf("linked list is empty");
    }
    else if(index==0)
    {
        ret_val=pop_head(head);
    }
    else
    {
        for(count=0;count<index-1;count++)
            {
                if(head==NULL)
                {
                    return pop_last(head,*head);
                }
                current=current->next;
            }
            temp=current->next;
            ret_val=temp->val;
            current->next=temp->next;
            free(temp);

    }
    return ret_val;
}







