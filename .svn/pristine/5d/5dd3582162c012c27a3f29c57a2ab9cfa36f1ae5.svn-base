/*******************************************************************************
* Filename: AutoTune.c                                             	 		   	   *
*                                                                 		   *
* Description:											   			 		   *
* Author:                                                                   *
* Date: 														           *
* Revision:															 		   *															 		   *
*******************************************************************************/
#include "AutoTune.h"
#include "PARA.h"
#include "CommonRam.h"
#include "MC_MotorControl_Layer.h"
#include "PLCLogic.h"

#define		CENTER_VOLT_MAX		300	//中位电压最大值 3.00V
#define		CENTER_VOLT_MIN		200	//中位电压最小值 2.00V
#define		MAX_VOLT_DELTA		100	//1.00V

#define PARA_INDEX_MIN			92
#define PARA_INDEX_MAX			93
#define PARA_INDEX_CENTER		94
 AUTOTUNE AutoTune;

void AutoTuneWiper( AUTOTUNE* this)
{
	switch (this->Step)
	{
		case 0:		//Init
			this->WiperVoltSum = 0;
			this->Max=250;
			this->Mid=250;
			this->Min=250;	
			if(this->TuneCount==64)
			{
				this->Step = 1;
				this->TuneCount = 0;
			}				
			else
				this->TuneCount++;
			break;
		case 1:		//Tune middle voltage
			if(this->Enable == 1)
			{
				MCL_SetFault(AUTOTUNE_TIP);	
				SL_SET(PLC_STOP_MOVE);  //禁止电机动作
				this->WiperVolt = gPara.ThrottleWipVoltage;
				this->WiperVoltSum += this->WiperVolt;
				this->TuneCount++;
				if(this->TuneCount==64)
				{
					this->TuneCount = 0;
					this->Mid = this->WiperVoltSum>>6;
					this->Step = 2;					
				}
			}				
			break;
		case 2:		//Tune Left&Right voltage
			if(this->Enable == 1)
			{
				this->WiperVolt = gPara.ThrottleWipVoltage;

				if(this->WiperVolt < this->Min)
					this->Min = this->WiperVolt;
				if(this->WiperVolt > this->Max)
					this->Max = this->WiperVolt;
			}	
			else
			{
				this->TuneCount++;
				if(this->TuneCount > TUNETIMEOUT)
				{
					if((this->Mid>CENTER_VOLT_MIN) && (this->Mid<CENTER_VOLT_MAX))
					{
						if(((this->Max-this->Mid)>=MAX_VOLT_DELTA) && ((this->Mid-this->Min)>=MAX_VOLT_DELTA)) //Delat voltage >= 1.0V
							this->Step = 3;  //Finished
						else
							this->Step = -1;  //Abnormal	
					}
					else
						this->Step = -1;  //Abnormal
				}
			}			
			break;		
		case 3:		//Finished
//			gPara.ThrottleMinVoltage=this->Min;
//			gPara.ThrottleMaxVoltage=this->Max;	
//			gPara.ThrottleMap=this->Mid;
			SaveParaToEeprom(PARA_INDEX_MIN,this->Min);		
			SaveParaToEeprom(PARA_INDEX_MAX,this->Max);	
			SaveParaToEeprom(PARA_INDEX_CENTER,this->Mid);	
			this->Step = 4;  //Exit
			MCL_ClearFault(AUTOTUNE_TIP);	
			break;		
		case -1:		//Abnormal
			MCL_ClearFault(AUTOTUNE_TIP);	
			MCL_SetFault(AUTOTUNE_ALM);
			break;	
		default:
			break;
	}
}

