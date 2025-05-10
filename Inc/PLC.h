/***************************Copyright (c)**************************************
**PLC.h 
**�߼�����
*******************************************************************************/
#include		"KSDsys.h"

#define PRDUCT_TYPE  2  //0ǣ�� 1 ����  2ת��

//ϵͳ����
#define		  Prc_Idle			  0
#define	    Prc_Monitor  		1	//
#define	    Prc_SysConfig  	2	//
#define			Prc_Match		    3	//
#define			Prc_FirmWare		4//

//����ָ��
#define		  Instruction_Null			0
#define		  Instruction_READ			1
#define		  Instruction_WRITE			2


/*******************************************************************************
* 1. ָʾ��
*******************************************************************************/
//����
#define PLC_PERIOD					5
#define LED_BLINK_PERIOD 		2500

//״ָ̬ʾ��
#define 	LED_YELLOW_SET						(1 << 0)
#define 	LED_YELLOW_RESET					(1 << 1)
#define 	LED_YELLOW_BLINK					(1 << 2)
#define		LED_RED_SET							(1 << 8)
#define		LED_RED_RESET						(1 << 9)
#define		LED_RED_BLINK						(1 << 10)


extern void InitPLCLogic(void);	
extern void Sys_Prco(void);
extern void iCAN_Prco(void);

void LedStateShow(INT16U ucState);
void LEDInit(void);
void LEDProcess(void);

