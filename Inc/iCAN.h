/*******************************************************************************
* Filename: iCAN.h	                                             	 		   *
* Description:											   			 		   *
* Author:                                                           		   *
* Date:     														 		   *
* Revision:															 		   *
*******************************************************************************/
#ifndef __ICAN_H
#define __ICAN_H

#include		"KSDsys.h"
#ifdef MICRO_CANOPEN
	#include "mco.h"
#endif
/*******************************************************************************
* CAN����														 		   																	*
*******************************************************************************/

/*******************************************************************************
* ICAN����														 		   																	*
*******************************************************************************/
#define		ICAN_SLV_NUM			8		//ICAN��վ����
#define		MACID_TOTAL				0xFF	//��վMACID��Ŷ���
//�����ʺ궨��
#define			CANBAUD_1M              0
#define			CANBAUD_500K            1
#define     CANBAUD_250K            2
#define     CANBAUD_125K            3
#define     CANBAUD_100k            4
#define     CANBAUD_50k	            5
#define     CANBAUD_25k							6
#define     CANBAUD_20k							7
#define     CANBAUD_10k							8
#define     CANBAUD_5k							9

//�����붨��
#define		ICAN_Func_WritePort 			0x01	//����д�˿�
#define		ICAN_Func_ReadPort  			0x02	//�������˿�
#define		ICAN_Func_TransTriger			0x03	//�¼���������
#define		ICAN_Func_SetConnect			0x04	//��������
#define		ICAN_Func_DelConnect			0x05	//ɾ������
#define		ICAN_Func_SlvReset				0x06	//��վ��λ
#define		ICAN_Func_MacIDCheck			0x07	//MACID���
#define		ICAN_Func_ErrAck					0x0f	//�쳣��Ӧ

//��Ӧ��ʶλ����
#define     ICAN_ACK_Enable         0	     //��ҪӦ��
#define     ICAN_ACK_Disable        1	     //����ҪӦ��

// �쳣��Ӧ�붨��
#define			ICAN_Ack_ErrFuncID			0x01	//	�����벻����
#define     ICAN_Ack_ErrSrcID 	  	0x02	//	��Դ������
#define     ICAN_Ack_ErrCommand	   	0x03	//	���֧��
#define     ICAN_Ack_ErrFuncParms	 	0x04	//	����������Ƿ�
#define     ICAN_Ack_ErrConnect			0x05	//	���Ӳ�����
#define     ICAN_Ack_ErrOperation		0x06	//	������Ч
#define     ICAN_Ack_ErrTrans	    	0x07	//	�ֶδ�����̳���

//��վ�ڵ�״̬
#define			ICAN_Slv_Idle               0		//	����
#define			ICAN_Slv_Post								1		//	���ڷ���
#define     ICAN_Slv_Pend               2		//	�ȴ�����
#define     ICAN_Slv_Finished						3		//	������ɣ��ȴ�����
#define     ICAN_Slv_Overtime           4		//	��ʱ

//��Ʒ����
#define		Prd_Move						0	//��ǣ��������
#define		Prd_Lift						1	//����������
#define		Prd_Steer						2	//ת�������
#define		Prd_Move_Second			3	//��ǣ��������
#define		Prd_Logic						4	//�߼�������
#define		Prd_HMI							5	//�Ǳ�
#define		Prd_PC							6	//PC�ն�

//��Դ�ڵ��ַ����
#define		ICAN_Addr_DI 			0x01	//����д�˿�
#define		ICAN_Addr_DO 			0x02	//�������˿�
#define		ICAN_Addr_AI			0x03	//�¼���������
#define		ICAN_Addr_AO			0x04	//��������

#pragma pack(1) //�ñ�����������ṹ��1�ֽڶ���
//�ṹ������
//#ifdef ICAN_SLAVE
//��Prd_Move�ṹ��
typedef struct _tPrd_Move
{
		//��Դ�ڵ���Ϣ
	//unsigned char  ucPageNmuber;		//	�Ǳ���ʾҳ�� 		 SoruceID:0x00
	unsigned char  ucPrdState;			//	�豸����״̬��ʾ SoruceID:0x20
	unsigned short usPrdSpd;			  //	�豸�����ٶ�		 SoruceID:0x21,0x22
	unsigned char  ucErrorCode;			//	���ϴ��� 				 SoruceID:0x23
	unsigned char  ucDIState;		    // ��������״̬      SoruceID:0x26
	unsigned char  ucDOState;		    // �������״̬      SoruceID:0x27
	unsigned char  ucThrottleInput;	//	̤������״̬     SoruceID:0x28
	unsigned char  ucMotorSpeedF;		//	�������Ƶ�� 		 SoruceID:0x2A
	unsigned short usPhaseCurrent; //	����� 		 			   SoruceID:0x2B,0x2C
	unsigned short usPhaseVoltage; //	����� 		 			   SoruceID:0x2B,0x2C
	unsigned short usBusVoltage;	  //	ĸ�ߵ�ѹ���ֽ�   SoruceID:0x2D,0x2E
	unsigned char  ucControllerTmp;	//	�������¶�       SoruceID:0x2F
	unsigned char  ucMotorTmp;			//	����¶�         SoruceID:0x30
	
}tPrd_Move;

//����Prd_Lift�ṹ��
typedef struct _tPrd_Lift
{
		//��Դ�ڵ���Ϣ
	unsigned char  ucPrdState;			//	�豸����״̬��ʾ SoruceID:0x20
	unsigned char  ucErrorCode;			//	���ϴ��� 				 SoruceID:0x23
	unsigned char  ucDIState;		    // ��������״̬      SoruceID:0x26
	unsigned char  ucDOState;		    // �������״̬      SoruceID:0x27
	unsigned char  ucThrottleInput;	//	̤������״̬     SoruceID:0x28
	unsigned char  ucAIInput;				//	ģ�������� 			 SoruceID:0x29
	unsigned char  ucMotorSpeedF;		//	�������Ƶ�� 		 SoruceID:0x2A
	unsigned short usPhaseCurrent; //	����� 		 			   SoruceID:0x2B,0x2C
	unsigned short usPhaseVoltage; //	����� 		 			   SoruceID:0x2B,0x2C
	unsigned short usBusVoltage;	  //	ĸ�ߵ�ѹ���ֽ�   SoruceID:0x2D,0x2E
	unsigned char  ucControllerTmp;	//	�������¶�       SoruceID:0x2F
	unsigned char  ucMotorTmp;			//	����¶�         SoruceID:0x30
	
}tPrd_Lift;
//��Prd_Steer�ṹ��
typedef struct _tPrd_Steer
{
		//��Դ�ڵ���Ϣ
	unsigned char  ucPrdState;			//	�豸����״̬��ʾ SoruceID:0x20
	unsigned char  ucErrorCode;			//	���ϴ��� 				 SoruceID:0x23
	unsigned short usSteerAngle;		//	ת��Ƕ�   			 SoruceID:0x24,0x25
	unsigned char  ucDIState;		    // ��������״̬      SoruceID:0x26
	unsigned char  ucDOState;		    // �������״̬      SoruceID:0x27
	unsigned char  ucDirEncoder;	  //	���������������� SoruceID:0x28,0x29
	unsigned char  ucMotorSpeedF;		//	�������Ƶ�� 		 SoruceID:0x2A
	unsigned short usPhaseCurrent; //	����� 		 			   SoruceID:0x2B,0x2C
	unsigned short usPhaseVoltage; //	����� 		 			   SoruceID:0x2B,0x2C	
	unsigned short usBusVoltage;	  //	ĸ�ߵ�ѹ���ֽ�   SoruceID:0x2D,0x2E
	unsigned char  ucControllerTmp;	//	�������¶�       SoruceID:0x2F
	unsigned char  ucMotorTmp;			//	����¶�         SoruceID:0x30
	
}tPrd_Steer;
//��Prd_Move_Sec�ṹ��
typedef struct _tPrd_Move_Sec
{
		//��Դ�ڵ���Ϣ
	unsigned char  ucPrdState;			//	�豸����״̬��ʾ SoruceID:0x20
	unsigned char  ucErrorCode;			//	���ϴ��� 				 SoruceID:0x23
	unsigned char  ucDOState;		    // �������״̬      SoruceID:0x27
	unsigned char  ucMotorSpeedF;		//	�������Ƶ�� 		 SoruceID:0x2A
	unsigned short usPhaseCurrent;  //	����� 		 			 SoruceID:0x2B,0x2C
	unsigned short usPhaseVoltage; //	����� 		 			   SoruceID:0x2B,0x2C	
	unsigned short usBusVoltage;	  //	ĸ�ߵ�ѹ���ֽ�   SoruceID:0x2D,0x2E
	unsigned char  ucControllerTmp;	//	�������¶�       SoruceID:0x2F
	unsigned char  ucMotorTmp;			//	����¶�         SoruceID:0x30
	
}tPrd_Move_Sec;
//#endif
//����iCAN֡�ṹ��
typedef struct _tICANFrame	 
{
	INT8U  ucSrcMacID;		//	Դ�ڵ��ַ
	INT8U  ucDestMacID;		//	Ŀ��ڵ��ַ
	INT8U  ucACK;					//	��Ӧ��ʶλ
	INT8U  ucFuncID;			//	������
	INT8U  ucSourceID;		//	��Դ�ڵ��ַ
	INT8U  ucDataLength;	//	��Ч���ݳ���
	INT8U  ucData[8];			//  8�ֽ�����
}tICANFrame;

//�����վ�ڵ�ṹ�壨��վ����
#define SLV_RXBUF_LEN   32
typedef struct _tICANSlave
{
	//�ڵ���Ϣ
	INT8U	ucMacID;		//	��վID
	INT8U	ucType;			//	��վ��Ʒ����
	INT32U	ulSN;			//	��վ��Ʒ���к�
	INT8U ucDILength;	//
	INT8U ucDOLength;	//
	INT8U ucAILength;	//
	INT8U ucAOLength;	//
	//����״̬
	tBoolean  bIsConnect;			//	�Ƿ�����վ��������
	INT8U  ucStatus;		//	��վ�ڵ㾵��״̬
	tBoolean  bIsOnline;			//
	INT8U     ucErrCount;		// �������
	INT8U ucTime;						//���������ݶ�д����
	//������Ϣ
	INT8U ucDataAddress;	//
	tICANFrame icanFrame;			//
	INT8U ucRxBuffer[SLV_RXBUF_LEN];	//	��վ�Ľ������ݻ�����
	INT8U ucRxBufLength;	//��վ�Ľ������ݻ�������Ч����
	//��Դ�ڵ���Ϣ
	//DI
	INT8U ucSource0x00;	//PCWorkSetting
	INT8U ucSource0x01;	
	INT8U ucSource0x02;
	INT8U ucSource0x03;
	INT8U ucSource0x04;
	INT8U ucSource0x05;
	INT8U ucSource0x06;
	INT8U ucSource0x07;
	INT8U ucSource0x08;
	INT8U ucSource0x09;
	INT8U ucSource0x0A;
	INT8U ucSource0x0B;
	INT8U ucSource0x0C;
	INT8U ucSource0x0D;
	//INDEX 1~6
	INT8U ucSource0x0E;	//PARAIndex1
	INT8U ucSource0x0F;	//PARAValueH1
	INT8U ucSource0x10;	//PARAValueL1
	INT8U ucSource0x11;	//PARAIndex2
	INT8U ucSource0x12;	//PARAValueH2
	INT8U ucSource0x13;	//PARAValueL2
	INT8U ucSource0x14;	//PARAIndex3
	INT8U ucSource0x15;	//PARAValueH3
	INT8U ucSource0x16;	//PARAValueL3
	INT8U ucSource0x17;	//PARAIndex4
	INT8U ucSource0x18;	//PARAValueH4
	INT8U ucSource0x19;	//PARAValueL4
  INT8U ucSource0x1A;	//PARAIndex5
	INT8U ucSource0x1B;	//PARAValueH5
	INT8U ucSource0x1C;	//PARAValueL5
  INT8U ucSource0x1D;	//PARAIndex6
	INT8U ucSource0x1E;	//PARAValueH6
	INT8U ucSource0x1F;	//PARAValueL6

  //DO
	INT8U ucSource0x20;		//WorkSetting
	INT8U ucSource0x21;	//�Ǳ�ICANNetCfg
	INT8U ucSource0x22;	//�Ǳ�ErrMove
	INT8U ucSource0x23;	//�Ǳ�ErrLift
	INT8U ucSource0x24;	//�Ǳ�ErrSteer
	INT8U ucSource0x25;	//�Ǳ�ErrMoveSecond
	INT8U ucSource0x26;
	INT8U ucSource0x27;
	INT8U ucSource0x28;
	INT8U ucSource0x29;
	INT8U ucSource0x2A;
	INT8U ucSource0x2B;
	INT8U ucSource0x2C;
	INT8U ucSource0x2D;
	//INDEX 1~6
	INT8U ucSource0x2E;	//PARAIndex1
	INT8U ucSource0x2F;	//PARAValueH1 
	INT8U ucSource0x30; //PARAValueL1
	INT8U ucSource0x31;	//PARAIndex2
	INT8U ucSource0x32;	//PARAValueH2
	INT8U ucSource0x33;	//PARAValueL2
	INT8U ucSource0x34;	//DIPARAIndex3
	INT8U ucSource0x35;	//PARAValueH3
	INT8U ucSource0x36;	//PARAValueL3
	INT8U ucSource0x37;	//PARAIndex4
	INT8U ucSource0x38;	//PARAValueH4
	INT8U ucSource0x39;	//PARAValueL4
	INT8U ucSource0x3A;	//PARAIndex5
	INT8U ucSource0x3B;	//PARAValueH5
	INT8U ucSource0x3C;	//PARAValueL5
	INT8U ucSource0x3D;	//PARAIndex6
	INT8U ucSource0x3E;	//PARAValueH6
	INT8U ucSource0x3F;	//PARAValueL6	

	INT8U ucSource0xE2; //��Ʒ����
}tICANSlave;

//������վ�ڵ�ṹ��
typedef struct _tICANMaster
{
	//�ڵ���Ϣ
	INT8U	ucMacID;		//	��վID
	INT8U	ucBand;  		//  ������
	INT8U	ucCycle;		//	ICAN������վ��ʱѭ����������Χ1~255����λ10ms
	//��Ʒ��Ϣ
	INT8U	ucType;			//	��վ��Ʒ����
	INT32U	ulSN;			//	��վ��Ʒ���к�
	//����״̬
	tBoolean 		bIsOnline;		//	�Ƿ�����
	INT8U  ucStatus;		//	��վ�ڵ㾵��״̬				
	//��վ��������
	INT8U  ucIdtoSlvArrayIndex[ICAN_SLV_NUM]; // ID �� ��վ��pICANSlvArray�е�λ������
	INT32U ucNetCfg;   //id connect bit flag, order by id
	tICANSlave	pICANSlvArray[ICAN_SLV_NUM];		//	�����վ���������ָ��
	INT8U ucSlvArrLength;	//	��վ����������Ч����
	INT8U ucCurSlvIndex;	//	��ǰ��ѵ��վ�ڵ�
	INT8U REMABUF[8];
}tICANMaster;

#pragma pack() //ȡ��1�ֽڶ��룬�ָ�ΪĬ��4�ֽڶ���

extern tICANMaster	icanMaster;			//������վ
extern tICANSlave icanSlave;	 //�����վ
extern void ICANSend(tICANFrame icanFrame);
extern void ICANInitialize_Master(void);		//ICAN��ʼ��
extern void ICANInitialize_Slave(void);		//ICAN��ʼ��
extern void ICANDataInManage_Master(void);
extern void ICANDataInManage_Slave(void);
extern void ICANNetManage_Master(void);
extern void ICANNetManage_Slave(void);
extern void ICANDataOutManage_Master(void);
extern void ICANDataOutManage_Slave(void);

#endif //#define __ICAN_H

