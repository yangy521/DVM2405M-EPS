/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : MC_MotorControl_Layer.c
* Author             :   
* Date First Issued  : 
* Description        : 
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "PLCLogic.h"
#include "MC_MotorControl_Layer.h"
#include "CommonRam.h"
#include "iTimer.h"
#include "CanOpen_QexpandAgvV04.h"
#include "Device.h"
void GetNewTargetValue(void)
{
		INT32S lTemp;
	
//		GetCmdPercent();	//模拟指令转换为指令百分比
		
		if (gPLCCtl.ctrl_mode == CTRL_M)
		{			
			if(gPLCCtl.scs == SCS1_AV) //模拟指令
			{
				gCRam.SetPos=_GetSetPosition(); 	/* 得到设定位置值 */
			}
			else  //数字指令
			{
				lTemp = QExpandAGV_PDO.VCUCmdAngle;  //指令角度（0.1°）
				lTemp = lTemp*gPLCCtl.CycleLimit/3600; 		//degree to position
				if(lTemp > gPLCCtl.MaxPosition) lTemp = gPLCCtl.MaxPosition;
				else if(lTemp < -gPLCCtl.MaxPosition)	lTemp = -gPLCCtl.MaxPosition; 
				gCRam.SetPos=lTemp;
			}
			
			if(gPLCCtl.RotateDir)  //旋转方向反向
				gCRam.SetPos=-gCRam.SetPos;
		}
		else if (gPLCCtl.ctrl_mode == CTRL_V)
		{		
			if(gPLCCtl.scs == SCS1_AV) //模拟指令
			{
				lTemp = gCRam.CmdPercent;
				lTemp = lTemp*gPLCCtl.ssp/100;
				lTemp=(lTemp*(int)gPLCCtl.enc)/60;

				if(gCRam.CmdDirection==1)	lTemp = lTemp;
				else 	if(gCRam.CmdDirection==-1)	lTemp = -lTemp;	
				else lTemp=0;
			}
			else  //数字指令
			{
				lTemp = (INT32S)QExpandAGV_PDO.VCUCmdSpeed*gPLCCtl.enc/60;		  //指令速度rpm									
			}	

			if(gPLCCtl.RotateDir) lTemp=-lTemp; //旋转方向反向					
			if(lTemp>gCRam.MaxSpeed)lTemp=gCRam.MaxSpeed;
			else if(lTemp<-gCRam.MaxSpeed)lTemp=-gCRam.MaxSpeed;
			gCRam.SetSpeed=lTemp;			
		}
		else if (gPLCCtl.ctrl_mode == CTRL_I)
		{		
			lTemp = gCRam.CmdPercent;
			lTemp = lTemp*gPLCCtl.scc/100;
			lTemp=(int)GetAdFromI(lTemp);

			if(gCRam.CmdDirection==1)	lTemp = lTemp;
			else 	if(gCRam.CmdDirection==-1)	lTemp = -lTemp;	
			else lTemp=0;
		
			if(lTemp>MAX_ISET)lTemp=MAX_ISET;
			else if(lTemp<-MAX_ISET)lTemp=-MAX_ISET;
			gCRam.ISet=lTemp;		
		}			
		else if (gPLCCtl.ctrl_mode == CTRL_A)
		{
			lTemp = gCRam.CmdPercent;
			lTemp = lTemp*MAX_PWM/100;

			if(gCRam.CmdDirection==1)	lTemp = lTemp;
			else 	if(gCRam.CmdDirection==-1)	lTemp = -lTemp;	
			else lTemp=0;
		
			if (lTemp>MAX_PWM)	lTemp = MAX_PWM;
			else if (lTemp<-MAX_PWM)	lTemp = -MAX_PWM;
		
			gCRam.SetPwm=lTemp;
		}
		else
		{//无效模式,关闭PWM
			gCRam.bPwmClose=1;
		}
	
}

void ChangeModScs(INT16U nMod,INT16U nScs)
{

	long lTemp;

		if (nMod == CTRL_M)
		{//
			g_lPEK2=g_lPEK1=0;
			if(gPLCCtl.ctrl_mode==CTRL_I || gPLCCtl.ctrl_mode==CTRL_A)
			{
				g_lVEK1=g_lVEK2=g_lVEK3=0;
			}

			GetNewTargetValue();
				
		}
		else if (nMod == CTRL_V)
		{
			if(gPLCCtl.ctrl_mode==CTRL_I || gPLCCtl.ctrl_mode==CTRL_A)
			{
				g_lVEK1=g_lVEK2=g_lVEK3=0;
			}
			if(nScs==SCS0_CAN)
			{
				lTemp=gCRam.CANSetV*gPLCCtl.enc/60; //指令速度

				if(lTemp>gCRam.MaxSpeed)lTemp=gCRam.MaxSpeed;
				else if(lTemp<-gCRam.MaxSpeed)lTemp=-gCRam.MaxSpeed;
				gCRam.SetSpeed=lTemp;
				if(gPLCCtl.ctrl_mode==CTRL_I || gPLCCtl.ctrl_mode==CTRL_A)
					gCRam.OldSetSpeed=gCRam.SetSpeed;
			}
			else if(nScs==SCS1_AV)
			{
				GetNewTargetValue();
				if(gPLCCtl.ctrl_mode==CTRL_I || gPLCCtl.ctrl_mode==CTRL_A) gCRam.OldSetSpeed=gCRam.SetSpeed;				
			}	
		}	
		else if (nMod == CTRL_I)
		{	
			if(nScs==SCS0_CAN)
			{
				lTemp=gCRam.CANSetI;
				if(lTemp>gPLCCtl.scc)lTemp=gPLCCtl.scc;
				else if(lTemp<-gPLCCtl.scc)lTemp=-gPLCCtl.scc;				
				lTemp=GetAdFromI(lTemp);					

				if(lTemp>MAX_ISET)lTemp=MAX_ISET;
				else if(lTemp<-MAX_ISET)lTemp=-MAX_ISET;
				gCRam.ISet=lTemp;							
			}
			else if(nScs==SCS1_AV)
			{
					
			}
		}	
		else if (nMod == CTRL_A)
		{
				if(nScs==SCS0_CAN)
				{
						lTemp=gCRam.CANSetA;
						if(lTemp>100)lTemp=100;
						else if(lTemp<-100) lTemp=-100;
						lTemp=lTemp*MAX_PWM/100;
					
						if(lTemp>MAX_PWM) gCRam.SetPwm=MAX_PWM;
						else if(lTemp<-MAX_PWM) gCRam.SetPwm=-MAX_PWM;
						else gCRam.SetPwm=lTemp;			
				}
				else if(nScs==SCS1_AV)
				{
//					GetNewTargetValue();
				}
		}
		gPLCCtl.ctrl_mode=nMod;
		gPLCCtl.scs=nScs;

		setDataBitGroup(gCRam.SI,MOD,nMod);
		setDataBitGroup(gCRam.SI,SCS,nScs);
}
//电机控制初始化程序
void	InitPLCCtl(void)
{
//	static unsigned int ErrCount=0;	
	  static unsigned int count=0;
		//
		//母线电容电压检测
		//
		while(1)  
		{
				if (gCurrentSample.VBus > RELAYON_THRESHOLD)   
				{
					if(netTimer[Timer_VBusCheck].bIsStart==false)
					{
						SetNetTimer(Timer_VBusCheck,500);
					}
					if(netTimer[Timer_VBusCheck].bIsOvertime==true)
					{
//						RELAY_ON();
//						gPLCCtl.doDataOut[RELAY]=1;
						setDataBit(gCRam.SI,KSIRDY);	
						setDataBit(gCRam.SI,VBUSRDY);	
		//					SL_SET(PLC_VBUS_RDY);
						KillNetTimer(Timer_VBusCheck);
						break;
					}
				}
				else
				{
					if(netTimer[Timer_RelayDelay].bIsStart==false)
					{
						SetNetTimer(Timer_RelayDelay,3000);
					}
					if(netTimer[Timer_RelayDelay].bIsOvertime==true)
					{		
						MCL_SetFault(BUS_CAP_ERR);	
						KillNetTimer(Timer_RelayDelay);
						break;
					}
				}	
		}
		
		while(1)  //电流采样零漂计算
		{
			count++;
			Delay(100);//延时等待
			gCurrentSample.Calc_ZeroDrift(&gCurrentSample);
			if(count>1024)	//
				break;
		}
		
		g_nMainState=MAIN_STATE_STOP;
#ifdef HOMESW_POINT
		EepromQualifiedRead(EEPROM_PVD_ADDR, &gPLCCtl.HomeFlagRd);	//读取上次的中位位置标志
#endif	
		
		CfgVariable();		

		ChangeModScs(gPLCCtl.ctrl_mode,gPLCCtl.scs);
		
//		TIM_CtrlPWMOutputs(TIM1, ENABLE); //PWM enable	
		TIM1->CCER |= 0x0055; 	//打开四路PWM输出
	  setDataBit(gCRam.SI,EN_PWM);
		
		/***********短路检测***********/
//		count=800; //100ms  10A电流建立时间大概40ms
//		gCRam.bPwmClose=0;				  
//		while(count--)
//		{
////			if(count&0x01)
////				gCRam.PwmValue=-SHORTCHECK_PWM;	//20A
////			else
//				gCRam.PwmValue=SHORTCHECK_PWM;	//20A
//			PwmUpdate();	
//			delay_us(100);	//100us		
//			if(gCurrentSample.U<0) gCurrentSample.U=-gCurrentSample.U;		
//			
//			if(gCurrentSample.U > (I20A/2)) //电流大于10A,则认为电机短路！
//			{
//				ErrCount++;
//				if(ErrCount>300) //30ms时间到
//				{
//					MCL_SetFault(MOTOR_SHORTCUT_ERR);			
//					break;
//				}
//			}					
//		} 
//		gCRam.PwmValue=0;
//		gCRam.bPwmClose=1;				
		/*********end of 短路检测******/

		g_nMainState =MAIN_STATE_ZEROAUTO;
		g_nZeroRunState=ZERO_RUN_INIT;
}


int myvpid(long lSetSpeed,long lMeaSpeed)
{
	long lTemp,lTemp0,lTemp1,lTemp2;
	float fTemp,fTemp0,fTemp1,fTemp2,fTemp3;
	
	static long lRamp=0;
	static int integar=0;

	if(gCRam.bPwmClose)
	{
		g_lVEK2=0;
		g_lVEK1=0;
		gCRam.OldSetSpeed=0;
		lTemp=0;
		gCRam.SpeedEK=0;
		lRamp=0;
	}
	else
	{
		gCRam.SpeedEK=lSetSpeed-lMeaSpeed;
		//
		lTemp0=lSetSpeed-gCRam.OldSetSpeed;
			
		if(SL_CHK(SL_TER_CURRENT_CUT))	//消减电流指令
		{
			lTemp0 = 0;
		}
		if(SL_CHK(PLC_MAX_VOLTAGE_ERR))	//消减电流指令
		{
			lTemp0 = 0;
		}		
		
		if(lTemp0>0)
		{
			lRamp+=gCRam.Acceleration;
			gCRam.OldSetSpeed+=(lRamp/1000);
			lRamp=lRamp%1000;
			gCRam.OldSetSpeed+=gCRam.Acceleration;
			if(gCRam.OldSetSpeed>lSetSpeed)gCRam.OldSetSpeed=lSetSpeed;
		}
		else if(lTemp0<0)
		{
			lRamp+=gCRam.Acceleration;
			gCRam.OldSetSpeed-=(lRamp/1000);
			lRamp=lRamp%1000;
			gCRam.OldSetSpeed-=gCRam.Acceleration;
			if(gCRam.OldSetSpeed<lSetSpeed)gCRam.OldSetSpeed=lSetSpeed;
		}
		lTemp0=gCRam.OldSetSpeed;
		if(lTemp0>gCRam.MaxSpeed)lTemp0=gCRam.MaxSpeed;
		else if(lTemp0<-gCRam.MaxSpeed)lTemp0=-gCRam.MaxSpeed;
		
		fTemp2=lTemp2=lTemp0-lMeaSpeed;
		fTemp3=g_lVEK1;
		
		fTemp0=(long)gPLCCtl.Vp*(fTemp2-fTemp3);
		
		fTemp1=(long)gPLCCtl.Vi*fTemp2+g_nIntegar;
		lTemp1=(long)fTemp1;
		g_nIntegar=lTemp1&0x3fff;
		
		if(gPLCCtl.Vd==0)
		{
			fTemp3=0;
		}
		else
		{
			fTemp3=(long)gPLCCtl.Vd*(fTemp2+g_lVEK2-fTemp3-fTemp3);	
		}	

		fTemp=(fTemp0+fTemp1+fTemp3)/16384;
		if(fTemp>MAX_PWM)lTemp=MAX_PWM;
		else if(fTemp<-MAX_PWM)lTemp=-MAX_PWM;
		else lTemp=(long)fTemp;
		
		if(lTemp==0)
		{
			if(lTemp2>0)integar++;
			else if(lTemp2<0)integar--;
			else integar=0;
			if(integar>8)
			{
				lTemp=1;
				integar=0;
			}
			else if(integar<-8)
			{
				lTemp=-1;
				integar=0;
			}	 
		}
		else integar=0;	
		
		if(lTemp>MAX_PWM) lTemp=MAX_PWM;
		else if(lTemp<-MAX_PWM)	lTemp=-MAX_PWM;
		g_lVEK2=g_lVEK1;
		g_lVEK1=lTemp2;		
	}
	return (int)lTemp;
}

void Homing(void)
{
	static int nMod,nScs;
	static long lPs;
	static long lTemp;
	static unsigned int nTimes=0,nTimes1=0;
	static long lOldPs;
	
	if(!gPLCCtl.IsHomeEna)		//是否启用回中
	{
		g_nMainState = MAIN_STATE_RUN; 
		return;
	}
	
	if(!gCRam.bEnaHard) 
	{
		gPLCCtl.doDataOut[LOCK_OUT]=0;  //互锁信号
		return; //等待使能有效
	}
	else
		gPLCCtl.doDataOut[LOCK_OUT]=1;  //互锁信号
	
		
	switch(g_nZeroRunState)
	{
		case ZERO_RUN_INIT:
				//初始化变量
		  gCRam.HomSw_sta=READ_HOME(); //Home switch 初始状态
			gCRam.FindZ=0;
			gCRam.HomeStep = 0;
			SL_CLR(SL_TER_CWLI);  //清除正向禁止标志
			SL_CLR(SL_TER_CCWLI);  //清除反向禁止标志

			//保护现场
			nMod=gPLCCtl.ctrl_mode;
			nScs=gPLCCtl.scs;
			lPs=gCRam.SetPos=gCRam.RelPos;
			gCRam.MaxSpeed=(INT32S)gPLCCtl.sov*gPLCCtl.enc/60;	//寻零最大速度				
			
			//模式设置
			ChangeModScs(CTRL_M,SCS1_AV);
			nTimes=0;
			nTimes1=0;
			if(gCRam.bEnaHard && SL_CHK(SL_TER_RDY))
			{
				if(gPLCCtl.HomeMode==1)  //单点回中
				{
					if(gPLCCtl.HomeFlagRd) 	//上次位置标志(反向)
					{
						if(gCRam.bHomeDir)
							g_nZeroRunState=ZERO_RUN_LEFT;
						else
							g_nZeroRunState=ZERO_RUN_RIGHT;
					}								
					else	//正向
					{
						if(gCRam.bHomeDir)
							g_nZeroRunState=ZERO_RUN_RIGHT;	
						else
							g_nZeroRunState=ZERO_RUN_LEFT;
					}	
				}
				else  //面域回中
				{
					if(READ_HOME()==GPIO_PIN_SET) //中位开关状态
					{
						if(gCRam.bHomeDir)
							g_nZeroRunState=ZERO_RUN_LEFT;
						else
							g_nZeroRunState=ZERO_RUN_RIGHT;
					}								
					else	
					{
						if(gCRam.bHomeDir)
							g_nZeroRunState=ZERO_RUN_RIGHT;	
						else
							g_nZeroRunState=ZERO_RUN_LEFT;
					}	
				}						
			}			
			break;			
		case ZERO_RUN_RIGHT:			//正向寻零	
			if(!SL_CHK(SL_TER_CWLI)) 
			{
				gCRam.SetPos=lPs+gPLCCtl.sop;	//设置目标位置
			}
			else
			{
				#ifdef HOME_ZERO
				gCRam.SetPos=0;
				#endif
				g_nZeroRunState=ZERO_RUN_SETZERO;
			}				

			if(!gCRam.FindZ)
			{		    		
				//堵转
				lTemp=lOldPs-gCRam.RelPos;
				if(lTemp>-HOME_STALLCNT && lTemp<HOME_STALLCNT) nTimes++;
				else nTimes=0;
				lOldPs=gCRam.RelPos;
				if(nTimes>HOME_STALLTIME)
				{
					nTimes=0;
					nTimes1=0;

					SL_SET(SL_TER_CWLI);
				#ifdef RL_LIMIT_SWITCH
					g_nZeroRunState=ZERO_RUN_LEFT;
				#else
					g_nZeroRunState=ZERO_RUN_SETZERO;
					MCL_SetFault(CMD_POSITION_ERR);
				#endif
					break;
				}	
				
				//到位置
				lTemp=gCRam.SetPos-gCRam.RelPos;
				if(lTemp>-HOME_ERROR&&lTemp<HOME_ERROR)nTimes1++;
				else nTimes1=0;
				if(nTimes1>=HOME_TIMECNT) 
				{	
					nTimes=0;
					nTimes1=0;
					SL_SET(SL_TER_CWLI);
				#ifdef HOME_ZERO
					g_nZeroRunState=ZERO_RUN_LEFT;
				#else
					g_nZeroRunState=ZERO_RUN_SETZERO;
				#endif						
					break;
				}		
			}
			else 
			{
				nTimes=0;
				nTimes1=0;
				g_nZeroRunState=ZERO_RUN_SETZERO;
			}			  
			break;
	
		case ZERO_RUN_LEFT:			//反向寻零
			if(!SL_CHK(SL_TER_CCWLI))
			{
				gCRam.SetPos=lPs-gPLCCtl.sop;	//设置目标位置
			}
			else
			{
				#ifdef HOME_ZERO
				gCRam.SetPos=0;
				#endif
				g_nZeroRunState=ZERO_RUN_SETZERO;
			}			   
		
			if(!gCRam.FindZ)
			{ 					
			//堵转
				lTemp=lOldPs-gCRam.RelPos;
				if(lTemp>-HOME_STALLCNT&&lTemp<HOME_STALLCNT) nTimes++;
				else nTimes=0;
				lOldPs=gCRam.RelPos;
				if(nTimes>HOME_STALLTIME)
				{
					nTimes=0;
					nTimes1=0;
					SL_SET(SL_TER_CCWLI);
					
				#ifdef RL_LIMIT_SWITCH
					g_nZeroRunState=ZERO_RUN_RIGHT;
				#else
					g_nZeroRunState=ZERO_RUN_SETZERO;
					MCL_SetFault(CMD_POSITION_ERR);
				#endif
					break;
				}
				
			//到位置
				lTemp=gCRam.SetPos-gCRam.RelPos;
				if(lTemp>-HOME_ERROR&&lTemp<HOME_ERROR)nTimes1++;
				else nTimes1=0;
				if(nTimes1>=HOME_TIMECNT)
				{
					nTimes=0;
					nTimes1=0;
					SL_SET(SL_TER_CCWLI);
				#ifdef HOME_ZERO
					g_nZeroRunState=ZERO_RUN_RIGHT;
				#else
					g_nZeroRunState=ZERO_RUN_SETZERO;
				#endif	
					break;	
				}
			}		
			else 
			{
				nTimes=0;
				nTimes1=0;
				g_nZeroRunState=ZERO_RUN_SETZERO;			
			}		
			break;
	
		case ZERO_RUN_SETZERO:
			#ifdef HOME_ZERO
			if(gCRam.FindZ)  //回零成功
			{
				g_nZeroRunState=ZERO_RUN_END;
			}
			else  //回零失败,等到回到起始位置
			{				
				//堵转
				lTemp=lOldPs-gCRam.RelPos;
				if(lTemp>-HOME_STALLCNT&&lTemp<HOME_STALLCNT) nTimes++;
				else nTimes=0;
				lOldPs=gCRam.RelPos;
				if(nTimes>HOME_STALLTIME)
				{
					nTimes=0;
					nTimes1=0;
					g_nZeroRunState=ZERO_RUN_END;
					break;
				}
				
				//到位置
				lTemp=gCRam.SetPos-gCRam.RelPos;
				if(lTemp>-HOME_ERROR&&lTemp<HOME_ERROR)nTimes1++;
				else nTimes1=0;
				if(nTimes1>=HOME_TIMECNT)
				{
					nTimes=0;
					nTimes1=0;
					g_nZeroRunState=ZERO_RUN_END;
					break;	
				}
			}		
			#else
			g_nZeroRunState=ZERO_RUN_END;			
			#endif
			break;	
		
		case ZERO_RUN_END:	
			if(gCRam.FindZ)  //回零成功
			{
				lPs=0;	
				gPLCCtl.doDataOut[LOCK_OUT]=0;  //恢复互锁信号
				SL_SET(PLC_MIDDLE_RDY);
			}
			else  //回零失败
			{
				gPLCCtl.doDataOut[LOCK_OUT]=1;  //互锁信号
				MCL_SetFault(HOMING_ERR); 
				SL_CLR(PLC_MIDDLE_RDY);
			}
			//回复现场	
			gCRam.MaxSpeed=(INT32S)gPLCCtl.ssp*gPLCCtl.enc/60;	
			gCRam.SetSpeed=0;	
			gCRam.ISet=0;
			gCRam.SetPwm=0;
			ChangeModScs(nMod,nScs);
			g_nMainState =MAIN_STATE_RUN;
			gCRam.bPwmClose = 0;
				break;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
		default:	
			break;
	}
}	

void TIM1ms_ISR(void)
{
	short nclk;
	unsigned int  value;
	long lTemp,lTemp1,lTemp2;
	float fTemp,fTemp0;//,fTemp1;
	static unsigned int wTs=0;
	static	unsigned int wReadEnc=0;
	int nSetPwm;
	INT16S LimitOutputPWM;
	static long lPwmRamp=0;
	static INT16U TmsCntPre=0;

		g_wTms++;

	#if (ENCODER_TYPE == ENCODER_CLKDIR)
		value=gCRam.EncoderCnt;
	#else	
		value=(unsigned int)TIM_GetCounter(); //读取正交解码寄存器
	#endif

	  if (gPLCCtl.SwapEncoderDir == 0)  	
    {// encoder timer down-counting
			nclk=(short)(wReadEnc - value);    }
    else  
    {//encoder timer up-counting
			nclk=(short)(value - wReadEnc);
    }
		wReadEnc = value;
		
		gCRam.RelPos += nclk;   //实时位置值

		gCRam.SpeedAvgAdd += (nclk-gCRam.SpeedAvg);
		gCRam.SpeedAvg = (gCRam.SpeedAvgAdd>>4);
		
		if (nclk>=0)  //正反转标志		
			setDataBit(gCRam.SI,RL);		
		else		
			clrDataBit(gCRam.SI,RL);
		
		if(gCRam.bPwmClose)
		{
			g_lPEK2=g_lPEK1=0;
			g_lVEK1=g_lVEK2=g_lVEK3=0;	
			g_nIEK=0;g_nIEK1=0;
			g_nIntegar=0;			
			gCRam.SetSpeed=0;
			gCRam.OldSetSpeed=0;
			return;
		}
		if(gPLCCtl.ctrl_mode == CTRL_M)
	  {
			if(!(g_wTms&0x03))
			{
				g_lPEK1=gCRam.SetPos-gCRam.RelPos;		
				gCRam.OldPos=gCRam.SetPos;					
				if((g_lPEK1<gCRam.PosOffset)&&(g_lPEK1>-gCRam.PosOffset))	
				{	
					if(g_wTms-TmsCntPre>500)
						setDataBit(gCRam.SI,POS_OK);					
				}
				else if((g_lPEK1>=(gCRam.PosOffset+4))||(g_lPEK1<=-(gCRam.PosOffset+4)))	
				{			
					clrDataBit(gCRam.SI,POS_OK);
					TmsCntPre = g_wTms;
				}
				else
				{
					TmsCntPre = g_wTms;
				}
				
				fTemp=g_lPEK1;
				fTemp0=gPLCCtl.Mp*fTemp;

//				if(gPLCCtl.Md==0)fTemp1=0;
//				else fTemp1=gPLCCtl.Md*(fTemp-g_lPEK2);				
//				fTemp=fTemp0+fTemp1;
				
				lTemp1=g_lPEK1*gPLCCtl.Mi;
				if(lTemp1>-64 && lTemp1<64) lTemp1=0;
				else lTemp1=lTemp1>>6;
				lTemp1=lTemp1+g_lI_K_P;
				if(lTemp1>32767)g_lI_K_P=32767;
				else if(lTemp1<-32767)g_lI_K_P=-32767;
				else g_lI_K_P=lTemp1;

				fTemp=fTemp0+g_lI_K_P;
				lTemp=(long)(fTemp/1024);			
			
				if(lTemp>gCRam.MaxSpeed)lTemp=gCRam.MaxSpeed;
				else if(lTemp<-gCRam.MaxSpeed)lTemp=-gCRam.MaxSpeed;		
				gCRam.SetSpeed=lTemp;

				g_lPEK2=g_lPEK1;
			}		
			
			//位置环内嵌速度环
			lTemp2=gCRam.SetSpeed;
			lTemp1=(long)gCRam.SpeedAvg*1000;	
			lTemp=myvpid(lTemp2,lTemp1);			
			
	  	if(gPLCCtl.pmod==1)
			{
				lTemp+=gCRam.PwmValue;
			}
			else
			{
				gCRam.bMoreI--;  			
				if(gCRam.bMoreI<=1)
				{
					lTemp=gCRam.PwmValue+lTemp;
					gCRam.bMoreI=1;
				}
				else if(gCRam.bMoreI>20)
				lTemp=gCRam.PwmValue;
				else
					lTemp=gCRam.PwmValue+lTemp/gCRam.bMoreI;  				
			}
			if(lTemp>MAX_PWM) lTemp=MAX_PWM;
			else if(lTemp<-MAX_PWM)lTemp=-MAX_PWM;
			gCRam.PwmValue = lTemp;	
			
			if(getDataBit(gCRam.SI,POS_OK))
			{
				gCRam.PwmValue = 0;
			}
		}
		else if(gPLCCtl.ctrl_mode == CTRL_V)
		{					
			lTemp2=gCRam.SetSpeed;				
			lTemp1=(long)gCRam.SpeedAvg*1000;			
  			
			lTemp=myvpid(lTemp2,lTemp1);
			if(gPLCCtl.pmod==1)
			{
				lTemp+=gCRam.PwmValue;
			}
			else
			{
				gCRam.bMoreI--;  			
				if(gCRam.bMoreI<=1)
				{
					lTemp=gCRam.PwmValue+lTemp;
					gCRam.bMoreI=1;
				}
				else if(gCRam.bMoreI>20)
				lTemp=gCRam.PwmValue;
				else
					lTemp=gCRam.PwmValue+lTemp/gCRam.bMoreI;  				
			}
 			if(lTemp>MAX_PWM) lTemp=MAX_PWM;
 			else if(lTemp<-MAX_PWM)lTemp=-MAX_PWM;
 			gCRam.PwmValue = lTemp;
		
		}
		else if(gPLCCtl.ctrl_mode == CTRL_A)//
		{				  		
				nSetPwm = gCRam.SetPwm;
				
				if(gCRam.PwmValue<nSetPwm)
				{
					if(nSetPwm>0)
						lPwmRamp+=gCRam.PwmAcc;	
					else
						lPwmRamp+=gCRam.PwmDec;	
					lTemp=lPwmRamp/1000;
					lPwmRamp=lPwmRamp%1000;		  			
//					if(gCRam.PwmValue>nSetPwm)gCRam.PwmValue=nSetPwm;
				}
				else if(gCRam.PwmValue>nSetPwm)
				{
					if(nSetPwm>=0)
						lPwmRamp+=gCRam.PwmDec;	
					else
						lPwmRamp+=gCRam.PwmAcc;	
					lTemp=-lPwmRamp/1000;
					lPwmRamp=lPwmRamp%1000;		  			
//					if(gCRam.PwmValue<nSetPwm)gCRam.PwmValue=nSetPwm;		  			
				}	  
				else
				{
					lTemp=0;
				}	
			
				gCRam.bMoreI--;  			
				if(gCRam.bMoreI<=1)
				{
					lTemp=gCRam.PwmValue+lTemp;
					gCRam.bMoreI=1;
				}
				else if(gCRam.bMoreI>20)
				lTemp=gCRam.PwmValue;
				else
					lTemp=gCRam.PwmValue+lTemp/gCRam.bMoreI;  	
				
				LimitOutputPWM = MAX_PWM*gPLCCtl.HighSpeedRatio>>15;
				if(lTemp>LimitOutputPWM) lTemp=LimitOutputPWM;
				else if(lTemp<-LimitOutputPWM) lTemp=-LimitOutputPWM;
				gCRam.PwmValue = lTemp;				
		}		
  wTs++;
 	if(wTs>1000)  //秒计数器
	{
		g_wTs+=1;	
		wTs=0;
	}
	
}

//ADC 转换结束中断服务函数
void ControllerISR(void)
{
	INT16S nIpc;
	INT32S nPwmValue; 
	INT32S nISet=0;
	INT16S LimitCurrent,LimitCurrent_Rvs;
	static INT8U bOverTmp=0;
	static INT16U bOverVolt=0;

	/* feedback process */
	FeedbackProcess();
	nIpc=gCurrentSample.U;
	
		//记录回零位置
		gCRam.HomSw_sta = READ_HOME();
		if((!gCRam.FindZ)  && (g_nZeroRunState!=ZERO_RUN_INIT))
		{
			if(gPLCCtl.HomeMode == 1)  //点域回中
			{
				if((gCRam.HomSw_sta!=gCRam.HomSw_sta_old) && (gCRam.HomSw_sta==1))  //上升沿
				{
					if(gPLCCtl.TrigType==1)  //高电平有效时，上升沿为起始
					{
						gCRam.StartPos = gCRam.RelPos;
					}
					else //低电平有效时，上升沿为结束
					{
						gCRam.EndPos = gCRam.RelPos;
						
						gCRam.DetaPos = gCRam.EndPos-gCRam.StartPos;
						gCRam.SetPos=gCRam.RelPos= gCRam.DetaPos/2+gCRam.ZeroOffset;  //记录位置
						g_nZeroRunState=ZERO_RUN_SETZERO;		
						gCRam.FindZ=1;			
					}
				}
				else if((gCRam.HomSw_sta!=gCRam.HomSw_sta_old) && (gCRam.HomSw_sta==0))  //下降沿
				{
					if(gPLCCtl.TrigType==1) //高电平有效时，下降沿为结束
					{
						gCRam.EndPos = gCRam.RelPos;
						
						gCRam.DetaPos = gCRam.EndPos-gCRam.StartPos;
						gCRam.SetPos=gCRam.RelPos= gCRam.DetaPos/2+gCRam.ZeroOffset;  //记录位置
						g_nZeroRunState=ZERO_RUN_SETZERO;		
						gCRam.FindZ=1;			
					}
					else //低电平有效时，上升沿为起始
					{
						gCRam.StartPos = gCRam.RelPos;
					}
				}	
			}	
			else //面域回中
			{
			#ifdef RL_LIMIT_SWITCH
				if((gCRam.HomSw_sta!=gCRam.HomSw_sta_old)&&(gCRam.HomSw_sta==0))
				{
					gCRam.SetPos=gCRam.RelPos=gCRam.HomeOffset;
					g_nZeroRunState=ZERO_RUN_SETZERO;		
					gCRam.FindZ=1;		
				}
				if((gCRam.HomSw_sta!=gCRam.HomSw_sta_old)&&(gCRam.HomSw_sta==1))
				{
					//翻转运行方向
					if(g_nZeroRunState==ZERO_RUN_RIGHT)
						g_nZeroRunState=ZERO_RUN_LEFT;			
					else if(g_nZeroRunState==ZERO_RUN_LEFT)
						g_nZeroRunState=ZERO_RUN_RIGHT;					
				}
			#else
				if(gCRam.HomSw_sta!=gCRam.HomSw_sta_old)
				{
					if(gCRam.HomeStep == 0) 
					{
						gCRam.StartPos = gCRam.RelPos;
						gCRam.HomeStep = 1;
						gCRam.HomSw_Presta = gCRam.HomSw_sta;	

						//翻转运行方向
						if(g_nZeroRunState==ZERO_RUN_RIGHT)
							g_nZeroRunState=ZERO_RUN_LEFT;			
						else if(g_nZeroRunState==ZERO_RUN_LEFT)
							g_nZeroRunState=ZERO_RUN_RIGHT;							
					}
					else if(gCRam.HomeStep == 1) 
					{
						if(gCRam.HomSw_sta!=gCRam.HomSw_Presta) //两次触发沿不同
						{
							gCRam.EndPos = gCRam.RelPos;
							gCRam.HomeStep = 2;	
						}
					}					
								
					if(gCRam.HomeStep == 2) 
					{
						gCRam.DetaPos = gCRam.EndPos-gCRam.StartPos;
						gCRam.SetPos=gCRam.RelPos= gCRam.DetaPos/2+gCRam.ZeroOffset;  //记录位置
						g_nZeroRunState=ZERO_RUN_SETZERO;		
						gCRam.FindZ=1;					
					}			
				}		
			#endif
			}
	
		}

		gCRam.HomSw_sta_old = gCRam.HomSw_sta;  //update state		
		
		/************************/	
	if(g_nMainState!=MAIN_STATE_INIT)
	{
		if(gCRam.bPwmClose)
		{  
			if(gPLCCtl.ErrCode == CMDPOS_ERR)	//油门断线紧急制动
				gCRam.PwmValue=0;	
			
			if(gCRam.PwmValue>0) 
				gCRam.PwmValue--;
			else if(gCRam.PwmValue<0) 
				gCRam.PwmValue++;		
		}
		else
		{		
			//转矩模式
			if(gPLCCtl.ctrl_mode == CTRL_I)
			{	 				  		
				if(gCRam.ISet==0) gCRam.PwmValue=0;
				else
				{
					nISet= (INT32S)(gCRam.ISet - nIpc);
						nPwmValue=gCRam.PwmValue;
						if(nPwmValue>=MAX_PWM)
						{
							if(nISet<0) nPwmValue=(long)(gPLCCtl.Ip>>3)*(nISet-g_nIEK)+(((long)(gPLCCtl.Ii>>3)*nISet)>>3)+(long)gPLCCtl.Id*(g_nIEK1+nISet-g_nIEK-g_nIEK);
							else nPwmValue=(gPLCCtl.Ip>>3)*(nISet-g_nIEK)+gPLCCtl.Id*(g_nIEK1+nISet-g_nIEK-g_nIEK);
						}
						else if(nPwmValue<=-MAX_PWM)
						{
							if(nISet>0) nPwmValue=(long)(gPLCCtl.Ip>>3)*(nISet-g_nIEK)+(((long)(gPLCCtl.Ii>>3)*nISet)>>3)+(long)gPLCCtl.Id*(g_nIEK1+nISet-g_nIEK-g_nIEK);
							else nPwmValue=(gPLCCtl.Ip>>3)*(nISet-g_nIEK)+gPLCCtl.Id*(g_nIEK1+nISet-g_nIEK-g_nIEK);
						}
						else nPwmValue=(long)(gPLCCtl.Ip>>3)*(nISet-g_nIEK)+(((long)(gPLCCtl.Ii>>3)*nISet)>>3)+(long)gPLCCtl.Id*(g_nIEK1+nISet-g_nIEK-g_nIEK);
						
						if(nPwmValue>=1024||nPwmValue<0)nPwmValue=nPwmValue>>10;
						else if(nPwmValue>0)nPwmValue=1;
						g_nIEK1= g_nIEK;		
						g_nIEK = nISet;
						
						nPwmValue += gCRam.PwmValue;
						if(nPwmValue>MAX_PWM) nPwmValue=MAX_PWM;
						else if(nPwmValue<-MAX_PWM)nPwmValue=-MAX_PWM;
						gCRam.PwmValue = nPwmValue;
				}										
			}
		}
		
//		nIpc=gCurrentSample.U;
//		if(gPLCCtl.pmod == 1) //过流保护模式：报错停机
//		{					
//		}
//		else 	//限流模式：
		{	
			if(gPLCCtl.ErrCode==BOARD_OT_ALM)
				bOverTmp= 1;		
			else
				bOverTmp=0;		
			
			//如果过温，削减功率运行
			if(bOverTmp)	// || g_bVoltLimit)
			{
				LimitCurrent = gCRam.OverloadAd>>1;
				LimitCurrent_Rvs = gCRam.OverloadAd_M>>1;						
			}
			else
			{
				LimitCurrent = gCRam.OverloadAd;
				LimitCurrent_Rvs = gCRam.OverloadAd_M;
			}
			
			if(gCurrentSample.VBus>OVERVOLTAGE_THRESHOLD) //电压钳制
			{
				SL_SET(PLC_MAX_VOLTAGE_ERR);	//过压信号
				bOverVolt = 0;		
	
				if(gCRam.SpeedAvg>0)
				{
					LimitCurrent = gCRam.OverloadAd>>1;	//给定力矩
					LimitCurrent_Rvs = gCRam.OverloadAd>>1;
				}				
				else if(gCRam.SpeedAvg<0)
				{					
					LimitCurrent = gCRam.OverloadAd_M>>1;	//给定力矩
					LimitCurrent_Rvs = gCRam.OverloadAd_M>>1;
				}
				else
				{
					LimitCurrent = 0;
					LimitCurrent_Rvs = 0;				
				}
			}
			else 
			{	
				if(bOverVolt>100)
				{
					SL_CLR(PLC_MAX_VOLTAGE_ERR);	//清过压信号	
				}
				else
					bOverVolt++;
			}
			
			if(nIpc>LimitCurrent || nIpc<LimitCurrent_Rvs )
			{					
				SL_SET(SL_TER_CURRENT_CUT);	//过流信号			
				if(nIpc>LimitCurrent)	nISet=(INT32S)(LimitCurrent-nIpc);//
				else if(nIpc<LimitCurrent_Rvs)	nISet=(INT32S)(LimitCurrent_Rvs-nIpc);//
				else nISet=0;					
				
				nPwmValue=nISet*(gPLCCtl.Ip>>2);				
				nPwmValue=nPwmValue>>8;
				
				g_nIEK1= g_nIEK;
				g_nIEK = nISet;
				
				nPwmValue += gCRam.PwmValue;			
			}
			else
			{
				nPwmValue = gCRam.PwmValue;
				SL_CLR(SL_TER_CURRENT_CUT);	
			}	
				
			//Umax = Imax*R + f(V);  backEMF = f(V)
			if((gPara.AcMotorSpeed<0)&&(gPara.AcMotorSpeedF<0))
				nISet = -gPara.AcMotorSpeed;
			else if((gPara.AcMotorSpeed>0)&&(gPara.AcMotorSpeedF>0))
				nISet = gPara.AcMotorSpeed;	
			else
				nISet = 0;
			
			nISet = nISet<<10;
			gPLCCtl.MaxPWMOut = gPLCCtl.IR_Offset + nISet/gPLCCtl.ssp;	  
			gPLCCtl.MaxPWMOut = (gPLCCtl.MaxPWMOut*MAX_PWM)>>10;
			if(gPLCCtl.MaxPWMOut>MAX_PWM) gPLCCtl.MaxPWMOut = MAX_PWM;
			if(nPwmValue>gPLCCtl.MaxPWMOut) nPwmValue=gPLCCtl.MaxPWMOut;
			else if(nPwmValue<-gPLCCtl.MaxPWMOut)nPwmValue=-gPLCCtl.MaxPWMOut;

			gCRam.PwmValue = nPwmValue;		
		}
		
		gCRam.PwmOut = gCRam.PwmValue;
		PwmUpdate(gCRam.PwmOut);	
	}		
}

/*******************************************************************************
* Function Name  : MCL_ChkPowerStage
* Description    : This function check for power stage working conditions
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MCL_ChkPowerStatue(void)
{
	static unsigned short w5V_A_Counter = 0;
	static unsigned	short w5V_B_Counter = 0;
	static unsigned short wOV_Counter = 0;
	static unsigned short wLV_Counter = 0;
	static unsigned short wCmdPos_Counter = 0;
//	INT16S nTemp;	
#if (CTLBOARD_TYPE == _1220_V103)	
    /*  功率板严重过热保护  */ 
    if (gPLCCtl.TmpPower >= BOARD_OVERTMP_THRESHOLD)   
    {
				MCL_SetFault(BOARD_OT_ERR);
    } 
		/*  功率板轻度过温报警  */ 
    else if (gPLCCtl.TmpPower >= BOARDTMP_ALM_THRESHOLD)   
    {
				MCL_SetFault(BOARD_OT_ALM);
    } 
		else if (gPLCCtl.TmpPower <= BOARD_LOWTMP_THRESHOLD)   
    {
				MCL_SetFault(BOARD_LT_ALM);
    } 
	//	else MCL_ClearFault(BOARD_OT_ERR);
#endif		
				
		/*  KSI电压检测  */
		if (MCL_Chk_BusVolt() == OVER_VOLT) 
    {
			wOV_Counter++;
			if(wOV_Counter>12000) //12s
			{
				MCL_SetFault(OVERVOLT_ERR);
				gPLCCtl.doDataOut[RELAY]=0;
			}
    }		    	
		else if (MCL_Chk_BusVolt() == UNDER_VOLT) 
    {
			wLV_Counter++;
			if(wLV_Counter>12000) //12s
			{
				MCL_SetFault(UNDERVOLT_ERR);
			}
    }
		else
		{
			wOV_Counter = 0;
			wLV_Counter = 0;
		}

#if ((CTLBOARD_TYPE == _1220_V103)||(CTLBOARD_TYPE == _1220_G4))
		/*  5V电源A低压检测  */	
		if (gCurrentSample.V5out < POWER5V_THRESHOLD)	
		{
			w5V_A_Counter++;
			if(w5V_A_Counter>1000) //1s
				MCL_SetFault(POWER5VA_ERR);
		}
		else	w5V_A_Counter=0;

		/*  5V电源B低压检测  */	
		if (gCurrentSample.V5out < POWER5V_THRESHOLD)	
		{
			w5V_B_Counter++;
			if(w5V_B_Counter>1000) //1s
				MCL_SetFault(POWER5VA_ERR);
		}
		else	w5V_B_Counter=0;
		
		/*  检测继电器控制反馈，异常则关闭PWM  */
		#if(CTLBOARD_TYPE == _1220_V20)
			if(gPLCCtl.doDataOut[RELAY]==1)  
		#else
		if(1)//
		#endif  // 
		{
			if(READ_RELAY() == 0) //继电器关闭 
			{
				if(netTimer[Timer_RelayCheck].bIsStart==false)
					SetNetTimer(Timer_RelayCheck,50);
				
				if(netTimer[Timer_RelayCheck].bIsOvertime==true)
				{//超时则关闭Pwm输出
					MCL_SetFault(RELAY_DRIVE_ERR);
				}
			}
			else //继电器打开成功
			{
				SL_SET(SL_TER_RDY);
				netTimer[Timer_RelayCheck].bIsStart=false;
			}
		}
#endif

#if (CTLBOARD_TYPE == _1220_V103)		
		/*  转弯限速逻辑判断  */		
		if(SL_CHK(PLC_MIDDLE_RDY)) //回中完成
		{
			nTemp = (INT16S)gPara.SteerAngle;
			if(nTemp<0) nTemp = -nTemp;
			nTemp = nTemp/10;  
			if(nTemp>=gPLCCtl.AngleLimit1)  //第一档限速角度
			{
				gPLCCtl.doDataOut[SOUT1]=1;
			}
			else 
			{
				gPLCCtl.doDataOut[SOUT1]=0;
			}
			
			if(nTemp>=gPLCCtl.AngleLimit2)  //第二档限速角度
			{
				gPLCCtl.doDataOut[SOUT2]=1;	
			}
			else 
			{
				gPLCCtl.doDataOut[SOUT2]=0;
			}
		}
#endif //(CTLBOARD_TYPE == _1220_V103)
		
	/*  角度传感器检测  */	
	if(gPara.ThrottleType==0)
	{
		if ((gPara.ThrottleWipVoltage <= CMDPOSVOLTMIN) || (gPara.ThrottleWipVoltage >= CMDPOSVOLTMAX))   		
		{
				wCmdPos_Counter++;
				if(wCmdPos_Counter>100) //0.2s
					MCL_SetFault(CMDPOS_ERR);

		}
		else	wCmdPos_Counter=0;
	}
	
	//
	//母线电容电压异常检测
	//
	if (gCurrentSample.VBus < RELAYON_THRESHOLD)   
	{
		if(netTimer[Timer_VBusAbnormalCheck].bIsStart==false)
		{
			SetNetTimer(Timer_VBusAbnormalCheck,3000);
		}
		if(netTimer[Timer_VBusAbnormalCheck].bIsOvertime==true)
		{
			KillNetTimer(Timer_VBusAbnormalCheck);
			MCL_SetFault(BUS_CAP_ERR);	
//			gPLCCtl.doDataOut[RELAY]=0;
	//				SL_CLR(PLC_VBUS_RDY);
		}		
	}	
	else
	{
		SL_SET(SL_TER_RDY);
		KillNetTimer(Timer_VBusAbnormalCheck);
	}		

}

/*******************************************************************************
* Function Name  : MCL_SetFault() 
* Description    : This function manage faults occurences
* Input          : Fault type
* Output         : None
* Return         : None
*******************************************************************************/
void MCL_SetFault(u16 hFault_type)
{
	if(hFault_type<=40)	//严重错误
	{
//		gCRam.PwmValue=0;
		gCRam.bPwmClose=1;
		gPLCCtl.doDataOut[FAULT_OUT]=1;
		gPLCCtl.doDataOut[LOCK_OUT]=1;  //互锁信号
	 /* Main PWM Output DISABLE */
//		TIM_CtrlPWMOutputs(TIM1, DISABLE);
		if(hFault_type != CMDPOS_ERR)	//油门断线紧急制动
			TIM1->CCER &= ~0x0055; 	//关闭四路PWM输出
		clrDataBit(gCRam.SI,EN_PWM);
	}
	else 	//一般告警
	{

	}
	
	if(gPLCCtl.ErrCode == 0)  //仅保留第一次报警号
	{
		gPLCCtl.ErrCode = hFault_type;	
	  gPLCCtl.icanSteer.ucErrorCode=gPLCCtl.ErrCode;
	}
}

/*******************************************************************************
* Function Name  : MCL_ClearFault() 
* Description    : This function check if the fault source is over. In case it 
*                  is, it clears the related flag and return true. Otherwise it 
*                  returns FALSE
* Input          : Fault type
* Output         : None
* Return         : None
*******************************************************************************/
void MCL_ClearFault(u16 hFault_type)
{     
	if(gPLCCtl.ErrCode == hFault_type)
	{
		gPLCCtl.ErrCode = 0;
		
		gPLCCtl.doDataOut[FAULT_OUT]=0;
		gPLCCtl.doDataOut[LOCK_OUT]=0;  //互锁信号
	 /* Main PWM Output DISABLE */
//		TIM_CtrlPWMOutputs(TIM1, ENABLE);
		TIM1->CCER |= 0x0055; 	//打开四路PWM输出
		setDataBit(gCRam.SI,EN_PWM);
	}
}


/*******************************************************************************
* Function Name  : MCL_Chk_BusVolt 
* Description    : Check for Bus Over Voltage
* Input          : None
* Output         : Boolean
* Return         : None
*******************************************************************************/
BusV_t MCL_Chk_BusVolt(void)
{
  BusV_t baux;
  if (gCurrentSample.KsiVBus > OVERVOLTAGE_THRESHOLD)    
  {
    baux = OVER_VOLT;
  }
  else if (gCurrentSample.KsiVBus < UNDERVOLTAGE_THRESHOLD)    
  {
    baux = UNDER_VOLT;
  }
  else 
  {
    baux = NO_FAULT; 
  }
  return ((BusV_t)baux);
}



void  GetCmdPercent(void )
{
	float Command_now; 
//	float fTemp;
	INT16U CmdMin,CmdMinRvs;

	//模拟信号平滑滤波
	gCRam.CmdRaw = gCurrentSample.CmdVal1;	//	
	gCRam.CmdSum += gCRam.CmdRaw-gCRam.CmdAvg;
	gCRam.CmdAvg = gCRam.CmdSum>>4; //	
		
	//Command_now=gCommand.Command1*33/4096/ANALOG_ADC_CONV_RATIO;
	Command_now=(float)(gCRam.CmdAvg*330+5)/2048;	
	gCRam.WiperVoltage = Command_now;
	
	if(gPLCCtl.ThrottleType==0)//油门类型1：0V~2.5V~5V
	{
		CmdMin = gPLCCtl.Command_centre+gCRam.nMav;
		CmdMinRvs = gPLCCtl.Command_centre-gCRam.nMav;	
	
		if(gPLCCtl.Command_right > gPLCCtl.Command_centre)
		{
			if(Command_now>CmdMin)//gPLCCtl.Command_centre) 
			{
				Command_now =Command_now-CmdMin;
				gCRam.CmdPercent =Command_now*100/(gPLCCtl.Command_right-CmdMin);
				gCRam.CmdDirection= 1;	
			}
			else if(Command_now<CmdMinRvs)
			{
				Command_now = CmdMinRvs-Command_now;
				gCRam.CmdPercent =Command_now*100/(CmdMinRvs-gPLCCtl.Command_left);
				gCRam.CmdDirection= -1;
			}
			else
			{
				gCRam.CmdPercent = 0;
				gCRam.CmdDirection= 0;			
			}
		}
		else if(gPLCCtl.Command_left > gPLCCtl.Command_centre)
		{
			if(Command_now>CmdMin) 
			{
				Command_now =Command_now-CmdMin;
				gCRam.CmdPercent =Command_now*100/(gPLCCtl.Command_left-CmdMin);
				gCRam.CmdDirection= -1;
			}
			else if(Command_now<CmdMinRvs)
			{
				Command_now = CmdMinRvs-Command_now;
				gCRam.CmdPercent =Command_now*100/(CmdMinRvs-gPLCCtl.Command_right);	
				gCRam.CmdDirection= 1;
			}
			else
			{
				gCRam.CmdPercent = 0;
				gCRam.CmdDirection= 0;			
			}
		}
		else
		{
			gCRam.CmdPercent = 0;
			gCRam.CmdDirection= 0;
			MCL_SetFault(CMD_POSITION_ERR);
		}
		#if (USER_TYPE == USER_MOVE_XIDICHE) //svoff 延时处理
		if(gPLCCtl.diDataIn.ucIn[SWI1_R]==0)  //使能信号无效
		{
			gCRam.CmdPercent = 0;
			gCRam.CmdDirection= 0;
		}
	#endif
	}
	else if(gPLCCtl.ThrottleType==1)//油门类型2：0V~5V + DIR
	{
			if(Command_now>gPLCCtl.Command_left)
			{
				Command_now = Command_now-gPLCCtl.Command_left;
				gCRam.CmdPercent = Command_now*100/(gPLCCtl.Command_right-gPLCCtl.Command_left);
			}
			else 
			{
				gCRam.CmdPercent = 0;
			}
		#ifdef SINGLE_DIR_SW
			//单方向开关信号：0：正向  1：反向
			if(gPLCCtl.diDataIn.ucIn[SWI5_R]==1) //反向
			{
				gCRam.CmdDirection= -1;	
				gPLCCtl.HighSpeedRatio = gPara.LowSpeedRatio;
			}
			else
			{
				gCRam.CmdDirection= 1;					
//				if(gPLCCtl.diDataIn.ucIn[SWI5_R]==1)  //slow mode select 
//					gPLCCtl.HighSpeedRatio = gPara.LowSpeedRatio;
//				else
					gPLCCtl.HighSpeedRatio = gPara.HighSpeedRatio;			
			}				
		#else
			//双方向开关信号：正向
			if((gPLCCtl.diDataIn.ucIn[SWI4_R]==1)&&(gPLCCtl.diDataIn.ucIn[SWI5_R]==0))
			{
				gCRam.CmdDirection= 1;	
				
//				if(gPLCCtl.diDataIn.ucIn[SWI5_R]==1)  //slow mode select 
//					gPLCCtl.HighSpeedRatio = gPara.LowSpeedRatio;
//				else
					gPLCCtl.HighSpeedRatio = gPara.HighSpeedRatio;
			}
			else if((gPLCCtl.diDataIn.ucIn[SWI4_R]==0)&&(gPLCCtl.diDataIn.ucIn[SWI5_R]==1)) //反向
			{
				gCRam.CmdDirection= -1;	
				gPLCCtl.HighSpeedRatio = gPara.LowSpeedRatio;
			}
			else
			{
				gCRam.CmdPercent = 0;
				gCRam.CmdDirection= 0;				
			}			
		#endif
				
		#if (USER_TYPE == USER_MOVE_XIDICHE) //svoff 延时处理			
			if(gPLCCtl.diDataIn.ucIn[SWI1_R]==0)  //使能信号无效
			{
				gCRam.CmdPercent = 0;
				gCRam.CmdDirection= 0;
			}
		#endif
	}		
	else   //未知油门类型
	{
		gCRam.CmdPercent = 0;
		gCRam.CmdDirection= 0;
	}
	
	if(gCRam.CmdPercent>100)  gCRam.CmdPercent = 100;
}

INT32S  _GetSetPosition(void )
{
	INT32S ret=0;
	float X,K,X0,Y0;
	float fTemp;

	X = gCRam.CmdPercent;
	
  if(X < gPLCCtl.PL) 
	{
		K=0; 	//0
		X0=0;
		Y0=0;
	}
	else 	if(X < gPLCCtl.P2) 
	{
		K=(gPLCCtl.P2_deg-gPLCCtl.PL_deg)*10/(gPLCCtl.P2-gPLCCtl.PL); 	//
		X0=gPLCCtl.PL;
		Y0=gPLCCtl.PL_deg;
	}
	else 	if(X < gPLCCtl.P3) 
	{
		K=(gPLCCtl.P3_deg-gPLCCtl.P2_deg)*10/(gPLCCtl.P3-gPLCCtl.P2); 	//
		X0=gPLCCtl.P2;
		Y0=gPLCCtl.P2_deg;		
	}
	else 	if(X < gPLCCtl.PH) 
	{
		K=(gPLCCtl.PH_deg-gPLCCtl.P3_deg)*10/(gPLCCtl.PH-gPLCCtl.P3); 	//
		X0=gPLCCtl.P3;
		Y0=gPLCCtl.P3_deg;		
	}
	else
	{
		K=0;
		X0=gPLCCtl.PH;
		Y0=gPLCCtl.PH_deg;	
	}

	if(X<X0)	 ret = 0;
	
	fTemp = K*(X - X0)/10 + Y0;  //degree

	ret =fTemp*gPLCCtl.CycleLimit/360; 		//degree to position
	gCRam.CmdDegree = fTemp;
	
	if(ret > gPLCCtl.MaxPosition) ret = gPLCCtl.MaxPosition;
	else if(ret < -gPLCCtl.MaxPosition)	ret = -gPLCCtl.MaxPosition; 
	
	return (gCRam.CmdDirection==1? ret:-ret);
}

INT32S  _GetSetDegree(INT32S SetPosition)
{
	INT32S ret=0;
	INT32S nTemp;
	
	nTemp = SetPosition%gPLCCtl.CycleLimit;
	ret = nTemp*360/gPLCCtl.CycleLimit;	
	
	return ret;
}

void Protection(void)
{	
	INT32S lTemp=0;
	INT16S nIpc;

			//电流AD值
			nIpc=gCurrentSample.U;
	
			if(nIpc>gCRam.OverIAd || nIpc<gCRam.OverIAd_M )  
			{
					gCRam.MaxCurrentCount++;
					if(gCRam.MaxCurrentCount > (FS * 6))	//6s
					{				
						MCL_SetFault(OVERCURRENT_ERR);
						gCRam.MaxCurrentCount = 0;
						return;
					}
			}
			else 
			{
				if(gCRam.MaxCurrentCount>0)	gCRam.MaxCurrentCount--;
			}	
	
			if(nIpc>=(gCRam.OverloadAd*0.9) || nIpc<=(gCRam.OverloadAd_M*0.9))
			{
				gCRam.OverCurrentCount2M++;
				if(gCRam.OverCurrentCount2M >= (FS * 120))  //120s
				{
					MCL_SetFault(OVERCURRENT_2M_ERR);
					gCRam.OverCurrentCount2M = 0;
				}
			}
			else
			{
				if(gCRam.OverCurrentCount2M>0)	gCRam.OverCurrentCount2M--;
			}
							
			if(gPLCCtl.ctrl_mode == CTRL_V)
			{//速度失控保护
					lTemp=gCRam.PwmOut;//gCRam.PwmValue;
					if(lTemp>=(gPLCCtl.MaxPWMOut*0.8))
					{
						if((gCRam.SpeedAvgAdd<(-(gCRam.n1RPM<<2)))||(gCRam.SpeedAvgAdd==0))
						{
							gCRam.SpeedDelayCount++;
							if(gCRam.SpeedDelayCount > SPEEDLOST_CNT)
							{
								MCL_SetFault(FB_OVERSPEED_ERR);
							}
						}
						else
							gCRam.SpeedDelayCount=0;
					}
					else if(lTemp<=-(gPLCCtl.MaxPWMOut*0.8))
					{
						if((gCRam.SpeedAvgAdd>((gCRam.n1RPM<<2)))||(gCRam.SpeedAvgAdd==0))
						{
							gCRam.SpeedDelayCount++;
							if(gCRam.SpeedDelayCount > SPEEDLOST_CNT)
							{
								MCL_SetFault(FB_OVERSPEED_ERR);
							}
						}
						else
							gCRam.SpeedDelayCount=0;							
					}
					else
						gCRam.SpeedDelayCount=0;
			
			}
			else if(gPLCCtl.ctrl_mode == CTRL_M)
			{  
				//速度失控保护
					lTemp=gCRam.PwmOut;//gCRam.PwmValue;
					if(lTemp>=(gPLCCtl.MaxPWMOut*0.8))
					{
//						if((gCRam.SpeedAvgAdd<(-(gCRam.n1RPM<<4)))||(gCRam.SpeedAvgAdd==0))
						if(gCRam.SpeedAvgAdd<(gCRam.n1RPM<<2))
						{
							gCRam.SpeedDelayCount++;
							if(gCRam.SpeedDelayCount > SPEEDLOST_CNT)
							{
								MCL_SetFault(FB_OVERSPEED_ERR);
							}
						}
						else
							gCRam.SpeedDelayCount=0;
					}
					else if(lTemp<=-(gPLCCtl.MaxPWMOut*0.8))
					{
//						if((gCRam.SpeedAvgAdd>((gCRam.n1RPM<<4)))||(gCRam.SpeedAvgAdd==0))
						if(gCRam.SpeedAvgAdd>(-(gCRam.n1RPM<<2)))
						{
							gCRam.SpeedDelayCount++;
							if(gCRam.SpeedDelayCount > SPEEDLOST_CNT)
							{
								MCL_SetFault(FB_OVERSPEED_ERR);
							}
						}
						else
							gCRam.SpeedDelayCount=0;						
					}
					else
					{
						if(gCRam.SpeedDelayCount>0)
						gCRam.SpeedDelayCount--;
					}
					
					//跟踪超限保护gCRam.FollowingErr_TLimit
				if(g_nMainState !=MAIN_STATE_ZEROAUTO)
				{
					if(g_lPEK1>(int)gPLCCtl.FollowingErr||g_lPEK1<-(int)gPLCCtl.FollowingErr)
					{
							gCRam.FollowingCuount++;
							if(gCRam.FollowingCuount > gCRam.FollowingErr_TLimit)  //6s
							{
									MCL_SetFault(FOLLOWING_ERR);
								 gCRam.FollowingCuount = 0;
							}
					}
					else	
					{
	//						if(gCRam.FollowingCuount>0)	gCRam.FollowingCuount--;
						gCRam.FollowingCuount= 0;
					}
				}

			}													
				
		if(gPLCCtl.ErrCode>0 && gPLCCtl.ErrCode<=40)
		{		
//			gCRam.PwmValue=0;
			gCRam.bPwmClose=1;
		}
			
}
/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
