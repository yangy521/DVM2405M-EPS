/*******************************************************************************
* Filename: HourCount.c                                                  	 	   *
*                                                                    		   *
* Description: 							            				 		   *
* Author:                                                                 	   *
* Date: 20190711														           *
* Revision:															 		   *
*																	 		   												*
*******************************************************************************/

#include "KSDsys.h"
#include "CommonRam.h"
#include	"PARA.h"
#include "HourCount.h"

#define PARANO_HOURPOWERON1_FLAG				PARA_NO_HOURPOWERON_FLAG1
#define PARANO_HOURPOWERON1_LOW				PARA_NO_HOURPOWERON_COUNTL1
#define PARANO_HOURPOWERON1_HIGH				PARA_NO_HOURPOWERON_COUNTH1
#define PARANO_HOURPOWERON2_FLAG				PARA_NO_HOURPOWERON_FLAG2
#define PARANO_HOURPOWERON2_LOW				PARA_NO_HOURPOWERON_COUNTL2
#define PARANO_HOURPOWERON2_HIGH				PARA_NO_HOURPOWERON_COUNTH2

#define PARANO_HOUR1_FLAG				PARA_NO_HOUR_FLAG1
#define PARANO_HOUR1_LOW				PARA_NO_HOUR_COUNTL1
#define PARANO_HOUR1_HIGH				PARA_NO_HOUR_COUNTH1
#define PARANO_HOUR2_FLAG				PARA_NO_HOUR_FLAG2
#define PARANO_HOUR2_LOW				PARA_NO_HOUR_COUNTL2
#define PARANO_HOUR2_HIGH				PARA_NO_HOUR_COUNTH2


// 从Eeprom读取配置信息
void HourCountRead(void)
{
	INT16U dataL, dataH;
	INT16U	HourFlag1, HourFlag2;
	INT32U	Hour1, Hour2;
	
	// 小时计
	//No1
	if (EepromQualifiedRead(PARANO_HOUR1_FLAG, &HourFlag1) != 0)
		HourFlag1 = BATTERY_HOUR_INVALID;
	if (HourFlag1 == BATTERY_HOUR_VALID)
	{
		if ((EepromQualifiedRead(PARANO_HOUR1_LOW, &dataL) == 0)
			&&(EepromQualifiedRead(PARANO_HOUR1_HIGH, &dataH) == 0))
			Hour1 = dataL + ((INT32U)dataH << 16);
		else
			Hour1 = 0;
	}
	else
	{
		Hour1 = 0;
	}
	//No2
	if (EepromQualifiedRead(PARANO_HOUR2_FLAG, &HourFlag2) != 0)
		HourFlag2 = BATTERY_HOUR_INVALID;
	if (HourFlag2 == BATTERY_HOUR_VALID)
	{
		if ((EepromQualifiedRead(PARANO_HOUR2_LOW, &dataL) == 0)
			&&(EepromQualifiedRead(PARANO_HOUR2_HIGH, &dataH) == 0))
			Hour2 = dataL + ((INT32U)dataH << 16);
		else
			Hour2 = 0;
	}
	else
	{
		Hour2 = 0;
	}
	//Adopt larger Hour
	if (Hour1 > Hour2)
	{
		gPLCCtl.HourCnt = Hour1;
	}
	else
	{
		gPLCCtl.HourCnt = Hour2;
	}
	gPLCCtl.HourCntNew = gPLCCtl.HourCnt;

	// 上电小时计
	//No1
	if (EepromQualifiedRead(PARANO_HOURPOWERON1_FLAG, &HourFlag1) != 0)
		HourFlag1 = BATTERY_HOUR_INVALID;
	if (HourFlag1 == BATTERY_HOUR_VALID)
	{
		if ((EepromQualifiedRead(PARANO_HOURPOWERON1_LOW, &dataL) == 0)
			&&(EepromQualifiedRead(PARANO_HOURPOWERON1_HIGH, &dataH) == 0))
			Hour1 = dataL + ((INT32U)dataH << 16);
		else
			Hour1 = 0;
	}
	else
	{
		Hour1 = 0;
	}
	//No2
	if (EepromQualifiedRead(PARANO_HOURPOWERON2_FLAG, &HourFlag2) != 0)
		HourFlag2 = BATTERY_HOUR_INVALID;
	if (HourFlag2 == BATTERY_HOUR_VALID)
	{
		if ((EepromQualifiedRead(PARANO_HOURPOWERON2_LOW, &dataL) == 0)
			&&(EepromQualifiedRead(PARANO_HOURPOWERON2_HIGH, &dataH) == 0))
			Hour2 = dataL + ((INT32U)dataH << 16);
		else
			Hour2 = 0;
	}
	else
	{
		Hour2 = 0;
	}
	//Adopt larger Hour
	if (Hour1 > Hour2)
	{
		gPLCCtl.HourCntPowerOn = Hour1;
	}
	else
	{
		gPLCCtl.HourCntPowerOn = Hour2;
	}
	gPLCCtl.HourCntPowerOnNew = gPLCCtl.HourCntPowerOn;
	gPLCCtl.HourCount6min = 0;
}
// 向I2C写入配置信息
void HourCountWrite(INT32S HourType)
{
	INT16U dataL, dataH;
	INT16U	HourFlag1, HourFlag2;
	INT32U	Hour1, Hour2, HourCnt;
	INT16U AdrHourFlag,AdrDataL, AdrDataH;
	if (HourType == HOUR_TYPE_NORMAL)
	{
		AdrHourFlag = PARANO_HOUR1_FLAG;
		AdrDataL = PARANO_HOUR1_LOW;
		AdrDataH = PARANO_HOUR1_HIGH;
		HourCnt = gPLCCtl.HourCnt;
	}
	else if (HourType == HOUR_TYPE_POWENON)
	{
		AdrHourFlag = PARANO_HOURPOWERON1_FLAG;
		AdrDataL = PARANO_HOURPOWERON1_LOW;
		AdrDataH = PARANO_HOURPOWERON1_HIGH;
		HourCnt = gPLCCtl.HourCntPowerOn;
	}
	else
	{
		AdrHourFlag = PARANO_HOUR1_FLAG;
		AdrDataL = PARANO_HOUR1_LOW;
		AdrDataH = PARANO_HOUR1_HIGH;
		HourCnt = gPLCCtl.HourCnt;
	}
	// 小时计
	//No1
	if (EepromQualifiedRead(AdrHourFlag, &HourFlag1) != 0)
		HourFlag1 = BATTERY_HOUR_INVALID;
	if (HourFlag1 == BATTERY_HOUR_VALID)
	{
		if ((EepromQualifiedRead(AdrDataL, &dataL) == 0)
			&&(EepromQualifiedRead(AdrDataH, &dataH) == 0))
			Hour1 = dataL + ((INT32U)dataH << 16);
		else
			Hour1 = 0;
	}
	else
	{
		Hour1 = 0;
	}
	if ((HourFlag1 != BATTERY_HOUR_VALID)
		||(HourCnt != Hour1))
	{
		Hour1 = HourCnt;
		if (EepromQualifiedWrite(AdrHourFlag, BATTERY_HOUR_INVALID) == 0)
		{
			if ((EepromQualifiedWrite(AdrDataL, (Hour1 & 0xFFFF)) == 0)
				&&(EepromQualifiedWrite(AdrDataH, ((Hour1 >> 16) & 0xFFFF)) == 0))
			{
				EepromQualifiedWrite(AdrHourFlag, BATTERY_HOUR_VALID);
			}
		}
	}
	//No2
	if (HourType == HOUR_TYPE_NORMAL)
	{
		AdrHourFlag = PARANO_HOUR2_FLAG;
		AdrDataL = PARANO_HOUR2_LOW;
		AdrDataH = PARANO_HOUR2_HIGH;
		HourCnt = gPLCCtl.HourCnt;
	}
	else if (HourType == HOUR_TYPE_POWENON)
	{
		AdrHourFlag = PARANO_HOURPOWERON2_FLAG;
		AdrDataL = PARANO_HOURPOWERON2_LOW;
		AdrDataH = PARANO_HOURPOWERON2_HIGH;
		HourCnt = gPLCCtl.HourCntPowerOn;
	}
	else
	{
		AdrHourFlag = PARANO_HOUR2_FLAG;
		AdrDataL = PARANO_HOUR2_LOW;
		AdrDataH = PARANO_HOUR2_HIGH;
		HourCnt = gPLCCtl.HourCnt;
	}
	if (EepromQualifiedRead(AdrHourFlag, &HourFlag2) != 0)
		HourFlag2 = BATTERY_HOUR_INVALID;
	if (HourFlag2 == BATTERY_HOUR_VALID)
	{
		if ((EepromQualifiedRead(AdrDataL, &dataL) == 0)
			&&(EepromQualifiedRead(AdrDataH, &dataH) == 0))
			Hour2 = dataL + ((INT32U)dataH << 16);
		else
			Hour2 = 0;
	}
	else
	{
		Hour2 = 0;
	}
	if ((HourFlag2 != BATTERY_HOUR_VALID)
		||(HourCnt != Hour2))
	{
		Hour2 = HourCnt;
		if (EepromQualifiedWrite(AdrHourFlag, BATTERY_HOUR_INVALID) == 0)
		{
			if ((EepromQualifiedWrite(AdrDataL, (Hour2 & 0xFFFF)) == 0)
				&&(EepromQualifiedWrite(AdrDataH, ((Hour2 >> 16) & 0xFFFF)) == 0))
			{
				EepromQualifiedWrite(AdrHourFlag, BATTERY_HOUR_VALID);
			}
		}
	}
}
