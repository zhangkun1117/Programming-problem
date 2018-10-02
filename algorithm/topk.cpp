#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

/**
* 插入实现:前K个最大值
**/
void insertTopK(vector<int> &array, int K){
	if (K >= array.size()){
		sort(array.begin(), array.end(),greater<int>());
		return;
	}
	sort(array.begin(), array.begin() + K,greater<int>());
	for (int i = K; i<array.size();i++){
		if (array[i]>array[K - 1]){
			swap(array[i], array[K - 1]);
			int temp = K-1;
			while (temp > 0 && array[temp-1]<array[temp]){
				swap(array[temp-1], array[temp]);
				temp--;
			}
		}
	}
}
//快排实现top k
int Partition(vector<int> &A, int left, int right)
{
	int pivot = A[right];
	int tail = left - 1;
	for (int i = left; i<right; i++)
	{
		if (A[i] <= pivot)
			swap(A[i], A[++tail]);
	}
	swap(A[tail + 1], A[right]);
	return tail + 1;
}
void QucikSort(vector<int> &A, int left, int right,int k)
{
	if (left >= right)
		return;
	int pivot_index = Partition(A, left, right);

	for (auto &temp : A) cout << temp << " ";
	cout << pivot_index <<  " " << k<<endl;

	if (pivot_index == k-1){
		return;
	}
	else if (k-1 < pivot_index){
		QucikSort(A, left, pivot_index-1,k);
	}
	else if (k-1>pivot_index)
	{
		QucikSort(A, pivot_index, right, k - pivot_index+1);
	}
}
/**堆排序实现
*堆的设计对于处理top K问题十分方便。首先设置一个大小为K的堆（
*如果求最大top K,那么用最小堆，如果求最小top K,那么用最大堆），
*然后扫描数组。并将数组的每个元素与堆的根比较，符合条件的就插入堆中，
*同时调整堆使之符合堆的特性，扫描完成后，堆中保留的元素就是最终的结果。
*说到调整堆，不得不提的是调整的算法，分为两类：
*向下调整（shiftdown） 和 向上调整(shiftup)。
**/
int main(){
	int N, K=5;
	vector<int> array = { 10, 30, 5, 15, 110, 2, 42, 6, 36,200 };
	// 插入排序实现
	/*
	insertTopK(array, K);
	for (auto &i : array){
		cout << i << " ";
	}
	cout << "\n";
	*/
	//快排实现
	QucikSort(array, 0, 9, 5);
	for (auto &temp : array) cout << temp << " ";
	cout << endl;
	return 0;
}