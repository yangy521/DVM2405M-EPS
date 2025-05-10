/*******************************************************************************
* Filename: USER_QEXPANDAGV.c	                                             	 		   *
* Description: ?????								   			 		   *
* Author:                                                           		       *
* Date:     														 		   													       *
* Revision:															 		   
*******************************************************************************/
#include "Device.h"
#include "CommonRam.h"
//#include	"canSTM32F4.h"
#include	"USER_QEXPANDAGV.h"
#include  "CanOpen_QexpandAgvV04.h"
#if (USER_TYPE == USER_QEXPANDAGV)

/*******************************************************************************
* Filename: USER_QEXPANDAGV (QEXPAND CANOPEN V104)                                            	 		   	       *
* Description: *
* Author:                                                           		       *
* Date:     														 		   													       *
* Revision:		
* IO Define:
*******************************************************************************/
//Constant define
#define THROTTLE_LOCK					(0x0001 << 0)
#define SA_LOCK								(0x0001 << 1)
#define ESPREVPWON_LOCK				(0x0001 << 2)
#define ESPREVACT_LOCK				(0x0001 << 3)
#define LIFT_LOCK							(0x0001 << 4)

//Bit of LogicDi define  
#define ENABLE_LogicDi  				(1 << 0)
#define N_ESTOP_LogicDi  				(1 << 1)
#define BREAK1_LogicDi  				(1 << 2)
#define FWD_LogicDi  					(1 << 3)
#define RVS_LogicDi  					(1 << 4)
#define LIFT_LogicDi  					(1 << 5)
#define DOWN_LogicDi  					(1 << 6)
#define EMRVS_LogicDi  					(1 << 7)

void ClrAutoModeBuf(void)
{

	QExpandAGV_PDO.VCUControlWord = QExpandAGV_PDO.CanBuf_ID1X0R[0];
	QExpandAGV_PDO.VCUCmdSpeed = (QExpandAGV_PDO.CanBuf_ID1X0R[2] << 8) | QExpandAGV_PDO.CanBuf_ID1X0R[1];
}

void QEXPAND_AGV_STEER(void)
{

		CanOpenUpdatePlcDataFromRxbuf();
		CanOpenRxFrameMonitor();
		
		gPLCCtl.AutoManuelMode = QExpandAGV_PDO.AgvMode;

		if(gPLCCtl.AutoManuelMode==1)
		{
			if(QExpandAGV_PDO.AgvHeartBeatError==1) 
				MCL_SetFault(HEARTBEAT_ERR);
			else
				MCL_ClearFault(HEARTBEAT_ERR);
		}

		//StateWord Bit0.4
		if(SL_CHK(PLC_MIDDLE_RDY))  //home flag
					QExpandAGV_PDO.StateWord |= SWITCH5_StateWord;
		else  QExpandAGV_PDO.StateWord &= ~SWITCH5_StateWord;
		//StateWord Bit0.5	
		if(gPLCCtl.ErrCode!=0)  //In alram 
		{
			QExpandAGV_PDO.IsInAlarm = 1;
		}
		else  
		{
			QExpandAGV_PDO.IsInAlarm = 0;
		}
		//StateWord Bit0.6	
		if(gPLCCtl.AutoManuelMode)  //AGV mode 
					QExpandAGV_PDO.StateWord |= AGVMode_StateWord;
		else  QExpandAGV_PDO.StateWord &= ~AGVMode_StateWord;
		//StateWord Bit0.7 Toggle 	
		if ((QExpandAGV_PDO.TxCnt & 1) == 0)	
			QExpandAGV_PDO.StateWord ^= Stuffing_StateWord;

		if(gCRam.bPwmClose==0)
					QExpandAGV_PDO.StateWord |= READY_StateWord;
		else  QExpandAGV_PDO.StateWord &= ~READY_StateWord;

//		if((gPara.AcMotorSpeed>3) || (gPara.AcMotorSpeed<-3))
//					QExpandAGV_PDO.StateWord |= 0x04;
//		else  QExpandAGV_PDO.StateWord &= ~0x04;
		
		QExpandAGV_PDO.SpeedMeasured =  gPara.AcMotorSpeed; //rpm gCRam.SpeedAvgAdd*6250/gPLCCtl.enc; //0.01Hz
		QExpandAGV_PDO.AngleMeasured =  (gPLCCtl.icanSteer.ucSteerAngleH<<8) + gPLCCtl.icanSteer.ucSteerAngleL;
		QExpandAGV_PDO.CurrentMeasured = gPara.AcPhaseCurrent;
		QExpandAGV_PDO.ErrorCode = gPLCCtl.ErrCode;
		QExpandAGV_PDO.BoardTemperature = gPLCCtl.TmpPower+40;
		QExpandAGV_PDO.MotorTemperature = 60;	
		QExpandAGV_PDO.SoftwareVersion = gPara.SoftVersion;		
		
		CanOpenUpdateTxbufFromPlcData();
		CanOpenTxFrame();
}


#endif //(USER_TYPE == USER_QEXPANDAGV)

