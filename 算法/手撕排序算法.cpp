/*
排序算法
*/
/* 冒泡：交换相邻元素实现排序
*/
#include <bits/stdc++.h>

void BubbleSort(int& a[],int n)
{
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-1-i;j++)
        {
            if(a[j]>a[j+1])
                swap(a[i],a[i+1]);
        }
}
/*
选择排序：从未排序列表总去出最小或者最大
*/
void SelectionSort(int &a[],int n)
{
    for(int i=0;i<n;i++)
    {
        int minindex = i;
        for(int j=i;j<n;j++)
        {
            minindex = (a[minindex]>a[j] ? j:minindex);
        }
        if(minindex !=i)
            swap(a[minindex],a[i])
    }    
}
/*插入排序
*/
void InsertionSort(int& a[],int n)
{
    for(int i=1;i<n;i++)
    {
        int j = i-1;
        int get = a[i];
        while(j>=0 && a[j]>get)
        {
            a[j+1] =a[j];
            j--;
        }
        a[j+1] = get;
    }
}
/*
shell 排序:插入排序的一种
*/
void shellSort(int & a[],int n)
{
    int h=0;
    while(h<=n)
        h = 3*h+1;
    while(h>=1)
    {
        for(int i=h;i<n;i++)
        {
            int get = a[i];
            int j= i-h;
            while(j>=0 && a[j] >get)
            {
                a[j+h] = a[j];
                j = j-h;        
            }
            a[j+h] = get;
        }
        h = (h-1)/3;
    }
}

/*
归并排序
*/

void Merge(int &a[],int left,int mid,int right)
{
    int len = right-left+1;
    int *temp = new int[len];
    int index =0;
    int i = left;
    int j = mid +1;
    while(i<= mid &&  j<=right)
        temp[index++] = a[i]< a[j]?a[i]:a[j];
    while(i<=mid)
        temp[index++] = a[i++];
    while(j<=right)
        temp[index++] = a[j++];
    for(int i=0;i<n;i++)
        a[i] = temp[i];
}
//递归版本
void MergeSortRecursion(int a[],int left,int right)
{
    if(left == right)
        return;
    int mid = (right+left) /2;
    MergeSortRecursion(a,left,mid);
    MergeSortRecursion(a,mid+1,right);
    Merge(a,left,mid,right);
}
//非递归版本
void MergeSortIteration(int &a[],int len)
{
    int left,mid,right;
    for(int i=1;i<len;i++)
    {
        left =0;
        while(left +i <len )
        {
            mid = left+i-1;
            right = mid+i<len?mid+i:len-1;
            Merge(a,left,mid,right);
            left = right+1;
        }
    }
}

/*
堆排序
*/
void Heapify(int &A[],int i,int size)//从A[i]向下进行堆调整
{
    int left_child = 2*i+1;
    int right_child = 2*i+2;
    int max =1;
    if(left_child <size && A[left_child] >A[max])
        max = left_child;
    if(right_child <size && A[right_child] >A[max])
        max = right_child;
    if(max != i)
    {
        swap(A[i],A[max])
        Heapify(A,max,size);
    }
}
void BuildHeap(int A[],int n)
{
    int heap_size = n;
    for(int i= heap_size/2-1;i>=0;i--)
        Heapify(A,i,heap_size);
    return heap_size;

}
void HeapSort(int A[],int n)
{
    int heap_size = BuildHeap(A,n);
    while(heap_size > 1)
    {
        swap(A[0],A[--heap_size]);
        Heapify(A,0,heap_size);
    }
}

/*
快排
*/
int Partition(int& A[],int left ,int right)
{
    int pivot = A[right];
    int tail = left -1;
    for(int i= left;i<right;i++)
    {
        if(A[i] <= pivot)
            swap(A[i],A[++tail]);
    }
    swap(A[tail+1],A[right]);
    return tail+1;
}
void QucikSort(int& A[],int left,int right)
{
    if(left<=right)
        return ;
    int pivot_index = Partition(A,left,right);
    QuickSort(A,left,pivot_index-1);
    QucikSort(A,pivot_index+1,right);
}


