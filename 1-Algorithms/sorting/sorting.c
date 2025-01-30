#include "sorting.h"
#define ARR_SIZE 6

void selection_sort(int *arr,int size)
{
    int count_1,count_2;
    int temp,location;
    for(count_1=0;count_1<size-1;count_1++)
    {
        location=count_1;
        for(count_2=count_1+1;count_2<size;count_2++)
        {
            if(arr[count_2]<arr[location])
            {
                location=count_2;
            }
        }
        if(location!=count_1)
        {
            temp=arr[count_1];
            arr[count_1]=arr[location];
            arr[location]=temp;
        }
    }
}

void bubble_sort(int *arr,int size)
{
    int count_1,count_2;
    int temp,flag;
    for(count_1=size-1;count_1>0;count_1--)
    {
        flag=0;
        for(count_2=0;count_2<count_1;count_2++)
        {
            if(arr[count_2+1]<arr[count_2])
            {
                temp=arr[count_2];
                arr[count_2]=arr[count_2+1];
                arr[count_2+1]=temp;
                flag=1;
            }
        }
        if(flag==0)
        {
            break;
        }
    }
}

void insertion_sort(int *arr,int size)
{
    int count,value,hole;
    for(count=1;count<size;count++)
    {
        hole=count;
        value=arr[hole];
        while(hole>0&&arr[hole-1]>value)
        {
            arr[hole]=arr[hole-1];
            hole--;
        }
        arr[hole]=value;
    }
}

void merge_halves(int *arr,int left_first,int right_end)
{
    int temp[ARR_SIZE];
    int left=left_first;
    int left_end=(left_first+right_end)/2;
    int right=left_end+1;
    int index_temp=left_first;
    while(left<=left_end&&right<=right_end)
    {
        if(arr[left]<=arr[right])
        {
            temp[index_temp++]=arr[left++];
        }
        else
        {
            temp[index_temp++]=arr[right++];
        }
    }
    while(left<=left_end)
    {
        temp[index_temp++]=arr[left++];
    }
    while(right<=right_end)
    {
        temp[index_temp++]=arr[right++];
    }
    index_temp=left=left_first;
    while(left<=right_end)
    {
        arr[left++]=temp[index_temp++];
    }
}

void merge_sort(int *arr,int left_first,int right_end)
{
    if(left_first<right_end)
    {
        int middle=(left_first+right_end)/2;
        merge_sort(arr,left_first,middle);
        merge_sort(arr,middle+1,right_end);
        merge_halves(arr,left_first,right_end);
    }
}
