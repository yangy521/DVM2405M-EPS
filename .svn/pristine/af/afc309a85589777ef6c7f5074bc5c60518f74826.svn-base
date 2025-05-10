/*******************************************************************************
* Filename: FDB.h 	                                    	     		   *
*                                                                              *
* Description: The header file of FDB.c.							           *
* Author:                                                                      *
* Date: 															           *
* Revision:															           *
*																	           *
*******************************************************************************/

#include	"KSDsys.h"
#include "stm32g473xx.h"

/******************************************************************************
*数据类型定义
******************************************************************************/
/* encoder */
typedef struct ENCODER 
{
	INT16S 	ElecTheta;		/* Output: Motor Electrical angle (Q15) */
	INT16S 	ElecThetaM;		/* Output: Motor Electrical angle (Q15) */
	INT16S 	ElecThetaT;		/* Output: Motor Electrical angle (Q15) */
	INT16S	SyncFlag;		/* Variable: Z flag */
	INT32S  Angle;			/* Mec angle Q0, pulse unit 0 ~ stdinc-1/rotation*/
	INT32S 	CalibAngle; 	/* Parameter: Raw angular offset between 
								encoder index and phase a (Q0) */
	INT16U 	PolePairs;		/* Parameter: Number of pole pairs (Q0) */
	INT16S 	ErrorTimes;		/* Output: Error times */
	INT32S	PosAbs;			/* Q0, absolute */
	INT32S	PosAbsRaw;		/* Q0, 原始绝对位置 */
	INT32S	PosAbsOffset;	/* Q0, 绝对位置偏移 */
	INT32S	PosInc;			/* Q0, inc */
	INT16S	PosOld;			/* Q0, old, 增量编码器记录上次位置 */
	INT16S	CntOld;			/* Q0, old, 增量编码器记录上次位置 */

	//T法测速
	INT16S  TCntOld;
	INT32S	TimeAbs;
	INT32S	TimeWait;
	INT32S	TimeCapA;
	INT32S	TimeCapB;
	INT32S	WidthMin;
	INT32S  WidthMax;
	INT32S	tWidth;
	
	//No encoder check
	INT32S TimeCount;
	INT32S IncCount;
	
	void 	(*Init)(struct ENCODER *);		/*Pointer to the init function*/
	void 	(*Calc)(struct ENCODER *);		/*Pointer to the calc function*/
//wwq temp	void 	(*Calc_Pre)(struct ENCODER *);	/*Pointer to the calc_pre function*/
} ENCODER;

/* current sample */
#define NO_CUR     0
#define U_CUR_P     1
#define V_CUR_P     2
#define W_CUR_P     3
#define U_CUR_N     4
#define V_CUR_N     5
#define W_CUR_N     6
/* Motor phase bit def */
#define PWMA_U     		0x4
#define PWMB_V     		0x2
#define PWMC_W     		0x1

typedef struct ONE_SHUNT_BUF
{
	INT16S MapBuf[1][2];
	INT16S WrIndex;
}ONE_SHUNT_BUF;

typedef struct CURRENT_SAMPLE
{
	ONE_SHUNT_BUF SampleMapBuf;   //
	INT16S  U;				/* Q11 */
	INT16S  W;				/* Q11 */
	INT16S	KsiVBus;
	INT16S	VBus;			/* Q12 */
	INT16S	V5out;
	INT16S  V12_5OvCurrent;
	INT16S  V5out2;
	INT16S  V12_5OvCurrent2;	
	INT16S	V12out;
	INT16S	RelayOut;
	INT16S	PowTmpHigh;
	INT16S	PowTmpLow;
	INT16S	MotorTmp;		/* Q??*/
	INT16S	CmdVal1;	//THROTLE WIPER1
	INT16S	CmdVal2;	//THROTLE WIPER2  
	INT16S	Swi7;	//1222  
	INT16S	Swi8;	//1222
	INT16S	VrefInt;
	
	INT16S	URaw;				/* A1 */
	INT16S	WRaw;				/* B0 */
	INT16S	Adc1Data;     //ad1 data
	INT16S	Adc2Data;     //ad2 data
	INT16S	Adc3Data;     //ad3 data
	INT16S	KsiVBusRaw;			/* A0 */
	INT16S	VBusRaw;			/* B5 */
	INT16S	V5outRaw;			/* A6 */
	INT16S  V12_5OvCurrentRaw;
	INT16S  V5outRaw2;
	INT16S  V12_5OvCurrentRaw2;
	INT16S	V12outRaw;
	INT16S	RelayOutRaw;	/* A3 */
	INT16S	PowTmpHighRaw;		/* A4 */
	INT16S	PowTmpLowRaw;		/* A2 */
	INT16S	MotorTmpRaw;		/* B6 */
	INT16S	CmdVal1Raw;	//THROTLE WIPER
	INT16S	CmdVal2Raw;	//1222
	INT16S	Swi7Raw;	//1222
	INT16S	Swi8Raw;	//1222
	INT16S VrefIntRaw;
	
	INT32S  USum;				/* Q11 */
	INT32S	KsiVBusSum;
	INT32S	VBusSum;			/* Q12 */
	INT32S	V5outSum;
	INT32S  V12_5OvCurrentSum;
	INT32S  V5outSum2;
	INT32S  V12_5OvCurrentSum2;
	INT32S	RelayOutSum;
	INT32S	PowTmpHighSum;
	INT32S	PowTmpLowSum;
	INT32S	CmdVal1Sum;	//THROTLE WIPER
	INT32S	CmdVal2Sum;	//1222

	INT16S	UPhaseRaw;
	INT16S	VPhaseRaw;
	INT16S	WPhaseRaw;
	INT16S	UPhase;
	INT16S	VPhase;
	INT16S	WPhase;
	INT32S	UPhaseSum;
	INT32S	VPhaseSum;
	INT32S	WPhaseSum;
	
	INT16S	UZeroDrift;
	INT32S	UZeroDriftSum;
	INT16S	WZeroDrift;
	INT32S	VZeroDriftSum;
	INT32S	WZeroDriftSum;
	INT16S	VBusZeroDrift;
	INT32S	VBusZeroDriftSum;
	INT16S	KsiVBusZeroDrift;
	INT32S	KsiVBusZeroDriftSum;
	INT16S	VCmdZeroDrift;
	INT32S	VCmdZeroDriftSum;

	void 	(*Init)(struct CURRENT_SAMPLE *);	/*Pointer to the init function*/
	void 	(*Calc)(struct CURRENT_SAMPLE *);	/*Pointer to the calc function*/
	void 	(*Calc_ZeroDrift)(struct CURRENT_SAMPLE *);	
	void 	(*Filter)(struct CURRENT_SAMPLE *);
} CURRENT_SAMPLE;



/* variables for feedback */
extern		ENCODER			gEncoder;
extern		CURRENT_SAMPLE	gCurrentSample;
extern const INT16U HALLABC_TO_UVW_VOLTAGE[8];

/******************************************************************************
*函数定义
******************************************************************************/

extern void InitFeedbackDevice(void);
extern void FeedbackProcess(void);
extern void ThreeRshuntCurrentSampleMapSet(TIM_TypeDef* pTimerPwm, TIM_TypeDef* pTimerAd,ONE_SHUNT_BUF* pSampleMapBuf);
