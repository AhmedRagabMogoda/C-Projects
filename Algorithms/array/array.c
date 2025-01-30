#include <stdio.h>
#include <stdlib.h>
#include "array.h"

void scan_array(int *arr,int size)
{
    int count=0;
    for(count =0;count<size;count++)
    {
        printf("please enter the array element number %i \n",count);
        scanf("%i",&arr[count]);
    }
}

void print_array(int *arr,int size)
{
    int count=0;
    printf("---------------------------------------------------\n");
    for(count =0;count<size;count++)
    {
        printf("the array element number %i is : %i \n",count,arr[count]);
    }
    printf("---------------------------------------------------\n");
}
