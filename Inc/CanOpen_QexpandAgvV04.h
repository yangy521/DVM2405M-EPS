/*******************************************************************************
* Filename: CanOpen_QexpandAgvV04.h	                                           *
* Description:											   			 		                               *
* Author:  QExpand, Chow                                                       *
* Date:  2019/05/24   														 		   *
* Revision:	1.04															 		                             *
*******************************************************************************/
#ifndef __CANOPEN_QEXPANDAGVV04_H
#define __CANOPEN_QEXPANDAGVV04_H

#include	"KSDsys.h"
#include  "canSTM32F4.h"
#include  "iCAN.h"

/*******************************************************************************
* CAN∂®“Â														 		   																	*
*******************************************************************************/
#define QEXPANDAGVPDOTX1_ID_OFS  0x180
#define QEXPANDAGVPDORX1_ID_OFS  0x200
#define QEXPANDAGVPDOTX2_ID_OFS  0x280
#define QEXPANDAGVPDORX2_ID_OFS  0x300
#define QEXPANDAGVPDOTX3_ID_OFS  0x380
#define QEXPANDAGVPDORX3_ID_OFS  0x400
#define QEXPANDAGVPDOTX4_ID_OFS  0x480
#define QEXPANDAGVPDORX4_ID_OFS  0x500
#define QEXPANDAGVSDOTX_ID_OFS  0x580
#define QEXPANDAGVSDORX_ID_OFS  0x600
#define NMT_MSG_ID  0x000
#define EMERG_MSG_ID_OFS  0x080

#if (LOGIC_TYPE	== Prd_Move)
#define QEXPANDAGVPDO_ID  0x18
#endif //#if (LOGIC_TYPE	== _CONTROLLER_MOVE)

#if (LOGIC_TYPE	== Prd_Lift)
#define QEXPANDAGVPDO_ID  0x09
#endif //#if (LOGIC_TYPE	== _CONTROLLER_LIFT)

#if (LOGIC_TYPE	== Prd_Steer)
#if (USER_TYPE == USER_NBRY_STEER) || (USER_TYPE == USER_HANGCHA_DDTBC_STEER) 
	#define QEXPANDAGVPDO_ID  0x60
#elif (USER_TYPE == USER_ZHONGLI)
	#define QEXPANDAGVPDO_ID  0x2C
#else
	#define QEXPANDAGVPDO_ID  0x18
#endif //#if (USER_TYPE == USER_NBRY_STEER)	
#endif //#if (LOGIC_TYPE	== _CONTROLLER_STEER)

#if (LOGIC_TYPE	== Prd_Move_Second)
#define QEXPANDAGVPDO_ID  0x0B
#endif //#if (LOGIC_TYPE	== _CONTROLLER_MOVE_SECOND)


/***** Bit define *****/
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
#define Stuffing_VCUControlWord   					(1<<15)

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
#define TX_WINDOW_ID1X9T			(200/T_MS_PLC_PERIOD)
#define TX_WINDOW_ID1XAT			(200/T_MS_PLC_PERIOD)
#define TX_WINDOW_ID1XBT			(25/T_MS_PLC_PERIOD)

/***** Struct define *****/
typedef struct _tQEXPANDAGV_PDO
{
	//Rx buf for every ID;
	INT8U CanBuf_ID1X0R[8];
	INT8U CanBuf_ID1X1R[8];
	INT8U CanBuf_ID1X2R[8];
	INT8U CanBuf_IDSDOR[8];
	INT8U CanBuf_ID1X0R_Delay;
	INT8U CanBuf_ID1X1R_Delay;
	INT8U CanBuf_ID1X2R_Delay;
	INT8U CanBuf_IDSDOR_Delay;

	//Tx buf for every ID;
	INT8U CanBuf_ID1X8T[8];
	INT8U CanBuf_ID1X9T[8];
	INT8U CanBuf_ID1XAT[8];
	INT8U CanBuf_ID1XBT[8];
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
		
	//DATA from MCU to VCU
	INT16U StateWord;       	//state word 
	INT16S SpeedMeasured;			//1 rpm
	INT16S AngleMeasured;			//0.1 centigrade
	INT16S CurrentMeasured;		//actual current 1A

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

}tQEXPANDAGV_PDO;

extern tQEXPANDAGV_PDO	QExpandAGV_PDO;

extern INT16S CanOpenInit (void);
extern INT16S CanOpenRxFrame (tCANFrame  *pCANFrame);
extern INT16S CanOpenTxFrame (void);
extern INT16S CanOpenRxFrameMonitor(void);
extern INT16S CanOpenUpdatePlcDataFromRxbuf(void);
extern INT16S CanOpenUpdateTxbufFromPlcData(void);

#endif //#define __CANOPEN_QEXPANDAGVV04_H

