#include <stdio.h>
#include <stdlib.h>
#include "searching.h"

int linear_searching(int *arr,int size,int key)
{
    int count,index;
    for(count=0;count<size;count++)
    {
        if(key==arr[count])
        {
            index=count;
            break;
        }
        else
        {
            index=-1;
        }
    }
    return index;
}

int binary_searching(int *arr,int first,int last,int key)
{
    int index;
    int mid=(first+last)/2;
    if(first>last)
    {
        index=-1;
    }
    else if(arr[mid]==key)
    {
        index=mid;
    }
    else if(arr[mid]>=key)
    {
        index=binary_searching(arr,first,mid-1,key);
    }
    else if(arr[mid]<=key)
    {
        index=binary_searching(arr,mid+1,last,key);
    }
    return index;
}
