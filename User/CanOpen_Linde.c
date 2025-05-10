/*******************************************************************************
* Filename: CANOPEN_LINDE.c	                                           *
* Description:	QExpand_canopen_profile										   			 		   			 *
* Author:  QExpand, Chow                                                       *
* Date:  2024/05/24   														 		   *
* Revision:	1.04														 		   *
*******************************************************************************/

//#include	"canSTM32F4.h"
#include  "iCAN.h"
#include	"CommonRam.h"
#include "CanOpen_Linde.h"

#if (CANOPEN_TYPE == CANOPEN_LINDE)

#define DATA_TYPE_MASK            (1 << 8)
#define DATA_TYPE_HEX             (0 << 8)
#define DATA_TYPE_BCD             (1 << 8)
const INT16U LINDE_SDOTAB[256]=
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
		210,	211,	212,	DATA_TYPE_BCD|213,	DATA_TYPE_BCD|214,	DATA_TYPE_BCD|215,	DATA_TYPE_BCD|216,	DATA_TYPE_BCD|217,	218,	219,
		220,	221,	222,	223,	224,	225,	226,	227,	228,	229,
		230,	231,	232,	233,	234,	235,	236,	237,	238,	239,
		240,	241,	242,	243,	244,	245,	246,	247,	248,	249,
		250,	251,	252,	253,	254,	255	
};


const INT16U LINDE_CONFIGURE_LIMIT_START[256]=
{
//      00,  01,  02,  03,  04,  05,  06,   07,  08,  09,
		0,	 0,   0,    0,  20,	  0,	1,	16,	 16,  10, //0
		1,	 1,	  1,   1000,4096,600,600,	300, 100,1638, //10
		1638,1638,1638,1638,1638,1638,1638,1638,1638,1638, //20
		1638,1638,1638,1638,1638,1638,512,	0,	 0,	  25, //30
		25,	300,  0,	0,	0,	 0,	  0,	0,	300,  300, //40
		100, 5,	  5,   10,	10,	 0,   0,	100,100,  0, //50
		0,	100,  100, 100,	100, 100, 100,	100,100,  100, //60
		100,100,  0,   0,	0,	 100, 100,	0,	0,	  0, //70
		0,	0,	  5,   5,	100, 0,	  5,	512,512,  512, //80
		512,0,	  0,   0,	0,	 0,	  0,	0,	0,	  0, //90
		0,	0,	  0,   0,	0,	 0,	 1638,	0,	0,	  0, //100
		0,	0,	  0,   0,	0,	 0,	 0,	    0,	0,	  0, //110
		0,	100,  0,   0,	1,	 1,	 1,	    40,	0,	  0, //120
		0,	0,	  0,   0,	0,	 0,	 1,	    0,	0,	  0, //130
		0,	0,	  0,   0,	0,	 5,	 0,	    1638,0,	  5, //140
		10,	328,  82,  0,	0,	 10, 0,	    10,	 0,	  600, //150
		100,100,  10,  10,	0,	 0,	 0,	    0,	 0,	  0, //160
		0,	0,	  0,   0,	0,	 0,	 0,	    0,	 0,	  0, //170
		0,	0,	  0,   0,	0,	 0,	 0,	    0,	 0,	  0, //180
		0,	0,	  1,   1,	1,	 4,	 0,	    0,	 0,	  0, //190
		0,	0,	  0,   0,	0,	 0,	 0,	    0,	 0,	  0, //200
		0,	0,	  0,   0,	0,	 0,	 0,	    0,	 0,	  0, //210
		0,	0,	  0,   0,	0,	 0,	 0,	    0,	 0,	  0, //220
		0,	0,	  0,   0,	0,	 0,	 0,	    0,	 0,	  0, //230
		15,	10,	  0,   0,	0,	 0,	 0,	    0,	 0,	  0, //240
		0,	0,	  0,   0,	0,   0		
};

const INT16U LINDE_CONFIGURE_LIMIT_END[256]=
{
//      00,   01,    02,    03,    04,    05,    06,    07,    08,    09,
		0,    255,   255,   255,   255,   400,   255,	32,	   4096,  65535, //0
		65535,65535, 65535, 65535, 32767, 20000, 30000,	15000, 3500,  32767, //10
		32767,32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, //20
		32767,32767, 32767, 32767, 32767, 32767, 32767, 8,     65515,     250, //30  //38# ---> -20
		250,  30000, 0,	    0,	   0,	  0,	 0,	    0,	   30000,  30000, //40
		1200, 200,	 200,   1600,  1600,  100,   5000,	5000,  2000,   5000, //50
		5000, 5000,  2000,  30000, 30000, 30000, 30000,	30000, 30000,  30000, //60
		30000,30000, 32767, 32767, 32767, 30000, 30000,	100,   100,	   100, //70
		100,  2000,	 100,   100,   5000,  3,	 100,	32767, 32767,  32767, //80
		32767,255,	 500,   500,   500,	  32767, 500,	500,   500,	   32767, //90
		250,  255,	 150,   150,   100,	  32767, 32767,	0,	   0,	   0, //100
		0,	  0,	  0,   0,	   0,	  0,	 0,	    150,   150,	   150, //110
		32767,32767, 30000, 30000, 3281,  3281,	 3281,	65535,	255,	  0, //120
		0,	  255,	 255,   100,   100,	  5000,	 8000,	100,   100,	   100, //130
		100,  2,	 100,   100,   100,	  250,	 15000,	32767, 100,	   100, //140
		30000,32767, 8192,  2000,  2000,  500,   100,	10000, 30001,  2000, //150
		3000, 1000,  100, 100,	0,	 0,	 0,	    0,	 0,	  0, //160
		0,	0,	  0,   0,	0,	 0,	 0,	    0,	 0,	  0, //170
		0,	0,	  0,   0,	0,	 0,	 0,	    0,	 0,	  0, //180
		255,1000, 200,32767,32767,8192,16384,16384,65535,65535, //190   /*** 198  199运行修改负值***/
		0,	0,	  0,   0,	0,	 0,	 0,	    0,	 0,	  0, //200
		0,	0,	  0,   0,	0,	 0,	 0,	    0,	 0,	  0, //210
		0,	0,	  0,   0,	0,	 0,	 0,	    0,	 0,	  0, //220
		0,	0,	  0,   0,	0,	 0,	 0,	    0,	 0,	  0, //230
		30,	25,	  0,   0,	0,	 0,	 0,	    0,	 0,	  0, //240
		0,	0,	  0,   0,	0,   0	
};

tQEXPANDAGV_PDO	QExpandAGV_PDO;
/*******************************************************************************
* Name: QExpandAGVInit
* Description: Initialise the default data following power on
* Input: pointer to the data structure
* Output: 
*					0- 
*					1- Success
* Author: 
* Date: 
* Revision:
*******************************************************************************/
INT16S CanOpenInit (void)
{
	INT32S index;
	tQEXPANDAGV_PDO  *pQExpandAGV_PDO;
	
	pQExpandAGV_PDO = &QExpandAGV_PDO;
	for (index = 0; index < sizeof(tQEXPANDAGV_PDO); index++)
	{
		((INT8U*)pQExpandAGV_PDO)[index] = 0;
	}
	
	if((gPara.ConBit2>>6)&0x01)	//NMT auto 
		QExpandAGV_PDO.AgvMode = 1;	
	return 1;
}

/*******************************************************************************
* Name: CanOpenRxFrame
* Description: Transmit buf data frame.  Called by plc per 5ms 
* Input: none
* Output: none
*
* Author: 
* Date: 
* Revision:
*******************************************************************************/
INT16S CanOpenRxFrame (tCANFrame  *pCANFrame)
{
	INT32S flag;
	
	flag = 1;
	if (pCANFrame->ucXID == 0)
	{
		if (pCANFrame->ulID == (NMT_MSG_ID))  //NMT message 
		{
			QExpandAGV_PDO.AgvMode = pCANFrame->ucData[0];
		}
		else if (pCANFrame->ulID == (QEXPANDAGVPDORX1_ID_OFS + QEXPANDAGVPDO_ID))		
		{
			QExpandAGV_PDO.CanBuf_ID1X0R[0] = pCANFrame->ucData[0];
			QExpandAGV_PDO.CanBuf_ID1X0R[1] = pCANFrame->ucData[1];
			QExpandAGV_PDO.CanBuf_ID1X0R[2] = pCANFrame->ucData[2];
			QExpandAGV_PDO.CanBuf_ID1X0R[3] = pCANFrame->ucData[3];
			QExpandAGV_PDO.CanBuf_ID1X0R[4] = pCANFrame->ucData[4];
			QExpandAGV_PDO.CanBuf_ID1X0R[5] = pCANFrame->ucData[5];
			QExpandAGV_PDO.CanBuf_ID1X0R[6] = pCANFrame->ucData[6];
			QExpandAGV_PDO.CanBuf_ID1X0R[7] = pCANFrame->ucData[7];
			QExpandAGV_PDO.CanBuf_ID1X0R_Delay = 0;
			QExpandAGV_PDO.CanBufRxState |= RX200_CANBUFRXSTATE;
		}
		else if (pCANFrame->ulID == (QEXPANDAGVPDORX4_ID_OFS + QEXPANDAGVPDO_ID))
		{
			QExpandAGV_PDO.CanBuf_ID1X1R[0] = pCANFrame->ucData[0];
			QExpandAGV_PDO.CanBuf_ID1X1R[1] = pCANFrame->ucData[1];
			QExpandAGV_PDO.CanBuf_ID1X1R[2] = pCANFrame->ucData[2];
			QExpandAGV_PDO.CanBuf_ID1X1R[3] = pCANFrame->ucData[3];
			QExpandAGV_PDO.CanBuf_ID1X1R[4] = pCANFrame->ucData[4];
			QExpandAGV_PDO.CanBuf_ID1X1R[5] = pCANFrame->ucData[5];
			QExpandAGV_PDO.CanBuf_ID1X1R[6] = pCANFrame->ucData[6];
			QExpandAGV_PDO.CanBuf_ID1X1R[7] = pCANFrame->ucData[7];
			QExpandAGV_PDO.CanBuf_ID1X1R_Delay = 0;
			QExpandAGV_PDO.CanBufRxState |= RX500_CANBUFRXSTATE; 
		}
		else if(pCANFrame->ulID == (QEXPANDAGVSDORX_ID_OFS))
		{
			QExpandAGV_PDO.CanBuf_IDSDOR[0] = pCANFrame->ucData[0];
			QExpandAGV_PDO.CanBuf_IDSDOR[1] = pCANFrame->ucData[1];
			QExpandAGV_PDO.CanBuf_IDSDOR[2] = pCANFrame->ucData[2];
			QExpandAGV_PDO.CanBuf_IDSDOR[3] = pCANFrame->ucData[3];
			QExpandAGV_PDO.CanBuf_IDSDOR[4] = pCANFrame->ucData[4];
			QExpandAGV_PDO.CanBuf_IDSDOR[5] = pCANFrame->ucData[5];
			QExpandAGV_PDO.CanBuf_IDSDOR[6] = pCANFrame->ucData[6];
			QExpandAGV_PDO.CanBuf_IDSDOR[7] = pCANFrame->ucData[7];
			QExpandAGV_PDO.CanBuf_IDSDOR_Delay = 0;
			QExpandAGV_PDO.CanBufRxState |= RXSDO_CANBUFRXSTATE;
		}
		if (pCANFrame->ulID == (0x260))
		{
			QExpandAGV_PDO.CanBuf_ID260R[0] = pCANFrame->ucData[0];
			QExpandAGV_PDO.CanBuf_ID260R[1] = pCANFrame->ucData[1];
			QExpandAGV_PDO.CanBuf_ID260R[2] = pCANFrame->ucData[2];
			QExpandAGV_PDO.CanBuf_ID260R[3] = pCANFrame->ucData[3];
			QExpandAGV_PDO.CanBuf_ID260R[4] = pCANFrame->ucData[4];
			QExpandAGV_PDO.CanBuf_ID260R[5] = pCANFrame->ucData[5];
			QExpandAGV_PDO.CanBuf_ID260R[6] = pCANFrame->ucData[6];
			QExpandAGV_PDO.CanBuf_ID260R[7] = pCANFrame->ucData[7];
			QExpandAGV_PDO.CanBuf_ID260R_Delay = 0;
			QExpandAGV_PDO.CanBufRxState |= RX260_CANBUFRXSTATE;
		}
		else
			flag = 0;
	}
	else
	{
		flag = 0;
	}
	
	return flag;	
}

INT16S CanOpenRxFrameMonitor(void)
{
	if(QExpandAGV_PDO.CanBufRxState & RX260_CANBUFRXSTATE)	//PDO Tx enable
	{
		if (QExpandAGV_PDO.CanBuf_ID260R_Delay >= RX_TIMEOUT)
		{
	//		QExpandAGV_PDO.CanBuf_ID1X0R_Delay = 0;		
			QExpandAGV_PDO.AgvHeartBeatError = 1;
		}
		else
		{
			QExpandAGV_PDO.CanBuf_ID260R_Delay += 1;
			QExpandAGV_PDO.AgvHeartBeatError = 0;
		}
	}
	else
	{
		if (QExpandAGV_PDO.CanBuf_ID260R_Delay >= (RX_TIMEOUT*10))
		{	
			QExpandAGV_PDO.AgvHeartBeatError = 1;
		}
		else
		{
			QExpandAGV_PDO.CanBuf_ID260R_Delay += 1;
			QExpandAGV_PDO.AgvHeartBeatError = 0;
		}	
	}
		
	
	return 1;
}
/*******************************************************************************
* Name: Emergency_Msg_send
* Description: Emergency message,send one time on alarm change
* Input: none
* Output: none
*
* Author: 
* Date: 
* Revision:
*******************************************************************************/
void Emergency_Msg_send(INT8U AlramCode)
{
	static INT8U AlramCodelast=0;
	tCANFrame canFrame;	
	
//	if(QExpandAGV_PDO.AgvMode == 1)	//PDO Tx enable
	{
		if(AlramCode!=AlramCodelast)
		{
			canFrame.ulID = (EMERG_MSG_ID_OFS + QEXPANDAGVPDO_ID);
			canFrame.ucXID=0;			//0 standard frame;  1 extended frame
			canFrame.ucDataLength=8;	

			canFrame.ucData[0] = AlramCode;
			canFrame.ucData[1] = 0;
			canFrame.ucData[2] = 0x00;
            if(AlramCode != 0)
                canFrame.ucData[3] = 1;
            else
                canFrame.ucData[3] = 0;
			canFrame.ucData[4] = 0;
			canFrame.ucData[5] = AlramCode;
			canFrame.ucData[6] = 0;
			CANWriteBuffer(&canFrmTxBuffer, &canFrame);	
		}
		AlramCodelast = AlramCode;
	}
}

/*******************************************************************************
* Name: CanOpenTxFrame
* Description: Transmit buf data frame.  Called by plc per 5ms 
* Input: none
* Output: none
*
* Author: 
* Date: 
* Revision:
*******************************************************************************/
INT16S CanOpenTxFrame (void)
{
	tCANFrame canFrame;	//
	tQEXPANDAGV_PDO *pQExpandAGV_PDO;
	pQExpandAGV_PDO = &QExpandAGV_PDO;
			
    if((pQExpandAGV_PDO->TxCnt & 3) == 0)
    {
       //pQExpandAGV_PDO->u8HeartBeatTrig ^= 0x01;
        
       canFrame.ulID = HEARTBEAT_ID_OFS + QEXPANDAGVPDO_ID;
       canFrame.ucXID = 0;
       canFrame.ucDataLength = 1;
        
       canFrame.ucData[0] = 0x05;
       CANWriteBuffer(&canFrmTxBuffer, &canFrame);
        
    }
	if (pQExpandAGV_PDO->TxCnt == TX_PERIOD_ID1X8T)
	{
			canFrame.ulID = (QEXPANDAGVPDOTX1_ID_OFS + QEXPANDAGVPDO_ID);
			canFrame.ucXID=0;			//0 standard frame;  1 extended frame
			canFrame.ucDataLength=8;	

			canFrame.ucData[0] = pQExpandAGV_PDO->CanBuf_ID1X8T[0];
			canFrame.ucData[1] = pQExpandAGV_PDO->CanBuf_ID1X8T[1];
			canFrame.ucData[2] = pQExpandAGV_PDO->CanBuf_ID1X8T[2];
			canFrame.ucData[3] = pQExpandAGV_PDO->CanBuf_ID1X8T[3];
			canFrame.ucData[4] = pQExpandAGV_PDO->CanBuf_ID1X8T[4];
			canFrame.ucData[5] = pQExpandAGV_PDO->CanBuf_ID1X8T[5];
			canFrame.ucData[6] = pQExpandAGV_PDO->CanBuf_ID1X8T[6];
			canFrame.ucData[7] = pQExpandAGV_PDO->CanBuf_ID1X8T[7];
			CANWriteBuffer(&canFrmTxBuffer, &canFrame);
	}
	if (pQExpandAGV_PDO->TxCnt == TX_WINDOW_ID1X9T)
	{
			canFrame.ulID = (QEXPANDAGVPDOTX2_ID_OFS + QEXPANDAGVPDO_ID);
			canFrame.ucXID=0;			//0 standard frame;  1 extended frame
			canFrame.ucDataLength=8;	

			canFrame.ucData[0] = pQExpandAGV_PDO->CanBuf_ID1X9T[0];
			canFrame.ucData[1] = pQExpandAGV_PDO->CanBuf_ID1X9T[1];
			canFrame.ucData[2] = pQExpandAGV_PDO->CanBuf_ID1X9T[2];
			canFrame.ucData[3] = pQExpandAGV_PDO->CanBuf_ID1X9T[3];
			canFrame.ucData[4] = pQExpandAGV_PDO->CanBuf_ID1X9T[4];
			canFrame.ucData[5] = pQExpandAGV_PDO->CanBuf_ID1X9T[5];
			canFrame.ucData[6] = pQExpandAGV_PDO->CanBuf_ID1X9T[6];
			canFrame.ucData[7] = pQExpandAGV_PDO->CanBuf_ID1X9T[7];
			CANWriteBuffer(&canFrmTxBuffer, &canFrame);
	}
	if (pQExpandAGV_PDO->TxCnt == TX_WINDOW_ID1XAT)
	{
			canFrame.ulID = (QEXPANDAGVPDOTX3_ID_OFS + QEXPANDAGVPDO_ID);
			canFrame.ucXID=0;			//0 standard frame;  1 extended frame
			canFrame.ucDataLength=8;	

			canFrame.ucData[0] = pQExpandAGV_PDO->CanBuf_ID1XAT[0];
			canFrame.ucData[1] = pQExpandAGV_PDO->CanBuf_ID1XAT[1];
			canFrame.ucData[2] = pQExpandAGV_PDO->CanBuf_ID1XAT[2];
			canFrame.ucData[3] = pQExpandAGV_PDO->CanBuf_ID1XAT[3];
			canFrame.ucData[4] = pQExpandAGV_PDO->CanBuf_ID1XAT[4];
			canFrame.ucData[5] = pQExpandAGV_PDO->CanBuf_ID1XAT[5];
			canFrame.ucData[6] = pQExpandAGV_PDO->CanBuf_ID1XAT[6];
			canFrame.ucData[7] = pQExpandAGV_PDO->CanBuf_ID1XAT[7];
			CANWriteBuffer(&canFrmTxBuffer, &canFrame);
	}
//    if (pQExpandAGV_PDO->TxCnt == TX_WINDOW_ID1XBT)
//    {
//            canFrame.ulID = (QEXPANDAGVPDOTX4_ID_OFS + QEXPANDAGVPDO_ID);
//            canFrame.ucXID=0;			//0 standard frame;  1 extended frame
//            canFrame.ucDataLength=8;	

//            canFrame.ucData[0] = pQExpandAGV_PDO->CanBuf_ID1XBT[0];
//            canFrame.ucData[1] = pQExpandAGV_PDO->CanBuf_ID1XBT[1];
//            canFrame.ucData[2] = pQExpandAGV_PDO->CanBuf_ID1XBT[2];
//            canFrame.ucData[3] = pQExpandAGV_PDO->CanBuf_ID1XBT[3];
//            canFrame.ucData[4] = pQExpandAGV_PDO->CanBuf_ID1XBT[4];
//            canFrame.ucData[5] = pQExpandAGV_PDO->CanBuf_ID1XBT[5];
//            canFrame.ucData[6] = pQExpandAGV_PDO->CanBuf_ID1XBT[6];
//            canFrame.ucData[7] = pQExpandAGV_PDO->CanBuf_ID1XBT[7];
//            CANWriteBuffer(&canFrmTxBuffer, &canFrame);
//    }	
	
	if ((pQExpandAGV_PDO->CanBufTxState & TXSDO_CANBUFRXSTATE) != 0)
	{
		pQExpandAGV_PDO->CanBufTxState &= ~TXSDO_CANBUFRXSTATE;
		
		canFrame.ulID = (QEXPANDAGVSDOTX_ID_OFS);
		canFrame.ucXID=0;			//0 standard frame;  1 extended frame
		canFrame.ucDataLength=8;	

		canFrame.ucData[0] = pQExpandAGV_PDO->CanBuf_IDSDOT[0];
		canFrame.ucData[1] = pQExpandAGV_PDO->CanBuf_IDSDOT[1];
		canFrame.ucData[2] = pQExpandAGV_PDO->CanBuf_IDSDOT[2];
		canFrame.ucData[3] = pQExpandAGV_PDO->CanBuf_IDSDOT[3];
		canFrame.ucData[4] = pQExpandAGV_PDO->CanBuf_IDSDOT[4];
		canFrame.ucData[5] = pQExpandAGV_PDO->CanBuf_IDSDOT[5];
		canFrame.ucData[6] = pQExpandAGV_PDO->CanBuf_IDSDOT[6];
		canFrame.ucData[7] = pQExpandAGV_PDO->CanBuf_IDSDOT[7];
		CANWriteBuffer(&canFrmTxBuffer, &canFrame);
	}
	
//	if(pQExpandAGV_PDO->IsInAlarm)
		Emergency_Msg_send(pQExpandAGV_PDO->ErrorCode);

	pQExpandAGV_PDO->TxCnt += 1;
	if (pQExpandAGV_PDO->TxCnt >= TX_PERIOD)
		pQExpandAGV_PDO->TxCnt = 0;
	
	return 1;
}


/*******************************************************************************
* Name: CanOpenUpdatePlcDataFromRxbuf
* Description: Update PLC data from RX bufID. 
* Input: none
* Output: none
*
* Author: 
* Date: 
* Revision:
*******************************************************************************/
INT16S CanOpenUpdatePlcDataFromRxbuf(void)
{
	tQEXPANDAGV_PDO *pQExpandAGV_PDO;
	pQExpandAGV_PDO = &QExpandAGV_PDO;

	//PDO RX1
	pQExpandAGV_PDO->VCUControlWord = (pQExpandAGV_PDO->CanBuf_ID1X0R[1] << 8) | pQExpandAGV_PDO->CanBuf_ID1X0R[0];
	pQExpandAGV_PDO->VCUCmdSpeed = (pQExpandAGV_PDO->CanBuf_ID1X0R[3] << 8) | pQExpandAGV_PDO->CanBuf_ID1X0R[2];
	pQExpandAGV_PDO->VCUCmdAngle =(pQExpandAGV_PDO->CanBuf_ID1X0R[5] << 8) | pQExpandAGV_PDO->CanBuf_ID1X0R[4];
	pQExpandAGV_PDO->VCUCmdTorque = pQExpandAGV_PDO->CanBuf_ID1X0R[6];
	pQExpandAGV_PDO->VCUCmdTorqueBrk = pQExpandAGV_PDO->CanBuf_ID1X0R[7];
	//PDO RX2
	pQExpandAGV_PDO->VCUPedalBrake = pQExpandAGV_PDO->CanBuf_ID1X1R[0];
	pQExpandAGV_PDO->VCUCmdPump = pQExpandAGV_PDO->CanBuf_ID1X1R[1];	
	pQExpandAGV_PDO->VCUCmdEVP = pQExpandAGV_PDO->CanBuf_ID1X1R[2];
	pQExpandAGV_PDO->VCUCmdEVP1 = pQExpandAGV_PDO->CanBuf_ID1X1R[3];

	pQExpandAGV_PDO->ErrorMove = pQExpandAGV_PDO->CanBuf_ID260R[1];
	pQExpandAGV_PDO->MoveSpeedFdb = pQExpandAGV_PDO->CanBuf_ID260R[3];
	
	//KWP2000协议 （兼容林德专用诊断工具）
	if (1)//((pQExpandAGV_PDO->DgnDataRxTx.Flag & (RX_FLAG | RDOP_FLAG | WROP_FLAG | TX_FLAG)) == 0)
	{  
		if ((pQExpandAGV_PDO->CanBufRxState & RXSDO_CANBUFRXSTATE) != 0)
		{					
			pQExpandAGV_PDO->DgnDataRxTx.UserByte = pQExpandAGV_PDO->CanBuf_IDSDOR[0];
			pQExpandAGV_PDO->DgnDataRxTx.FuncCode = pQExpandAGV_PDO->CanBuf_IDSDOR[1];
			pQExpandAGV_PDO->DgnDataRxTx.Index = pQExpandAGV_PDO->CanBuf_IDSDOR[2];
			pQExpandAGV_PDO->DgnDataRxTx.DataL16 = (pQExpandAGV_PDO->CanBuf_IDSDOR[4] <<8) | pQExpandAGV_PDO->CanBuf_IDSDOR[3];
			pQExpandAGV_PDO->DgnDataRxTx.DataH16 = (pQExpandAGV_PDO->CanBuf_IDSDOR[6] <<8) | pQExpandAGV_PDO->CanBuf_IDSDOR[5];
			pQExpandAGV_PDO->DgnDataRxTx.Flag |= RX_FLAG ;			
			if((pQExpandAGV_PDO->DgnDataRxTx.UserByte == 0x02) &&(pQExpandAGV_PDO->DgnDataRxTx.FuncCode == READ_REQUWST))
			{//监控数据查询
				if((pQExpandAGV_PDO->DgnDataRxTx.Index > MONITOR_PARA_END)||((pQExpandAGV_PDO->DgnDataRxTx.Index > CONFIGURE_PARA_END)&&(pQExpandAGV_PDO->DgnDataRxTx.Index < MONITOR_PARA_START)))
				{//参数超限 超过监控参数/配置和监控参数之中          
					pQExpandAGV_PDO->DgnDataRxTx.FuncCode = READ_ANSWER_FAIL; 	//0x7F
					pQExpandAGV_PDO->DgnDataRxTx.DataL16 = MODIFY_ANSWER_FAIL_1; //参数超限
					pQExpandAGV_PDO->DgnDataRxTx.DataH16 = 0xAAAA;
					pQExpandAGV_PDO->DgnDataRxTx.Flag |= TX_FLAG;
				}
				else
				{					
					if ((pQExpandAGV_PDO->DgnDataRxTx.Index >= CONFIGURE_PARA_START)&&(pQExpandAGV_PDO->DgnDataRxTx.Index <= CONFIGURE_PARA_END))
					{//回读配置参数
						pQExpandAGV_PDO->DgnDataRxTx.Flag |= TX_FLAG;//RDOP_FLAG;

						pQExpandAGV_PDO->DgnDataRxTx.FuncCode = READ_ANSWER_SUCCESS;  //0x61
						pQExpandAGV_PDO->DgnDataRxTx.DataL16 = ReadParaValByIndex(LINDE_SDOTAB[pQExpandAGV_PDO->DgnDataRxTx.Index]);
							
						if((pQExpandAGV_PDO->DgnDataRxTx.DataL16 & 0xFF00) == 0)
						{
							pQExpandAGV_PDO->DgnDataRxTx.DataL16 |= 0x0000;
						}

						pQExpandAGV_PDO->DgnDataRxTx.DataH16 = 0xAAAA;
					}
					else if((pQExpandAGV_PDO->DgnDataRxTx.Index >= MONITOR_PARA_START)&&(pQExpandAGV_PDO->DgnDataRxTx.Index <= MONITOR_PARA_END))
					{//监控数据
						INT16U MonitorDataVal = 0;
						pQExpandAGV_PDO->DgnDataRxTx.FuncCode = READ_ANSWER_SUCCESS;  //0x61
						MonitorDataVal = ReadMonitorParaValByIndex(pQExpandAGV_PDO->DgnDataRxTx.Index);
						if ((LINDE_SDOTAB[pQExpandAGV_PDO->DgnDataRxTx.Index] & DATA_TYPE_MASK)  == DATA_TYPE_BCD)
						{
							MonitorDataVal = ((MonitorDataVal >> 0) & 0xF) 
											 + ((MonitorDataVal >> 4) & 0xF) * 10 
											 + ((MonitorDataVal >> 8) & 0xF) * 100 
											 + ((MonitorDataVal >> 12) & 0xF) * 1000; 
						}
//						if((MonitorDataVal & 0xFF00) == 0)
//						{
//							MonitorDataVal |= 0xAA00;					//高位为0 AA占位
//						}

						pQExpandAGV_PDO->DgnDataRxTx.DataL16 = MonitorDataVal;
						pQExpandAGV_PDO->DgnDataRxTx.DataH16 = 0xAAAA;
						pQExpandAGV_PDO->DgnDataRxTx.Flag |= TX_FLAG;
					}
					else
					{//参数异常
						pQExpandAGV_PDO->DgnDataRxTx.FuncCode = READ_ANSWER_FAIL; 	//0x7F
						pQExpandAGV_PDO->DgnDataRxTx.DataL16 = MODIFY_ANSWER_FAIL_1; //参数超限
						pQExpandAGV_PDO->DgnDataRxTx.DataH16 = 0xAAAA;
						pQExpandAGV_PDO->DgnDataRxTx.Flag |= TX_FLAG;						
					}
				}
			}
			else if(pQExpandAGV_PDO->DgnDataRxTx.FuncCode == MODIFY_REQUEST)
			{//更改参数
				if((pQExpandAGV_PDO->DgnDataRxTx.UserByte >= 5)||(pQExpandAGV_PDO->DgnDataRxTx.UserByte <= 2))
				{//写入条件错误
					pQExpandAGV_PDO->DgnDataRxTx.FuncCode = MODIFY_ANSWER_FAIL; 
					pQExpandAGV_PDO->DgnDataRxTx.DataL16 = MODIFY_ANSWER_FAIL_2;
					pQExpandAGV_PDO->DgnDataRxTx.DataH16 = 0xAAAA;
					pQExpandAGV_PDO->DgnDataRxTx.Flag |= TX_FLAG;
				}
				else if((pQExpandAGV_PDO->DgnDataRxTx.Index <= CONFIGURE_PARA_END)||((pQExpandAGV_PDO->DgnDataRxTx.Index >= CONFIGURE_PARA_START)))
				{//参数在配置参数范围内，开放更改				
					if(pQExpandAGV_PDO->DgnDataRxTx.UserByte  == 3)
					{//有效字节为3 高8位为无效数据
						pQExpandAGV_PDO->DgnDataRxTx.DataL16 &= 0x00FF;
					}
					
					if((pQExpandAGV_PDO->DgnDataRxTx.DataL16 >= LINDE_CONFIGURE_LIMIT_START[pQExpandAGV_PDO->DgnDataRxTx.Index])
						&&(pQExpandAGV_PDO->DgnDataRxTx.DataL16 <= LINDE_CONFIGURE_LIMIT_END[pQExpandAGV_PDO->DgnDataRxTx.Index]))
					{										
						if((pQExpandAGV_PDO->DgnDataRxTx.DataL16 & 0xFF00) == 0xAA00)
						{
							pQExpandAGV_PDO->DgnDataRxTx.DataL16 &= 0x00FF;
						}						
						
						INT8U ret = EepromQualifiedWrite(LINDE_SDOTAB[pQExpandAGV_PDO->DgnDataRxTx.Index],pQExpandAGV_PDO->DgnDataRxTx.DataL16);
						
						pQExpandAGV_PDO->DgnDataRxTx.Flag |= TX_FLAG;//WROP_FLAG;
						if(ret)	//failed
						{
							pQExpandAGV_PDO->DgnDataRxTx.FuncCode = MODIFY_ANSWER_FAIL; 						
						}
						else
						{
							pQExpandAGV_PDO->DgnDataRxTx.DataL16 = 0xAAAA;
							pQExpandAGV_PDO->DgnDataRxTx.FuncCode = MODIFY_ANSWER_SUCCESS;
						}
						if((pQExpandAGV_PDO->DgnDataRxTx.DataL16 & 0xFF00) == 0)
						{
							pQExpandAGV_PDO->DgnDataRxTx.DataL16 |= 0xAA00;					//高位为0 AA占位
						}

						pQExpandAGV_PDO->DgnDataRxTx.DataH16 = 0xAAAA;
					}
					else
					{
						pQExpandAGV_PDO->DgnDataRxTx.FuncCode = MODIFY_ANSWER_FAIL; 
						pQExpandAGV_PDO->DgnDataRxTx.DataL16 = MODIFY_ANSWER_FAIL_3;
						pQExpandAGV_PDO->DgnDataRxTx.DataH16 = 0xAAAA;
						pQExpandAGV_PDO->DgnDataRxTx.Flag |= TX_FLAG;	
					}
				}
				else if((pQExpandAGV_PDO->DgnDataRxTx.Index > CONFIGURE_PARA_END))			
				{//参数超限
					pQExpandAGV_PDO->DgnDataRxTx.FuncCode = MODIFY_ANSWER_FAIL; 
					pQExpandAGV_PDO->DgnDataRxTx.DataL16 = MODIFY_ANSWER_FAIL_2;
					pQExpandAGV_PDO->DgnDataRxTx.DataH16 = 0xAAAA;
					pQExpandAGV_PDO->DgnDataRxTx.Flag |= TX_FLAG;					
				}
				else
					pQExpandAGV_PDO->DgnDataRxTx.Flag &= ~RX_FLAG ;
			}
			else
			{//无效控制字
			   pQExpandAGV_PDO->DgnDataRxTx.Flag &= ~RX_FLAG ;
			}
			pQExpandAGV_PDO->CanBufRxState &= ~RXSDO_CANBUFRXSTATE;
		}
	}

	return 1;	
}
/*******************************************************************************
* Name: CanOpenUpdateTxbufFromPlcData
* Description: Update TX bufID from PLC data. 
* Input: none
* Output: none
*
* Author: 
* Date: 
* Revision:
*******************************************************************************/
INT16S CanOpenUpdateTxbufFromPlcData(void)
{
    INT8U ErrFlag = 0;
	tQEXPANDAGV_PDO *pQExpandAGV_PDO;
	pQExpandAGV_PDO = &QExpandAGV_PDO;

	//DATA from MCU to VCU
    //0x190  0x290 0x390 -> 1X8 1X9 1XA
    if(pQExpandAGV_PDO->AngleMeasured < 0 )
        pQExpandAGV_PDO->AngleMeasured = -pQExpandAGV_PDO->AngleMeasured;
    if(gPara.ErrCode != 0)
        ErrFlag = 1;
    else 
        ErrFlag = 0;
    
	pQExpandAGV_PDO->CanBuf_ID1X8T[0] = (pQExpandAGV_PDO->AngleMeasured) & 0xFF;
	pQExpandAGV_PDO->CanBuf_ID1X8T[1] = (pQExpandAGV_PDO->AngleMeasured >> 8) & 0xFF;
	pQExpandAGV_PDO->CanBuf_ID1X8T[2] = 0;
	pQExpandAGV_PDO->CanBuf_ID1X8T[3] = 0;
	pQExpandAGV_PDO->CanBuf_ID1X8T[4] = (pQExpandAGV_PDO->SpeedMeasured) & 0xFF;;
	pQExpandAGV_PDO->CanBuf_ID1X8T[5] = (pQExpandAGV_PDO->SpeedMeasured >> 8) & 0xFF;;
	pQExpandAGV_PDO->CanBuf_ID1X8T[6] = (pQExpandAGV_PDO->CurrentMeasured) & 0xFF;
	pQExpandAGV_PDO->CanBuf_ID1X8T[7] = (pQExpandAGV_PDO->CurrentMeasured >> 8) & 0xFF;
    
    pQExpandAGV_PDO->CanBuf_ID1X9T[0] = 0;
    pQExpandAGV_PDO->CanBuf_ID1X9T[1] = (ErrFlag << 6) | (0x1 << 2);
    pQExpandAGV_PDO->CanBuf_ID1X9T[2] = 0;
    pQExpandAGV_PDO->CanBuf_ID1X9T[3] = 0;
    pQExpandAGV_PDO->CanBuf_ID1X9T[4] = 0;
    pQExpandAGV_PDO->CanBuf_ID1X9T[5] = 0;
    pQExpandAGV_PDO->CanBuf_ID1X9T[6] = 0;
    pQExpandAGV_PDO->CanBuf_ID1X9T[7] = 0;
    
    pQExpandAGV_PDO->CanBuf_ID1XAT[0] = 0;
    pQExpandAGV_PDO->CanBuf_ID1XAT[1] = (pQExpandAGV_PDO->AngleMeasured) & 0xFF;
    pQExpandAGV_PDO->CanBuf_ID1XAT[2] = (pQExpandAGV_PDO->AngleMeasured >> 8) & 0xFF;
    pQExpandAGV_PDO->CanBuf_ID1XAT[3] = pQExpandAGV_PDO->BoardTemperature;
    pQExpandAGV_PDO->CanBuf_ID1XAT[4] = pQExpandAGV_PDO->TxCnt & 0x0F;
    pQExpandAGV_PDO->CanBuf_ID1XAT[5] = 0;
    pQExpandAGV_PDO->CanBuf_ID1XAT[6] = 0;
    pQExpandAGV_PDO->CanBuf_ID1XAT[7] = 0;  
    
    
//	pQExpandAGV_PDO->CanBuf_ID1XBT[0] = pQExpandAGV_PDO->ErrorCode;
//	pQExpandAGV_PDO->CanBuf_ID1XBT[1] = pQExpandAGV_PDO->MotorTemperature;
//	pQExpandAGV_PDO->CanBuf_ID1XBT[2] = pQExpandAGV_PDO->BoardTemperature;
//	pQExpandAGV_PDO->CanBuf_ID1XBT[3] = pQExpandAGV_PDO->BDIPercent;
//	pQExpandAGV_PDO->CanBuf_ID1XBT[4] = pQExpandAGV_PDO->AnalogInput1;
//	pQExpandAGV_PDO->CanBuf_ID1XBT[5] = pQExpandAGV_PDO->AnalogInput2;
//	pQExpandAGV_PDO->CanBuf_ID1XBT[6] = 0;
//	pQExpandAGV_PDO->CanBuf_ID1XBT[7] = pQExpandAGV_PDO->SoftwareVersion;
	
	if ((pQExpandAGV_PDO->DgnDataRxTx.Flag & TX_FLAG) != 0)
	{
		INT8U i,len=0;
		pQExpandAGV_PDO->DgnDataRxTx.Flag &= ~(RX_FLAG | RDOP_FLAG | WROP_FLAG | TX_FLAG);
				       
		pQExpandAGV_PDO->CanBuf_IDSDOT[1] = pQExpandAGV_PDO->DgnDataRxTx.FuncCode;
		pQExpandAGV_PDO->CanBuf_IDSDOT[2] = pQExpandAGV_PDO->DgnDataRxTx.Index;
		pQExpandAGV_PDO->CanBuf_IDSDOT[3] = pQExpandAGV_PDO->DgnDataRxTx.DataL16 & 0xFF;
		pQExpandAGV_PDO->CanBuf_IDSDOT[4] = (pQExpandAGV_PDO->DgnDataRxTx.DataL16>>8) & 0xFF;
		pQExpandAGV_PDO->CanBuf_IDSDOT[5] = pQExpandAGV_PDO->DgnDataRxTx.DataH16 & 0xFF;
		pQExpandAGV_PDO->CanBuf_IDSDOT[6] = (pQExpandAGV_PDO->DgnDataRxTx.DataH16>>8) & 0xFF;
		pQExpandAGV_PDO->CanBuf_IDSDOT[7] = 0xAA;
		for(i =7;i>1;i--)
		{//计算有效字节
			if(pQExpandAGV_PDO->CanBuf_IDSDOT[i] == 0xAA)
				len++;
			else
			{
				pQExpandAGV_PDO->DgnDataRxTx.UserByte = 7-len;
				break;
			}
		}
		pQExpandAGV_PDO->CanBuf_IDSDOT[0] = pQExpandAGV_PDO->DgnDataRxTx.UserByte;		
		pQExpandAGV_PDO->CanBufTxState |= TXSDO_CANBUFRXSTATE;		
	}

	return 1;
}

#endif //#if (CANOPEN_TYPE == CANOPEN_LINDE)
