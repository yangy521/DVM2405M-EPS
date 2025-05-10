/*******************************************************************************
* Filename: iCANLogic.h	                                             	 		   *
* Description:											   			 		   *
* Author:                                                           		   *
* Date:     														 		   *
* Revision:															 		   *
*******************************************************************************/
#ifndef __ICANLOGIC_H
#define __ICANLOGIC_H

#include "KSDsys.h"

void PCMonitor_Slave(void);
void PCMonitor_Master(void);
void PCConfig_Slave(void);
void PCConfig_Master(void);
void PCIdle_Master(void);
void PCIdle_Slave(void);
void ICANSysMatch(void);
void HMIMonitor_Master(void);
void HMIMonitor_Slave(void);
void HMIConfig_Master(void);
void HMIConfig_Slave(void);
void HMIIdle_Master(void);
void HMIIdle_Slave(void);
void HMIPcIdle_Master(void);
void HMIPcIdle_Slave(void);
void GetSysProcedure(unsigned char  *pPcProcType, unsigned char  *pHmiProcType);



#endif //__ICANLOGIC_H
