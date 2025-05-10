/*******************************************************************************
* FileName: CanOpen_HangChaApp.c
* Description:  杭叉通用APP文件
* Input: 
* Output: 
*
* Author: Young
* Date: 2024-02-23
* Revision: V1.0
*******************************************************************************/
#include "Device.h"
#include "CommonRam.h" 
#include "CanOpen_QexpandAgvV04.h"
#include "CanOpen_HangChaApp.h"
#include  <stdlib.h>
#include  <ctype.h>
#include  <string.h>
#include  <time.h>
#include  <stdio.h>

#if(USER_TYPE == USER_HANGCHA_DDTBC_STEER)

#define DATA_TYPE_MASK            (1 << 8)
#define DATA_TYPE_HEX             (0 << 8)
#define DATA_TYPE_BCD             (1 << 8)

const wchar_t ErrorUnicode[][10] ={ {0x53cd, 0x9988, 0x8d85, 0x901f},													 /*** 1 反馈超速***/ 
									{0x5185, 0x6838, 0x9519, 0x8bef},  													 /*** 2 内核错误***/
									{0x8fc7, 0x8f7d, 0x9519, 0x8bef},  											   		 /*** 3 过载错误***/
									{0x8ddf, 0x8e2a, 0x8d85, 0x9650, 0x9519, 0x8bef},									 /*** 4 跟踪超限错误***/
									{0},  																				 /*** 5 *******/
									{0x901f, 0x5ea6, 0x8d85, 0x9650},   												 /*** 6 速度超限***/
									{0x8f6c, 0x77e9, 0x8d85, 0x9650},  													 /*** 7 转矩超限***/
									{0x4f4d, 0x7f6e, 0x6307, 0x4ee4, 0x9519, 0x8bef},   								 /*** 8 位置指令错误***/													
									{0},  																				 /*** 9  *********/
									{0},																				 /*** 10 *********/
									{0x4e24, 0x5206, 0x949f, 0x7535, 0x6d41, 0x4fdd ,0x62a4},   						 /*** 11 两分钟电流保护***/
									{0x63a7, 0x5236, 0x5668, 0x8fc7, 0x6d41},   										 /*** 12 控制器过流***/
									{0x6bcd, 0x7ebf, 0x7535, 0x5bb9, 0x5145, 0x7535, 0x6545, 0x969c},   				 /*** 13 母线电容充电故障***/
									{0x7ee7, 0x7535, 0x5668, 0x8fde, 0x63a5, 0x6545, 0x969c},   						 /*** 14 继电器连接故障***/
									{0},   																				 /*** 15 ******/
									{0x6b20, 0x538b, 0x9519, 0x8bef},   												 /*** 16 欠压错误***/
									{0x7535, 0x6c60, 0x7535, 0x538b, 0x4e25, 0x91cd, 0x8fc7, 0x9ad8},  					 /*** 17 电池电压严重过高***/
									{0x529f, 0x7387, 0x677f, 0x4e25, 0x91cd, 0x8fc7, 0x6e29},  							 /*** 18 功率板严重过温***/
									{0},   																				 /*** 19 ******/
									{0x6307, 0x4ee4, 0x7535, 0x538b, 0x9519, 0x8bef},   								 /*** 20 指令电压错误***/
									{0},   																				 /*** 21 ******/
									{0x8f93, 0x51fa, 0x4e94, 0x4f0f, 0x6545, 0x969c},  								  	 /*** 22 输出五伏故障***/
									{0x8282, 0x70b9, 0x68c0, 0x6d4b, 0x5931, 0x8d25},   								 /*** 23 节点检测失败***/
									{0x7ee7, 0x7535, 0x5668, 0x9a71, 0x52a8, 0x9519, 0x8bef},  							 /*** 24 继电器驱动错误***/
									{0},   																				 /*** 25 *****/
									{0x7535, 0x673a, 0x77ed, 0x8def},  													 /*** 26 电机短路***/
									{0x5bfb, 0x96f6, 0x9519, 0x8bef},   												 /*** 27 寻零错误***/
									{0x4f4d, 0x7f6e, 0x6307, 0x4ee4, 0x4f20, 0x611f, 0x5668, 0x9519, 0x8bef},			 /*** 28 位置指令传感器错误***/																																/*** 28 位置指令传感器错误***/
									{0x5fc3, 0x8df3, 0x9519, 0x8bef},   												 /*** 29 心跳错误***/
									{0},  																				 /*** 30 ***/
									{0}, 																				 /*** 31 ***/
									{0},   																				 /*** 32 ***/	
									{0x529f, 0x7387, 0x677f, 0x4f4e, 0x6e29},   										 /*** 33 功率板低温***/	
									{0},   																				 /*** 34 ***/	
									{0},  																				 /*** 35 ***/	
									{0},   																				 /*** 36 ***/	
									{0},  																				 /*** 37 ***/	
									{0x8bfb, 0x5199, 0x53c2, 0x6570, 0x9519, 0x8bef},   								 /*** 38 读写参数错误***/	
									{0x53c2, 0x6570, 0x8d85, 0x9650, 0x9519, 0x8bef},  	 								 /*** 39 参数超限错误***/	
									{0x53c2, 0x6570, 0x5e8f, 0x53f7, 0x8d85, 0x9650},  									 /*** 40 参数序号超限***/
									{0x529f, 0x7387, 0x677f, 0x8f7b, 0x5ea6, 0x8fc7, 0x6e29},  							 /*** 41 功率板轻度过温***/
									{0},  																				 /*** 42 ***/
									{0x53c2, 0x6570, 0x81ea, 0x5b66, 0x4e60, 0x63d0, 0x793a},  							 /*** 43 参数自学习提示***/
									{0x53c2, 0x6570, 0x81ea, 0x5b66, 0x4e60, 0x9519, 0x8bef},  							 /*** 44 参数自学习错误***/																				
};
const char ErrorAscii[][28] = { {0x46, 0x65, 0x65, 0x64, 0x62, 0x61, 0x63, 0x6B, 0x20, 0x4F, 0x76, 0x65, 0x72, 0x73, 0x70, 0x65, 0x65, 0x64},											/*** 1 Feedback Overspeed***/ 
								{0x4B, 0x65, 0x72, 0x6E, 0x65, 0x6C, 0x20, 0x45, 0x72, 0x72, 0x6F, 0x72},																				/*** 2 Kernel Error***/ 
								{0x4F, 0x76, 0x65, 0x72, 0x6C, 0x6F, 0x61, 0x64, 0x20, 0x45, 0x72, 0x72, 0x6F, 0x72},																	/*** 3 Overload Error***/ 
								{0x54, 0x72, 0x61, 0x63, 0x65, 0x20, 0x4F, 0x76, 0x65, 0x72, 0x72, 0x75, 0x6E, 0x20, 0x45, 0x72, 0x72, 0x6F, 0x72},										/*** 4 Trace Overrun Rrror***/ 
								{0x00},  								 																												/*** 5 ***/ 
								{0x53, 0x70, 0x65, 0x65, 0x64, 0x20, 0x4f, 0x76, 0x65, 0x72, 0x72, 0x75, 0x6e}, 																		/*** 6 Speed Overrun***/ 
								{0x54, 0x6f, 0x72, 0x71, 0x75, 0x65, 0x20, 0x4f, 0x76, 0x65, 0x72, 0x72, 0x75, 0x6e},  																	/*** 7 Torque Overrun***/ 
								{0x50, 0x6F, 0x73, 0x69, 0x74, 0x69, 0x6F, 0x6E, 0x20, 0x43, 0x6D, 0x64, 0x20, 0x45, 0x72, 0x72, 0x6F, 0x72},  											/*** 8 Position Cmd Error***/ 
								{0x00},  																																				/*** 9  None***/ 
								{0x00},  																																				/*** 10 None***/ 
								{0x32, 0x6D, 0x69, 0x6E, 0x20, 0x43, 0x75, 0x72, 0x72, 0x65, 0x6E, 0x74, 0x20, 0x50, 0x72, 0x6F, 0x74, 0x65, 0x63, 0x74, 0x73},  				   		/*** 11 2min Current Protects***/ 
								{0x43,0x6F,0x6E,0x74,0x72,0x6F,0x6C,0x6C,0x65,0x72,0x20,0x4F,0x76,0x65,0x72,0x63,0x75,0x72,0x72,0x65,0x6E,0x74},  										/*** 12 Controller Overcurrent***/ 
								{0x42,0x75,0x73,0x20,0x43,0x61,0x70,0x61,0x63,0x69,0x74,0x6F,0x72,0x20,0x43,0x68,0x61,0x72,0x67,0x69,0x6E,0x67,0x20,0x45,0x72,0x72},  					/*** 13 Bus Capacitor Charging Err***/ 
								{0x52, 0x65, 0x6C, 0x61, 0x79, 0x20, 0x43, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x73, 0x20, 0x46, 0x61, 0x69, 0x6C, 0x75, 0x72, 0x65},  		    		/*** 14 Relay Connects Failure***/ 
								{0x00},  																																				/*** 15 None***/ 
								{0x55, 0x6E, 0x64, 0x65, 0x72, 0x76, 0x6F, 0x6C, 0x74, 0x61, 0x67, 0x65, 0x20, 0x45, 0x72, 0x72, 0x6F, 0x72},  											/*** 16 Undervoltage Error***/ 
								{0x48, 0x69, 0x67, 0x68, 0x20, 0x42, 0x61, 0x74, 0x74, 0x65, 0x72, 0x79, 0x20, 0x56, 0x6F, 0x6C, 0x74, 0x61, 0x67, 0x65},  								/*** 17 High Battery Voltage***/ 
								{0x50,0x6F,0x77,0x65,0x72,0x42,0x6F,0x61,0x72,0x64,0x20,0x4F,0x76,0x65,0x72,0x74,0x6D,0x70,0x20,0x53,0x65,0x72,0x69,0x6F,0x75,0x73,0x6C,0x79},   		/*** 18 PowerBoard Overtmp Seriously***/ 
								{0x00},  																																				/*** 19 None***/ 
								{0x43, 0x6D, 0x64, 0x20, 0x56, 0x6F, 0x6C, 0x74, 0x61, 0x67, 0x65, 0x20, 0x45, 0x72, 0x72, 0x6F, 0x72},  												/*** 20 Cmd Voltage Error***/ 
								{0x00},  																																				/*** 21 None***/ 
								{0x35, 0x56, 0x20, 0x4F, 0x75, 0x74, 0x70, 0x75, 0x74, 0x20, 0x46, 0x61, 0x75, 0x6C, 0x74},  													 		/*** 22 5V Output Fault***/ 
								{0x4D,0x41,0x43,0x49,0x44,0x20,0x44,0x65,0x74,0x65,0x63,0x74,0x69,0x6F,0x6E,0x20,0x46,0x61,0x69,0x6C,0x75,0x72,0x65},  									/*** 23 MACID Detection Failure***/ 
								{0x52, 0x65, 0x6C, 0x61, 0x79, 0x20, 0x44, 0x72, 0x69, 0x76, 0x65, 0x73, 0x20, 0x46, 0x61, 0x75, 0x6C, 0x74},  											/*** 24 Relay Drives Fault***/ 
								{0x00},  																																				/*** 25 None***/ 
								{0x4D, 0x6F, 0x74, 0x6F, 0x72, 0x20, 0x53, 0x68, 0x6F, 0x72, 0x74, 0x20, 0x43, 0x69, 0x72, 0x63, 0x75, 0x69, 0x74},  									/*** 26 Motor Short Circuit***/ 
								{0x5A, 0x65, 0x72, 0x6F, 0x20, 0x53, 0x65, 0x61, 0x72, 0x63, 0x68, 0x20, 0x45, 0x72, 0x72, 0x6F, 0x72},													/*** 27 Zero Search Error***/ 
								{0x50,0x6F,0x73,0x69,0x74,0x69,0x6F,0x6E,0x20,0x43,0x6D,0x64,0x20,0x53,0x65,0x6E,0x73,0x6F,0x72,0x20,0x45,0x72,0x72,0x6F,0x72},							/*** 28 Position Cmd Sensor Error***/  																																																																				  /*** 28 Position Cmd Sensor Error***/ 
								{0x48, 0x65, 0x61, 0x72, 0x74, 0x62, 0x65, 0x61, 0x74, 0x20, 0x45, 0x72, 0x72, 0x6F, 0x72},  															/*** 29 Heartbeat Error***/ 
								{0x00},  													 																							/*** 30 None***/ 
								{0x00}, 																																				/*** 31 None***/ 
								{0x00},  																																				/*** 32 None***/ 
								{0x50,0x6F,0x77,0x65,0x72,0x42,0x6F,0x61,0x72,0x64,0x20,0x4C,0x6F,0x77,0x20,0x54,0x65,0x6D,0x70,0x65,0x72,0x61,0x74,0x75,0x72,0x65},   			 		/*** 33 PowerBoard Low Temperature***/ 
								{0x00},  													 																							/*** 34 None***/ 
								{0x00},  													 																							/*** 35 None***/
								{0x00},  																																				/*** 36 None***/ 
								{0x00},  																																				/*** 37 Nne***/ 
								{0x52,0x57,0x20,0x50,0x61,0x72,0x61,0x6D,0x65,0x74,0x65,0x72,0x73,0x20,0x41,0x72,0x65,0x20,0x49,0x6E,0x63,0x6F,0x72,0x72,0x65,0x63,0x74},  				/*** 38 RW Parameters Are Incorrect***/
								{0x50,0x61,0x72,0x61,0x6D,0x65,0x74,0x65,0x72,0x20,0x4C,0x69,0x6D,0x69,0x74,0x20,0x45,0x72,0x72,0x6F,0x72},  											/*** 39 Parameter Limit Error***/
								{0x50,0x61,0x72,0x61,0x20,0x4E,0x75,0x6D,0x62,0x65,0x72,0x20,0x45,0x78,0x63,0x65,0x65,0x64,0x73,0x20,0x4C,0x69,0x6D,0x69,0x74},  						/*** 40 Para Number Exceeds Limit***/
								{0x50,0x6F,0x77,0x65,0x72,0x62,0x6F,0x61,0x72,0x64,0x20,0x4F,0x54,0x20,0x53,0x6C,0x69,0x67,0x68,0x74,0x6C,0x79},										/*** 41 Powerboard OT Slightly***/
								{0x00},  																																				/*** 42 None***/
								{0x50, 0x61, 0x72, 0x61, 0x20, 0x4C, 0x65, 0x61, 0x72, 0x6E, 0x20, 0x50, 0x72, 0x6F, 0x6D, 0x70, 0x74, 0x73},  											/*** 43 Para Learn Prompts***/ 
								{0x50, 0x61, 0x72, 0x61, 0x20, 0x4C, 0x65, 0x61, 0x72, 0x6E, 0x20, 0x45, 0x72, 0x72, 0x6F, 0x72},														/*** 44 Para Learn Error***/ 																									
};

const INT16U HANGCHA_SDOTAB[256]=
{
// 00,  01,  02,  03,  04,  05, 06,   07,  08,  09,
	0,	1,	2,	3,	4,	5,	6,	7,	8,	9,
	10,	11,	12,	13,	14,	15,	16,	17,	18,	19,
	20,	21,	22,	23,	24,	25,	26,	27,	28,	29,
	30,	31,	32,	33,	34,	35,	36,	37,	38,	39,
	40,	41,	42,	43,	44,	45,	46,	47,	48,	49,
	50,	51,	52,	53,	54,	55,	56,	57,	58,	59,
	60,	61,	62,	63,	64,	65,	66,	67,	68,	69,
	70,	71,	72,	73,	74,	75,	76,	77,	78,	79,
	80,	81,	82,	83,	84,	85,	86,	87,	88,	89,
	90,	91,	92,	93,	94,	95,	96,	97,	98,	99,
	100,	101,	102,	103,	104,	105,	106,	107,	108,	109,
	110,	111,	112,	113,	114,	115,	116,	117,	118,	119,
	120,	121,	122,	123,	124,	125,	126,	127,	128,	129,
	130,	131,	132,	133,	134,	135,	136,	137,	138,	139,
	140,	141,	142,	143,	144,	145,	146,	147,	148,	149,
	150,	151,	152,	153,	154,	155,	156,	157,	158,	159,
	160,	161,	162,	163,	164,	165,	166,	167,	168,	169,
	170,	171,	172,	173,	174,	175,	176,	177,	178,	179,
	180,	181,	182,	183,	184,	185,	186,	187,	188,	189,
	190,	191,	192,	193,	194,	195,	196,	197,	198,	199,
	200,	201,	202,	203,	204,	205,	206,	207,	208,	209,
	210,	211,	212,	DATA_TYPE_BCD|213,	DATA_TYPE_BCD|214,	DATA_TYPE_BCD|215,	216,	217,	218,	219,
	220,	221,	222,	223,	224,	225,	226,	227,	228,	229,
	230,	231,	232,	233,	234,	235,	236,	237,	238,	239,
	240,	241,	242,	243,	244,	245,	246,	247,	248,	249,
	250,	251,	252,	253,	254,	255	
};
const INT16S K_XISHU[210]=
{
	1,	1,	1,	1,	1,	100,	100,	10,	100,	1,	100,	100,	1,	1,	1,	1,	1,	1,	1,	1,	1,			//0~20
	1,	1,	1,	1,	1,	1, 32767,  1,  1,  1,  1,  1,  32767,  32767,  1,  1,  1,  1,  1,  1,  1,			//21~41
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,			//42~62
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,			//63~83
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,			//84~104
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,			//105~125
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,																											
};
const INT16S K_CHU_XISHU[210]=
{
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,  1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,			//0~20
	1,	1,	1,	1,	1,	1,	100,  1,  1,  1,  1,  1,  100,  100,  1,  1,  1,  1,  1,  1,  1,			//21~41
	1,	10,	10,	10,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,			//42~62
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,			//63~83
	5,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,			//84~104
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,			//105~125
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,																											
};
const INT16S B_XISHU[210]=
{
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,  0,	0,	900,	0,	0,	0,	0,	0,	0,	0,	0,			//0~20
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,  0,	0,	0,	0,	0,	0,	0,	0,			//21~41
	0,	0,  0,	0,	0,	0,	0,	0,	0,  -16384,	-16384,	0,	0,	0,	0,	0,	0,	0,	10000,	0,	0,			//42~62
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,			//63~83
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,			//84~004
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,			//005~025
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,																											
};

static const INT8U SpecialBitArr[4]= {3, 4, 190};
/*******************************************************************************
* FunctionName: ReceiveAPPDataUpdatePro
* Description:  下发APP报文时， 模拟SDO进行的解析与发送
* Input: tHANGCHAAPP_PDO *pCanopenPDO
* Output: 
*
* Author: Young
* Date: 2023-02-23
* Revision: V1.0
*******************************************************************************/
void ReceiveAPPDataUpdatePro(tHANGCHAAPP_PDO *pCanopenPDO)
{
	char ReplaceChar1[4] = "";
	char ParseKeyFour[4];
	char *getString = CONTROLLER_TYPE;
	char tempword[20] = "";
	static INT16U Bitdelay = 0;
	static INT8U bitcount = 0;
	static INT8U temp = 0;	
	/*****握手-加密-查询****/
	//上电第一次握手
	if((pCanopenPDO->CanBufRxState & RX670_CANBUFRXSTATE) != 0)
	{
		pCanopenPDO->HandshakeFlag = pCanopenPDO->CanBuf_ID670R[0];
		pCanopenPDO->SelectLanguage = pCanopenPDO->CanBuf_ID670R[4];
		pCanopenPDO->CanBufRxState &= ~RX670_CANBUFRXSTATE;
	    pCanopenPDO->NumCount = 0;
	}
	if(Bitdelay < 1000 / T_MS_PLC_PERIOD)
	{
		Bitdelay++;
	}
	else
	{
		if(bitcount < 9)  //上电后先将所有bit控制位读出并存储
		{
			pCanopenPDO->ReadBitFlag = true;
			pCanopenPDO->DgnDataRxTx.Q_AFlag |= RDOP_FLAG;
			gPLCCtl.RemoteParaRdWrIndex = SpecialBitArr[bitcount];	
			gPLCCtl.RemoteParaRdWrFlag |= RDREQ_RemoteParaRdWrFlag;		
			bitcount++;
		}
		if(pCanopenPDO->ReadBitFlag)
		{
			if ((pCanopenPDO->DgnDataRxTx.Q_AFlag & RDOP_FLAG) != 0)
			{	
				if ((gPLCCtl.RemoteParaRdWrFlag & RDRDY_RemoteParaRdWrFlag) != 0)
				{
					pCanopenPDO->OriginalBitVal1[temp] = gPLCCtl.RemoteParaRdWrData;
					temp++;
					pCanopenPDO->ReadBitFlag = false;
					gPLCCtl.RemoteParaRdWrFlag &= ~RDRDY_RemoteParaRdWrFlag;
				}
			}
		}
	}	
	if((pCanopenPDO->DgnDataRxTx.Q_AFlag & (RX_FLAG | RDOP_FLAG | WROP_FLAG | TX_FLAG)) == 0)//查询 & 配置	  //DATA from DGN
	{
		if ((pCanopenPDO->CanBufRxState & RX651_CANBUFRXSTATE) != 0)
		{
			pCanopenPDO->DgnDataRxTx.FuncCode = pCanopenPDO->CanBuf_ID651R[0];
			pCanopenPDO->DgnDataRxTx.Index = (pCanopenPDO->CanBuf_ID651R[1] & 0xFF) | (pCanopenPDO->CanBuf_ID651R[2] << 8);
			pCanopenPDO->DgnDataRxTx.SubIndex = pCanopenPDO->CanBuf_ID651R[3];
			pCanopenPDO->DgnDataRxTx.DataL16 = (pCanopenPDO->CanBuf_ID651R[4] & 0xFF) | (pCanopenPDO->CanBuf_ID651R[5] << 8);
			pCanopenPDO->DgnDataRxTx.DataH16 = (pCanopenPDO->CanBuf_ID651R[6] & 0xFF) | (pCanopenPDO->CanBuf_ID651R[7] << 8);
			pCanopenPDO->CanBufRxState &= ~RX651_CANBUFRXSTATE;
			pCanopenPDO->DgnDataRxTx.Q_AFlag |= RX_FLAG;
			IndexToAddress();
			
//			if((pCanopenPDO->DgnDataRxTx.SubIndex >= 0x53) && (pCanopenPDO->DgnDataRxTx.SubIndex <= 0x5B))
//			{
//				pCanopenPDO->TempCnt += 1;
//				pCanopenPDO->TempArr[pCanopenPDO->TempCnt] = pCanopenPDO->DgnDataRxTx.SubIndex;
//			}
			
			if (pCanopenPDO->DgnDataRxTx.FuncCode == READ_REQUIR_DGNFUNC)		//40
			{
				//连接请求
				if(pCanopenPDO->DgnDataRxTx.Index == DGN_CONNECT_REQ_INDEX)  //0x1F52
				{
					pCanopenPDO->DgnDataRxTx.FuncCode = READ_ANSWER_DGNFUNC;
					switch(pCanopenPDO->DgnDataRxTx.SubIndex)
					{
						case DGN_CONNECT_REQ_SUBINDEX:		//请求连接
							if(pCanopenPDO->GeneratePwdFlag == 0)
							{
								vGetRandPwd(pCanopenPDO,4);
							}
							pCanopenPDO->DgnDataRxTx.DataL16 = ((pCanopenPDO->RandPwdArr[0] & 0x00FF)| ((pCanopenPDO->RandPwdArr[1] << 8) & 0xFF00));
							pCanopenPDO->DgnDataRxTx.DataH16 = ((pCanopenPDO->RandPwdArr[2] & 0x00FF)| ((pCanopenPDO->RandPwdArr[3] << 8) & 0xFF00));	 							
							pCanopenPDO->DgnDataRxTx.SynFlag = 2;
							break;
						case DGN_CAR_TYPE_SUBINDEX: //查询车型   //预留功能
							pCanopenPDO->DgnDataRxTx.SynFlag = 9;
							break;
						case DGN_MENU_ID_SUBINDEX:	//查询菜单标识
							pCanopenPDO->DgnDataRxTx.DataL16 = 0x0;
							pCanopenPDO->DgnDataRxTx.DataH16 = 0;
							pCanopenPDO->DgnDataRxTx.SynFlag = 10;
							break;						
						case DGN_MENU_TYPE_SUBINDEX:	//查询菜单类型
							pCanopenPDO->DgnDataRxTx.DataL16 = 0x02;
							pCanopenPDO->DgnDataRxTx.DataH16 = 0x0100;
							pCanopenPDO->DgnDataRxTx.SynFlag = 11;
							break;	
					}
				}
				else if(pCanopenPDO->DgnDataRxTx.Index == DGN_QUERY_AUTO_INDEX)  //1018
				{
					pCanopenPDO->DgnDataRxTx.FuncCode = READ_ANSWER_DGNFUNC;
					if(pCanopenPDO->DgnDataRxTx.SubIndex <= 0x0C) //子索引在表中则查表  不在则终止查询
					{
						/**特殊查询***/
						switch(pCanopenPDO->DgnDataRxTx.SubIndex)
						{
							case QUERY_CONTROLLER_TYPE_F4:
								memcpy(tempword,getString,8);
								pCanopenPDO->DgnDataRxTx.DataL16 = (tempword[0] & 0xFF) | ((tempword[1] << 8) & 0xFF00);
								pCanopenPDO->DgnDataRxTx.DataH16 = (tempword[2] & 0xFF) | ((tempword[3] << 8) & 0xFF00);	
								pCanopenPDO->DgnDataRxTx.SynFlag = 5;//保持原样 回复0
								break;
							case QUERY_CONTROLLER_TYPE_B4:
							{  
								memcpy(tempword,getString,8);
							//	 strcpy(tempword, STRINGIFY(DRIVER_TYPE));
								pCanopenPDO->DgnDataRxTx.DataL16 = (tempword[4] & 0xFF) | ((tempword[5] << 8) & 0xFF00);
								pCanopenPDO->DgnDataRxTx.DataH16 = (tempword[6] & 0xFF) | ((tempword[7] << 8) & 0xFF00);					 
								pCanopenPDO->DgnDataRxTx.SynFlag = 6;
								break;
							}
							case QUERY_CONTROLLER_SN:
								pCanopenPDO->DgnDataRxTx.DataH16 = 0x0100;
								pCanopenPDO->DgnDataRxTx.SynFlag = 7;							
								break;
							case QUERY_APP_SOFT_VERSION:
								pCanopenPDO->DgnDataRxTx.DataL16 = (SOFTVERSION >> 8) | ((SOFTVERSION & 0xFF) << 8);
								
								pCanopenPDO->DgnDataRxTx.SynFlag = 8;
								break;
							default:
								pCanopenPDO->DgnDataRxTx.SynFlag = 12;  //查询其他信息
								break;
						}
					}
					else  //出错
					{
						pCanopenPDO->DgnDataRxTx.SubIndex = 0xFB;
						pCanopenPDO->DgnDataRxTx.DataH16 = 0x80;
					}
				}	
				else if(pCanopenPDO->DgnDataRxTx.Index == DGN_QUERY_ERR_INDEX) //0xFF10
				{
					pCanopenPDO->DgnDataRxTx.FuncCode = READ_ANSWER_DGNFUNC;				
					if(pCanopenPDO->DgnDataRxTx.SubIndex == 0x01) //当前故障请求
					{
						pCanopenPDO->DgnDataRxTx.DataL16 = 0;
						pCanopenPDO->DgnDataRxTx.DataH16 = 0x5D1;
						pCanopenPDO->ErrcodeType = 1;
						pCanopenPDO->DgnDataRxTx.SynFlag = 13;  //故障分包预发送标志
						pCanopenPDO->SendErrFlag = false;
					}
					else if(pCanopenPDO->DgnDataRxTx.SubIndex == 0x02)  //历史故障请求
					{
						static INT8U i = 0, j = 1;
						if(j ==1)
						{
							for(i=0;i<7;i++)
							{
								if(gCRam.ErrorTrace[i] != 0)
								{
									pCanopenPDO->sendcnt+= 1;
								}
							}
							j = 0;
						}
						pCanopenPDO->DgnDataRxTx.DataL16 = pCanopenPDO->sendcnt + 1;//(pCanopenPDO->CurErrNum + 1);  //应该发送的故障数						
						pCanopenPDO->DgnDataRxTx.DataH16 = pCanopenPDO->sendcnt + 1;//(pCanopenPDO->CurErrNum + 1);   //Actually Num
						pCanopenPDO->DgnDataRxTx.SynFlag = 14;  //历史故障第一次预发送标志	
						pCanopenPDO->SendErrFlag = false;
					}
				}
				else if(pCanopenPDO->DgnDataRxTx.Index == PREERROR_PACK_SEND_INDEX)   //FF12
				{
					if(pCanopenPDO->DgnDataRxTx.SubIndex == 0x00)
					{
						pCanopenPDO->DgnDataRxTx.FuncCode = 0x43;
						pCanopenPDO->DgnDataRxTx.DataL16 = 0;
						pCanopenPDO->DgnDataRxTx.DataH16 = 0x5D1;
						pCanopenPDO->ErrcodeType = 2;
						pCanopenPDO->DgnDataRxTx.SynFlag = 15;  //故障分包预发送标志	
					}
				}
				else if(pCanopenPDO->DgnDataRxTx.Index == DGN_STOP_REQ_INDEX)		//FF11
				{
					pCanopenPDO->SendErrFlag = false;
					pCanopenPDO->SubFunID = 0xFF;
					//pCanopenPDO->ReqAnsyFlag = false;
					pCanopenPDO->DgnDataRxTx.Q_AFlag &= ~RX_FLAG;   //此处是为了APP退出当前故障时 发出的一帧退出请求
				}
				else
				{
					pCanopenPDO->SendErrFlag = false;
					/******特殊地址SDO查询********/
				//读取参数或状态
					if( (pCanopenPDO->Address < 256) && (HANGCHA_SDOTAB[pCanopenPDO->Address] != 0))
					{
						if ((pCanopenPDO->Address) < MONITOR_PARA_START)
						{//回读参数/***配置信息时 读取***/
							pCanopenPDO->DgnDataRxTx.Q_AFlag |= RDOP_FLAG;
							gPLCCtl.RemoteParaRdWrFlag |= RDREQ_RemoteParaRdWrFlag;
							gPLCCtl.RemoteParaRdWrIndex = pCanopenPDO->Address;
						}
						else
						{//监控数据
							INT16U MonitorDataVal = 0;
							pCanopenPDO->DgnDataRxTx.FuncCode = READ_ANSWER_DGNFUNC;
							MonitorDataVal = ReadMonitorParaValByIndex(pCanopenPDO->Address);
//							/**********  TEST   MONITOR   PARA  AREA  *****/
//							if(pCanopenPDO->DgnDataRxTx.Index == 0x4001)
//								{
//									if((pCanopenPDO->DgnDataRxTx.SubIndex == 0x0D))// && (pCanopenPDO->DgnDataRxTx.SubIndex <= 0x04))
//									{
//										MonitorDataVal= -52;
//									}
//								}
							/************** END *****************/							
							if ((HANGCHA_SDOTAB[pCanopenPDO->Address] & DATA_TYPE_MASK)  == DATA_TYPE_BCD)
							{
								MonitorDataVal = ((MonitorDataVal >> 0) & 0xF) 
								                 + ((MonitorDataVal >> 4) & 0xF) * 10 
								                 + ((MonitorDataVal >> 8) & 0xF) * 100 
								                 + ((MonitorDataVal >> 12) & 0xF) * 1000; 
							} 		
							pCanopenPDO->DgnDataRxTx.DataH16 = 0;
							pCanopenPDO->DgnDataRxTx.DataL16 = vMonitorParaAdjust(&HangCha_GDC_PDO,MonitorDataVal);  //需要调整监控参数的 返回调整后的值 不需要的 返回原值
							pCanopenPDO->DgnDataRxTx.Q_AFlag |= TX_FLAG;
						}
					}
					else //Index over or para read protect. Silent
					{
						pCanopenPDO->DgnDataRxTx.Q_AFlag &= ~RX_FLAG;
					}
				}	
			}
			else if (pCanopenPDO->DgnDataRxTx.FuncCode == WRITE_REQUIR_DGNFUNC)		//23
			{
				/*** APP回复解码数据 ***/
				if(pCanopenPDO->DgnDataRxTx.Index == DGN_CONNECT_REQ_INDEX)
				{
					switch(pCanopenPDO->DgnDataRxTx.SubIndex)//02 
					{
						case DGN_DECODE_DATA_SUBINDEDX:  //比对解码结果
//						for(parseCnt = 0; parseCnt < 4; parseCnt++)
//						{
 								vGetReplaceChar(pCanopenPDO->RandPwdArr,ReplaceChar1);  //源字符替换
//						} 
							vGenerateKeyPro(ReplaceChar1,ParseKeyFour);		//加密过程处理
							if(1 == iRemoteUnlockPWD(&HangCha_GDC_PDO,ParseKeyFour))  //对比APP解析的密码
							{
								pCanopenPDO->DgnDataRxTx.FuncCode = 0x60;		
							}
							else
							{
								pCanopenPDO->DgnDataRxTx.FuncCode = 0x80;
							}
							pCanopenPDO->DgnDataRxTx.DataH16 = 0;
							pCanopenPDO->DgnDataRxTx.DataL16 = 0;		
							pCanopenPDO->DgnDataRxTx.SynFlag = 3;
							break;
						case DGN_PERMIS_LEVEL_SUBINDEX: //发送使用等级
							pCanopenPDO->DgnDataRxTx.FuncCode = WRITE_ANSWER_DGNFUNC;
							pCanopenPDO->DgnDataRxTx.DataH16  = 0x00;
							pCanopenPDO->DgnDataRxTx.SynFlag = 4;
							break;
					}		
				}		
			}
			else if(pCanopenPDO->DgnDataRxTx.FuncCode == WRITE_SYNCREQ_DGNFUNC)  //0x2B
			{				
				//更改参数
				if ( (pCanopenPDO->Address < MONITOR_PARA_START)
					   && (HANGCHA_SDOTAB[pCanopenPDO->Address] != 0)
				     && (gCRam.bPwmClose == 1)
				)
				{
					//开放修改
					if(pCanopenPDO->BitAddr != -1)  //需要特殊调整的
					{			
						gPLCCtl.RemoteParaRdWrData = iModifyParaAdjust(&HangCha_GDC_PDO);
					}
					else
					{
						gPLCCtl.RemoteParaRdWrData = pCanopenPDO->DgnDataRxTx.DataL16*K_XISHU[pCanopenPDO->XiShu] / K_CHU_XISHU[pCanopenPDO->XiShu] + B_XISHU[pCanopenPDO->XiShu];				
					}
					pCanopenPDO->DgnDataRxTx.Q_AFlag |= WROP_FLAG;
					gPLCCtl.RemoteParaRdWrFlag |= WRREQ_RemoteParaRdWrFlag;
					gPLCCtl.RemoteParaRdWrIndex = pCanopenPDO->Address;					
				}
				else //Index over or para read protect. Silent
				{
					pCanopenPDO->DgnDataRxTx.Q_AFlag &= ~RX_FLAG;
				}				
			}
			else //Illegal FuntId. Silent
			{
				pCanopenPDO->DgnDataRxTx.Q_AFlag &= ~RX_FLAG;
			}
		}
//		else
//		{
//			memset(&pCanopenPDO->DgnDataRxTx,0,sizeof(pCanopenPDO->DgnDataRxTx));
//		}
	}
	
	if ((pCanopenPDO->DgnDataRxTx.Q_AFlag & RDOP_FLAG) != 0)
	{
		if ((gPLCCtl.RemoteParaRdWrFlag & RDRDY_RemoteParaRdWrFlag) != 0)
		{
			//pCanopenPDO->OriginalBitVal = gPLCCtl.RemoteParaRdWrData;  //BIt值回读
			 
			if(!pCanopenPDO->ReadBitFlag)
			{
				if(pCanopenPDO->BitAddr != -1)
				{
					pCanopenPDO->DgnDataRxTx.DataL16 = (gPLCCtl.RemoteParaRdWrData >> pCanopenPDO->BitAddr) & 0x01;	
				}
				else
				{
					pCanopenPDO->DgnDataRxTx.DataL16 =  ((gPLCCtl.RemoteParaRdWrData -B_XISHU[pCanopenPDO->XiShu]) * K_CHU_XISHU[pCanopenPDO->XiShu]) / K_XISHU[pCanopenPDO->XiShu];				
				}
			}
			gPLCCtl.RemoteParaRdWrFlag &= ~RDRDY_RemoteParaRdWrFlag;
			pCanopenPDO->DgnDataRxTx.FuncCode = READ_ANSWER_DGNFUNC;
			pCanopenPDO->DgnDataRxTx.DataH16 = 0;
			pCanopenPDO->DgnDataRxTx.Q_AFlag |= TX_FLAG;
		}
	}

	if ((pCanopenPDO->DgnDataRxTx.Q_AFlag & WROP_FLAG) != 0)
	{
		if ((gPLCCtl.RemoteParaRdWrFlag & WRRDY_RemoteParaRdWrFlag) != 0)
		{
			gPLCCtl.RemoteParaRdWrFlag &= ~WRRDY_RemoteParaRdWrFlag;
			pCanopenPDO->DgnDataRxTx.FuncCode = WRITE_ANSWER_DGNFUNC;
			pCanopenPDO->DgnDataRxTx.DataL16 = 0;
			pCanopenPDO->DgnDataRxTx.DataH16 = 0;
			pCanopenPDO->DgnDataRxTx.Q_AFlag |= TX_FLAG;
		}
	}	
}

//转向控制器定时发送PDO报文
void PDO_Prco_HANGCHA(void)
{
	static INT8U Count=0;
    INT16U CmdAngle = 0;
	tCANFrame canFrame;	//
	
	tHANGCHAAPP_PDO *pCanopenPDO;
	pCanopenPDO = &HangCha_GDC_PDO;
    
    CanOpenUpdatePlcDataFromRxbuf();
	ReceiveAPPDataUpdatePro(&HangCha_GDC_PDO);
	
		//上电第一次握手成功
	if((pCanopenPDO->HandshakeFlag & 0xff) == SHAKE_HANDS_DGNFUNC)
	{
		pCanopenPDO->DgnDataRxTx.FuncCode = 0x01;
		pCanopenPDO->DgnDataRxTx.Index = 0x00;
		pCanopenPDO->DgnDataRxTx.SubIndex = 0x00;
		pCanopenPDO->DgnDataRxTx.DataL16 = 0x04;		//响应上电信息
		pCanopenPDO->DgnDataRxTx.DataH16 = 0x00;  
		pCanopenPDO->HandshakeFlag &= ~SHAKE_HANDS_DGNFUNC;
		pCanopenPDO->DgnDataRxTx.SynFlag = 1;
		pCanopenPDO->SubFunID = 0xFF;
		pCanopenPDO->SendErrFlag = false;
	}
	
	if(pCanopenPDO->SendErrFlag == true)   //故障分包处理
	{
		pCanopenPDO->DgnDataRxTx.FuncCode = ERR_READ_ANSWER_DGNFUNC;		//0xFF
		bErrCodePackParse(&HangCha_GDC_PDO);
	}
	if (((pCanopenPDO->DgnDataRxTx.Q_AFlag & TX_FLAG) != 0) || (pCanopenPDO->DgnDataRxTx.SynFlag != 0) || ((pCanopenPDO->SendErrFlag == true) && (pCanopenPDO->ReqAnsyFlag == true)))
	{
		pCanopenPDO->CanBufTxState |= TX5D1_CANBUFTXSTATE;			
		pCanopenPDO->DgnDataRxTx.Q_AFlag &= ~(RX_FLAG | RDOP_FLAG | WROP_FLAG | TX_FLAG);
		if((pCanopenPDO->DgnDataRxTx.SynFlag == 13) || (pCanopenPDO->DgnDataRxTx.SynFlag == 15))
		{
			pCanopenPDO->SendErrFlag = true;  //故障码总分包标志 发送标志
		}
	}
	if(!(Count++&0x03))  //2*10=20ms
	{
//		CanOpenRxFrameMonitor();
	
		//发送反馈报文
		canFrame.ulID=0x360;
		canFrame.ucXID=0;			//0 标准帧；1 扩展帧  
		canFrame.ucDataLength=8;		//数据场长度
		
		if(SL_CHK(PLC_MIDDLE_RDY))		//homing ok flag
			QExpandAGV_PDO.StateWord |= 0x01;
		else  QExpandAGV_PDO.StateWord &= ~0x01;
		if(gCRam.bEnaSoft)		//upright flag
			QExpandAGV_PDO.StateWord |= 0x10;
		else  QExpandAGV_PDO.StateWord &= ~0x10;
        
//		if(QExpandAGV_PDO.VCUControlWord & 0x0080) //byte0.7 转向方向切换
//			gPLCCtl.RotateDir = 1;
//		else
//			gPLCCtl.RotateDir = 0;
        
		CmdAngle = TIM_GetCounter(TIM4);	
        
		QExpandAGV_PDO.AngleMeasured =  (gPLCCtl.icanSteer.ucSteerAngleH<<8) + gPLCCtl.icanSteer.ucSteerAngleL;
		QExpandAGV_PDO.SpeedMeasured =  gPara.AcMotorSpeed; //rpm gCRam.SpeedAvgAdd*6250/gPLCCtl.enc; //0.01Hz

	
		canFrame.ucData[0] = QExpandAGV_PDO.StateWord & 0xFF;
		canFrame.ucData[1] = ErrorCodeDisp(gPLCCtl.ErrCode) & 0xFF;
		canFrame.ucData[2] = (QExpandAGV_PDO.AngleMeasured) & 0xFF;
		canFrame.ucData[3] = (QExpandAGV_PDO.AngleMeasured >> 8) & 0xFF;
		canFrame.ucData[4] = (QExpandAGV_PDO.SpeedMeasured) & 0xFF;
		canFrame.ucData[5] = (QExpandAGV_PDO.SpeedMeasured >> 8) & 0xFF;

		canFrame.ucData[6] = CmdAngle & 0xFF;
		canFrame.ucData[7] = (CmdAngle >> 8) & 0xFF;	
		CANWriteBuffer(&canFrmTxBuffer, &canFrame);
//		CANFrmSend(&canFrmTxBuffer);		
	}
	
	if( ((pCanopenPDO->CanBufTxState & TX5D1_CANBUFTXSTATE) != 0)
	||  ((pCanopenPDO->SendErrFlag == true) && (pCanopenPDO->ReqAnsyFlag == true)))
	{
		canFrame.ulID=0x5D1;
		canFrame.ucXID=0;			//0 标准帧；1 扩展帧  
		canFrame.ucDataLength=8;		//数据场长度
		canFrame.ucData[0] = pCanopenPDO->DgnDataRxTx.FuncCode;
		canFrame.ucData[1] = pCanopenPDO->DgnDataRxTx.Index & 0xFF;
		canFrame.ucData[2] = (pCanopenPDO->DgnDataRxTx.Index >> 8) & 0xFF;
		canFrame.ucData[3] = pCanopenPDO->DgnDataRxTx.SubIndex;
		canFrame.ucData[4] = pCanopenPDO->DgnDataRxTx.DataL16 & 0xFF;
		canFrame.ucData[5] = (pCanopenPDO->DgnDataRxTx.DataL16 >> 8) & 0xFF;
		canFrame.ucData[6] = pCanopenPDO->DgnDataRxTx.DataH16 & 0xFF;
		canFrame.ucData[7] = (pCanopenPDO->DgnDataRxTx.DataH16 >> 8) & 0xFF;
		
		pCanopenPDO->CanBufTxState &= ~TX5D1_CANBUFTXSTATE;
		pCanopenPDO->DgnDataRxTx.SynFlag = 0;
		CANWriteBuffer(&canFrmTxBuffer, &canFrame);
	}
}

/*******************************************************************************
* FunctionName: vGetRandPwd
* Description:  用于生成随机数密码（字母大小写、数字），无请求时只生成一次，直至下次请求
* Input: _tHANGCHADGC_PDO *pCanopenPDO 
* Output: None
*
* Author: Young
* Date: 2024-01-06
* Revision: V1.0
*******************************************************************************/
void vGetRandPwd(tHANGCHAAPP_PDO *pCanopenPDO, INT8U length)
{
	INT8U i;
	static INT32U TempPwd;
	static INT8U CallNum = 0;
	const char str[] = "xaqt";//"XAQT";
	CallNum++;
	
	//如果解密错误 则允许生成下一次随机密码
	if(pCanopenPDO->GeneratePwdFlag == 0)
	{
		srand(TIM1->CNT);
		TempPwd= (INT32U)rand() + 0x20;
		pCanopenPDO->RandPwdArr[0] = (char)((TempPwd >> 24) & 0xFF);		
		pCanopenPDO->RandPwdArr[1] = (char)((TempPwd >> 16) & 0xFF);		
		pCanopenPDO->RandPwdArr[2] = (char)((TempPwd >> 8) & 0xFF);	
		pCanopenPDO->RandPwdArr[3] = (char)(TempPwd  & 0xFF);

   for(i = 0;i < 4; i++)
	 {
		 //if (!isalnum(pCanopenPDO->RandPwdArr[i]))  //可能由于编译器问题导致部分字符识别不出
		if(  (pCanopenPDO->RandPwdArr[i] < 0x30) 
			|| ((pCanopenPDO->RandPwdArr[i] >= 0x3A) &&(pCanopenPDO->RandPwdArr[i] <= 0x40))
			|| ((pCanopenPDO->RandPwdArr[i] >= 0x5B) &&(pCanopenPDO->RandPwdArr[i] <= 0x60)) 
			|| (pCanopenPDO->RandPwdArr[i] >= 0x7A) )
		 {
			 memcpy(&pCanopenPDO->RandPwdArr[i],&str[i], sizeof(str[i]));  //生成“XAQT”
		 }
	 }

	pCanopenPDO->GeneratePwdFlag = 1;  //密码校验错误时需将该标志位清0
  }
}
/*******************************************************************************
* FunctionName: vGetReplaceChar(char *oldpwd,char *newpwd)
* Description: 该函数用于将随机密码与给定字符串,做指定替换，得到一个原始密码
* Input: char *oldpwd
* Output: char *newpwd
*
* Author: Young
* Date: 2024-1-6
* Revision: V1.0
*******************************************************************************/
void vGetReplaceChar(char *oldpwd,char *newpwd)
{
	INT8U i;
	INT8U found = 0;

// 定义映射数组  加密步骤一
CharMapping mappings[] = {	{'1', '\\'},{'2', '!'},  {'3', '@'}, {'4', '#'},
							{'5', '&'},	{'6', '%'},  {'7', '?'}, {'8', '*'},
							{'9', '^'},	{'0', '/'},  {'d', '1'}, {'m', '1'},
							{'o', '1'},	{'j', '2'},  {'y', '2'}, {'z', '2'},
							{'b', '3'},	{'g', '3'},  {'r', '3'}, {'k', '4'},
							{'t', '4'},	{'u', '4'},  {'a', '5'}, {'h', '5'},
							{'x', '5'},	{'c', '6'},  {'p', '6'}, {'n', '6'},
							{'f', '7'},	{'q', '7'},  {'v', '7'}, {'e', '8'},
							{'l', '8'},	{'i', '8'},  {'w', '9'}, {'s', '9'}};

/*根据生成的随机密码在mappings的original哪个位置，然后根据映射关系，找出替代字符，大写不变*/
    while (*oldpwd)
	{
		for (i = 0; i < sizeof(mappings) / sizeof(CharMapping); ++i) 
		{
			if (*oldpwd == mappings[i].original) 
			{
				*newpwd++ = mappings[i].replacement;
				found = 1;
				break;
			}
		}
		if(!found)//如果未找到映射关系，直接赋值字符
		{
			*newpwd++ = *oldpwd;		
			found		 = 0;	
			if(*oldpwd == 0x30)  *newpwd++ = 0x2F;
		}
		// 移动到下一个字符
		++oldpwd;
    }
    // 添加字符串结束符
   //  *newpwd = '\0';
}
/*******************************************************************************
* FunctionName: vGenerateKeyPro
* Description: 根据得到的原始密码，然后进行四次加密换算
* Input: char *Original
* Output: char *CodeKey
*
* Author: Young
* Date: 2024-01-11
* Revision: V1.0
*******************************************************************************/
void vGenerateKeyPro(char *Original,char *CodeKey)
{
	char TempKey[4];
	INT8U step;
	INT8U i,j;
	INT8U indexInMappings;
	char currentChar;
	CharMapping mappings2[] = {	{'c', 'S'},	{'9', '5'},  {'j', 'd'}, {'^', 'f'},
								{'p', 'v'},	{'@', 'D'},  {'#', '8'}, {'5', 'g'},
								{'q', 't'},	{'l', '^'},  {'a', 'U'}, {'4', 'I'},
								{'\\', '9'},{'b', '2'},  {'m', '@'}, {'0', 'K'},
								{'z', 'w'},	{'g', '/'},  {'&', 'P'}, {'i', 'L'},
								{'e', 'Q'},	{'3', 'n'},  {'1', 'm'}, {'r', '%'},
								{'s', 'Y'},	{'/', 'r'},  {'t', 'W'}, {'%', 'z'},
								{'7', 'x'},	{'d', 'c'},  {'v', 'k'}, {'f', '!'},
								{'*', 'V'},	{'x', 'B'},  {'o', 'E'}, {'h', 'a'},
								{'n', '4'},	{'u', 'M'},  {'!', '3'}, {'k', '7'}};
    for (step = 0; step < 4; step++)  //四次加密
	{
		for(i = 0; i < 4; i++)	//四位密码迭代
		{		
		//1、根据原始字符现将密码中的大写字母全部换成小写
		//2、先找出原始替换字符在mappings2中的index；
		//3、根据index映射到替换字符				
			currentChar = Original[i];
			indexInMappings = (INT8U)-1;
			if((currentChar >= 0x41) && (currentChar <= 0x5A))
			{
				currentChar += 0x20;
			}
			// 查找字符在映射表中的位置
			for (j = 0; j < sizeof(mappings2) / sizeof(CharMapping); j++) 
			{
				if (currentChar == mappings2[j].original) 
				{
					indexInMappings = j;
					break;
				}
			}

			if (indexInMappings != (INT8U)-1)
			{
				TempKey[i] = mappings2[indexInMappings].replacement;
			} 
			else 
			{
				TempKey[i] = Original[i];  // 找不到的保留原字符
			}
		}
       // 用 TempKey 作为下一轮加密的输入
      for (i = 0; i < 4; i++)
		{
			Original[i] = TempKey[i];
		}
    }
	//最后一次加密后  将 TempKey的结果拷贝到 CodeKey 中
	for(i = 0; i < 4; i++)
	{
		CodeKey[i] = TempKey[i];
	}
//    for (INT8U i = 0; i < sizeof(mappings2) / sizeof(CharMapping); i++)
//		{
//			if (Original[i] == mappings2[i].original)
//			{
//				TempKey[i] = mappings2[i].replacement;//return i;  // 返回找到的位置
//				
//			}
//    }
  //  return (INT8U)-1;  // 如果没找到，返回特殊值（例如0xFF）									 

}

/*******************************************************************************
* FunctionName: iRemoteUnlockPWD
* Description:  将最终加密的密码与APP解析密码对比，一致return 1
* Input: _tHANGCHADGC_PDO  *pCanopenPDO, char *myParsepwd
* Output: char *myParsepwd
* 
* Author: Young
* Date:2024-01-08
* Revision:V1.0
*******************************************************************************/
INT8U iRemoteUnlockPWD(tHANGCHAAPP_PDO  *pCanopenPDO,char *myParsepwd)
{	
	INT8U i;
	char ReceivePwd[4];

	ReceivePwd[0] = pCanopenPDO->DgnDataRxTx.DataL16 & 0xFF;
	ReceivePwd[1] = (pCanopenPDO->DgnDataRxTx.DataL16>>8)  & 0xFF;
	ReceivePwd[2] =  pCanopenPDO->DgnDataRxTx.DataH16 & 0xFF;
	ReceivePwd[3] = (pCanopenPDO->DgnDataRxTx.DataH16 >> 8) & 0xFF;	
	
	for (i = 0; i < 4; ++i)
	{
		if (ReceivePwd[i] != (unsigned char)myParsepwd[i])
		{
			pCanopenPDO->GeneratePwdFlag = 0;	
			return 0;  // 比较失败，返回0
		}
	}
    return 1;  // 比较成功，返回1
}
/*******************************************************************************
* FunctionName: INT16S IndexToAddress(void)
* Description: 索引转换为上位机地址
* Input: None
* Output: INT16S
*
* Author: Young
* Date: 2024-03-25
* Revision: V1.0
*******************************************************************************/
INT16S IndexToAddress(void)
{
	tHANGCHAAPP_PDO *pCanopenPDO;
	pCanopenPDO = &HangCha_GDC_PDO;

	pCanopenPDO->BitAddr = -1;
	pCanopenPDO->IndexAddress = (pCanopenPDO->DgnDataRxTx.Index << 8) | (pCanopenPDO->DgnDataRxTx.SubIndex & 0xFF);
	
	switch(pCanopenPDO->IndexAddress)
	{
		/*********** 监控参数 地址分配 ***********/
		case 0x400101:
			pCanopenPDO->Address = 238;
			pCanopenPDO->XiShu = 1;					
			break;
		case 0x400102:
			pCanopenPDO->Address = 238;
			pCanopenPDO->XiShu = 1;	
			break;
		case 0x400103:
			pCanopenPDO->Address = 241;
			pCanopenPDO->XiShu = 2;	
			break;
		case 0x400104:
			pCanopenPDO->Address = 242;
			pCanopenPDO->XiShu = 3;	
			break;
		case 0x400105:
			pCanopenPDO->Address = 240;
			pCanopenPDO->XiShu = 4;	
			break;	
		case 0x400106:
			pCanopenPDO->Address = 234;
			pCanopenPDO->XiShu = 5;	
			break;	
		case 0x400107:
			pCanopenPDO->Address = 235;
			pCanopenPDO->XiShu = 6;	
			break;	
		case 0x400108:
			pCanopenPDO->Address = 236;
			pCanopenPDO->XiShu = 7;	
			break;	
		case 0x400109:
			pCanopenPDO->Address = 237;
			pCanopenPDO->XiShu = 8;	
			break;
		case 0x40010A:
			pCanopenPDO->Address = 230;
			pCanopenPDO->XiShu = 9;	
			break;	
		case 0x40010B:
			pCanopenPDO->Address = 231;
			pCanopenPDO->XiShu = 10;	
			break;		
		case 0x40010C:
			pCanopenPDO->Address = 232;
			pCanopenPDO->XiShu = 11;	
			break;
		case 0x40010D:
			pCanopenPDO->Address = 228;
			pCanopenPDO->XiShu = 12;	
			break;
		case 0x40010E:
			pCanopenPDO->Address = 252;
			pCanopenPDO->XiShu = 13;	
			break;
		case 0x40010F:
			pCanopenPDO->Address = 228;
			pCanopenPDO->XiShu = 60;	
			break;
		case 0x400201:
			pCanopenPDO->Address = 239;
			pCanopenPDO->XiShu = 13;	
			break;
		case 0x400202:
			pCanopenPDO->Address = 239;
			pCanopenPDO->XiShu = 13;	
			break;
		case 0x400203:
			pCanopenPDO->Address = 239;
			pCanopenPDO->XiShu = 13;	
			break;	
		case 0x400C01:
			pCanopenPDO->Address = 222;
			pCanopenPDO->XiShu = 14;	
			break;
		case 0x400C02:
			pCanopenPDO->Address = 221;
			pCanopenPDO->XiShu = 15;	
			break;
		case 0x400C03:
			pCanopenPDO->Address = 224;
			pCanopenPDO->XiShu = 16;	
			break;
		case 0x400C04:
			pCanopenPDO->Address = 225;
			pCanopenPDO->XiShu = 17;	
			break;
		case 0x400C05:
			pCanopenPDO->Address = 226;
			pCanopenPDO->XiShu = 18;	
			break;
		case 0x400C06:
			pCanopenPDO->Address = 243;
			pCanopenPDO->XiShu = 19;	
			break;
		case 0x400D07:
			pCanopenPDO->Address = 220;
			pCanopenPDO->XiShu = 20;	
			break;
		case 0x400D50:
			pCanopenPDO->Address = 215;
			pCanopenPDO->XiShu = 21;	
			break;
		case 0x400D51:
			pCanopenPDO->Address = 216;
			pCanopenPDO->XiShu = 22;	
			break;
		case 0x400D52:
			pCanopenPDO->Address = 217;
			pCanopenPDO->XiShu = 23;	
			break;
		/*************** 配置参数地址分配 ***************/
		case 0x200501:    /*电机基本参数*/
			pCanopenPDO->Address = 7;
			pCanopenPDO->XiShu = 24;	
			break;
		case 0x200502:
			pCanopenPDO->Address = 10;
			pCanopenPDO->XiShu = 25;	
			break;
		case 0x200503:
			pCanopenPDO->Address = 16;
			pCanopenPDO->XiShu = 26;	
			break;
		case 0x200504:
			pCanopenPDO->Address = 19;
			pCanopenPDO->XiShu = 27;	
			break;
		case 0x200505:
			pCanopenPDO->Address = 8;
			pCanopenPDO->XiShu = 28;	
			break;
		case 0x200506:
			pCanopenPDO->Address = 3;
			pCanopenPDO->XiShu = 29;
			pCanopenPDO->BitAddr = 0;
			break;
		case 0x200507:
			pCanopenPDO->Address = 3;
			pCanopenPDO->XiShu = 29;
			pCanopenPDO->BitAddr = 1;		
			break;
		case 0x200508:
			pCanopenPDO->Address = 102;
			pCanopenPDO->XiShu = 30;	
			break;
		case 0x200601:       /* 转向灵敏度 */
			pCanopenPDO->Address = 63;
			pCanopenPDO->XiShu = 31;	
			break;
		case 0x200602:
			pCanopenPDO->Address = 66;
			pCanopenPDO->XiShu = 32;	
			break;	
		case 0x200603:
			pCanopenPDO->Address = 72;
			pCanopenPDO->XiShu = 33;	
			break;	
		case 0x200604:
			pCanopenPDO->Address = 73;
			pCanopenPDO->XiShu = 34;	
			break;	
		case 0x200605:
			pCanopenPDO->Address = 191;
			pCanopenPDO->XiShu = 35;	
			break;	
		case 0x200606:
			pCanopenPDO->Address = 192;
			pCanopenPDO->XiShu = 36;	
			break;	
		case 0x200701:   /* 速度模式参数*/
			pCanopenPDO->Address = 6;
			pCanopenPDO->XiShu = 37;	
			break;
		case 0x200702:
			pCanopenPDO->Address = 51;
			pCanopenPDO->XiShu = 38;	
			break;
		case 0x200703:
			pCanopenPDO->Address = 52;
			pCanopenPDO->XiShu = 39;	
			break;
		case 0x200704:
			pCanopenPDO->Address = 53;
			pCanopenPDO->XiShu = 40;	
			break;
		case 0x200705:
			pCanopenPDO->Address = 54;
			pCanopenPDO->XiShu = 41;	
			break;
		case 0x200201:   /*角度输入设置*/
			pCanopenPDO->Address = 91;
			pCanopenPDO->XiShu = 42;	
			break;
		case 0x200202:
			pCanopenPDO->Address = 92;
			pCanopenPDO->XiShu = 43;	
			break;
		case 0x200203:
			pCanopenPDO->Address = 93;
			pCanopenPDO->XiShu = 44;	
			break;
		case 0x200204:
			pCanopenPDO->Address = 94;
			pCanopenPDO->XiShu = 45;	
			break;
		case 0x200205:
			pCanopenPDO->Address = 95;
			pCanopenPDO->XiShu = 46;	
			break;
		case 0x200206:
			pCanopenPDO->Address = 4;
			pCanopenPDO->XiShu = 47;
			pCanopenPDO->BitAddr = 0;		
			break;
		case 0x200207:
			pCanopenPDO->Address = 4;
			pCanopenPDO->XiShu = 47;
			pCanopenPDO->BitAddr = 5;		
			break;
		case 0x200208:
			pCanopenPDO->Address = 195;
			pCanopenPDO->XiShu = 48;	
			break;
		case 0x200209:
			pCanopenPDO->Address = 196;
			pCanopenPDO->XiShu = 49;	
			break;
		case 0x20020A:
			pCanopenPDO->Address = 197;
			pCanopenPDO->XiShu = 50;	
			break;
		case 0x20020B:
			pCanopenPDO->Address = 199;
			pCanopenPDO->XiShu = 51;	
			break;
		case 0x200301:
			pCanopenPDO->Address = 198;
			pCanopenPDO->XiShu = 52;	
			break;
		case 0x200302:    /* 回中设置 */
			pCanopenPDO->Address = 190;
			pCanopenPDO->XiShu = 53;	
			pCanopenPDO->BitAddr = 1;
			break;
		case 0x200303:
			pCanopenPDO->Address = 190;
			pCanopenPDO->XiShu = 53;	
			pCanopenPDO->BitAddr = 2;
			break;
		case 0x200304:
			pCanopenPDO->Address = 190;
			pCanopenPDO->XiShu = 53;	
			pCanopenPDO->BitAddr = 5;
			break;
		case 0x200305:
			pCanopenPDO->Address = 190;
			pCanopenPDO->XiShu = 53;	
			pCanopenPDO->BitAddr = 6;
			break;
		case 0x200306:
			pCanopenPDO->Address = 77;
			pCanopenPDO->XiShu = 54;	
			break;
		case 0x200401:  /* 车辆参数 */
			pCanopenPDO->Address = 193;
			pCanopenPDO->XiShu = 55;	
			break;
		case 0x200402:
			pCanopenPDO->Address = 194;
			pCanopenPDO->XiShu = 56;	
			break;
		case 0x200403:
			pCanopenPDO->Address = 146;
			pCanopenPDO->XiShu = 57;	
			break;
		case 0x200404:
			pCanopenPDO->Address = 79;
			pCanopenPDO->XiShu = 58;	
			break;
		case 0x200405:
			pCanopenPDO->Address = 80;
			pCanopenPDO->XiShu = 59;	
			break;
		default:
			pCanopenPDO->Address = 0;
			pCanopenPDO->XiShu = 0;	
			break;		
	}
	return 1;
}

/*******************************************************************************
* FunctionName: INT16U vMonitorParaAdjust(tHANGCHAAPP_PDO *pCanopenPDO,OriginVal)
* Description:  
* Input: tHANGCHAAPP_PDO *pCanopenPDO ，OriginVal
* Output: 
*
* Author: Young
* Date: 2024-03-26
* Revision: V1.0
*******************************************************************************/
INT16U vMonitorParaAdjust(tHANGCHAAPP_PDO *pCanopenPDO,INT16U OriginVal)
{
	if((pCanopenPDO->DgnDataRxTx.Index == 0x4001)
		&& ((pCanopenPDO->DgnDataRxTx.SubIndex >= 0x01) && (pCanopenPDO->DgnDataRxTx.SubIndex <= 0x02)))
	{
		OriginVal = (OriginVal >> (pCanopenPDO->DgnDataRxTx.SubIndex - 1)) & 0x01;	// //开关输入
	}
	else if(pCanopenPDO->DgnDataRxTx.Index == 0x4002)
	{
		if((pCanopenPDO->DgnDataRxTx.SubIndex >= 0x01) && (pCanopenPDO->DgnDataRxTx.SubIndex <= 0x03))
		{
			switch(pCanopenPDO->DgnDataRxTx.SubIndex)  // 驱动输出		
			{
				case 0x01:
					OriginVal = (OriginVal >> 0) & 0x01;
					break;
				case 0x02:
					OriginVal = (OriginVal >> 1) & 0x01; 
					break;
				case 0x03:
					OriginVal = (OriginVal >> 2) & 0x01;
					break;
//			default:
//				MonitorDataVal = MonitorDataVal & 0x00;
//				break;
			}
		}		
	}
	else if(pCanopenPDO->DgnDataRxTx.Index == 0x400D)
	{
		switch(pCanopenPDO->DgnDataRxTx.SubIndex)
		{
			case 0x50:
			{
				//例如：0x20240331  App上对应显示20240331
				INT8U YearL = (gPara.SoftVerYear >> 4) & 0x0F; //2000+解析年
				INT8U MonthH = (gPara.SoftVerMonthDay >> 12) & 0x0F;  //解析月
				INT8U MonthL = (gPara.SoftVerMonthDay >> 8) & 0x0F;  
				INT8U DayH = (gPara.SoftVerMonthDay >> 4) & 0x0F; //gPara.SoftVerMonthDay十六进制 // 十位数值
				INT8U DayL = gPara.SoftVerMonthDay & 0x0F;       // 个位数值

				OriginVal = (( YearL * 10) + (gPara.SoftVerYear & 0xF)) | (((MonthH * 10) +MonthL)  << 8);
				pCanopenPDO->DgnDataRxTx.DataH16 = (DayH * 10) + DayL;			
				break;
			}
			case 0x51:
				OriginVal = (gPara.HardVersion1 >> 8) | ((gPara.HardVersion1 & 0xFF) << 8);
				break;
			case 0x52:
				OriginVal = (gPara.HardVersion2 >> 8) | ((gPara.HardVersion2 & 0xFF) << 8);
				break;
			default:
				OriginVal =OriginVal;
				break;
		}
	}
	else  //其余的根据y=kx+b进行调整
	{
		OriginVal =OriginVal* K_XISHU[pCanopenPDO->XiShu] / K_CHU_XISHU[pCanopenPDO->XiShu] + B_XISHU[pCanopenPDO->XiShu];
	}
	return OriginVal;
}

/*******************************************************************************
* FunctionName: INT16U iModifyParaAdjust(_tHANGCHADGC_PDO *pCanopenPDO)
* Description:  该函数用于APP下发修改参数时，电控用于调整参数时的函数
* Input: _tHANGCHADGC_PDO
* Output: None
*
* Author: Young
* Date: 2024-02-06
* Revision: V1.0
*******************************************************************************/
INT16U iModifyParaAdjust(tHANGCHAAPP_PDO *pCanopenPDO)
{
	INT8U AppBitVal = 0;
	static INT8U Num = 0;
	static INT8U SpecialBitVal[4] = {0};   //修改之后  缓存

	AppBitVal = pCanopenPDO->DgnDataRxTx.DataL16;			//APP下发值
	/*** 累计APP修改的值 ***/
	for(Num = 0; Num < sizeof(SpecialBitArr)/sizeof(SpecialBitArr[0]);Num++)
	{
		if(pCanopenPDO->Address == SpecialBitArr[Num])  //当前地址为特殊bit控制位中的一个
		{
			if(SpecialBitVal[Num] == 0)  //切换为新的控制位
			{
				SpecialBitVal[Num] = pCanopenPDO->OriginalBitVal1[Num];  //如果遍历到当前控制位的值，将值暂存
			}
			break;
		}
	}
	if(AppBitVal)
	{
		SpecialBitVal[Num] |= (1 << pCanopenPDO->BitAddr);
	}
	else
	{
		SpecialBitVal[Num] &= ~(1 << pCanopenPDO->BitAddr);	
	}
  return SpecialBitVal[Num];
}


/*******************************************************************************
* FunctionName: LanguageChange()
* Description: 该函数用于中英文转换，主要针对故障码打包
* Input: _tHANGCHADGC_PDO *pCanopenPDO
* Output: 
* return: 0:false 1:true
* Author: Young
* Date: 2024-01-10
* Revision: V1.0
*******************************************************************************/
tBoolean bErrCodePackParse(tHANGCHAAPP_PDO *pCanopenPDO)
{
	//static INT8U Count = 0;  //历史故障记录 只有在本次故障编码全部发出之后才会发下一个故障 才++
  static INT16U LastCnt = 0;

	pCanopenPDO->ErrNum = 0;
	pCanopenPDO->ErrorTotalLength = 0;

	if(pCanopenPDO->ErrcodeType == 1)
	{
		pCanopenPDO->ErrNum = gPara.ErrCode;
	}
	else if(pCanopenPDO->ErrcodeType == 2)
	{
		pCanopenPDO->ErrNum = gCRam.ErrorTrace[pCanopenPDO->NumCount];  //从数组0开始发送
	}
	/***1 获取故障码所在数组的二维实际长度 ***/
	if(pCanopenPDO->ErrNum != 0) 
	{
		if(pCanopenPDO->SelectLanguage == CHINESE_OPTION)
		{
			while((ErrorUnicode[pCanopenPDO->ErrNum - 1][pCanopenPDO->ErrorTotalLength] != L'\0') && (pCanopenPDO->ErrorTotalLength < (sizeof(ErrorUnicode[pCanopenPDO->ErrNum]) / sizeof(wchar_t))))
			{
				pCanopenPDO->ErrorTotalLength++; //多少个汉字（多少个双字节）
			}
		}
		else if(pCanopenPDO->SelectLanguage == ENGLISH_OPTION)
		{
			while((ErrorAscii[pCanopenPDO->ErrNum - 1][pCanopenPDO->ErrorTotalLength] != '\0') && (pCanopenPDO->ErrorTotalLength < (sizeof(ErrorAscii[pCanopenPDO->ErrNum]) / sizeof(char))))
			{
				pCanopenPDO->ErrorTotalLength++;  //多少个单字节
			}		
		}
	}
	else
	{
		pCanopenPDO->ErrorTotalLength = 0;
	}
	/*** 判断故障请求是当前故障 or 历史故障 ***/
	if(pCanopenPDO->ErrcodeType == QUERY_CURRENT_ERR_SUBINDEX)  //01 当前故障
	{
		pCanopenPDO->DgnDataRxTx.Index = CURERROR_PACK_SEND_INDEX;
		if(gPara.ErrCode != 0)
		{
			vErrPackSendPro(pCanopenPDO->ErrorTotalLength);
		}
	}
	else if(pCanopenPDO->ErrcodeType == QUERY_PREVIOUS_ERR_SUBINDEX) //02 历史故障
	{
		pCanopenPDO->DgnDataRxTx.Index = PREERROR_PACK_SEND_INDEX;	//FF12
		if((gCRam.ErrorTrace[pCanopenPDO->NumCount] != 0) && (pCanopenPDO->sendcnt))
		{
			vErrPackSendPro(pCanopenPDO->ErrorTotalLength); 
			if(LastCnt > TX_PERIOD)
			{
				LastCnt = 0;
				if(pCanopenPDO->LastErrByte == true)
						pCanopenPDO->NumCount++;
				if((pCanopenPDO->NumCount >= 7) ||  (pCanopenPDO->NumCount >= pCanopenPDO->sendcnt))
				{	
					pCanopenPDO->NumCount = 0;
					pCanopenPDO->SendErrFlag = false;  //历史故障只需要发一次 一旦超过最大故障数 停止发送
				}					
			}		
			else
				LastCnt++;
		}
	}
	else
		return  false;
	return true;
}	
/*******************************************************************************
* FunctionName:void vErrPackSendPro(INT8U length)
* Description:  故障码打包处理，主要针对当前和历史故障做处理
* Input: INT8U length（当前故障码的长度 特指中文unicod和英文ASCII的长度<包含空格>）
* Output: 
*
* Author: Young
* Date:
* Revision:V1.0 
*******************************************************************************/
void vErrPackSendPro(INT8U length)
{
	static INT16U  TxTimeOut1 = 0;
	INT8U DaoxuIndex = 0;
	Time_InitTypeDef TIME_InitStructure;
	tHANGCHAAPP_PDO *pCanopenPDO;
	pCanopenPDO = &HangCha_GDC_PDO;

	if(pCanopenPDO->SelectLanguage == CHINESE_OPTION)
	{
		length *= 2;		 //比如：控制器过流  五个双字节  字节总数就是5*2 = 10;
	}
	else if(pCanopenPDO->SelectLanguage == ENGLISH_OPTION)
	{
		length *= 1;		
	}
	if(length >= MAX_BYTE_NUM)
		length = MAX_BYTE_NUM;  //最大只允许28个
	
	TIME_InitStructure.Hour = (gPLCCtl.HourCnt * 6) / 60;
	TIME_InitStructure.Minute = (gPLCCtl.HourCnt * 6) % 60;
	
	/*** Send process Processing ***/
	if(length % 4) 
	{
		DaoxuIndex = (length / 4) + 1;
	}
	else
		DaoxuIndex = length / 4;

	switch (pCanopenPDO->SubFunID)
	{
		case 0xFF:
			pCanopenPDO->DgnDataRxTx.SubIndex = 0xFF;
			pCanopenPDO->DataStateBit1 = length;
			if(pCanopenPDO->ErrcodeType == 1)
			{
				pCanopenPDO->DataStateBit2  = 0x0D; 
				pCanopenPDO->DgnDataRxTx.DataL16 = gPara.ErrCode;
				pCanopenPDO->DgnDataRxTx.DataH16 = ((pCanopenPDO->DataStateBit1) | pCanopenPDO->DataStateBit2 << 8);
			}
			else
			{
				pCanopenPDO->DataStateBit2 = 0x0C;
				pCanopenPDO->DgnDataRxTx.DataL16 = pCanopenPDO->ErrNum;
				pCanopenPDO->DgnDataRxTx.DataH16 = ((pCanopenPDO->DataStateBit1) | pCanopenPDO->DataStateBit2 << 8);
			}
			break;
		case 0xFE:
			pCanopenPDO->DgnDataRxTx.SubIndex = 0xFE;
			if(pCanopenPDO->ErrcodeType == 1)
			{
				pCanopenPDO->DgnDataRxTx.DataL16 = 0;
				pCanopenPDO->DgnDataRxTx.DataH16 = 0;
			}
			else if(pCanopenPDO->ErrcodeType == 2)
			{
				pCanopenPDO->DgnDataRxTx.DataL16 = TIME_InitStructure.Hour;//TIME_InitStructure.Minute << 3;//TIME_InitStructure.Hour; 		//32-48Bit  
				pCanopenPDO->DgnDataRxTx.DataH16 = TIME_InitStructure.Minute;		//49-54Bit
			}
			break;
		case 0xFD:
			pCanopenPDO->DgnDataRxTx.SubIndex = 0xFD;
			if(pCanopenPDO->SelectLanguage == CHINESE_OPTION)
			{
				if(pCanopenPDO->ErrcodeType == 1)
				{
					pCanopenPDO->DgnDataRxTx.DataL16 = ErrorUnicode[gPara.ErrCode - 1][0];
					pCanopenPDO->DgnDataRxTx.DataH16 = ErrorUnicode[gPara.ErrCode - 1][1];
				}
				else if(pCanopenPDO->ErrcodeType == 2)
				{
					pCanopenPDO->DgnDataRxTx.DataL16 = ErrorUnicode[pCanopenPDO->ErrNum - 1][0];
					pCanopenPDO->DgnDataRxTx.DataH16 = ErrorUnicode[pCanopenPDO->ErrNum - 1][1];					
				}
			}
			else
			{
				if(pCanopenPDO->ErrcodeType == 1)
				{
					pCanopenPDO->DgnDataRxTx.DataL16 = ErrorAscii[gPara.ErrCode - 1][0] | (ErrorAscii[gPara.ErrCode - 1][1] << 8);
					pCanopenPDO->DgnDataRxTx.DataH16 = ErrorAscii[gPara.ErrCode - 1][2] | (ErrorAscii[gPara.ErrCode - 1][3] << 8);	
				}
				else if(pCanopenPDO->ErrcodeType == 2)
				{
					pCanopenPDO->DgnDataRxTx.DataL16 = ErrorAscii[pCanopenPDO->ErrNum - 1][0] | (ErrorAscii[pCanopenPDO->ErrNum - 1][1] << 8);
					pCanopenPDO->DgnDataRxTx.DataH16 = ErrorAscii[pCanopenPDO->ErrNum - 1][2] | (ErrorAscii[pCanopenPDO->ErrNum - 1][3] << 8);						
				}
			}
			break;
		case 0xFC:
			pCanopenPDO->DgnDataRxTx.SubIndex = 0xFC;
			if(pCanopenPDO->SelectLanguage == CHINESE_OPTION)
			{
				if(pCanopenPDO->ErrcodeType == 1)
				{
					pCanopenPDO->DgnDataRxTx.DataL16 = ErrorUnicode[gPara.ErrCode - 1][2];
					pCanopenPDO->DgnDataRxTx.DataH16 = ErrorUnicode[gPara.ErrCode - 1][3];
				}
				else if(pCanopenPDO->ErrcodeType == 2)
				{
					pCanopenPDO->DgnDataRxTx.DataL16 = ErrorUnicode[pCanopenPDO->ErrNum - 1][2];
					pCanopenPDO->DgnDataRxTx.DataH16 = ErrorUnicode[pCanopenPDO->ErrNum - 1][3];					
				}
			}
			else
			{
				if(pCanopenPDO->ErrcodeType == 1)
				{
					pCanopenPDO->DgnDataRxTx.DataL16 = ErrorAscii[gPara.ErrCode - 1][4] | (ErrorAscii[gPara.ErrCode - 1][5] << 8);
					pCanopenPDO->DgnDataRxTx.DataH16 = ErrorAscii[gPara.ErrCode - 1][6] | (ErrorAscii[gPara.ErrCode - 1][7] << 8);
				}
				else if(pCanopenPDO->ErrcodeType == 2)
				{
					pCanopenPDO->DgnDataRxTx.DataL16 = ErrorAscii[pCanopenPDO->ErrNum - 1][4] | (ErrorAscii[pCanopenPDO->ErrNum - 1][5] << 8);
					pCanopenPDO->DgnDataRxTx.DataH16 = ErrorAscii[pCanopenPDO->ErrNum - 1][6] | (ErrorAscii[pCanopenPDO->ErrNum - 1][7] << 8);					
				}
			}
			 break;
		case 0xFB:
			pCanopenPDO->DgnDataRxTx.SubIndex = 0xFB;
			if(pCanopenPDO->SelectLanguage == CHINESE_OPTION)
			{
				if(pCanopenPDO->ErrcodeType == 1)
				{
					pCanopenPDO->DgnDataRxTx.DataL16 = ErrorUnicode[gPara.ErrCode - 1][4];
					pCanopenPDO->DgnDataRxTx.DataH16 = ErrorUnicode[gPara.ErrCode - 1][5];
				}
				else if(pCanopenPDO->ErrcodeType == 2)
				{
					pCanopenPDO->DgnDataRxTx.DataL16 = ErrorUnicode[pCanopenPDO->ErrNum - 1][4];
					pCanopenPDO->DgnDataRxTx.DataH16 = ErrorUnicode[pCanopenPDO->ErrNum - 1][5];					
				}
			}
			else
			{
				if(pCanopenPDO->ErrcodeType == 1)
				{
					pCanopenPDO->DgnDataRxTx.DataL16 = ErrorAscii[gPara.ErrCode - 1][8] | (ErrorAscii[gPara.ErrCode - 1][9] << 8);
					pCanopenPDO->DgnDataRxTx.DataH16 = ErrorAscii[gPara.ErrCode - 1][10] | (ErrorAscii[gPara.ErrCode - 1][11] << 8);
				}
				else if(pCanopenPDO->ErrcodeType == 2)
				{
					pCanopenPDO->DgnDataRxTx.DataL16 = ErrorAscii[pCanopenPDO->ErrNum - 1][8] | (ErrorAscii[pCanopenPDO->ErrNum - 1][9] << 8);
					pCanopenPDO->DgnDataRxTx.DataH16 = ErrorAscii[pCanopenPDO->ErrNum - 1][10] | (ErrorAscii[pCanopenPDO->ErrNum - 1][11] << 8);					
				}				
			}
			break;
		case 0xFA:
			pCanopenPDO->DgnDataRxTx.SubIndex = 0xFA;
			if(pCanopenPDO->SelectLanguage == CHINESE_OPTION)
			{
				if(pCanopenPDO->ErrcodeType == 1)
				{
					pCanopenPDO->DgnDataRxTx.DataL16 = ErrorUnicode[gPara.ErrCode - 1][6];
					pCanopenPDO->DgnDataRxTx.DataH16 = ErrorUnicode[gPara.ErrCode - 1][7];
				}
				else if(pCanopenPDO->ErrcodeType == 2)
				{
					pCanopenPDO->DgnDataRxTx.DataL16 = ErrorUnicode[pCanopenPDO->ErrNum - 1][6];
					pCanopenPDO->DgnDataRxTx.DataH16 = ErrorUnicode[pCanopenPDO->ErrNum - 1][7];					
				}
			}
			else
			{
				if(pCanopenPDO->ErrcodeType == 1)
				{
					pCanopenPDO->DgnDataRxTx.DataL16 = ErrorAscii[gPara.ErrCode - 1][12] | (ErrorAscii[gPara.ErrCode - 1][13] << 8);
					pCanopenPDO->DgnDataRxTx.DataH16 = ErrorAscii[gPara.ErrCode - 1][14] | (ErrorAscii[gPara.ErrCode - 1][15] << 8);
				}
				else if(pCanopenPDO->ErrcodeType == 2)
				{
					pCanopenPDO->DgnDataRxTx.DataL16 = ErrorAscii[pCanopenPDO->ErrNum - 1][12] | (ErrorAscii[pCanopenPDO->ErrNum - 1][13] << 8);
					pCanopenPDO->DgnDataRxTx.DataH16 = ErrorAscii[pCanopenPDO->ErrNum - 1][14] | (ErrorAscii[pCanopenPDO->ErrNum - 1][15] << 8);					
				}
			}
			break;
		case 0xF9:
			pCanopenPDO->DgnDataRxTx.SubIndex = 0xF9;
			if(pCanopenPDO->SelectLanguage == CHINESE_OPTION)
			{
				if(pCanopenPDO->ErrcodeType == 1)
				{
					pCanopenPDO->DgnDataRxTx.DataL16 = ErrorUnicode[gPara.ErrCode - 1][8];
					pCanopenPDO->DgnDataRxTx.DataH16 = ErrorUnicode[gPara.ErrCode - 1][9];
				}
				else if(pCanopenPDO->ErrcodeType == 2)
				{
					pCanopenPDO->DgnDataRxTx.DataL16 = ErrorUnicode[pCanopenPDO->ErrNum - 1][8];
					pCanopenPDO->DgnDataRxTx.DataH16 = ErrorUnicode[pCanopenPDO->ErrNum - 1][9];					
				}
			}
			else
			{
				if(pCanopenPDO->ErrcodeType == 1)
				{
					pCanopenPDO->DgnDataRxTx.DataL16 = ErrorAscii[gPara.ErrCode - 1][16] | (ErrorAscii[gPara.ErrCode - 1][17] << 8);
					pCanopenPDO->DgnDataRxTx.DataH16 = ErrorAscii[gPara.ErrCode - 1][18] | (ErrorAscii[gPara.ErrCode - 1][19] << 8);
				}
				else if(pCanopenPDO->ErrcodeType == 2)
				{
					pCanopenPDO->DgnDataRxTx.DataL16 = ErrorAscii[pCanopenPDO->ErrNum - 1][16] | (ErrorAscii[pCanopenPDO->ErrNum - 1][17] << 8);
					pCanopenPDO->DgnDataRxTx.DataH16 = ErrorAscii[pCanopenPDO->ErrNum - 1][18] | (ErrorAscii[pCanopenPDO->ErrNum - 1][19] << 8);					
				}
			}
			break;
		case 0xF8:
			pCanopenPDO->DgnDataRxTx.SubIndex = 0xF8;
			if(pCanopenPDO->SelectLanguage == ENGLISH_OPTION)
			{
				if(pCanopenPDO->ErrcodeType == 1)
				{
					pCanopenPDO->DgnDataRxTx.DataL16 = ErrorAscii[gPara.ErrCode - 1][20] | (ErrorAscii[gPara.ErrCode - 1][21] << 8);
					pCanopenPDO->DgnDataRxTx.DataH16 = ErrorAscii[gPara.ErrCode - 1][22] | (ErrorAscii[gPara.ErrCode - 1][23] << 8);
				}
				else if(pCanopenPDO->ErrcodeType == 2)
				{
					pCanopenPDO->DgnDataRxTx.DataL16 = ErrorAscii[pCanopenPDO->ErrNum - 1][20] | (ErrorAscii[pCanopenPDO->ErrNum - 1][21] << 8);
					pCanopenPDO->DgnDataRxTx.DataH16 = ErrorAscii[pCanopenPDO->ErrNum - 1][22] | (ErrorAscii[pCanopenPDO->ErrNum - 1][23] << 8);					
				}
			}
			break;
		case 0xF7:
			pCanopenPDO->DgnDataRxTx.SubIndex = 0xF7;
			if(pCanopenPDO->SelectLanguage == ENGLISH_OPTION)
			{
				if(pCanopenPDO->ErrcodeType == 1)
				{
					pCanopenPDO->DgnDataRxTx.DataL16 = ErrorAscii[gPara.ErrCode - 1][24] | (ErrorAscii[gPara.ErrCode - 1][25] << 8);
					pCanopenPDO->DgnDataRxTx.DataH16 = ErrorAscii[gPara.ErrCode - 1][26] | (ErrorAscii[gPara.ErrCode - 1][27] << 8);
				}
				else if(pCanopenPDO->ErrcodeType == 2)
				{
					pCanopenPDO->DgnDataRxTx.DataL16 = ErrorAscii[pCanopenPDO->ErrNum - 1][24] | (ErrorAscii[pCanopenPDO->ErrNum - 1][25] << 8);
					pCanopenPDO->DgnDataRxTx.DataH16 = ErrorAscii[pCanopenPDO->ErrNum - 1][26] | (ErrorAscii[pCanopenPDO->ErrNum - 1][27] << 8);					
				}
			}
			break;
		}
	if(TxTimeOut1 >= TX_PERIOD)
	{
		TxTimeOut1 = 0;
		if(pCanopenPDO->SubFunID <=  0xFD - DaoxuIndex + 1)
		{
			pCanopenPDO->LastErrByte = true;
			pCanopenPDO->SubFunID = 0xFF;
		}
		else
		{
			pCanopenPDO->LastErrByte = false;
			pCanopenPDO->SubFunID--;
		}
		pCanopenPDO->ReqAnsyFlag  = true;
	} 
	else
	{
		TxTimeOut1++;	
		pCanopenPDO->ReqAnsyFlag  = false;
	}
}
#endif
