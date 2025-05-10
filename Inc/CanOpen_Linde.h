/*******************************************************************************
* Filename: CanOpen_Linde.h	                                           *
* Description:											   			 		                               *
* Author:  QExpand, Chow                                                       *
* Date:  2024/05/24   														 		   *
* Revision:	1.04															 		                             *
*******************************************************************************/
#ifndef __CANOPEN_LINDE_H
#define __CANOPEN_LINDE_H

#if(CANOPEN_TYPE == CANOPEN_LINDE)

#include	"KSDsys.h"
#include  "canSTM32F4.h"
#include  "iCAN.h"

/*******************************************************************************
* CAN定义														 		   																	*
*******************************************************************************/
#define QEXPANDAGVPDOTX1_ID_OFS  0x180
#define QEXPANDAGVPDORX1_ID_OFS  0x200
#define QEXPANDAGVPDOTX2_ID_OFS  0x280
#define QEXPANDAGVPDORX2_ID_OFS  0x300
#define QEXPANDAGVPDOTX3_ID_OFS  0x380
#define QEXPANDAGVPDORX3_ID_OFS  0x400
#define QEXPANDAGVPDOTX4_ID_OFS  0x480
#define QEXPANDAGVPDORX4_ID_OFS  0x500
#define QEXPANDAGVSDOTX_ID_OFS  0x590    //MCU -> PC response
#define QEXPANDAGVSDORX_ID_OFS  0x610    //PC -> MCU request
#define NMT_MSG_ID  0x000
#define EMERG_MSG_ID_OFS  0x080
#define HEARTBEAT_ID_OFS  0x700

#define QEXPANDAGVPDO_ID  0x10

/***** Bit define *****/
//*** Bit define for CanBufRxState
#define NMT_MSG_CANBUFRXSTATE						(1 << 0)
#define RX200_CANBUFRXSTATE							(1 << 1)
#define RX300_CANBUFRXSTATE							(1 << 2)
#define RX400_CANBUFRXSTATE							(1 << 3)
#define RX500_CANBUFRXSTATE							(1 << 4)
#define RX260_CANBUFRXSTATE							(1 << 5)
#define RXSDO_CANBUFRXSTATE							(1 << 6)
#define TXSDO_CANBUFRXSTATE							(1 << 6)

//*** Bit define for ControlWord
#define AGVModeEnable_VCUControlWord				(1<<0)
#define MainConn_VCUControlWord   					(1<<1)
#define BrakeRequest_VCUControlWord   				(1<<2)
#define ForwardRequest_VCUControlWord   			(1<<3)
#define BackwardRequest_VCUControlWord   			(1<<4)
#define LiftRequest_VCUControlWord    				(1<<5)
#define FallRequest_VCUControlWord    				(1<<6)
#define Reserved_VCUControlWord   					(1<<7)
#define SpeedModeRequest_VCUControlWord    				(1<<12)
#define PosModeRequest_VCUControlWord   					(1<<13)
#define ClearFaults_VCUControlWord   					(1<<14)
#define Stuffing_VCUControlWord   						(1<<15)

//*** Bit define for StateWord
#define READY_StateWord			   			(1<<0)
#define POWER_EN_StateWord   				(1<<1)
#define EBrake_StateWord   					(1<<2)
#define AGVMode_StateWord    				(1<<3)
#define SWITCH1_StateWord    				(1<<4)
#define SWITCH2_StateWord   				(1<<5)
#define SWITCH3_StateWord   				(1<<6)
#define SWITCH4_StateWord   				(1<<7)
#define SWITCH5_StateWord   				(1<<8)
#define SWITCH6_StateWord   				(1<<9)

#define Stuffing_StateWord   				(1<<15)

/***** Period define *****/
#define T_MS_PLC_PERIOD        5
#define RX_TIMEOUT						(200/T_MS_PLC_PERIOD)

#define TX_PERIOD							(100/T_MS_PLC_PERIOD)
#define TX_PERIOD_ID1X8T			(10/T_MS_PLC_PERIOD)
#define TX_WINDOW_ID1X9T			(20/T_MS_PLC_PERIOD)
#define TX_WINDOW_ID1XAT			(30/T_MS_PLC_PERIOD)
#define TX_WINDOW_ID1XBT			(40/T_MS_PLC_PERIOD)

typedef struct tEPDGN_DATA
{
	INT16U Flag;
	
	INT8U UserByte;           //BYTE[0]   有效字节数
	INT8U FuncCode;           //BYTE[1]   功能码
	INT8U Index;          	  //BYTE[2]   参数ID
	INT16U DataL16;           //BYTE[4:3]
	INT16U DataH16;           //BYTE[6:5]	
	INT8U  TRUEDateFlag;      //真实数据标志位，若存储实际数据为AA时，该标志为1。
}tEPDGN_DATA;

//*** Bit define for tEPDGN_DATA.Flag
#define RX_FLAG													(1 << 0)
#define RDOP_FLAG												(1 << 1)
#define WROP_FLAG												(1 << 2)
#define TX_FLAG													(1 << 3)

#define READ_REQUWST                        0x21
#define READ_ANSWER_SUCCESS					0x61
#define READ_ANSWER_FAIL                    0x7F

#define MODIFY_REQUEST						0x3B
#define MODIFY_ANSWER_SUCCESS				0x7B
#define MODIFY_ANSWER_FAIL                  0x7F

//NRC反馈
#define MODIFY_ANSWER_FAIL_1				0xAA12//未找到ID或数据长度错误
#define MODIFY_ANSWER_FAIL_2				0xAA22//写入条件失败
#define MODIFY_ANSWER_FAIL_3				0xAA31//写入数据超出范围
#define MODIFY_ANSWER_FAIL_4				0xAA22//请求速度过快，正在处理其他数据

//参数范围
#define CONFIGURE_PARA_START                1
#define CONFIGURE_PARA_END                  201

#define MONITOR_PARA_START                  210
#define MONITOR_PARA_END					250

/***** Struct define *****/
typedef struct _tQEXPANDAGV_PDO
{
	//Rx buf for every ID;
	INT8U CanBuf_ID1X0R[8];
	INT8U CanBuf_ID1X1R[8];
	INT8U CanBuf_ID1X2R[8];
	INT8U CanBuf_IDSDOR[8];
	INT8U CanBuf_ID260R[8];
	INT16U CanBuf_ID1X0R_Delay;
	INT16U CanBuf_ID1X1R_Delay;
	INT16U CanBuf_ID1X2R_Delay;
	INT16U CanBuf_IDSDOR_Delay;	
	INT16U CanBuf_ID260R_Delay;
	INT16U CanBufRxState;

	//Tx buf for every ID;
	INT8U CanBuf_ID1X8T[8];
	INT8U CanBuf_ID1X9T[8];
	INT8U CanBuf_ID1XAT[8];
	INT8U CanBuf_ID1XBT[8];
	INT8U CanBuf_IDSDOT[8];
	INT16U CanBufTxState;
	INT32S TxCnt;							//Tx time period counter
	
	//DATA from VCU to MCU
	INT16U  VCUControlWord;
	INT16S	VCUCmdSpeed;	  	//1 rpm
	INT16S	VCUCmdAngle;	  	//0.1 centigrade
	INT8U		VCUCmdTorque;	  	//255 = max torque
	INT8U		VCUCmdTorqueBrk;	//255 = max torque

	INT8U		VCUPedalBrake;		//brake target  0~255
	INT8U		VCUCmdPump;	 			//DC pump control  0~255
	INT8U		VCUCmdEVP;	 			//EVP target  0~255
	INT8U		VCUCmdEVP1;	 			//EVP target  0~255
	
	//DATA from MOVE to STEER 0x260
	INT16S	MoveSpeedFdb;	 //km/h
	INT8U	ErrorMove;	 //ErrorMove
		
	//DATA from MCU to VCU
	INT16U StateWord;       	//state word 
	INT16S SpeedMeasured;			//1 rpm
	INT16S AngleMeasured;			//0.1 centigrade
	INT16S CurrentMeasured;		//actual current 1A
	
	INT16S Current;			//0.1A
	INT16U PotVolt;			//0-32767   0-100%
	INT16S BoardTmp;		//board temperatrue 0.1℃

	INT8U  ErrorCode;					//alarm/error code
	INT8U  MotorTemperature; 	//tmp + 40 
	INT8S  BoardTemperature;	//tmp	
	INT8U  BDIPercent; 				//battery BDI percent
	INT8U  AnalogInput1;      //0~255
	INT8U  AnalogInput2;      //0~255
	INT8U  Reserved;       
	INT8U  SoftwareVersion; 	
	
	//Emergency message,send one time on alarm change
//	INT16U CANopenAlmCode;
	INT8U  IsInAlarm; 
	INT8U  AlarmCode; 

	INT16U AgvHeartBeat;   
	INT16U AgvMode;    
	INT16U AgvHeartBeatError;   
    INT8U u8HeartBeatTrig;

	tEPDGN_DATA DgnDataRxTx;

}tQEXPANDAGV_PDO;

extern tQEXPANDAGV_PDO	QExpandAGV_PDO;

extern INT16S CanOpenInit (void);
extern INT16S CanOpenRxFrame (tCANFrame  *pCANFrame);
extern INT16S CanOpenTxFrame (void);
extern INT16S CanOpenRxFrameMonitor(void);
extern INT16S CanOpenUpdatePlcDataFromRxbuf(void);
extern INT16S CanOpenUpdateTxbufFromPlcData(void);

#endif
#endif //#define __CANOPEN_LINDE_H

