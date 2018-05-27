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
double mean(double *data, int len);
double var(double *data, int len);
int countStep(double *dst, int &index, int len);
void checkflag(int* tag,int len);
pos PostureTag(double* svm, double* accy, int len, int &lastdownindex);
int maxIndex(int * ,int );
int simplifyPosture(int *,int ,int );


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
	int lastdownindex = 0;
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
	Timewindows = round((m - 15) / stage);

	for (i = 1; i<Timewindows; i++)
	{
		int start = stage*(i - 1);
		int finish = start + 60;
		if (finish > m)
			break;

		for (int j = 0; j < finish - start + 1; j++)
		{
			svmonec[j] = svm[start + j + 1];
			accyonec[j] = ACCy[start + j + 1];
		}
		flags = PostureTag(svmonec, accyonec, finish - start + 1, lastdownindex);
		totalstep += flags.step;
		totalflag[i] = flags.flag;
	}
	

	checkflag(totalflag,i);
	system("pause");
	return 0;
}
/************************************************************************/
/* 指针数据求均值
/* 输入：
/*    data为指针数组
/*    len为指针数组长度
/* 输出： 该数组的均值
/************************************************************************/
double mean(double* data, int len)
{
	double sum = 0;
	int i = len;
	while (i--)
	{
		sum += *data++;
	}
	return sum / len;
}
/************************************************************************/
/*指针数组求方差
/*输入：   data 为指针数组；
/*        len 为指针数组长度；
/*输出：  返回指针数组方差
/************************************************************************/
double var(double* data, int len)//len长度数组求方差
{
	double sum = 0;
	double ave = mean(data, len);
	int i = len;
	while (i--)
	{
		sum += (*data - ave)*(*data - ave);
		*data++;
	}
	return sqrt(sum / len);
}
/************************************************************************/
/*极值计步算法
/*        1, 通过三轴加速度数据,求均值(me)和方差(std);
/*        2, 设置两个bool变量updir和downdir 初始值为updir = false,downdir = true;
/*        3, 在updir方向查找较大值upmax:
/*            满足upmax>me+st
/*        4，3满足时,updir=1&& downdir=0:
/*            在downdir方向查找极小值，满足downmin < me-st; 
/*        5， 4满足则downdir =1,则认为走了一步；   
/*输入：
/*    data为指针数组
/*    lastdownindex 为上一次计步波谷位置；
/*    len为指针数组长度
/*输出：计步步数
/************************************************************************/
int countStep(double *data, int &lastdownindex, int len)
{
	bool updir = false, downdir = true;
	int downindex = 0;
	int step = 0;
	double me = mean(data, len);
	double st = var(data, len);
	double upmax = me, downmin = me;

	int i = lastdownindex;
	while (i++ < len)
	{
		if (downdir)
		{
			if (*data > me + st && *data > upmax)
				upmax = *data;
			if (*data < me - st && upmax > me + st)
			{
				updir = true;
				downdir = false;
				*data--;
			}
		}
		if (updir)
		{
			if (*data < (me - st) && downmin > *data)
			{
				downmin = *data;
				downindex = i;
			}
			if (*data > (me + st) && downmin < (me - st))
			{
				downdir = true;
				updir = false;
				lastdownindex = downindex;
				step++;
				upmax = me + st;
				downmin = me - st;
				*data--;//退回一位，防止采样率低导致大于me+st的极大值只有一个的值。
			}
		}
		*data++;
	}
	lastdownindex = (lastdownindex > 45) ? (lastdownindex - 45) : 0;
	return step;
}
/************************************************************************/
/*姿态识别程序：
/*    1.通过sma 差分累积和，粗分类运动静止；
/*    2. sma<1.2 则认为静止，静止时通过z轴和svm之间判断 躺和其他静止状态（站立、坐）；
/*    3. sma >1.2 则运动
/*    4. sma >20 剧烈活动 认为跑步；
/*    5. sma <20 && sma>1.2 计步不为0，则认为走路
/*    6. sma <3.5 && step =0 ,则认为处于姿态转换阶段
/*输入：
/*    svm为合加速度信号
/*    accy为Y轴加速度信号
/*    len为信号长度
/*    lastdownindex 为上次波谷位置

/输出：
/* pos 为一个结构体，包含当前姿态和计步数据
/*  姿态数据说明:(修改小数为整数 i*2+3)
/*   	-1.5  0 站立
/* 		-1*   1 坐 
/*		-0.5  2 躺
/*		0  	  3 休息：指不确定站立还是坐着。
/*      0.5   4 走路
/*		1     5 跑步
/*      1.5   6 状态改变：
/*      2 	  7 发生跌倒
/************************************************************************/
pos PostureTag(double* svm, double* accy, int len,int &lastdownindex)
{
	double me = mean(svm, len);
	double st = var(svm,len);
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
	if (sma < 1.2)
	{
		double theta = acos(fabs(mean(accy,len)) / me);
		flag = (theta > pi / 3 && theta<2 * pi / 3) ? 2 : 3;
	}
	else
	{
		if (st>0.05)
			step = countStep(svm, lastdownindex, len);

		if (sma > 20)
			flag = 5;
		else
		{
			if (sma <3.5 && step <= 1)
				flag = 6;
			else
				flag = 4;
		}
		for (int j = 0; j<len; j++)
		{
			if (svm[j]>1.8 && mean(accy, j + 1) / mean(svm, j + 1) >0.86 && mean(accy + j, len - j) / mean(svm + j, len- j) <0.5)
			{
				flag = 7;
				break;
			}
		}
	}
	flags.flag = flag;
	flags.step = step;
	return flags;
}
/************************************************************************/
/*姿态检查修改阶段
/*     1. 如果发生跌倒，并且之后3s 后出现连续平躺姿态，自认为发生跌倒；
/*     2. 如果不确定当前静止状态，则将值改为0，直到出现走路和跑步然后按规则3-5；
/*    3. 姿态变换设定为 静止-改变-静止 模板匹配；
/*    4. 走路/跑步之后认为当前姿态为站立，如果发生姿态转换，则认为改变后为坐；没有发生状态改变则延续上一动作；
/*    5. 如果改变前后姿态不为静止则 将改变改为上一个状态；
/*输入：
/*    tag为一段时间识别的姿态；
/*    len为指针数组长度；
/************************************************************************/
void checkflag(int* tag,int len)
{
	int ret = len;
	for(int i=0;i<len;i++){
		if(tag[i] ==7)
		{

		}
		if(tag[i] == 3 && (tag[i-1] == 4 || tag[i-1] ==5)){
			tag[i] = 0;
			continue;
		}
		if(tag[i] ==3 && (tag[i-1]<=3)){
			tag[i] = tag[i-1];
			continue;
		}
		if(tag[i] == 6 && i+1<len && tag[i+1] ==3){
			if(tag[i-1] >3){
				tag[i] = tag[i-1];
				continue;
			}
			tag[i+1] = tag[i-1]==0 ?1:0;
		}
		else{
			if(tag[i] == 6)
				tag[i] = tag[i-1];
		}
	}
}
	/*while (ret--&& *tag++)
	{
		if (*tag == 7) // 当前状态为跌倒状态，判断后面连续5个躺状态则当前认为摔倒
		{
			int* tmp = tag;
			int i=1;
			while(*(tmp +i) && *(tmp+i) ==2)

			while (*tmp != 2  && tmp - tag >5)
				*tmp++;
			if (tmp - tag == 5)
			{
				*tag = *(tag - 1);
				continue;
			}
		}
		if (*tag == 3 && (*(tag - 1) == 4 || *(tag - 1) == 5))
			//当前状态判定为休息，且前面一个状态为走路或者跑步，则后面一个为站立
		{
			*tag = 0;
			continue;
		}
		if (*tag == 3 && *(tag - 1) <= 3)
			//当前状态为3，且前面一个为静止态，则认为同上一个状态
		{
			*tag = *(tag - 1);
			continue;
		}
		if (*tag == 6 && *(tag + 1) == 3)
			//当前状态为改变，并且下一个状态为休息，进行前后状态发生改变情况
		{
			if ((*tag - 1) >3)
			{
				*tag = *(tag - 1);
				continue;
			}

			*(tag +1)  = *(tag-1) == 0 ?1:0;
		}
		else{
			if (*tag = 6)
				*tag = *(tag - 1);
		}
	}
}*/

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
*/
int simplifyPosture(int *posture,int len,int step)
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
	//如果发生姿态转换，则返回转换后的姿态
	if(countPosture[6] !=0 )
		return posture[countPosture[6] - 1] == 0 ? 1:0;//countPosture[6]存放姿态转换位置，posture[countPosture[6] - 1]则为姿态转换前的姿态

	int countIndex =  maxIndex(countPosture,6);
	return maxIndex(countPosture,6);
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