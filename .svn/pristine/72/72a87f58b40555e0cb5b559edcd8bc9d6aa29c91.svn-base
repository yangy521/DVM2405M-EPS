/*******************************************************************************
* Filename: Position.c                                             	 		   *
*                                                                    		   *
* Description:											   			 		   *
* Author: kff                                                                  *
* Date: 100623														           *
* Revision:															 		   *
*																	 		   *
*******************************************************************************/

#include	"Position.h"
#include	"CommonRam.h"
#include	"Kernel.h"
#include	"Tune.h"
#include  "ServoPara.h"

POSITION_LOOP	gPositionLoop;

/*******************************************************************************
* Name: PosLoop2CmdUnit
* Description: Only run in ISR.
* Input: 
* Output: 
*
* Author:
* Date:
* Revision:
*******************************************************************************/
INT32S	PosLoop2CmdUnit(INT32S Value)
{
	INT32S	ret;
	INT64S	t64S;

	t64S = (INT64S)Value * (INT32S)gCRam.SvPa.PosGearDen;
	t64S += (INT64S)gPositionLoop.GearRemainder;

	/* +-0.5 for the stable output of ret */
	if(t64S > 0)
	{
		t64S += ((INT64S)gCRam.SvPa.PosGearNum >> 1);
	}
	else
	{
		t64S -= ((INT64S)gCRam.SvPa.PosGearNum >> 1);
	}

	ret = (INT32S)(t64S / (INT32S)gCRam.SvPa.PosGearNum);

	return ret;
}

/*******************************************************************************
* Name: CmdUnit2PosLoop
* Description: Only run in ISR.
* Input: 
* Output: 
*
* Author:
* Date:
* Revision:
*******************************************************************************/
INT32S	CmdUnit2PosLoop(INT32S Value)
{
	INT32S	ret;
	INT64S	t64S,i64s;

	t64S = (INT64S)Value * (INT32S)gCRam.SvPa.PosGearNum + (INT64S)gPositionLoop.GearRemainder;

	if(t64S > 0)
	{
		i64s = t64S + ((INT64S)gCRam.SvPa.PosGearDen >> 1);
	}
	else
	{
		i64s = t64S - ((INT64S)gCRam.SvPa.PosGearDen >> 1);
	}
	ret = (INT32S)(i64s / (INT32S)gCRam.SvPa.PosGearDen);

	gPositionLoop.GearRemainder = 
		(INT32S)(t64S - (INT64S)ret * (INT32S)gCRam.SvPa.PosGearDen);

	return ret;
}
/*******************************************************************************
* Name: Encoder2CmdUnit
* Description: Only run in ISR.
* Input: 
* Output: 
*
* Author:
* Date:
* Revision:
*******************************************************************************/
INT32S	Encoder2CmdUnit(INT32S Value)
{
	INT32S gear, ret;

	/* ????????1/128?128??,??gear???? */
	gear = _IQdiv((INT32S)gCRam.SvPa.PosGearDen, (INT32S)gCRam.SvPa.PosGearNum);
	
	ret = _IQrmpy(Value, gear);

	return ret;
}


/*******************************************************************************
* Name: Cmd2EncoderUnit
* Description: Only run in ISR.
* Input: 
* Output: 
*
* Author:
* Date:
* Revision:
*******************************************************************************/
INT32S	Cmd2EncoderUnit(INT32S Value)
{
	INT32S gear, ret;

	/* ????????1/128?128??,??gear???? */
	gear = _IQdiv((INT32S)gCRam.SvPa.PosGearNum, (INT32S)gCRam.SvPa.PosGearDen);
	
	ret = _IQrmpy(Value, gear);

	return ret;
}

/*******************************************************************************
* Name: PositionPidInit
* Description: position loop PID initialization
* Input: 
* Output: 
*
* Author:
* Date: 
* Revision:
*******************************************************************************/
void PositionPidInit(POSITION_PID *p)
{
	p->Out = 0;
	p->Ref = 0;
	p->Fdb = 0;
	p->Err = 0;
	p->Kp = 0;
	p->Up = 0;
	p->OutMax = +_IQ(10.0);
	p->OutMin = -_IQ(10.0);
	p->State = 0;
}

/*******************************************************************************
* Name: PositionPidCalc
* Description: position loop PID calculation
* Input: 
* Output: 
*
* Author:
* Date: 
* Revision:
*******************************************************************************/
void PositionPidCalc(POSITION_PID *p)
{
	/* Compute the error */
	p->Err = (p->Ref - p->Fdb);

	/* Compute the proportional item */
	p->Up = (INT64S)p->Kp * p->Err;

	/* set output */
	p->State &= ~(POS_POSITIVE_SATURATION | POS_NEGTIVE_SATURATION);
	if (p->Up > p->OutMax)
	{
		p->Out = p->OutMax;
		p->State |= POS_POSITIVE_SATURATION;
	}
	else if (p->Up < p->OutMin)
	{
		p->Out = p->OutMin;
		p->State |= POS_NEGTIVE_SATURATION;
	}
	else
	{
		p->Out = p->Up;
	}	
}

/*******************************************************************************
* Name: PositionLoopInit
* Description: position loop initialization
* Input: 
* Output: 
*
* Author:
* Date: 
* Revision:
*******************************************************************************/
void PositionLoopInit(POSITION_LOOP *p)
{
	/* Initialize PID */
	p->PID.Init = PositionPidInit;
	p->PID.Calc = PositionPidCalc;
	p->PID.Init(&p->PID);

	/* Initializa PosRef and PosFdb */
	p->PosCmd = 0;
	p->PosCmdOld = 0;

	p->GearRemainder = 0;
	p->PosRefG = 0;
	p->PosRef = 0;
	p->PosRefFiltK = 0;
	p->PosFdb = 0;
	p->PosFdbOld = p->PosFdb;
	p->SpeedCmd = 0;
	p->PosIncFiltOut = 0;
	p->PosIncFiltSum = 0;
	p->PosRefFiltSumRem = 0;

	/* Initialize Feedforward Parameter */
	p->SpdFdfwdLPF.w = 0;
	p->SpdFdfwdLPF.Design = Lpf1Design;
	p->SpdFdfwdLPF.Calc = Lpf1Calc;
	p->SpdFdfwdLPF.a0 = 0;
	p->SpdFdfwdLPF.a1 = 0;
	p->SpdFdfwdLPF.a2 = 0;
	p->SpdFdfwdLPF.b1 = 0;
	p->SpdFdfwdLPF.b2 = 0;
	p->SpdFdfwdLPF.x0 = 0;
	p->SpdFdfwdLPF.x1 = 0;
	p->SpdFdfwdLPF.x2 = 0;
	p->SpdFdfwdLPF.y0 = 0;
	p->SpdFdfwdLPF.y1 = 0;
	p->SpdFdfwdLPF.y2 = 0;
	p->SpdFdfwdK = 0;
	p->SpdFdfwd = 0;
	p->CoePls2Hz = _IQ(1.0) / gCRam.SvPa.MotorPara.EncoderLineNumM4;
}

/*******************************************************************************
* Name: PositionLoopCalc
* Description: position loop calculation
* Input: 
* Output: 
*
* Author:
* Date: 
* Revision:
*******************************************************************************/
//#define DEBUG_POSITION
void PositionLoopCalc(POSITION_LOOP *p)
{
}
/*******************************************************************************
* Name: PositionLoopReset
* Description: position loop reset
* Input: 
* Output: 
*
* Author:
* Date: 
* Revision:
*******************************************************************************/
void PositionLoopReset(POSITION_LOOP *p)
{
	p->PosRefG= gCRam.PosFdb;
	p->PosRef = gCRam.PosFdb;
	p->PosFdb = gCRam.PosFdb;
	p->PosFdbOld = p->PosFdb;
	p->PosCmd = gCRam.PosCmd;
	p->PosCmdOld = gCRam.PosCmd;
	p->GearRemainder = 0;
	p->SpeedCmd = 0;
	p->PosRefFiltSumRem = 0;

	p->SpdFdfwdLPF.x0 = 0;
	p->SpdFdfwdLPF.x1 = 0;
	p->SpdFdfwdLPF.x2 = 0;
	p->SpdFdfwdLPF.y0 = 0;
	p->SpdFdfwdLPF.y1 = 0;
	p->SpdFdfwdLPF.y2 = 0;

	p->PID.State = 0;
}


