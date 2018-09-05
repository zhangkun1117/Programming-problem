/*****************************************************************************
*
*function    : 读取传感器数据，进行姿态判别。
*Description : <math.h>建立编译工具链的时候已经弄好了	
*
*
*****************************************************************************/
#include <math.h>        
#include "ql_timer.h"
#include "ril_location.h"
#include "ql_uart.h"
#include "ql_error.h"
#include "ril.h"
#include "ril_system.h"
#include "ql_stdlib.h"
#include "ql_trace.h"
#include "cellphone.h"
#include "gps.h"
#include "ql_type.h"
#include "ql_gpio.h"
#include "ql_iic.h"
#include "ql_error.h"
#include "I2C.h"
#include "pos.h"

#define DEBUG_ENABLE 1
#if DEBUG_ENABLE > 0
#define DEBUG_PORT  UART_PORT1
#define DBG_BUF_LEN   64
static char DBG_BUFFER[DBG_BUF_LEN];
#define APP_DEBUG(FORMAT,...) {\
    Ql_memset(DBG_BUFFER, 0, DBG_BUF_LEN);\
    Ql_sprintf(DBG_BUFFER,FORMAT,##__VA_ARGS__); \
    if (UART_PORT2 == (DEBUG_PORT)) \
    {\
        Ql_Debug_Trace(DBG_BUFFER);\
    } else {\
        Ql_UART_Write((Enum_SerialPort)(DEBUG_PORT), (u8*)(DBG_BUFFER), Ql_strlen((const char *)(DBG_BUFFER)));\
    }\
}
#else
#define APP_DEBUG(FORMAT,...) 
#endif



/* 定时读取传感器数据，30ms为周期 */
#define SENSOR_DATA_ID         TIMER_ID_USER_START + 4
#define SENSOR_DATA_PERIOD     50

#define pi                     3.1415926 

static void Callback_Sensor_Timer(u32 timerId, void* param);

/* 全局变量，用以保存传感器数据 */
s16 ax,ay,az,gx,gy,gz;

Enum_POSSTATE m_Pos_State = STATE_POS_SITTING;	/* 初始状态，默认--坐 */
u32 Steps_1min = 0;

static s32 Sensor_Index = 0;					/* 计数周期：50ms */
static s32 Tag_Index = 0;						/* 计数周期：3S */
static s32 Index_LastDown = 0;					/* 上一次的波谷 */
bool Flag_Is_FistTime = FALSE;

//static double PosBuf[200] = {0.0};


static double temp_svm[60] = {0};
static double temp_accy[60] = {0};

static double svm[80] = {0};
static double accy[80] = {0};


typedef struct 
{
	float flag;
	s32 step;
}FuXing_Pos;


void RegTimer_SensorTimer()
{
	s32 ret;
	
	//注册传感器读取定时器
	//FAST timer!
	ret = Ql_Timer_RegisterFast(SENSOR_DATA_ID, Callback_Sensor_Timer, NULL);

	if (QL_RET_OK != ret)
	{
		APP_DEBUG("reg sensor timer failed\r\n");
	}

	//APP_DEBUG("double is %d,float is %d\r\n",sizeof(double),sizeof(float));
}

/* 开启传感器读取定时器 */
void Fuxing_OpenSensorTimer()
{
	Ql_Timer_Start(SENSOR_DATA_ID, SENSOR_DATA_PERIOD, TRUE);
}

/* 关闭传感器读取定时器 */
void Fuxing_CloseSensorTimer()
{
	Ql_Timer_Stop(SENSOR_DATA_ID);
}
/*-------------------------------------------------------------------------------------------------------------*/

/*求均值*/
double mean(double* data, s32 len)
{
	double sum = 0;
	for (s32 i = 0; i < len; i++)
		sum += data[i];
	return sum / len;
}
/*求标准差*/
double var(double* data, s32 len)//len长度数组求方差
{
	double sum = 0;
	double ave = mean(data, len);
	for (s32 i = 0; i < len; i++)
	{
		sum += (data[i] - ave)*(data[i] - ave);
	}
	//cout << sqrt(sum / len) << endl;
	return sqrt(sum / len);
}
/************************************************************************/
/*极值计步算法
/*        1, 通过三轴加速度数据,求均值(me)和方差(std);
/*        2, 设置两个updir和downdir 初始值为0,1;
/*        3, 在updir方向查找较大值upmax:
/*            满足upmax>me+st
/*        4，3满足时,updir=1&& downdir=0:
/*            在downdir方向查找极小值，满足downmin < me-st; 
/*        5， 4满足则downdir =1,则认为走了一步；   
/*输入：
/*    	  data指向数组的起始位置；
/*        lastdownindex 为上一次计步波谷位置；
/*        len为指针数组长度
/*输出：     计步步数
/************************************************************************/
s32 countStep(double *data, s32 *lastdownindex, s32 len)
{
	bool updir = FALSE, downdir = TRUE;
	s32 downindex = 0;
	s32 step = 0;
	double me = mean(data, len);
	double st = var(data, len);
	double upmax = me, downmin = me;

	s32 i = *lastdownindex;
	while (i++ < len)
	{
		if (downdir)
		{
			if (*data>me + st && *data >upmax)
				upmax = *data;
			if (*data<me - st && upmax > me + st)
			{
				updir = TRUE;
				downdir = FALSE;
			}
		}
		if (updir)
		{
			if (*data < (me - st) && downmin > *data)
			{
				downmin = *data;
				downindex = i;
			}
			if (*data>(me + st) && downmin < (me - st))
			{
				downdir = TRUE;
				updir = FALSE;
				*lastdownindex = downindex;
				step++;
				upmax = me + st;
				downmin = me - st;
			}
		}
		*data++;
	}
	*lastdownindex = (*lastdownindex > 60) ? (*lastdownindex - 60) : 0;
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
/************************************************************************/
FuXing_Pos PostureTag(double* svm, double* accy, s32 len,s32 *lastdownindex)
{
	double me = mean(svm, len);
	double st = var(svm,len);
	double sma = 0;
	double flag = 0;
	s32 step=0,j=0,k= 0;
	FuXing_Pos flags = {0,0};
	double theta = 0.0;

	for (k = 1; k<len; k++)
	{
		sma += fabs(*(svm+k) - *(svm+k-1));		
	}
	//APP_DEBUG("sma=%lf\n",sma);
	//APP_DEBUG("me=%lf\r\n",me);
	//APP_DEBUG("st=%lf\r\n",st);

	//姿态判断
	if (sma < 1.2)
	{
		theta = acos(fabs(mean(accy,len)) / me);
		flag = (theta > pi / 3 && theta<2 * pi / 3) ? (-0.5) : 0;
	}
	else
	{
		if (st>0.05)
			step = countStep(svm, lastdownindex, len);

		if (sma > 20)
			flag = 1;
		else
		{
			if (sma <3.5 && step == 0)
				flag = 1.5;
			else
				flag = 0.5;
		}
		for (j = 0; j<len; j++)
		{
			if (svm[j]>1.8 && mean(accy, j + 1) / mean(svm, j + 1) >0.86 && mean(accy + j, len - j) / mean(svm + j, len- j) <0.5)
			{
				flag = 2;
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
/*     3. 姿态变换设定为 静止-改变-静止 模板匹配；
/*     4. 走路/跑步之后认为当前姿态为站立，如果发生姿态转换，则认为改变后为坐；没有发生状态改变则延续上一动作；
/*     5. 如果改变前后姿态不为静止则 将改变改为上一个状态；
/*输入：
/*     tag为一段时间识别的姿态；
/*     len为指针数组长度；
/************************************************************************/
void checkflag(double* tag,int len)
{
	int ret = len;
	while (ret--&& *tag++)
	{
		if (*tag == 2) // 当前状态为跌倒状态，判断后面连续5个躺状态则当前认为摔倒
		{
			double* tmp = tag;
			while (*tmp != -0.5 && tag - tmp >5)
				*tmp++;
			if (tmp - tag == 5)
			{
				*tag = *(tag - 1);
				continue;
			}
		}
		if (*tag == 0 && (*(tag - 1) == 0.5 || *(tag - 1) == 1))
			//当前状态判定为休息，且前面一个状态为走路或者跑步，则后面一个为站立
		{
			*tag = -1.5;
			continue;
		}
		if (*tag == 0 && *(tag - 1) <= 0)
			//当前状态为0，且前面一个为静止态，则认为同上一个状态
		{
			*tag = *(tag - 1);
			continue;
		}
		if (*tag == 1.5 && *(tag + 1) == 0)
			//当前状态为改变，并且下一个状态为休息，进行前后状态发生改变情况
		{
			if ((*tag - 1) >0)
			{
				*tag = *(tag - 1);
				continue;
			}
			if (*(tag - 1) == -1.5)
			{
				*(tag + 1) = -1;
			}
			if (*(tag - 1) == -1)
			{
				*(tag + 1) = -1.5;
			}
		}
		else{
			if (*tag = 1.5)
				*tag = *(tag - 1);
		}
	}
}
/*****************************************
*	类型:	定时器返回函数
*	功能:	<1>读取传感器数据
*		  <2>
*		  <3>
*	返回：无			
******************************************/
static double last_svm[20] = {0.0};
static double last_accy[20] = {0.0};


static void Callback_Sensor_Timer(u32 timerId, void* param)
{
	FuXing_Pos flags = {0,0};
	double d_ax,d_ay,d_az;
	s32 ret;

	/* 50ms定时时间到，此时应该通过I2C总线读取传感器数据 */
	if(SENSOR_DATA_ID==timerId)
	{
		MPU6050_getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
		d_ax = (double)ax/16384.0;
		d_ay = (double)ay/16384.0;
		d_az = (double)az/16384.0;
		/* 进行姿态判别 */
		/* 如何实现部分数据的重叠？？ */ 
		if( Sensor_Index < 60 )
		{
			temp_svm[Sensor_Index]  = sqrt(pow(d_ax, 2) + pow(d_ay, 2) + pow(d_az, 2));
			temp_accy[Sensor_Index] = d_ay;
			Sensor_Index++;
		}
		else
		{
			Sensor_Index = 0;
			
			if ( Flag_Is_FistTime == TRUE )
			{
				Ql_memset((void *)svm,0,20*sizeof(double));
				Ql_memset((void *)accy,0,20*sizeof(double));
				Ql_memcpy(svm+20,temp_svm,60*sizeof(double));
				Ql_memcpy(accy+20,temp_accy,60*sizeof(double));
				Flag_Is_FistTime = FALSE;
			}else
			{
				Ql_memcpy(svm,last_svm,20*sizeof(double));
				Ql_memcpy(accy,last_accy,20*sizeof(double));
				Ql_memcpy(svm+20,temp_svm,60*sizeof(double));
				Ql_memcpy(accy+20,temp_accy,60*sizeof(double));			
			}
			Ql_memcpy(last_svm,svm+60,20*sizeof(double));
			Ql_memcpy(last_accy,accy+60,20*sizeof(double));
			
			flags = PostureTag(svm, accy,80,&Index_LastDown);

			//APP_DEBUG("pos = %f ,steps = %d\r\n",flags.flag,flags.step);

			if( Tag_Index < 20 )
			{
				//PosBuf[Tag_Index] = flags.flag;
				//Steps_1min += flags.step;
				Tag_Index++;
			}
			else
			{
				APP_DEBUG("1 min\r\n");
				//1min时间到
				//checkflag(PosBuf,20);
				Tag_Index = 0;

				ret  = Ql_OS_SendMessage (0, MSG_ID_URC_INDICATION_JINGO, REMOTE_CURRENT_GPSLOCATE,0);

				ret = BulidRequest_Post_PosAndLoc();
				
			}	

		}
	}
}
