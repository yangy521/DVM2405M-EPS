/*******************************************************************************
* Filename: iTimer.c	                                             	 		   *
* Description:											   			 		   *
* Author:                                                           		   *
* Date:     														 		   *
* Revision:															 		   *
*******************************************************************************/

#include		"iTimer.h"

tNetTimer netTimer[32];		//定时器

//网络定时器初始化
void netTimerInit(void)
{
	unsigned int i;
	for(i=0;i<sizeof(netTimer)/sizeof(netTimer[0]);i++)
	{
		KillNetTimer(i);
	}
}

/*********************************************************************************************************
** 函数名称: netTimerUpdate
** 功能描述: 网络事件定时器计时(单位ms)
** 输　入: 定时时常（us）
** 输　出: 
********************************************************************************************************/
void netTimerUpdate(unsigned int us)
{
	unsigned int i,co;
	if(us>1000)
	{
		return;
	}
	co=1000/us;	//定时系数
	for(i=0;i<sizeof(netTimer)/sizeof(netTimer[0]);i++)
	{
		if(netTimer[i].bIsStart)
		{	
			netTimer[i].ulTimerCount++;
			if(netTimer[i].ulTimerCount>=netTimer[i].ulDeadline*co)
			{
				netTimer[i].bIsOvertime=true;
				netTimer[i].ulTimerCount=netTimer[i].ulDeadline;
			}
			else
			{
				netTimer[i].bIsOvertime=false;
			}
		}
	}
	
}

//启动网络定时器
void SetNetTimer(unsigned char ucTimerID,unsigned long ulDeadline)
{
	netTimer[ucTimerID].ulTimerCount=0;
	netTimer[ucTimerID].ulDeadline=ulDeadline;
	netTimer[ucTimerID].bIsStart=true;
	netTimer[ucTimerID].bIsOvertime=false;
}

//复位网络定时器
void ResetNetTimer(unsigned char ucTimerID)
{
	netTimer[ucTimerID].ulTimerCount=0;
	netTimer[ucTimerID].bIsOvertime=false;
}

//删除网络定时器
void KillNetTimer(unsigned char ucTimerID)
{
	netTimer[ucTimerID].ulTimerCount=0;
	netTimer[ucTimerID].ulDeadline=0;
	netTimer[ucTimerID].bIsStart=false;
	netTimer[ucTimerID].bIsOvertime=false;
}
