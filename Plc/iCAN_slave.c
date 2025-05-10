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
//��վ
tICANSlave icanSlave;	 //�����վ
tBoolean bConnectEnable;	//�Ƿ�������
static unsigned char bMacIDCheck_Err_Flag=0;

//��վ�ڵ��ʼ��
void ICANInitialize_Slave()	
{
	//�ڵ���Ϣ
	icanSlave.ucMacID=PRDUCT_TYPE;//gCRam.SvPa.StationAddr; //StationType		 //��վID
	icanSlave.ucType=PRDUCT_TYPE;//gCRam.SvPa.StationAddr;	    //	��վ��Ʒ����
	icanSlave.ulSN=0x00;			//	��վ��Ʒ���к�
	icanSlave.ucDILength=32;	//
	icanSlave.ucDOLength=32;	//
	icanSlave.ucAILength=0;	//
	icanSlave.ucAOLength=0;	//
	// ����״̬
	icanSlave.bIsConnect=false;			//�Ƿ�����վ��������
	icanSlave.bIsOnline=false;			//
	icanSlave.ucStatus=ICAN_Slv_Idle;		//	����״̬
	icanSlave.ucErrCount=0;		//	���������	
	icanSlave.ucTime = 0;
	//���ܻ���������
	icanSlave.ucRxBufLength=0;	//	���ܻ���������

	//��Դ�ڵ���Ϣ
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
	icanSlave.ucSource0x20=0;	//�Ǳ�PrdState
	icanSlave.ucSource0x21=0;	//�Ǳ�ICANNetCfg
	icanSlave.ucSource0x22=0;	//�Ǳ�ErrMove
	icanSlave.ucSource0x23=0;	//�Ǳ�ErrLift
	icanSlave.ucSource0x24=0;	//�Ǳ�ErrSteer
	icanSlave.ucSource0x25=0;	//�Ǳ�ErrMoveSecond
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

	icanSlave.ucSource0xE2=0; //��Ʒ����
	// ���Գ�ʼ��
	bConnectEnable=true;
	//��Ϣ���г�ʼ��
	MsgInitialize();

}

// ɾ������
void ICANDelConnection_Slave(void)
{
	icanSlave.bIsConnect=false;	
	bConnectEnable=false;
}

//MacID���
void ICANMacIDCheck_Slave(void)
{
	tICANFrame icanFrame;

	//�����ǰ�ڵ���У�����MacID���֡
	if(icanSlave.ucStatus==ICAN_Slv_Idle)
	{
		icanFrame.ucSrcMacID=icanSlave.ucMacID;		//	ԭ�ڵ��ַ
		icanFrame.ucDestMacID=icanSlave.ucMacID;		//	Ŀ��ڵ��ַ
		icanFrame.ucACK=ICAN_ACK_Enable;			//	��Ӧ��ʾ��
		icanFrame.ucFuncID=ICAN_Func_MacIDCheck;	//	������
		icanFrame.ucSourceID=0xFF;		//	MacIDCheck��Դ�ڵ��ַΪ0xFF
		icanFrame.ucDataLength=0x06;	//	��Ч���ݳ���
		//6�ֽ�����
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

//ICAN����
void ICANReceive_Slave(tICANSlave *pICANSlave,tCANFrame *pCANFrame)
{
	unsigned char ucSrcMacID;
	unsigned char ucACK;
	unsigned char ucFuncID;
	unsigned char ucSourceID;
//	tICANFrame icanFrame;

	ucSrcMacID = (pCANFrame->ulID >> 21) & 0x000000FF; // ԭ�ڵ��ַ(ID28-ID21)
	ucACK = (pCANFrame->ulID >> 12) & 0x00000001; // ��Ӧ��ʾ��(ID12) 
    ucFuncID = (pCANFrame->ulID >> 8) & 0x000000F; // ������(ID11-ID8) 
	ucSourceID = pCANFrame->ulID & 0x000000FF; // ��Դ�ڵ��ַ(ID7-ID0)
//	ucDataLength=pCANFrame->ucDataLength;	//���ݳ���

	//���δ����,ֻ��MacID������������Ӧ 	
	if((icanSlave.bIsOnline==false)&&(ucFuncID==ICAN_Func_MacIDCheck))
	{
		if(ucACK==ICAN_ACK_Disable)	//���յ�MacID����
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

	//��������ߣ���ҪӦ��
	if((icanSlave.bIsOnline==true)&&(ucACK==ICAN_ACK_Enable))
	{
		//��⹦����
		if(ucFuncID==ICAN_Func_WritePort)  //����д�˿�
		{
			if(icanSlave.bIsConnect)
			{
					if(pCANFrame->ucData[0]==0x00)	//û�зֶ�
					{
						
						//������ϣ�ע����Ϣ
			     MsgICANRegister(0x00,Msg_WritePort);
					}								
					if(pCANFrame->ucData[0]==0x40)	//��ʼ֡���ֶ�֡��1֡
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
					else if(pCANFrame->ucData[0]==0x81)	//�м�֡���ֶ�֡��2֡
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
					else if(pCANFrame->ucData[0]==0x82)	//�м�֡���ֶ�֡��3֡
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
					else if(pCANFrame->ucData[0]==0x83)	//�м�֡���ֶ�֡��4֡
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
					else if(pCANFrame->ucData[0]==0xC0)	//��β֡���ֶ�֡��5֡
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
						
						//������ϣ�ע����Ϣ
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
		else if(ucFuncID==ICAN_Func_ReadPort)  //�������˿�
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
		else if(ucFuncID==ICAN_Func_TransTriger)  //�¼���������
		{
		}
		else if(ucFuncID==ICAN_Func_SetConnect)  //��������
		{
			if(bConnectEnable)
			{
				//MsgRegister(Msg_Type_ICAN,0x00,Msg_SetConnect);
				MsgICANRegister(0x00,Msg_SetConnect);
				pICANSlave->ucStatus=ICAN_Slv_Idle;
				pICANSlave->bIsConnect=true;	//���ý�������
			}
		}
		else if(ucFuncID==ICAN_Func_DelConnect)  //ɾ������
		{
		}
		else if(ucFuncID==ICAN_Func_SlvReset)	//�豸��λ
		{
		}
		else if(ucFuncID==ICAN_Func_MacIDCheck)  //MACID���
		{
			//MsgICANRegister(Msg_Type_ICAN,ucSrcMacID,Msg_MacIDCheck);
			MsgICANRegister(ucSrcMacID,Msg_MacIDCheck);
			pICANSlave->ucStatus=ICAN_Slv_Idle;	//���ýڵ�״̬
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
	//��CAN���ݻ������ж�ȡCAN����֡��������Ӧ����վ������
	//if(fReadEnable)
	{
		while(CANReadBuffer(&canFrmRxBuffer,&canFrame)!=EMPTY)//��ȡCAN���ݽ��ջ�����
		{	
			if (canFrame.ucXID == 0)
			{//��׼֡ͷ
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
			ucSrcMacID = (canFrame.ulID >> 21) & 0x000000FF; // ԭ�ڵ��ַ(ID28-ID21)
			ucDestMacID = (canFrame.ulID >> 13) & 0x000000FF; // Ŀ��ڵ���(ID20-ID13) 			
			ucACK = (canFrame.ulID >> 12) & 0x00000001; // ��Ӧ��ʾ��(ID12) 
			ucFuncID = (canFrame.ulID >> 8) & 0x000000F; // ������(ID11-ID8) 
			//��վ���ϵ磬��վ������վ������վ��Ӹô�վ
		//	if(ucSrcMacID==0x00 && ucFuncID==ICAN_Func_MacIDCheck)
			if((ucSrcMacID==0x00 ||ucSrcMacID==icanSlave.ucMacID )&& ucFuncID==ICAN_Func_MacIDCheck)
			{
				if(ucACK==ICAN_ACK_Enable)
				{
					icanFrame.ucSrcMacID=icanSlave.ucMacID;		//	ԭ�ڵ��ַ
					icanFrame.ucDestMacID=icanSlave.ucMacID;		//	Ŀ��ڵ��ַ
					icanFrame.ucACK=ICAN_ACK_Disable;			//	��Ӧ��ʾ��
					icanFrame.ucFuncID=ICAN_Func_MacIDCheck;	//	������
					icanFrame.ucSourceID=0xFF;		//	MacIDCheck��Դ�ڵ��ַΪ0xFF
					icanFrame.ucDataLength=0x06;	//	��Ч���ݳ���
					//6�ֽ�����
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
				ICANReceive_Slave(&icanSlave,&canFrame);	//ICAN����
	//	fReadEnable=false;
			}  
		}
	}  	
}

//
void ICANNetManage_Slave(void)
{

	//MacID��ⳬʱ����
	if(netTimer[Timer_MacIDCheck].bIsOvertime)
	{
		icanSlave.bIsOnline=true;
		icanSlave.ucStatus=ICAN_Slv_Idle;
		KillNetTimer(Timer_MacIDCheck);
	}
	//�������Ͷ�ʱ��
	if(icanSlave.bIsConnect&&(netTimer[Timer_Connect].bIsStart==false))
	{
//    SetNetTimer(Timer_Connect,200);
		SetNetTimer(Timer_Connect,1000);
	}
	//��վ����ͨ�ų�ʱ����
	if(netTimer[Timer_Connect].bIsOvertime && icanSlave.bIsConnect) //
	{
		icanSlave.bIsConnect=false;	//�Ͽ�����
		KillNetTimer(Timer_Connect);
		//��λ��Դ�ڵ�
		//�ڵ���Ϣ
		icanSlave.ucDILength=27;	//
		icanSlave.ucDOLength=32;	//
		icanSlave.ucAILength=0;	//
		icanSlave.ucAOLength=0;	//
		//����״̬
		icanSlave.bIsConnect=false;			//�Ͽ�����
		icanSlave.ucStatus=ICAN_Slv_Idle;		//	��վ����״̬
		icanSlave.ucErrCount=0;		//	���������
		icanSlave.ucTime = 0;
		//������Ϣ
		icanSlave.ucRxBufLength=0;	//��վ���ܻ���������
		
		//��Դ�ڵ���Ϣ
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
		icanSlave.ucSource0x20=0;	//�Ǳ�PrdState
		icanSlave.ucSource0x21=0;	//�Ǳ�ICANNetCfg
		icanSlave.ucSource0x22=0;	//�Ǳ�ErrMove
		icanSlave.ucSource0x23=0;	//�Ǳ�ErrLift
		icanSlave.ucSource0x24=0;	//�Ǳ�ErrSteer
		icanSlave.ucSource0x25=0;	//�Ǳ�ErrMoveSecond
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
  * ������: 	ICAN_DOProc()
  * ����:   	pICANSlave ��վ����
  * ����������DO����Source0x20~Source0x3F
  * ����ֵ��	NULL
  ********************************************************************/
	void ICAN_DOProc_Slave(tICANSlave *pICANSlave)
{
		unsigned long  ucSrcMacID;	//	Դ�ڵ��ַ
		unsigned long  ucDestMacID;	//	Ŀ��ڵ��ַ
		unsigned long  ucACK;		//	��Ӧ��ʶλ
		unsigned long  ucFuncID;	//	������
		unsigned long  ucSourceID;		//	��Դ�ڵ��ַ
		tCANFrame canFrame;	//
	
			ucSrcMacID=icanSlave.ucMacID;		//	Դ�ڵ��ַ;
			ucDestMacID=0x00;//pICANSlave->ucMacID;		//	Ŀ��ڵ��ַ
			ucACK=ICAN_ACK_Disable;			//	��Ӧ��ʶλ;
			ucFuncID=ICAN_Func_ReadPort;	//	������
			ucSourceID=0x00;		//	��Դ�ڵ㡪��DO��ַΪ0x20
		//	icanFrame.ucDataLength=icanSlave.ucDILength+1;	//
	
			canFrame.ulID=(ucSrcMacID<<21)+(ucDestMacID<<13)+(ucACK<<12)+(ucFuncID<<8)+ucSourceID;
			canFrame.ucXID=1;			//0 ��׼֡��1 ��չ֡ 
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
	//MacID���
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
	//ICAN��Ϣ�¼�����
	if((icanSlave.ucStatus==ICAN_Slv_Idle)&&(icanSlave.bIsConnect==true))	//�жϽڵ��Ƿ����
	{
		while(MsgICANPop(&message))
		{	
			if(message.ucMsgEvent==Msg_MacIDCheck)
			{
				icanFrame.ucSrcMacID=icanSlave.ucMacID;		//	Դ�ڵ��ַ
				icanFrame.ucDestMacID=message.ucMsgMacID;		//	Ŀ��ڵ��ַ
				icanFrame.ucACK=ICAN_ACK_Disable;			//	��Ӧ��ʾ��
				icanFrame.ucFuncID=ICAN_Func_MacIDCheck;	//	������
				icanFrame.ucSourceID=0xFF;		//	MacIDCheck��Դ�ڵ��ַΪ0xFF
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
				icanFrame.ucSrcMacID=icanSlave.ucMacID;		//	Դ�ڵ��ַ
				icanFrame.ucDestMacID=message.ucMsgMacID;		//	Ŀ��ڵ��ַ
				icanFrame.ucACK=ICAN_ACK_Disable;			//	��Ӧ��ʾ��
				icanFrame.ucFuncID=ICAN_Func_SetConnect;	//	������
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
				icanFrame.ucSrcMacID=icanSlave.ucMacID;		//	Դ�ڵ��ַ
				icanFrame.ucDestMacID=message.ucMsgMacID;		//	Ŀ��ڵ��ַ
				icanFrame.ucACK=ICAN_ACK_Disable;			//	��Ӧ��ʾ��
				icanFrame.ucFuncID=ICAN_Func_WritePort;	//	������
				icanFrame.ucSourceID=0x20;		//	
				icanFrame.ucDataLength=1;	//	
				icanFrame.ucData[0]=0x00;	//
				 	
				ICANSend(icanFrame);

				return;
			}
			if(message.ucMsgEvent==Msg_ErrAck)
			{
				icanFrame.ucSrcMacID=icanSlave.ucMacID;		//	Դ�ڵ��ַ
				icanFrame.ucDestMacID=message.ucMsgMacID;		//	Ŀ��ڵ��ַ
				icanFrame.ucACK=ICAN_ACK_Disable;			//	��Ӧ��ʾ��
				icanFrame.ucFuncID=ICAN_Func_ErrAck;	//	������
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


