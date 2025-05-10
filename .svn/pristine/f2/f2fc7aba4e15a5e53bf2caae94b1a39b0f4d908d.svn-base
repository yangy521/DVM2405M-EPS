/*******************************************************************************
* Filename: iCAN_slave.c	                                             	 		   *
* Description:											   			 		   *
* Author:                                                           		   *
* Date:     														 		   *
* Revision:															 		   *
*******************************************************************************/

#include  "iCAN.h"
#include	"iTimer.h"
#include	"canSTM32F4.h"
#include 	"message.h"
#include	"CommonRam.h"
#include 	"PLC.h"
#include	"PLCLogic.h"

#ifdef MICRO_CANOPEN
	extern CAN_MSG MEM_FAR gRxCAN;
#endif
//从站
tICANSlave icanSlave;	 //定义从站
tBoolean bConnectEnable;	//是否建立连接
static unsigned char bMacIDCheck_Err_Flag=0;

//从站节点初始化
void ICANInitialize_Slave()	
{
	//节点信息
	icanSlave.ucMacID=PRDUCT_TYPE;//gCRam.SvPa.StationAddr; //StationType		 //从站ID
	icanSlave.ucType=PRDUCT_TYPE;//gCRam.SvPa.StationAddr;	    //	从站产品类型
	icanSlave.ulSN=0x00;			//	从站产品序列号
	icanSlave.ucDILength=32;	//
	icanSlave.ucDOLength=32;	//
	icanSlave.ucAILength=0;	//
	icanSlave.ucAOLength=0;	//
	// 网络状态
	icanSlave.bIsConnect=false;			//是否与主站建立连接
	icanSlave.bIsOnline=false;			//
	icanSlave.ucStatus=ICAN_Slv_Idle;		//	镜像状态
	icanSlave.ucErrCount=0;		//	错误计数器	
	icanSlave.ucTime = 0;
	//接受缓冲区长度
	icanSlave.ucRxBufLength=0;	//	接受缓冲区长度

	//资源节点信息
	//DI
	icanSlave.ucSource0x00=0;
	icanSlave.ucSource0x01=0;
	icanSlave.ucSource0x02=0;
	icanSlave.ucSource0x03=0;
	icanSlave.ucSource0x04=0;
	icanSlave.ucSource0x05=0;
	icanSlave.ucSource0x06=0;
	icanSlave.ucSource0x07=0;
	icanSlave.ucSource0x08=0;
	icanSlave.ucSource0x09=0;
	icanSlave.ucSource0x0A=0;
	icanSlave.ucSource0x0B=0;
	icanSlave.ucSource0x0C=0;
	icanSlave.ucSource0x0D=0;
	//INDEX 1~6
	icanSlave.ucSource0x0E=0;	//PARAIndex1
	icanSlave.ucSource0x0F=0;	//PARAValueH1
	icanSlave.ucSource0x10=0;	//PARAValueL1
	icanSlave.ucSource0x11=0;	//PARAIndex2
	icanSlave.ucSource0x12=0;	//PARAValueH2
	icanSlave.ucSource0x13=0;	//PARAValueL2
	icanSlave.ucSource0x14=0;	//PARAIndex3
	icanSlave.ucSource0x15=0;	//PARAValueH3
	icanSlave.ucSource0x16=0;	//PARAValueL3
	icanSlave.ucSource0x17=0;	//PARAIndex4
	icanSlave.ucSource0x18=0;	//PARAValueH4
	icanSlave.ucSource0x19=0;	//PARAValueL4
  icanSlave.ucSource0x1A=0;	//PARAIndex5
	icanSlave.ucSource0x1B=0;	//PARAValueH5
	icanSlave.ucSource0x1C=0;	//PARAValueL5
  icanSlave.ucSource0x1D=0;	//PARAIndex6
	icanSlave.ucSource0x1E=0;	//PARAValueH6
	icanSlave.ucSource0x1F=0;	//PARAValueL6

  //DO
	icanSlave.ucSource0x20=0;	//仪表：PrdState
	icanSlave.ucSource0x21=0;	//仪表：ICANNetCfg
	icanSlave.ucSource0x22=0;	//仪表：ErrMove
	icanSlave.ucSource0x23=0;	//仪表：ErrLift
	icanSlave.ucSource0x24=0;	//仪表：ErrSteer
	icanSlave.ucSource0x25=0;	//仪表：ErrMoveSecond
	icanSlave.ucSource0x26=0;
	icanSlave.ucSource0x27=0;
	icanSlave.ucSource0x28=0;
	icanSlave.ucSource0x29=0;
	icanSlave.ucSource0x2A=0;
	icanSlave.ucSource0x2B=0;
	icanSlave.ucSource0x2C=0;
	icanSlave.ucSource0x2D=0;
	//INDEX 1~6
	icanSlave.ucSource0x2E=0;	//PARAIndex1
	icanSlave.ucSource0x2F=0;	//PARAValueH1 
	icanSlave.ucSource0x30=0; //PARAValueL1
	icanSlave.ucSource0x31=0;	//PARAIndex2
	icanSlave.ucSource0x32=0;	//PARAValueH2
	icanSlave.ucSource0x33=0;	//PARAValueL2
	icanSlave.ucSource0x34=0;	//DIPARAIndex3
	icanSlave.ucSource0x35=0;	//PARAValueH3
	icanSlave.ucSource0x36=0;	//PARAValueL3
	icanSlave.ucSource0x37=0;	//PARAIndex4
	icanSlave.ucSource0x38=0;	//PARAValueH4
	icanSlave.ucSource0x39=0;	//PARAValueL4
	icanSlave.ucSource0x3A=0;	//PARAIndex5
	icanSlave.ucSource0x3B=0;	//PARAValueH5
	icanSlave.ucSource0x3C=0;	//PARAValueL5
	icanSlave.ucSource0x3D=0;	//PARAIndex6
	icanSlave.ucSource0x3E=0;	//PARAValueH6
	icanSlave.ucSource0x3F=0;	//PARAValueL6	

	icanSlave.ucSource0xE2=0; //产品类型
	// 属性初始化
	bConnectEnable=true;
	//消息队列初始化
	MsgInitialize();

}

// 删除连接
void ICANDelConnection_Slave(void)
{
	icanSlave.bIsConnect=false;	
	bConnectEnable=false;
}

//MacID检测
void ICANMacIDCheck_Slave(void)
{
	tICANFrame icanFrame;

	//如果当前节点空闲，发送MacID检测帧
	if(icanSlave.ucStatus==ICAN_Slv_Idle)
	{
		icanFrame.ucSrcMacID=icanSlave.ucMacID;		//	原节点地址
		icanFrame.ucDestMacID=icanSlave.ucMacID;		//	目标节点地址
		icanFrame.ucACK=ICAN_ACK_Enable;			//	响应标示符
		icanFrame.ucFuncID=ICAN_Func_MacIDCheck;	//	功能码
		icanFrame.ucSourceID=0xFF;		//	MacIDCheck资源节点地址为0xFF
		icanFrame.ucDataLength=0x06;	//	有效数据长度
		//6字节数据
		icanFrame.ucData[0]=0x00;
		icanFrame.ucData[1]=icanSlave.ucMacID;
		icanFrame.ucData[2]=GetDataByte(icanSlave.ulSN,1);
		icanFrame.ucData[3]=GetDataByte(icanSlave.ulSN,2);
		icanFrame.ucData[4]=GetDataByte(icanSlave.ulSN,3);
		icanFrame.ucData[5]=GetDataByte(icanSlave.ulSN,4);

		icanSlave.ucStatus=ICAN_Slv_Post;
		SetNetTimer(Timer_MacIDCheck,100);	
		ICANSend(icanFrame);
	}

}

//ICAN接收
void ICANReceive_Slave(tICANSlave *pICANSlave,tCANFrame *pCANFrame)
{
	unsigned char ucSrcMacID;
	unsigned char ucACK;
	unsigned char ucFuncID;
	unsigned char ucSourceID;
//	tICANFrame icanFrame;

	ucSrcMacID = (pCANFrame->ulID >> 21) & 0x000000FF; // 原节点地址(ID28-ID21)
	ucACK = (pCANFrame->ulID >> 12) & 0x00000001; // 响应标示符(ID12) 
    ucFuncID = (pCANFrame->ulID >> 8) & 0x000000F; // 功能码(ID11-ID8) 
	ucSourceID = pCANFrame->ulID & 0x000000FF; // 资源节点地址(ID7-ID0)
//	ucDataLength=pCANFrame->ucDataLength;	//数据长度

	//如果未上线,只对MacID检测回馈做出响应 	
	if((icanSlave.bIsOnline==false)&&(ucFuncID==ICAN_Func_MacIDCheck))
	{
		if(ucACK==ICAN_ACK_Disable)	//接收到MacID回馈
		{
			pICANSlave->ucStatus=ICAN_Slv_Idle;
			SL_SET(ICAN_MACIDCHECK_ERR);
			MCL_SetFault(ICAN_MACIDCHECK_ERR);
			bMacIDCheck_Err_Flag=1;
			icanSlave.bIsOnline=false;
			KillNetTimer(Timer_MacIDCheck);
		}
/*		else	//
		{
			pICANSlave->ucStatus=ICAN_Slv_Idle;	//??????

			icanFrame.ucSrcMacID=icanSlave.ucMacID;		//	?????
			icanFrame.ucDestMacID=ucSrcMacID;		//	??????
			icanFrame.ucACK=ICAN_ACK_Disable;			//	?????
			icanFrame.ucFuncID=ICAN_Func_MacIDCheck;	//	???
			icanFrame.ucSourceID=0xFF;		//	MacIDCheck???????0xFF
			icanFrame.ucDataLength=0x06;	//	??????
			//6????
			icanFrame.ucData[0]=0x00;
			icanFrame.ucData[1]=icanSlave.ucMacID;
			icanFrame.ucData[2]=GetDataByte(icanSlave.ulSN,1);
			icanFrame.ucData[3]=GetDataByte(icanSlave.ulSN,2);
			icanFrame.ucData[4]=GetDataByte(icanSlave.ulSN,3);
			icanFrame.ucData[5]=GetDataByte(icanSlave.ulSN,4);
				 	
			ICANSend(icanFrame);
		}*/
	}

	//如果已上线，需要应答
	if((icanSlave.bIsOnline==true)&&(ucACK==ICAN_ACK_Enable))
	{
		//检测功能码
		if(ucFuncID==ICAN_Func_WritePort)  //连续写端口
		{
			if(icanSlave.bIsConnect)
			{
					if(pCANFrame->ucData[0]==0x00)	//没有分段
					{
						
						//接收完毕，注册消息
			     MsgICANRegister(0x00,Msg_WritePort);
					}								
					if(pCANFrame->ucData[0]==0x40)	//起始帧：分段帧第1帧
					{
						INT32S index;
						INT8U *pSrc, *pDst;
						pSrc = &pCANFrame->ucData[1];
						pDst = &pICANSlave->ucRxBuffer[0];
						for (index=0; index < 7; index++)
						{
							pDst[index] = pSrc[index];
						}
						pICANSlave->ucRxBufLength = 7;
					}
					else if(pCANFrame->ucData[0]==0x81)	//中间帧：分段帧第2帧
					{
						if (pICANSlave->ucRxBufLength == 7)
						{
							INT32S index;
							INT8U *pSrc, *pDst;
							pSrc = &pCANFrame->ucData[1];
							pDst = &pICANSlave->ucRxBuffer[7];
							for (index=0; index < 7; index++)
							{
								pDst[index] = pSrc[index];
							}
							pICANSlave->ucRxBufLength += 7;
						}
						else
							pICANSlave->ucRxBufLength = 0;
					}
					else if(pCANFrame->ucData[0]==0x82)	//中间帧：分段帧第3帧
					{
						if (pICANSlave->ucRxBufLength == 14)
						{
							INT32S index;
							INT8U *pSrc, *pDst;
							pSrc = &pCANFrame->ucData[1];
							pDst = &pICANSlave->ucRxBuffer[14];
							for (index=0; index < 7; index++)
							{
								pDst[index] = pSrc[index];
							}
							pICANSlave->ucRxBufLength += 7;
						}
						else
							pICANSlave->ucRxBufLength = 0;
					}
					else if(pCANFrame->ucData[0]==0x83)	//中间帧：分段帧第4帧
					{
						if (pICANSlave->ucRxBufLength == 21)
						{
							INT32S index;
							INT8U *pSrc, *pDst;
							pSrc = &pCANFrame->ucData[1];
							pDst = &pICANSlave->ucRxBuffer[21];
							for (index=0; index < 7; index++)
							{
								pDst[index] = pSrc[index];
							}
							pICANSlave->ucRxBufLength += 7;
						}
						else
							pICANSlave->ucRxBufLength = 0;
					}
					else if(pCANFrame->ucData[0]==0xC0)	//结尾帧：分段帧第5帧
					{
						if (pICANSlave->ucRxBufLength == 28)
						{
							INT32S index;
							INT8U *pSrc, *pDst;
							pSrc = &pCANFrame->ucData[1];
							pDst = &pICANSlave->ucRxBuffer[28];
							for (index=0; index < 4; index++)
							{
								pDst[index] = pSrc[index];
							}
							pICANSlave->ucRxBufLength = 0;

							pICANSlave->ucSource0x20=pICANSlave->ucRxBuffer[0];
							pICANSlave->ucSource0x21=pICANSlave->ucRxBuffer[1];
							pICANSlave->ucSource0x22=pICANSlave->ucRxBuffer[2];
							pICANSlave->ucSource0x23=pICANSlave->ucRxBuffer[3];
							pICANSlave->ucSource0x24=pICANSlave->ucRxBuffer[4];
							pICANSlave->ucSource0x25=pICANSlave->ucRxBuffer[5];
							pICANSlave->ucSource0x26=pICANSlave->ucRxBuffer[6];
							pICANSlave->ucSource0x27=pICANSlave->ucRxBuffer[7];
							pICANSlave->ucSource0x28=pICANSlave->ucRxBuffer[8];
							pICANSlave->ucSource0x29=pICANSlave->ucRxBuffer[9];
							pICANSlave->ucSource0x2A=pICANSlave->ucRxBuffer[10];
							pICANSlave->ucSource0x2B=pICANSlave->ucRxBuffer[11];
							pICANSlave->ucSource0x2C=pICANSlave->ucRxBuffer[12];
							pICANSlave->ucSource0x2D=pICANSlave->ucRxBuffer[13];
							pICANSlave->ucSource0x2E=pICANSlave->ucRxBuffer[14];
							pICANSlave->ucSource0x2F=pICANSlave->ucRxBuffer[15];
							pICANSlave->ucSource0x30=pICANSlave->ucRxBuffer[16];
							pICANSlave->ucSource0x31=pICANSlave->ucRxBuffer[17];
							pICANSlave->ucSource0x32=pICANSlave->ucRxBuffer[18];
							pICANSlave->ucSource0x33=pICANSlave->ucRxBuffer[19];
							pICANSlave->ucSource0x34=pICANSlave->ucRxBuffer[20];
							pICANSlave->ucSource0x35=pICANSlave->ucRxBuffer[21];
							pICANSlave->ucSource0x36=pICANSlave->ucRxBuffer[22];
							pICANSlave->ucSource0x37=pICANSlave->ucRxBuffer[23];
							pICANSlave->ucSource0x38=pICANSlave->ucRxBuffer[24];
							pICANSlave->ucSource0x39=pICANSlave->ucRxBuffer[25];
							pICANSlave->ucSource0x3A=pICANSlave->ucRxBuffer[26];
							pICANSlave->ucSource0x3B=pICANSlave->ucRxBuffer[27];
							pICANSlave->ucSource0x3C=pICANSlave->ucRxBuffer[28];
							pICANSlave->ucSource0x3D=pICANSlave->ucRxBuffer[29];
							pICANSlave->ucSource0x3E=pICANSlave->ucRxBuffer[30];
							pICANSlave->ucSource0x3F=pICANSlave->ucRxBuffer[31];
						}
						else
							pICANSlave->ucRxBufLength = 0;
						
						//接收完毕，注册消息
			      MsgICANRegister(0x00,Msg_WritePort);						
					}		
			
				pICANSlave->ucStatus=ICAN_Slv_Idle;
				ResetNetTimer(Timer_Connect);

		}
			else
			{
				MsgICANRegister(0x00,Msg_ErrAck);
				pICANSlave->ucStatus=ICAN_Slv_Idle;
			}
	}
		else if(ucFuncID==ICAN_Func_ReadPort)  //连续读端口
		{
			if(icanSlave.bIsConnect)
			{
				if(ucSourceID==0x00)
				{
					//MsgRegister(Msg_Type_ICAN,0x00,Msg_ReadPort);
					MsgICANRegister(0x00,Msg_ReadPort);
				}
				if(ucSourceID==0xE2)
				{
					//MsgRegister(Msg_Type_ICAN,0x00,Msg_ReadPrdType);
					MsgICANRegister(0x00,Msg_ReadPrdType);
				}
				pICANSlave->ucStatus=ICAN_Slv_Idle;
				ResetNetTimer(Timer_Connect);
			}
			else
			{
				//MsgRegister(Msg_Type_ICAN,0x00,Msg_ErrAck);
					MsgICANRegister(0x00,Msg_ErrAck);
				pICANSlave->ucStatus=ICAN_Slv_Idle;
			}		
		}
		else if(ucFuncID==ICAN_Func_TransTriger)  //事件触发传输
		{
		}
		else if(ucFuncID==ICAN_Func_SetConnect)  //建立连接
		{
			if(bConnectEnable)
			{
				//MsgRegister(Msg_Type_ICAN,0x00,Msg_SetConnect);
				MsgICANRegister(0x00,Msg_SetConnect);
				pICANSlave->ucStatus=ICAN_Slv_Idle;
				pICANSlave->bIsConnect=true;	//设置建立连接
			}
		}
		else if(ucFuncID==ICAN_Func_DelConnect)  //删除连接
		{
		}
		else if(ucFuncID==ICAN_Func_SlvReset)	//设备复位
		{
		}
		else if(ucFuncID==ICAN_Func_MacIDCheck)  //MACID检测
		{
			//MsgICANRegister(Msg_Type_ICAN,ucSrcMacID,Msg_MacIDCheck);
			MsgICANRegister(ucSrcMacID,Msg_MacIDCheck);
			pICANSlave->ucStatus=ICAN_Slv_Idle;	//设置节点状态
		}
	}			

}

void ICANDataInManage_Slave(void)
{	
	unsigned char ucDestMacID;
	unsigned char ucSrcMacID;
	unsigned char ucACK;
	unsigned char ucFuncID;
 	tCANFrame canFrame;	//
	tICANFrame icanFrame;
	//从CAN数据缓冲区中读取CAN数据帧，放入相应的子站镜像中
	//if(fReadEnable)
	{
		while(CANReadBuffer(&canFrmRxBuffer,&canFrame)!=EMPTY)//读取CAN数据接收缓冲区
		{	
			if (canFrame.ucXID == 0)
			{//标准帧头
				CanOpenRxFrame(&canFrame);
				#ifdef MICRO_CANOPEN
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
				#endif
				continue;
			}
			ucSrcMacID = (canFrame.ulID >> 21) & 0x000000FF; // 原节点地址(ID28-ID21)
			ucDestMacID = (canFrame.ulID >> 13) & 0x000000FF; // 目标节点编号(ID20-ID13) 			
			ucACK = (canFrame.ulID >> 12) & 0x00000001; // 响应标示符(ID12) 
			ucFuncID = (canFrame.ulID >> 8) & 0x000000F; // 功能码(ID11-ID8) 
			//从站先上电，从站回馈主站并在主站添加该从站
		//	if(ucSrcMacID==0x00 && ucFuncID==ICAN_Func_MacIDCheck)
			if((ucSrcMacID==0x00 ||ucSrcMacID==icanSlave.ucMacID )&& ucFuncID==ICAN_Func_MacIDCheck)
			{
				if(ucACK==ICAN_ACK_Enable)
				{
					icanFrame.ucSrcMacID=icanSlave.ucMacID;		//	原节点地址
					icanFrame.ucDestMacID=icanSlave.ucMacID;		//	目标节点地址
					icanFrame.ucACK=ICAN_ACK_Disable;			//	响应标示符
					icanFrame.ucFuncID=ICAN_Func_MacIDCheck;	//	功能码
					icanFrame.ucSourceID=0xFF;		//	MacIDCheck资源节点地址为0xFF
					icanFrame.ucDataLength=0x06;	//	有效数据长度
					//6字节数据
					icanFrame.ucData[0]=0x00;
					icanFrame.ucData[1]=icanSlave.ucMacID;
					icanFrame.ucData[2]=GetDataByte(icanSlave.ulSN,1);
					icanFrame.ucData[3]=GetDataByte(icanSlave.ulSN,2);
					icanFrame.ucData[4]=GetDataByte(icanSlave.ulSN,3);
					icanFrame.ucData[5]=GetDataByte(icanSlave.ulSN,4);

					if(ucSrcMacID==icanSlave.ucMacID)
						icanSlave.ucStatus=ICAN_Slv_Post;
					ICANSend(icanFrame);
				}
			}
			
			if(ucDestMacID==icanSlave.ucMacID)
			{
				ICANReceive_Slave(&icanSlave,&canFrame);	//ICAN接收
	//	fReadEnable=false;
			}  
		}
	}  	
}

//
void ICANNetManage_Slave(void)
{

	//MacID检测超时处理
	if(netTimer[Timer_MacIDCheck].bIsOvertime)
	{
		icanSlave.bIsOnline=true;
		icanSlave.ucStatus=ICAN_Slv_Idle;
		KillNetTimer(Timer_MacIDCheck);
	}
	//启动发送定时器
	if(icanSlave.bIsConnect&&(netTimer[Timer_Connect].bIsStart==false))
	{
//    SetNetTimer(Timer_Connect,200);
		SetNetTimer(Timer_Connect,1000);
	}
	//从站连接通信超时处理
	if(netTimer[Timer_Connect].bIsOvertime && icanSlave.bIsConnect) //
	{
		icanSlave.bIsConnect=false;	//断开连接
		KillNetTimer(Timer_Connect);
		//复位资源节点
		//节点信息
		icanSlave.ucDILength=27;	//
		icanSlave.ucDOLength=32;	//
		icanSlave.ucAILength=0;	//
		icanSlave.ucAOLength=0;	//
		//网络状态
		icanSlave.bIsConnect=false;			//断开连接
		icanSlave.ucStatus=ICAN_Slv_Idle;		//	从站镜像状态
		icanSlave.ucErrCount=0;		//	错误计数器
		icanSlave.ucTime = 0;
		//数据信息
		icanSlave.ucRxBufLength=0;	//从站接受缓冲区长度
		
		//资源节点信息
		//DI
		icanSlave.ucSource0x00=0;
		icanSlave.ucSource0x01=0;
		icanSlave.ucSource0x02=0;
		icanSlave.ucSource0x03=0;
		icanSlave.ucSource0x04=0;
		icanSlave.ucSource0x05=0;
		icanSlave.ucSource0x06=0;
		icanSlave.ucSource0x07=0;
		icanSlave.ucSource0x08=0;
		icanSlave.ucSource0x09=0;
		icanSlave.ucSource0x0A=0;
		icanSlave.ucSource0x0B=0;
		icanSlave.ucSource0x0C=0;
		icanSlave.ucSource0x0D=0;
		//INDEX 1~6
		icanSlave.ucSource0x0E=0;	//PARAIndex1
		icanSlave.ucSource0x0F=0;	//PARAValueH1
		icanSlave.ucSource0x10=0;	//PARAValueL1
		icanSlave.ucSource0x11=0;	//PARAIndex2
		icanSlave.ucSource0x12=0;	//PARAValueH2
		icanSlave.ucSource0x13=0;	//PARAValueL2
		icanSlave.ucSource0x14=0;	//PARAIndex3
		icanSlave.ucSource0x15=0;	//PARAValueH3
		icanSlave.ucSource0x16=0;	//PARAValueL3
		icanSlave.ucSource0x17=0;	//PARAIndex4
		icanSlave.ucSource0x18=0;	//PARAValueH4
		icanSlave.ucSource0x19=0;	//PARAValueL4
		icanSlave.ucSource0x1A=0;	//PARAIndex5
		icanSlave.ucSource0x1B=0;	//PARAValueH5
		icanSlave.ucSource0x1C=0;	//PARAValueL5
		icanSlave.ucSource0x1D=0;	//PARAIndex6
		icanSlave.ucSource0x1E=0;	//PARAValueH6
		icanSlave.ucSource0x1F=0;	//PARAValueL6

		//DO
		icanSlave.ucSource0x20=0;	//仪表：PrdState
		icanSlave.ucSource0x21=0;	//仪表：ICANNetCfg
		icanSlave.ucSource0x22=0;	//仪表：ErrMove
		icanSlave.ucSource0x23=0;	//仪表：ErrLift
		icanSlave.ucSource0x24=0;	//仪表：ErrSteer
		icanSlave.ucSource0x25=0;	//仪表：ErrMoveSecond
		icanSlave.ucSource0x26=0;
		icanSlave.ucSource0x27=0;
		icanSlave.ucSource0x28=0;
		icanSlave.ucSource0x29=0;
		icanSlave.ucSource0x2A=0;
		icanSlave.ucSource0x2B=0;
		icanSlave.ucSource0x2C=0;
		icanSlave.ucSource0x2D=0;
		//INDEX 1~6
		icanSlave.ucSource0x2E=0;	//PARAIndex1
		icanSlave.ucSource0x2F=0;	//PARAValueH1 
		icanSlave.ucSource0x30=0; //PARAValueL1
		icanSlave.ucSource0x31=0;	//PARAIndex2
		icanSlave.ucSource0x32=0;	//PARAValueH2
		icanSlave.ucSource0x33=0;	//PARAValueL2
		icanSlave.ucSource0x34=0;	//DIPARAIndex3
		icanSlave.ucSource0x35=0;	//PARAValueH3
		icanSlave.ucSource0x36=0;	//PARAValueL3
		icanSlave.ucSource0x37=0;	//PARAIndex4
		icanSlave.ucSource0x38=0;	//PARAValueH4
		icanSlave.ucSource0x39=0;	//PARAValueL4
		icanSlave.ucSource0x3A=0;	//PARAIndex5
		icanSlave.ucSource0x3B=0;	//PARAValueH5
		icanSlave.ucSource0x3C=0;	//PARAValueL5
		icanSlave.ucSource0x3D=0;	//PARAIndex6
		icanSlave.ucSource0x3E=0;	//PARAValueH6
		icanSlave.ucSource0x3F=0;	//PARAValueL6	
	
		MsgFlush();
	}
}

 /********************************************************************
  * 函数名: 	ICAN_DOProc()
  * 参数:   	pICANSlave 从站镜像
  * 功能描述：DO发送Source0x20~Source0x3F
  * 返回值：	NULL
  ********************************************************************/
	void ICAN_DOProc_Slave(tICANSlave *pICANSlave)
{
		unsigned long  ucSrcMacID;	//	源节点地址
		unsigned long  ucDestMacID;	//	目标节点地址
		unsigned long  ucACK;		//	响应标识位
		unsigned long  ucFuncID;	//	功能码
		unsigned long  ucSourceID;		//	资源节点地址
		tCANFrame canFrame;	//
	
			ucSrcMacID=icanSlave.ucMacID;		//	源节点地址;
			ucDestMacID=0x00;//pICANSlave->ucMacID;		//	目标节点地址
			ucACK=ICAN_ACK_Disable;			//	响应标识位;
			ucFuncID=ICAN_Func_ReadPort;	//	功能码
			ucSourceID=0x00;		//	资源节点——DO地址为0x20
		//	icanFrame.ucDataLength=icanSlave.ucDILength+1;	//
	
			canFrame.ulID=(ucSrcMacID<<21)+(ucDestMacID<<13)+(ucACK<<12)+(ucFuncID<<8)+ucSourceID;
			canFrame.ucXID=1;			//0 标准帧；1 扩展帧 
			canFrame.ucDataLength=8;
				
			canFrame.ucData[0]=0x40;	//1000 0001
			canFrame.ucData[1]=pICANSlave->ucSource0x00;
			canFrame.ucData[2]=pICANSlave->ucSource0x01;
			canFrame.ucData[3]=pICANSlave->ucSource0x02;	//
			canFrame.ucData[4]=pICANSlave->ucSource0x03;	//
			canFrame.ucData[5]=pICANSlave->ucSource0x04;	//
			canFrame.ucData[6]=pICANSlave->ucSource0x05;	//
			canFrame.ucData[7]=pICANSlave->ucSource0x06;	//
			CANWriteBuffer(&canFrmTxBuffer, &canFrame);

			canFrame.ucData[0]=0x81;	//1000 0001
			canFrame.ucData[1]=pICANSlave->ucSource0x07;
			canFrame.ucData[2]=pICANSlave->ucSource0x08;
			canFrame.ucData[3]=pICANSlave->ucSource0x09;	//
			canFrame.ucData[4]=pICANSlave->ucSource0x0A;	//
			canFrame.ucData[5]=pICANSlave->ucSource0x0B;	//
			canFrame.ucData[6]=pICANSlave->ucSource0x0C;	//
			canFrame.ucData[7]=pICANSlave->ucSource0x0D;	//
			CANWriteBuffer(&canFrmTxBuffer, &canFrame);

			canFrame.ucData[0]=0x82;	//1000 0001
			canFrame.ucData[1]=pICANSlave->ucSource0x0E;
			canFrame.ucData[2]=pICANSlave->ucSource0x0F;
			canFrame.ucData[3]=pICANSlave->ucSource0x10;	//
			canFrame.ucData[4]=pICANSlave->ucSource0x11;
			canFrame.ucData[5]=pICANSlave->ucSource0x12;	//
			canFrame.ucData[6]=pICANSlave->ucSource0x13;	//
			canFrame.ucData[7]=pICANSlave->ucSource0x14;	//
				CANWriteBuffer(&canFrmTxBuffer, &canFrame);

			canFrame.ucData[0]=0x83;	//1000 0001
			canFrame.ucData[1]=pICANSlave->ucSource0x15;
			canFrame.ucData[2]=pICANSlave->ucSource0x16;
			canFrame.ucData[3]=pICANSlave->ucSource0x17;	//
			canFrame.ucData[4]=pICANSlave->ucSource0x18;	//
			canFrame.ucData[5]=pICANSlave->ucSource0x19;	//
			canFrame.ucData[6]=pICANSlave->ucSource0x1A;	//
			canFrame.ucData[7]=pICANSlave->ucSource0x1B;	//
			CANWriteBuffer(&canFrmTxBuffer, &canFrame);

			canFrame.ucData[0]=0xC0;	//1100 0000
			canFrame.ucData[1]=pICANSlave->ucSource0x1C;
			canFrame.ucData[2]=pICANSlave->ucSource0x1D;
			canFrame.ucData[3]=pICANSlave->ucSource0x1E;	//
			canFrame.ucData[4]=pICANSlave->ucSource0x1F;	//
			canFrame.ucData[5]=0x00;	//
			canFrame.ucData[6]=0x00;	//
			canFrame.ucData[7]=0x00;	//
			CANWriteBuffer(&canFrmTxBuffer, &canFrame);
			
//			CANFrmSend(&canFrmTxBuffer);	
}

//
void ICANDataOutManage_Slave(void)
{	
	tICANFrame icanFrame;
	tMessage message;

	//
	//MacID检测
	//
	if(icanSlave.bIsOnline==false)
	{
	//	if(!SL_CHK(ICAN_MACIDCHECK_ERR))
		if(bMacIDCheck_Err_Flag==0)
		{
			ICANMacIDCheck_Slave();
		}
		return;
	}
	//ICAN消息事件处理
	if((icanSlave.ucStatus==ICAN_Slv_Idle)&&(icanSlave.bIsConnect==true))	//判断节点是否空闲
	{
		while(MsgICANPop(&message))
		{	
			if(message.ucMsgEvent==Msg_MacIDCheck)
			{
				icanFrame.ucSrcMacID=icanSlave.ucMacID;		//	源节点地址
				icanFrame.ucDestMacID=message.ucMsgMacID;		//	目标节点地址
				icanFrame.ucACK=ICAN_ACK_Disable;			//	响应标示符
				icanFrame.ucFuncID=ICAN_Func_MacIDCheck;	//	功能码
				icanFrame.ucSourceID=0xFF;		//	MacIDCheck资源节点地址为0xFF
				icanFrame.ucDataLength=0x06;	//	
				//6
				icanFrame.ucData[0]=0x00;
				icanFrame.ucData[1]=icanSlave.ucMacID;
				icanFrame.ucData[2]=GetDataByte(icanSlave.ulSN,1);
				icanFrame.ucData[3]=GetDataByte(icanSlave.ulSN,2);
				icanFrame.ucData[4]=GetDataByte(icanSlave.ulSN,3);
				icanFrame.ucData[5]=GetDataByte(icanSlave.ulSN,4);
				 	
				ICANSend(icanFrame);
				return;
			}
			if(message.ucMsgEvent==Msg_SetConnect)
			{
				icanFrame.ucSrcMacID=icanSlave.ucMacID;		//	源节点地址
				icanFrame.ucDestMacID=message.ucMsgMacID;		//	目标节点地址
				icanFrame.ucACK=ICAN_ACK_Disable;			//	响应标示符
				icanFrame.ucFuncID=ICAN_Func_SetConnect;	//	功能码
				icanFrame.ucSourceID=0xF7;		//	
				icanFrame.ucDataLength=5;	//	
				icanFrame.ucData[0]=0x00;	//
				icanFrame.ucData[1]=icanSlave.ucDILength;
				icanFrame.ucData[2]=icanSlave.ucDOLength;
				icanFrame.ucData[3]=icanSlave.ucAILength;
				icanFrame.ucData[4]=icanSlave.ucAOLength;
				 	
				ICANSend(icanFrame);
				return;
			}
			if(message.ucMsgEvent==Msg_ReadPort)
			{				
				icanSlave.ucStatus=ICAN_Slv_Post;	
				
				ICAN_DOProc_Slave(&icanSlave); //DO
				return;
			}		
			if(message.ucMsgEvent==Msg_WritePort)
			{
				icanFrame.ucSrcMacID=icanSlave.ucMacID;		//	源节点地址
				icanFrame.ucDestMacID=message.ucMsgMacID;		//	目标节点地址
				icanFrame.ucACK=ICAN_ACK_Disable;			//	响应标示符
				icanFrame.ucFuncID=ICAN_Func_WritePort;	//	功能码
				icanFrame.ucSourceID=0x20;		//	
				icanFrame.ucDataLength=1;	//	
				icanFrame.ucData[0]=0x00;	//
				 	
				ICANSend(icanFrame);

				return;
			}
			if(message.ucMsgEvent==Msg_ErrAck)
			{
				icanFrame.ucSrcMacID=icanSlave.ucMacID;		//	源节点地址
				icanFrame.ucDestMacID=message.ucMsgMacID;		//	目标节点地址
				icanFrame.ucACK=ICAN_ACK_Disable;			//	响应标示符
				icanFrame.ucFuncID=ICAN_Func_ErrAck;	//	功能码
				icanFrame.ucSourceID=0xFF;		//	
				icanFrame.ucDataLength=2;	//	
				icanFrame.ucData[0]=0x00;	//
				icanFrame.ucData[1]=ICAN_Ack_ErrConnect;
				 	
				ICANSend(icanFrame);
				return;
			}						
		}
	}	
}


