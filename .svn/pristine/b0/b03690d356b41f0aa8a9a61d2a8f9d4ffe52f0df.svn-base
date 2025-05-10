/**************************************************************************

***************************************************************************/

//#include <string.h>
#include "./mco.h"
#include "./mcohw.h"
#include "para.h"

#define NODEID 0x18

//PDO_CANID define
#define		TPDO1_CANID		(0x180+NODEID)
#define		TPDO2_CANID		0x360//(0x280+NODEID)
#define		TPDO3_CANID		(0x380+NODEID)
#define		TPDO4_CANID		(0x480+NODEID)

#define		RPDO1_CANID		0x260	//(0x200+NODEID)
#define		RPDO2_CANID		(0x300+NODEID)
#define		RPDO3_CANID		(0x400+NODEID)
#define		RPDO4_CANID		(0x500+NODEID)

// Global timer/conter variable, incremented every millisecond
extern WORD volatile gTimCnt;
extern WORD volatile gCANFilter;
//extern	PLC_CTL		gPLCCtl;

/**************************************************************************
GLOBAL VARIABLES
***************************************************************************/
BYTE ODNodeID = NODEID;
OD_TABLE OD[MAX_OD_SIZE];


BYTE SizeOfOD(BYTE DataTyp)
{
	switch (DataTyp)
	{
	case 0x0005:
		return 1;
	case 0x0006:
		return 2;
	case 0x0007:
		return 4;
	case 0x0040:
		return 30;
	}	
	return 0;
}	
// ////////////////////////////////
// void CpODVal2Ary(DWORD Ary[], BYTE ODNumB, BYTE ODNumE)
// {
//     BYTE i,Len;
//     DWORD j;
//     Len = ODNumE - ODNumB + 1;
//     for(i = 0; i < Len; i++)
//     {
//         Ary[i] = OD[ODNumB + i].Val;
//     }
//     CRC_ResetDR();
//     Ary[i] = CRC_CalcBlockCRC((u32*)Ary, Len);
//     i2c_24c_init(I2C2);
//     i2c_24c_buffer_write((u8*)Ary, 0x00, (Len + 1) * 2, EE24C_Block0_ADDR, I2C2);
//     for(j = 0; j < 600000; j++)
//     {}
//     i2c_24c_init(I2C2);
//     i2c_24c_buffer_write(((u8*)Ary + (Len + 1) * 2), 0x00, (Len + 1) * 2, EE24C_Block1_ADDR, I2C2);
// }
// void CpAry2ODVal(DWORD Ary[], BYTE ODNumB, BYTE ODNumE)
// {
//     BYTE i,Len;
//     DWORD j;
//     Len = ODNumE - ODNumB + 1;
//     i2c_24c_init(I2C2);
//     i2c_24c_buffer_read((u8*)Ary, 0x00, (Len + 1) * 2, EE24C_Block0_ADDR, I2C2);
//     for(j = 0; j < 600000; j++)
//     {}
//     i2c_24c_init(I2C2);
//     i2c_24c_buffer_read(((u8*)Ary + (Len + 1) * 2), 0x00, (Len + 1) * 2, EE24C_Block1_ADDR, I2C2);
//     CRC_ResetDR();
//     if(Ary[Len] == CRC_CalcBlockCRC((u32*)Ary, Len))
//     {
//         for(i = 0; i < Len; i++)
//         {
//             OD[ODNumB + i].Val = Ary[i];
//         }
//     }
// }
// ////////////////////////////////////
void OD_init(WORD Num,WORD Idx,BYTE SubIdx,
             BYTE ObjTyp,WORD DataTyp,BYTE AccTyp,BYTE PdoMap,
             DWORD Val)
{
	OD[Num].idx = Idx;
	OD[Num].subidx = SubIdx;
	OD[Num].ObjTyp = ObjTyp;
	OD[Num].DataTyp = DataTyp;
	OD[Num].AccTyp = AccTyp;
	OD[Num].PdoMap = PdoMap;
	//OD[Num].DefVal = DefVal;
	OD[Num].Val = Val;
}
////////////////////////////////////////////////////////////////
void ODTALE_init(void)
{
	int i;
	i=0;
	OD_init(0 + i,0x1000,0x00,ODVAR,ODUS32,ODRD,ODNMP,OD_DEVICE_TYPE);
	OD_init(1 + i,0x1018,0x00,ODVAR,ODUS16,ODRD,ODNMP,4);
	OD_init(2 + i,0x1018,0x01,ODVAR,ODUS32,ODRD,ODNMP,OD_VENDOR_ID);
	OD_init(3 + i,0x1018,0x02,ODVAR,ODUS32,ODRD,ODNMP,OD_PRODUCT_CODE);
	OD_init(4 + i,0x1018,0x03,ODVAR,ODUS32,ODRD,ODNMP,OD_REVISION);
	OD_init(5 + i,0x1018,0x04,ODVAR,ODUS32,ODRD,ODNMP,OD_SERIAL);
	/*RPDO1 Communication Parameter*/
	OD_init(6 + i,0x1400,0x00,ODVAR,ODUS8,ODRD,ODNMP,2);                               //number of entries
	OD_init(7 + i,0x1400,0x01,ODVAR,ODUS32,ODRD,ODNMP,RPDO1_CANID);//COB-ID used by PDO = 0x200+ODNodeID
 	OD_init(8 + i,0x1400,0x02,ODVAR,ODUS8,ODRD,ODNMP,0xff);                         //transmission type = asynchronous
	/*RPDO1 Mapping Parameter*/
	OD_init(9 + i,0x1600,0x00,ODVAR,ODUS8,ODRD,ODNMP,4);                    //number of mapped objects
	OD_init(10 + i,0x1600,0x01,ODVAR,ODUS32,ODRD,ODNMP,0x22000110);//first mapped object     
	OD_init(11 + i,0x1600,0x02,ODVAR,ODUS32,ODRD,ODNMP,0x22000210);//second mapped object    
	OD_init(12 + i,0x1600,0x03,ODVAR,ODUS32,ODRD,ODNMP,0x22000310);//third mapped object     
	OD_init(13 + i,0x1600,0x04,ODVAR,ODUS32,ODRD,ODNMP,0x22000410);//fourth mapped object    
	/*RPDO2 Communication Parameter*/
	OD_init(14 + i,0x1401,0x00,ODVAR,ODUS8,ODRD,ODNMP,2);			              //number of entries
	OD_init(15 + i,0x1401,0x01,ODVAR,ODUS32,ODRD,ODNMP,RPDO2_CANID);//COB-ID used by PDO
	OD_init(16 + i,0x1401,0x02,ODVAR,ODUS8,ODRD,ODNMP,0xff);			      //transmission type 
	/*RPDO2 Mapping Parameter*/
	OD_init(17 + i,0x1601,0x00,ODVAR,ODUS8,ODRD,ODNMP,4);
	OD_init(18 + i,0x1601,0x01,ODVAR,ODUS32,ODRD,ODNMP,0x20600210);//first mapped object     
	OD_init(19 + i,0x1601,0x02,ODVAR,ODUS32,ODRD,ODNMP,0x20600310);//second mapped object    
	OD_init(20 + i,0x1601,0x03,ODVAR,ODUS32,ODRD,ODNMP,0x20600110);//third mapped object     
	OD_init(21 + i,0x1601,0x04,ODVAR,ODUS32,ODRD,ODNMP,0x20600410);//fourth mapped object  
	/*RPDO3 Communication Parameter*/
	OD_init(22 + i,0x1402,0x00,ODVAR,ODUS8,ODRD,ODNMP,2);			              //number of entries
	OD_init(23 + i,0x1402,0x01,ODVAR,ODUS32,ODRD,ODNMP,RPDO3_CANID);//COB-ID used by PDO
	OD_init(24 + i,0x1402,0x02,ODVAR,ODUS8,ODRD,ODNMP,0xff);			      //transmission type 
	/*RPDO3 Mapping Parameter*/
	OD_init(25 + i,0x1602,0x00,ODVAR,ODUS8,ODRD,ODNMP,4);
	OD_init(26 + i,0x1602,0x01,ODVAR,ODUS32,ODRD,ODNMP,0x20660010);//first mapped object     
	OD_init(27 + i,0x1602,0x02,ODVAR,ODUS32,ODRD,ODNMP,0x20650010);//second mapped object    
	OD_init(28 + i,0x1602,0x03,ODVAR,ODUS32,ODRD,ODNMP,0);//third mapped object     
	OD_init(29 + i,0x1602,0x04,ODVAR,ODUS32,ODRD,ODNMP,0);//fourth mapped object  
	/*RPDO4 Communication Parameter*/
	OD_init(30 + i,0x1403,0x00,ODVAR,ODUS8,ODRD,ODNMP,2);			              //number of entries
	OD_init(31 + i,0x1403,0x01,ODVAR,ODUS32,ODRD,ODNMP,RPDO4_CANID);//COB-ID used by PDO
	OD_init(32 + i,0x1403,0x02,ODVAR,ODUS8,ODRD,ODNMP,0xff);			      //transmission type 
	/*RPDO4 Mapping Parameter*/
	OD_init(33 + i,0x1603,0x00,ODVAR,ODUS8,ODRD,ODNMP,4);
	OD_init(34 + i,0x1603,0x01,ODVAR,ODUS32,ODRD,ODNMP,0x60100110);//first mapped object     
	OD_init(35 + i,0x1603,0x02,ODVAR,ODUS32,ODRD,ODNMP,0x60030110);//second mapped object    
	OD_init(36 + i,0x1603,0x03,ODVAR,ODUS32,ODRD,ODNMP,0x60030210);//third mapped object     
	OD_init(37 + i,0x1603,0x04,ODVAR,ODUS32,ODRD,ODNMP,0x60030310);//fourth mapped object  
	//////////////////////////////////////////////////////////////////////////////////////////////////
	/*TPDO1 Communication Parameter*/
	OD_init(38 + i,0x1800,0x00,ODVAR,ODUS8,ODRD,ODNMP,4);                               //number of entries 条目的数量
	OD_init(39 + i,0x1800,0x01,ODVAR,ODUS32,ODRW,ODNMP,TPDO1_CANID);//COB-ID used by PDO
	OD_init(40 + i,0x1800,0x02,ODVAR,ODUS8,ODRW,ODNMP,0xff);	                      //transmission type  传输类型
	OD_init(41 + i,0x1800,0x03,ODVAR,ODUS16,ODRD,ODNMP,1000);	                      //inhibit time       禁止时间
	OD_init(42 + i,0x1800,0x05,ODVAR,ODUS16,ODRW,ODNMP,1000);	                      //event timer        事件定时周期
	/*TPDO1 Mapping Parameter*/
	OD_init(43 + i,0x1A00,0x00,ODVAR,ODUS8,ODRD,ODNMP,4);                   //number of mapped objects  映射对象的数量
	OD_init(44 + i,0x1A00,0x01,ODVAR,ODUS32,ODRW,ODNMP,0x20EE0010);//first mapped object       第一个映射对象
	OD_init(45 + i,0x1A00,0x02,ODVAR,ODUS32,ODRW,ODNMP,0x20DC0010);//second mapped object      第二个映射对象
	OD_init(46 + i,0x1A00,0x03,ODVAR,ODUS32,ODRW,ODNMP,0x20E40010);//third mapped object       第三个映射对象
	OD_init(47 + i,0x1A00,0x04,ODVAR,ODUS32,ODRW,ODNMP,0x20DE0010);//fourth mapped object      第四个映射对象
	/*TPDO2 Communication Parameter*/
	OD_init(48 + i,0x1801,0x00,ODVAR,ODUS8,ODRD,ODNMP,4);                               //number of entries 条目的数量
	OD_init(49 + i,0x1801,0x01,ODVAR,ODUS32,ODRD,ODNMP,TPDO2_CANID);//COB-ID used by PDO
	OD_init(50 + i,0x1801,0x02,ODVAR,ODUS8,ODRD,ODNMP,0xff);                         //transmission type  传输类型
	OD_init(51 + i,0x1801,0x03,ODVAR,ODUS16,ODRD,ODNMP,10);                              //inhibit time       禁止时间
	OD_init(52 + i,0x1801,0x05,ODVAR,ODUS16,ODRD,ODNMP,1000);                          //event timer        事件定时周期
	/*TPDO2 Mapping Parameter*/
	OD_init(53 + i,0x1A01,0x00,ODVAR,ODUS8,ODRD,ODNMP,4);                   //number of mapped objects  映射对象的数量
	OD_init(54 + i,0x1A01,0x01,ODVAR,ODUS32,ODRW,ODNMP,0x20E10010);//first mapped object       第一个映射对象
	OD_init(55 + i,0x1A01,0x02,ODVAR,ODUS32,ODRW,ODNMP,0x00);//second mapped object      第二个映射对象
	OD_init(56 + i,0x1A01,0x03,ODVAR,ODUS32,ODRW,ODNMP,0x00);//third mapped object       第三个映射对象
	OD_init(57 + i,0x1A01,0x04,ODVAR,ODUS32,ODRW,ODNMP,0x00);//fourth mapped object      第四个映射对象
	/*TPDO3 Communication Parameter*/
	OD_init(58 + i,0x1802,0x00,ODVAR,ODUS8,ODRD,ODNMP,4);                               //number of entries 条目的数量
	OD_init(59 + i,0x1802,0x01,ODVAR,ODUS32,ODRD,ODNMP,TPDO3_CANID);//COB-ID used by PDO
	OD_init(60 + i,0x1802,0x02,ODVAR,ODUS8,ODRD,ODNMP,0);                         //transmission type  传输类型
	OD_init(61 + i,0x1802,0x03,ODVAR,ODUS16,ODRD,ODNMP,10);                              //inhibit time       禁止时间
	OD_init(62 + i,0x1802,0x05,ODVAR,ODUS16,ODRD,ODNMP,0);                          //event timer        事件定时周期
	/*TPDO3 Mapping Parameter*/
	OD_init(63 + i,0x1A02,0x00,ODVAR,ODUS8,ODRD,ODNMP,4);                   //number of mapped objects  映射对象的数量
	OD_init(64 + i,0x1A02,0x01,ODVAR,ODUS32,ODRW,ODNMP,0x00);//first mapped object       第一个映射对象
	OD_init(65 + i,0x1A02,0x02,ODVAR,ODUS32,ODRW,ODNMP,0x00);//second mapped object      第二个映射对象
	OD_init(66 + i,0x1A02,0x03,ODVAR,ODUS32,ODRW,ODNMP,0x00);//third mapped object       第三个映射对象
	OD_init(67 + i,0x1A02,0x04,ODVAR,ODUS32,ODRW,ODNMP,0x00);//fourth mapped object      第四个映射对象
	/*TPDO4 Communication Parameter*/
	OD_init(68 + i,0x1803,0x00,ODVAR,ODUS8,ODRD,ODNMP,4);                               //number of entries 条目的数量
	OD_init(69 + i,0x1803,0x01,ODVAR,ODUS32,ODRD,ODNMP,TPDO4_CANID);//COB-ID used by PDO
	OD_init(70 + i,0x1803,0x02,ODVAR,ODUS8,ODRD,ODNMP,0);                         //transmission type  传输类型
	OD_init(71 + i,0x1803,0x03,ODVAR,ODUS16,ODRD,ODNMP,10);                              //inhibit time       禁止时间
	OD_init(72 + i,0x1803,0x05,ODVAR,ODUS16,ODRD,ODNMP,0);                          //event timer        事件定时周期
	/*TPDO4 Mapping Parameter*/
	OD_init(73 + i,0x1A03,0x00,ODVAR,ODUS8,ODRD,ODNMP,4);                   //number of mapped objects  映射对象的数量
	OD_init(74 + i,0x1A03,0x01,ODVAR,ODUS32,ODRW,ODNMP,0x00);//first mapped object       第一个映射对象
	OD_init(75 + i,0x1A03,0x02,ODVAR,ODUS32,ODRW,ODNMP,0x00);//second mapped object      第二个映射对象
	OD_init(76 + i,0x1A03,0x03,ODVAR,ODUS32,ODRW,ODNMP,0x00);//third mapped object       第三个映射对象
	OD_init(77 + i,0x1A03,0x04,ODVAR,ODUS32,ODRW,ODNMP,0x00);//fourth mapped object      第四个映射对象
	//SDO
	OD_init(78 + i,0x1280,0x00,ODVAR,ODUS8,ODRW,ODNMP,3);	                              //number of entries 入口数量
	OD_init(79 + i,0x1280,0x01,ODVAR,ODUS32,ODRW,ODNMP,0x600 + ODNodeID);//COB-ID Client->Server (tx)  接受SDO 
	OD_init(80 + i,0x1280,0x02,ODVAR,ODUS32,ODRW,ODNMP,0x580 + ODNodeID);//COB-ID Server->Client (rx)  发送SDO 
	OD_init(81 + i,0x1280,0x03,ODVAR,ODUS8,ODRW,ODNMP,0x05);                         //Node-ID of the SDO server   节点号
	//HMI ObjDict
//	OD_init(82 + i,0x2020,0x00,ODVAR,ODUS16,ODRW,ODNMP,0x00);//CAN baudrate
//	OD_init(83 + i,0x2060,0x00,ODVAR,ODUS8,ODRD,ODNMP,0x03);//number of battery info
//	OD_init(84 + i,0x2060,0x01,ODVAR,ODUS16,ODRW,ODNMP,0x00);//battery SOC
//	OD_init(85 + i,0x2060,0x02,ODVAR,ODUS16,ODRW,ODNMP,0x00);//battery volt
//	OD_init(86 + i,0x2060,0x03,ODVAR,ODUS16,ODRW,ODNMP,0x00);//battery current
//	OD_init(87 + i,0x2060,0x04,ODVAR,ODUS16,ODRW,ODNMP,0x00);//error code 
//	OD_init(88 + i,0x2060,0x05,ODVAR,ODUS16,ODRW,ODNMP,0x00);//internal SOC
//	OD_init(89 + i,0x2061,0x00,ODVAR,ODUS8,ODRD,ODNMP,0x03);//number of control info
//	OD_init(90 + i,0x2061,0x01,ODVAR,ODUS16,ODRW,ODNMP,0x00);//low alm threshold
//	OD_init(91 + i,0x2061,0x02,ODVAR,ODUS16,ODRW,ODNMP,0x00);//relay logic
//	OD_init(92 + i,0x2061,0x03,ODVAR,ODUS16,ODRW,ODNMP,0x00);//backlight
//	OD_init(93 + i,0x2062,0x00,ODVAR,ODUS16,ODRW,ODNMP,0x00);//protocl type
//	OD_init(94 + i,0x2063,0x00,ODVAR,ODUS16,ODRW,ODNMP,0x00);//HourCnt low
//	OD_init(95 + i,0x2064,0x00,ODVAR,ODUS16,ODRW,ODNMP,0x00);//HourCnt high
//	OD_init(96 + i,0x2065,0x00,ODVAR,ODUS16,ODRW,ODNMP,0x00);//Switch flag
//	OD_init(97 + i,0x2066,0x00,ODVAR,ODUS16,ODRW,ODNMP,0x00);//Throttle input
//	OD_init(98 + i,0x2067,0x00,ODVAR,ODUS16,ODRW,ODNMP,0x00);//error move

	//读取控制器参数列表，用于对象字典初始化。
	for(i=0;i<256;i++)
	{
		OD_init(OD_SDOCFG_OFFSET + i,(0x2000+i),0x00,ODVAR,ODUS16,ODRW,ODNMP,*(INT16U*)cPara_Table[i]->pPrmData);//
	}
	
	//PDO buff 
	#define OD_PDOBUFF_OFFSET	(OD_SDOCFG_OFFSET+256)
	OD_init(OD_PDOBUFF_OFFSET + 0,0x2200,0x00,ODVAR,ODUS8,ODRD,ODNMP,4);//number of mapped objects
	OD_init(OD_PDOBUFF_OFFSET + 1,0x2200,0x01,ODVAR,ODUS16,ODRW,ODNMP,0x00);//first mapped object
	OD_init(OD_PDOBUFF_OFFSET + 2,0x2200,0x02,ODVAR,ODUS16,ODRW,ODNMP,0x00);//second mapped object
	OD_init(OD_PDOBUFF_OFFSET + 3,0x2200,0x03,ODVAR,ODUS16,ODRW,ODNMP,0x00);//third mapped object
	OD_init(OD_PDOBUFF_OFFSET + 4,0x2200,0x04,ODVAR,ODUS16,ODRW,ODNMP,0x00);//fourth mapped object
	
	//DS402 ObjDict
//	OD_init(99 + i,0x603F,0x00,ODVAR,ODUS16,ODRD,ODNMP,0x00);//error code
//	OD_init(100 + i,0x6040,0x00,ODVAR,ODUS16,ODRW,ODNMP,0x00);//control word
//	OD_init(101 + i,0x6041,0x00,ODVAR,ODUS16,ODRD,ODNMP,0x00);//state word
//	OD_init(102 + i,0x6060,0x00,ODVAR,ODUS16,ODRW,ODNMP,0x00);//operation mode
	
	//结束标志
	OD_init(MAX_OD_SIZE-1,0xffff,0xff,0xff,0xffff,0xff,0xff,0xffffffff);
}

/**************************************************************************
GLOBAL FUNCTIONS
***************************************************************************/

/**************************************************************************
DOES:    Call-back function for get data from ProcImg.
**************************************************************************/

/**************************************************************************
DOES:    Call-back function for occurance of node off line event.
**************************************************************************/
void Node_OffLineHandle(BYTE Node_ID)
{
}
/**************************************************************************
DOES:    Call-back function for occurance of SDO abort.
**************************************************************************/
void SDO_AbortHandle(BYTE Node_ID)
{
}
/**************************************************************************
DOES:    Call-back function for occurance of a fatal error.
Stops operation and displays blnking error pattern on LED
**************************************************************************/
void MCOUSER_FatalError (WORD ErrCode)
{
	// To Do: DEBUG, report Error Code
}
/**************************************************************************
DOES:    Call-back function for occurance of a emergency.
Do anything you need when slave node emergency msg received
**************************************************************************/

void MCO_Handle_Emergency(BYTE Node_ID)
{
}
/**************************************************************************
DOES:    Call-back function for reset application.
Starts the watchdog and waits until watchdog causes a reset.
**************************************************************************/
void MCOUSER_ResetApplication (void)
{
	while (1) // No wait until Watchdog hits
	{
	}
}


/**************************************************************************
DOES:    Call-back function for reset communication.
Re-initializes the process image and the entire MicroCANopen
communication.
**************************************************************************/
void MCOUSER_ResetCommunication (void)
{
	WORD delay;
	//ODNodeID = GetNodeID();
	ODTALE_init();

// 125kbit, Node 6, 2s heartbeat
  	MCO_Init(125,NODEID,1000);
//	CAN_Buadrate_Set(gPLCCtl.CANbaudrate);
#if NR_OF_SLAVES > 0
	//Number 0 slave, node_id 0x06,0ms heartbeat time,10ms sdo timeout, 3times to retry
	MCO_SLV_Init(0,NODEID,1000,0,3);
#endif	
  	// DEBUG: Delay 10ms for all external HW to catch up
  	delay = gTimCnt + 10;
  	while (!MCOHW_IsTimeExpired(delay))
  	{
  	}
	// RPDO1, default ID(0x200+nodeID), 1 bytes
	MCO_InitRPDO(1);
  	// RPDO2, default ID(0x300+nodeID), 2 bytes
	MCO_InitRPDO(2);
	// RPDO3, TPDO1 OF NODE 0X07, 2 bytes
	MCO_InitRPDO(3);

// TPDO1, default ID (0x180+nodeID), 0ms event, 0ms inhibit, 2 bytes
	MCO_InitTPDO(1);
// TPDO2, default ID (0x280+nodeID), 0ms event, 0ms inhibit, 2 bytes
	MCO_InitTPDO(2);
//// TPDO3, default ID (0x380+nodeID), 0ms event, 0ms inhibit, 2 bytes
//	MCO_InitTPDO(3);
//// TPDO4, default ID (0x480+nodeID), 0ms event, 0ms inhibit, 2 bytes
//	MCO_InitTPDO(4);
}

//保存CANopen OD数据
//Flag=1:保存至RAM
//Flag=2:保存至EEPROM
INT16U	SavePara(INT16U Index, INT8U Flag)  
{
	PRM_DEF_STRUCT *pPrmDef;
	INT16U ret;
	
	pPrmDef = (PRM_DEF_STRUCT*)(cPara_Table[Index]);
	if(Flag==1)
	{		
		if((*(INT16U*)pPrmDef->pPrmData > (INT16U)pPrmDef->PrmMaxVal) || (*(INT16U*)pPrmDef->pPrmData < (INT16U)pPrmDef->PrmMinVal))
		{
			ret = 1;
		}
		else
		{
			*(INT16U*)pPrmDef->pPrmData = OD[MCO_Search_ODTABLE(0x2000+Index,0x00)].Val;
			ret = 0;
		}
	}
	else	if(Flag==2)
	{
		*(INT16U*)pPrmDef->pPrmData = OD[MCO_Search_ODTABLE(0x2000+Index,0x00)].Val;
		ret = SaveParaToEeprom(Index, *(INT16U*)pPrmDef->pPrmData);
		
	}
	
	if(ret==1)
			MCO_Send_SDO_Abort(0x06070010UL);
	return ret;
}

//Thsi function called when PDORX massage received。
//@para: i, the index number of RPDO
void PDORX_user_callback(int i)
{
	INT16U MoveState = 0;
	INT16U ErrMove = 0;
	if(i==0)	//first RPDO
	{
		MoveState = OD[MCO_Search_ODTABLE(0x2200,0x01)].Val&0xFF;
		ErrMove = (OD[MCO_Search_ODTABLE(0x2200,0x01)].Val>>8)&0xFF;
	}
	else if(i==1)	//second RPDO
	{
		
	}	
}

/**************************************************************************
END-OF-FILE
***************************************************************************/
