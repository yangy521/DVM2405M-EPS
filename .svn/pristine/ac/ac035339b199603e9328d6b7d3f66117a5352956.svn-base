/**************************************************************************

***************************************************************************/ 

//#include <LPCAN21XX.H> // LPCAN21XX Peripheral Register
//#include "typ_user.h"
#include "./mcohw.h"
#include "canSTM32F4.h"

// Maximum number of FullCAN Filters
#define MAX_FILTERS 6

// Global timer/conter variable, incremented every millisecond▲
WORD volatile gTimCnt = 0;

// Counts number of filters (CAN message objects) used
WORD volatile gCANFilter = 0;



// FullCAN Message List
CAN_MSG volatile gFullCANList[MAX_FILTERS];

// Lookup table for receive filters
WORD gFilterList[MAX_FILTERS];                           

extern CAN_MSG MEM_FAR gRxCAN;

// Pull the next CAN message from receive buffer
BYTE MCOHW_PullMessage (CAN_MSG MEM_FAR *pReceiveBuf)
{
//    BYTE i;
//    CanRxMsg RxMessage;
//    CAN_Receive(CAN1,CAN_FIFO0,&RxMessage);
//    pReceiveBuf->ID = RxMessage.StdId;
//    pReceiveBuf->LEN = RxMessage.DLC;
//    for(i = 0; i < pReceiveBuf->LEN; i++)
//        pReceiveBuf->BUF[i] = RxMessage.Data[i]; 
    return 1; // Return False, no msg rcvd 
}

// Push the next transmit message into transmit queue
BYTE MCOHW_PushMessage (CAN_MSG MEM_FAR *pTransmitBuf)
{  
	BYTE i;
	tCANFrame canFrame;	//
	canFrame.ulID=(pTransmitBuf->ID)&0x7ff;
	canFrame.ucXID=0;			//0 标准帧；1 扩展帧  
	canFrame.ucDataLength=pTransmitBuf->LEN;		//数据场长度
	for(i=0;i<canFrame.ucDataLength;i++)
	{
		canFrame.ucData[i]=pTransmitBuf->BUF[i];
	}

	CANWriteBuffer(&canFrmTxBuffer, &canFrame);	
	return 1;
}


/**************************************************************************
DOES: Reads and returns the value of the current 1 millisecond system
timer tick.
**************************************************************************/
WORD MCOHW_GetTime (void)
{
    return gTimCnt;
}
//WORD TimCount;
void CanTimTik(void)
{
    gTimCnt++;
}
// Checks if a TimeStamp expired
BYTE MCOHW_IsTimeExpired(WORD timestamp)
{
	WORD time_now;
  	time_now = gTimCnt;
  	if (time_now > timestamp)
  	{
    	if ((time_now - timestamp) < 0x8000)
      		return 1;
    	else
      		return 0;
  	}
  	else
  	{
    	if ((timestamp - time_now) > 0x8000)
      		return 1;
    	else
      		return 0;
  	}
}
// Init CAN Interface and Timer
//BYTE MCOHW_Init (void)
//{
//	MX_FDCAN1_Init();
//	return (1);
//}


BYTE MCOHW_SetCANFilter (WORD CANID)
{
//    BYTE p;
//    WORD buf0, buf1;
//    CAN_FilterInitTypeDef CAN_FilterInitStructure;
//    if (gCANFilter == 0)
//    { // First call, init entry zero
//        gFilterList[0] = 0x17FF; // Disabled and unused
//    }
//    if (gCANFilter >= MAX_FILTERS)
//    {
//		return 0;
//    }
//	
//    // Filters must be sorted by priority
//	
//    // new filter is sorted into array
//    p = 0;
//    while (p < gCANFilter) // loop through all existing filters 
//    {
//        if (gFilterList[p] > CANID)
//        {
//            break;
//        }
//        p++;
//    }
//    // insert new filter here
//    buf0 = gFilterList[p]; // save current entry
//    gFilterList[p] = CANID; // insert the new entry
//    // move all remaining entries one row up
//    gCANFilter++;
//    while (p < gCANFilter)
//    {
//        p++;
//        buf1 = gFilterList[p];
//        gFilterList[p] = buf0;
//        buf0 = buf1;
//    }
//    p = 0;
//    while (p < gCANFilter) // loop through all existing filters 
//    {
//        CAN_FilterInitStructure.CAN_FilterNumber = p;
//        CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;
//        CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
//        CAN_FilterInitStructure.CAN_FilterIdHigh = gFilterList[p] << 5;
//        CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
//        CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
//        CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
//        CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FilterFIFO0;
//        CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
//        CAN_FilterInit(&CAN_FilterInitStructure);
//        p++;
//    }   
    return 1;
}

void CAN_Dispatch(void)
{
	 	tCANFrame canFrame;	//
	
		if(CANReadBuffer(&canFrmRxBuffer,&canFrame)!=EMPTY)//读取CAN数据接收缓冲区
		{						
				gRxCAN.ID = canFrame.ulID;
				gRxCAN.LEN = canFrame.ucDataLength;
				gRxCAN.BUF[0] = canFrame.ucData[0];
				gRxCAN.BUF[1] = canFrame.ucData[1];
				gRxCAN.BUF[2] = canFrame.ucData[2];
				gRxCAN.BUF[3] = canFrame.ucData[3];	
				gRxCAN.BUF[4] = canFrame.ucData[4];
				gRxCAN.BUF[5] = canFrame.ucData[5];
				gRxCAN.BUF[6] = canFrame.ucData[6];
				gRxCAN.BUF[7] = canFrame.ucData[7];
				CanOpenRxPres();
		}
}

/*----------------------- END OF FILE ----------------------------------*/

