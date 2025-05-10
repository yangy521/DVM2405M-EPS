#ifndef __LPCLOGIC_H
#define __LPCLOGIC_H
#include "KSDSys.h"

#define	AI_LOST_CHK_DELAY_TIME 2000

void LocalDO(void);
void LocalDI(void);
void DOProcess(void);
void EncoderCurrentCheck(void);
extern void MCL_SetFault(u16 hFault_type);
#endif
