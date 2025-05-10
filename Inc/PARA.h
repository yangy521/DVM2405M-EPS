/*******************************************************************************
* Filename: PARA.h 	                                         		   		   *
*                                                                              *
* Description: 																   *
* Author:                                                                      *
* Date: 															           *
* Revision:															           *
*******************************************************************************/
#ifndef _PARA_H_
#define _PARA_H_
#include "KSDsys.h"
#include "iCAN.h"

#define ErrTraceNum         8
#define PARA_NO_ERRORTRACE0     200
#define PARA_VOLUME_NUM				255
#define PARA_HARDHEAD_NUM				(234)
#define PARA_HARDEND_NUM				(249)
#define EEPROM_PARA_NUM				256

#define PARA_NO_HOURPOWERON_FLAG1	  	217	
#define PARA_NO_HOURPOWERON_COUNTL1	  218	
#define PARA_NO_HOURPOWERON_COUNTH1	  219	
#define PARA_NO_HOURPOWERON_FLAG2	  	220	
#define PARA_NO_HOURPOWERON_COUNTL2	  221	
#define PARA_NO_HOURPOWERON_COUNTH2	  222	

#define PARA_NO_BATTERY_FLAG1	  	224	
#define PARA_NO_BATTERY_COUNT1	  225	
#define PARA_NO_BATTERY_FLAG2	  	226	
#define PARA_NO_BATTERY_COUNT2	  227	

#define PARA_NO_HOUR_FLAG1	  	228	
#define PARA_NO_HOUR_COUNTL1	  229	
#define PARA_NO_HOUR_COUNTH1	  230	
#define PARA_NO_HOUR_FLAG2	  	231	
#define PARA_NO_HOUR_COUNTL2	  232	
#define PARA_NO_HOUR_COUNTH2	  233	
#define BATTERY_HOUR_VALID			0x5555
#define BATTERY_HOUR_INVALID		0xFFFF
/******************************************************************************/
#define	PRM_ATTR_POWEROFF  	(1 << 0)
#define	PRM_ATTR_SIGNED    	(1 << 1)
#define	PRM_ATTR_SIZE(n) 	(sizeof(n) << 2)
#define	PRM_ATTR_POSOFS(n)  ((n & 0x1f) << 4)
#define	PRM_ATTR_BITNUM(n)  (((n-1) & 0x1f) << 9)
#define	PRM_ATTR_TYPE_BIT_SET(ofs,len)  	(PRM_ATTR_TYPE_BIT | PRM_ATTR_POSOFS(ofs) | PRM_ATTR_BITNUM(len))
#define PRM_ATTR_RDPOWER(n)	((n & 0x7) << 14)
#define PRM_ATTR_WRPOWER(n)	((n & 0x7) << 17)
#define PRM_ARRT_EPROM			(1 << 20)
#define PRM_ATTR_TYPE_BIT		(1 << 21)
#define PRM_ARRT_HARD			(1 << 22)
typedef struct
{
	INT32U	PowerOff : 1;	// 0--No poweroff required, 1--Poweroff required
	INT32U	Signed : 1; 	// 0--unsigned, 1--signed,
	INT32U	Size : 2;			// 0--bit, 1--byte, 2--half word, 3--rsv
	INT32U	PosOfs : 5;		// This para‘s bit offset in para var. 0-bit0, 31-bit31
	INT32U	BitNum : 5;   // This para‘s bit number. 0~31 - 1~32 bit
	INT32U	RdPower : 3;   // bit0--一级读权限
	INT32U	WrPower : 3;   // bit0--一级写权限
	INT32U	Eprom: 1;   // 
	INT32U	Bit: 1;   // 
	INT32U	Hard: 1;   // 
	INT32U	 rev: 9;   // 
} PRM_ATTR_STRUCT;


typedef struct
{
	INT32U	PrmNo;
	INT32U	PrmAttr;
	INT32S  PrmMinVal;
	INT32S  PrmMaxVal;
	INT32S  PrmInitVal;
	void*	  pPrmData;
	const CHAR* m_pStrGroup;
//	const CHAR* m_pStr0;
//	const CHAR* m_pStr1;
//	const CHAR* m_pStr2;
//	const CHAR* m_pStr3;
//	const CHAR* m_pStr4;
//	const CHAR* m_pStr5;
//	const CHAR* m_pStr6;
//	const CHAR* m_pStr7;
} PRM_DEF_STRUCT;

/* ConBit1 bit define */
#define AcMotorSwapEncoderDir  	(0x1 << 0)	//bit0: Changes the motor encoder's effective direction of rotation.
#define RotationDir  						(0x1 << 1)	//bit1:  旋转方向 
#define MotorTmpChkEnable  			(0x1 << 2)	//bit2:  电机温度传感器使能
#define PosHoldEnable  					(0x1 << 3)	//bit3:  位置保持使能
//#define RSV  							(0x1 << 4)	//bit4: hpd check
#define THROTTLE_PEDAL_ENABLE 	(0x1 << 5)	//bit5: Throttle enable
#define BrakePedalEnable  			(0x1 << 6)	//bit6: Brake enable 
#define MetricUnits  						(0x1 << 7)	//bit7: Metric Units

/* ConBit2 bit define */
//#define Rsv  							(0x1 << 0)	//bit0:
//#define Rsv  							(0x1 << 1)	//bit1:
//#define Rsv  							(0x1 << 2)	//bit2:
//#define Rsv  							(0x1 << 3)	//bit3:
#define HpdCheck  							(0x1 << 4)	//bit4: hpd check
#define SroCheck 								(0x1 << 5)	//bit5: Sro check
//#define Rsv  							(0x1 << 6)	//bit6:
//#define Rsv  							(0x1 << 7)	//bit7:

/* DriverEn1 bit define */
#define MainEnable							(0x1 << 0)	//bit0-MainEnable; 
#define MainCheckEnable					(0x1 << 1)	//bit1- 主接触器使能
#define InterlockEnable					(0x1 << 2)	//bit2- 互锁使能,io
#define BrakeEnable							(0x1 << 3)	//bit3- 制动输出使能
#define BrakeTrqPreload					(0x1 << 4)	//bit4-BrakeTrqPreload;
#define BrakeSetOnFault					(0x1 << 5)	//bit5-BrakeSetOnFault;
#define PdEnable								(0x1 << 6)	//bit6-PdEnable;
#define PdHydLowerEnable				(0x1 << 7)	//bit7-PdHydLowerEnable;

/* DriverEn2 bit define */
#define Drive1Enable						(0x1 << 0)	//bit0-Drive1Enable; 
#define Drive2Enable						(0x1 << 1)	//bit1-Drive2Enable;
#define Drive3Enable						(0x1 << 2)	//bit2-Drive3Enable;
#define Drive4Enable						(0x1 << 3)	//bit3-Drive4Enable;
#define PdCheckEnable						(0x1 << 4)	//bit4-PdCheckEnable; 
#define SWI1Type								(0x1 << 5)	//bit5- SWI1Type 0：数字输入；1：模拟输入
#define EmrEnable								(0x1 << 6)	//bit6- EmrEnable
#define EmrDirLock							(0x1 << 7)	//bit7- EmrDirLock

/* SteerBit bit define */
#define FXP_ROTDIR							(0x01 << 0)		//bit0- FXP rotation direction				
#define ZERO_RETURNDIR					(0x01 << 1)		//bit1- Middle pos return direction				
#define ZERO_RETURN_SVON  			(0x01 << 2)		//bit2- Middle return action each time SVON

typedef struct
{
	/* CAN */
	INT16U  CanEn; 			    //bit0~7  dirver act; SteerCommEnable
	INT16U  CanLockEn; 			//bit0~7  dirver can lock act;
	INT16U ConBit1;            
													//"Bit0: 编码器换向",
													//"Bit1: 电机反向",
													//"Bit2: 检查电机温度使能",
													//"Bit3: 位置保持使能",
													//"Bit4: Rsv",
													//"Bit5: 油门踏板使能",
													//"Bit6: 制动踏板使能",
													//"Bit7: 英制单位",
	INT16U ConBit2;            
													//	"Bit0: Rsv",
													//	"Bit1: Rsv",
													//	"Bit2: Rsv",
													//	"Bit3: Rsv",
													//	"Bit4: Throttle hpd check",
													//	"Bit5: Throttle sro check",
													//	"Bit6: Rsv",
													//	"Bit7: Rsv",
	INT16U  CanHeartBeat;    //0~80 =  0~400ms

	/* motor */
	INT16U	MotorType;						/*电机类型0:电机参数上位机设定；1~n：电机参数程序预先内置 cMotorParaRom[n] */
	/* motor_constant */
	INT16U AcMotorPloes;				 //电机极对数
	INT16U	EncoderLineNum; 				//编码器线数
	INT16U	Inertia;						//惯量 0.0001 Kgm^2
	INT16U	StatorResist;				//定子电阻 0.00001 ohm
	INT16U	StatorTimeConstant;	//定子时间常数 0.0001 s
	INT16U	TorqueCoe1;					//转矩系数1  0.001 A/NM
	INT16U	RotorTimeConstant;	//转子时间常数 0.0001 s
	INT16U	AcMotorFluxRatio;		//励磁电流占最大电流的比例
	INT16U	AcMotorWkBaseSpdF;	 //Base frq for weak flux uint 0.01hz 600~20000

	INT16U	AcMotorTypicalSpdF;	 //Typical frq, as standard for acc/dec rate. uint 0.01hz
	INT16U	AcMotorRateSpdF;		 //Base frq for current limit uint 0.01hz
	INT16U	AcMotorDeltaSpdF;		 //Delta frq uint 0.01hz
	INT16U	AcMotorDriveCurrentLimitRatio;		//Drive current limit ratio of max driver current  5~100%--1638~32767
	INT16U	AcMotorUphillCurrentLimitRatio;		//Drive current limit ratio of max driver current  5~100%--1638~32767
	INT16U	AcMotorRegenCurrentLimitRatio;		//Regenerate current limit ratio of max driver current  5~100%--1638~32767
	INT16U	AcMotorBrakeCurrentLimitRatio;		//Brake current limit ratio of max driver current  5~100%--1638~32767
	INT16U	AcMotorEmrCurrentLimitRatio;		//Emr Brake & Drive current limit ratio of max driver current  5~100%--1638~32767
	INT16U	AcMotorDriveMapNominalRatio;	//Drive current limit  map nominal ratio 0~100%--0~32767
	INT16U	AcMotorDriveMapDelta1Ratio;		//Drive current limit  map nominal ratio 0~100%--0~32767
	INT16U	AcMotorDriveMapDelta2Ratio;		//Drive current limit  map nominal ratio 0~100%--0~32767
	INT16U	AcMotorDriveMapDelta4Ratio;		//Drive current limit  map nominal ratio 0~100%--0~32767
	INT16U	AcMotorDriveMapDelta8Ratio;		//Drive current limit  map nominal ratio 0~100%--0~32767
	INT16U	AcMotorRegenMapNominalRatio;	//Regenerate current limit  map nominal ratio 0~100%--0~32767
	INT16U	AcMotorRegenMapDelta1Ratio;		//Regenerate current limit  map nominal ratio 0~100%--0~32767
	INT16U	AcMotorRegenMapDelta2Ratio;		//Regenerate current limit  map nominal ratio 0~100%--0~32767
	INT16U	AcMotorRegenMapDelta4Ratio;		//Regenerate current limit  map nominal ratio 0~100%--0~32767
	INT16U	AcMotorRegenMapDelta8Ratio;		//Regenerate current limit  map nominal ratio 0~100%--0~32767
	INT16U	AcMotorWkPowerRatio;					//The amount of high speed power the controller will allow 0~100%--0~32767
	INT16U	AcMotorWkRate;								//The control loop gains for field weakening.
	INT16U	WkAdjRatio;										//The weak flux Ratio adjustment amount from WkBaseHZ to TypicalHZ 12.5%~800%--512~32767

	INT16U	MotorTmpSensorType;	//温度传感器类型 ,0-no sensor; 1~255 - Valid sensor
	INT16S	MotorTmpOfs;				//tem offset
	INT16U	MotorCutTmp;				//电机过载温度1，需降低电机电流
	INT16U	MotorMaxTmp;				//电机最大极限温度，需停止运行
	INT16U MotorTmpLosSpd;         //Sensor lost ,limit the spd

	/* Speed */
	INT16U	FwdMaxSpd;			 //Maximum frq at full throttle uint 0.01hz, 
	INT16U	RvsMaxSpd;					//反向最大速度
	INT16U	IntertiaRatio;		/* 惯量比(%) */
	INT16U	SpeedWc;					/* 速度环截止频率(Hz) */
	INT16U	SpeedWit;					/* 速度环积分时间(ms) */
	INT16U	TorFilt1W;				/* 一阶转矩滤波器截止频率(Hz) */
	INT16U	TorFilt2W;				/* 二阶转矩滤波器截止频率(Hz) */
	INT16U	TorFilt2Q;				/* 二阶转矩滤波器品质因数(%) */

	INT16U	KvffCurrent;			/* V forward control 0~500A -- 0~5000 */
	INT16U	KvffBuildTime;		/* Kvff build up time 0.1~5.0 sec -- 100~5000 */
	INT16U	KvffReleaseTime;	/* Kvff release time  0.1~2.0 sec -- 100~2000 */
	
	INT16U	KaccCurrent;			/* Acc forward control 0~500A -- 0~5000 */
	INT16U	KbkeCurrent;			/* Brake forward control 0~500A -- 0~5000 */
	INT16U	KaccBuildTime;		/* Kacc build up time 0.1~5.0 sec -- 100~5000 */
	INT16U	KaccReleaseTime;	/* Kacc release time  0.1~2.0 sec -- 100~2000 */
	
	INT16U	FullAccTimeHs;	/* Acc time for full throttle at high speed  0.1~30.0 sec -- 100~30000*/
	INT16U	FullAccTimeLs;	/* Acc time for full throttle at low speed  0.1~30.0 sec -- 100~30000*/
	INT16U	LowAccTime;	    /* Acc time for small amount throttle  0.1~30.0 sec -- 100~30000*/
	INT16U	NeutralDecTimeHs;	/* Dec time for neutral throttle at high speed  0.1~30.0 sec -- 100~30000*/
	INT16U	NeutralDecTimeLs;	/* Dec time for neutral throttle at low speed  0.1~30.0 sec -- 100~30000*/
	INT16U	FullBrakeDecTimeHs;	/* Dec time for full brake or full neg throttle at high speed  0.1~30.0 sec -- 100~30000*/
	INT16U	FullBrakeDecTimeLs;	/* Dec time for full brake or full neg throttle at low speed  0.1~30.0 sec -- 100~30000*/
	INT16U	LowBrakeDecTimeHLs;	    /* Dec time for small amount Brake or small amount neg throttle 0.1~30.0 sec -- 100~30000*/
	INT16U	PartialDecTimeHLs;	   /* Dec time for throttle up  neutral 0.1~30.0 sec -- 100~30000*/
	INT16U	HighSpeedRatio;				/*Sets Hs percentage of the Typical Max Speed 0~100%--0~32767*/
	INT16U	LowSpeedRatio;				/*Sets Ls percentage of the Typical Max Speed 0~100%--0~32767*/
	INT16U	SmallSpeedRatio;			/*Sets Small percentage of the Typical Max Speed 0~100%--0~32767*/
	INT16U	ReversalSoften;		/*Larger values create a softer reversal from regen braking to drive when near zero speed.*/
	INT16U	MaxSpdAccTime;		/*Acc time for maxspd vary.  0.1~30.0 sec -- 100~30000*/
	INT16U	MaxSpdDecTime;		/*Dec time for maxspd vary.  0.1~30.0 sec -- 100~30000*/

	INT16U	SpeedRate1;					/*Sets gear 1 percentage of the Typical Max Speed 0~100%--0~100*/
	INT16U	SpeedRate2;					/*Sets gear 2 percentage of the Typical Max Speed 0~100%--0~100*/
	INT16U	SpeedRate3;					/*Sets gear 3 percentage of the Typical Max Speed 0~100%--0~100*/
	INT16U	SpeedRate4;					/*Sets gear 4 percentage of the Typical Max Speed 0~100%--0~100*/
	/* Restraint */
	//Position Hold Enable  ConBit1:bit3
	INT16U	SoftStopSpeed;	//Defines the speed below which a much slower decel rate is used.
	INT16U	 EntryRateStop;			//Defines the dec rate when speed below SoftStopSpeed
	INT16U		SetSpeedThreshold; //Determines the speed below which the EM brake will be commanded to set.
	INT16U  SetSpeedSettleTime;//Determines how long the position hold function is allowed to operate before the EM brake is set.
	INT16U	StopMode;						//Ramp stop mode: 1-stop,2- move~stop~move~;3- stop-move~~
	INT16U	EntryRateApproach;			//Defines the Acc/dec rate when speed error below SoftStopSpeed

	INT16U  SpdAccRatioFast;  /* The acc ratio for Fast Mode  12.5%~800% -- 512~32767 */
	INT16U  SpdDecRatioFast;  /* The dec ratio for Fast Mode  12.5%~800% -- 512~32767 */
	INT16U  SpdAccRatioSlow;  /* The acc ratio for Slow Mode  12.5%~800% -- 512~32767 */
	INT16U  SpdDecRatioSlow;  /* The dec ratio for Slow Mode  12.5%~800% -- 512~32767 */

	/* Throttle */
	INT16U	ThrottleType;	        //脚踏板速度信号输入类型：0：电压输入；1：2线电阻输入；2；3线电阻输入；3：总线输入
	INT16U	ThrottleMinVoltage;		//踏板死区最小值
	INT16U	ThrottleMaxVoltage;		//踏板死区最大值
	INT16U ThrottleMap;					//踏板斜率曲线（%）
	INT16U ThrottleOfs;					//initial ofs to increase act

	INT16U	ThrottleMinVoltageRvs;		//踏板死区最小值
	INT16U	ThrottleMaxVoltageRvs;		//踏板死区最大值
	INT16U ThrottleOfsRvs;					//initial ofs to increase act
	INT16U ThrottleMapRvs;					//踏板斜率曲线（%）
	INT16U SequenceDelay;          //the interlock switch to be cycled within a set time 0~250 -- 0~5s
	/* Brake */
	INT16U	BrakePedalType;	        //脚踏板速度信号输入类型：0：电压输入；1：2线电阻输入；2；3线电阻输入；3：总线输入
	INT16U	BrakePedalMinVoltage;		//踏板死区最小值
	INT16U	BrakePedalMaxVoltage;		//踏板死区最大值
	INT16U	BrakePedalMap;						//踏板斜率曲线（%）
	INT16U BrakePedalOfs;					//initial ofs to increase act

	/* Second Move */

	/* Vehicle */
	//Metric Units ConBit1:bit7
	INT16U SpdPerKmRatio;		//conversion factor that scales motor speed to vehicle speed ((vehicle speed 0.1kmph)*2^15/(motor rpm))
	INT16U CapSpd1;					//The controller captures the time it takes the motor to go from 0 rpm to this para val, set to TimetoSpd1
	INT16U CapSpd2;					//The controller captures the time it takes the motor to go from 0 rpm to this para val, set to TimetoSpd2
	INT16U CapDist1;		//The controller captures the time it takes the vehicle to travel from 0 rpm to the programmed Capture Distance,store to TimetoDist1
	INT16U CapDist2;		//The controller captures the time it takes the vehicle to travel from 0 rpm to the programmed Capture Distance,store to TimetoDist2
	INT16U CapDist3;		//The controller captures the time it takes the vehicle to travel from 0 rpm to the programmed Capture Distance,store to TimetoDist1
	INT16U WeihuPeriod; //Wei hu period. Unit 1Hour.
	/* Driver */
	INT16U DriverEn1;		//bit0-MainEnable; 
	                    //bit1-MainCheckEnable 主接触器使能
	                    //bit2-InterlockEnable 互锁使能,io
	                    //bit3-BrakeEnable;  制动输出使能
	                    //bit4-BrakeTrqPreload;
	                    //bit5-BrakeSetOnFault;
	                    //bit6-PdEnable;
	                    //bit7-PdHydLowerEnable;
	INT16U DriverEn2;		//bit0-Drive1Enable; 
											//bit1-Drive2Enable;
											//bit2-Drive3Enable;
											//bit3-Drive4Enable;
											//bit4-PdCheckEnable; 
											//bit5- SWI1Type 0：数字输入；1：模拟输入
											//bit6- EmrEnable
											//bit7- EmrDirLock
	/* Main Contactor */
	INT16U	MainPullVoltage;	//initial voltage when the contactor driver first turns on,1~100-- 1~100%
	INT16U	MainHoldVoltage;	//reduced average voltage to be applied to the contactor coil once it has closed.1~100-- 1~100%
	INT16U MainOpenDelay;   //Delay time after the interlock lost.
	INT16U MainDncThreshold;   //Voltage for detecting the main drive do not closed.
	/* Drive3 */
	INT16U	Drive3PullVoltage;	//initial voltage when the contactor driver first turns on,1~100-- 1~100%
	INT16U	Drive3HoldVoltage;	//reduced average voltage to be applied to the contactor coil once it has closed.1~100-- 1~100%
	/* Drive4 */
	INT16U	Drive4PullVoltage;	//initial voltage when the contactor driver first turns on,1~100-- 1~100%
	INT16U	Drive4HoldVoltage;	//reduced average voltage to be applied to the contactor coil once it has closed.1~100-- 1~100%
	/* EmBrake */
	INT16U	EmBrkType;
	INT16U	EmBrkPullVoltage;	//initial voltage when the contactor driver first turns on,1~100-- 1~100%
	INT16U	EmBrkHoldVoltage;	//reduced average voltage to be applied to the contactor coil once it has closed.1~100-- 1~100%
													// BrkHoldVoltage
	INT16U TrqPreloadDelay;
	INT16U EmBrkReleaseDelay; //
	INT16U TrqPreloadCancelDelay;
	
	/* Propdriver */
	INT16U	PropDKp;					/* Propdriver current loop Kp gain 1%~100%--328~32767 */
	INT16U	PropDKi;					/* Propdriver current loop Ki gain 1%~100%--82~8192 */
	INT16U	PropDMaxCurrent;	/* Propdriver max current 0~2.0A -- 0~2000 */
	INT16U	PropDMinCurrent;	/* Propdriver min current 0~2.0A -- 0~2000 */
	INT16U	PropDDitherPeriod;/* Propdriver dither period 15ms~120ms--1~8 */
	INT16U	PropDDitherRatio;	/* Propdriver dither current ratio.(DitherCurrent/PropDMaxCurrent) 0~100% -- 0~32767 */
	INT16U	PropValveResistance;	/* Prop valve coil resistance. 1~1000 ohm -- 10~10000 */
	/* Emreverse */
	INT16U  EmrTimeLimit;					/* Time limit after the vehicle is moving in the reverse direction.0~30000--0~30s */
	                              /* >30000 is a special case of no limit */
	INT16U  EmrSpeed;             /* The maximum reverse speed when emergency reverse is active. 0.01Hz*/
	INT16U  EmrAccTime;           /* Rate for reverse acc 100~3000 -- 0.1~3 s */
	INT16U  EmrDecTime;           /* Rate for dec forward move to stop 100~3000 -- 0.1~3 s */
	
    INT16U  RedundantParaConfig;    //redundant para config
	INT16U  CANBaudrate; //CAN baudrate. 0:default, 125:125K, 250:250K, 500:500K, 800:800K, 1000:1M 	;   
	/* Steer */
	INT16U  SteerBit;
	INT16U  PosRefFiltT;      /*位置指令平滑时间ms*/
	INT16U	PosKp;						/* 位置环增益(rad/s) */
	INT16U	PosGearNum;	  		//齿轮比分子
	INT16U	PosGearDen;				//齿轮比分母
	INT16U PosCmdFor90Degree;			//Cmd Pulse number(M4) required for steer wheel rotate 90 degree.
	INT16U PosCmdLimitCw;					//CW转向范围限制	
	INT16U PosCmdLimitCcw;					//CCW转向范围限制	
	INT16S MiddleOfs;					//中点位置(0度)
	INT16S MiddleDirErr;					//反向间隙，向右转动回到零点到向左转动回到零点之间的矢量，右向(Cw)为正。

	/* Bat meter */
	INT16U	BatFlag1;
	INT16U	BatCount1;
	INT16U	BatFlag2;
	INT16U	BatCount2;
	/* Hour count */
	INT16U	HourFlag1;
	INT16U	HourCount1L;
	INT16U	HourCount1H;
	INT16U	HourFlag2;
	INT16U	HourCount2L;
	INT16U	HourCount2H;
	/*Hardware*/
	INT16U	CurrentULin;
	INT16U	CurrentVLin;
	INT16U	KsiVotageLin;
	INT16S	KsiVotageOfs;
	INT16U	BusVotageLin;
	INT16S	BusVotageOfs;
	INT16U	HardwareRsv;
	INT16U	HardwareSum;
	/*PassWord*/
	INT16U	AppPassWord;
	INT16U	OemPassWord;
	INT16U	SysPassWord;
	INT16U	SysDevPassWord;
	/* Product */
	INT16U	UserType;		     /* 用户及车型 */
	/********************* Read only fix para *********************/
	/* CAN */
	INT16U	 StationAddr;			//CAN站点地址
	/* motor */
	INT16U	RotorTCoe;				//The thermal Coe for motor rotor  0.00256~0.00512 -- 256~512
	INT16U	CalibAngle;				/* Parameter: Raw angular offset between encoder index and phase a (Q0) */
	/* Speed */
	INT16U	RunMode;						/* 运行模式 */
	INT16U	SpdAccT;     			/*Acc acceleration  low filter time 0~1000 ms*/
	INT16U	SpdDecT;     			/*Dec acceleration low filter time 0~1000 ms*/
	INT16U	NotchFilt1W;			/* 第一陷波滤波器陷波频率(Hz) */
	INT16U	NotchFilt1Q;			/* 第一陷波滤波器品质因数(%) */
	INT16U	NotchFilt2W;			/* 第二陷波滤波器陷波频率(Hz) */
	INT16U	NotchFilt2Q;			/* 第二陷波滤波器品质因数(%) */
	/* Vehicle */
	INT16U	TimetoSpd1;
	INT16U	TimetoSpd2;
	INT16U	TimetoDist1;
	INT16U	TimetoDist2;
	INT16U	TimetoDist3;
	INT16U	DcRateVoltage;		  //电瓶电压等级,unit 0.1
	INT16U		BatAlarmRatio;		  //电瓶电量低报警点(%) 20% default
	INT16U		BatProtectRatio;		//电瓶电量低保护点(%) 15% default

	/*Hardware*/
	INT16U	DcMaxVoltage;				/* 最高电压，超过该电压系统不启动 ,unit 0.1V*/
	INT16U	DcBrkLimitVoltage;	/* 最高电压，超过该电压限制刹车力,unit 0.1V*/
	INT16U	DcCutVoltage;				/* 削减电压，低于该电压系统降耗运行，削减输出扭矩 ,unit 0.1V*/
	INT16U	DcMinVoltage;				/* 最低电压，低于该电压系统不启动，停止运行 ,unit 0.1V*/
	INT16U	DcBroVoltage;				/* 启动电压，低于该电压，系统复位，关闭一切输出 ,unit 0.1V*/
	INT16U	DcEspLowVoltage;		/* 急停电压，低于该电压，认为短路，关闭PWM上下桥臂，必须断电恢复 unit 0.1  */
	INT16U	CtlRate1HCurrent;		/* 1小时工作制电流  unit A */
	INT16U	CtlRate2MCurrent;		/* 2分钟工作制电流   unit A */
	INT16U  Out5VMaxVoltage;		//,unit 0.1V
	INT16U  Out5VMinVoltage;		//,unit 0.1V
	INT16U  Out12VMaxVoltage;		//,unit 0.1V
	INT16U  Out12VMinVoltage;		//,unit 0.1V
	
	INT16S	PowerCutTmp;	//功率板过载温度1，需降低功率板输出电流
	INT16S	PowerMaxTmp;
	INT16S	PowerMinTmp;

	/* Tune */
	INT16U	TuneSpdMax;				/* 参数整定 最大速度 */
	INT16U	TuneR;						/* 参数整定 最大圈数 */
	INT16U	RefRigid;					/* 参考刚性 */

	/* other */
	INT16U	ExtBrakeHoldTime;	/* 电机抱闸保持时间(10 ms) */
	INT16U	ErrorTrace[10];		/* 错误历史 */
	INT16U	TorqueOffset;			/* 转矩运行模式时的转矩偏置(0.01Nm) */
	INT16U	ObserverEnable;		/* 速度观测器使能 (BOOL) */
	INT16U	ObserverK;				/* 速度观测器系数：负载带宽是速度带宽的K%倍 */

/**********Ican readable******************************************************/
	/* Product */
	INT16U	ProductType;		  //产品类型 4845/4835/2425/2405/4805
	INT16U	ControllerType;	  /* 控制器类型  Move/lift/steer */
	INT16U SoftVersion;			 /* 低字节内核程序、高字节逻辑程序 */
	INT16U SoftVerYear;				/* release data year*/
	INT16U SoftVerMonthDay;			/* release data month+day*/
	INT16U HardVersion1;			/* 硬件版本号1*/
	INT16U HardVersion2;			/* 硬件版本号2*/
	INT16U FrameVersion;			/* 结构版本*/

	
	/* monitor state*/
	INT16S AcMotorSpeed;		//电机当前转速(rpm)
	INT16S AcMotorSpeedF;		//电机当前转速命令(rpm)
	INT16U AcPhaseCurrent;	//电机当前相电流
	INT16S MotorTmp;				//电机当前温度
	INT16S ControllerTmp;		//控制器当前温度
	INT16U VBusVoltage;			//当前母线电压
	INT16U KsiVBusVoltage;	//KSI电压
	INT16S MoveSpeed;				//行驶速度
	INT16U SteerAngle;			//转向角度
	
	/* monitor signal*/
	INT16U ThrottleCmdSpd;	//踏板指令（%）
	INT16U ThrottleWipVoltage;	//踏板滑动端电压值（v）
	INT16U ThrottleHighVoltage;	//踏板高端电压值（v）
	INT16U BrakePedalCmdSpd;	//brake 踏板指令（%）
	INT16U BrakePedalWipVoltage;	//brake 踏板滑动端电压值（v）
	INT16U BrakePedalHighVoltage;	//brake 踏板高端电压值（v）
	INT16U PotLowVoltage;					// 电位计低端电压
	INT16U AnologOut;				//模拟量输出（v）
	INT16U Analog1;				//模拟量1输入（v）
	INT16U Analog2;				//模拟量2输入（v）
	INT16U Analog3;				//模拟量3输入（v）
	INT16U Analog4;				//模拟量4输入（v）
	INT16U Switch;					//开关输入
	INT16U Driver;					//驱动输出
	INT16U MotorEncoder;		//电机编码器输入
	INT16U DirectionEncoder1;		//方向盘编码器输入1
	INT16U DirectionEncoder2;		//方向盘编码器输入2
	INT16U KernelState;					//控制环状态监测
	
	INT16U ErrCode;					//错误代码
	INT16U	NullPara;
} PARAMETER_STRUCT;



/* ACCESS */
#define			ACCESS_R	0x00	//参数可读
#define			ACCESS_RW	0x01	//参数可写
/* ACCESS_AUTH */
#define			NONE	0x00	//无权限
#define			OEM		0x01	//OEM用户权限
#define			APP		0x02	//应用工程师权限
#define			SYS		0x03	//系统工程师权限
/* EEPROM */
#define 		EEPROM_PARA_AREA_ADDR	0
#define 		EEPROM_BACK_AREA_ADDR	128
#define 		EEPROM_PVD_ADDR    250

//static 
extern const PRM_DEF_STRUCT* cPara_Table[];
//static 
extern const PRM_DEF_STRUCT* cMonitorPara_Table[];
extern PARAMETER_STRUCT gPara;

extern void InitPara(void);
extern INT16U ReadParaFromEeprom(INT16U Index);
INT16U SaveParaToEeprom(INT16U Index,INT16U data);
INT16U ReadParaValByIndex(INT16U Index);
INT16U EepromQualifiedRead(INT16U address, INT16U* pdata);
INT16U EepromQualifiedWrite(INT16U address, INT16U data);
INT16U SaveMonitorParaValByIndexToRam(INT16U Index, INT16U Val);
INT16U ReadMonitorParaValByIndex(INT16U PrmNo);
INT8U GetPrmNoFromMoveMonitorTab(INT16U Index);
INT16U GetPrmNoFromLiftMonitorTab(INT16U Index);
INT16U GetPrmNoFromSteerMonitorTab(INT16U Index);


#endif //#ifndef _PARA_H_
