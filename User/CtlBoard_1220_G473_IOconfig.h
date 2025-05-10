/*******************************************************************************
* (C) Copyright 2023,Xi'an QExpand All Rights Reserved
*
* Filename:  CtlBoard_1220_G473_IOconfig.h
* Description:
* Author: QExpand
* Date: 2023-08-16
* Revision: V1.0
*******************************************************************************/

#ifndef _CTLBOARD_1220_G473_IOCONFIG_H_
#define _CTLBOARD_1220_G473_IOCONFIG_H_

/* Private defines -----------------------------------------------------------*/
//#define PWM_PRSC 0
//#define DEADTIME_NS 1000
//#define PWM_FREQ 16000
//#define PWM_PERIOD 7500
//#define REP_RATE 1
//#define DEADTIME 60

#define SPI_CS_Pin 				GPIO_PIN_2
#define SPI_CS_GPIO_Port 		GPIOD
#define SPI_CLK_Pin 			GPIO_PIN_10
#define SPI_CLK_GPIO_Port   	GPIOC
#define SPI_MISO_Pin 			GPIO_PIN_11
#define SPI_MISO_GPIO_Port  	GPIOC
#define SPI_MOSI_Pin 			GPIO_PIN_12
#define SPI_MOSI_GPIO_Port  	GPIOC
#define GPIO_AF_SPIX			GPIO_AF6_SPI3

#define SW1_Pin					GPIO_PIN_15   //Interlock
#define SW1_GPIO_Port			GPIOC
#define SW2_Pin					GPIO_PIN_14   //Interlock
#define SW2_GPIO_Port			GPIOC
#define SW3_Pin			      	GPIO_PIN_13   //Home Di
#define SW3_GPIO_Port			GPIOC

//#define ENA_Pin 						GPIO_PIN_15
//#define ENA_GPIO_Port 			GPIOC  //
////#define INLOCK_Pin    			GPIO_Pin_15
//#define INLOCK_GPIO_Port   	GPIOC		//PC15 Inter-Lock  sw1
//#define HOME_DI_Pin 				GPIO_PIN_13
//#define HOME_DI_GPIO_Port		GPIOC  //

//#define LOCK_OUT_Pin 				GPIO_PIN_14 //daiding
//#define LOCK_OUT_GPIO_Port 	GPIOC
#define FAULT_OUT_EN_Pin			GPIO_PIN_10
#define FAULT_OUT_EN_GPIO_Port		GPIOA
#define FAULT_RESET_Pin				GPIO_PIN_8
#define FAULT_RESET_GPIO_Port		GPIOC
#define FAULT_OUT_R_Pin				GPIO_PIN_9
#define FAULT_OUT_R_GPIO_Port		GPIOC
//#define CS_AD_Pin 					GPIO_PIN_0 
//#define CS_AD_GPIO_Port 		GPIOA  //
#define KSI_Pin 					GPIO_PIN_2
#define KSI_GPIO_Port 				GPIOC
#define VBUS_Pin 					GPIO_PIN_0
#define VBUS_GPIO_Port				GPIOC
#define CMD_ENCA_Pin 				GPIO_PIN_6
#define CMD_ENCA_GPIO_Port 			GPIOB
#define CMD_ENCB_Pin 				GPIO_PIN_7
#define CMD_ENCB_GPIO_Port 			GPIOB

#define LED_Y_Pin 					GPIO_PIN_4
#define LED_Y_GPIO_Port 			GPIOC
#define LED_R_Pin 					GPIO_PIN_5
#define LED_R_GPIO_Port 			GPIOC
#define M_ENCODE_A_Pin 				GPIO_PIN_6   //Motor_ENCODER1
#define M_ENCODE_A_GPIO_Port  		GPIOC
#define M_ENCODE_B_Pin 				GPIO_PIN_7
#define M_ENCODE_B_GPIO_Port  		GPIOC
#define RLY_DO_Pin 					GPIO_PIN_15
#define RLY_DO_GPIO_Port 			GPIOA
#define RELAY_Pin					GPIO_PIN_1
#define RELAY_GPIO_Port				GPIOC

#define M1_I_Pin					GPIO_PIN_3
#define M1_I_GPIO_Port  		 	GPIOC
#define M2_I_Pin					GPIO_PIN_0
#define M2_I_GPIO_Port			 	GPIOA
#define THROWIP2_Pin				GPIO_PIN_1
#define THROWIP2_GPIO_Port	 		GPIOA
#define TMP_Pin						GPIO_PIN_2
#define TMP_GPIO_Port				GPIOA
#define THROWIP1_Pin  			 	GPIO_PIN_3
#define THROWIP1_GPIO_Port   		GPIOA
#define V5OUTA_I_Pin	      		GPIO_PIN_4
#define V5OUTA_I_GPIO_Port			GPIOA
#define V5OUTB_I_Pin			   	GPIO_PIN_5
#define V5OUTB_I_GPIO_Port	 		GPIOA
#define V5OUTA_Pin 					GPIO_PIN_6
#define V5OUTA_GPIO_Port		 	GPIOA
#define V5OUTB_Pin 					GPIO_PIN_7
#define V5OUTB_GPIO_Pin			 	GPIOA


#define M1_Pin 						GPIO_PIN_0
#define M1_GPIO_Port 				GPIOB
#define M2_Pin 						GPIO_PIN_1
#define M2_GPIO_Port 				GPIOB
#define DRIVER_EN_Pin				GPIO_PIN_8
#define DRIVER_EN_GPIO_Port			GPIOB
#define THROTTLE1_Pin				GPIO_PIN_9
#define THROTTLE1_GPIO_Port 		GPIOB
#define THROTTLE2_Pin				GPIO_PIN_2
#define THROTTLE2_GPIO_Port			GPIOB
#define TMP_LOW_Pin					GPIO_PIN_12
#define	TMP_LOW_GPIO_Port			GPIOB


#define FDCAN_NO   		1
#define CAN_TX_Pin 					GPIO_PIN_12
#define CAN_TX_GPIO_Port 			GPIOA
#define CAN_RX_Pin 					GPIO_PIN_11
#define CAN_RX_GPIO_Port 			GPIOA

#define UART3_DRIVER_EN        1
#define UART3_RX_Pin 				GPIO_PIN_11
#define UART3_RX_GPIO_Port 			GPIOB
#define UART3_TX_Pin 				GPIO_PIN_10
#define UART3_TX_GPIO_Port 			GPIOB

#define  WATCH_DOG_Pin				GPIO_PIN_5
#define  WATCH_DOG_GPIO_Port  		GPIOB
#define  WATCH_DOG_IN_Pin   		GPIO_PIN_3
#define  WATCH_DOG_IN_GPIO_Port  	GPIOB

#define DO_PWM2_NO	2
#define TIM2_CHANNEL1_DO_Pin          RLY_DO_Pin
#define TIM2_CHANNEL1_DO_GPIO_Port    RLY_DO_GPIO_Port

/********Motor Pins Config***********/
#define MOTOR_H1_Pin				GPIO_PIN_8
#define MOTOR_H1_GPIO_Port			GPIOA
#define MOTOR_H2_Pin				GPIO_PIN_9
#define MOTOR_H2_GPIO_Port			GPIOA
#define MOTOR_N1_Pin				GPIO_PIN_13
#define MOTOR_N1_GPIO_Port			GPIOB
#define MOTOR_N2_Pin				GPIO_PIN_14
#define MOTOR_N2_GPIO_Port			GPIOB


/************ DI INPUT pins config *****************/
//#define INPUT_PINS_GPIOA  (0)
#define INPUT_PINS_GPIOB  (WATCH_DOG_IN_Pin)
#define INPUT_PINS_GPIOC  (SW1_Pin|SW2_Pin|SW3_Pin|RELAY_Pin|FAULT_OUT_R_Pin)
//#define INPUT_PINS_GPIOD  (0)
//#define INPUT_PINS_GPIOE  (0)

/************ DO OUTPUT pins config *****************/
#define OUTPUT_PINS_GPIOA  (FAULT_OUT_EN_Pin)
#define OUTPUT_PINS_GPIOB  (THROTTLE1_Pin|THROTTLE2_Pin|DRIVER_EN_Pin|WATCH_DOG_Pin|TMP_LOW_Pin)
#define OUTPUT_PINS_GPIOC  (LED_Y_Pin|LED_R_Pin|FAULT_RESET_Pin)
#define OUTPUT_PINS_GPIOD  (SPI_CS_Pin)
//#define OUTPUT_PINS_GPIOE  (0)

/************ Analog INPUT Channel config *****************/
#define VBUS_ADC12_CHANNEL    ADC_CHANNEL_6
#define KSI_ADC12_CHANNEL    ADC_CHANNEL_8
#define IM1_ADC12_CHANNEL    ADC_CHANNEL_9
#define IM2_ADC12_CHANNEL    ADC_CHANNEL_1
#define THROWIP2_ADC1_CHANNEL    ADC_CHANNEL_2
#define TMP_ADC1_CHANNEL    ADC_CHANNEL_3
#define THROWIP1_ADC1_CHANNEL    ADC_CHANNEL_4
#define OUT5V_A_I_ADC2_CHANNEL    ADC_CHANNEL_17
#define OUT5V_B_I_ADC2_CHANNEL    ADC_CHANNEL_13
#define OUT_5V_A_ADC2_CHANNEL    ADC_CHANNEL_3
#define OUT_5V_B_ADC2_CHANNEL    ADC_CHANNEL_4
#define M1_R_ADC3_CHANNEL    ADC_CHANNEL_12
#define M2_R_ADC3_CHANNEL    ADC_CHANNEL_1
/************ ADC1 INPUT pins config *****************/
#define ADC1_PINS_GPIOA  (THROWIP2_Pin | TMP_Pin |THROWIP1_Pin)
//#define ADC1_PINS_GPIOB  (0)
#define ADC1_PINS_GPIOC  (VBUS_Pin| KSI_Pin |M1_I_Pin)
//#define ADC1_PINS_GPIOD  (0)
//#define ADC1_PINS_GPIOE  (0)
//#define ADC1_PINS_GPIOF  (0)
/************ ADC1 Regular config *****************/
#define   ADC1_NUM		6

#define ADC1_REGULAR_RANK_1_CHANNEL    TMP_ADC1_CHANNEL
#define ADC1_REGULAR_RANK_2_CHANNEL    THROWIP2_ADC1_CHANNEL
#define ADC1_REGULAR_RANK_3_CHANNEL    VBUS_ADC12_CHANNEL
#define ADC1_REGULAR_RANK_4_CHANNEL    KSI_ADC12_CHANNEL
#define ADC1_REGULAR_RANK_5_CHANNEL    THROWIP1_ADC1_CHANNEL  

#define ADC1_REGULAR_RANK_VREFINT_CHANNEL   ADC_CHANNEL_VREFINT
#define ADC1_REGULAR_RANK_VREFINT        		ADC_REGULAR_RANK_6
/************ ADC1 Injected config *****************/
#define ADC1_INJECTED_RANK_1_CHANNEL    IM1_ADC12_CHANNEL


/************ ADC2 INPUT pins config *****************/
#define ADC2_PINS_GPIOA  (M2_I_Pin |V5OUTA_I_Pin|V5OUTB_I_Pin|V5OUTA_Pin|V5OUTB_Pin)
#define ADC2_PINS_GPIOB  (M1_Pin)
//#define ADC2_PINS_GPIOC  (0)
//#define ADC2_PINS_GPIOD  (0)
//#define ADC2_PINS_GPIOE  (0)
//#define ADC2_PINS_GPIOF  (0)
/************ ADC2 Regular config *****************/
#define   ADC2_NUM		4

#define ADC2_REGULAR_RANK_1_CHANNEL    OUT_5V_A_ADC2_CHANNEL 
#define ADC2_REGULAR_RANK_2_CHANNEL    OUT_5V_B_ADC2_CHANNEL
#define ADC2_REGULAR_RANK_3_CHANNEL    OUT5V_A_I_ADC2_CHANNEL
#define ADC2_REGULAR_RANK_4_CHANNEL    OUT5V_B_I_ADC2_CHANNEL
/************ ADC2 Injected config *****************/
#define ADC2_INJECTED_RANK_1_CHANNEL    IM2_ADC12_CHANNEL

/************ ADC3 INPUT pins config *****************/
//#define ADC3_PINS_GPIOA  (0)
#define ADC3_PINS_GPIOB  (M1_Pin | M2_Pin)
//#define ADC3_PINS_GPIOC  (0)
//#define ADC3_PINS_GPIOD  (0)
//#define ADC3_PINS_GPIOE  (0)
//#define ADC3_PINS_GPIOF  (0)
/************ ADC3 Regular config *****************/
#define   ADC3_NUM		2
#define ADC3_REGULAR_RANK_1_CHANNEL    M1_R_ADC3_CHANNEL 
#define ADC3_REGULAR_RANK_2_CHANNEL    M2_R_ADC3_CHANNEL
/************ ADC3 Injected config *****************/
//#define ADC3_INJECTED_RANK_1_CHANNEL    

/************ DO *****************/
#define FAULT_LOW()			HAL_GPIO_WritePin(FAULT_OUT_EN_GPIO_Port,FAULT_OUT_EN_Pin,GPIO_PIN_RESET)
#define FAULT_HIGH()		HAL_GPIO_WritePin(FAULT_OUT_EN_GPIO_Port,FAULT_OUT_EN_Pin,GPIO_PIN_SET)
#define FAULT_RESET()    	HAL_GPIO_WritePin( FAULT_RESET_GPIO_Port, FAULT_RESET_Pin, GPIO_PIN_RESET) 	//Low level is effect
#define FAULT_NORESET()   	HAL_GPIO_WritePin( FAULT_RESET_GPIO_Port, FAULT_RESET_Pin, GPIO_PIN_SET) 	

#define THROTTLE1_ON() 	HAL_GPIO_WritePin(THROTTLE1_GPIO_Port, THROTTLE1_Pin, GPIO_PIN_SET)
#define THROTTLE1_OFF()	HAL_GPIO_WritePin(THROTTLE1_GPIO_Port, THROTTLE1_Pin, GPIO_PIN_RESET)
#define THROTTLE2_ON() 	HAL_GPIO_WritePin(THROTTLE2_GPIO_Port, THROTTLE2_Pin, GPIO_PIN_SET)
#define THROTTLE2_OFF()	HAL_GPIO_WritePin(THROTTLE2_GPIO_Port, THROTTLE2_Pin, GPIO_PIN_RESET)
#define LED_Y_ON()     	HAL_GPIO_WritePin(LED_Y_GPIO_Port, LED_Y_Pin, GPIO_PIN_SET)
#define LED_Y_OFF()     HAL_GPIO_WritePin(LED_Y_GPIO_Port, LED_Y_Pin, GPIO_PIN_RESET)
#define LED_R_ON()     	HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET)
#define LED_R_OFF()     HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET)

#define DRIVEREN_ON()    HAL_GPIO_WritePin( DRIVER_EN_GPIO_Port, DRIVER_EN_Pin, GPIO_PIN_SET)
#define DRIVEREN_OFF()   HAL_GPIO_WritePin( DRIVER_EN_GPIO_Port, DRIVER_EN_Pin, GPIO_PIN_RESET)

/************ DI *****************/ 
#define	 READ_RELAY()	 HAL_GPIO_ReadPin(RELAY_GPIO_Port,RELAY_Pin)
#define  READ_CMD2() 	 HAL_GPIO_ReadPin(CMD2_GPIO_Port, CMD2_Pin)

#define	 READ_SW1()   HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)
#define	 READ_SW2()   HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin)
#define	 READ_SW3()   HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)
#define  READ_HOME()  HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)
#define  READ_FAULTOUT()	HAL_GPIO_ReadPin(FAULT_OUT_R_GPIO_Port,FAULT_OUT_R_Pin)
	
/* USER CODE BEGIN Private defines */
#define SPI_CS_0       	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET)
#define SPI_CS_1     	 	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET)

#define RESET_AD_LOWSIDE		HAL_GPIO_WritePin(TMP_LOW_GPIO_Port,TMP_LOW_Pin,GPIO_PIN_RESET);
#define SET_AD_LOWSIDE			HAL_GPIO_WritePin(TMP_LOW_GPIO_Port,TMP_LOW_Pin,GPIO_PIN_SET);
	
#define WATCH_DOG_OUT_TOGGLE()		HAL_GPIO_TogglePin(WATCH_DOG_GPIO_Port,WATCH_DOG_Pin)  //向副Mcu发出翻转信号（WatchDog）
#define READ_WATCH_DOG_IN()   		HAL_GPIO_ReadPin(WATCH_DOG_IN_GPIO_Port,WATCH_DOG_IN_Pin)  //Check  from B

#define IWDG_ReloadCounter()    WRITE_REG(IWDG->KR, IWDG_KEY_RELOAD)
#define UART3_PreemptionPriority  2
#define UART3RX_SubPriority		2

#endif //ifndef _CTLBOARD_1220_G473_IOCONFIG_H_
