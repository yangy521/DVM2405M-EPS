/*******************************************************************************
* Filename: canSTM32F4.c 	                                    	     		   *
* Description: 							           *
* Author:                                                                      *
* Date: 															           *
* Revision:															           *								           *
*******************************************************************************/

#include "canSTM32F4.h"
#include "fdcan.h"
#if(CTLBOARD_TYPE == _1220_V20)
#include <stm32g431xx.h>
#endif
#if(CTLBOARD_TYPE == _1220_G4)
#include <stm32g473xx.h>
#endif
tCANFrmBuffer canFrmRxBuffer; //定义CAN接收缓冲区
tCANFrmBuffer canFrmTxBuffer; //定义CAN发送缓冲区

//发送扩展帧数据
tBoolean CANFrmSend(tCANFrmBuffer  *pCanFrmbuffer)
{
	tCANFrame canFrame;
	uint16_t Len;
	FDCAN_TxHeaderTypeDef TxHeader;
	uint8_t TxData[8] = {0};
  //unsigned char ucMailBox;	//发送信箱号 
	
	HAL_NVIC_DisableIRQ(FDCAN1_IT0_IRQn);
	    
	if (   (HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan1) == 3)
		  && ((hfdcan1.Instance->CCCR & FDCAN_CCCR_INIT) == 0U)
     )
	{
		if (CANReadBuffer(pCanFrmbuffer, &canFrame) == NOT_EMPTY)
		{
			TxHeader.Identifier=canFrame.ulID;

			TxHeader.TxFrameType = FDCAN_DATA_FRAME;
			if(canFrame.ucXID==1)
				TxHeader.IdType = FDCAN_EXTENDED_ID;
			else
				TxHeader.IdType = FDCAN_STANDARD_ID;
			TxHeader.DataLength = canFrame.ucDataLength;
			TxHeader.DataLength <<= 16;//
			TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
			TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
			TxHeader.FDFormat = FDCAN_CLASSIC_CAN;
			TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
			TxHeader.MessageMarker = 0;
			
			TxData[0]= canFrame.ucData[0];
			TxData[1]= canFrame.ucData[1];
			TxData[2]= canFrame.ucData[2];
			TxData[3]= canFrame.ucData[3];
			TxData[4]= canFrame.ucData[4];
			TxData[5]= canFrame.ucData[5];
			TxData[6]= canFrame.ucData[6];
			TxData[7]= canFrame.ucData[7];
			if(HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData) == HAL_ERROR)                
			{
				if ((hfdcan1.Instance->CCCR & FDCAN_CCCR_INIT) != 0U)
				{
					CLEAR_BIT(hfdcan1.Instance->CCCR, FDCAN_CCCR_INIT);
				}
			}
		}
	}
	else
	{
		if ((hfdcan1.Instance->CCCR & FDCAN_CCCR_INIT) != 0U)
		{
			CLEAR_BIT(hfdcan1.Instance->CCCR, FDCAN_CCCR_INIT);
		}
	}		
	
	HAL_NVIC_EnableIRQ(FDCAN1_IT0_IRQn);
	return true;
}

//写CAN数据缓冲区
unsigned char CANWriteBuffer (tCANFrmBuffer  *pCanFrmbuffer, tCANFrame  *pCANFrame)
{
   	signed int tempWrite;
   	
   	tempWrite = pCanFrmbuffer->ucWrite + 1;
	if (tempWrite >= sizeof(pCanFrmbuffer->canFrmData)/sizeof(pCanFrmbuffer->canFrmData[0]))
		tempWrite = 0;

	if (tempWrite != pCanFrmbuffer->ucRead){
   		pCanFrmbuffer->canFrmData[pCanFrmbuffer->ucWrite] = *pCANFrame;					        /*  向接收缓冲区写数据          */
    	pCanFrmbuffer->ucWrite = tempWrite;    
    	return NOT_FULL;
	}else{
		return FULL;
	}
}

//读CAN数据缓冲区
unsigned char CANReadBuffer (tCANFrmBuffer *pCanFrmbuffer, tCANFrame  *pCANFrame)
{
	if (pCanFrmbuffer->ucRead != pCanFrmbuffer->ucWrite){
		*pCANFrame = pCanFrmbuffer->canFrmData[pCanFrmbuffer->ucRead];
		pCanFrmbuffer->ucRead++;
		if (pCanFrmbuffer->ucRead >= sizeof(pCanFrmbuffer->canFrmData)/sizeof(pCanFrmbuffer->canFrmData[0]))
			pCanFrmbuffer->ucRead = 0;
		return NOT_EMPTY;
	}else{
	    return EMPTY;
	}
}



////CAN中断处理
//void CANIntHandler(void)
//{
//	CanRxMsg rxMessage;
//	tCANFrame canFrame;

//  //判断引起中断的原因
//	if(CAN_GetITStatus(CAN1,CAN_IT_TME)==SET)//发送成功引起的中断
//	{
//		CAN_ClearITPendingBit(CAN1,CAN_IT_TME);
//		CANFrmSend(&canFrmTxBuffer);	//
//		
//	}
//	if(CAN_GetITStatus(CAN1,CAN_IT_FMP0)==SET)//接收成功引起的中断(FIFO0)
//	{
//		CAN_Receive(CAN1, CAN_FIFO0, &rxMessage);
//		if (rxMessage.IDE == CAN_Id_Standard)
//		{
//			canFrame.ucXID = 0;
//			canFrame.ulID = rxMessage.StdId; // 
//		}
//		else 
//		{
//			canFrame.ucXID = 1;
//			canFrame.ulID = rxMessage.ExtId; // 
//		}
//		canFrame.ucDataLength=rxMessage.DLC;	//	有效数据长度
//		canFrame.ucData[0]=rxMessage.Data[0];
//		canFrame.ucData[1]=rxMessage.Data[1];
//		canFrame.ucData[2]=rxMessage.Data[2];
//		canFrame.ucData[3]=rxMessage.Data[3];
//		canFrame.ucData[4]=rxMessage.Data[4];
//		canFrame.ucData[5]=rxMessage.Data[5];
//		canFrame.ucData[6]=rxMessage.Data[6];
//		canFrame.ucData[7]=rxMessage.Data[7];
//		CANWriteBuffer(&canFrmRxBuffer,&canFrame);	//把接收的数据写入CAN数据接收缓存区
//		CAN_ClearITPendingBit(CAN1,CAN_IT_FMP0);
//	}
//	else if(CAN_GetITStatus(CAN1,CAN_IT_FMP1)==SET)//接收成功引起的中断(FIFO1)
//	{
//		CAN_Receive(CAN1, CAN_FIFO1, &rxMessage);
//		if (rxMessage.IDE == CAN_Id_Standard)
//		{
//			canFrame.ucXID = 0;
//			canFrame.ulID = rxMessage.StdId; // 
//		}
//		else 
//		{
//			canFrame.ucXID = 1;
//			canFrame.ulID = rxMessage.ExtId; // 
//		}
//		canFrame.ucDataLength=rxMessage.DLC;	//	有效数据长度
//		canFrame.ucData[0]=rxMessage.Data[0];
//		canFrame.ucData[1]=rxMessage.Data[1];
//		canFrame.ucData[2]=rxMessage.Data[2];
//		canFrame.ucData[3]=rxMessage.Data[3];
//		canFrame.ucData[4]=rxMessage.Data[4];
//		canFrame.ucData[5]=rxMessage.Data[5];
//		canFrame.ucData[6]=rxMessage.Data[6];
//		canFrame.ucData[7]=rxMessage.Data[7];
//		CANWriteBuffer(&canFrmRxBuffer,&canFrame);	//把接收的数据写入CAN数据接收缓存区
//		CAN_ClearITPendingBit(CAN1,CAN_IT_FMP1);
//	}
//	else //总线故障引起的中断
//	{
//	}
//}

