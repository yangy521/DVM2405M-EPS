/*******************************************************************************
* Filename: iCANPlc.c	                                             	 		   *
* Description:											   			 		   *
* Author:                                                           		   *
* Date:     														 		   *
* Revision:															 		   *
*******************************************************************************/

#include "iCANPlc.h"
#include "iCAN.h"
#include "PARA.h"
#include "CommonRam.h"
#include  "iCANLogic.h"

//*********Ican logic data for Master & Move
#if IS_LOGIC_MASTER(LOGIC_TYPE)
void ICANLogicIn_Master_From_Move(tICANSlave *pICANSlave)
{
}
#endif //#if IS_LOGIC_MASTER(LOGIC_TYPE)

#if IS_LOGIC_SLAVE(LOGIC_TYPE)
void ICANLogicOut_Slave_Move_To_Master(tICANSlave *pICANSlave)
{
}
#endif //#if IS_LOGIC_SLAVE(LOGIC_TYPE)

#if IS_LOGIC_MASTER(LOGIC_TYPE)
void ICANLogicOut_Master_To_Move(tICANSlave *pICANSlave)
{
}
#endif //#if IS_LOGIC_MASTER(LOGIC_TYPE)

#if IS_LOGIC_SLAVE(LOGIC_TYPE)
void ICANLogicIn_Slave_Move_From_Master(tICANSlave *pICANSlave)
{
}
#endif //#if IS_LOGIC_SLAVE(LOGIC_TYPE)

//*********Ican logic data for Master & Lift
#if IS_LOGIC_MASTER(LOGIC_TYPE)
void ICANLogicIn_Master_From_Lift(tICANSlave *pICANSlave)
{
	gPLCCtl.icanLift.ucStateSettingS = pICANSlave->ucSource0x00;
	gPLCCtl.icanLift.ucErrorCode = pICANSlave->ucSource0x01;
	gPLCCtl.icanLift.ucPrdStateS = pICANSlave->ucSource0x0D;
}
#endif //#if IS_LOGIC_MASTER(LOGIC_TYPE)

#if IS_LOGIC_SLAVE(LOGIC_TYPE)
void ICANLogicOut_Slave_Lift_To_Master(tICANSlave *pICANSlave)
{
//	pICANSlave->ucSource0x00 = gPLCCtl.icanLift.ucStateSettingS;
	pICANSlave->ucSource0x01=gPLCCtl.icanLift.ucErrorCode;
	pICANSlave->ucSource0x0D=gPLCCtl.icanLift.ucPrdStateS;
}
#endif //#if IS_LOGIC_SLAVE(LOGIC_TYPE)

#if IS_LOGIC_MASTER(LOGIC_TYPE)
void ICANLogicOut_Master_To_Lift(tICANSlave *pICANSlave)
{
//	pICANSlave->ucSource0x20 = gPLCCtl.icanLift.ucStateSettingM;			
	#if (USER_TYPE == USER_NBRY_QYCC15T_MOVE)
	pICANSlave->ucSource0x21 = gPLCCtl.icanLift.ucPitchCmd;
	pICANSlave->ucSource0x22 = gPLCCtl.icanLift.ucSidleCmd;
	#endif
	#if ((USER_TYPE == USER_AHHL_PHZC20T_MOVE) \
	|| (USER_TYPE == USER_AHHL_PHZC25T_MOVE))
	pICANSlave->ucSource0x21 = gPLCCtl.icanLift.ucIoFromMove;
	#endif

	pICANSlave->ucSource0x29 = gPLCCtl.icanLift.ucBatteryAct;
	pICANSlave->ucSource0x2D = gPLCCtl.icanLift.ucPrdStateM;
}
#endif //#if IS_LOGIC_MASTER(LOGIC_TYPE)

#if IS_LOGIC_SLAVE(LOGIC_TYPE)
void ICANLogicIn_Slave_Lift_From_Master(tICANSlave *pICANSlave)
{
	gPLCCtl.icanLift.ucStateSettingM = pICANSlave->ucSource0x20;
#if (USER_TYPE == USER_NBRY_QYCC15T_LIFT)
	gPLCCtl.icanLift.ucPitchCmd = pICANSlave->ucSource0x21;
	gPLCCtl.icanLift.ucSidleCmd = pICANSlave->ucSource0x22;
#endif
#if ((USER_TYPE == USER_AHHL_PHZC20T_LIFT) \
	|| (USER_TYPE == USER_AHHL_PHZC25T_LIFT))
		gPLCCtl.icanLift.ucIoFromMove =  pICANSlave->ucSource0x21;
#endif
	if (pICANSlave->ucSource0x29 != 0)
	{
		gPLCCtl.icanLift.ucBatteryAct = pICANSlave->ucSource0x29;
	}
	else if (gPLCCtl.icanLift.ucBatteryAct == 0)
	{
		gPLCCtl.icanLift.ucBatteryAct = 50;
	}
	gPLCCtl.icanLift.ucPrdStateM = pICANSlave->ucSource0x2D;
}
#endif //#if IS_LOGIC_SLAVE(LOGIC_TYPE)

//*********Ican logic data for Master & Steer
#if IS_LOGIC_MASTER(LOGIC_TYPE)
void ICANLogicIn_Master_From_Steer(tICANSlave *pICANSlave)
{
	gPLCCtl.icanSteer.ucStateSettingS = pICANSlave->ucSource0x00;
	gPLCCtl.icanSteer.ucErrorCode=pICANSlave->ucSource0x01;
	gPLCCtl.icanSteer.ucSteerAngleH=pICANSlave->ucSource0x02;
	gPLCCtl.icanSteer.ucSteerAngleL=pICANSlave->ucSource0x03;			
#if (USER_TYPE == USER_NBRY_QYCC15T_MOVE)
	gPLCCtl.icanSteer.ucPitchCmd = pICANSlave->ucSource0x04;
	gPLCCtl.icanSteer.ucSidleCmd = pICANSlave->ucSource0x05;
#endif
	gPLCCtl.icanSteer.ucPrdStateS=pICANSlave->ucSource0x0D;
}
#endif //#if IS_LOGIC_MASTER(LOGIC_TYPE)

#if IS_LOGIC_SLAVE(LOGIC_TYPE)
void ICANLogicOut_Slave_Steer_To_Master(tICANSlave *pICANSlave)
{
//	pICANSlave->ucSource0x00=gPLCCtl.icanSteer.ucStateSettingS;
//	temp=gPLCCtl.icanSteer.ucErrorCode;
	pICANSlave->ucSource0x01=gPara.ErrCode;//gPLCCtl.icanSteer.ucErrorCode;
	pICANSlave->ucSource0x02=gPLCCtl.icanSteer.ucSteerAngleH;
	pICANSlave->ucSource0x03=gPLCCtl.icanSteer.ucSteerAngleL;
	pICANSlave->ucSource0x0D=gPLCCtl.icanSteer.ucPrdStateS;
	pICANSlave->ucSource0x06=gPLCCtl.icanSteer.ucSteerSpeedH;
	pICANSlave->ucSource0x07=gPLCCtl.icanSteer.ucSteerSpeedL;
}
#endif //#if IS_LOGIC_SLAVE(LOGIC_TYPE)

#if IS_LOGIC_MASTER(LOGIC_TYPE)
void ICANLogicOut_Master_To_Steer(tICANSlave *pICANSlave)
{
//	pICANSlave->ucSource0x20 = gPLCCtl.icanSteer.ucStateSettingM;			
	pICANSlave->ucSource0x29 = gPLCCtl.icanSteer.ucBatteryAct;
	pICANSlave->ucSource0x2D = gPLCCtl.icanSteer.ucPrdStateM;
}
#endif //#if IS_LOGIC_MASTER(LOGIC_TYPE)

#if IS_LOGIC_SLAVE(LOGIC_TYPE)
void ICANLogicIn_Slave_Steer_From_Master(tICANSlave *pICANSlave)
{
	gPLCCtl.icanSteer.ucStateSettingM = pICANSlave->ucSource0x20;
	if (pICANSlave->ucSource0x29 != 0)
	{
		gPLCCtl.icanSteer.ucBatteryAct = pICANSlave->ucSource0x29;
	}
	else if (gPLCCtl.icanSteer.ucBatteryAct == 0)
	{
		gPLCCtl.icanSteer.ucBatteryAct = 50;
	}
	gPLCCtl.icanSteer.ucPrdStateM = pICANSlave->ucSource0x2D;
}
#endif //#if IS_LOGIC_SLAVE(LOGIC_TYPE)

//*********Ican logic data for Master & Smove
#if IS_LOGIC_MASTER(LOGIC_TYPE)
void ICANLogicIn_Master_From_Smove(tICANSlave *pICANSlave)
{
	gPLCCtl.icanSmove.ucStateSettingS = pICANSlave->ucSource0x00;
	gPLCCtl.icanSmove.ucErrorCode = pICANSlave->ucSource0x01;
	gPLCCtl.icanSmove.ucPrdStateS = pICANSlave->ucSource0x0D;
}
#endif //#if IS_LOGIC_MASTER(LOGIC_TYPE)

#if IS_LOGIC_SLAVE(LOGIC_TYPE)
void ICANLogicOut_Slave_Smove_To_Master(tICANSlave *pICANSlave)
{
//	pICANSlave->ucSource0x00 = gPLCCtl.icanSmove.ucStateSettingS;
	pICANSlave->ucSource0x01=gPLCCtl.icanSmove.ucErrorCode;
	pICANSlave->ucSource0x0D=gPLCCtl.icanSmove.ucPrdStateS;
}
#endif //#if IS_LOGIC_SLAVE(LOGIC_TYPE)

#if IS_LOGIC_MASTER(LOGIC_TYPE)
void ICANLogicOut_Master_To_Smove(tICANSlave *pICANSlave)
{
//	pICANSlave->ucSource0x20 = gPLCCtl.icanSmove.ucStateSettingM;			
	pICANSlave->ucSource0x29 = gPLCCtl.icanSmove.ucBatteryAct;
	pICANSlave->ucSource0x2D = gPLCCtl.icanSmove.ucPrdStateM;
}
#endif //#if IS_LOGIC_MASTER(LOGIC_TYPE)

#if IS_LOGIC_SLAVE(LOGIC_TYPE)
void ICANLogicIn_Slave_Smove_From_Master(tICANSlave *pICANSlave)
{
	gPLCCtl.icanSmove.ucStateSettingM = pICANSlave->ucSource0x20;
	if (pICANSlave->ucSource0x29 != 0)
	{
		gPLCCtl.icanSmove.ucBatteryAct = pICANSlave->ucSource0x29;
	}
	else if (gPLCCtl.icanSmove.ucBatteryAct == 0)
	{
		gPLCCtl.icanSmove.ucBatteryAct = 50;
	}
	gPLCCtl.icanSmove.ucPrdStateM = pICANSlave->ucSource0x2D;
}
#endif //#if IS_LOGIC_SLAVE(LOGIC_TYPE)

//*********Ican logic data for Master & Logic
#if IS_LOGIC_MASTER(LOGIC_TYPE)
void ICANLogicIn_Master_From_Logic(tICANSlave *pICANSlave)
{
	gPLCCtl.icanLogic.ucStateSettingS = pICANSlave->ucSource0x00;
	gPLCCtl.icanLogic.ucErrorCode = pICANSlave->ucSource0x01;
	gPLCCtl.icanLogic.ucPrdStateS = pICANSlave->ucSource0x0D;
}
#endif //#if IS_LOGIC_MASTER(LOGIC_TYPE)

#if IS_LOGIC_SLAVE(LOGIC_TYPE)
void ICANLogicOut_Slave_Logic_To_Master(tICANSlave *pICANSlave)
{
//	pICANSlave->ucSource0x00 = gPLCCtl.icanLogic.ucStateSettingS;
	pICANSlave->ucSource0x01=gPLCCtl.icanLogic.ucErrorCode;
	pICANSlave->ucSource0x0D=gPLCCtl.icanLogic.ucPrdStateS;
}
#endif //#if IS_LOGIC_SLAVE(LOGIC_TYPE)

#if IS_LOGIC_MASTER(LOGIC_TYPE)
void ICANLogicOut_Master_To_Logic(tICANSlave *pICANSlave)
{
//	pICANSlave->ucSource0x20 = gPLCCtl.icanLogic.ucStateSettingM;			
	pICANSlave->ucSource0x29 = gPLCCtl.icanLogic.ucBatteryAct;
	pICANSlave->ucSource0x2D = gPLCCtl.icanLogic.ucPrdStateM;
}
#endif //#if IS_LOGIC_MASTER(LOGIC_TYPE)

#if IS_LOGIC_SLAVE(LOGIC_TYPE)
void ICANLogicIn_Slave_Logic_From_Master(tICANSlave *pICANSlave)
{
	gPLCCtl.icanLogic.ucStateSettingM = pICANSlave->ucSource0x20;
	if (pICANSlave->ucSource0x29 != 0)
	{
		gPLCCtl.icanLogic.ucBatteryAct = pICANSlave->ucSource0x29;
	}
	else if (gPLCCtl.icanLogic.ucBatteryAct == 0)
	{
		gPLCCtl.icanLogic.ucBatteryAct = 50;
	}
	gPLCCtl.icanLogic.ucPrdStateM = pICANSlave->ucSource0x2D;
}
#endif //#if IS_LOGIC_SLAVE(LOGIC_TYPE)

//*********Ican logic data for Master & HMI
#if IS_LOGIC_MASTER(LOGIC_TYPE)
void ICANLogicIn_Master_From_Hmi(tICANSlave *pICANSlave)
{
	gPLCCtl.icanHMI.ucStateSettingS = pICANSlave->ucSource0x00;
	gPLCCtl.icanHMI.ucErrorCode = pICANSlave->ucSource0x01;
	if (pICANSlave->ucSource0x02 != 0)
	{
		gPLCCtl.icanHMI.ucBattery = pICANSlave->ucSource0x02;
	}
	else if (gPLCCtl.icanHMI.ucBattery == 0)
	{
		gPLCCtl.icanHMI.ucBattery = 50;
	}

	gPLCCtl.icanHMI.ucPrdStateS = pICANSlave->ucSource0x0D;
}
#endif //#if IS_LOGIC_MASTER(LOGIC_TYPE)

#if IS_LOGIC_SLAVE(LOGIC_TYPE)
void ICANLogicOut_Slave_Hmi_To_Master(tICANSlave *pICANSlave)
{
//	pICANSlave->ucSource0x00 = gPLCCtl.icanHMI.ucStateSettingS;
	pICANSlave->ucSource0x01=gPLCCtl.icanHMI.ucErrorCode;
	pICANSlave->ucSource0x02=gPLCCtl.icanHMI.ucBattery;
	pICANSlave->ucSource0x0D=gPLCCtl.icanHMI.ucPrdStateS;
}
#endif //#if IS_LOGIC_SLAVE(LOGIC_TYPE)

#if IS_LOGIC_MASTER(LOGIC_TYPE)
void ICANLogicOut_Master_To_Hmi(tICANSlave *pICANSlave)
{
//	pICANSlave->ucSource0x20 =	gPLCCtl.icanHMI.ucStateSettingM;
	pICANSlave->ucSource0x21 = gPLCCtl.icanHMI.ucNetCfg;
	pICANSlave->ucSource0x22=	gPLCCtl.icanHMI.ucErrMove;
	pICANSlave->ucSource0x23=	gPLCCtl.icanHMI.ucErrLift;
	pICANSlave->ucSource0x24=	gPLCCtl.icanHMI.ucErrSteer;
	pICANSlave->ucSource0x25=	gPLCCtl.icanHMI.ucMoveSpeedH;
	pICANSlave->ucSource0x26=	gPLCCtl.icanHMI.ucMoveSpeedL;
	pICANSlave->ucSource0x27=	gPLCCtl.icanHMI.ucSteerAngleH;
	pICANSlave->ucSource0x28=	gPLCCtl.icanHMI.ucSteerAngleL;
	pICANSlave->ucSource0x29=	gPLCCtl.icanHMI.ucBatteryAct;
	pICANSlave->ucSource0x2A=	gPLCCtl.icanHMI.ucVehicleState;
	pICANSlave->ucSource0x2D = gPLCCtl.icanHMI.ucPrdStateM;
}
#endif //#if IS_LOGIC_MASTER(LOGIC_TYPE)

#if IS_LOGIC_SLAVE(LOGIC_TYPE)
void ICANLogicIn_Slave_Hmi_From_Master(tICANSlave *pICANSlave)
{
	gPLCCtl.icanHMI.ucStateSettingM = pICANSlave->ucSource0x20;
	gPLCCtl.icanHMI.ucNetCfg = pICANSlave->ucSource0x21;
	gPLCCtl.icanHMI.ucErrMove =	pICANSlave->ucSource0x22;
	gPLCCtl.icanHMI.ucErrLift =	pICANSlave->ucSource0x23;
	gPLCCtl.icanHMI.ucErrSteer =	pICANSlave->ucSource0x24;
	gPLCCtl.icanHMI.ucMoveSpeedH =	pICANSlave->ucSource0x25;
	gPLCCtl.icanHMI.ucMoveSpeedL =	pICANSlave->ucSource0x26;
	gPLCCtl.icanHMI.ucSteerAngleH =	pICANSlave->ucSource0x27;
	gPLCCtl.icanHMI.ucSteerAngleL =	pICANSlave->ucSource0x28;

	if (pICANSlave->ucSource0x29 != 0)
	{
		gPLCCtl.icanHMI.ucBatteryAct = pICANSlave->ucSource0x29;
	}
	else if (gPLCCtl.icanHMI.ucBatteryAct == 0)
	{
		gPLCCtl.icanHMI.ucBatteryAct = 50;
	}
	gPLCCtl.icanHMI.ucVehicleState =	pICANSlave->ucSource0x2A;
	gPLCCtl.icanHMI.ucPrdStateM = pICANSlave->ucSource0x2D;
}
#endif //#if IS_LOGIC_SLAVE(LOGIC_TYPE)

//*********Ican logic data for Master & Pc
#if IS_LOGIC_MASTER(LOGIC_TYPE)
void ICANLogicIn_Master_From_Pc(tICANSlave *pICANSlave)
{
	gPLCCtl.icanPc.ucStateSettingS = pICANSlave->ucSource0x00;
	gPLCCtl.icanPc.ucPrdStateS = pICANSlave->ucSource0x0D;
}
#endif //#if IS_LOGIC_MASTER(LOGIC_TYPE)

#if IS_LOGIC_SLAVE(LOGIC_TYPE)
void ICANLogicOut_Slave_Pc_To_Master(tICANSlave *pICANSlave)
{
//	pICANSlave->ucSource0x00 = gPLCCtl.icanPc.ucStateSettingS;
	pICANSlave->ucSource0x01=gPLCCtl.icanPc.ucErrorCode;
	pICANSlave->ucSource0x0D=gPLCCtl.icanPc.ucPrdStateS;
}
#endif //#if IS_LOGIC_SLAVE(LOGIC_TYPE)

#if IS_LOGIC_MASTER(LOGIC_TYPE)
void ICANLogicOut_Master_To_Pc(tICANSlave *pICANSlave)
{
//	pICANSlave->ucSource0x20 = gPLCCtl.icanPc.ucStateSettingM;
	pICANSlave->ucSource0x21 = gPLCCtl.icanPc.ucNetCfg;
}
#endif //#if IS_LOGIC_MASTER(LOGIC_TYPE)

#if IS_LOGIC_SLAVE(LOGIC_TYPE)
void ICANLogicIn_Slave_Pc_From_Master(tICANSlave *pICANSlave)
{
}
#endif //#if IS_LOGIC_SLAVE(LOGIC_TYPE)


#if IS_LOGIC_MASTER(LOGIC_TYPE)
typedef void (*ICANLOGICIN_MASTER_FUNC)(tICANSlave *);
ICANLOGICIN_MASTER_FUNC ICANLogicIn_Master_Func[] =
{
	ICANLogicIn_Master_From_Move,				//Prd_Move
	ICANLogicIn_Master_From_Lift,				//Prd_Lift
	ICANLogicIn_Master_From_Steer,			//Prd_Steer
	ICANLogicIn_Master_From_Smove,			//Prd_Move_Second
	ICANLogicIn_Master_From_Logic,			//Prd_Logic
	ICANLogicIn_Master_From_Hmi,			  //Prd_HMI
	ICANLogicIn_Master_From_Pc			    //Prd_PC
};

void ICANLogicIn_Master(void)
{
	INT8U i;
	tICANSlave *pICANSlave;
	
	for(i=1;i<icanMaster.ucSlvArrLength;i++)
	{
		pICANSlave = &icanMaster.pICANSlvArray[i];
		if (pICANSlave->ucMacID < (sizeof(ICANLogicIn_Master_Func)/sizeof(ICANLogicIn_Master_Func[0])))
			ICANLogicIn_Master_Func[pICANSlave->ucMacID](pICANSlave);
	}	

}
#endif //#if IS_LOGIC_MASTER(LOGIC_TYPE)

#if IS_LOGIC_MASTER(LOGIC_TYPE)
typedef void (*ICANLOGICOUT_MASTER_FUNC)(tICANSlave *);
ICANLOGICOUT_MASTER_FUNC ICANLogicOut_Master_Func[] =
{
	ICANLogicOut_Master_To_Move,			//Prd_Move
	ICANLogicOut_Master_To_Lift,			//Prd_Lift
	ICANLogicOut_Master_To_Steer,			//Prd_Steer
	ICANLogicOut_Master_To_Smove,			//Prd_Move_Second
	ICANLogicOut_Master_To_Logic,			//Prd_Logic
	ICANLogicOut_Master_To_Hmi,			  //Prd_HMI
	ICANLogicOut_Master_To_Pc			    //Prd_PC
};
void ICANLogicOut_Master(void)
{
	INT8U i;
	tICANSlave *pICANSlave;

	for(i=1;i<icanMaster.ucSlvArrLength;i++)
	{
		pICANSlave = &icanMaster.pICANSlvArray[i];
		if (pICANSlave->ucMacID < (sizeof(ICANLogicOut_Master_Func)/sizeof(ICANLogicOut_Master_Func[0])))
			ICANLogicOut_Master_Func[pICANSlave->ucMacID](pICANSlave);
	}	
}
#endif //#if IS_LOGIC_MASTER(LOGIC_TYPE)

#if IS_LOGIC_SLAVE(LOGIC_TYPE)
typedef void (*ICANLOGICIN_SLAVE_FUNC)(tICANSlave *);
ICANLOGICIN_SLAVE_FUNC ICANLogicIn_Slave_Func[] =
{
	ICANLogicIn_Slave_Move_From_Master,			  //Prd_Move
	ICANLogicIn_Slave_Lift_From_Master,			  //Prd_Lift
	ICANLogicIn_Slave_Steer_From_Master,			//Prd_Steer
	ICANLogicIn_Slave_Smove_From_Master,			//Prd_Move_Second
	ICANLogicIn_Slave_Logic_From_Master,			//Prd_Logic
	ICANLogicIn_Slave_Hmi_From_Master,			  //Prd_HMI
	ICANLogicIn_Slave_Pc_From_Master			    //Prd_PC
};
void ICANLogicIn_Slave(void)
{
	tICANSlave *pICANSlave = &icanSlave;

	if (pICANSlave->bIsConnect == false)
		return;
	if (pICANSlave->ucMacID < (sizeof(ICANLogicIn_Slave_Func)/sizeof(ICANLogicIn_Slave_Func[0])))
		ICANLogicIn_Slave_Func[pICANSlave->ucMacID](pICANSlave);
}
#endif //#if IS_LOGIC_SLAVE(LOGIC_TYPE)


#if IS_LOGIC_SLAVE(LOGIC_TYPE)
typedef void (*ICANLOGICOUT_SLAVE_FUNC)(tICANSlave *);
ICANLOGICOUT_SLAVE_FUNC ICANLogicOut_Slave_Func[] =
{
	ICANLogicOut_Slave_Move_To_Master,			//Prd_Move
	ICANLogicOut_Slave_Lift_To_Master,			//Prd_Lift
	ICANLogicOut_Slave_Steer_To_Master,			//Prd_Steer
	ICANLogicOut_Slave_Smove_To_Master,			//Prd_Move_Second
	ICANLogicOut_Slave_Logic_To_Master,			//Prd_Logic
	ICANLogicOut_Slave_Hmi_To_Master,			  //Prd_HMI
	ICANLogicOut_Slave_Pc_To_Master			    //Prd_PC
};
void ICANLogicOut_Slave(void)
{
	tICANSlave *pICANSlave = &icanSlave;

	if (pICANSlave->ucMacID < (sizeof(ICANLogicOut_Slave_Func)/sizeof(ICANLogicOut_Slave_Func[0])))
		ICANLogicOut_Slave_Func[pICANSlave->ucMacID](pICANSlave);
}
#endif //#if IS_LOGIC_SLAVE(LOGIC_TYPE)

//********iCAN Init
void ICANInitialize(void)
{
	#if IS_LOGIC_MASTER(LOGIC_TYPE)
		ICANInitialize_Master();
	#else
		ICANInitialize_Slave();	
	#endif //#if IS_LOGIC_MASTER(LOGIC_TYPE)
}
