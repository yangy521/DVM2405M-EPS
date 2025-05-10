/*******************************************************************************
* Filename: iCANlogic.c	                                             	 		   *
* Description:											   			 		   *
* Author:                                                           		   *
* Date:     														 		   *
* Revision:															 		   *
*******************************************************************************/

#include "iCANLogic.h"
#include "iCAN.h"
#include "iCANPlc.h"
#include "PARA.h"
#include "CommonRam.h"
#include  "Device.h"

//检测网络组成
#if IS_LOGIC_MASTER(LOGIC_TYPE)
void NetOnlineCheck(void )
{
	unsigned char i;
	
	for (i = 0; i < (sizeof(icanMaster.ucIdtoSlvArrayIndex)/sizeof(icanMaster.ucIdtoSlvArrayIndex[0])); i++)
	{
		icanMaster.ucIdtoSlvArrayIndex[i] = 0;
	}
	//检测网络组成
  icanMaster.ucNetCfg=0x01;    //Master is always act
	for(i=1;i<icanMaster.ucSlvArrLength;i++)
	{
		if(icanMaster.pICANSlvArray[i].bIsConnect)
		{
			icanMaster.ucNetCfg |= (1 << icanMaster.pICANSlvArray[i].ucMacID);
			if (icanMaster.pICANSlvArray[i].ucMacID < (sizeof(icanMaster.ucIdtoSlvArrayIndex)/sizeof(icanMaster.ucIdtoSlvArrayIndex[0])))
				icanMaster.ucIdtoSlvArrayIndex[icanMaster.pICANSlvArray[i].ucMacID] = i;
		}			
	}
}
#endif //#if IS_LOGIC_MASTER(LOGIC_TYPE)

//获取监控和配置处理类型
void GetSysProcedure(unsigned char  *pPcProcType, unsigned char  *pHmiProcType)
{
#if IS_LOGIC_MASTER(LOGIC_TYPE)
	unsigned char PCStateSetting, HMIStateSetting;
	NetOnlineCheck();
	
	//Default idle mode.
	*pPcProcType = PC_IDLE_MODE_STATESETTING;
	*pHmiProcType = HMI_IDLE_MODE_STATESETTING;
	if ((icanMaster.ucNetCfg & (1<<Prd_PC)) != 0)
	{ // PC act
		gPLCCtl.icanPc.ucNetCfg = icanMaster.ucNetCfg;
		PCStateSetting = icanMaster.pICANSlvArray[icanMaster.ucIdtoSlvArrayIndex[Prd_PC]].ucSource0x00;
		*pPcProcType = MODE_STATESETTING(PCStateSetting);
		
		if ((icanMaster.ucNetCfg & (1<<Prd_HMI)) != 0)
		{
			gPLCCtl.icanHMI.ucNetCfg = icanMaster.ucNetCfg;
			HMIStateSetting = icanMaster.pICANSlvArray[icanMaster.ucIdtoSlvArrayIndex[Prd_HMI]].ucSource0x00;
			if (((PRDID_STATESETTING(HMIStateSetting) != Prd_Move) && (PRDID_STATESETTING(PCStateSetting) == PRDID_STATESETTING(HMIStateSetting)))  //PC have priority 
				||(PRDID_STATESETTING(PCStateSetting) == Prd_HMI))
				*pHmiProcType = PC_IDLE_MODE_STATESETTING;
			else
				*pHmiProcType = MODE_STATESETTING(HMIStateSetting);
		}
		else //No HMI
		{}
	}
	else //No PC
	{
		if ((icanMaster.ucNetCfg & (1<<Prd_HMI)) != 0)
		{
			gPLCCtl.icanHMI.ucNetCfg = icanMaster.ucNetCfg;
			HMIStateSetting = gPLCCtl.icanHMI.ucStateSettingS;
			*pHmiProcType = MODE_STATESETTING(HMIStateSetting);
		}
	}
#endif //#if IS_LOGIC_MASTER(LOGIC_TYPE)

#if IS_LOGIC_SLAVE(LOGIC_TYPE)
	//PC——主站-从站；PCWorkSetting
	//HMI——主站-从站；HMIWorkSetting
	*pPcProcType =	MODE_STATESETTING(icanSlave.ucSource0x20); //PrdEcho
	*pHmiProcType = MODE_STATESETTING(icanSlave.ucSource0x20); //PrdEcho
#endif //#if IS_LOGIC_SLAVE(LOGIC_TYPE)
}



 //PC监控模式
#if IS_LOGIC_MASTER(LOGIC_TYPE)
void PCMonitor_Master(void)
{
	unsigned char Index1,Index2,Index3,Index4,Index5,Index6;
	unsigned short  Index1Val,Index2Val,Index3Val,Index4Val,Index5Val,Index6Val;
	unsigned char DstId,DstStateSetting;
	tICANSlave *pICANSlave_PC;
	tICANSlave *pICANSlave_Dst;
	
	if ((icanMaster.ucNetCfg & (1<<Prd_PC)) != 0)
	{
		pICANSlave_PC = &icanMaster.pICANSlvArray[icanMaster.ucIdtoSlvArrayIndex[Prd_PC]];
		DstId = PRDID_STATESETTING(pICANSlave_PC->ucSource0x00);
		if ((icanMaster.ucNetCfg & (1<<DstId)) != 0)
		{
			pICANSlave_Dst = &icanMaster.pICANSlvArray[icanMaster.ucIdtoSlvArrayIndex[DstId]];

			Index1=pICANSlave_PC->ucSource0x0E; 
			Index2=pICANSlave_PC->ucSource0x11; 
			Index3=pICANSlave_PC->ucSource0x14; 
			Index4=pICANSlave_PC->ucSource0x17; 
			Index5=pICANSlave_PC->ucSource0x1A; 
			Index6=pICANSlave_PC->ucSource0x1D; 
			if(DstId == Prd_Move)
			{
				//监控主站，直接返回参数列表相应内容
				DstStateSetting = pICANSlave_PC->ucSource0x00;
				Index1Val=ReadMonitorParaValByIndex(Index1);	//			
				Index2Val=ReadMonitorParaValByIndex(Index2);	//
				Index3Val=ReadMonitorParaValByIndex(Index3);	//
				Index4Val=ReadMonitorParaValByIndex(Index4);	//
				Index5Val=ReadMonitorParaValByIndex(Index5);	//
				Index6Val=ReadMonitorParaValByIndex(Index6);	//							
			}
			else //从站：监控对象ucPrdID
			{
				//将index信息传递给目标从站镜像
				pICANSlave_Dst->ucSource0x20 = pICANSlave_PC->ucSource0x00;						
				pICANSlave_Dst->ucSource0x2E=Index1;		
				pICANSlave_Dst->ucSource0x31=Index2;
				pICANSlave_Dst->ucSource0x34=Index3;
				pICANSlave_Dst->ucSource0x37=Index4;
				pICANSlave_Dst->ucSource0x3A=Index5;
				pICANSlave_Dst->ucSource0x3D=Index6;
				
				//从从站镜像读取当前的index和value(实际数据会有一个轮训周期的延迟)
				DstStateSetting = pICANSlave_Dst->ucSource0x00;
				Index1=pICANSlave_Dst->ucSource0x0E;
				Index1Val=(pICANSlave_Dst->ucSource0x0F<<8)+pICANSlave_Dst->ucSource0x10;	//						
				Index2=pICANSlave_Dst->ucSource0x11;
				Index2Val=(pICANSlave_Dst->ucSource0x12<<8)+pICANSlave_Dst->ucSource0x13;	//
				Index3=pICANSlave_Dst->ucSource0x14;
				Index3Val=(pICANSlave_Dst->ucSource0x15<<8)+pICANSlave_Dst->ucSource0x16;	//						
				Index4=pICANSlave_Dst->ucSource0x17;
				Index4Val=(pICANSlave_Dst->ucSource0x18<<8)+pICANSlave_Dst->ucSource0x19;	//
				Index5=pICANSlave_Dst->ucSource0x1A;
				Index5Val=(pICANSlave_Dst->ucSource0x1B<<8)+pICANSlave_Dst->ucSource0x1C;	//							
				Index6=pICANSlave_Dst->ucSource0x1D;
				Index6Val=(pICANSlave_Dst->ucSource0x1E<<8)+pICANSlave_Dst->ucSource0x1F;	//				
			} 
		}
		else //No dst id
		{
			DstStateSetting = pICANSlave_PC->ucSource0x00;
			//Force PC to discard the data
			Index1 = 0;
			Index2 = 0;
			Index3 = 0;
			Index4 = 0;
			Index5 = 0;
			Index6 = 0;
		}
		//0x40
		pICANSlave_PC->ucSource0x20 = DstStateSetting;
		//0x81 
		//0x82
		pICANSlave_PC->ucSource0x2E=Index1;	//
		pICANSlave_PC->ucSource0x2F=Index1Val>>8;	//
		pICANSlave_PC->ucSource0x30=Index1Val;	//
		pICANSlave_PC->ucSource0x31=Index2;	//
		pICANSlave_PC->ucSource0x32=Index2Val>>8;	//
		pICANSlave_PC->ucSource0x33=Index2Val;	//
		pICANSlave_PC->ucSource0x34=Index3;
		//0x83
		pICANSlave_PC->ucSource0x35=Index3Val>>8;	//
		pICANSlave_PC->ucSource0x36=Index3Val;	//
		pICANSlave_PC->ucSource0x37=Index4;	//
		pICANSlave_PC->ucSource0x38=Index4Val>>8;	//
		pICANSlave_PC->ucSource0x39=Index4Val;	//
		pICANSlave_PC->ucSource0x3A=Index5;	//
		pICANSlave_PC->ucSource0x3B=Index5Val>>8;
		//0xC0
		pICANSlave_PC->ucSource0x3C=Index5Val;	//
		pICANSlave_PC->ucSource0x3D=Index6;	//
		pICANSlave_PC->ucSource0x3E=Index6Val>>8;	//
		pICANSlave_PC->ucSource0x3F=Index6Val; //				
	}
}
#endif //#if IS_LOGIC_MASTER(LOGIC_TYPE)

 //PC监控模式
#if IS_LOGIC_SLAVE(LOGIC_TYPE)
void PCMonitor_Slave(void)
{
	unsigned char Index1,Index2,Index3,Index4,Index5,Index6;
	unsigned short  Index1Val,Index2Val,Index3Val,Index4Val,Index5Val,Index6Val;
	unsigned char DstId;
	
	DstId=PRDID_STATESETTING(icanSlave.ucSource0x20);
		
	if(DstId == icanSlave.ucMacID)
	{
		icanSlave.ucSource0x00=icanSlave.ucSource0x20;

		//获取从站相应参数列表值
		Index1=icanSlave.ucSource0x2E;
		Index1Val=ReadMonitorParaValByIndex(Index1);	//			
		icanSlave.ucSource0x0E=Index1;	//
		icanSlave.ucSource0x0F=Index1Val>>8;	//
		icanSlave.ucSource0x10=Index1Val;	//

		Index2=icanSlave.ucSource0x31;
		Index2Val=ReadMonitorParaValByIndex(Index2);	//			
		icanSlave.ucSource0x11=Index2;	//
		icanSlave.ucSource0x12=Index2Val>>8;	//
		icanSlave.ucSource0x13=Index2Val;	//

		Index3=icanSlave.ucSource0x34;
		Index3Val=ReadMonitorParaValByIndex(Index3);	//			
		icanSlave.ucSource0x14=Index3;
		icanSlave.ucSource0x15=Index3Val>>8;	//
		icanSlave.ucSource0x16=Index3Val;	//

		Index4=icanSlave.ucSource0x37;
		Index4Val=ReadMonitorParaValByIndex(Index4);	//			
		icanSlave.ucSource0x17=Index4;	//
		icanSlave.ucSource0x18=Index4Val>>8;	//
		icanSlave.ucSource0x19=Index4Val;	//
		
		Index5=icanSlave.ucSource0x3A;
		Index5Val=ReadMonitorParaValByIndex(Index5);	//			
		icanSlave.ucSource0x1A=Index5;	//
		icanSlave.ucSource0x1B=Index5Val>>8;
		icanSlave.ucSource0x1C=Index5Val;	//
		
		Index6=icanSlave.ucSource0x3D;
		Index6Val=ReadMonitorParaValByIndex(Index6);	//			
		icanSlave.ucSource0x1D=Index6;	//
		icanSlave.ucSource0x1E=Index6Val>>8;	//
		icanSlave.ucSource0x1F=Index6Val; //
	}
}
#endif //#if IS_LOGIC_SLAVE(LOGIC_TYPE)

	 //PC配置模式
#if IS_LOGIC_MASTER(LOGIC_TYPE)
void PCConfig_Master(void)
{
	unsigned char Index1,Index2,Index3,Index4,Index5,Index6;
	unsigned short  Index1Val,Index2Val,Index3Val,Index4Val,Index5Val,Index6Val;
	unsigned char DstId;
	tICANSlave *pICANSlave_PC;
	tICANSlave *pICANSlave_Dst;
	
	if ((icanMaster.ucNetCfg & (1<<Prd_PC)) != 0)
	{
		pICANSlave_PC = &icanMaster.pICANSlvArray[icanMaster.ucIdtoSlvArrayIndex[Prd_PC]];
		DstId = PRDID_STATESETTING(pICANSlave_PC->ucSource0x00);
		if ((icanMaster.ucNetCfg & (1<<DstId)) != 0)
		{
			pICANSlave_Dst = &icanMaster.pICANSlvArray[icanMaster.ucIdtoSlvArrayIndex[DstId]];
			
			if (DstId == Prd_Move)
			{
				Index1=pICANSlave_PC->ucSource0x0E;
				Index2=pICANSlave_PC->ucSource0x11;
				Index3=pICANSlave_PC->ucSource0x14;
				Index4=pICANSlave_PC->ucSource0x17;
				Index5=pICANSlave_PC->ucSource0x1A;
				Index6=pICANSlave_PC->ucSource0x1D;
				if (INSTRUCT_STATESETTING(pICANSlave_PC->ucSource0x00) == WR_INSTRUCT_STATESETTING)
				{
					//更新参数列表
					Index1Val=(pICANSlave_PC->ucSource0x0F<<8)+pICANSlave_PC->ucSource0x10;
					SaveParaToEeprom(Index1,Index1Val);

					Index2Val=(pICANSlave_PC->ucSource0x12<<8)+pICANSlave_PC->ucSource0x13;
					SaveParaToEeprom(Index2,Index2Val);

					Index3Val=(pICANSlave_PC->ucSource0x15<<8)+pICANSlave_PC->ucSource0x16;
					SaveParaToEeprom(Index3,Index3Val);

					Index4Val=(pICANSlave_PC->ucSource0x18<<8)+pICANSlave_PC->ucSource0x19;
					SaveParaToEeprom(Index4,Index4Val);

					Index5Val=(pICANSlave_PC->ucSource0x1B<<8)+pICANSlave_PC->ucSource0x1C;
					SaveParaToEeprom(Index5,Index5Val);

					Index6Val=(pICANSlave_PC->ucSource0x1E<<8)+pICANSlave_PC->ucSource0x1F;
					SaveParaToEeprom(Index6,Index6Val);
				}
				//回显PC配置的数据
				pICANSlave_PC->ucSource0x20 = pICANSlave_PC->ucSource0x00;

				pICANSlave_PC->ucSource0x2E=Index1;
				Index1Val = ReadParaValByIndex(Index1);
				pICANSlave_PC->ucSource0x2F=(INT8U)(Index1Val>>8);
				pICANSlave_PC->ucSource0x30=(INT8U)Index1Val;

				pICANSlave_PC->ucSource0x31=Index2;
				Index2Val = ReadParaValByIndex(Index2);
				pICANSlave_PC->ucSource0x32=(INT8U)(Index2Val>>8);
				pICANSlave_PC->ucSource0x33=(INT8U)Index2Val;

				pICANSlave_PC->ucSource0x34=Index3;
				Index3Val = ReadParaValByIndex(Index3);
				pICANSlave_PC->ucSource0x35=(INT8U)(Index3Val>>8);
				pICANSlave_PC->ucSource0x36=(INT8U)Index3Val;

				pICANSlave_PC->ucSource0x37=Index4;
				Index4Val = ReadParaValByIndex(Index4);
				pICANSlave_PC->ucSource0x38=(INT8U)(Index4Val>>8);
				pICANSlave_PC->ucSource0x39=(INT8U)Index4Val;
				
				pICANSlave_PC->ucSource0x3A=Index5;
				Index5Val = ReadParaValByIndex(Index5);
				pICANSlave_PC->ucSource0x3B=(INT8U)(Index5Val>>8);
				pICANSlave_PC->ucSource0x3C=(INT8U)Index5Val;
				
				pICANSlave_PC->ucSource0x3D=Index6;
				Index6Val = ReadParaValByIndex(Index6);
				pICANSlave_PC->ucSource0x3E=(INT8U)(Index6Val>>8);
				pICANSlave_PC->ucSource0x3F=(INT8U)Index6Val;
			}
			else //Slave
			{
				pICANSlave_Dst->ucSource0x20 = pICANSlave_PC->ucSource0x00;
				pICANSlave_Dst->ucSource0x2E = pICANSlave_PC->ucSource0x0E;
				pICANSlave_Dst->ucSource0x2F = pICANSlave_PC->ucSource0x0F;
				pICANSlave_Dst->ucSource0x30 = pICANSlave_PC->ucSource0x10;
				pICANSlave_Dst->ucSource0x31 = pICANSlave_PC->ucSource0x11;
				pICANSlave_Dst->ucSource0x32 = pICANSlave_PC->ucSource0x12;
				pICANSlave_Dst->ucSource0x33 = pICANSlave_PC->ucSource0x13;
				pICANSlave_Dst->ucSource0x34 = pICANSlave_PC->ucSource0x14;
				pICANSlave_Dst->ucSource0x35 = pICANSlave_PC->ucSource0x15;
				pICANSlave_Dst->ucSource0x36 = pICANSlave_PC->ucSource0x16;
				pICANSlave_Dst->ucSource0x37 = pICANSlave_PC->ucSource0x17;
				pICANSlave_Dst->ucSource0x38 = pICANSlave_PC->ucSource0x18;
				pICANSlave_Dst->ucSource0x39 = pICANSlave_PC->ucSource0x19;
				pICANSlave_Dst->ucSource0x3A = pICANSlave_PC->ucSource0x1A;
				pICANSlave_Dst->ucSource0x3B = pICANSlave_PC->ucSource0x1B;
				pICANSlave_Dst->ucSource0x3C = pICANSlave_PC->ucSource0x1C;
				pICANSlave_Dst->ucSource0x3D = pICANSlave_PC->ucSource0x1D;
				pICANSlave_Dst->ucSource0x3E = pICANSlave_PC->ucSource0x1E;
				pICANSlave_Dst->ucSource0x3F = pICANSlave_PC->ucSource0x1F;
				
				//回显PC配置的数据
				pICANSlave_PC->ucSource0x20 = pICANSlave_Dst->ucSource0x00;
				
				pICANSlave_PC->ucSource0x2E = pICANSlave_Dst->ucSource0x0E;
				pICANSlave_PC->ucSource0x2F = pICANSlave_Dst->ucSource0x0F;
				pICANSlave_PC->ucSource0x30 = pICANSlave_Dst->ucSource0x10;
				pICANSlave_PC->ucSource0x31 = pICANSlave_Dst->ucSource0x11;
				pICANSlave_PC->ucSource0x32 = pICANSlave_Dst->ucSource0x12;
				pICANSlave_PC->ucSource0x33 = pICANSlave_Dst->ucSource0x13;
				pICANSlave_PC->ucSource0x34 = pICANSlave_Dst->ucSource0x14;
				
				pICANSlave_PC->ucSource0x35 = pICANSlave_Dst->ucSource0x15;
				pICANSlave_PC->ucSource0x36 = pICANSlave_Dst->ucSource0x16;
				pICANSlave_PC->ucSource0x37 = pICANSlave_Dst->ucSource0x17;
				pICANSlave_PC->ucSource0x38 = pICANSlave_Dst->ucSource0x18;
				pICANSlave_PC->ucSource0x39 = pICANSlave_Dst->ucSource0x19;
				pICANSlave_PC->ucSource0x3A = pICANSlave_Dst->ucSource0x1A;
				pICANSlave_PC->ucSource0x3B = pICANSlave_Dst->ucSource0x1B;
				
				pICANSlave_PC->ucSource0x3C = pICANSlave_Dst->ucSource0x1C;
				pICANSlave_PC->ucSource0x3D = pICANSlave_Dst->ucSource0x1D;
				pICANSlave_PC->ucSource0x3E = pICANSlave_Dst->ucSource0x1E;
				pICANSlave_PC->ucSource0x3F = pICANSlave_Dst->ucSource0x1F;
			}
		}
		else //No dstID
		{
			pICANSlave_PC->ucSource0x20 = pICANSlave_PC->ucSource0x00;
			pICANSlave_PC->ucSource0x2E = 0;
			pICANSlave_PC->ucSource0x31 = 0;
			pICANSlave_PC->ucSource0x34 = 0;
			pICANSlave_PC->ucSource0x37 = 0;
			pICANSlave_PC->ucSource0x3A = 0;
			pICANSlave_PC->ucSource0x3D = 0;
		}
	}
}
#endif //#if IS_LOGIC_MASTER(LOGIC_TYPE)

	 //PC配置模式
#if IS_LOGIC_SLAVE(LOGIC_TYPE)
void PCConfig_Slave(void)
{
	unsigned char Index1,Index2,Index3,Index4,Index5,Index6;
	unsigned short  Index1Val,Index2Val,Index3Val,Index4Val,Index5Val,Index6Val;
	unsigned char DstId;
	
	DstId=PRDID_STATESETTING(icanSlave.ucSource0x20);
	if(DstId == icanSlave.ucMacID)
	{
		Index1=icanSlave.ucSource0x2E;
		Index2=icanSlave.ucSource0x31;
		Index3=icanSlave.ucSource0x34;
		Index4=icanSlave.ucSource0x37;
		Index5=icanSlave.ucSource0x3A;
		Index6=icanSlave.ucSource0x3D;
		if (INSTRUCT_STATESETTING(icanSlave.ucSource0x20) == WR_INSTRUCT_STATESETTING)
		{
			
			Index1Val=(icanSlave.ucSource0x2F<<8)+icanSlave.ucSource0x30;
			SaveParaToEeprom(Index1,Index1Val);
			
			Index2Val=(icanSlave.ucSource0x32<<8)+icanSlave.ucSource0x33;	//
			SaveParaToEeprom(Index2,Index2Val);
			
			Index3Val=(icanSlave.ucSource0x35<<8)+icanSlave.ucSource0x36;	//
			SaveParaToEeprom(Index3,Index3Val);
			
			Index4Val=(icanSlave.ucSource0x38<<8)+icanSlave.ucSource0x39;	//
			SaveParaToEeprom(Index4,Index4Val);
			
			Index5Val=(icanSlave.ucSource0x3B<<8)+icanSlave.ucSource0x3C;	//
			SaveParaToEeprom(Index5,Index5Val);
			
			Index6Val=(icanSlave.ucSource0x3E<<8)+icanSlave.ucSource0x3F;	//
			SaveParaToEeprom(Index6,Index6Val);
		}
		//回显PC配置的数据
		icanSlave.ucSource0x00=icanSlave.ucSource0x20;
		
		icanSlave.ucSource0x0E=Index1;	//
		Index1Val = ReadParaValByIndex(Index1);
		icanSlave.ucSource0x0F=(INT8U)(Index1Val>>8);
		icanSlave.ucSource0x10=(INT8U)Index1Val;
		
		icanSlave.ucSource0x11=Index2;	//
		Index2Val = ReadParaValByIndex(Index2);
		icanSlave.ucSource0x12=(INT8U)(Index2Val>>8);	//
		icanSlave.ucSource0x13=(INT8U)Index2Val;
		
		icanSlave.ucSource0x14=Index3;
		Index3Val = ReadParaValByIndex(Index3);
		icanSlave.ucSource0x15=(INT8U)(Index3Val>>8);	//
		icanSlave.ucSource0x16=(INT8U)Index3Val;
		
		icanSlave.ucSource0x17=Index4;	//	
		Index4Val = ReadParaValByIndex(Index4);
		icanSlave.ucSource0x18=(INT8U)(Index4Val>>8);	//	
		icanSlave.ucSource0x19=(INT8U)Index4Val;
		
		icanSlave.ucSource0x1A=Index5;		
		Index5Val = ReadParaValByIndex(Index5);
		icanSlave.ucSource0x1B=(INT8U)(Index5Val>>8);	//
		icanSlave.ucSource0x1C=(INT8U)Index5Val;
		
		icanSlave.ucSource0x1D=Index6;	//	
		Index6Val = ReadParaValByIndex(Index6);
		icanSlave.ucSource0x1E=(INT8U)(Index6Val>>8);	//	
		icanSlave.ucSource0x1F=(INT8U)Index6Val;
	}
}		
#endif //#if IS_LOGIC_SLAVE(LOGIC_TYPE)

#if IS_LOGIC_MASTER(LOGIC_TYPE)
void PCIdle_Master(void)
{
	tICANSlave *pICANSlave_PC;
	
	if ((icanMaster.ucNetCfg & (1<<Prd_PC)) != 0)
	{
		pICANSlave_PC = &icanMaster.pICANSlvArray[icanMaster.ucIdtoSlvArrayIndex[Prd_PC]];
		pICANSlave_PC->ucSource0x20 = pICANSlave_PC->ucSource0x00;
	}
}
#endif //#if IS_LOGIC_MASTER(LOGIC_TYPE)

#if IS_LOGIC_SLAVE(LOGIC_TYPE)
void PCIdle_Slave(void)
{
}
#endif //#if IS_LOGIC_SLAVE(LOGIC_TYPE)

 //仪表监控
#if IS_LOGIC_MASTER(LOGIC_TYPE)
void HMIMonitor_Master(void)
{
	unsigned char Index1,Index2,Index3,Index4,Index5,Index6;
	unsigned short  Index1Val,Index2Val,Index3Val,Index4Val,Index5Val,Index6Val;
	unsigned char DstId,DstStateSetting;
	tICANSlave *pICANSlave_HMI;
	tICANSlave *pICANSlave_Dst;
	
	if ((icanMaster.ucNetCfg & (1<<Prd_HMI)) != 0)
	{
		pICANSlave_HMI = &icanMaster.pICANSlvArray[icanMaster.ucIdtoSlvArrayIndex[Prd_HMI]];
		DstId = PRDID_STATESETTING(pICANSlave_HMI->ucSource0x00);
		if ((icanMaster.ucNetCfg & (1<<DstId)) != 0)
		{
			pICANSlave_Dst = &icanMaster.pICANSlvArray[icanMaster.ucIdtoSlvArrayIndex[DstId]];

			Index1=pICANSlave_HMI->ucSource0x0E; 
			Index2=pICANSlave_HMI->ucSource0x11; 
			Index3=pICANSlave_HMI->ucSource0x14; 
			Index4=pICANSlave_HMI->ucSource0x17; 
			Index5=pICANSlave_HMI->ucSource0x1A; 
			Index6=pICANSlave_HMI->ucSource0x1D; 
			if(DstId == Prd_Move)
			{
				//监控主站，直接返回参数列表相应内容
				DstStateSetting = pICANSlave_HMI->ucSource0x00;
				Index1Val=ReadMonitorParaValByIndex(Index1);	//			
				Index2Val=ReadMonitorParaValByIndex(Index2);	//
				Index3Val=ReadMonitorParaValByIndex(Index3);	//
				Index4Val=ReadMonitorParaValByIndex(Index4);	//
				Index5Val=ReadMonitorParaValByIndex(Index5);	//
				Index6Val=ReadMonitorParaValByIndex(Index6);	//							
			}
			else //从站：监控对象ucPrdID
			{
				//将index信息传递给目标从站镜像
				pICANSlave_Dst->ucSource0x20 = pICANSlave_HMI->ucSource0x00;						
				pICANSlave_Dst->ucSource0x2E=Index1;		
				pICANSlave_Dst->ucSource0x31=Index2;
				pICANSlave_Dst->ucSource0x34=Index3;
				pICANSlave_Dst->ucSource0x37=Index4;
				pICANSlave_Dst->ucSource0x3A=Index5;
				pICANSlave_Dst->ucSource0x3D=Index6;
				
				//从从站镜像读取当前的index和value(实际数据会有一个轮训周期的延迟)
				DstStateSetting = pICANSlave_Dst->ucSource0x00;
				Index1=pICANSlave_Dst->ucSource0x0E;
				Index1Val=(pICANSlave_Dst->ucSource0x0F<<8)+pICANSlave_Dst->ucSource0x10;	//						
				Index2=pICANSlave_Dst->ucSource0x11;
				Index2Val=(pICANSlave_Dst->ucSource0x12<<8)+pICANSlave_Dst->ucSource0x13;	//
				Index3=pICANSlave_Dst->ucSource0x14;
				Index3Val=(pICANSlave_Dst->ucSource0x15<<8)+pICANSlave_Dst->ucSource0x16;	//						
				Index4=pICANSlave_Dst->ucSource0x17;
				Index4Val=(pICANSlave_Dst->ucSource0x18<<8)+pICANSlave_Dst->ucSource0x19;	//
				Index5=pICANSlave_Dst->ucSource0x1A;
				Index5Val=(pICANSlave_Dst->ucSource0x1B<<8)+pICANSlave_Dst->ucSource0x1C;	//							
				Index6=pICANSlave_Dst->ucSource0x1D;
				Index6Val=(pICANSlave_Dst->ucSource0x1E<<8)+pICANSlave_Dst->ucSource0x1F;	//				
			} 
		}
		else //No dst id
		{
			DstStateSetting = pICANSlave_HMI->ucSource0x00;
			//Force HMI to discard the data
			Index1 = 0;
			Index2 = 0;
			Index3 = 0;
			Index4 = 0;
			Index5 = 0;
			Index6 = 0;
		}
		//0x40
		pICANSlave_HMI->ucSource0x20 = DstStateSetting;
		//0x81 
		//0x82
		pICANSlave_HMI->ucSource0x2E=Index1;	//
		pICANSlave_HMI->ucSource0x2F=Index1Val>>8;	//
		pICANSlave_HMI->ucSource0x30=Index1Val;	//
		pICANSlave_HMI->ucSource0x31=Index2;	//
		pICANSlave_HMI->ucSource0x32=Index2Val>>8;	//
		pICANSlave_HMI->ucSource0x33=Index2Val;	//
		pICANSlave_HMI->ucSource0x34=Index3;
		//0x83
		pICANSlave_HMI->ucSource0x35=Index3Val>>8;	//
		pICANSlave_HMI->ucSource0x36=Index3Val;	//
		pICANSlave_HMI->ucSource0x37=Index4;	//
		pICANSlave_HMI->ucSource0x38=Index4Val>>8;	//
		pICANSlave_HMI->ucSource0x39=Index4Val;	//
		pICANSlave_HMI->ucSource0x3A=Index5;	//
		pICANSlave_HMI->ucSource0x3B=Index5Val>>8;
		//0xC0
		pICANSlave_HMI->ucSource0x3C=Index5Val;	//
		pICANSlave_HMI->ucSource0x3D=Index6;	//
		pICANSlave_HMI->ucSource0x3E=Index6Val>>8;	//
		pICANSlave_HMI->ucSource0x3F=Index6Val; //				
	}
}
#endif //#if IS_LOGIC_MASTER(LOGIC_TYPE)

//系统监控模式
#if (IS_LOGIC_SLAVE(LOGIC_TYPE) && (LOGIC_TYPE != _CONTROLLER_HMI))
void HMIMonitor_Slave(void)
{
	unsigned char Index1,Index2,Index3,Index4,Index5,Index6;
	unsigned short  Index1Val,Index2Val,Index3Val,Index4Val,Index5Val,Index6Val;
	unsigned char DstId;
	
	DstId=PRDID_STATESETTING(icanSlave.ucSource0x20);
		
	if(DstId == icanSlave.ucMacID)
	{
		icanSlave.ucSource0x00=icanSlave.ucSource0x20;

		//获取从站相应参数列表值
		Index1=icanSlave.ucSource0x2E;
		Index1Val=ReadMonitorParaValByIndex(Index1);	//			
		icanSlave.ucSource0x0E=Index1;	//
		icanSlave.ucSource0x0F=Index1Val>>8;	//
		icanSlave.ucSource0x10=Index1Val;	//

		Index2=icanSlave.ucSource0x31;
		Index2Val=ReadMonitorParaValByIndex(Index2);	//			
		icanSlave.ucSource0x11=Index2;	//
		icanSlave.ucSource0x12=Index2Val>>8;	//
		icanSlave.ucSource0x13=Index2Val;	//

		Index3=icanSlave.ucSource0x34;
		Index3Val=ReadMonitorParaValByIndex(Index3);	//			
		icanSlave.ucSource0x14=Index3;
		icanSlave.ucSource0x15=Index3Val>>8;	//
		icanSlave.ucSource0x16=Index3Val;	//

		Index4=icanSlave.ucSource0x37;
		Index4Val=ReadMonitorParaValByIndex(Index4);	//			
		icanSlave.ucSource0x17=Index4;	//
		icanSlave.ucSource0x18=Index4Val>>8;	//
		icanSlave.ucSource0x19=Index4Val;	//
		
		Index5=icanSlave.ucSource0x3A;
		Index5Val=ReadMonitorParaValByIndex(Index5);	//			
		icanSlave.ucSource0x1A=Index5;	//
		icanSlave.ucSource0x1B=Index5Val>>8;
		icanSlave.ucSource0x1C=Index5Val;	//
		
		Index6=icanSlave.ucSource0x3D;
		Index6Val=ReadMonitorParaValByIndex(Index6);	//			
		icanSlave.ucSource0x1D=Index6;	//
		icanSlave.ucSource0x1E=Index6Val>>8;	//
		icanSlave.ucSource0x1F=Index6Val; //
	}
}
#endif //#if (IS_LOGIC_SLAVE(LOGIC_TYPE) && (LOGIC_TYPE != _CONTROLLER_HMI))

#if (IS_LOGIC_SLAVE(LOGIC_TYPE) && (LOGIC_TYPE == _CONTROLLER_HMI))
void HMIMonitor_Slave(void)
{
	INT16U index1Val,index2Val,index3Val,index4Val,index5Val,index6Val;

	if (icanSlave.bIsConnect == true)
	{
		//读取ICAN资源节点
		
		if ( (icanSlave.ucSource0x0E == icanSlave.ucSource0x2E)
			|| (icanSlave.ucSource0x11 == icanSlave.ucSource0x31)
			|| (icanSlave.ucSource0x14 == icanSlave.ucSource0x34)
			|| (icanSlave.ucSource0x17 == icanSlave.ucSource0x37)
			|| (icanSlave.ucSource0x1A == icanSlave.ucSource0x3A)
			|| (icanSlave.ucSource0x1D == icanSlave.ucSource0x3D)
			)
		{
			icanSlave.ucTime++;
			index1Val=(icanSlave.ucSource0x2F<<8)+icanSlave.ucSource0x30;
			SaveMonitorParaValByIndexToRam(icanSlave.ucSource0x2E,index1Val);
			index2Val=(icanSlave.ucSource0x32<<8)+icanSlave.ucSource0x33;
			SaveMonitorParaValByIndexToRam(icanSlave.ucSource0x31,index2Val);
			index3Val=(icanSlave.ucSource0x35<<8)+icanSlave.ucSource0x36;
			SaveMonitorParaValByIndexToRam(icanSlave.ucSource0x34,index3Val);
			index4Val=(icanSlave.ucSource0x38<<8)+icanSlave.ucSource0x39;
			SaveMonitorParaValByIndexToRam(icanSlave.ucSource0x37,index4Val);
			index5Val=(icanSlave.ucSource0x3B<<8)+icanSlave.ucSource0x3C;
			SaveMonitorParaValByIndexToRam(icanSlave.ucSource0x3A,index5Val);
			index6Val=(icanSlave.ucSource0x3E<<8)+icanSlave.ucSource0x3F;
			SaveMonitorParaValByIndexToRam(icanSlave.ucSource0x3D,index6Val);
		}
	}

}
#endif //#if (IS_LOGIC_SLAVE(LOGIC_TYPE) && (LOGIC_TYPE == _CONTROLLER_HMI))
//HMI 配置
#if IS_LOGIC_MASTER(LOGIC_TYPE)
void HMIConfig_Master(void)
{
	unsigned char Index1,Index2,Index3,Index4,Index5,Index6;
	unsigned short  Index1Val,Index2Val,Index3Val,Index4Val,Index5Val,Index6Val;
	unsigned char DstId;
	tICANSlave *pICANSlave_HMI;
	tICANSlave *pICANSlave_Dst;
	
	if ((icanMaster.ucNetCfg & (1<<Prd_HMI)) != 0)
	{
		pICANSlave_HMI = &icanMaster.pICANSlvArray[icanMaster.ucIdtoSlvArrayIndex[Prd_HMI]];
		DstId = PRDID_STATESETTING(pICANSlave_HMI->ucSource0x00);
		if ((icanMaster.ucNetCfg & (1<<DstId)) != 0)
		{
			pICANSlave_Dst = &icanMaster.pICANSlvArray[icanMaster.ucIdtoSlvArrayIndex[DstId]];
			
			if (DstId == Prd_Move)
			{
				Index1 = pICANSlave_HMI->ucSource0x0E;
				Index2 = pICANSlave_HMI->ucSource0x11;
				Index3 = pICANSlave_HMI->ucSource0x14;
				Index4 = pICANSlave_HMI->ucSource0x17;
				Index5 = pICANSlave_HMI->ucSource0x1A;
				Index6 = pICANSlave_HMI->ucSource0x1D;
				if (INSTRUCT_STATESETTING(pICANSlave_HMI->ucSource0x00) == WR_INSTRUCT_STATESETTING)
				{
					//更新参数列表
					Index1Val=(pICANSlave_HMI->ucSource0x0F<<8)+pICANSlave_HMI->ucSource0x10;
					SaveParaToEeprom(Index1,Index1Val);

					Index2Val=(pICANSlave_HMI->ucSource0x12<<8)+pICANSlave_HMI->ucSource0x13;
					SaveParaToEeprom(Index2,Index2Val);

					Index3Val=(pICANSlave_HMI->ucSource0x15<<8)+pICANSlave_HMI->ucSource0x16;
					SaveParaToEeprom(Index3,Index3Val);

					Index4Val=(pICANSlave_HMI->ucSource0x18<<8)+pICANSlave_HMI->ucSource0x19;
					SaveParaToEeprom(Index4,Index4Val);

					Index5Val=(pICANSlave_HMI->ucSource0x1B<<8)+pICANSlave_HMI->ucSource0x1C;
					SaveParaToEeprom(Index5,Index5Val);

					Index6Val=(pICANSlave_HMI->ucSource0x1E<<8)+pICANSlave_HMI->ucSource0x1F;
					SaveParaToEeprom(Index6,Index6Val);
				}
				//回显PC配置的数据
				pICANSlave_HMI->ucSource0x20 = pICANSlave_HMI->ucSource0x00;

				pICANSlave_HMI->ucSource0x2E=Index1;
				Index1Val = ReadParaValByIndex(Index1);
				pICANSlave_HMI->ucSource0x2F=(INT8U)(Index1Val>>8);
				pICANSlave_HMI->ucSource0x30=(INT8U)Index1Val;
				pICANSlave_HMI->ucSource0x31=Index2;
				Index2Val = ReadParaValByIndex(Index2);
				pICANSlave_HMI->ucSource0x32=(INT8U)(Index2Val>>8);
				pICANSlave_HMI->ucSource0x33=(INT8U)Index2Val;
				pICANSlave_HMI->ucSource0x34=Index3;
				Index3Val = ReadParaValByIndex(Index3);
				pICANSlave_HMI->ucSource0x35=(INT8U)(Index3Val>>8);
				pICANSlave_HMI->ucSource0x36=(INT8U)Index3Val;
				pICANSlave_HMI->ucSource0x37=Index4;
				Index4Val = ReadParaValByIndex(Index4);
				pICANSlave_HMI->ucSource0x38=(INT8U)(Index4Val>>8);
				pICANSlave_HMI->ucSource0x39=(INT8U)Index4Val;
				pICANSlave_HMI->ucSource0x3A=Index5;
				Index5Val = ReadParaValByIndex(Index5);
				pICANSlave_HMI->ucSource0x3B=(INT8U)(Index5Val>>8);
				pICANSlave_HMI->ucSource0x3C=(INT8U)Index5Val;
				pICANSlave_HMI->ucSource0x3D=Index6;
				Index6Val = ReadParaValByIndex(Index6);
				pICANSlave_HMI->ucSource0x3E=(INT8U)(Index6Val>>8);
				pICANSlave_HMI->ucSource0x3F=(INT8U)Index6Val;
			}
			else //Slave
			{
				pICANSlave_Dst->ucSource0x20 = pICANSlave_HMI->ucSource0x00;
				pICANSlave_Dst->ucSource0x2E = pICANSlave_HMI->ucSource0x0E;
				pICANSlave_Dst->ucSource0x2F = pICANSlave_HMI->ucSource0x0F;
				pICANSlave_Dst->ucSource0x30 = pICANSlave_HMI->ucSource0x10;
				pICANSlave_Dst->ucSource0x31 = pICANSlave_HMI->ucSource0x11;
				pICANSlave_Dst->ucSource0x32 = pICANSlave_HMI->ucSource0x12;
				pICANSlave_Dst->ucSource0x33 = pICANSlave_HMI->ucSource0x13;
				pICANSlave_Dst->ucSource0x34 = pICANSlave_HMI->ucSource0x14;
				pICANSlave_Dst->ucSource0x35 = pICANSlave_HMI->ucSource0x15;
				pICANSlave_Dst->ucSource0x36 = pICANSlave_HMI->ucSource0x16;
				pICANSlave_Dst->ucSource0x37 = pICANSlave_HMI->ucSource0x17;
				pICANSlave_Dst->ucSource0x38 = pICANSlave_HMI->ucSource0x18;
				pICANSlave_Dst->ucSource0x39 = pICANSlave_HMI->ucSource0x19;
				pICANSlave_Dst->ucSource0x3A = pICANSlave_HMI->ucSource0x1A;
				pICANSlave_Dst->ucSource0x3B = pICANSlave_HMI->ucSource0x1B;
				pICANSlave_Dst->ucSource0x3C = pICANSlave_HMI->ucSource0x1C;
				pICANSlave_Dst->ucSource0x3D = pICANSlave_HMI->ucSource0x1D;
				pICANSlave_Dst->ucSource0x3E = pICANSlave_HMI->ucSource0x1E;
				pICANSlave_Dst->ucSource0x3F = pICANSlave_HMI->ucSource0x1F;
				
				//回显PC配置的数据
				pICANSlave_HMI->ucSource0x20 = pICANSlave_Dst->ucSource0x00;
				
				pICANSlave_HMI->ucSource0x2E = pICANSlave_Dst->ucSource0x0E;
				pICANSlave_HMI->ucSource0x2F = pICANSlave_Dst->ucSource0x0F;
				pICANSlave_HMI->ucSource0x30 = pICANSlave_Dst->ucSource0x10;
				pICANSlave_HMI->ucSource0x31 = pICANSlave_Dst->ucSource0x11;
				pICANSlave_HMI->ucSource0x32 = pICANSlave_Dst->ucSource0x12;
				pICANSlave_HMI->ucSource0x33 = pICANSlave_Dst->ucSource0x13;
				pICANSlave_HMI->ucSource0x34 = pICANSlave_Dst->ucSource0x14;
				
				pICANSlave_HMI->ucSource0x35 = pICANSlave_Dst->ucSource0x15;
				pICANSlave_HMI->ucSource0x36 = pICANSlave_Dst->ucSource0x16;
				pICANSlave_HMI->ucSource0x37 = pICANSlave_Dst->ucSource0x17;
				pICANSlave_HMI->ucSource0x38 = pICANSlave_Dst->ucSource0x18;
				pICANSlave_HMI->ucSource0x39 = pICANSlave_Dst->ucSource0x19;
				pICANSlave_HMI->ucSource0x3A = pICANSlave_Dst->ucSource0x1A;
				pICANSlave_HMI->ucSource0x3B = pICANSlave_Dst->ucSource0x1B;
				
				pICANSlave_HMI->ucSource0x3C = pICANSlave_Dst->ucSource0x1C;
				pICANSlave_HMI->ucSource0x3D = pICANSlave_Dst->ucSource0x1D;
				pICANSlave_HMI->ucSource0x3E = pICANSlave_Dst->ucSource0x1E;
				pICANSlave_HMI->ucSource0x3F = pICANSlave_Dst->ucSource0x1F;
			}
		}
		else //No dstID
		{
			pICANSlave_HMI->ucSource0x20 = pICANSlave_HMI->ucSource0x00;
			pICANSlave_HMI->ucSource0x2E = 0;
			pICANSlave_HMI->ucSource0x31 = 0;
			pICANSlave_HMI->ucSource0x34 = 0;
			pICANSlave_HMI->ucSource0x37 = 0;
			pICANSlave_HMI->ucSource0x3A = 0;
			pICANSlave_HMI->ucSource0x3D = 0;
		}
	}
}
#endif //#if IS_LOGIC_MASTER(LOGIC_TYPE)

#if IS_LOGIC_SLAVE(LOGIC_TYPE)
void HMIConfig_Slave(void)
{
	unsigned char Index1,Index2,Index3,Index4,Index5,Index6;
	unsigned short  Index1Val,Index2Val,Index3Val,Index4Val,Index5Val,Index6Val;
	unsigned char DstId;
	
	DstId=PRDID_STATESETTING(icanSlave.ucSource0x20);
	if(DstId == icanSlave.ucMacID)
	{
		Index1=icanSlave.ucSource0x2E;
		Index2=icanSlave.ucSource0x31;
		Index3=icanSlave.ucSource0x34;
		Index4=icanSlave.ucSource0x37;
		Index5=icanSlave.ucSource0x3A;
		Index6=icanSlave.ucSource0x3D;
		if (INSTRUCT_STATESETTING(icanSlave.ucSource0x20) == WR_INSTRUCT_STATESETTING)
		{
			
			Index1Val=(icanSlave.ucSource0x2F<<8)+icanSlave.ucSource0x30;
			SaveParaToEeprom(Index1,Index1Val);
			
			Index2Val=(icanSlave.ucSource0x32<<8)+icanSlave.ucSource0x33;	//
			SaveParaToEeprom(Index2,Index2Val);
			
			Index3Val=(icanSlave.ucSource0x35<<8)+icanSlave.ucSource0x36;	//
			SaveParaToEeprom(Index3,Index3Val);
			
			Index4Val=(icanSlave.ucSource0x38<<8)+icanSlave.ucSource0x39;	//
			SaveParaToEeprom(Index4,Index4Val);
			
			Index5Val=(icanSlave.ucSource0x3B<<8)+icanSlave.ucSource0x3C;	//
			SaveParaToEeprom(Index5,Index5Val);
			
			Index6Val=(icanSlave.ucSource0x3E<<8)+icanSlave.ucSource0x3F;	//
			SaveParaToEeprom(Index6,Index6Val);
		}
		//回显PC配置的数据
		icanSlave.ucSource0x00=icanSlave.ucSource0x20;
		
		icanSlave.ucSource0x0E=Index1;	//
		Index1Val = ReadParaValByIndex(Index1);
		icanSlave.ucSource0x0F=(INT8U)(Index1Val>>8);
		icanSlave.ucSource0x10=(INT8U)Index1Val;
		
		icanSlave.ucSource0x11=Index2;	//
		Index2Val = ReadParaValByIndex(Index2);
		icanSlave.ucSource0x12=(INT8U)(Index2Val>>8);	//
		icanSlave.ucSource0x13=(INT8U)Index2Val;
		
		icanSlave.ucSource0x14=Index3;
		Index3Val = ReadParaValByIndex(Index3);
		icanSlave.ucSource0x15=(INT8U)(Index3Val>>8);	//
		icanSlave.ucSource0x16=(INT8U)Index3Val;
		
		icanSlave.ucSource0x17=Index4;	//	
		Index4Val = ReadParaValByIndex(Index4);
		icanSlave.ucSource0x18=(INT8U)(Index4Val>>8);	//	
		icanSlave.ucSource0x19=(INT8U)Index4Val;
		
		icanSlave.ucSource0x1A=Index5;		
		Index5Val = ReadParaValByIndex(Index5);
		icanSlave.ucSource0x1B=(INT8U)(Index5Val>>8);	//
		icanSlave.ucSource0x1C=(INT8U)Index5Val;
		
		icanSlave.ucSource0x1D=Index6;	//	
		Index6Val = ReadParaValByIndex(Index6);
		icanSlave.ucSource0x1E=(INT8U)(Index6Val>>8);	//	
		icanSlave.ucSource0x1F=(INT8U)Index6Val;
	}
}
#endif //#if IS_LOGIC_SLAVE(LOGIC_TYPE)

#if IS_LOGIC_MASTER(LOGIC_TYPE)
void HMIIdle_Master(void)
{
	tICANSlave *pICANSlave_HMI;
	
	if ((icanMaster.ucNetCfg & (1<<Prd_HMI)) != 0)
	{
		pICANSlave_HMI = &icanMaster.pICANSlvArray[icanMaster.ucIdtoSlvArrayIndex[Prd_HMI]];
		pICANSlave_HMI->ucSource0x20 = pICANSlave_HMI->ucSource0x00;
	}
}
#endif //	#if IS_LOGIC_MASTER(LOGIC_TYPE)

#if IS_LOGIC_SLAVE(LOGIC_TYPE)
void HMIIdle_Slave(void)
{
}
#endif
//HMI conflict with PC. HMI Keep silent.
#if IS_LOGIC_MASTER(LOGIC_TYPE)
void HMIPcIdle_Master(void)
{
	tICANSlave *pICANSlave_HMI;
	tICANSlave *pICANSlave_PC;
	
	if ((icanMaster.ucNetCfg & (1<<Prd_HMI)) != 0)
	{
		pICANSlave_HMI = &icanMaster.pICANSlvArray[icanMaster.ucIdtoSlvArrayIndex[Prd_HMI]];
		if ((icanMaster.ucNetCfg & (1<<Prd_PC)) != 0)
		{
			pICANSlave_PC = &icanMaster.pICANSlvArray[icanMaster.ucIdtoSlvArrayIndex[Prd_PC]];
			
			pICANSlave_HMI->ucSource0x20 = pICANSlave_PC->ucSource0x00;
		}
		else
		{
			pICANSlave_HMI->ucSource0x20 = pICANSlave_HMI->ucSource0x00;
		}
	}
}
#endif //#if IS_LOGIC_MASTER(LOGIC_TYPE)

#if IS_LOGIC_SLAVE(LOGIC_TYPE)
void HMIPcIdle_Slave(void)
{
}
#endif //#if IS_LOGIC_SLAVE(LOGIC_TYPE)

//系统匹配模式
void ICANSysMatch(void)
{

}
