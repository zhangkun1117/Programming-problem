/**
 * 全排列算法：
 *      1.递归
 *      2.字典序
 * */
#include <iostream>
#include <algorithm>

using namespace std; 
//递归实现
template<typename T>
void permutation(T array[], int begin, int end)
{    
    int i;     
    if(begin == end){        
        for(i = 0; i <= end; ++i){            
            cout<<array[i]<<" ";        
            }        
        cout<<endl;        
        return;   
    } else {        
         //for循环遍历该排列中第一个位置的所有可能情况        
        for(i = begin; i <= end; ++i) {            
            swap(array[i], array[begin]);            
            permutation(array, begin + 1, end);            
            swap(array[i], array[begin]);        
        }    
    }
} 

/**利用stl next_permutation：它的作用是如果对于一个序列，
*存在按照字典排序后这个排列的下一个排列，那么就返回true且产生这个排列，否则返回false。
*/
template <typename BidirectionalIterator>
void permutationRecursion(BidirectionalIterator array, int len){    
    sort(array, array + len);    
    do{        
        for(int i = 0; i < len; ++i){            
            cout<<array[i]<<" ";        
        }        
        cout<<endl;    
        
    }while(next_permutation(array, array + len));
} 

/**
 * 实现相当于next_permutaion的功能
 * */
//交换数组a中下标为i和j的两个元素的值
void swap(int *a,int i,int j)
{
    a[i]^=a[j];
    a[j]^=a[i];
    a[i]^=a[j];
}
 
//将数组a中的下标i到下标j之间的所有元素逆序倒置
void reverse(int a[],int i,int j)
{
    for(; i<j; ++i,--j) {
        swap(a,i,j);
    }
}
 
void print(int a[],int length)
{
    for(int i=0; i<length; ++i)
        cout<<a[i]<<" ";
    cout<<endl;
}
 
//求取全排列,打印结果
void combination(int a[],int length)
{
    if(length<2) return;
 
    bool end=false;
    while(true) {
        print(a,length);
 
        int i,j;
        //找到不符合趋势的元素的下标i
        for(i=length-2; i>=0; --i) {
            if(a[i]<a[i+1]) break;
            else if(i==0) return;
        }
 
        for(j=length-1; j>i; --j) {
            if(a[j]>a[i]) break;
        }
 
        swap(a,i,j);
        reverse(a,i+1,length-1);
    }
}
int main(int argc, char **argv){    
    int a[4] = {1, 2, 3, 4};    
    permutation(a,0,sizeof(a)/sizeof(int) -1);
    //
    cout<<"Using STL to achieve permutation "<<endl;
    permutationRecursion(a, sizeof(a) / sizeof(int));    
    cout<<"achieve next_permutation "<<endl; 
     combination(a, sizeof(a) / sizeof(int));
    return 0;
}
