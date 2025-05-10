#include "Device.h"
#include "CommonRam.h"
#include  "CanOpen_QexpandAgvV04.h"

//中力转向SDO
const INT16U EP_STEER_SDOTAB[256]=
{
// 00,  01,  02,  03,  04,  05, 06,   07,  08,  09,
		0,	1,	2,	3,	4,	5,	6,	7,	8,	9,
		10,	11,	12,	13,	14,	15,	16,	17,	18,	19,
		20,	21,	22,	23,	24,	25,	26,	27,	28,	29,
		30,	31,	32,	33,	34,	35,	36,	37,	38,	39,
		40,	41,	42,	43,	44,	45,	46,	47,	48,	49,
		50,	51,	52,	53,	54,	55,	56,	57,	58,	59,
		60,	61,	62,	63,	64,	65,	66,	67,	68,	69,
		70,	71,	72,	73,	74,	75,	76,	77,	78,	79,
		80,	81,	82,	83,	84,	85,	86,	87,	88,	89,
		90,	91,	92,	93,	94,	95,	96,	97,	98,	99,
		100,	101,	102,	103,	104,	105,	106,	107,	108,	109,
		110,	111,	112,	113,	114,	115,	116,	117,	118,	119,
		120,	121,	122,	123,	124,	125,	126,	127,	128,	129,
		130,	131,	132,	133,	134,	135,	136,	137,	138,	139,
		140,	141,	142,	143,	144,	145,	146,	147,	148,	149,
		150,	151,	152,	153,	154,	155,	156,	157,	158,	159,
		160,	161,	162,	163,	164,	165,	166,	167,	168,	169,
		170,	171,	172,	173,	174,	175,	176,	177,	178,	179,
		180,	181,	182,	183,	184,	185,	186,	187,	188,	189,
		190,	191,	192,	193,	194,	195,	196,	197,	198,	199,
		200,	201,	202,	203,	204,	205,	206,	207,	208,	209,
		210,	211,	212,	213,	214,	215,	216,	217,	218,	219,
		220,	221,	222,	223,	224,	225,	226,	227,	228,	229,
		230,	231,	232,	233,	234,	235,	236,	237,	238,	239,
		240,	241,	242,	243,	244,	245,	246,	247,	248,	249,
		250,	251,	252,	253,	254,	255	
};

//中力转向故障表
const INT8U EP_STEER_CODE[100]=
{
// 00,  01,  02,  03,  04,  05, 06,   07,  08,  09,
    0, 241,  13,  70, 220, 227, 227, 227, 228,  83,		/* 0~9*/
  227,  70,  70,  72,  48, 227,  19,  19,  61,  65,		/*10~19*/
    0, 227,  53, 227, 227,  73,  32, 238, 249, 227,		/*20~29*/
    0, 227,  61,  61,  65, 227, 227, 227,  13, 227,		/*30~39*/
  227,  61,  61, 245, 245,   0,   0,   0,   0,   0,		/*40~49*/
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,		/*50~59*/
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,		/*60~69*/
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,		/*70~79*/
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,		/*80~89*/
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0		/*90~99*/
};

//转向控制器定时发送PDO报文
void PDO_Prco_ZHONGLI(void)
{
	static INT8U Count=0;
	tCANFrame canFrame;	//
	INT16U Index,SubIndex,Val;
	INT16U Temp;
	
	if(1)
	{
		if(QExpandAGV_PDO.CanBuf_IDSDOR[0] == 0x42)	//read
		{
			QExpandAGV_PDO.CanBuf_IDSDOR[0] = 0;
			Index = QExpandAGV_PDO.CanBuf_IDSDOR[2];
			Index = Index << 8;
			Index += QExpandAGV_PDO.CanBuf_IDSDOR[1];
			SubIndex = QExpandAGV_PDO.CanBuf_IDSDOR[3];
			
			if(((Index & 0xFF00) == 0x3600) || (((Index & 0xFF00) == 0x2600)))
			{
				canFrame.ulID = QEXPANDAGVSDOTX_ID_OFS + 0x2C;
				canFrame.ucXID = 0;			//0 标准帧；1 扩展帧  
				canFrame.ucDataLength = 8;		//数据场长度
				canFrame.ucData[0] = 0x42;
				canFrame.ucData[1] = Index & 0xFF;
				canFrame.ucData[2] = (Index >> 8) & 0xFF;;
				canFrame.ucData[3] = SubIndex;
				
				if(Index >= 0x36D5)	//monitor read
				{
					if((Index == 0x36D5) || (Index == 0x36D6)||(Index == 0x36D7))	//按照10进制显示
					{
						Temp = ReadMonitorParaValByIndex(EP_STEER_SDOTAB[Index-0x3600]);
						Val = (Temp) & 0x0F;
						Val += ((Temp >> 4) & 0x0F) * 10;
						Val += ((Temp >> 8) & 0x0F) * 100;
						Val += ((Temp >> 12) & 0x0F) * 1000;
					}
					else
						Val = ReadMonitorParaValByIndex(EP_STEER_SDOTAB[Index - 0x3600]);
				}
				else	//config read
					Val = ReadParaValByIndex(EP_STEER_SDOTAB[Index - 0x2600]);
				
				canFrame.ucData[4] = Val & 0xFF;
				canFrame.ucData[5] = (Val >> 8) & 0xFF;
				canFrame.ucData[6] = 0;
				canFrame.ucData[7] = 0;
				
				CANWriteBuffer(&canFrmTxBuffer, &canFrame);
			}
			else
			{
					//Index error
			}	
		}
		else if(QExpandAGV_PDO.CanBuf_IDSDOR[0] == 0x22)	//write
		{
			QExpandAGV_PDO.CanBuf_IDSDOR[0] = 0;
			Index = QExpandAGV_PDO.CanBuf_IDSDOR[2];
			Index = Index << 8;
			Index += QExpandAGV_PDO.CanBuf_IDSDOR[1];
			SubIndex = QExpandAGV_PDO.CanBuf_IDSDOR[3];
			
			if((Index & 0xFF00) == 0x2600)
			{
				Val = QExpandAGV_PDO.CanBuf_IDSDOR[5];
				Val = Val << 8;
				Val += QExpandAGV_PDO.CanBuf_IDSDOR[4];
				
				if(1)	//控制器停止状态
					EepromQualifiedWrite(EP_STEER_SDOTAB[Index - 0x2600],Val);
				
				canFrame.ulID=QEXPANDAGVSDOTX_ID_OFS + 0x2C;
				canFrame.ucXID = 0;			//0 标准帧；1 扩展帧  
				canFrame.ucDataLength = 8;		//数据场长度
				canFrame.ucData[0] = 0x60;
				canFrame.ucData[1] = Index & 0xFF;
				canFrame.ucData[2] = (Index >> 8) & 0xFF;;
				canFrame.ucData[3] = SubIndex;					
				canFrame.ucData[4] = 0;
				canFrame.ucData[5] = 0;
				canFrame.ucData[6] = 0;
				canFrame.ucData[7] = 0;
				
				CANWriteBuffer(&canFrmTxBuffer, &canFrame);
			}
			else
			{
					//Index error
			}				
		}	
	}

	Count++;
	if(!(Count&0x03))  //2*10=20ms
	{
		CanOpenUpdatePlcDataFromRxbuf();
//		CanOpenRxFrameMonitor();
//		if (QExpandAGV_PDO.CanBuf_ID1X0R_Delay >= 10)
//		{
//			QExpandAGV_PDO.CanBuf_ID1X0R[0] = 0;
//			QExpandAGV_PDO.CanBuf_ID1X0R[1] = 0;
//			
//			QExpandAGV_PDO.AgvHeartBeatError = 1;
//		}
//		else
//		{
//			QExpandAGV_PDO.CanBuf_ID1X0R_Delay += 1;
//			QExpandAGV_PDO.AgvHeartBeatError = 0;
//		}
		
		if(QExpandAGV_PDO.VCUControlWord & 0x0040)	//0x23C byte6.6 电刹开关 1-ON  0-OFF
			gCRam.bEnaSoft = 1;
		else
			gCRam.bEnaSoft = 0;
		
		//发送反馈报文
		canFrame.ulID = 0x360;
		canFrame.ucXID = 0;			//0 标准帧；1 扩展帧  
		canFrame.ucDataLength = 8;		//数据场长度
		
		if(SL_CHK(PLC_MIDDLE_RDY))		//homing ok flag
					QExpandAGV_PDO.StateWord |= 0x01;
		else  QExpandAGV_PDO.StateWord &= ~0x01;
		if(gCRam.bEnaSoft)		//upright flag
					QExpandAGV_PDO.StateWord |= 0x10;
		else  QExpandAGV_PDO.StateWord &= ~0x10;
		
		QExpandAGV_PDO.ErrorCode = gPLCCtl.ErrCode;		
		QExpandAGV_PDO.AngleMeasured =  (gPLCCtl.icanSteer.ucSteerAngleH<<8) + gPLCCtl.icanSteer.ucSteerAngleL;
		QExpandAGV_PDO.SpeedMeasured =  gPara.AcMotorSpeed; //rpm gCRam.SpeedAvgAdd*6250/gPLCCtl.enc; //0.01Hz

	
		canFrame.ucData[0] = QExpandAGV_PDO.StateWord & 0xFF;
		canFrame.ucData[1] = QExpandAGV_PDO.ErrorCode & 0xFF;
		canFrame.ucData[2] = (QExpandAGV_PDO.AngleMeasured) & 0xFF;
		canFrame.ucData[3] = (QExpandAGV_PDO.AngleMeasured >> 8) & 0xFF;
		canFrame.ucData[4] = (QExpandAGV_PDO.SpeedMeasured) & 0xFF;
		canFrame.ucData[5] = (QExpandAGV_PDO.SpeedMeasured >> 8) & 0xFF;
		canFrame.ucData[6] = (QExpandAGV_PDO.CurrentMeasured) & 0xFF;
		canFrame.ucData[7] = (QExpandAGV_PDO.CurrentMeasured >> 8) & 0xFF;
		
		CANWriteBuffer(&canFrmTxBuffer, &canFrame);
//		CANFrmSend(&canFrmTxBuffer);		
	}	
	
	if(!(Count&0x1F))  //32*5=160ms
	{
//		CanOpenUpdatePlcDataFromRxbuf();
////		CanOpenRxFrameMonitor();
//		if (QExpandAGV_PDO.CanBuf_ID1X0R_Delay >= 10)
//		{
//			QExpandAGV_PDO.CanBuf_ID1X0R[0] = 0;
//			QExpandAGV_PDO.CanBuf_ID1X0R[1] = 0;
//			
//			QExpandAGV_PDO.AgvHeartBeatError = 1;
//		}
//		else
//		{
//			QExpandAGV_PDO.CanBuf_ID1X0R_Delay += 1;
//			QExpandAGV_PDO.AgvHeartBeatError = 0;
//		}
//		
//		if(QExpandAGV_PDO.VCUControlWord & 0x0010)
//			gCRam.bEnaSoft = 1;
//		else
//			gCRam.bEnaSoft = 0;
		
		//发送反馈报文
		canFrame.ulID=0x353;
		canFrame.ucXID=0;			//0 标准帧；1 扩展帧  
		canFrame.ucDataLength=8;		//数据场长度
		
		if(SL_CHK(PLC_MIDDLE_RDY))		//homing ok flag
					QExpandAGV_PDO.StateWord |= 0x01;
		else  QExpandAGV_PDO.StateWord &= ~0x01;
		if(gCRam.bEnaSoft)		//upright flag
					QExpandAGV_PDO.StateWord |= 0x10;
		else  QExpandAGV_PDO.StateWord &= ~0x10;
			
		if(gPLCCtl.ErrCode<100)
			QExpandAGV_PDO.ErrorCode = EP_STEER_CODE[gPLCCtl.ErrCode];
		QExpandAGV_PDO.AngleMeasured =  (gPLCCtl.icanSteer.ucSteerAngleH<<8) + gPLCCtl.icanSteer.ucSteerAngleL;
		QExpandAGV_PDO.SpeedMeasured =  gPara.AcMotorSpeed; //rpm gCRam.SpeedAvgAdd*6250/gPLCCtl.enc; //0.01Hz
		QExpandAGV_PDO.BoardTemperature = gPara.ControllerTmp+55;	//偏移值-55。
		gPara.MotorTmp = 25;	
		QExpandAGV_PDO.MotorTemperature = gPara.MotorTmp+55;	//偏移值-55。默认值25。
		QExpandAGV_PDO.CurrentMeasured = gPara.AcPhaseCurrent;
		
		canFrame.ucData[0] = QExpandAGV_PDO.ErrorCode;
		canFrame.ucData[1] = 0;
		canFrame.ucData[2] = 0x14;
		canFrame.ucData[3] = (QExpandAGV_PDO.BoardTemperature) & 0xFF;
		canFrame.ucData[4] = (QExpandAGV_PDO.MotorTemperature) & 0xFF;
		canFrame.ucData[5] = (QExpandAGV_PDO.CurrentMeasured) & 0xFF;
		canFrame.ucData[6] = (QExpandAGV_PDO.CurrentMeasured >> 8) & 0xFF;
		canFrame.ucData[7] = 0;
		
		CANWriteBuffer(&canFrmTxBuffer, &canFrame);
//		CANFrmSend(&canFrmTxBuffer);		
	}
}

