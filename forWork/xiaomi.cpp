#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <string>   
#include <set>
#include <algorithm>
#include <map>
#include <stdio.h>
#include <string.h>
using namespace std;
//递归判断是否是一个后序的结果
bool isTree(int a[],int begin,int end){

	if(begin>=end) return true;
	//最后一个数为根节点的数据
	int root=a[end];
	int i=begin;
	//遍历找最后一个比根节点小的数
	while(a[i]<=root){
		i++;
	}
	int position=i; //分割点 
	bool isLeftTree=(a,begin,position-1);
	bool isRightTree=true;
	//首先判断后边的数是不是都比根节点数 
	for(int j=position;j<=end-1;j++){
		if(a[j]<root){
			isRightTree=false;
			break;
		}
	}
	//如果右边满足当前的根节点的话，则递归判断剩下的右边元素是不是满足 
	if(isRightTree){
		isRightTree= isTree(a,position,end-1);
	}
	//只有左边和右边都满足了才返回true 
	return (isLeftTree && isRightTree) ;
}
int main(){
	
 
	int a[7]={5,7,6,9,11,10,8};
	bool isRight=isTree(a,0,7);
	if(isRight){
		cout<<"Yes"<<endl;
	}else{
		cout<<"No"<<endl;
	}
	return 0;
}