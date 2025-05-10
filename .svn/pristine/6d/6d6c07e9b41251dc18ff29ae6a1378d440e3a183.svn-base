/*******************************************************************************
* Filename: Device.h 	                                    	     		   *
*                                                                              *
* Description: The header file of Device.c.							           *
* Author:                                                                      *
* Date: 															           *
* Revision:															           *
*																	           *
*******************************************************************************/

#include "KSDsys.h"
#include "main.h"
#include "stm32g4xx_hal_conf.h"
#include <stm32g473xx.h>
#include "PLC.h"

#if(CTLBOARD_TYPE == _1220_G4 )
	#include "CtlBoard_1220_G473_IOconfig.h"
#endif

#if (CAN_BAND_RATE	==	CAN_500KBPS)
	#define	CAN_BAUDRATE 4     //16--125K; 4--500K
#elif (CAN_BAND_RATE	==	CAN_250KBPS)
	#define	CAN_BAUDRATE 8     //16--125K; 4--500K
#elif (CAN_BAND_RATE	==	CAN_125KBPS)
	#define	CAN_BAUDRATE 16     //16--125K; 4--500K
#else
	#define	CAN_BAUDRATE 4     //16--125K; 4--500K
#endif

#define FULL_VOLTAGE_ACT_TIME (400/PLC_PERIOD)   //400MS
#define	DO_PWM_CMP_LIMIT_MIN		(DO_PWM_TIM_PERIOD*5/100)
#define	DO_PWM_CMP_LIMIT_MAX		(DO_PWM_TIM_PERIOD*95/100)
/********************** POWER BOARD PROTECTIONS THRESHOLDS ********************/

#define NTC_THRESHOLD_C    (INT16U)80 //on heatsink of MB459 board
#define NTC_HYSTERIS_C     (INT16U)5   // Temperature hysteresis


/* Exported types ------------------------------------------------------------*/
/*******************************************************************************
* 1. DI
*******************************************************************************/
#define		SWI1_R					0
#define		SWI2_R					1
#define		SWI3_R					2
#define		AUTOTUNE_R				3
#define		FAULTOUT_R				4
/*******************************************************************************
* 2. DO
*******************************************************************************/
#define 	LED_Y           	0
#define 	LED_R           	1
#define 	RELAY           	2
#define 	LOCK_OUT       		3
#define 	FAULT_OUT       	4
#define		FAULT_OUT_RESET		5
#define 	SOUT1   	 	    6
#define 	SOUT2   	 	    7
#define		DRIVER_EN			8
#define		LED_OUT				9
/*******************************************************************************
* 3. AI
*******************************************************************************/
#define			AD_VBus 					0
#define			AD_KsiVBus 			  1
#define			AD_V12out 				2
#define			AD_V5out 			  	3
#define			AD_V12_5OvCurrent 4
#define			AD_MotorTmp 			5
#define			AD_Swi7 					6
#define			AD_Swi8 					7
#define			AD_PowTmpHigh 		8
#define			AD_PowTmpLow 		  9
#define			AD_Swi5 					10
#define			AD_Swi6					  11
#define			AD_RelayR					12
/******************************************************************************
*数据类型定义
******************************************************************************/
/******************************************************************************
*数据类型定义
******************************************************************************/
#define PWM_PRSC ((uint8_t)0)
#define CKTIM	((uint32_t)120000000uL)
#define PWM_FREQ ((uint16_t) FS) //Power devices switching frequency in Hz 
#define DEADTIME_NS	((uint16_t)1200)  //Deadtime Valuein nsec; range is [0...3500] 
#define DEADTIME_US	(DEADTIME_NS/1000.0)  //Deadtime Valuein usec;  

#define PWM_PERIOD ((uint16_t) (CKTIM / (uint32_t)(2 * PWM_FREQ *(PWM_PRSC+1)))) /* Resolution: 1Hz */  
#define HALL_TIM_PERIOD					(PWM_PERIOD*4)

#define DEADTIME  (INT16U)((unsigned long long)CKTIM/2 \
          *(unsigned long long)DEADTIME_NS/1000000000uL) // Deadtime Value 
			  
#if (CURRENT_SAMPLE_MODE == _CURRENT_SAMPLE_1HALL_LOW)
	#define MIN_AD_HOLD_TIME_US   8    //8US
#endif
#if (   (CURRENT_SAMPLE_MODE == _CURRENT_SAMPLE_3RES_LOW) \
			||(CURRENT_SAMPLE_MODE == _CURRENT_SAMPLE_3RES_LOW_3PHASE) \
		)
	#define MIN_AD_HOLD_TIME_US   9    //9US  12
	#define MID_SAMPLE_TIME_LIMIT_US   3    //3US, 4 for 4820. 

#endif

#define MIN_AD_HOLD_TIME  (uint16_t)((unsigned long long)CKTIM/2 \
          *(unsigned long long)MIN_AD_HOLD_TIME_US/1000000uL)
#define MID_SAMPLE_TIME_LIMIT  (uint16_t)((unsigned long long)CKTIM/2 \
          *(unsigned long long)MID_SAMPLE_TIME_LIMIT_US/1000000uL)
			  
#define AD_SAMPLE_DELAY_TIME_US   2.0    //2, 3US for 4805_G4
#define AD_SAMPLE_DELAY_TIME  (uint16_t)((unsigned long long)CKTIM/2 \
          *(unsigned long long)AD_SAMPLE_DELAY_TIME_US/1000000uL)	
			  
//该参数可以调整电流环的刷新频率 SAMPLING_FREQ
/****	ADC IRQ-HANDLER frequency, related to PWM  ****/
#define REP_RATE (1)  // (N.b): Internal current loop is performed every 
                      //             (REP_RATE + 1)/(2*PWM_FREQ) seconds.
                      // REP_RATE has to be an odd number in case of three-shunt
                      // current reading; this limitation doesn't apply to ICS
 
#define TIM_CtrlPWMOutputs(timer, setvalue)  ( ((setvalue)==ENABLE) ? (timer->BDTR |= (TIM_BDTR_MOE)) : (timer->BDTR &= ~(TIM_BDTR_MOE)) )
#define TIM_SetAutoreload(TIMx, Autoreload)  (TIMx->ARR = Autoreload)
#define TIM_SetCompare1(TIMx, Value)         (TIMx->CCR1 = Value)		
#define TIM_GetCounter(TIMx)                 (TIMx->CNT)	
					
#define FLASH_OB_GetRDP() READ_BIT(FLASH->OPTR, FLASH_OPTR_RDP)
#define IWDG_ReloadCounter()    WRITE_REG(IWDG->KR, IWDG_KEY_RELOAD)
extern FDCAN_HandleTypeDef hfdcan1;
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern ADC_HandleTypeDef hadc3;
extern ADC_HandleTypeDef hadc4;
extern ADC_HandleTypeDef hadc5;
extern DMA_HandleTypeDef hdma_adc1;
extern DMA_HandleTypeDef hdma_adc2;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim8;
extern IWDG_HandleTypeDef hiwdg;
extern SPI_HandleTypeDef hspi3;

#if (UART3_DRIVER_EN == 1)
extern UART_HandleTypeDef huart3;
#endif
					
extern INT32U ADCValue[ADC1_NUM];
extern INT32U ADC2Value[ADC2_NUM];
extern INT32U ADC3Value[ADC3_NUM];
/******************************************************************************
*函数定义
******************************************************************************/
extern void Bsp_Init(void);
extern void InitSysCtrl(void);
extern void InitDone(void);
extern void CPULoadStat(void);
extern void PwmEnable(void);
extern void PwmDisable(void);
extern void PwmDisableEsp(void);
void PwmUpdate(INT16S nSetPwm);
extern void PWMDriver(void);
//extern void STM32F4PwmUpdate(PWM_GEN *p);
extern INT16U EepromWrite(INT16U address, INT16U data);
extern INT16U EepromRead(INT16U address, INT16U* pdata);
extern void Delay(unsigned long ulTime);
extern void delay_us(INT32U nus);
INT32U TIM_SetCounter(TIM_TypeDef *TIMx,INT32U CountValue);

//extern 	tBoolean EepromBufRead(unsigned short address, unsigned short NByte,unsigned short *pRcvBuffer);
//extern 	tBoolean EepromBufWrite(unsigned short address,unsigned short NByte,unsigned short *pSndBuffer);
