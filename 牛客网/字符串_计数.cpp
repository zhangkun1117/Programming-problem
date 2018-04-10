/*题目描述
求字典序在s1和s2之间的，长度在len1到len2的字符串的个数，结果mod 1000007。

输入描述:
每组数据包涵s1（长度小于100），s2（长度小于100），len1（小于100000），len2（大于len1，小于100000）
输出描述:
输出答案。
示例1
输入
ab ce 1 2
输出
56
*/
#include<iostream>
#include<string>
#include<vector>
#include<math.h>
using namespace std;
 
int main(){
    //根据题中给出的例子，这个字符串只包含小写字母，不然答案就不应该是56了
    string s1,s2;
    int len1,len2;
    while(cin>>s1>>s2>>len1>>len2){
        //只包含小写字母的字符串可以看成26进制的数制
        //将s1和s2补长到len2长度
        s1.append(len2-s1.size(),'a');
        s2.append(len2-s2.size(),(char)('z'+1));
        vector<int> array;
        for(int i=0;i<len2;i++){
            array.push_back(s2[i]-s1[i]);
        }
        int result = 0;
        for(int i=len1;i<=len2;i++){
            for(int k=0;k<i;k++){
                result += array[k]*pow(26,i-1-k);
            }
        }
        //所有字符串最后都不包含是s2自身，所以最后要减1；
        cout<<result-1<<endl;
    }
    return 0;
}