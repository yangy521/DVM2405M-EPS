/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : MC_type.h
* Author             : IMS Systems Lab 
* Date First Issued  : 21/11/07
* Description        : This header file provides structure type definitions that 
*                      are used throughout this motor control library.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MC_TYPE_H
#define __MC_TYPE_H

/* Includes ------------------------------------------------------------------*/

#include "KSDsys.h"
#include <stm32g473xx.h>

/* Exported types ------------------------------------------------------------*/

#define U8_MAX     ((u8)255)
#define S8_MAX     ((s8)127)
#define S8_MIN     ((s8)-128)
#define U16_MAX    ((u16)65535u)
#define S16_MAX    ((s16)32767)
#define S16_MIN    ((s16)-32768)
#define U32_MAX    ((u32)4294967295uL)
#define S32_MAX    ((s32)2147483647)
#define S32_MIN    ((s32)-2147483648)

/******************** SPEED PID-CONTROLLER INIT VALUES************************/

/* default values for Speed control loop */
#define PID_SPEED_REFERENCE_RPM   (s16)900 
#define PID_SPEED_KP_DEFAULT      (s16)400
#define PID_SPEED_KI_DEFAULT      (s16)200//80
#define PID_SPEED_KD_DEFAULT      (s16)0

/* Speed PID parameter dividers          */
#define SP_KPDIV ((u16)(16))
#define SP_KIDIV ((u16)(256))
#define SP_KDDIV ((u16)(16))

/* default values for Torque control loop */
#define PID_TORQUE_REFERENCE   (s16)5000   //(N.b: that's the reference init  
                                       //value in both torque and speed control)
#define PID_TORQUE_KP_DEFAULT  (s16)8192//2865//15000
#define PID_TORQUE_KI_DEFAULT  (s16)512//175//4000
#define PID_TORQUE_KD_DEFAULT  (s16)0

/* default values for Flux control loop */
#define PID_FLUX_REFERENCE   (s16)0
#define PID_FLUX_KP_DEFAULT  (s16)8192//2865//15000
#define PID_FLUX_KI_DEFAULT  (s16)512//175//4000
#define PID_FLUX_KD_DEFAULT  (s16)0  

// Toruqe/Flux PID  parameter dividers
#define TF_KPDIV ((u16)(8192))
#define TF_KIDIV ((u16)(4096))
#define TF_KDDIV ((u16)(8192))

typedef struct 
{  
  s16 hKp_Gain;
  u16 hKp_Divisor;
  s16 hKi_Gain;
  u16 hKi_Divisor;  
  s16 hLower_Limit_Output;     //Lower Limit for Output limitation
  s16 hUpper_Limit_Output;     //Lower Limit for Output limitation
  s32 wLower_Limit_Integral;   //Lower Limit for Integral term limitation
  s32 wUpper_Limit_Integral;   //Lower Limit for Integral term limitation
  s32 wIntegral;
  // Actually used only if DIFFERENTIAL_TERM_ENABLED is enabled in
  //stm32f10x_MCconf.h
  s16 hKd_Gain;
  u16 hKd_Divisor;
  s32 wPreviousError;
} PID_Struct_t;


typedef enum 
{
NO_FAULT, OVER_VOLT, UNDER_VOLT
} BusV_t;


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __MC_TYPE_H */
/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
