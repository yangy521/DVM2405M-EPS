/*******************************************************************************
* Filename: ObjDict.c	                                             	 		   *
*                                                                    		   *
* Description:											   			 		   *
* Author:                                                           		   *
* Date:     														 		   *
* Revision:															 		   *
*																	 		   *
*******************************************************************************/
#include "ObjDict.h"
#include "mco.h"

typedef  const PARA_OBJ_STRUCT PARA_STRUCT; 

/* index 0x1000 :   Device Type. */
static PARA_STRUCT ParaIdx_1000[]=
	{
		{1,	0x1000,	0,	ODUS32,	ODRD,	ODNMP,	(void*)NULL,	0,	0,	0},
	};
/* index 0x1018 :   Identity. */
static PARA_STRUCT ParaIdx_1018[]=
	{	
		{2,	0x1018,	0,	ODUS16,	ODRD,	ODNMP,	(void*)NULL,	0,	0,	0},
		{3,	0x1018,	1,	ODUS16,	ODRD,	ODNMP,	(void*)NULL,	0,	0,	0},
	};
	
static PARA_STRUCT ParaIdx_1400[]=
	{
		{4,	0x1400,	0,	ODUS16,	ODRD,	ODNMP,	(void*)NULL,	0,	0,	0},
	};
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	