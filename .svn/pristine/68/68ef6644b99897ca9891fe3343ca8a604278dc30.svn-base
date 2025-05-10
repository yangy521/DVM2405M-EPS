/*******************************************************************************
* Filename: iCAN_master.c	                                             	 		   *
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
#include 	"PLCLogic.h"

#ifdef MICRO_CANOPEN
	extern CAN_MSG MEM_FAR gRxCAN;
#endif

tICANMaster	icanMaster;			//定义主站

void ICANInitialize_Master()	
{
	//消息队列初始化
  //MsgInitialize();
	
	//主站节点初始化
	icanMaster.ucMacID=0x00;	//
	icanMaster.ucBand=CANBAUD_500K;	//
	icanMaster.ucCycle=1;	//
	icanMaster.ucType=Prd_Move;	//
	icanMaster.ulSN=0x00;	//
	icanMaster.bIsOnline=false;	//
	icanMaster.ucSlvArrLength=1;	//
	icanMaster.ucCurSlvIndex=0;
	//CAN缓冲区初始化
	canFrmRxBuffer.ucWrite=0;	    //当前写位置
	canFrmRxBuffer.ucRead=0;	    //当前读位置
	canFrmTxBuffer.ucWrite=0;	    //当前写位置
	canFrmTxBuffer.ucRead=0;	    //当前读位置
	
}


//添加从站镜像
void ICANAddSlave(INT8U ucMacID, INT8U ucProductType)
{
	INT8U i;
	tICANSlave *pSlave;
	//如果已存在于从站镜像列表中，退出
	for(i=1;i<icanMaster.ucSlvArrLength;i++)
	{
		if(ucMacID==icanMaster.pICANSlvArray[i].ucMacID)
		{
			return;
		}
	}
	if (icanMaster.ucSlvArrLength >= (sizeof(icanMaster.pICANSlvArray)/sizeof(icanMaster.pICANSlvArray[0])))
		return;
	//
	pSlave=icanMaster.pICANSlvArray + icanMaster.ucSlvArrLength;
	//节点信息
	pSlave->ucMacID=ucMacID;			 //	从站ID
	pSlave->ucType=ucProductType;	    //	从站产品类型
	pSlave->ulSN=0x00;			//	从站产品序列号
	pSlave->ucDILength=0;	//
	pSlave->ucDOLength=0;	//
	pSlave->ucAILength=0;	//
	pSlave->ucAOLength=0;	//
	//网络状态
	pSlave->bIsConnect=false;			//	是否与主站建立连接
	pSlave->ucStatus=ICAN_Slv_Idle;		//	从站节点镜像状态
	//接收数据缓冲
	pSlave->ucRxBufLength=0;	//从站的接收数据缓冲区有效长度
	//数据信息
	pSlave->ucDataAddress=ICAN_Addr_DI;	//
	//资源节点信息
	pSlave->ucSource0x00=0x00;	//0x00
	pSlave->ucSource0x01=0x00;	//0x01
	pSlave->ucSource0x02=0;	//0x02
	pSlave->ucSource0x03=0x00;	//0x03
	pSlave->ucSource0x20=0x00;	//0x20
	pSlave->ucSource0x21=0x00;	//0x21
	pSlave->ucSource0xE2=0x00;	//0xE2

	icanMaster.ucSlvArrLength++;	
}

//ICAN网络删除子站
void ICANDelSlave(INT8U ucMacID)
{
	INT8U i;
	if(ucMacID==MACID_TOTAL)	//删除所有从站
	{
		for(i=1;i<icanMaster.ucSlvArrLength;i++)
		{
			//节点信息
			icanMaster.pICANSlvArray[i].ucMacID=0x00;			 //	从站ID
			icanMaster.pICANSlvArray[i].ucType=0x00;	    //	从站产品类型
			icanMaster.pICANSlvArray[i].ulSN=0x00;			//	从站产品序列号
			icanMaster.pICANSlvArray[i].ucDILength=0;	//
			icanMaster.pICANSlvArray[i].ucDOLength=0;	//
			icanMaster.pICANSlvArray[i].ucAILength=0;	//
			icanMaster.pICANSlvArray[i].ucAOLength=0;	//
			//网络状态
			icanMaster.pICANSlvArray[i].bIsConnect=false;			//	是否与主站建立连接
			icanMaster.pICANSlvArray[i].ucStatus=ICAN_Slv_Idle;		//	从站节点镜像状态
			//数据信息
			icanMaster.pICANSlvArray[i].ucDataAddress=ICAN_Addr_DI;	//
			icanMaster.pICANSlvArray[i].ucRxBufLength=0;	//从站的接收数据缓冲区有效长度
			//资源节点信息
			icanMaster.pICANSlvArray[i].ucSource0x00=0x00;	//0x00
			icanMaster.pICANSlvArray[i].ucSource0x01=0x00;	//0x01
			icanMaster.pICANSlvArray[i].ucSource0x02=0;		//0x02
			icanMaster.pICANSlvArray[i].ucSource0x03=0x00;	//0x03
			icanMaster.pICANSlvArray[i].ucSource0x20=0x00;	//0x20
			icanMaster.pICANSlvArray[i].ucSource0x21=0x00;	//0x21
			icanMaster.pICANSlvArray[i].ucSource0xE2=0x00;	//0xE2
		}
		icanMaster.ucSlvArrLength=1;
		icanMaster.ucCurSlvIndex=0;
	}
	else if(ucMacID>0&&ucMacID<64) //删除单个从站	kff
	{
			
	}	
}

//ICAN发送
void ICANSend(tICANFrame icanFrame)
{
	INT8U i;
	unsigned long  ucSrcMacID;	//	源节点地址
	unsigned long  ucDestMacID;	//	目标节点地址
	unsigned long  ucACK;		//	响应标识位
	unsigned long  ucFuncID;	//	功能码
	unsigned long  ucSourceID;		//	资源节点地址
	tCANFrame canFrame;	//

	ucSrcMacID=icanFrame.ucSrcMacID;
	ucDestMacID=icanFrame.ucDestMacID;
	ucACK=icanFrame.ucACK;
	ucFuncID=icanFrame.ucFuncID;
	ucSourceID=icanFrame.ucSourceID;
		
	canFrame.ulID=(ucSrcMacID<<21)+(ucDestMacID<<13)+(ucACK<<12)+(ucFuncID<<8)+ucSourceID;
	canFrame.ucXID=1;			//0 标准帧；1 扩展帧  
    canFrame.ucDataLength=icanFrame.ucDataLength;		//数据场长度
	//
	for(i=0;i<icanFrame.ucDataLength;i++)
	{
		canFrame.ucData[i]=icanFrame.ucData[i];
	}

	CANWriteBuffer(&canFrmTxBuffer, &canFrame);
//	CANFrmSend(&canFrmTxBuffer);	
}

//MacID检测
void ICANMacIDCheck(void)
{
	tICANFrame icanFrame;

	icanFrame.ucSrcMacID=icanMaster.ucMacID;		//	源节点地址
	icanFrame.ucDestMacID=icanMaster.ucMacID;		//	目标节点地址
	icanFrame.ucACK=ICAN_ACK_Enable;			//	响应标识位
	icanFrame.ucFuncID=ICAN_Func_MacIDCheck;	//	功能码
	icanFrame.ucSourceID=0xFF;		//	MacIDCheck资源节点地址为0xFF
	icanFrame.ucDataLength=0x06;	//	有效数据长度
	//6字节数据
	icanFrame.ucData[0]=0x00;
	icanFrame.ucData[1]=icanMaster.ucMacID;
	icanFrame.ucData[2]=GetDataByte(icanMaster.ulSN,1);
	icanFrame.ucData[3]=GetDataByte(icanMaster.ulSN,2);
	icanFrame.ucData[4]=GetDataByte(icanMaster.ulSN,3);
	icanFrame.ucData[5]=GetDataByte(icanMaster.ulSN,4);

//	if(netTimer[Timer_MacIDCheck].bIsStart==false)
	{
		SetNetTimer(Timer_MacIDCheck,100);
	}
	icanMaster.ucStatus=ICAN_Slv_Post;
	ICANSend(icanFrame);
}

//ICAN建立连接
void ICANSetConnect(tICANSlave *pICANSlave)
{
	tICANFrame icanFrame;

	if(pICANSlave->ucStatus==ICAN_Slv_Idle)
	{
		icanFrame.ucSrcMacID=icanMaster.ucMacID;		//	源节点地址
		icanFrame.ucDestMacID=pICANSlave->ucMacID;		//	目标节点地址
		icanFrame.ucACK=ICAN_ACK_Enable;			//	响应标识位
		icanFrame.ucFuncID=ICAN_Func_SetConnect;	//	功能码
		icanFrame.ucSourceID=0xF7;		//	SetConnect资源节点地址为0xF7
		icanFrame.ucDataLength=0x03;	//	有效数据长度
		icanFrame.ucData[0]=0x00;	//3字节数据
		icanFrame.ucData[1]=icanMaster.ucMacID;
 		icanFrame.ucData[2]=0xFF;	//主站通讯定时参数为，单位10ms

		pICANSlave->ucStatus=ICAN_Slv_Post;

		pICANSlave->icanFrame.ucSrcMacID=icanMaster.ucMacID;		//	源节点地址
		pICANSlave->icanFrame.ucDestMacID=pICANSlave->ucMacID;		//	目标节点地址
		pICANSlave->icanFrame.ucACK=ICAN_ACK_Enable;			//	响应标识位
		pICANSlave->icanFrame.ucFuncID=ICAN_Func_SetConnect;	//	功能码
		pICANSlave->icanFrame.ucSourceID=0xF7;		//	SetConnect资源节点地址为0xF7
		pICANSlave->icanFrame.ucDataLength=0x03;	//	有效数据长度
		pICANSlave->icanFrame.ucData[0]=0x00;	//3字节数据
		pICANSlave->icanFrame.ucData[1]=icanMaster.ucMacID;
 		pICANSlave->icanFrame.ucData[2]=0xFF;	//主站通讯定时参数为，单位10ms
		pICANSlave->icanFrame.ucData[3]=0x00;
		pICANSlave->icanFrame.ucData[4]=0x00;
		pICANSlave->icanFrame.ucData[5]=0x00;
		pICANSlave->icanFrame.ucData[6]=0x00;
		pICANSlave->icanFrame.ucData[7]=0x00;

		ICANSend(icanFrame);
	}
}

//ICAN接收
void ICANReceive(tICANSlave *pICANSlave,tCANFrame *pCANFrame)
{
//	INT8U i;
//	INT8U ucSrcMacID;
	INT8U ucACK;
	INT8U ucFuncID;
	INT8U ucSourceID;
//	INT8U ucDataLength;
	tICANFrame icanFrame;
	
//	ucSrcMacID = (pCANFrame->ulID >> 21) & 0x000000FF; // 原节点地址(ID28-ID21)
	ucACK = (pCANFrame->ulID >> 12) & 0x00000001; // 应答标志（ID12） 
    ucFuncID = (pCANFrame->ulID >> 8) & 0x000000F; // 功能码（ID11－ID8） 
	ucSourceID = pCANFrame->ulID & 0x000000FF; // 资源节点编号（ID7－ID0）
//	ucDataLength=pCANFrame->ucDataLength;	//数据长度

	//如果主站未上线，只对MacID检测作出回应
	if(icanMaster.bIsOnline==false)
	{
		if(ucFuncID!=ICAN_Func_MacIDCheck)
		{
			return;
		}
	}

	//需要应答(从站的MACID检测帧）	
	if(ucACK==ICAN_ACK_Enable) 
	{
		//判断功能码
		if(ucFuncID==ICAN_Func_MacIDCheck)	//从站MACID检测
		{
			if(icanMaster.ucMacID==pICANSlave->ucMacID)	//MACID检测有效
			{
				//发送MACID应答帧
				icanFrame.ucSrcMacID=icanMaster.ucMacID;		//	源节点地址
				icanFrame.ucDestMacID=pICANSlave->ucMacID;		//	目标节点地址
				icanFrame.ucACK=ICAN_ACK_Disable;			//	响应标识位
				icanFrame.ucFuncID=ICAN_Func_MacIDCheck;	//	功能码
				icanFrame.ucSourceID=0xFF;		//	MacIDCheck资源节点地址为0xFA
				icanFrame.ucDataLength=0x06;	//	有效数据长度
				//6字节数据
				icanFrame.ucData[0]=0x00;
				icanFrame.ucData[1]=icanMaster.ucMacID;
				icanFrame.ucData[2]=GetDataByte(icanMaster.ulSN,1);
				icanFrame.ucData[3]=GetDataByte(icanMaster.ulSN,2);
				icanFrame.ucData[4]=GetDataByte(icanMaster.ulSN,3);
				icanFrame.ucData[5]=GetDataByte(icanMaster.ulSN,4);
			
				ICANSend(icanFrame);
			}
		}	
	}
	//不需要应答
	if(ucACK==ICAN_ACK_Disable)
	{
		//检测功能码
		if(ucFuncID==ICAN_Func_WritePort)  //连续写端口
		{
			//delete 20150311
		//if((ucFuncID==pICANSlave->icanFrame.ucFuncID)&&(ucSourceID==pICANSlave->icanFrame.ucSourceID))
			{
				pICANSlave->ucStatus=ICAN_Slv_Idle;	//设置节点状态
				ResetNetTimer(pICANSlave->ucMacID);  //复位发送超时定时器
			}	
		}
		else if(ucFuncID==ICAN_Func_ReadPort)  //连续读端口
		{
			if(ucFuncID==pICANSlave->icanFrame.ucFuncID)//&&(ucSourceID==pICANSlave->icanFrame.ucSourceID))
			{

				if(ucSourceID==0x00)
				{
					if(pCANFrame->ucData[0]==0x00)	//没有分段
					{
						
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

							pICANSlave->ucSource0x00=pICANSlave->ucRxBuffer[0];
							pICANSlave->ucSource0x01=pICANSlave->ucRxBuffer[1];
							pICANSlave->ucSource0x02=pICANSlave->ucRxBuffer[2];
							pICANSlave->ucSource0x03=pICANSlave->ucRxBuffer[3];
							pICANSlave->ucSource0x04=pICANSlave->ucRxBuffer[4];
							pICANSlave->ucSource0x05=pICANSlave->ucRxBuffer[5];
							pICANSlave->ucSource0x06=pICANSlave->ucRxBuffer[6];
							pICANSlave->ucSource0x07=pICANSlave->ucRxBuffer[7];
							pICANSlave->ucSource0x08=pICANSlave->ucRxBuffer[8];
							pICANSlave->ucSource0x09=pICANSlave->ucRxBuffer[9];
							pICANSlave->ucSource0x0A=pICANSlave->ucRxBuffer[10];
							pICANSlave->ucSource0x0B=pICANSlave->ucRxBuffer[11];
							pICANSlave->ucSource0x0C=pICANSlave->ucRxBuffer[12];
							pICANSlave->ucSource0x0D=pICANSlave->ucRxBuffer[13];
							pICANSlave->ucSource0x0E=pICANSlave->ucRxBuffer[14];
							pICANSlave->ucSource0x0F=pICANSlave->ucRxBuffer[15];
							pICANSlave->ucSource0x10=pICANSlave->ucRxBuffer[16];
							pICANSlave->ucSource0x11=pICANSlave->ucRxBuffer[17];
							pICANSlave->ucSource0x12=pICANSlave->ucRxBuffer[18];
							pICANSlave->ucSource0x13=pICANSlave->ucRxBuffer[19];
							pICANSlave->ucSource0x14=pICANSlave->ucRxBuffer[20];
							pICANSlave->ucSource0x15=pICANSlave->ucRxBuffer[21];
							pICANSlave->ucSource0x16=pICANSlave->ucRxBuffer[22];
							pICANSlave->ucSource0x17=pICANSlave->ucRxBuffer[23];
							pICANSlave->ucSource0x18=pICANSlave->ucRxBuffer[24];
							pICANSlave->ucSource0x19=pICANSlave->ucRxBuffer[25];
							pICANSlave->ucSource0x1A=pICANSlave->ucRxBuffer[26];
							pICANSlave->ucSource0x1B=pICANSlave->ucRxBuffer[27];
							pICANSlave->ucSource0x1C=pICANSlave->ucRxBuffer[28];
							pICANSlave->ucSource0x1D=pICANSlave->ucRxBuffer[29];
							pICANSlave->ucSource0x1E=pICANSlave->ucRxBuffer[30];
							pICANSlave->ucSource0x1F=pICANSlave->ucRxBuffer[31];
						}
						else
							pICANSlave->ucRxBufLength = 0;
					}					
    		}
// 				if(ucSourceID==0x0E) //PC
// 				{
// 						if(pCANFrame->ucData[0]==0x40)	//起始帧
// 							{
// 								pICANSlave->ucSource0x0E=pCANFrame->ucData[1];
// 								pICANSlave->ucSource0x0F=pCANFrame->ucData[2];
// 								pICANSlave->ucSource0x10=pCANFrame->ucData[3];	//
// 								pICANSlave->ucSource0x11=pCANFrame->ucData[4];	//
// 								pICANSlave->ucSource0x12=pCANFrame->ucData[5];	//
// 								pICANSlave->ucSource0x13=pCANFrame->ucData[6];	//
// 								pICANSlave->ucSource0x14=pCANFrame->ucData[7];	//	
// 							}		
// 							else if(pCANFrame->ucData[0]==0x81)	//结尾帧
// 							{
// 								pICANSlave->ucSource0x15=pCANFrame->ucData[1];
// 								pICANSlave->ucSource0x16=pCANFrame->ucData[2];
// 								pICANSlave->ucSource0x17=pCANFrame->ucData[3];	//
// 								pICANSlave->ucSource0x18=pCANFrame->ucData[4];	//
// 								pICANSlave->ucSource0x19=pCANFrame->ucData[5];	//
// 								pICANSlave->ucSource0x1A=pCANFrame->ucData[6];	//
// 								pICANSlave->ucSource0x1B=pCANFrame->ucData[7];	//
// 							}		
// 						if(pCANFrame->ucData[0]==0xC0)	//起始帧
// 							{
// 								pICANSlave->ucSource0x1C=pCANFrame->ucData[1];
// 								pICANSlave->ucSource0x1D=pCANFrame->ucData[2];
// 								pICANSlave->ucSource0x1E=pCANFrame->ucData[3];	//
// 								pICANSlave->ucSource0x1F=pCANFrame->ucData[4];	//		
// 							}		
// 							
// 				}
				if(ucSourceID==0xE2)
				{
					pICANSlave->ucSource0xE2=pCANFrame->ucData[1];
				}
				pICANSlave->ucStatus=ICAN_Slv_Idle;	//设置节点状态
				ResetNetTimer(pICANSlave->ucMacID);  //复位发送超时定时器
			}		
		}
		else if(ucFuncID==ICAN_Func_TransTriger)  //事件触发传送
		{
		}
		else if(ucFuncID==ICAN_Func_SetConnect)  //建立连接
		{
			if((ucFuncID==pICANSlave->icanFrame.ucFuncID)&&(ucSourceID==pICANSlave->icanFrame.ucSourceID))
			{
				pICANSlave->ucDILength=pCANFrame->ucData[1];
				pICANSlave->ucDOLength=pCANFrame->ucData[2];
				pICANSlave->ucAILength=pCANFrame->ucData[3];
				pICANSlave->ucAOLength=pCANFrame->ucData[4];
			
				pICANSlave->ucStatus=ICAN_Slv_Idle;	//设置节点状态
				pICANSlave->bIsConnect=true;	//设置建立连接
			}
		}
		else if(ucFuncID==ICAN_Func_DelConnect)  //删除连接
		{
		}
		else if(ucFuncID==ICAN_Func_SlvReset)	//从站复位
		{
		}
		else if(ucFuncID==ICAN_Func_MacIDCheck)  //接收到本站发出的MACID检测回馈
		{
			icanMaster.ucStatus=ICAN_Slv_Idle;
			SL_SET(ICAN_MACIDCHECK_ERR);
			MCL_SetFault(ICAN_MACIDCHECK_ERR);
			icanMaster.bIsOnline=false;   //off line 
			KillNetTimer(Timer_MacIDCheck);
		}
		else if(ucFuncID==ICAN_Func_ErrAck)  //异常响应
		{
			if(pCANFrame->ucData[1]==0x05)	//异常响应码：连接不存在
			{
				pICANSlave->bIsConnect=false;	//断开连接
				pICANSlave->ucStatus=ICAN_Slv_Idle;
			}
			if(pCANFrame->ucData[1]==0x07)	//异常响应码：传输过程出错
			{
				pICANSlave->ucStatus=ICAN_Slv_Idle;
				MsgICANRegister(pICANSlave->ucMacID,Msg_ICANRetry);
			}
		}
	}			
}

void ICANDataInManage_Master(void)
{	
	INT8U i;
	INT8U ucSrcMacID;
	INT8U ucDestMacID;
 	tCANFrame canFrame;	//
	tICANFrame icanFrame;
	tICANSlave *pICANSlave;
	
	INT8U ucACK;
	INT8U ucFuncID;

	//从CAN数据缓冲区中读取CAN数据帧，放入相应的子站镜像中
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
		pICANSlave=icanMaster.pICANSlvArray;	 

	//自动注册从站镜像 add:20150301
		ucSrcMacID = (canFrame.ulID >> 21) & 0x000000FF; // 源节点编号（ID28－ID21）
		ucDestMacID = (canFrame.ulID >> 13) & 0x000000FF; // 目标节点编号（ID20－ID13） 
	  ucACK = (canFrame.ulID >> 12) & 0x00000001; // 应答标志（ID12） 
    ucFuncID = (canFrame.ulID >> 8) & 0x000000F; // 功能码（ID11－ID8） 
		
		//Add:20150310
		if(ucFuncID==ICAN_Func_MacIDCheck && ucSrcMacID!=icanMaster.ucMacID) //从站的MACID检测帧
		{
				//主站先上电
				if(ucACK==ICAN_ACK_Enable) 
				{
				//	pICANSlave->ucStatus=ICAN_Slv_Idle;
					KillNetTimer(Timer_MacIDCheck);
					ICANAddSlave(ucSrcMacID, 0);					
				}
			//从站先上电，从站对主站的MACID反馈帧，不需应答 
				else 
				{
					//pICANSlave->ucStatus=ICAN_Slv_Idle;
					ICANAddSlave(ucSrcMacID, 0);
				}
		}
		else if(ucFuncID==ICAN_Func_MacIDCheck && ucSrcMacID==icanMaster.ucMacID) //多个主站
		{
				//本主站先上电
				if(ucACK==ICAN_ACK_Enable) 
				{
					//发送MACID应答帧
					icanFrame.ucSrcMacID=icanMaster.ucMacID;		//	源节点地址
					icanFrame.ucDestMacID=pICANSlave->ucMacID;		//	目标节点地址
					icanFrame.ucACK=ICAN_ACK_Disable;			//	响应标识位
					icanFrame.ucFuncID=ICAN_Func_MacIDCheck;	//	功能码
					icanFrame.ucSourceID=0xFF;		//	MacIDCheck资源节点地址为0xFA
					icanFrame.ucDataLength=0x06;	//	有效数据长度
					//6字节数据
					icanFrame.ucData[0]=0x00;
					icanFrame.ucData[1]=icanMaster.ucMacID;
					icanFrame.ucData[2]=GetDataByte(icanMaster.ulSN,1);
					icanFrame.ucData[3]=GetDataByte(icanMaster.ulSN,2);
					icanFrame.ucData[4]=GetDataByte(icanMaster.ulSN,3);
					icanFrame.ucData[5]=GetDataByte(icanMaster.ulSN,4);

					icanMaster.ucStatus=ICAN_Slv_Post;
				//canMaster.bIsOnline=true;
					ICANSend(icanFrame);	
				}
				else 		//本主站后上电，offline
				{
					pICANSlave->ucStatus=ICAN_Slv_Idle;
          SL_SET(ICAN_MACIDCHECK_ERR);
					MCL_SetFault(ICAN_MACIDCHECK_ERR);
					KillNetTimer(Timer_MacIDCheck);
					icanMaster.bIsOnline=false;
				}	
	
		}
			
		//搜索该数据帧对应的子站镜像
		for(i=1;i<icanMaster.ucSlvArrLength;i++)
//		for(i=0;i<icanMaster.ucSlvArrLength;i++)
		{ 
			ucSrcMacID = (canFrame.ulID >> 21) & 0x000000FF; // 源节点编号（ID28－ID21）
			ucDestMacID = (canFrame.ulID >> 13) & 0x000000FF; // 目标节点编号（ID20－ID13）  
			if(((pICANSlave+i)->ucMacID==ucSrcMacID)&&(icanMaster.ucMacID==ucDestMacID))
			{
				ICANReceive(pICANSlave+i,&canFrame);	//ICAN接收

			} 
		} 
	}  	
}

//
void ICANNetManage_Master(void)
{
	INT8U i;
	tICANSlave *pICANSlave;
	//MacID检测超时处理
	if(netTimer[Timer_MacIDCheck].bIsOvertime)
	{
		icanMaster.bIsOnline=true;
		icanMaster.ucStatus=ICAN_Slv_Idle;
		KillNetTimer(Timer_MacIDCheck);
	}

	//发送超时处理
	for(i=1;i<icanMaster.ucSlvArrLength;i++)
	{
		pICANSlave=icanMaster.pICANSlvArray+i;
		//启动发送定时器
		if((pICANSlave->ucStatus==ICAN_Slv_Post)&&(netTimer[pICANSlave->ucMacID].bIsStart==false))
		{
//			SetNetTimer(pICANSlave->ucMacID,200);
			SetNetTimer(pICANSlave->ucMacID,1000);
		}
		//站点通信超时处理
		if(netTimer[pICANSlave->ucMacID].bIsOvertime)
		{
			if(pICANSlave->bIsConnect==false)//如果未建立连接	
			{				
				pICANSlave->ucStatus=ICAN_Slv_Idle;
				AlarmICANRegister(pICANSlave->ucMacID,Msg_Err_ICANConnect);
				
			}
			else //如果已建立连接
			{			
				pICANSlave->bIsConnect=false;	//断开连接
				pICANSlave->ucStatus=ICAN_Slv_Idle;				
			}
		}
		//删除网络定时器
		if(pICANSlave->ucStatus==ICAN_Slv_Idle)
		{
			KillNetTimer(pICANSlave->ucMacID);	
		}
	}
	//当前从站轮训节点设定
	if(icanMaster.ucSlvArrLength>1)
	{
		icanMaster.ucCurSlvIndex++;
	}
	if(icanMaster.ucCurSlvIndex>=icanMaster.ucSlvArrLength)
	{
		icanMaster.ucCurSlvIndex=1;
	}
}

 /********************************************************************
  * 函数名: 	ICAN_DOProc()
  * 参数:   	pICANSlave 从站镜像
  * 功能描述：DO发送Source0x20~Source0x3F
  * 返回值：	NULL
  ********************************************************************/
void ICAN_DOProc(tICANSlave *pICANSlave)
{
//		unsigned char  index;
//		unsigned long  ucSrcMacID;	//	源节点地址
//		unsigned long  ucDestMacID;	//	目标节点地址
//		unsigned long  ucACK;		//	响应标识位
//		unsigned long  ucFuncID;	//	功能码
//		unsigned long  ucSourceID;		//	资源节点地址
//	
//		tCANFrame canFrame[5];	//
//	
//			ucSrcMacID=icanMaster.ucMacID;		//	源节点地址;
//			ucDestMacID=pICANSlave->ucMacID;		//	目标节点地址
//			ucACK=ICAN_ACK_Enable;			//	响应标识位;
//			ucFuncID=ICAN_Func_WritePort;	//	功能码
//	
//			ucSourceID=0x20;		//	资源节点——DO地址为0x20

//			canFrame[0].ulID=(ucSrcMacID<<21)+(ucDestMacID<<13)+(ucACK<<12)+(ucFuncID<<8)+ucSourceID;
//			canFrame[0].ucXID=1;			//0 标准帧；1 扩展帧 
//			canFrame[0].ucDataLength=8;	

//			canFrame[0].ucData[0]=0x40;	//1000 0001
//			canFrame[0].ucData[1]=pICANSlave->ucSource0x20;
//			canFrame[0].ucData[2]=pICANSlave->ucSource0x21;
//			canFrame[0].ucData[3]=pICANSlave->ucSource0x22;	//
//			canFrame[0].ucData[4]=pICANSlave->ucSource0x23;	//
//			canFrame[0].ucData[5]=pICANSlave->ucSource0x24;	//
//			canFrame[0].ucData[6]=pICANSlave->ucSource0x25;	//
//			canFrame[0].ucData[7]=pICANSlave->ucSource0x26;	//
////				CANWriteBuffer(&canFrmTxBuffer, &canFrame);
//			canFrame[1].ulID=(ucSrcMacID<<21)+(ucDestMacID<<13)+(ucACK<<12)+(ucFuncID<<8)+ucSourceID;
//			canFrame[1].ucXID=1;			//0 标准帧；1 扩展帧 
//			canFrame[1].ucDataLength=8;	
//			canFrame[1].ucData[0]=0x81;	//1000 0001
//			canFrame[1].ucData[1]=pICANSlave->ucSource0x27;
//			canFrame[1].ucData[2]=pICANSlave->ucSource0x28;
//			canFrame[1].ucData[3]=pICANSlave->ucSource0x29;	//
//			canFrame[1].ucData[4]=pICANSlave->ucSource0x2A;	//
//			canFrame[1].ucData[5]=pICANSlave->ucSource0x2B;	//
//			canFrame[1].ucData[6]=pICANSlave->ucSource0x2C;	//
//			canFrame[1].ucData[7]=pICANSlave->ucSource0x2D;	//
////				CANWriteBuffer(&canFrmTxBuffer, &canFrame);
//			canFrame[2].ulID=(ucSrcMacID<<21)+(ucDestMacID<<13)+(ucACK<<12)+(ucFuncID<<8)+ucSourceID;
//			canFrame[2].ucXID=1;			//0 标准帧；1 扩展帧 
//			canFrame[2].ucDataLength=8;	
//			canFrame[2].ucData[0]=0x82;	//1000 0001
//			canFrame[2].ucData[1]=pICANSlave->ucSource0x2E;
//			canFrame[2].ucData[2]=pICANSlave->ucSource0x2F;
//			canFrame[2].ucData[3]=pICANSlave->ucSource0x30;	//
//			canFrame[2].ucData[4]=pICANSlave->ucSource0x31;
//			canFrame[2].ucData[5]=pICANSlave->ucSource0x32;	//
//			canFrame[2].ucData[6]=pICANSlave->ucSource0x33;	//
//			canFrame[2].ucData[7]=pICANSlave->ucSource0x34;	//
////				CANWriteBuffer(&canFrmTxBuffer, &canFrame);
//			canFrame[3].ulID=(ucSrcMacID<<21)+(ucDestMacID<<13)+(ucACK<<12)+(ucFuncID<<8)+ucSourceID;
//			canFrame[3].ucXID=1;			//0 标准帧；1 扩展帧 
//			canFrame[3].ucDataLength=8;	
//			canFrame[3].ucData[0]=0x83;	//1000 0001
//			canFrame[3].ucData[1]=pICANSlave->ucSource0x35;
//			canFrame[3].ucData[2]=pICANSlave->ucSource0x36;
//			canFrame[3].ucData[3]=pICANSlave->ucSource0x37;	//
//			canFrame[3].ucData[4]=pICANSlave->ucSource0x38;	//
//			canFrame[3].ucData[5]=pICANSlave->ucSource0x39;	//
//			canFrame[3].ucData[6]=pICANSlave->ucSource0x3A;	//
//			canFrame[3].ucData[7]=pICANSlave->ucSource0x3B;	//
////			CANWriteBuffer(&canFrmTxBuffer, &canFrame);
//			canFrame[4].ulID=(ucSrcMacID<<21)+(ucDestMacID<<13)+(ucACK<<12)+(ucFuncID<<8)+ucSourceID;
//			canFrame[4].ucXID=1;			//0 标准帧；1 扩展帧 
//			canFrame[4].ucDataLength=8;	
//			canFrame[4].ucData[0]=0xC0;	//1100 0000
//			canFrame[4].ucData[1]=pICANSlave->ucSource0x3C;
//			canFrame[4].ucData[2]=pICANSlave->ucSource0x3D;
//			canFrame[4].ucData[3]=pICANSlave->ucSource0x3E;	//
//			canFrame[4].ucData[4]=pICANSlave->ucSource0x3F;	//
//			canFrame[4].ucData[5]=0x00;	//
//			canFrame[4].ucData[6]=0x00;	//
//			canFrame[4].ucData[7]=0x00;	//
////			CANWriteBuffer(&canFrmTxBuffer, &canFrame);

//			for(index=0;index<5;index++)
//			{
//				CANWriteBuffer(&canFrmTxBuffer, canFrame+index);
//			}
//					
//			//发送缓冲区数据
//			CANFrmSend(&canFrmTxBuffer);	

		unsigned long  ucSrcMacID;	//	源节点地址
		unsigned long  ucDestMacID;	//	目标节点地址
		unsigned long  ucACK;		//	响应标识位
		unsigned long  ucFuncID;	//	功能码
		unsigned long  ucSourceID;		//	资源节点地址
	//	tICANSlave *pICANSlave;
		tCANFrame canFrame;	//
	
			ucSrcMacID=icanMaster.ucMacID;		//	源节点地址;
			ucDestMacID=pICANSlave->ucMacID;		//	目标节点地址
			ucACK=ICAN_ACK_Enable;			//	响应标识位;
			ucFuncID=ICAN_Func_WritePort;	//	功能码
	
			ucSourceID=0x20;		//	资源节点——DO地址为0x20

			canFrame.ulID=(ucSrcMacID<<21)+(ucDestMacID<<13)+(ucACK<<12)+(ucFuncID<<8)+ucSourceID;
			canFrame.ucXID=1;			//0 标准帧；1 扩展帧 
			canFrame.ucDataLength=8;	

			canFrame.ucData[0]=0x40;	
			canFrame.ucData[1]=pICANSlave->ucSource0x20;
			canFrame.ucData[2]=pICANSlave->ucSource0x21;
			canFrame.ucData[3]=pICANSlave->ucSource0x22;	//
			canFrame.ucData[4]=pICANSlave->ucSource0x23;	//
			canFrame.ucData[5]=pICANSlave->ucSource0x24;	//
			canFrame.ucData[6]=pICANSlave->ucSource0x25;	//
			canFrame.ucData[7]=pICANSlave->ucSource0x26;	//
			CANWriteBuffer(&canFrmTxBuffer, &canFrame);
			
			canFrame.ucData[0]=0x81;	
			canFrame.ucData[1]=pICANSlave->ucSource0x27;
			canFrame.ucData[2]=pICANSlave->ucSource0x28;
			canFrame.ucData[3]=pICANSlave->ucSource0x29;	//
			canFrame.ucData[4]=pICANSlave->ucSource0x2A;	//
			canFrame.ucData[5]=pICANSlave->ucSource0x2B;	//
			canFrame.ucData[6]=pICANSlave->ucSource0x2C;	//
			canFrame.ucData[7]=pICANSlave->ucSource0x2D;	//
			CANWriteBuffer(&canFrmTxBuffer, &canFrame);
			
			canFrame.ucData[0]=0x82;	
			canFrame.ucData[1]=pICANSlave->ucSource0x2E;
			canFrame.ucData[2]=pICANSlave->ucSource0x2F;
			canFrame.ucData[3]=pICANSlave->ucSource0x30;	//
			canFrame.ucData[4]=pICANSlave->ucSource0x31;
			canFrame.ucData[5]=pICANSlave->ucSource0x32;	//
			canFrame.ucData[6]=pICANSlave->ucSource0x33;	//
			canFrame.ucData[7]=pICANSlave->ucSource0x34;	//
			CANWriteBuffer(&canFrmTxBuffer, &canFrame);
			
			canFrame.ucData[0]=0x83;	
			canFrame.ucData[1]=pICANSlave->ucSource0x35;
			canFrame.ucData[2]=pICANSlave->ucSource0x36;
			canFrame.ucData[3]=pICANSlave->ucSource0x37;	//
			canFrame.ucData[4]=pICANSlave->ucSource0x38;	//
			canFrame.ucData[5]=pICANSlave->ucSource0x39;	//
			canFrame.ucData[6]=pICANSlave->ucSource0x3A;	//
			canFrame.ucData[7]=pICANSlave->ucSource0x3B;	//
			CANWriteBuffer(&canFrmTxBuffer, &canFrame);
				
			canFrame.ucData[0]=0xC0;	
			canFrame.ucData[1]=pICANSlave->ucSource0x3C;
			canFrame.ucData[2]=pICANSlave->ucSource0x3D;
			canFrame.ucData[3]=pICANSlave->ucSource0x3E;	//
			canFrame.ucData[4]=pICANSlave->ucSource0x3F;	//
			canFrame.ucData[5]=0x00;	//
			canFrame.ucData[6]=0x00;	//
			canFrame.ucData[7]=0x00;	//
			CANWriteBuffer(&canFrmTxBuffer, &canFrame);
					
			//发送缓冲区数据
//			CANFrmSend(&canFrmTxBuffer);	
}

//
void ICANDataOutManage_Master(void)
{	
	INT8U i;
	tICANFrame icanFrame;
	tICANSlave *pICANSlave;
	tMessage message;

	//
	//MacID检测
	//
	if((icanMaster.bIsOnline==false)&&(icanMaster.ucStatus==ICAN_Slv_Idle))
	{
		if(!SL_CHK(ICAN_MACIDCHECK_ERR))
		{
			ICANMacIDCheck();
		}
		return;
	}
	
	//
	// 建立连接
	//
	if(icanMaster.ucCurSlvIndex >0)	//建立连接对象为从站
	{
		pICANSlave=icanMaster.pICANSlvArray+icanMaster.ucCurSlvIndex;
		if((pICANSlave->bIsConnect==false)&&(pICANSlave->ucStatus==ICAN_Slv_Idle))
		{
			ICANSetConnect(pICANSlave);
			goto END;
		}
	}
	//
	//ICAN消息事件处理
	//
	while(MsgICANPop(&message))
	{		
		for(i=1;i<icanMaster.ucSlvArrLength;i++)
		{
			pICANSlave=icanMaster.pICANSlvArray+i;
			if(pICANSlave->ucMacID==message.ucMsgMacID)
			{
				if((pICANSlave->bIsConnect==false)||(pICANSlave->ucStatus!=ICAN_Slv_Idle))//判断当前节点是否空闲
				{
					MsgAdd(Msg_Type_ICAN,message);
					goto END;
				}
				else
				{
					if(message.ucMsgEvent==Msg_ReadPrdType)
					{
						icanFrame.ucSrcMacID=icanMaster.ucMacID;		//	源节点地址
						icanFrame.ucDestMacID=message.ucMsgMacID;		//	目标节点地址
						icanFrame.ucACK=ICAN_ACK_Enable;			//	响应标识位
						icanFrame.ucFuncID=ICAN_Func_ReadPort;	//	功能码
						icanFrame.ucSourceID=0xE2;		//	资源节点——类型地址为0xE2
						icanFrame.ucDataLength=2;	//	有效数据长度
						icanFrame.ucData[0]=0x00;	//
						icanFrame.ucData[1]=1;
				 	
						pICANSlave->ucStatus=ICAN_Slv_Post;
						
						pICANSlave->icanFrame.ucSrcMacID=icanMaster.ucMacID;		//	源节点地址
						pICANSlave->icanFrame.ucDestMacID=message.ucMsgMacID;		//	目标节点地址
						pICANSlave->icanFrame.ucACK=ICAN_ACK_Enable;			//	响应标识位
						pICANSlave->icanFrame.ucFuncID=ICAN_Func_ReadPort;	//	功能码
						pICANSlave->icanFrame.ucSourceID=0xE2;		//	资源节点——类型地址为0xE2
						pICANSlave->icanFrame.ucDataLength=2;	//	有效数据长度
						pICANSlave->icanFrame.ucData[0]=0x00;	//
						pICANSlave->icanFrame.ucData[1]=1;
						pICANSlave->icanFrame.ucData[2]=0x00;	//
						pICANSlave->icanFrame.ucData[3]=0x00;	//
						pICANSlave->icanFrame.ucData[4]=0x00;	//
						pICANSlave->icanFrame.ucData[5]=0x00;	//
						pICANSlave->icanFrame.ucData[6]=0x00;	//
						pICANSlave->icanFrame.ucData[7]=0x00;	//
						
						pICANSlave->ucSource0xE2=0;	
				
						ICANSend(icanFrame);
						goto END;
					}
					if(message.ucMsgEvent==Msg_ICANRetry)
					{
						icanFrame.ucSrcMacID=pICANSlave->icanFrame.ucSrcMacID;		//	源节点地址
						icanFrame.ucDestMacID=pICANSlave->icanFrame.ucDestMacID;		//	目标节点地址
						icanFrame.ucACK=pICANSlave->icanFrame.ucACK;			//	响应标识位
						icanFrame.ucFuncID=pICANSlave->icanFrame.ucFuncID;	//	功能码
						icanFrame.ucSourceID=pICANSlave->icanFrame.ucSourceID;		//	资源节点——类型地址为0xE2
						icanFrame.ucDataLength=pICANSlave->icanFrame.ucDataLength;	//	有效数据长度
						icanFrame.ucData[0]=pICANSlave->icanFrame.ucData[0];	//
						icanFrame.ucData[1]=pICANSlave->icanFrame.ucData[1];
						icanFrame.ucData[2]=pICANSlave->icanFrame.ucData[2];
						icanFrame.ucData[3]=pICANSlave->icanFrame.ucData[3];
						icanFrame.ucData[4]=pICANSlave->icanFrame.ucData[4];
						icanFrame.ucData[5]=pICANSlave->icanFrame.ucData[5];
						icanFrame.ucData[6]=pICANSlave->icanFrame.ucData[6];
						icanFrame.ucData[7]=pICANSlave->icanFrame.ucData[7];
				 	
						pICANSlave->ucStatus=ICAN_Slv_Post;	
				
						ICANSend(icanFrame);
						goto END;
					}
				}
			}
		}		
	}
	//
	//轮询资源节点（DI、DO、AI、AO）
	//
	if(icanMaster.ucCurSlvIndex!=0)	//建立连接对象为从站	
	{
		if(pICANSlave->ucDataAddress==ICAN_Addr_DI)	//DI
		{
			if((pICANSlave->bIsConnect==true)&&(pICANSlave->ucStatus==ICAN_Slv_Idle))
			{
				icanFrame.ucSrcMacID=icanMaster.ucMacID;		//	源节点地址
				icanFrame.ucDestMacID=pICANSlave->ucMacID;		//	目标节点地址
				icanFrame.ucACK=ICAN_ACK_Enable;			//	响应标识位
				icanFrame.ucFuncID=ICAN_Func_ReadPort;	//	功能码
				icanFrame.ucSourceID=0x00;		//	资源节点——DI地址为0x00
				icanFrame.ucDataLength=2;	//	有效数据长度
				icanFrame.ucData[0]=0x00;	//
				icanFrame.ucData[1]=pICANSlave->ucDILength;
		 	
				pICANSlave->ucStatus=ICAN_Slv_Post;
				
				pICANSlave->icanFrame.ucSrcMacID=icanMaster.ucMacID;		//	源节点地址
				pICANSlave->icanFrame.ucDestMacID=pICANSlave->ucMacID;		//	目标节点地址
				pICANSlave->icanFrame.ucACK=ICAN_ACK_Enable;			//	响应标识位
				pICANSlave->icanFrame.ucFuncID=ICAN_Func_ReadPort;	//	功能码
				pICANSlave->icanFrame.ucSourceID=0x00;		//	资源节点——DI地址为0x00
				pICANSlave->icanFrame.ucDataLength=2;	//	有效数据长度
				pICANSlave->icanFrame.ucData[0]=0x00;	//
				pICANSlave->icanFrame.ucData[1]=pICANSlave->ucDILength;

				ICANSend(icanFrame);
				pICANSlave->ucDataAddress=ICAN_Addr_DO;
				
			}
		}
		else if(pICANSlave->ucDataAddress==ICAN_Addr_DO)	//DO
		{
			if((pICANSlave->bIsConnect==true)&&(pICANSlave->ucStatus==ICAN_Slv_Idle))
			{
//				icanFrame.ucSrcMacID=icanMaster.ucMacID;		//	源节点地址
//				icanFrame.ucDestMacID=pICANSlave->ucMacID;		//	目标节点地址
//				icanFrame.ucACK=ICAN_ACK_Enable;			//	响应标识位
//				icanFrame.ucFuncID=ICAN_Func_WritePort;	//	功能码
//				icanFrame.ucSourceID=0x20;		//	资源节点——DO地址为0x20
//				icanFrame.ucDataLength=pICANSlave->ucDOLength+1;	//	有效数据长度
//				icanFrame.ucData[0]=0x00;	//
//				icanFrame.ucData[1]=pICANSlave->ucSource0x20;
//				icanFrame.ucData[2]=pICANSlave->ucSource0x21;	
				

//				ucSrcMacID=icanMaster.ucMacID;		//	源节点地址;
//				ucDestMacID=pICANSlave->ucMacID;		//	目标节点地址
//				ucACK=ICAN_ACK_Enable;			//	响应标识位;
//				ucFuncID=ICAN_Func_WritePort;	//	功能码
//				ucSourceID=0x20;		//	资源节点——DO地址为0x20
//					
//				canFrame.ulID=(ucSrcMacID<<21)+(ucDestMacID<<13)+(ucACK<<12)+(ucFuncID<<8)+ucSourceID;
//				canFrame.ucXID=1;			//0 标准帧；1 扩展帧 
//				canFrame.ucDataLength=8;
					
				pICANSlave->ucStatus=ICAN_Slv_Post;	
					
				ICAN_DOProc(pICANSlave); //DO
		
				pICANSlave->ucDataAddress=ICAN_Addr_DI;
				}
			}
		}
		END: ;		
	}


