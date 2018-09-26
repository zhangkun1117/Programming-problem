
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
struct seq
{
    char str[7];
};
 
struct seq seqs[721];
int count;
 
void swap(char *str, int a, int b)
{
    char temp;
    temp = str[a];
    str[a] = str[b];
    str[b] = temp;
}
 
void permutation_process(char *name, int begin, int end) {
    int k;
 
    if (begin == end - 1) {
        strcpy(seqs[count].str, name);
        count ++;
    }else {
        for (k = begin; k < end; k ++) {
            swap(name, k, begin);
            permutation_process(name, begin + 1, end);
            swap(name, k, begin);
        }
    }
}
 
int compare(const void *p, const void *q)
{
    const char *a = p;
    const char *b = q;
    return strcmp(a, b);
}
 
int main()
{
    char name[7];
    int i, len;
 
    while (scanf("%s", name) != EOF) {
        count = 0;
        len = strlen(name);
        permutation_process(name, 0, len);
        qsort(seqs, count, sizeof(seqs[0]), compare);
 
        for (i = 0; i < count; i ++) {
            printf("%s\n", seqs[i].str);
        }
        printf("\n");
    }
 
    return 0;
}
/*
#include <iostream>
using namespace std;

int result(int first,int second){
    int sum=1;
    int temp = first;
    for(int i=second;i>0;i--){
        sum*=first--;
    }
    return sum;
}

int main(){
	int np,nq,nr;
    cin>>np>>nq>>nr;

    
}*/