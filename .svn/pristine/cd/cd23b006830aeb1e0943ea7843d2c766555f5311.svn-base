#include "Device.h" 

  //????????????  TIM1??1  
#define  LEFTCAPTURECHANNEL TIM1, TIM_IT_CC1  
#define  LEFTCAPTUREVALUE TIM_GetCapture1(TIM1)  
//<span style="font-family: Arial, Helvetica, sans-serif;">TIM1??4</span>  
#define  RIGHTCAPTURECHANNEL TIM1, TIM_IT_CC4  
#define  RIGHTCAPTUREVALUE TIM_GetCapture4(TIM1)  

void MeaSpeedInit(void)  
{  
      //????  
  GPIO_InitTypeDef WheelGPIO_InitStructure;  
  NVIC_InitTypeDef WheelNVIC_InitStructure;  
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef  TIM_ICInitStructure;  
      
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);  
      
      //????????????? ?? 10000  
  TIM_TimeBaseStructure.TIM_Period = 65535;   
  TIM_TimeBaseStructure.TIM_Prescaler = 7200-1;  
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;  
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  
    /**************????******************/  
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;  
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;  
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;  
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;  
  TIM_ICInitStructure.TIM_ICFilter = 0x0f;  
      
      //???????????? PA8  
  WheelGPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;  
  WheelGPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  
  WheelGPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  
  GPIO_Init(GPIOA, &WheelGPIO_InitStructure);  
      
    TIM_ICInit(TIM1, &TIM_ICInitStructure);  
    TIM_ITConfig(TIM1, TIM_IT_CC1, ENABLE);   
/**************??????******************/  
  
    /**************????******************/  
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;  
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;  
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;  
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;  
  TIM_ICInitStructure.TIM_ICFilter = 0x0f;  
      
      //???????????? PA11  
  WheelGPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;  
  WheelGPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  
  WheelGPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  
  GPIO_Init(GPIOA, &WheelGPIO_InitStructure);  
      
    TIM_ICInit(TIM1, &TIM_ICInitStructure);  
    TIM_ITConfig(TIM1, TIM_IT_CC4, ENABLE);   
/**************??????******************/  
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
  WheelNVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;  
  WheelNVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
  WheelNVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
  WheelNVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
  NVIC_Init(&WheelNVIC_InitStructure);  
  
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);  
  TIM_Cmd(TIM1, ENABLE);  
      
} 
// /* 
// ??????????????  ?stm32f10x-it.c??TIMx_IRQHandler()????? 
// */  
// void WheelCaptureIRQ(void)  
// {  
//   if(TIM_GetITStatus(LEFTCAPTURECHANNEL) == SET)   
//   {  
//         speed_contiue=100;  
//     TIM_ClearITPendingBit(LEFTCAPTURECHANNEL);  
//     if(LeftWheelCaptureTime == 0)  
//     {  
//       LeftWheel1stCapture = LEFTCAPTUREVALUE;  
//       LeftWheelCaptureTime = 1;  
//     }  
//     else if(LeftWheelCaptureTime == 1)  
//     {  
//       LeftWheel2ndCapture = LEFTCAPTUREVALUE;   
//       if (LeftWheel2ndCapture > LeftWheel1stCapture)  
//       {  
//         LeftWheelPulsePeriod = (LeftWheel2ndCapture - LeftWheel1stCapture);   
//       }  
//       else  
//       {  
//         LeftWheelPulsePeriod = ((0xFFFF - LeftWheel1stCapture) + LeftWheel2ndCapture);   
//       }  
//             LeftPeriodBuf[LeftPeriodIndex++] = LeftWheelPulsePeriod;//?????10??  
//             if(LeftPeriodIndex == PERIOD_BUFSIZE)   
//                 LeftPeriodIndex = 0;  
//       LeftWheelCaptureTime= 0;  
//     }  
//   }  
//       
//      if(TIM_GetITStatus(RIGHTCAPTURECHANNEL) == SET)   
//   {  
//         speed_contiue=100;  
//     TIM_ClearITPendingBit(RIGHTCAPTURECHANNEL);  
//     if(RightWheelCaptureTime == 0)  
//     {  
//       RightWheel1stCapture = RIGHTCAPTUREVALUE;  
//       RightWheelCaptureTime = 1;  
//     }  
//     else if(RightWheelCaptureTime == 1)  
//     {  
//       RightWheel2ndCapture = RIGHTCAPTUREVALUE;   
//       if (RightWheel2ndCapture > RightWheel1stCapture)  
//       {  
//         RightWheelPulsePeriod = (RightWheel2ndCapture - RightWheel1stCapture);   
//       }  
//       else  
//       {  
//         RightWheelPulsePeriod = ((0xFFFF - RightWheel1stCapture) + RightWheel2ndCapture);   
//       }  
//             RightPeriodBuf[RightPeriodIndex++] = RightWheelPulsePeriod;//?????10??  
//             if(RightPeriodIndex == PERIOD_BUFSIZE) RightPeriodIndex = 0;  
//       RightWheelCaptureTime= 0;  
//     }  
//   }  
// }  

// unsigned int GetLeftSpeed(void)  
// {  
//     int index,intex_temp=0;  
//     uint16_t LeftPeriodBufTemp[PERIOD_BUFSIZE];  
//     u8 max_index=0,min_index=0;  
//     uint16_t LeftValueTemp=0;  
//     unsigned int LeftValueAvg=0;//???  
//     u8 index_total=0;  
//     //????????????????  
//     for(index = LeftPeriodIndex;index < PERIOD_BUFSIZE ;index++)  
//     {  
//         LeftPeriodBufTemp[intex_temp++] = LeftPeriodBuf[index];  
//     }  
//     for(index = 0;index < LeftPeriodIndex ;index++)  
//     {  
//         LeftPeriodBufTemp[intex_temp++] = LeftPeriodBuf[index];  
//     }     
//       
//     //?????????  
//     LeftValueTemp = LeftPeriodBufTemp[0];  
//     for(index = 0;index < PERIOD_BUFSIZE-1; index++)  
//     {  
//         if(LeftValueTemp < LeftPeriodBufTemp[index+1])  
//         {  
//             max_index = index+1;  
//             LeftValueTemp = LeftPeriodBufTemp[index+1];  
//         }  
//     }  
//     //?????????  
//     LeftValueTemp = LeftPeriodBufTemp[0];  
//     for(index = 0;index < PERIOD_BUFSIZE-1; index++)  
//     {  
//         if(LeftValueTemp > LeftPeriodBufTemp[index+1])  
//         {  
//             min_index = index+1;  
//             LeftValueTemp = LeftPeriodBufTemp[index+1];  
//         }  
//     }  
//       
//     //????????? ??????  
//     for(index = 0;index < PERIOD_BUFSIZE;index++)  
//     {  
//         if((index != min_index) && (index != max_index))  
//         {  
//             LeftValueAvg += LeftPeriodBufTemp[index]*(index+1);  
//             index_total += index+1;  
//         }  
//     }  
//     LeftValueAvg = LeftValueAvg/index_total;//????  
//       
//     for(index = 0;index < PERIOD_BUFSIZE;index++)  
//     {  
//         printf("%d\t",LeftPeriodBufTemp[index]);  
//     }     
//       
//     if(LeftValueAvg == 0) return 0;  
//     LeftValueAvg = 10445/LeftValueAvg;  
//     printf("\t%d\r\n",LeftValueAvg);  
//     return LeftValueAvg;  
// }  
//   
// unsigned int GetRightSpeed(void)  
// {  
//     int index,intex_temp=0;  
//     uint16_t RightPeriodBufTemp[PERIOD_BUFSIZE];  
//     u8 max_index=0,min_index=0;  
//     uint16_t RightValueTemp=0;  
//     unsigned int RightValueAvg=0;//???  
//     u8 index_total=0;  
//       
//     //????????????????  
//     for(index = RightPeriodIndex;index < PERIOD_BUFSIZE ;index++)  
//     {  
//         RightPeriodBufTemp[intex_temp++] = RightPeriodBuf[index];  
//     }  
//     for(index = 0;index < RightPeriodIndex ;index++)  
//     {  
//         RightPeriodBufTemp[intex_temp++] = RightPeriodBuf[index];  
//     }     
//       
//     //?????????  
//     RightValueTemp = RightPeriodBufTemp[0];  
//     for(index = 0;index < PERIOD_BUFSIZE-1; index++)  
//     {  
//         if(RightValueTemp < RightPeriodBufTemp[index+1])  
//         {  
//             max_index = index+1;  
//             RightValueTemp = RightPeriodBufTemp[index+1];  
//         }  
//     }  
//     //?????????  
//     RightValueTemp = RightPeriodBufTemp[0];  
//     for(index = 0;index < PERIOD_BUFSIZE-1; index++)  
//     {  
//         if(RightValueTemp > RightPeriodBufTemp[index+1])  
//         {  
//             min_index = index+1;  
//             RightValueTemp = RightPeriodBufTemp[index+1];  
//         }  
//     }  
//       
//     //????????? ??????  
//     for(index = 0;index < PERIOD_BUFSIZE;index++)  
//     {  
//         if((index != min_index) && (index != max_index))  
//         {  
//             RightValueAvg += RightPeriodBufTemp[index]*(index+1);  
//             index_total += index+1;  
//         }  
//     }  
//     RightValueAvg = RightValueAvg/index_total;//????  
//     if(RightValueAvg == 0) return 0;  
//     RightValueAvg = 10445/RightValueAvg;  
//     return RightValueAvg;  
// }  
