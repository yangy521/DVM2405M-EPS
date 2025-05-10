/*******************************************************************************
*                 (C) Copyright 2023,Xi'an QExpand All Rights Reserved
*
* Filename:  CtlBoard_1220_G431_IOconfig.h
* Description:
* Author: QExpand
* Date: 2023-08-15
* Revision: V1.0
*******************************************************************************/

#ifndef _CTLBOARD_1220_G431_IOCONFIG_H_
#define _CTLBOARD_1220_G431_IOCONFIG_H_

/* USER CODE BEGIN Private defines */

/* Private defines -----------------------------------------------------------*/
//#define PWM_PRSC 0
//#define DEADTIME_NS 1000
//#define PWM_FREQ 16000
//#define PWM_PERIOD 7500
//#define REP_RATE 1
//#define DEADTIME 60
#define LOCK_OUT_Pin GPIO_PIN_10
#define LOCK_OUT_GPIO_Port GPIOG
#define CS_AD_Pin GPIO_PIN_0
#define CS_AD_GPIO_Port GPIOA
#define KSI_AD_Pin GPIO_PIN_1
#define KSI_AD_GPIO_Port GPIOA
#define VBUS_AD_Pin GPIO_PIN_2
#define VBUS_AD_GPIO_Port GPIOA
#define CMD1_AD_Pin GPIO_PIN_3
#define CMD1_AD_GPIO_Port GPIOA
#define CMD2_Pin GPIO_PIN_4
#define CMD2_GPIO_Port GPIOA
#define HOME_DI_Pin GPIO_PIN_5
#define HOME_DI_GPIO_Port GPIOA
#define ENA_Pin GPIO_PIN_10
#define ENA_GPIO_Port GPIOA
#define CAN_RX_Pin GPIO_PIN_11
#define CAN_RX_GPIO_Port GPIOA
#define CAN_TX_Pin GPIO_PIN_12
#define CAN_TX_GPIO_Port GPIOA
#define LED1_Pin GPIO_PIN_13
#define LED1_GPIO_Port GPIOA
#define LED2_Pin GPIO_PIN_14
#define LED2_GPIO_Port GPIOA
#define SPI_CS_Pin GPIO_PIN_15
#define SPI_CS_GPIO_Port GPIOA
#define SPI_CLK_Pin GPIO_PIN_3
#define SPI_CLK_GPIO_Port GPIOB
#define SPI_MISO_Pin GPIO_PIN_4
#define SPI_MISO_GPIO_Port GPIOB
#define SPI_MOSI_Pin GPIO_PIN_5
#define SPI_MOSI_GPIO_Port GPIOB
#define ENCODE_A_Pin GPIO_PIN_6
#define ENCODE_A_GPIO_Port GPIOB
#define ENCODE_B_Pin GPIO_PIN_7
#define ENCODE_B_GPIO_Port GPIOB
#define RLY_DO_Pin GPIO_PIN_8
#define RLY_DO_GPIO_Port GPIOB


//调试版禁用输出功能，保持SWD功能
#ifdef	LED1_Pin
	#undef	LED1_Pin	//SW_DO复用
	#undef	LED1_GPIO_Port
	#undef	LED2_Pin	//SW_CLK复用
	#undef	LED2_GPIO_Port

	#define LED1_Pin GPIO_PIN_15	
	#define LED1_GPIO_Port GPIOB	//invailed
	#define LED2_Pin GPIO_PIN_15
	#define LED2_GPIO_Port GPIOB	//invailed
#endif

/************ DO *****************/
#define RELAY_ON() 			HAL_GPIO_WritePin(RLY_DO_GPIO_Port, RLY_DO_Pin, GPIO_PIN_SET)
#define RELAY_OFF()			HAL_GPIO_WritePin(RLY_DO_GPIO_Port, RLY_DO_Pin, GPIO_PIN_RESET)

#define LOCK_ON()    		HAL_GPIO_WritePin( LOCK_OUT_GPIO_Port, LOCK_OUT_Pin, GPIO_PIN_SET) 	 //LOCK_OUT set
#define LOCK_OFF()   		HAL_GPIO_WritePin( LOCK_OUT_GPIO_Port, LOCK_OUT_Pin, GPIO_PIN_RESET) 	 //LOCK_OUT  clr

#ifdef __PRJ_RELEASE	
	#define LED_Y_ON()     	 	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, GPIO_PIN_SET)
	#define LED_Y_OFF()       HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, GPIO_PIN_RESET)

	#define LED_R_ON()     	 	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, GPIO_PIN_SET)
	#define LED_R_OFF()       HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, GPIO_PIN_RESET)
#else
	#define LED_Y_ON()     	 	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET)
	#define LED_Y_OFF()       HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET)

	#define LED_R_ON()     	 	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET)
	#define LED_R_OFF()       HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET)
#endif

///************ DI *****************/ 
#define    READ_ENA() 	HAL_GPIO_ReadPin(ENA_GPIO_Port, ENA_Pin)

#define    READ_HOME() 	HAL_GPIO_ReadPin(HOME_DI_GPIO_Port, HOME_DI_Pin)

#define    READ_CMD2() 	HAL_GPIO_ReadPin(CMD2_GPIO_Port, CMD2_Pin)



/* USER CODE BEGIN Private defines */
#define SPI_CS_0       	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET)
#define SPI_CS_1     	 	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET)

#endif  //ifndef _CTLBOARD_1220_G431_IOCONFIG_H
