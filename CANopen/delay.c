#include "stm32f37x.h"

static u8  fac_us=0;//us延时倍乘数
static u16 fac_ms=0;//ms延时倍乘数


/****************************************************************************
* 名称：delay_init(void)
* 功能：初始化延迟函数
* 入口参数：无
* 出口参数：无
****************************************************************************/
void delay_init(void)
{
//  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
//  fac_us=SystemCoreClock/8000000;	//为系统时钟的1/8 
//  fac_ms=(u16)fac_us*1000;//代表每个ms需要的systick时钟数
}

/****************************************************************************
* 名称：delay_us(u32 nus)
* 功能：延时nus
* 入口参数：nus 要延时的us数.
* 出口参数：无
****************************************************************************/
void delay_us(u32 nus)
{		
  u32 temp;	    	 
//  SysTick->LOAD=nus*fac_us; //时间加载	  		 
//  SysTick->VAL=0x00;        //清空计数器
//  SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //开始倒数	 
//  do
//  {
//    temp=SysTick->CTRL;
//  }
//  while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
//  SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
//  SysTick->VAL =0X00;       //清空计数器	 
}

/****************************************************************************
* 名称：delay_ms(u16 nms)
* 功能：延时nms
* 入口参数：nms 要延时的ms数.
* 出口参数：无
****************************************************************************/
void delay_ms(u16 nms)
{	 		  	  
//  u32 temp;		   
//  SysTick->LOAD=(u32)nms*fac_ms;//时间加载(SysTick->LOAD为24bit)
//  SysTick->VAL =0x00;           //清空计数器
//  SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //开始倒数  
//  do
//  {
//    temp=SysTick->CTRL;
//  }
//  while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
//  SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
//  SysTick->VAL =0X00;       //清空计数器	  	    
} 