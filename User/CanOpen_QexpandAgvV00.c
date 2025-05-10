/*******************************************************************************
* Filename: CanOpen_QexpandAgvV00.c	                                             	 		   *
* Description:											   			 		   *
* Author:                                                           		   *
* Date:     														 		   *
* Revision:															 		   *
*******************************************************************************/
#include  "iCAN.h"
#include	"CommonRam.h"
#include "CanOpen_QexpandAgvV00.h"

#if (CANOPEN_TYPE == CANOPEN_QEXPAND_AGV_V00)

tQEXPANDAGV_PDO	QExpandAGV_PDO;
/*******************************************************************************
* Name: QExpandAGVInit
* Description: Initialise the default data following power on
* Input: pointer to the data structure
* Output: 
*					0- 
*					1- Success
* Author: 
* Date: 
* Revision:
*******************************************************************************/
INT32S CanOpenInit (void)
{
	INT32S index;
	tQEXPANDAGV_PDO  *pQExpandAGV_PDO;
	
	pQExpandAGV_PDO = &QExpandAGV_PDO;
	for (index = 0; index < sizeof(tQEXPANDAGV_PDO); index++)
	{
		((INT8U*)pQExpandAGV_PDO)[index] = 0;
	}
	return 1;
}

/*******************************************************************************
* Name: CanOpenRxFrame
* Description: Transmit buf data frame.  Called by plc per 5ms 
* Input: none
* Output: none
*
* Author: 
* Date: 
* Revision:
*******************************************************************************/
INT32S CanOpenRxFrame (tCANFrame  *pCANFrame)
{
	INT32S flag;
	
	flag = 1;
	if (pCANFrame->ucXID == 0)
	{
		if (pCANFrame->ulID == (QEXPANDAGVPDORX1_ID_OFS + QEXPANDAGVPDO_ID))
		{
			QExpandAGV_PDO.CanBuf_ID1X0R[0] = pCANFrame->ucData[0];
			QExpandAGV_PDO.CanBuf_ID1X0R[1] = pCANFrame->ucData[1];
			QExpandAGV_PDO.CanBuf_ID1X0R[2] = pCANFrame->ucData[2];
			QExpandAGV_PDO.CanBuf_ID1X0R[3] = pCANFrame->ucData[3];
			QExpandAGV_PDO.CanBuf_ID1X0R[4] = pCANFrame->ucData[4];
			QExpandAGV_PDO.CanBuf_ID1X0R[5] = pCANFrame->ucData[5];
			QExpandAGV_PDO.CanBuf_ID1X0R[6] = pCANFrame->ucData[6];
			QExpandAGV_PDO.CanBuf_ID1X0R[7] = pCANFrame->ucData[7];
			QExpandAGV_PDO.CanBuf_ID1X0R_Delay = 0;
			QExpandAGV_PDO.AgvHeartBeatEnable = 1;
		}
		else if (pCANFrame->ulID == (QEXPANDAGVPDORX2_ID_OFS + QEXPANDAGVPDO_ID))
		{
			QExpandAGV_PDO.CanBuf_ID1X1R[0] = pCANFrame->ucData[0];
			QExpandAGV_PDO.CanBuf_ID1X1R[1] = pCANFrame->ucData[1];
			QExpandAGV_PDO.CanBuf_ID1X1R[2] = pCANFrame->ucData[2];
			QExpandAGV_PDO.CanBuf_ID1X1R[3] = pCANFrame->ucData[3];
			QExpandAGV_PDO.CanBuf_ID1X1R[4] = pCANFrame->ucData[4];
			QExpandAGV_PDO.CanBuf_ID1X1R[5] = pCANFrame->ucData[5];
			QExpandAGV_PDO.CanBuf_ID1X1R[6] = pCANFrame->ucData[6];
			QExpandAGV_PDO.CanBuf_ID1X1R[7] = pCANFrame->ucData[7];
			QExpandAGV_PDO.CanBuf_ID1X1R_Delay = 0;
		}
		else if (pCANFrame->ulID == (QEXPANDAGVPDORX3_ID_OFS + QEXPANDAGVPDO_ID))
		{
			QExpandAGV_PDO.CanBuf_ID1X2R[0] = pCANFrame->ucData[0];
			QExpandAGV_PDO.CanBuf_ID1X2R[1] = pCANFrame->ucData[1];
			QExpandAGV_PDO.CanBuf_ID1X2R[2] = pCANFrame->ucData[2];
			QExpandAGV_PDO.CanBuf_ID1X2R[3] = pCANFrame->ucData[3];
			QExpandAGV_PDO.CanBuf_ID1X2R[4] = pCANFrame->ucData[4];
			QExpandAGV_PDO.CanBuf_ID1X2R[5] = pCANFrame->ucData[5];
			QExpandAGV_PDO.CanBuf_ID1X2R[6] = pCANFrame->ucData[6];
			QExpandAGV_PDO.CanBuf_ID1X2R[7] = pCANFrame->ucData[7];
			QExpandAGV_PDO.CanBuf_ID1X2R_Delay = 0;
		}
		else
			flag = 0;
	}
	else
	{
		flag = 0;
	}
	
	return flag;	
}

INT32S CanOpenRxFrameMonitor(void)
{
	if (QExpandAGV_PDO.CanBuf_ID1X0R_Delay >= RX_TIMEOUT)
	{
		QExpandAGV_PDO.CanBuf_ID1X0R[0] = 0;
		QExpandAGV_PDO.CanBuf_ID1X0R[1] = 0;
		QExpandAGV_PDO.CanBuf_ID1X0R[2] = 0;
		QExpandAGV_PDO.CanBuf_ID1X0R[3] = 0;
		QExpandAGV_PDO.CanBuf_ID1X0R[4] = 0;
		QExpandAGV_PDO.CanBuf_ID1X0R[5] = 0;
		QExpandAGV_PDO.CanBuf_ID1X0R[6] = 0;
		QExpandAGV_PDO.CanBuf_ID1X0R[7] = 0;
//		QExpandAGV_PDO.CanBuf_ID1X0R_Delay = 0;		
		QExpandAGV_PDO.AgvHeartBeatError = 1;
	}
	else
	{
		QExpandAGV_PDO.CanBuf_ID1X0R_Delay += 1;
		QExpandAGV_PDO.AgvHeartBeatError = 0;
	}
	
	return 1;
}

/*******************************************************************************
* Name: CanOpenTxFrame
* Description: Transmit buf data frame.  Called by plc per 5ms 
* Input: none
* Output: none
*
* Author: 
* Date: 
* Revision:
*******************************************************************************/
INT32S CanOpenTxFrame (void)
{
	tCANFrame canFrame;	//
	tQEXPANDAGV_PDO *pQExpandAGV_PDO;
	pQExpandAGV_PDO = &QExpandAGV_PDO;
	
	if(QExpandAGV_PDO.AgvHeartBeatEnable == 0)	//PDO Tx disable
		return 0;
	if ((pQExpandAGV_PDO->TxCnt & 1) == 0)//TX_PERIOD_ID1X8T
	{
			canFrame.ulID = (QEXPANDAGVPDOTX1_ID_OFS + QEXPANDAGVPDO_ID);
			canFrame.ucXID=0;			//0 ???;1 ??? 
			canFrame.ucDataLength=8;	

			canFrame.ucData[0] = pQExpandAGV_PDO->CanBuf_ID1X8T[0];
			canFrame.ucData[1] = pQExpandAGV_PDO->CanBuf_ID1X8T[1];
			canFrame.ucData[2] = pQExpandAGV_PDO->CanBuf_ID1X8T[2];
			canFrame.ucData[3] = pQExpandAGV_PDO->CanBuf_ID1X8T[3];
			canFrame.ucData[4] = pQExpandAGV_PDO->CanBuf_ID1X8T[4];
			canFrame.ucData[5] = pQExpandAGV_PDO->CanBuf_ID1X8T[5];
			canFrame.ucData[6] = pQExpandAGV_PDO->CanBuf_ID1X8T[6];
			canFrame.ucData[7] = pQExpandAGV_PDO->CanBuf_ID1X8T[7];
			CANWriteBuffer(&canFrmTxBuffer, &canFrame);
	}
	if (pQExpandAGV_PDO->TxCnt == TX_WINDOW_ID1X9T)
	{
			canFrame.ulID = (QEXPANDAGVPDOTX2_ID_OFS + QEXPANDAGVPDO_ID);
			canFrame.ucXID=0;			//0 ???;1 ??? 
			canFrame.ucDataLength=8;	

			canFrame.ucData[0] = pQExpandAGV_PDO->CanBuf_ID1X9T[0];
			canFrame.ucData[1] = pQExpandAGV_PDO->CanBuf_ID1X9T[1];
			canFrame.ucData[2] = pQExpandAGV_PDO->CanBuf_ID1X9T[2];
			canFrame.ucData[3] = pQExpandAGV_PDO->CanBuf_ID1X9T[3];
			canFrame.ucData[4] = pQExpandAGV_PDO->CanBuf_ID1X9T[4];
			canFrame.ucData[5] = pQExpandAGV_PDO->CanBuf_ID1X9T[5];
			canFrame.ucData[6] = pQExpandAGV_PDO->CanBuf_ID1X9T[6];
			canFrame.ucData[7] = pQExpandAGV_PDO->CanBuf_ID1X9T[7];
			CANWriteBuffer(&canFrmTxBuffer, &canFrame);
	}
	if (pQExpandAGV_PDO->TxCnt == TX_WINDOW_ID1XAT)
	{
			canFrame.ulID = (QEXPANDAGVPDOTX3_ID_OFS + QEXPANDAGVPDO_ID);
			canFrame.ucXID=0;			//0 ???;1 ??? 
			canFrame.ucDataLength=8;	

			canFrame.ucData[0] = pQExpandAGV_PDO->CanBuf_ID1XAT[0];
			canFrame.ucData[1] = pQExpandAGV_PDO->CanBuf_ID1XAT[1];
			canFrame.ucData[2] = pQExpandAGV_PDO->CanBuf_ID1XAT[2];
			canFrame.ucData[3] = pQExpandAGV_PDO->CanBuf_ID1XAT[3];
			canFrame.ucData[4] = pQExpandAGV_PDO->CanBuf_ID1XAT[4];
			canFrame.ucData[5] = pQExpandAGV_PDO->CanBuf_ID1XAT[5];
			canFrame.ucData[6] = pQExpandAGV_PDO->CanBuf_ID1XAT[6];
			canFrame.ucData[7] = pQExpandAGV_PDO->CanBuf_ID1XAT[7];
			CANWriteBuffer(&canFrmTxBuffer, &canFrame);
	}
	if (pQExpandAGV_PDO->TxCnt == TX_WINDOW_ID1XBT)
	{
			canFrame.ulID = (QEXPANDAGVPDOTX4_ID_OFS + QEXPANDAGVPDO_ID);
			canFrame.ucXID=0;			//0 ???;1 ??? 
			canFrame.ucDataLength=8;	

			canFrame.ucData[0] = pQExpandAGV_PDO->CanBuf_ID1XBT[0];
			canFrame.ucData[1] = pQExpandAGV_PDO->CanBuf_ID1XBT[1];
			canFrame.ucData[2] = pQExpandAGV_PDO->CanBuf_ID1XBT[2];
			canFrame.ucData[3] = pQExpandAGV_PDO->CanBuf_ID1XBT[3];
			canFrame.ucData[4] = pQExpandAGV_PDO->CanBuf_ID1XBT[4];
			canFrame.ucData[5] = pQExpandAGV_PDO->CanBuf_ID1XBT[5];
			canFrame.ucData[6] = pQExpandAGV_PDO->CanBuf_ID1XBT[6];
			canFrame.ucData[7] = pQExpandAGV_PDO->CanBuf_ID1XBT[7];
			CANWriteBuffer(&canFrmTxBuffer, &canFrame);
	}


	pQExpandAGV_PDO->TxCnt += 1;
	if (pQExpandAGV_PDO->TxCnt >= TX_PERIOD)
		pQExpandAGV_PDO->TxCnt = 0;
	
	return 1;
}


/*******************************************************************************
* Name: CanOpenUpdatePlcDataFromRxbuf
* Description: Update PLC data from RX bufID. 
* Input: none
* Output: none
*
* Author: 
* Date: 
* Revision:
*******************************************************************************/
INT32S CanOpenUpdatePlcDataFromRxbuf(void)
{
	tQEXPANDAGV_PDO *pQExpandAGV_PDO;
	pQExpandAGV_PDO = &QExpandAGV_PDO;

	pQExpandAGV_PDO->VCUControlWord = pQExpandAGV_PDO->CanBuf_ID1X0R[0];
	pQExpandAGV_PDO->VCUCmdSpeed = (pQExpandAGV_PDO->CanBuf_ID1X0R[6] << 8) | pQExpandAGV_PDO->CanBuf_ID1X0R[5];
	pQExpandAGV_PDO->VCUCmdAngle =(pQExpandAGV_PDO->CanBuf_ID1X0R[4] << 8) | pQExpandAGV_PDO->CanBuf_ID1X0R[3];

	return 1;
}
/*******************************************************************************
* Name: CanOpenUpdateTxbufFromPlcData
* Description: Update TX bufID from PLC data. 
* Input: none
* Output: none
*
* Author: 
* Date: 
* Revision:
*******************************************************************************/
INT32S CanOpenUpdateTxbufFromPlcData(void)
{
	tQEXPANDAGV_PDO *pQExpandAGV_PDO;
	pQExpandAGV_PDO = &QExpandAGV_PDO;

	//DATA from MCU to VCU
	pQExpandAGV_PDO->CanBuf_ID1X8T[0] = pQExpandAGV_PDO->StateWord & 0xFF;
	pQExpandAGV_PDO->CanBuf_ID1X8T[1] = (pQExpandAGV_PDO->SpeedMeasured) & 0xFF;
	pQExpandAGV_PDO->CanBuf_ID1X8T[2] = (pQExpandAGV_PDO->SpeedMeasured >> 8) & 0xFF;
	pQExpandAGV_PDO->CanBuf_ID1X8T[3] = (pQExpandAGV_PDO->AngleMeasured) & 0xFF;
	pQExpandAGV_PDO->CanBuf_ID1X8T[4] = (pQExpandAGV_PDO->AngleMeasured >> 8) & 0xFF;
	pQExpandAGV_PDO->CanBuf_ID1X8T[5] = (pQExpandAGV_PDO->CurrentMeasured) & 0xFF;
	pQExpandAGV_PDO->CanBuf_ID1X8T[6] = (pQExpandAGV_PDO->CurrentMeasured >> 8) & 0xFF;//pQExpandAGV_PDO->StateWord2 & 0xFF;
	pQExpandAGV_PDO->CanBuf_ID1X8T[7] = pQExpandAGV_PDO->ErrorCode & 0xFF;

	pQExpandAGV_PDO->CanBuf_ID1XBT[0] = 0;
	pQExpandAGV_PDO->CanBuf_ID1XBT[1] = pQExpandAGV_PDO->BoardTemperature;
	pQExpandAGV_PDO->CanBuf_ID1XBT[2] = pQExpandAGV_PDO->MotorTemperature;
	pQExpandAGV_PDO->CanBuf_ID1XBT[3] = 0;
	pQExpandAGV_PDO->CanBuf_ID1XBT[4] = 0;
	pQExpandAGV_PDO->CanBuf_ID1XBT[5] = 0;
	pQExpandAGV_PDO->CanBuf_ID1XBT[6] = (pQExpandAGV_PDO->SoftwareVersion) & 0xFF;
	pQExpandAGV_PDO->CanBuf_ID1XBT[7] = (pQExpandAGV_PDO->SoftwareVersion>>8) & 0xFF;

	return 1;
}
#endif //#if (CANOPEN_TYPE == CANOPEN_QEXPAND_AGV_V00)
