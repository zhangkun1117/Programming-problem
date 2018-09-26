//24点
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>    
#include <cmath> 
#include <vector>
using namespace std;
#define SWAP(t, a, b) do {t v=a; a=b; b=v;} while (0)
#define OP(o,t,a,b) { t = a o b;}
bool _judge(vector<int > &numbers)
{	vector<int > temp = numbers;	
 	if (numbers.size() == 1)	
    {		
      if ((numbers[0] - 24<1e-8) && (numbers[0] - 24>-1e-8))		
      {			
        return true;		
      }else	{			
        return false;		
      }	
    }	
 	for (int i = 0; i<numbers.size(); i++)	
    {		
      for (int j = i + 1; j<numbers.size(); j++)		
      {			
        if (i != j)			
        {				
          temp.erase(temp.begin() + j);				
          OP(+, temp[i], numbers[i], numbers[j]);				
          if (_judge(temp) == 1)					
            return true;				
          OP(-, temp[i], numbers[i], numbers[j]);				
          if (_judge(temp) == 1)					
            return true;				
          OP(*, temp[i], numbers[i], numbers[j]);				
          if (_judge(temp) == 1)					
            return true;				
          if (numbers[j]>1e-8 || numbers[j]<-1e-8)				
          {					
            OP(/ , temp[i], numbers[i], numbers[j]);					
            if (_judge(temp) == 1)						
              return true;				
          }				
          temp = numbers;			
        }		
      }	
    }	
 return false;
}
bool judge(vector<int> &nums){
  if(nums.size()>4)
    return false;
  vector<int> tmp(nums);	
  for (int i = 0; i<nums.size(); i++)	
  {		
    SWAP(int , nums[0], nums[i]);		
    for (int j = 1; j < nums.size(); ++j) 
    {			
      SWAP(int , nums[1], nums[j]);			
      for (int p = 2; p<nums.size(); p++)			
      {				
        SWAP(int , nums[2], nums[p]);				
        tmp = nums;				
        if (_judge(nums) == 1)					
          return true;				
        nums = tmp;				
        SWAP(int , nums[2], nums[p]);			
      }			
      SWAP(int , nums[1], nums[j]);		
    }		
    SWAP(int , nums[0], nums[i]);	
  }	
  return false;
}
int main(){	
  	string s;
  	vector<int> arr;	
	getline(cin,s);
  	for(int i=0;i<s.size();i++){
    	if(s[i]>='0' && s[i] <='9'){
      	arr.push_back(s[i] - '0');
    	}
  	}
  	if(judge(arr)){
		  cout <<"true"<< endl;
  	}else{
   	 cout<<"false"<<endl;
  	}
  	return 0;
}