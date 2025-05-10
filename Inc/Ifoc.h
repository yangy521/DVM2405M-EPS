/*******************************************************************************
* Filename: Ifoc.h 	                                    	     		   *
*                                                                              *
* Description: The header file of Kernel.c.							           *
* Author:                                                                      *
* Date: 															           *
* Revision:															           *
*																	           *
*******************************************************************************/
#ifndef _IFOC_H_
#define _IFOC_H_

#include	"KSDsys.h"

/* Voltage limit pid regulator */
typedef struct VLIMIT_PID
{
	_iq  	Out;			/* Output: PID output */
	_iq  	Ref;			/* Input: Reference input */
	_iq  	Fdb;			/* Input: Feedback input */
	_iq  	Err;			/* Variable: Error */
	_iq  	Kp;				/* Parameter: Proportional gain */
	_iq  	Ki;				/* Parameter: Integral gain */
	_iq  	Kc;				/* Parameter: Integral correction gain */
	_iq  	Up;				/* Variable: Proportional output */
	_iq		KpCoe;		/* Kp coe for vary kp, eg during weak flux*/
	INT64S	Ui;				/* Variable: 64 bit Integral output */
	_iq  	OutMax;			/* Parameter: Maximum output */
	_iq  	OutMin;			/* Parameter: Minimum output */
	_iq  	OutPreSat;		/* Variable: Pre-saturated output */
	_iq  	SatErr;			/* Variable: Saturated difference */
	void 	(*Init)(struct VLIMIT_PID *);
	void 	(*Calc)(struct VLIMIT_PID *);
} VLIMIT_PID;
/* Current limit pid regulator */
typedef struct CLIMIT_PID
{
	_iq  	Out;			/* Output: PID output */
	_iq  	Ref;			/* Input: Reference input */
	_iq  	Fdb;			/* Input: Feedback input */
	_iq  	Err;			/* Variable: Error */
	_iq  	Kp;				/* Parameter: Proportional gain */
	_iq  	Ki;				/* Parameter: Integral gain */
	_iq  	Kc;				/* Parameter: Integral correction gain */
	_iq  	Up;				/* Variable: Proportional output */
	_iq		KpCoe;		/* Kp coe for vary kp, eg during weak flux*/
	INT64S	Ui;				/* Variable: 64 bit Integral output */
	_iq  	OutMax;			/* Parameter: Maximum output */
	_iq  	OutMin;			/* Parameter: Minimum output */
	_iq  	OutPreSat;		/* Variable: Pre-saturated output */
	_iq  	SatErr;			/* Variable: Saturated difference */
	void 	(*Init)(struct CLIMIT_PID *);
	void 	(*Calc)(struct CLIMIT_PID *);
} CLIMIT_PID;

//used by speed loop
//4Hz~300Hz, increase step (STD_FRQ/16)=0.266666667 Hz
#define HFLUX_START_FRQ  _IQ(4.0/STD_FRQ)
#define HFLUX_END_FRQ  _IQ(300.0/STD_FRQ)
#define IQSUM_SHIFT  13   //1s
#define BASEFLUX_MIN_RATIO  (0.50)   //50%

typedef struct SPEED_WEAK_FLUX
{
	VLIMIT_PID PID;
	INT64S		IqSum;
	INT64S 		SlipFreq;   //
	_iq				IqEverage;
	INT32U		State;  		//
	
	//output
	_iq				FluxRef;		//
	_iq				IqCmdOut;
	//input
	_iq				IqCmdIn;
	_iq				FluxRefIn;
	_iq				VoltageBus;			//dc bus voltage
	_iq				BaseFlux;				// Base flux current,vary under different state
	//para
	_iq				K_RAD_HZ;

	void 			(*Init)(struct SPEED_WEAK_FLUX *);
	void 			(*Calc)(struct SPEED_WEAK_FLUX *);
} SPEED_WEAK_FLUX;

extern const _iq  hflux_reference[1111]; 
extern const _iq  htorque_reference[1111];

/******************************************************************************
*º¯Êý¶¨Òå
******************************************************************************/
extern	void VlimitPidInit(struct VLIMIT_PID *p);
extern	void VlimitPidCalc(struct VLIMIT_PID *v);
extern	void ClimitPidInit(struct CLIMIT_PID *p);
extern	void ClimitPidCalc(struct CLIMIT_PID *v);

#endif //#ifndef _IFOC_H_
