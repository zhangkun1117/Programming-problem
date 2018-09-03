#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

#define pi 3.14156
struct pos
{
	int flag;
	int step;
};
//函数声明
double mean(double *, int ,int);
double var(double *, int ,int);
int countStep(double *,int ,bool &,bool &);
void checkflag(int* ,int );
pos PostureTag(double* , double* , int , bool &, bool &);
int maxIndex(int * ,int );
int simplifyPosture(int *,int);


int main()
{
	//定义变量
	int i = 0, m = 0;
	int Timewindows = 0, stage = 45;
	double a[2000][15];
	double svm[2000];
	double ACCy[2000];
	int step = 0, totalstep = 0;
	double svmonec[60] = { 0 };
	double accyonec[60] = { 0 };
	bool updir = false,downdir=false;
	int totalflag[200] = { 0 };


	struct pos flags = {0,0};
	//读取文件
	FILE* fstream;
	fstream = fopen("kuai35.txt", "rb");
	if (fstream == NULL)
	{
		printf("open file test.txt failed!\n");
		exit(1);
	}
	else
	{
		printf("open file test.txt succeed!\n");
	}
	while (!feof(fstream))
	{
		for (int j = 0; j<15; j++)
		{

			fscanf(fstream, "%lf", &a[i][j]);

		}
		fscanf(fstream, "\n");
		i++;
	}
	m = i;
    fclose(fstream);
	//文件读取结束

	//主要参数合加速度svm和ACCy
	for (i = 0; i<m; i++)
	{
		svm[i] = sqrt(pow(a[i][6], 2) + pow(a[i][7], 2) + pow(a[i][8], 2)) / 16384;
		ACCy[i] = a[i][7] / 16384;
	}

	//
	Timewindows = round(m / stage);

	for (i = 1; i<Timewindows; i++)
	{
		int start = stage*(i - 1);
		int finish = start + 59;
		if (finish > m)
			break;

		for (int j = 0; j < finish - start + 1; j++)
		{
			svmonec[j] = svm[start + j];
			accyonec[j] = ACCy[start + j];
		}
		flags = PostureTag(svmonec, accyonec, finish - start + 1,updir,downdir);
		totalstep += flags.step;
		totalflag[i] = flags.flag;
	}
	//可以设置不同时间间隔上传一次姿态，主要解决方法是设置totalflag
	//的大小，每次按指定的大小上传
	checkflag(totalflag,i);	
	// 一段时间的姿态
	int posturePeriod = simplifyPosture(totalflag,i);
	system("pause");
	return 0;
}
/************************************************************************/
/* 指针数据求均值
/* 输入：
/*    data为指针数组
/*    start 为开始位置
/*    end 为结束的的位置
/* 输出： 该数组的均值
/************************************************************************/
double mean(double* data, int start,int end)
{
	double sum = 0;
	for(int i=start;i<end;i++)
		sum += data[i];
	return sum / (end-start+1);
}
/************************************************************************/
/*指针数组求方差
/*输入：     data 为指针数组；
/*   	 	start 为开始位置
/*    		end 为结束的的位置
/*输出：  返回指针数组方差
/************************************************************************/
double var(double* data, int start,int end)//len长度数组求方差
{
	double sum = 0;
	double ave = mean(data,start,end);
	for(int i = start;i<end;i++)
		sum += (data[i] - ave)*(data[i] - ave);
	return sqrt(sum /(end-start+1));
}
/************************************************************************/
/*极值计步算法
/*        1, 通过三轴加速度数据,求均值(me)和方差(std);
/*        2, 设置两个bool变量updir和downdir 初始值为updir = false,downdir = false;
/*        3, 在updir方向查找较大值upmax:
/*            满足upmax>me+st/2
/*        4，3满足时,updir=1&& downdir=0:
/*            在downdir方向查找极小值，满足downmin < me-st/2; 
/*        5， 如果updir && downdir 成立，则认为走一步，并且 
/*输入：
/*    data为指针数组
/*    lastdownindex 为上一次计步波谷位置；
/*    len为指针数组长度
/*输出：计步步数
/************************************************************************/
int countStep(double *data,int len,bool &updir,bool &downdir)
{
	int step = 0;
	double me = mean(data,0,len-1);
	double st = var(data,0, len-1);
	double upmax = me+st/2, downmin = me - st/2;

	for(int i=0;i<len;i++){
		if(!updir && (data[i] >upmax))
			updir = true;
		if(updir && data[i] <downmin)
			downdir = true;
		if(updir && downdir){
			step++;
			updir = false;
			downdir = false;
		}
	}
	return step;
}
/************************************************************************/
/*姿态识别程序：
/*    1.通过sma 差分累积和，粗分类运动静止；
/*    2. sma<0.3 则认为静止，静止时通过z轴和svm之间判断 躺和其他静止状态（站立、坐）；
			theta = mean(ACCy)/mean(SVM)
		 	(1). theta< 0.3 站立
			(2). theta >0.3 && theta>0.8 坐
			(3). theta >0.8  躺
/*    3. sma >0.3 && sma <2 则认为走路
/*    4. sma >2 剧烈活动 认为跑步；
/*    /*输入：
/*    svm为合加速度信号
/*    accy为Y轴加速度信号
/*    len为信号长度
/*    updir 和downdir 存放的是上一次最后是否存在极大或者极小值

/输出：
/* pos 为一个结构体，包含当前姿态和计步数据
/*  姿态数据说明:(修改小数为整数 i*2+3)
/*   	-1.5  0 站立
/* 		-1*   1 坐 
/*		-0.5  2 躺
/*		0  	  3 休息：指不确定站立还是坐着。
/*      0.5   4 走路
/*		1     5 跑步
		1.5	  6 姿态转换
/*      2 	  7 发生跌倒
/************************************************************************/
pos PostureTag(double* svm, double* accy, int len,bool &updir,bool &downdir)
{
	double me = mean(svm,0,len-1);
	double st = var(svm,0,len-1);
	double sma = 0;
	int flag = 0;
	int step = 0;
	struct pos flags;

	for (int k = 1; k<len; k++)
	{
		sma += fabs(*(svm+k) - *(svm+k-1));		
		//cout <<k<<" "<< "*(svm+k)=" << *(svm + k) << "  " << *(svm + k - 1) << " " << sma << endl;
	}
	//cout << "子函数sma=" << sma << endl;
	//姿态判断
	
	if (sma < 0.3)
	{
		float theta = acos(fabs(mean(accy,0,len-1)) / me);
		if(theta >0.8)
			flag = 2;//表示躺
		else if (theta <0.3)
			flag = 0;
		else
			flag =1;
	}
	else
	{
		step = countStep(svm,len,updir,downdir);
		if (sma > 2)
			flag = 5;
		else if(sma<0.3 && sma>0.15)
			flag = 6;
		else
			flag =4;
		for (int j = 0; j<len; j++)
		{
			if (svm[j]>1.8 && mean(accy, j + 1,len-1) / mean(svm, j + 1,len-1) >0.86 && mean(accy,0,j) / mean(svm,0,j) <0.5)
			{
				flag = 6;
				break;
			}
		}
	}
	flags.flag = flag;
	flags.step = step;
	return flags;
}
/***********************************************************************/
/*% 设置一段时间内的flagattitude来纠错
% 需要检查的姿态：跌倒，站和坐的区分
% 不需要检查的姿态，走路，跑步，躺
% 判断流程：
%         1.如果跌倒后12s，即4个姿态中没有躺姿态，则认为误报，解除误报
%         2.如果站和坐过程中没有姿态转换信号，则认为当前姿态保持自上一个姿态
%         3.走路和跑步后的状态为站
%         4.如果发生姿态转换，且前后一致，则修改后面姿态与前面姿态相反
/*输入：
/*    tag为一段时间识别的姿态；
/*    len为指针数组长度；
/************************************************************************/
void checkflag(int* tag,int len)
{
	for(int i=0;i<len-1;i++){		
		if(i==0  && tag[i] !=7)
			continue;
		// 实现流程1：当前状态为跌倒状态，判断后面4个姿态存在躺状态则当前认为摔倒
		if(tag[i] ==7)
		{
			int n=0;
			for(int j=i+1;j<=i+4 && j<len;j++){
				if(tag[j] ==2)	n++;
			}
			if(n == 0) tag[i] = tag[i-1]; 
		}
		//实现流程2：
		if(tag[i] <=3 && tag[i] != tag[i-1])
			tag[i] = tag[i-1];
		//实现流程3
		if(tag[i] == 1 &&(tag[i-1] == 4 || tag[i-1]==5))
			tag[i] = 0;
		//实现流程4
		if(tag[i] ==6 && tag[i-1] == tag[i+1] ){
			tag[i+1] = tag[i-1] ==4?5:4;
		}
	}
	if(tag[len-1] != 7)
		tag[len-1] = tag[len-2];	
}
/*
姿态简化规则：
参数介绍：
	posture为输入数组;
	len 为数组长度；
	step 为这段时间内的走的步数
/*  姿态数据说明:
/*  姿态数据说明:(修改小数为整数 i*2+3)
/*   	-1.5  0 站立
/* 		-1*   1 坐 
/*		-0.5  2 躺
/*		0  	  3 休息：指不确定站立还是坐着。
/*      0.5   4 走路
/*		1     5 跑步
/*      1.5   6 状态改变：
/*      2 	  7 发生跌倒
/*			  8 活动(一段时间内没有主频姿态)
*/
//
int simplifyPosture(int *posture,int len)
{
	int countPosture[8] ={0};
	for(int i=0;i<len;i++){
		if(posture[i] == 0) countPosture[0]++;//Standing
		if(posture[i] == 1) countPosture[1]++;//Siting
		if(posture[i] == 2) countPosture[2]++;//Lyinging
		if(posture[i] == 3) countPosture[3]++;//Resting
		if(posture[i] == 4) countPosture[4]++;	//Walking
		if(posture[i] == 5) countPosture[5]++;//Runing
		if(posture[i] == 6) countPosture[6] = i;//存放姿态发生改变的位置
		if(posture[i] == 7) countPosture[7]++ ;
	}
	//如果跌倒，返回7
	if(countPosture[7] !=0) 
		return 7;
	int countIndex =  maxIndex(countPosture,6);
	if(countPosture[countIndex] > len/2)
		return countIndex;
	else
		return 8;//活动
}
/*
求最大值位置
*/
int maxIndex(int * data,int ilen)
{
	int index =0;
	for(int i=0;i<ilen;i++)
	{
		if(data[i]>data[index])
			index = i;
	}
	return index;
}