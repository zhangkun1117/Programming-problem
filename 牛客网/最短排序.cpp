/*题目描述
对于一个无序数组A，请设计一个算法，求出需要排序的最短子数组的长度。

给定一个整数数组A及它的大小n，请返回最短子数组的长度。

测试样例：
[1,5,3,4,2,6,7],7
返回：4
*/
class ShortSubsequence {
public:
    int findShortest(vector<int> A, int n) {
        // write code here
        vector<int> arr =A;
        sort(arr.begin(),arr.end());//转换为求序列相同值
        int res=0;
       for(int i=0;i<n/2;i++)
       {
           if(arr[i] == A[i])
               res++;
           else break;
       }
        for(int i=n-1;i>=n/2;i--)
            if(arr[i] == A[i])
                res++;
            else
                break;
        return n-res;
    }
};