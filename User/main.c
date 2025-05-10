#include "includes.h"
#include "Device.h"
#include "iTimer.h"
#include "logic.h"
#include "iCAN.h"
#include "CommonRam.h"
#include "MC_MotorControl_Layer.h"
/*******************************************************************************
* local function declaration 
*******************************************************************************/
//#define BOR_LEVEL   OB_BOR_LEVEL2 /*!< Supply voltage ranges from 2.40 to 2.70 V */
#define BOR_LEVEL   OB_BOR_LEVEL3 /*!< Supply voltage ranges from 2.70 to 3.60 V */

void SysInit(void)
{
	InitFeedbackDevice();	
	InitSysCtrl(); //Ӳ����ʼ��
	InitCommonRam();//��ʼ������	
	InitPara();//��ʼ�������б��е����ֵ ��Сֵ ��ʼֵ
	InitPLCCtl();
	InitFunc();
	
  ICANInitialize();
}
#ifdef HOMESW_POINT
	/*-----------------�ϵ紦����---------------------*/
	void PowerOff_Handle(void)
	{
		static uint8_t Flag_SaveOK=0;
		unsigned short HomeFlag;
		
		if(Flag_SaveOK==0 && gCurrentSample.KsiVBusRaw!=0 && gCurrentSample.KsiVBusRaw<PVDVOLTAGE_THRESHOLD)  //��Դ��ѹ����16Vʱִ��
		{
			if(gCRam.FindZ) //����OK
			{
				Flag_SaveOK = 1;		
				/**��Ӷϵ紦�����**/
				if(gCRam.RelPos<0)
					HomeFlag=1;
				else if(gCRam.RelPos>0)
					HomeFlag=0;
				else
					return;				
//				EepromWrite(EEPROM_PVD_ADDR, HomeFlag);	
				EepromQualifiedWrite(EEPROM_PVD_ADDR, HomeFlag);				
			}
		}
	}
#endif
/*******************************************************************************
* Name: main
* Description: Program entry.
* Input: 
* Output: 
*******************************************************************************/
int  main(void )
{
	if((FLASH_OB_GetBOR() & 0x0C) != BOR_LEVEL) 
	{
	 /* Unlocks the option bytes block access */
	 FLASH_OB_Unlock();

	 /* Select the desired V(BOR) Level */
	 FLASH_OB_BORConfig(BOR_LEVEL); 

	 /* Launch the option byte loading */
	 FLASH_OB_Launch();

	 /* Locks the option bytes block access */
	 FLASH_OB_Lock();
	}

#ifdef _BOOT_REMAP
	{
	uint32_t msp;

	NVIC_SetVectorTable(0x8004000,0x00);
	msp = *(__IO uint32_t*)0x8004000;
		__set_MSP(msp);
	}
#endif
	SysInit(); //ϵͳ��ʼ��	
	SetNetTimer(Timer_System,1); 
	SetNetTimer(Timer_iCAN,5);  
	
	while(1)
	{		
		while(netTimer[Timer_System].bIsOvertime)
		{		
			Sys_Prco();			//�ŷ����ƽ���
			
			ResetNetTimer(Timer_System);	//��λϵͳ��ʱ����			
		}		
		
		while(netTimer[Timer_iCAN].bIsOvertime)
		{		
			iCAN_Prco();		//iCAN����
			
			ResetNetTimer(Timer_iCAN);	//��λϵͳ��ʱ����			
		}	
	}
}

