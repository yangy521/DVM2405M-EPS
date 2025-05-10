/*******************************************************************************
* Filename: canSTM32F4.c 	                                    	     		   *
* Description: 							           *
* Author:                                                                      *
* Date: 															           *
* Revision:															           *								           *
*******************************************************************************/
#include "Device.h"
#include "canSTM32F4.h"
#include "stm32g4xx_hal.h"

tCANFrmBuffer canFrmRxBuffer; //定义CAN接收缓冲区
tCANFrmBuffer canFrmTxBuffer; //定义CAN发送缓冲区

//发送扩展帧数据
unsigned char CANFrmSend(tCANFrmBuffer  *pCanFrmbuffer)
{
    tCANFrame canFrame;
    FDCAN_TxHeaderTypeDef TxHeader;
    uint8_t TxData[8] = {0};

    //if ((hfdcan1.Instance->TXFQS & FDCAN_TXFQS_TFQF) != 0U)
#if (FDCAN_NO == 1)
    HAL_NVIC_DisableIRQ(FDCAN1_IT0_IRQn);
#endif
#if (FDCAN_NO == 2)
    HAL_NVIC_DisableIRQ(FDCAN2_IT0_IRQn);
#endif

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
#if (FDCAN_NO == 1)
    HAL_NVIC_EnableIRQ(FDCAN1_IT0_IRQn);
#endif
#if (FDCAN_NO == 2)
    HAL_NVIC_EnableIRQ(FDCAN2_IT0_IRQn);
#endif

    return true;
}

//写CAN数据缓冲区
unsigned char CANWriteBuffer (tCANFrmBuffer  *pCanFrmbuffer, tCANFrame  *pCANFrame)
{
    signed int tempWrite;

    tempWrite = pCanFrmbuffer->ucWrite + 1;
    if (tempWrite >= sizeof(pCanFrmbuffer->canFrmData)/sizeof(pCanFrmbuffer->canFrmData[0]))
        tempWrite = 0;

    if (tempWrite != pCanFrmbuffer->ucRead) {
        pCanFrmbuffer->canFrmData[pCanFrmbuffer->ucWrite] = *pCANFrame;					        /*  向接收缓冲区写数据          */
        pCanFrmbuffer->ucWrite = tempWrite;
        return NOT_FULL;
    } else {
        return FULL;
    }
}

//读CAN数据缓冲区
unsigned char CANReadBuffer (tCANFrmBuffer *pCanFrmbuffer, tCANFrame  *pCANFrame)
{
    if (pCanFrmbuffer->ucRead != pCanFrmbuffer->ucWrite) {
        *pCANFrame = pCanFrmbuffer->canFrmData[pCanFrmbuffer->ucRead];
        pCanFrmbuffer->ucRead++;
        if (pCanFrmbuffer->ucRead >= sizeof(pCanFrmbuffer->canFrmData)/sizeof(pCanFrmbuffer->canFrmData[0]))
            pCanFrmbuffer->ucRead = 0;
        return NOT_EMPTY;
    } else {
        return EMPTY;
    }
}

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    tCANFrame canFrame;
    FDCAN_RxHeaderTypeDef RxHeader;
    uint8_t RxData[8];
#if (FDCAN_NO == 1)
    if(hfdcan->Instance==FDCAN1)
#endif
#if (FDCAN_NO == 2)
        if(hfdcan->Instance==FDCAN2)
#endif
        {
            HAL_FDCAN_GetRxMessage(&hfdcan1,FDCAN_RX_FIFO0,&RxHeader,RxData);//Read CAN data

            if (RxHeader.IdType == FDCAN_STANDARD_ID)
            {
                canFrame.ucXID = 0;
                canFrame.ulID = RxHeader.Identifier; //
            }
            else
            {
                canFrame.ucXID = 1;
                canFrame.ulID = RxHeader.Identifier; //
            }
            canFrame.ucDataLength=RxHeader.DataLength>>16;        //right  shift  16
            canFrame.ucData[0]=RxData[0];
            canFrame.ucData[1]=RxData[1];
            canFrame.ucData[2]=RxData[2];
            canFrame.ucData[3]=RxData[3];
            canFrame.ucData[4]=RxData[4];
            canFrame.ucData[5]=RxData[5];
            canFrame.ucData[6]=RxData[6];
            canFrame.ucData[7]=RxData[7];
            CANWriteBuffer(&canFrmRxBuffer,&canFrame);        //write to canFrmRxBuffer
        }
}

void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs)
{
    FDCAN_RxHeaderTypeDef RxHeader;
    uint8_t RxData[8];
#if (FDCAN_NO == 1)
    if(hfdcan->Instance==FDCAN1)
#endif
#if (FDCAN_NO == 2)
        if(hfdcan->Instance==FDCAN2)
#endif
        {
            HAL_FDCAN_GetRxMessage(&hfdcan1,FDCAN_RX_FIFO1,&RxHeader,RxData);//????
        }
}


void HAL_FDCAN_TxFifoEmptyCallback(FDCAN_HandleTypeDef *hfdcan)
{
    tCANFrame canFrame;
    FDCAN_TxHeaderTypeDef TxHeader;
    uint8_t TxData[8] = {0};
    tCANFrmBuffer  *pCanFrmbuffer;
    pCanFrmbuffer = &canFrmTxBuffer;
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
            if(hfdcan1.ErrorCode & HAL_FDCAN_ERROR_FIFO_FULL)
                hfdcan1.Instance->CCCR &= ~0x00000001;        // Initialization started,then Normal operation
        }
    }
}

