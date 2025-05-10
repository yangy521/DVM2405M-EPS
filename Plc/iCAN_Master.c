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

tICANMaster	icanMaster;			//������վ

void ICANInitialize_Master()	
{
	//��Ϣ���г�ʼ��
  //MsgInitialize();
	
	//��վ�ڵ��ʼ��
	icanMaster.ucMacID=0x00;	//
	icanMaster.ucBand=CANBAUD_500K;	//
	icanMaster.ucCycle=1;	//
	icanMaster.ucType=Prd_Move;	//
	icanMaster.ulSN=0x00;	//
	icanMaster.bIsOnline=false;	//
	icanMaster.ucSlvArrLength=1;	//
	icanMaster.ucCurSlvIndex=0;
	//CAN��������ʼ��
	canFrmRxBuffer.ucWrite=0;	    //��ǰдλ��
	canFrmRxBuffer.ucRead=0;	    //��ǰ��λ��
	canFrmTxBuffer.ucWrite=0;	    //��ǰдλ��
	canFrmTxBuffer.ucRead=0;	    //��ǰ��λ��
	
}


//��Ӵ�վ����
void ICANAddSlave(INT8U ucMacID, INT8U ucProductType)
{
	INT8U i;
	tICANSlave *pSlave;
	//����Ѵ����ڴ�վ�����б��У��˳�
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
	//�ڵ���Ϣ
	pSlave->ucMacID=ucMacID;			 //	��վID
	pSlave->ucType=ucProductType;	    //	��վ��Ʒ����
	pSlave->ulSN=0x00;			//	��վ��Ʒ���к�
	pSlave->ucDILength=0;	//
	pSlave->ucDOLength=0;	//
	pSlave->ucAILength=0;	//
	pSlave->ucAOLength=0;	//
	//����״̬
	pSlave->bIsConnect=false;			//	�Ƿ�����վ��������
	pSlave->ucStatus=ICAN_Slv_Idle;		//	��վ�ڵ㾵��״̬
	//�������ݻ���
	pSlave->ucRxBufLength=0;	//��վ�Ľ������ݻ�������Ч����
	//������Ϣ
	pSlave->ucDataAddress=ICAN_Addr_DI;	//
	//��Դ�ڵ���Ϣ
	pSlave->ucSource0x00=0x00;	//0x00
	pSlave->ucSource0x01=0x00;	//0x01
	pSlave->ucSource0x02=0;	//0x02
	pSlave->ucSource0x03=0x00;	//0x03
	pSlave->ucSource0x20=0x00;	//0x20
	pSlave->ucSource0x21=0x00;	//0x21
	pSlave->ucSource0xE2=0x00;	//0xE2

	icanMaster.ucSlvArrLength++;	
}

//ICAN����ɾ����վ
void ICANDelSlave(INT8U ucMacID)
{
	INT8U i;
	if(ucMacID==MACID_TOTAL)	//ɾ�����д�վ
	{
		for(i=1;i<icanMaster.ucSlvArrLength;i++)
		{
			//�ڵ���Ϣ
			icanMaster.pICANSlvArray[i].ucMacID=0x00;			 //	��վID
			icanMaster.pICANSlvArray[i].ucType=0x00;	    //	��վ��Ʒ����
			icanMaster.pICANSlvArray[i].ulSN=0x00;			//	��վ��Ʒ���к�
			icanMaster.pICANSlvArray[i].ucDILength=0;	//
			icanMaster.pICANSlvArray[i].ucDOLength=0;	//
			icanMaster.pICANSlvArray[i].ucAILength=0;	//
			icanMaster.pICANSlvArray[i].ucAOLength=0;	//
			//����״̬
			icanMaster.pICANSlvArray[i].bIsConnect=false;			//	�Ƿ�����վ��������
			icanMaster.pICANSlvArray[i].ucStatus=ICAN_Slv_Idle;		//	��վ�ڵ㾵��״̬
			//������Ϣ
			icanMaster.pICANSlvArray[i].ucDataAddress=ICAN_Addr_DI;	//
			icanMaster.pICANSlvArray[i].ucRxBufLength=0;	//��վ�Ľ������ݻ�������Ч����
			//��Դ�ڵ���Ϣ
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
	else if(ucMacID>0&&ucMacID<64) //ɾ��������վ	kff
	{
			
	}	
}

//ICAN����
void ICANSend(tICANFrame icanFrame)
{
	INT8U i;
	unsigned long  ucSrcMacID;	//	Դ�ڵ��ַ
	unsigned long  ucDestMacID;	//	Ŀ��ڵ��ַ
	unsigned long  ucACK;		//	��Ӧ��ʶλ
	unsigned long  ucFuncID;	//	������
	unsigned long  ucSourceID;		//	��Դ�ڵ��ַ
	tCANFrame canFrame;	//

	ucSrcMacID=icanFrame.ucSrcMacID;
	ucDestMacID=icanFrame.ucDestMacID;
	ucACK=icanFrame.ucACK;
	ucFuncID=icanFrame.ucFuncID;
	ucSourceID=icanFrame.ucSourceID;
		
	canFrame.ulID=(ucSrcMacID<<21)+(ucDestMacID<<13)+(ucACK<<12)+(ucFuncID<<8)+ucSourceID;
	canFrame.ucXID=1;			//0 ��׼֡��1 ��չ֡  
    canFrame.ucDataLength=icanFrame.ucDataLength;		//���ݳ�����
	//
	for(i=0;i<icanFrame.ucDataLength;i++)
	{
		canFrame.ucData[i]=icanFrame.ucData[i];
	}

	CANWriteBuffer(&canFrmTxBuffer, &canFrame);
//	CANFrmSend(&canFrmTxBuffer);	
}

//MacID���
void ICANMacIDCheck(void)
{
	tICANFrame icanFrame;

	icanFrame.ucSrcMacID=icanMaster.ucMacID;		//	Դ�ڵ��ַ
	icanFrame.ucDestMacID=icanMaster.ucMacID;		//	Ŀ��ڵ��ַ
	icanFrame.ucACK=ICAN_ACK_Enable;			//	��Ӧ��ʶλ
	icanFrame.ucFuncID=ICAN_Func_MacIDCheck;	//	������
	icanFrame.ucSourceID=0xFF;		//	MacIDCheck��Դ�ڵ��ַΪ0xFF
	icanFrame.ucDataLength=0x06;	//	��Ч���ݳ���
	//6�ֽ�����
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

//ICAN��������
void ICANSetConnect(tICANSlave *pICANSlave)
{
	tICANFrame icanFrame;

	if(pICANSlave->ucStatus==ICAN_Slv_Idle)
	{
		icanFrame.ucSrcMacID=icanMaster.ucMacID;		//	Դ�ڵ��ַ
		icanFrame.ucDestMacID=pICANSlave->ucMacID;		//	Ŀ��ڵ��ַ
		icanFrame.ucACK=ICAN_ACK_Enable;			//	��Ӧ��ʶλ
		icanFrame.ucFuncID=ICAN_Func_SetConnect;	//	������
		icanFrame.ucSourceID=0xF7;		//	SetConnect��Դ�ڵ��ַΪ0xF7
		icanFrame.ucDataLength=0x03;	//	��Ч���ݳ���
		icanFrame.ucData[0]=0x00;	//3�ֽ�����
		icanFrame.ucData[1]=icanMaster.ucMacID;
 		icanFrame.ucData[2]=0xFF;	//��վͨѶ��ʱ����Ϊ����λ10ms

		pICANSlave->ucStatus=ICAN_Slv_Post;

		pICANSlave->icanFrame.ucSrcMacID=icanMaster.ucMacID;		//	Դ�ڵ��ַ
		pICANSlave->icanFrame.ucDestMacID=pICANSlave->ucMacID;		//	Ŀ��ڵ��ַ
		pICANSlave->icanFrame.ucACK=ICAN_ACK_Enable;			//	��Ӧ��ʶλ
		pICANSlave->icanFrame.ucFuncID=ICAN_Func_SetConnect;	//	������
		pICANSlave->icanFrame.ucSourceID=0xF7;		//	SetConnect��Դ�ڵ��ַΪ0xF7
		pICANSlave->icanFrame.ucDataLength=0x03;	//	��Ч���ݳ���
		pICANSlave->icanFrame.ucData[0]=0x00;	//3�ֽ�����
		pICANSlave->icanFrame.ucData[1]=icanMaster.ucMacID;
 		pICANSlave->icanFrame.ucData[2]=0xFF;	//��վͨѶ��ʱ����Ϊ����λ10ms
		pICANSlave->icanFrame.ucData[3]=0x00;
		pICANSlave->icanFrame.ucData[4]=0x00;
		pICANSlave->icanFrame.ucData[5]=0x00;
		pICANSlave->icanFrame.ucData[6]=0x00;
		pICANSlave->icanFrame.ucData[7]=0x00;

		ICANSend(icanFrame);
	}
}

//ICAN����
void ICANReceive(tICANSlave *pICANSlave,tCANFrame *pCANFrame)
{
//	INT8U i;
//	INT8U ucSrcMacID;
	INT8U ucACK;
	INT8U ucFuncID;
	INT8U ucSourceID;
//	INT8U ucDataLength;
	tICANFrame icanFrame;
	
//	ucSrcMacID = (pCANFrame->ulID >> 21) & 0x000000FF; // ԭ�ڵ��ַ(ID28-ID21)
	ucACK = (pCANFrame->ulID >> 12) & 0x00000001; // Ӧ���־��ID12�� 
    ucFuncID = (pCANFrame->ulID >> 8) & 0x000000F; // �����루ID11��ID8�� 
	ucSourceID = pCANFrame->ulID & 0x000000FF; // ��Դ�ڵ��ţ�ID7��ID0��
//	ucDataLength=pCANFrame->ucDataLength;	//���ݳ���

	//�����վδ���ߣ�ֻ��MacID���������Ӧ
	if(icanMaster.bIsOnline==false)
	{
		if(ucFuncID!=ICAN_Func_MacIDCheck)
		{
			return;
		}
	}

	//��ҪӦ��(��վ��MACID���֡��	
	if(ucACK==ICAN_ACK_Enable) 
	{
		//�жϹ�����
		if(ucFuncID==ICAN_Func_MacIDCheck)	//��վMACID���
		{
			if(icanMaster.ucMacID==pICANSlave->ucMacID)	//MACID�����Ч
			{
				//����MACIDӦ��֡
				icanFrame.ucSrcMacID=icanMaster.ucMacID;		//	Դ�ڵ��ַ
				icanFrame.ucDestMacID=pICANSlave->ucMacID;		//	Ŀ��ڵ��ַ
				icanFrame.ucACK=ICAN_ACK_Disable;			//	��Ӧ��ʶλ
				icanFrame.ucFuncID=ICAN_Func_MacIDCheck;	//	������
				icanFrame.ucSourceID=0xFF;		//	MacIDCheck��Դ�ڵ��ַΪ0xFA
				icanFrame.ucDataLength=0x06;	//	��Ч���ݳ���
				//6�ֽ�����
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
	//����ҪӦ��
	if(ucACK==ICAN_ACK_Disable)
	{
		//��⹦����
		if(ucFuncID==ICAN_Func_WritePort)  //����д�˿�
		{
			//delete 20150311
		//if((ucFuncID==pICANSlave->icanFrame.ucFuncID)&&(ucSourceID==pICANSlave->icanFrame.ucSourceID))
			{
				pICANSlave->ucStatus=ICAN_Slv_Idle;	//���ýڵ�״̬
				ResetNetTimer(pICANSlave->ucMacID);  //��λ���ͳ�ʱ��ʱ��
			}	
		}
		else if(ucFuncID==ICAN_Func_ReadPort)  //�������˿�
		{
			if(ucFuncID==pICANSlave->icanFrame.ucFuncID)//&&(ucSourceID==pICANSlave->icanFrame.ucSourceID))
			{

				if(ucSourceID==0x00)
				{
					if(pCANFrame->ucData[0]==0x00)	//û�зֶ�
					{
						
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
// 						if(pCANFrame->ucData[0]==0x40)	//��ʼ֡
// 							{
// 								pICANSlave->ucSource0x0E=pCANFrame->ucData[1];
// 								pICANSlave->ucSource0x0F=pCANFrame->ucData[2];
// 								pICANSlave->ucSource0x10=pCANFrame->ucData[3];	//
// 								pICANSlave->ucSource0x11=pCANFrame->ucData[4];	//
// 								pICANSlave->ucSource0x12=pCANFrame->ucData[5];	//
// 								pICANSlave->ucSource0x13=pCANFrame->ucData[6];	//
// 								pICANSlave->ucSource0x14=pCANFrame->ucData[7];	//	
// 							}		
// 							else if(pCANFrame->ucData[0]==0x81)	//��β֡
// 							{
// 								pICANSlave->ucSource0x15=pCANFrame->ucData[1];
// 								pICANSlave->ucSource0x16=pCANFrame->ucData[2];
// 								pICANSlave->ucSource0x17=pCANFrame->ucData[3];	//
// 								pICANSlave->ucSource0x18=pCANFrame->ucData[4];	//
// 								pICANSlave->ucSource0x19=pCANFrame->ucData[5];	//
// 								pICANSlave->ucSource0x1A=pCANFrame->ucData[6];	//
// 								pICANSlave->ucSource0x1B=pCANFrame->ucData[7];	//
// 							}		
// 						if(pCANFrame->ucData[0]==0xC0)	//��ʼ֡
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
				pICANSlave->ucStatus=ICAN_Slv_Idle;	//���ýڵ�״̬
				ResetNetTimer(pICANSlave->ucMacID);  //��λ���ͳ�ʱ��ʱ��
			}		
		}
		else if(ucFuncID==ICAN_Func_TransTriger)  //�¼���������
		{
		}
		else if(ucFuncID==ICAN_Func_SetConnect)  //��������
		{
			if((ucFuncID==pICANSlave->icanFrame.ucFuncID)&&(ucSourceID==pICANSlave->icanFrame.ucSourceID))
			{
				pICANSlave->ucDILength=pCANFrame->ucData[1];
				pICANSlave->ucDOLength=pCANFrame->ucData[2];
				pICANSlave->ucAILength=pCANFrame->ucData[3];
				pICANSlave->ucAOLength=pCANFrame->ucData[4];
			
				pICANSlave->ucStatus=ICAN_Slv_Idle;	//���ýڵ�״̬
				pICANSlave->bIsConnect=true;	//���ý�������
			}
		}
		else if(ucFuncID==ICAN_Func_DelConnect)  //ɾ������
		{
		}
		else if(ucFuncID==ICAN_Func_SlvReset)	//��վ��λ
		{
		}
		else if(ucFuncID==ICAN_Func_MacIDCheck)  //���յ���վ������MACID������
		{
			icanMaster.ucStatus=ICAN_Slv_Idle;
			SL_SET(ICAN_MACIDCHECK_ERR);
			MCL_SetFault(ICAN_MACIDCHECK_ERR);
			icanMaster.bIsOnline=false;   //off line 
			KillNetTimer(Timer_MacIDCheck);
		}
		else if(ucFuncID==ICAN_Func_ErrAck)  //�쳣��Ӧ
		{
			if(pCANFrame->ucData[1]==0x05)	//�쳣��Ӧ�룺���Ӳ�����
			{
				pICANSlave->bIsConnect=false;	//�Ͽ�����
				pICANSlave->ucStatus=ICAN_Slv_Idle;
			}
			if(pCANFrame->ucData[1]==0x07)	//�쳣��Ӧ�룺������̳���
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

	//��CAN���ݻ������ж�ȡCAN����֡��������Ӧ����վ������
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
		pICANSlave=icanMaster.pICANSlvArray;	 

	//�Զ�ע���վ���� add:20150301
		ucSrcMacID = (canFrame.ulID >> 21) & 0x000000FF; // Դ�ڵ��ţ�ID28��ID21��
		ucDestMacID = (canFrame.ulID >> 13) & 0x000000FF; // Ŀ��ڵ��ţ�ID20��ID13�� 
	  ucACK = (canFrame.ulID >> 12) & 0x00000001; // Ӧ���־��ID12�� 
    ucFuncID = (canFrame.ulID >> 8) & 0x000000F; // �����루ID11��ID8�� 
		
		//Add:20150310
		if(ucFuncID==ICAN_Func_MacIDCheck && ucSrcMacID!=icanMaster.ucMacID) //��վ��MACID���֡
		{
				//��վ���ϵ�
				if(ucACK==ICAN_ACK_Enable) 
				{
				//	pICANSlave->ucStatus=ICAN_Slv_Idle;
					KillNetTimer(Timer_MacIDCheck);
					ICANAddSlave(ucSrcMacID, 0);					
				}
			//��վ���ϵ磬��վ����վ��MACID����֡������Ӧ�� 
				else 
				{
					//pICANSlave->ucStatus=ICAN_Slv_Idle;
					ICANAddSlave(ucSrcMacID, 0);
				}
		}
		else if(ucFuncID==ICAN_Func_MacIDCheck && ucSrcMacID==icanMaster.ucMacID) //�����վ
		{
				//����վ���ϵ�
				if(ucACK==ICAN_ACK_Enable) 
				{
					//����MACIDӦ��֡
					icanFrame.ucSrcMacID=icanMaster.ucMacID;		//	Դ�ڵ��ַ
					icanFrame.ucDestMacID=pICANSlave->ucMacID;		//	Ŀ��ڵ��ַ
					icanFrame.ucACK=ICAN_ACK_Disable;			//	��Ӧ��ʶλ
					icanFrame.ucFuncID=ICAN_Func_MacIDCheck;	//	������
					icanFrame.ucSourceID=0xFF;		//	MacIDCheck��Դ�ڵ��ַΪ0xFA
					icanFrame.ucDataLength=0x06;	//	��Ч���ݳ���
					//6�ֽ�����
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
				else 		//����վ���ϵ磬offline
				{
					pICANSlave->ucStatus=ICAN_Slv_Idle;
          SL_SET(ICAN_MACIDCHECK_ERR);
					MCL_SetFault(ICAN_MACIDCHECK_ERR);
					KillNetTimer(Timer_MacIDCheck);
					icanMaster.bIsOnline=false;
				}	
	
		}
			
		//����������֡��Ӧ����վ����
		for(i=1;i<icanMaster.ucSlvArrLength;i++)
//		for(i=0;i<icanMaster.ucSlvArrLength;i++)
		{ 
			ucSrcMacID = (canFrame.ulID >> 21) & 0x000000FF; // Դ�ڵ��ţ�ID28��ID21��
			ucDestMacID = (canFrame.ulID >> 13) & 0x000000FF; // Ŀ��ڵ��ţ�ID20��ID13��  
			if(((pICANSlave+i)->ucMacID==ucSrcMacID)&&(icanMaster.ucMacID==ucDestMacID))
			{
				ICANReceive(pICANSlave+i,&canFrame);	//ICAN����

			} 
		} 
	}  	
}

//
void ICANNetManage_Master(void)
{
	INT8U i;
	tICANSlave *pICANSlave;
	//MacID��ⳬʱ����
	if(netTimer[Timer_MacIDCheck].bIsOvertime)
	{
		icanMaster.bIsOnline=true;
		icanMaster.ucStatus=ICAN_Slv_Idle;
		KillNetTimer(Timer_MacIDCheck);
	}

	//���ͳ�ʱ����
	for(i=1;i<icanMaster.ucSlvArrLength;i++)
	{
		pICANSlave=icanMaster.pICANSlvArray+i;
		//�������Ͷ�ʱ��
		if((pICANSlave->ucStatus==ICAN_Slv_Post)&&(netTimer[pICANSlave->ucMacID].bIsStart==false))
		{
//			SetNetTimer(pICANSlave->ucMacID,200);
			SetNetTimer(pICANSlave->ucMacID,1000);
		}
		//վ��ͨ�ų�ʱ����
		if(netTimer[pICANSlave->ucMacID].bIsOvertime)
		{
			if(pICANSlave->bIsConnect==false)//���δ��������	
			{				
				pICANSlave->ucStatus=ICAN_Slv_Idle;
				AlarmICANRegister(pICANSlave->ucMacID,Msg_Err_ICANConnect);
				
			}
			else //����ѽ�������
			{			
				pICANSlave->bIsConnect=false;	//�Ͽ�����
				pICANSlave->ucStatus=ICAN_Slv_Idle;				
			}
		}
		//ɾ�����綨ʱ��
		if(pICANSlave->ucStatus==ICAN_Slv_Idle)
		{
			KillNetTimer(pICANSlave->ucMacID);	
		}
	}
	//��ǰ��վ��ѵ�ڵ��趨
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
  * ������: 	ICAN_DOProc()
  * ����:   	pICANSlave ��վ����
  * ����������DO����Source0x20~Source0x3F
  * ����ֵ��	NULL
  ********************************************************************/
void ICAN_DOProc(tICANSlave *pICANSlave)
{
//		unsigned char  index;
//		unsigned long  ucSrcMacID;	//	Դ�ڵ��ַ
//		unsigned long  ucDestMacID;	//	Ŀ��ڵ��ַ
//		unsigned long  ucACK;		//	��Ӧ��ʶλ
//		unsigned long  ucFuncID;	//	������
//		unsigned long  ucSourceID;		//	��Դ�ڵ��ַ
//	
//		tCANFrame canFrame[5];	//
//	
//			ucSrcMacID=icanMaster.ucMacID;		//	Դ�ڵ��ַ;
//			ucDestMacID=pICANSlave->ucMacID;		//	Ŀ��ڵ��ַ
//			ucACK=ICAN_ACK_Enable;			//	��Ӧ��ʶλ;
//			ucFuncID=ICAN_Func_WritePort;	//	������
//	
//			ucSourceID=0x20;		//	��Դ�ڵ㡪��DO��ַΪ0x20

//			canFrame[0].ulID=(ucSrcMacID<<21)+(ucDestMacID<<13)+(ucACK<<12)+(ucFuncID<<8)+ucSourceID;
//			canFrame[0].ucXID=1;			//0 ��׼֡��1 ��չ֡ 
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
//			canFrame[1].ucXID=1;			//0 ��׼֡��1 ��չ֡ 
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
//			canFrame[2].ucXID=1;			//0 ��׼֡��1 ��չ֡ 
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
//			canFrame[3].ucXID=1;			//0 ��׼֡��1 ��չ֡ 
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
//			canFrame[4].ucXID=1;			//0 ��׼֡��1 ��չ֡ 
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
//			//���ͻ���������
//			CANFrmSend(&canFrmTxBuffer);	

		unsigned long  ucSrcMacID;	//	Դ�ڵ��ַ
		unsigned long  ucDestMacID;	//	Ŀ��ڵ��ַ
		unsigned long  ucACK;		//	��Ӧ��ʶλ
		unsigned long  ucFuncID;	//	������
		unsigned long  ucSourceID;		//	��Դ�ڵ��ַ
	//	tICANSlave *pICANSlave;
		tCANFrame canFrame;	//
	
			ucSrcMacID=icanMaster.ucMacID;		//	Դ�ڵ��ַ;
			ucDestMacID=pICANSlave->ucMacID;		//	Ŀ��ڵ��ַ
			ucACK=ICAN_ACK_Enable;			//	��Ӧ��ʶλ;
			ucFuncID=ICAN_Func_WritePort;	//	������
	
			ucSourceID=0x20;		//	��Դ�ڵ㡪��DO��ַΪ0x20

			canFrame.ulID=(ucSrcMacID<<21)+(ucDestMacID<<13)+(ucACK<<12)+(ucFuncID<<8)+ucSourceID;
			canFrame.ucXID=1;			//0 ��׼֡��1 ��չ֡ 
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
					
			//���ͻ���������
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
	//MacID���
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
	// ��������
	//
	if(icanMaster.ucCurSlvIndex >0)	//�������Ӷ���Ϊ��վ
	{
		pICANSlave=icanMaster.pICANSlvArray+icanMaster.ucCurSlvIndex;
		if((pICANSlave->bIsConnect==false)&&(pICANSlave->ucStatus==ICAN_Slv_Idle))
		{
			ICANSetConnect(pICANSlave);
			goto END;
		}
	}
	//
	//ICAN��Ϣ�¼�����
	//
	while(MsgICANPop(&message))
	{		
		for(i=1;i<icanMaster.ucSlvArrLength;i++)
		{
			pICANSlave=icanMaster.pICANSlvArray+i;
			if(pICANSlave->ucMacID==message.ucMsgMacID)
			{
				if((pICANSlave->bIsConnect==false)||(pICANSlave->ucStatus!=ICAN_Slv_Idle))//�жϵ�ǰ�ڵ��Ƿ����
				{
					MsgAdd(Msg_Type_ICAN,message);
					goto END;
				}
				else
				{
					if(message.ucMsgEvent==Msg_ReadPrdType)
					{
						icanFrame.ucSrcMacID=icanMaster.ucMacID;		//	Դ�ڵ��ַ
						icanFrame.ucDestMacID=message.ucMsgMacID;		//	Ŀ��ڵ��ַ
						icanFrame.ucACK=ICAN_ACK_Enable;			//	��Ӧ��ʶλ
						icanFrame.ucFuncID=ICAN_Func_ReadPort;	//	������
						icanFrame.ucSourceID=0xE2;		//	��Դ�ڵ㡪�����͵�ַΪ0xE2
						icanFrame.ucDataLength=2;	//	��Ч���ݳ���
						icanFrame.ucData[0]=0x00;	//
						icanFrame.ucData[1]=1;
				 	
						pICANSlave->ucStatus=ICAN_Slv_Post;
						
						pICANSlave->icanFrame.ucSrcMacID=icanMaster.ucMacID;		//	Դ�ڵ��ַ
						pICANSlave->icanFrame.ucDestMacID=message.ucMsgMacID;		//	Ŀ��ڵ��ַ
						pICANSlave->icanFrame.ucACK=ICAN_ACK_Enable;			//	��Ӧ��ʶλ
						pICANSlave->icanFrame.ucFuncID=ICAN_Func_ReadPort;	//	������
						pICANSlave->icanFrame.ucSourceID=0xE2;		//	��Դ�ڵ㡪�����͵�ַΪ0xE2
						pICANSlave->icanFrame.ucDataLength=2;	//	��Ч���ݳ���
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
						icanFrame.ucSrcMacID=pICANSlave->icanFrame.ucSrcMacID;		//	Դ�ڵ��ַ
						icanFrame.ucDestMacID=pICANSlave->icanFrame.ucDestMacID;		//	Ŀ��ڵ��ַ
						icanFrame.ucACK=pICANSlave->icanFrame.ucACK;			//	��Ӧ��ʶλ
						icanFrame.ucFuncID=pICANSlave->icanFrame.ucFuncID;	//	������
						icanFrame.ucSourceID=pICANSlave->icanFrame.ucSourceID;		//	��Դ�ڵ㡪�����͵�ַΪ0xE2
						icanFrame.ucDataLength=pICANSlave->icanFrame.ucDataLength;	//	��Ч���ݳ���
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
	//��ѯ��Դ�ڵ㣨DI��DO��AI��AO��
	//
	if(icanMaster.ucCurSlvIndex!=0)	//�������Ӷ���Ϊ��վ	
	{
		if(pICANSlave->ucDataAddress==ICAN_Addr_DI)	//DI
		{
			if((pICANSlave->bIsConnect==true)&&(pICANSlave->ucStatus==ICAN_Slv_Idle))
			{
				icanFrame.ucSrcMacID=icanMaster.ucMacID;		//	Դ�ڵ��ַ
				icanFrame.ucDestMacID=pICANSlave->ucMacID;		//	Ŀ��ڵ��ַ
				icanFrame.ucACK=ICAN_ACK_Enable;			//	��Ӧ��ʶλ
				icanFrame.ucFuncID=ICAN_Func_ReadPort;	//	������
				icanFrame.ucSourceID=0x00;		//	��Դ�ڵ㡪��DI��ַΪ0x00
				icanFrame.ucDataLength=2;	//	��Ч���ݳ���
				icanFrame.ucData[0]=0x00;	//
				icanFrame.ucData[1]=pICANSlave->ucDILength;
		 	
				pICANSlave->ucStatus=ICAN_Slv_Post;
				
				pICANSlave->icanFrame.ucSrcMacID=icanMaster.ucMacID;		//	Դ�ڵ��ַ
				pICANSlave->icanFrame.ucDestMacID=pICANSlave->ucMacID;		//	Ŀ��ڵ��ַ
				pICANSlave->icanFrame.ucACK=ICAN_ACK_Enable;			//	��Ӧ��ʶλ
				pICANSlave->icanFrame.ucFuncID=ICAN_Func_ReadPort;	//	������
				pICANSlave->icanFrame.ucSourceID=0x00;		//	��Դ�ڵ㡪��DI��ַΪ0x00
				pICANSlave->icanFrame.ucDataLength=2;	//	��Ч���ݳ���
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
//				icanFrame.ucSrcMacID=icanMaster.ucMacID;		//	Դ�ڵ��ַ
//				icanFrame.ucDestMacID=pICANSlave->ucMacID;		//	Ŀ��ڵ��ַ
//				icanFrame.ucACK=ICAN_ACK_Enable;			//	��Ӧ��ʶλ
//				icanFrame.ucFuncID=ICAN_Func_WritePort;	//	������
//				icanFrame.ucSourceID=0x20;		//	��Դ�ڵ㡪��DO��ַΪ0x20
//				icanFrame.ucDataLength=pICANSlave->ucDOLength+1;	//	��Ч���ݳ���
//				icanFrame.ucData[0]=0x00;	//
//				icanFrame.ucData[1]=pICANSlave->ucSource0x20;
//				icanFrame.ucData[2]=pICANSlave->ucSource0x21;	
				

//				ucSrcMacID=icanMaster.ucMacID;		//	Դ�ڵ��ַ;
//				ucDestMacID=pICANSlave->ucMacID;		//	Ŀ��ڵ��ַ
//				ucACK=ICAN_ACK_Enable;			//	��Ӧ��ʶλ;
//				ucFuncID=ICAN_Func_WritePort;	//	������
//				ucSourceID=0x20;		//	��Դ�ڵ㡪��DO��ַΪ0x20
//					
//				canFrame.ulID=(ucSrcMacID<<21)+(ucDestMacID<<13)+(ucACK<<12)+(ucFuncID<<8)+ucSourceID;
//				canFrame.ucXID=1;			//0 ��׼֡��1 ��չ֡ 
//				canFrame.ucDataLength=8;
					
				pICANSlave->ucStatus=ICAN_Slv_Post;	
					
				ICAN_DOProc(pICANSlave); //DO
		
				pICANSlave->ucDataAddress=ICAN_Addr_DI;
				}
			}
		}
		END: ;		
	}


