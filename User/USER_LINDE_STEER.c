#include <string.h>
#include "Device.h"
#include "CommonRam.h"
#include  "CanOpen_Linde.h"
//#include "CanSTM32F4.h"

void PDO_Prco_LINDE(void);
//转向控制器定时发送PDO报文
#if(USER_TYPE == USER_LINDE_DDTBC_STEER)

//bit define for VCUControlWord
#define MOVE_READY_ControlWord		(1<<2)  //主接触器READY
#define AUTOHOME_ControlWord		(1<<3)  //一键回中
#define UPRIGHT_ControlWord			(1<<4)  //直立行走

//bit define for StateWord
#define HOMERDY_StateWord			(1<<0)  //回中完成标志
#define LEFTLIMIT_StateWord			(1<<1)  //左限位
#define RIGHTLIMIT_StateWord		(1<<2)  //右限位
#define UPRIGHT_StateWord			(1<<4)  //直立行走
#define RESERVED1_StateWord			(1<<5)  //预留1
#define RESERVED2_StateWord			(1<<6)  //预留2
#define RESERVED3_StateWord			(1<<7)  //预留3


const INT8U LINDE_ERR_TAB[100]= {
	0x00, 0x47,0x43,0x44,0x73,0x00,0x00,0x00,0x24,0x00, /* 0~9 */
	0x00, 0x21,0x12,0x14,0x00,0x00,0x17,0x18,0x22,0x00, /* 10~19 */	
	0x41, 0x00,0x13,0x37,0x31,0x34,0x62,0x53,0x42,0x00, /* 20~29 */
	0x00, 0x00,0x16,0x15,0x73,0x00,0x00,0x00,0x46,0x75, /* 30~39 */
	0x45, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 40~49 */
	0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 50~59 */
	0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 60~69 */
	0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 70~79 */
	0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 80~89 */
	0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 90~99 */	
};

//中力转向SDO
//const INT16U EP_STEER_SDOTAB[256]=
//{
//// 00,  01,  02,  03,  04,  05, 06,   07,  08,  09,
//		0,	1,	2,	3,	4,	5,	6,	7,	8,	9,
//		10,	11,	12,	13,	14,	15,	16,	17,	18,	19,
//		20,	21,	22,	23,	24,	25,	26,	27,	28,	29,
//		30,	31,	32,	33,	34,	35,	36,	37,	38,	39,
//		40,	41,	42,	43,	44,	45,	46,	47,	48,	49,
//		50,	51,	52,	53,	54,	55,	56,	57,	58,	59,
//		60,	61,	62,	63,	64,	65,	66,	67,	68,	69,
//		70,	71,	72,	73,	74,	75,	76,	77,	78,	79,
//		80,	81,	82,	83,	84,	85,	86,	87,	88,	89,
//		90,	91,	92,	93,	94,	95,	96,	97,	98,	99,
//		100,	101,	102,	103,	104,	105,	106,	107,	108,	109,
//		110,	111,	112,	113,	114,	115,	116,	117,	118,	119,
//		120,	121,	122,	123,	124,	125,	126,	127,	128,	129,
//		130,	131,	132,	133,	134,	135,	136,	137,	138,	139,
//		140,	141,	142,	143,	144,	145,	146,	147,	148,	149,
//		150,	151,	152,	153,	154,	155,	156,	157,	158,	159,
//		160,	161,	162,	163,	164,	165,	166,	167,	168,	169,
//		170,	171,	172,	173,	174,	175,	176,	177,	178,	179,
//		180,	181,	182,	183,	184,	185,	186,	187,	188,	189,
//		190,	191,	192,	193,	194,	195,	196,	197,	198,	199,
//		200,	201,	202,	203,	204,	205,	206,	207,	208,	209,
//		210,	211,	212,	213,	214,	215,	216,	217,	218,	219,
//		220,	221,	222,	223,	224,	225,	226,	227,	228,	229,
//		230,	231,	232,	233,	234,	235,	236,	237,	238,	239,
//		240,	241,	242,	243,	244,	245,	246,	247,	248,	249,
//		250,	251,	252,	253,	254,	255	
//};

#define ERRCODE_MAXLEN	5
//故障码周期循环发送，循环周期 40ms
uint8_t ErrorCodeDisp(uint8_t ErrCode)
{
	static INT8U u8DispCnt;
	static INT8U u8ErrorCodeNum=0;
	static uint8_t ErrorCodeSend[ERRCODE_MAXLEN]={0};
	
	if(ErrCode == 0) 
	{		
		u8ErrorCodeNum = 0;
		memset(ErrorCodeSend,0,ERRCODE_MAXLEN);
		return 0;
	}
	
	u8DispCnt++; //显示循环计数器
	
	for(uint8_t i=0; i< ERRCODE_MAXLEN; i++)
	{
		if(ErrorCodeSend[i] == ErrCode) //already in ErrorCodeSend
		{
			break;
		}
		else if(ErrorCodeSend[i]==0)//new error code 
		{
			ErrorCodeSend[i] = ErrCode;
			u8ErrorCodeNum++;
			break;
		}
	}
	
	if(u8ErrorCodeNum) //有故障码
	{
		return ErrorCodeSend[u8DispCnt % u8ErrorCodeNum]; //显示发送故障码
	}
	return 0 ;
}

void PDO_Prco_LINDE(void)
{
	static INT8U Count=0;
	tCANFrame canFrame;	//
	

		CanOpenUpdatePlcDataFromRxbuf();
		CanOpenRxFrameMonitor();
		
		if(QExpandAGV_PDO.AgvHeartBeatError == 1) 
			MCL_SetFault(HEARTBEAT_ERR);

//		if(QExpandAGV_PDO.VCUControlWord & MOVE_READY_ControlWord)	//主接触器READY
//			gCRam.bReady = 1;
//		else
//			gCRam.bReady = 0;
		
		if(QExpandAGV_PDO.VCUControlWord & UPRIGHT_ControlWord)  //直立行走
		{
			gCRam.bEnaSoft = 1;			
		}
		#ifdef ONEKEY_BACKHOME
		else if(QExpandAGV_PDO.VCUControlWord & AUTOHOME_ControlWord)  //一键回中	
		{
			gCRam.bKeyBackhome = 1;
			gCRam.bEnaSoft = 1;
		}
		#endif
		else
		{
			//gCRam.bKeyBackhome = 0;
			gCRam.bEnaSoft = 0;
		}
		
		//主控报15#制动器故障、36#DO3、37#DO4故障，则关闭FaultOut		
		if((QExpandAGV_PDO.ErrorMove==0x32) || (QExpandAGV_PDO.ErrorMove==0xA3) || (QExpandAGV_PDO.ErrorMove==0xA4))	
		{
			gPLCCtl.doDataOut[FAULT_OUT] = 0;	//关闭输出
			QExpandAGV_PDO.StateWord |= RESERVED3_StateWord;
		}
		else
		{
			gPLCCtl.doDataOut[FAULT_OUT] = 1;
			QExpandAGV_PDO.StateWord &= ~RESERVED3_StateWord;
		}		
		
		gCRam.MoveSpeedFdb = QExpandAGV_PDO.MoveSpeedFdb;

	if(!(Count++&0x03))  //4*10=40ms
	{		
		//发送反馈报文
		canFrame.ulID=0x360;
		canFrame.ucXID=0;			//0 标准帧；1 扩展帧  
		canFrame.ucDataLength=8;		//数据场长度
		
		if(SL_CHK(PLC_MIDDLE_RDY))		//homing ok flag
					QExpandAGV_PDO.StateWord |= HOMERDY_StateWord;
		else  QExpandAGV_PDO.StateWord &= ~HOMERDY_StateWord;
		if(gCRam.bEnaSoft)		//upright flag
					QExpandAGV_PDO.StateWord |= UPRIGHT_ControlWord;
		else  QExpandAGV_PDO.StateWord &= ~UPRIGHT_ControlWord;
		
		QExpandAGV_PDO.ErrorCode = ErrorCodeDisp(gPLCCtl.ErrCode);//gPLCCtl.ErrCode;		
		QExpandAGV_PDO.AngleMeasured =  (gPLCCtl.icanSteer.ucSteerAngleH<<8) + gPLCCtl.icanSteer.ucSteerAngleL;
		QExpandAGV_PDO.SpeedMeasured =  gPara.AcMotorSpeed; //rpm gCRam.SpeedAvgAdd*6250/gPLCCtl.enc; //0.01Hz
		QExpandAGV_PDO.BoardTemperature = gPara.ControllerTmp + 40;	//偏移值40。

	
		canFrame.ucData[0] = QExpandAGV_PDO.StateWord & 0xFF;
		canFrame.ucData[1] = QExpandAGV_PDO.ErrorCode & 0xFF;
		canFrame.ucData[2] = (QExpandAGV_PDO.AngleMeasured) & 0xFF;
		canFrame.ucData[3] = (QExpandAGV_PDO.AngleMeasured >> 8) & 0xFF;
		canFrame.ucData[4] = (QExpandAGV_PDO.SpeedMeasured) & 0xFF;
		canFrame.ucData[5] = (QExpandAGV_PDO.SpeedMeasured >> 8) & 0xFF;
	#ifdef STEERVOLT_SEND_ENABLE
		canFrame.ucData[6] = (gPara.ThrottleWipVoltage/10) & 0xFF;
		canFrame.ucData[7] = ((gPara.ThrottleWipVoltage/10) >> 8) & 0xFF;
	#else
		canFrame.ucData[6] = (QExpandAGV_PDO.CurrentMeasured) & 0xFF;
		canFrame.ucData[7] = (QExpandAGV_PDO.CurrentMeasured >> 8) & 0xFF;
	#endif	//#ifdef STEERVOLT_SEND_ENABLE
		
		CANWriteBuffer(&canFrmTxBuffer, &canFrame);
//		CANFrmSend(&canFrmTxBuffer);		
	}
	
	if(!(Count&0x7F))  //64*10=640ms
	{	
			//发送反馈报文
			INT32S lTemp;
			QExpandAGV_PDO.Current =  gPara.AcPhaseCurrent*10;
			lTemp = gCRam.CmdPercent;
			QExpandAGV_PDO.PotVolt =  (lTemp<<15)/100; //		
			QExpandAGV_PDO.BoardTmp = gPara.ControllerTmp*10;
		
			canFrame.ulID=0x3E0;
			canFrame.ucXID=0;			//0 标准帧；1 扩展帧  
			canFrame.ucDataLength=8;		//数据场长度
			canFrame.ucData[0] = QExpandAGV_PDO.Current & 0xFF;
			canFrame.ucData[1] = (QExpandAGV_PDO.Current >> 8) & 0xFF;
			canFrame.ucData[2] = (QExpandAGV_PDO.PotVolt) & 0xFF;
			canFrame.ucData[3] = (QExpandAGV_PDO.PotVolt >> 8) & 0xFF;
			canFrame.ucData[4] = (QExpandAGV_PDO.BoardTmp) & 0xFF;
			canFrame.ucData[5] = (QExpandAGV_PDO.BoardTmp >> 8) & 0xFF;
			canFrame.ucData[6] = gCRam.bEnaHard;
			canFrame.ucData[7] = gCRam.bEnaSoft;
			
			CANWriteBuffer(&canFrmTxBuffer, &canFrame);
	}
	
	CanOpenUpdateTxbufFromPlcData();
	CanOpenTxFrame();
}
#endif //#if(USER_TYPE == USER_LINDE_STEER)
