
#include <stdio.h>
#include <stdlib.h>

typedef struct point{
int val;
struct point *next;
}node;

void print_list(node *head);
void push_head(node **head,int data);
void push_end(node **head_adr,node *head,int data);
int pop_head(node **head);
int pop_last(node **head_adr,node *head);
void insert_by_index(node **head_adr,node *head,int data,int index);
int remove_by_index(node **head,int index);
