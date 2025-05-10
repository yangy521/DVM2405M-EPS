#include "Device.h"
#include "CommonRam.h"
#include	"canSTM32F4.h"

//转向控制器定时发送PDO报文
#if (USER_TYPE == USER_STEER_ZDLD)	
void PDOTx_Prco_ZDLD(void)
{
	static INT8U Count=0;
	tCANFrame canFrame;	//
	INT8U i;
	INT32S lTemp;
	INT16S nTemp;
	
	if(!(Count++&0x01))  //2*10=20ms
	{
	  /* 第一帧 PDO1Tx */
		canFrame.ulID=0x198;  //0x180+0x18
		canFrame.ucXID=0;			//0 标准帧；1 扩展帧  
		canFrame.ucDataLength=8;		//数据场长度

		if(SL_CHK(PLC_MIDDLE_RDY))  //home flag
					gPLCCtl.PDO_Steer.DataStruct.ucSteerState |= 0x10;
		else  gPLCCtl.PDO_Steer.DataStruct.ucSteerState &= ~0x10;
		
		if(gPLCCtl.ErrCode!=0)  //In alram 
					gPLCCtl.PDO_Steer.DataStruct.ucSteerState |= 0x20;
		else  gPLCCtl.PDO_Steer.DataStruct.ucSteerState &= ~0x20;
		
		if(gPLCCtl.AutoManuelMode)  //AGV mode 
					gPLCCtl.PDO_Steer.DataStruct.ucSteerState |= 0x40;
		else  gPLCCtl.PDO_Steer.DataStruct.ucSteerState &= ~0x40;
		
		gPLCCtl.PDO_Steer.DataStruct.ucSteerState ^= 0x80;  //Toggle bit7
	
//		for(i=0;i<8;i++)
//			canFrame.ucData[i]=gPLCCtl.PDO_Steer.ucData[i];
		lTemp = gCRam.SpeedAvgAdd*6250/gPLCCtl.enc;  //0.01Hz
		nTemp = gPLCCtl.icanSteer.ucSteerAngleH; 
		nTemp = (nTemp<<8)+gPLCCtl.icanSteer.ucSteerAngleL; 
		
		canFrame.ucData[0] = gPLCCtl.PDO_Steer.DataStruct.ucSteerState;
		canFrame.ucData[1] = lTemp&0xff;	
		canFrame.ucData[2] = (lTemp>>8)&0xff;	
		canFrame.ucData[3] = 0;	
		canFrame.ucData[4] = 0; 
		canFrame.ucData[5] = nTemp&0xff;
		canFrame.ucData[6] = (nTemp>>8)&0xff;	
//		canFrame.ucData[5] = gPLCCtl.icanSteer.ucSteerAngleL;
//		canFrame.ucData[6] = gPLCCtl.icanSteer.ucSteerAngleH;
		canFrame.ucData[7] = 0;		
		
		CANWriteBuffer(&canFrmTxBuffer, &canFrame);
		
	  /* 第二帧 PDO4Tx */		
		canFrame.ulID=0x49A;  //0x480+0x1A
		canFrame.ucXID=0;			//0 标准帧；1 扩展帧  
		canFrame.ucDataLength=8;		//数据场长度
		for(i=0;i<8;i++)
			canFrame.ucData[i]=0;
    /*0.0	-
			1.0	Temperature
			2.0	Motor temperature 
			3.0	Error Code
			4.0	-
			5.0	-
			6.0	 SW release L
			7.0	 SW release H  */
		canFrame.ucData[1]=gPLCCtl.TmpPower;	//温度	
		canFrame.ucData[2]=0x3C;  //温度 20=60-40
		canFrame.ucData[3]=gPLCCtl.ErrCode;
		canFrame.ucData[6]=gPara.SoftVersion&0xFF;
		canFrame.ucData[7]=(gPara.SoftVersion>>8)&0xFF;		
		CANWriteBuffer(&canFrmTxBuffer, &canFrame);
		/* 发送数据   */ 
//		CANFrmSend(&canFrmTxBuffer);		
	}
}


#endif
