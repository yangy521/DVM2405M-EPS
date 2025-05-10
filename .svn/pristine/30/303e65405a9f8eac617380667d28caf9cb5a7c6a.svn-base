/*******************************************************************************
* Filename: Comm.c	                                             	 		   *
* Description:											   			 		   												*
* Author:                                                           		   *
* Date:     														 		   														*
* Revision:															 		 														  *
*******************************************************************************/
#include  "Packet.h"
#include  "iTimer.h"
#include "Device.h"
#include "uartSTM32F4.h"
#include "string.h"
#include	"PARA.h"
#include 	"CommonRam.h"
#include "PLCLogic.h"

#if ((UART_LOGIC_TYPE == UART_LOGIC_MASTER) || (UART_LOGIC_TYPE == UART_LOGIC_SLAVE))

tPacket	UARTPacketRx;
tPacket	UARTPacketTx;

tCommRamS gRamSlv;
tCommRamM gRamMst;
unsigned char Rx_Array[64];
unsigned char ReceiveTimeOut = 0;
void RXData_to_CtrlRam(void);

void PacketInit(void)
{
	memset(&uartRxBuffer,0,sizeof(uartRxBuffer));	
	memset(&uartTxBuffer,0,sizeof(uartTxBuffer));	
	memset(&UARTPacketRx,0,sizeof(UARTPacketRx));	
	memset(&UARTPacketTx,0,sizeof(UARTPacketTx));
	memset(&gRamMst,0,sizeof(gRamMst));	
	memset(&gRamSlv,0,sizeof(gRamSlv));
	UARTPacketRx.RxState = WAIT_INIT;
}

//求N字节的8位校验和
unsigned char GetSum8_size(unsigned char* pHead,unsigned short Size)
{
		unsigned char Sum=0;
		unsigned char* pTemp;
	
		if(Size == 0) return 0;  //有效数据个数判断
	
		pTemp = pHead;
		while(Size--)
		{
			Sum += *pTemp++;
		}

   return Sum;
}

//串口数据输入
void UARTPkt_DataInManage(void)
{
//////////////////////////////////////////////////////////////////////
	unsigned char ucData;

	if(UARTGetBufLen(&uartRxBuffer) == 0)  //当缓存区无数据  并且状态为初  则进入空数据判断状态
	{
		ReceiveTimeOut++;
	}
	else
	{
		ReceiveTimeOut = 0;  //有数据过来就从0开始
	}
		while(UARTGetBufLen(&uartRxBuffer) > 0)
		{
			switch (UARTPacketRx.RxState)
			{
				case WAIT_INIT:  //初始化
					UARTPacketRx.wHead = 0;
					UARTPacketRx.wLength = 0;
				
					UARTPacketRx.RxState = WAIT_HEAD1;
				
				case WAIT_HEAD1: //等待帧头AABB
					UARTReadBuffer(&uartRxBuffer, &ucData);
					if(ucData == 0xAA)
					{
						UARTPacketRx.wHead = 0xAA00;
						UARTPacketRx.RxState = WAIT_HEAD2;  //下一步
					}
					else
					{
						UARTPacketRx.RxState = WAIT_HEAD1;  //继续等待帧头	
					}					
					break;			
				case WAIT_HEAD2: //等待帧头AABB
					UARTReadBuffer(&uartRxBuffer, &ucData);
					if(ucData == 0xBB)
					{
						UARTPacketRx.wHead = 0xAABB;
						UARTPacketRx.RxState = WAIT_FUNC1;  //下一步
					}
					else if(ucData == 0xAA)
					{
						UARTPacketRx.wHead = 0xAA00;
						UARTPacketRx.RxState = WAIT_HEAD2;  //下一步
					}
					else
					{
						UARTPacketRx.RxState = WAIT_HEAD1;  //继续等待帧头	
					}					
					break;			
				case WAIT_FUNC1: //等待帧头功能码01
					UARTReadBuffer(&uartRxBuffer, &ucData);
					UARTPacketRx.wFunc = ucData & 0xff;
					UARTPacketRx.RxState = WAIT_FUNC2;  //
						//功能码01有效性检测
						//发送异常报错，功能码无效
					break;				
				case WAIT_FUNC2: //等待帧头功能码02
					UARTReadBuffer(&uartRxBuffer, &ucData);
					UARTPacketRx.wFunc |= ((unsigned short)ucData<<8);
					UARTPacketRx.RxState = WAIT_LEN1;  //
						//功能码02有效性检测
						//发送异常报错，功能码无效
					break;				
				case WAIT_LEN1:	//等待数据域长度
					UARTReadBuffer(&uartRxBuffer, &ucData);
					UARTPacketRx.wLength = ucData & 0xff;
					UARTPacketRx.RxState = WAIT_LEN2;  //
					if(UARTPacketRx.wLength > UART_BUF_NUM)	//接收数据超长错误
					{
						if(ucData == 0xAA)
						{
							UARTPacketRx.wHead = 0xAA00;
							UARTPacketRx.wLength = 0;
							UARTPacketRx.RxState = WAIT_HEAD2;  //下一步
						}
						else
						{
							UARTPacketRx.RxState = WAIT_INIT;  //继续等待帧头	
						}					
						//UARTBufFlush(&uartRxBuffer);
						//发送异常报错，数据长度错误
					}
					else  				
						UARTPacketRx.RxState = WAIT_LEN2;  //下一步	等待数据
					break;
				case WAIT_LEN2:	//等待数据域长度
					
					UARTReadBuffer(&uartRxBuffer, &ucData);
					UARTPacketRx.wLength |= ((unsigned short)ucData<<8);
					if(UARTPacketRx.wLength > UART_BUF_NUM)	//接收数据超长错误
					{
						if(ucData == 0xAA)
						{
							UARTPacketRx.wHead = 0xAA00;
							UARTPacketRx.wLength = 0;
							UARTPacketRx.RxState = WAIT_HEAD2;  //下一步
						}
						else
						{
							UARTPacketRx.RxState = WAIT_INIT;  //继续等待帧头	
						}					
						//UARTBufFlush(&uartRxBuffer);
						//发送异常报错，数据长度错误
						break;
					}
					else  				
						UARTPacketRx.RxState = WAIT_DATA;  //下一步	等待数据
				case WAIT_DATA:
					if(UARTGetBufLen(&uartRxBuffer) < (UARTPacketRx.wLength+1))
					{
						return ; //数据长度不足，等待下次读取	
					}	
					UARTReadBufArray(&uartRxBuffer, Rx_Array, UARTPacketRx.wLength+1);	//数据域
					UARTPacketRx.Checksum = Rx_Array[UARTPacketRx.wLength];
					
					//校验和判断
					if(GetSum8_size(Rx_Array,UARTPacketRx.wLength) != UARTPacketRx.Checksum)	//校验和错误
					{
						//UARTBufFlush(&uartRxBuffer);
						//发送异常报错，校验和错误
					}
					else
					{
						UARTPacketRx.pData = Rx_Array;
						RXData_to_CtrlRam();
						//UARTBufFlush(&uartRxBuffer);
					}
					UARTPacketRx.RxState = WAIT_INIT;
					
			}
		}
}


/* MASTER data define ->gRamMst
	NO.		Name			Datatype	Position	Meaning
	Byte0	Control word	Unsigned8	0.0			Driver EN
										0.1			Fault clr
										0.2..0.6	free
										0.7			Toggle bit
	Byte1	Alarm code		Unsigned8	1.0			alarm code
	Byte2~7											free
*/
/* SLAVE data define  ->gRamSlv
	NO.		Name			Datatype	Position	Meaning
	Byte0	State word		Unsigned8	0.0			Driver EN
										0.1			ChargeInhibit
										0.2..0.6	free
										0.7			Toggle bit
	Byte1	Alarm code		Unsigned8	1.0			alarm code
	Byte2	Board Tmp		Unsigned8	2.0
	Byte3	Motor Tmp		Unsigned8	3.0
	Byte4~5	Drvier1AD		Unsigned16	4.0
	Byte6~7	Drvier2AD		Unsigned16	6.0
	Byte8~9	Drvier3AD		Unsigned16	8.0
	Byte10~11			
*/
//串口数据解析处理
void RXData_to_CtrlRam(void)
{
#if (UART_LOGIC_TYPE == UART_LOGIC_MASTER)
	gRamSlv.Info.Stateword = *UARTPacketRx.pData;
	gRamSlv.Info.AlarmCode = *(UARTPacketRx.pData+1);
	gRamSlv.Info.SwiState = *(UARTPacketRx.pData + 2);
#endif	//#if (UART_LOGIC_TYPE == UART_LOGIC_MASTER)
	
#if	(UART_LOGIC_TYPE == UART_LOGIC_SLAVE)
	gRamMst.Info.Stateword = *UARTPacketRx.pData;
	gRamMst.Info.AlarmCode = *(UARTPacketRx.pData+1);
#endif	
}

//串口数据逻辑处理
void UARTPkt_DataLogicManage(void)
{
	static INT16U Swi_JudgeCount = 0;
	if(ReceiveTimeOut > 50) /***超时报警***/  //50*4 = 200ms 
	{ 
		MCL_SetFault(MASTER_UART_ERR);		   //收不到串口数据
	}
#ifndef _DEBUG_MODE	
#if(CTLBOARD_TYPE == _1220_G4)
	if(((gPara.Switch & 0x07) ^ (gRamSlv.Info.SwiState & 0x07)) != 0)   //SW1~SW3校验
	{
		if (Swi_JudgeCount > 200)
		{
			MCL_SetFault(MASTER_SWI_ERR);
		}
		else
		{
			Swi_JudgeCount++;
		}
	}
	else
	{
		Swi_JudgeCount = 0;
		gPLCCtl.doDataOut[DRIVER_EN] = 0;
	}
    
    if(gPLCCtl.ReMotorEnc == 1)  //128 bit0  勾选不报电机编码器冗余故障
    {
        if(gRamSlv.Info.AlarmCode == REDUNDANT_MOTOR_ENC_ERR)
            gRamSlv.Info.AlarmCode = 0;
    }
    if(gPLCCtl.ReCmdEnc == 1)  //128 bit1   勾选不报方向盘冗余故障
    {
        if(gRamSlv.Info.AlarmCode == PLUSE_CMD_LOST)
            gRamSlv.Info.AlarmCode = 0;       
    }
    
	if((gRamSlv.Info.AlarmCode > 50) && (gRamSlv.Info.AlarmCode <= REDUNDANT_MOTOR_ENC_ERR)) //副Mcu监测故障必须重启消除
	{
		gCRam.bEnaHard = 0;
		gCRam.bPwmClose = 1;
		gPLCCtl.ErrCode  = gRamSlv.Info.AlarmCode;
	}
#endif	//#if(CTLBOARD_TYPE == _1220_G4)
#endif	//_DEBUG_MODE
}

//串口数据输出,发送周期=20ms
void UARTPkt_DataOutManage(void)
{
	if(1)
	{
	#if (UART_LOGIC_TYPE == UART_LOGIC_MASTER)
		UARTPacketTx.wHead = 0xBBAA;
		UARTPacketTx.wFunc = 0x200;
		UARTPacketTx.wLength = sizeof(gRamMst.ucData);
		UARTPacketTx.pData = gRamMst.ucData;
		UARTPacketTx.Checksum = GetSum8_size(gRamMst.ucData,UARTPacketTx.wLength);

		UARTWriteBufArray(&uartTxBuffer,(unsigned char*)&UARTPacketTx,6);  //Headsize
		UARTWriteBufArray(&uartTxBuffer,UARTPacketTx.pData,UARTPacketTx.wLength);
		UARTWriteBufArray(&uartTxBuffer,&UARTPacketTx.Checksum,1);
		UARTSend(&uartTxBuffer);
	#endif	
	#if (UART_LOGIC_TYPE == UART_LOGIC_SLAVE)
		UARTPacketTx.wHead = 0xBBAA;
		UARTPacketTx.wFunc = 0x180;
		UARTPacketTx.wLength = (sizeof(gRamSlv.ucData) + 7);
		UARTPacketTx.pData = gRamSlv.ucData;
		UARTPacketTx.Checksum = GetSum8_size(gRamSlv.ucData,UARTPacketTx.wLength);	
		
		UARTWriteBufArray(&uartTxBuffer,(unsigned char*)&UARTPacketTx,6);  //Headsize
		UARTWriteBufArray(&uartTxBuffer,UARTPacketTx.pData,UARTPacketTx.wLength);
		UARTWriteBufArray(&uartTxBuffer,&UARTPacketTx.Checksum,1);
		UARTSend(&uartTxBuffer);		
	#endif
	}
}
void UpdataPlcDataFromUart(void)
{
}

void UpdataUartDataFromPlc(void)
{
	INT16U u16Temp;
#if (UART_LOGIC_TYPE == UART_LOGIC_MASTER)
	#if(CTLBOARD_TYPE == _1220_G4)
	gRamMst.Info.ControllWord = 0;
	if(SL_CHK(SL_TER_RDY) && (gCRam.AlmCode != 40))
		gRamMst.Info.ControllWord |= RDY_Stateword;
	else
		gRamMst.Info.ControllWord &= ~RDY_Stateword;
	
	switch(gPLCCtl.ThrottleType)  // 0 1 2
	{
		case AI_0_25_50V: 
			gRamMst.Info.ControllWord |= TYPE_0_25_50_Stateword;
			break;
		case AI_0_50V:
			gRamMst.Info.ControllWord |= TYPE_0_50_Stateword;
			break;
		case CMD_ENC:
			gRamMst.Info.ControllWord |= TYPE_ENC_stateword;			
			break;	
	}
	switch(gPara.CANBaudrate)
	{
		case 125:
			u16Temp = 1;
			break;
		case 250:
			u16Temp = 2;
			break;
		case 500:
			u16Temp = 3;
			break;
//		default:
//		break;
	}
		gRamMst.Info.SwiState = gPara.Switch;
		gRamMst.Info.Wiper1Voltage = gPara.Analog1;
		gRamMst.Info.Wiper2Voltage = gPara.Analog2;
	  	gRamMst.Info.CmdEncT =  (unsigned int)TIM_GetCounter(TIM4);
		gRamMst.Info.MotorEncoder = (unsigned int)TIM_GetCounter(TIM8);
		gRamMst.Info.CmdFor90DegreeCW = gCRam.PosCmdForMaxDegree; //CW
		gRamMst.Info.CmdFor90DegreeCCW = gCRam.PosCmdForRvsMaxDegree; //CCW limit
		#ifdef  CAN_BAUDRATE_PARA_ENABLE
		gRamMst.Info.SyncBaudrate = u16Temp;
		#endif
	#endif  //#if(CTLBOARD_TYPE == _1220_G4)
#endif //#if(UART_LOGIC_TYPE == UART_LOGIC_MASTER)

#if (UART_LOGIC_TYPE == UART_LOGIC_SLAVE)
		if(SL_CHK(PLC_SYS_ENABLE) && (gCRam.AlmCode != 40))
		gRamSlv.Info.Stateword |= RDY_Stateword;
	else
		gRamSlv.Info.Stateword &= ~RDY_Stateword;
		
	gRamSlv.Info.AlarmCode = gPara.ErrCode;

#endif	//#if(UART_LOGIC_TYPE == UART_LOGIC_SLAVE)

}

#endif //#if ((UART_LOGIC_TYPE == UART_LOGIC_MASTER) || (UART_LOGIC_TYPE == UART_LOGIC_SLAVE))
