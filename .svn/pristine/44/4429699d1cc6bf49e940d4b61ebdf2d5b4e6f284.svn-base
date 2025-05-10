/*******************************************************************************
* Filename: CanOpen_QexpandAgv.h	                                           *
* Description:											   			 		                               *
* Author:                                                           		       *
* Date:     														 		                                   *
* Revision:															 		                                   *
*******************************************************************************/
#ifndef __CANOPEN_QEXPANDAGVV00_H
#define __CANOPEN_QEXPANDAGVV00_H

#include		"KSDsys.h"
#include  "canSTM32F4.h"


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

#if (LOGIC_TYPE	== Prd_Move)
#define QEXPANDAGVPDO_ID  0x18

#elif (LOGIC_TYPE	== Prd_Move_Second)
#define QEXPANDAGVPDO_ID  0x09

#elif (LOGIC_TYPE	== Prd_Steer)
#define QEXPANDAGVPDO_ID  0x18

#endif 

/***** Bit define *****/
//*** Bit define for ControlWord
#define ForwardRequest_VCUControlWord   		(1<<0)
#define BackwardRequest_VCUControlWord   		(1<<1)
#define LiftRequest_VCUControlWord    			(1<<2)
#define FallRequest_VCUControlWord    			(1<<3)
#define BrakeRequest_VCUControlWord   			(1<<4)
#define Reserved_VCUControlWord   					(1<<5)
#define AGVModeRequest_VCUControlWord   		(1<<6)
#define Stuffing_VCUControlWord   					(1<<7)
//*** Bit define for StateWord
#define Reserved1_StateWord   			(1<<0)
#define Reserved2_StateWord   			(1<<1)
#define POWER_EN_StateWord   				(1<<2)
#define SVON_StateWord    					(1<<3)
#define INIT_StateWord    					(1<<4)
#define InAlm_StateWord   					(1<<5)
#define AGVMode_StateWord   				(1<<6)
#define Stuffing_StateWord   				(1<<7)

/***** Period define *****/
#define T_MS_PLC_PERIOD        5
#define RX_TIMEOUT						(500/T_MS_PLC_PERIOD)

#define TX_PERIOD							(50/T_MS_PLC_PERIOD)
#define TX_PERIOD_ID1X8T			(10/T_MS_PLC_PERIOD)
#define TX_WINDOW_ID1X9T			(100/T_MS_PLC_PERIOD)
#define TX_WINDOW_ID1XAT			(100/T_MS_PLC_PERIOD)
#define TX_WINDOW_ID1XBT			(25/T_MS_PLC_PERIOD)

/***** Struct define *****/
typedef struct _tQEXPANDAGV_PDO
{
	//Rx buf for every ID ,MCUL X=7; MCUR X=8;
	INT8U CanBuf_ID1X0R[8];
	INT8U CanBuf_ID1X1R[8];
	INT8U CanBuf_ID1X2R[8];
	INT8U CanBuf_ID1X0R_Delay;
	INT8U CanBuf_ID1X1R_Delay;
	INT8U CanBuf_ID1X2R_Delay;

	//Tx buf for every ID ,MCUL X=7; MCUR X=8;
	INT8U CanBuf_ID1X8T[8];
	INT8U CanBuf_ID1X9T[8];
	INT8U CanBuf_ID1XAT[8];
	INT8U CanBuf_ID1XBT[8];
	INT32S TxCnt;						//Tx time period counter
	
	//DATA from VCU to MCU
	INT16U  VCUControlWord;
	INT16S	VCUCmdSpeed;	 //0.01 Hz
	INT16S	VCUCmdAngle;	 //0.1 centigrade
	INT16S	MoveMaxSpdLimitBySteer;

	//DATA from MCU to VCU
	INT16U StateWord; 
	INT16S SpeedMeasured;		//0.01 Hz
	INT16S AngleMeasured;		//0.1 centigrade
	INT16S CurrentMeasured;
	INT16U StateWord2;
	INT16U ErrorCode;  
	
	INT8U BoardTemperature;	   //tmp + 40
	INT8U MotorTemperature; 	//tmp + 40 	
	INT16U SoftwareVersion; 
	
	INT16U AgvHeartBeatEnable;     
	INT16U AgvHeartBeatError;  
	INT16U AgvMode;  
	
}tQEXPANDAGV_PDO;

extern tQEXPANDAGV_PDO	QExpandAGV_PDO;

 INT32S CanOpenInit (void);
 INT32S CanOpenRxFrame (tCANFrame  *pCANFrame);
 INT32S CanOpenTxFrame (void);
 INT32S CanOpenRxFrameMonitor(void);
 INT32S CanOpenUpdatePlcDataFromRxbuf(void);
 INT32S CanOpenUpdateTxbufFromPlcData(void);
	
#endif //#define __CANOPEN_QEXPANDAGVV00_H

