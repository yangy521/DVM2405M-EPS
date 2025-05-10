/*******************************************************************************
* Filename: CanOpen_HangChaApp.h	                                          	 *
* Description:											   			 		                               *
* Author:  QExpand, Young                                                      *
* Date:  2025/01/20  														 		   												 *
* Revision:	1.00															 		                             *
*******************************************************************************/
#include "KSDsys.h"
#include <stdlib.h>

#if(USER_TYPE == USER_HANGCHA_DDTBC_STEER)
#define MAX_BYTE_NUM   28
#define DGN_PARAOFS_MCU			0x2000
#define MONITOR_PARA_START	210
#define CONTROLLER_TYPE			"DVM24S05"

/****bit define for Language***/
#define CHINESE_OPTION		0x00
#define ENGLISH_OPTION		0x01


/*** 以下为APP相关定义 ***/
/*** APP define for CANID ***/
#define HANGCHAAPPPDO_RX670_ID_OFS	 0x670		//From App to Mcu
#define HANGCHAAPPPDO_RX651_ID_OFS	 0x651		//From APP to Mcu

#define HANGCHAAPPPDO_TX5D1_ID_OFS	 0x5D1		//From Mcu to APP

#define RX651_CANBUFRXSTATE		(0x1 << 0)
#define RX670_CANBUFRXSTATE		(0x1 << 1)

#define TX5D1_CANBUFTXSTATE		(0x1 << 0)

/************ DGN FUNCTION CMD ****************/
#define READ_REQUIR_DGNFUNC			0x40
#define READ_ANSWER_DGNFUNC			0x43
#define WRITE_REQUIR_DGNFUNC		0x23
#define WRITE_ANSWER_DGNFUNC		0x60
#define WRITE_SYNCREQ_DGNFUNC		0x2B
#define ERR_READ_ANSWER_DGNFUNC 0xFF

#define DGN_CONNECT_REQ_INDEX		0x1F52
#define DGN_QUERY_AUTO_INDEX		0x1018
#define DGN_CONECT_CMD_INDEX		0x404E
#define DGN_CONECT_ANSWERL16		0xCDD8
#define DGN_CONECT_ANSWERH16		0xC7B0
#define DGN_QUERY_ERR_INDEX			0xFF10
#define DGN_STOP_REQ_INDEX			0xFF11
#define CURERROR_PACK_SEND_INDEX		0xFF11
#define PREERROR_PACK_SEND_INDEX		0xFF12


/***FF10 Query  ERROR Info   ***/
#define QUERY_CURRENT_ERR_SUBINDEX   0x01
#define QUERY_PREVIOUS_ERR_SUBINDEX  0x02
//***FF11  ErrorCode Process ***/
#define ERROR_REPORT_SUBINDEX			   0xFF
#define HISTORY_ERR_TIME_SUBINDEX	   0xFE
#define ERROR_SUBCONTRACT_SUBINDEX1  0xFD
#define ERROR_SUBCONTRACT_SUBINDEX2  0xFC
#define ERROR_SUBCONTRACT_SUBINDEX3  0xFB
#define ERROR_SUBCONTRACT_SUBINDEX4  0xFA
#define ERROR_SUBCONTRACT_SUBINDEX5  0xF9
#define ERROR_SUBCONTRACT_SUBINDEX6  0xF8
#define ERROR_SUBCONTRACT_SUBINDEX7  0xF7
/************ PassWord FUNCTION CMD ****************/
#define SHAKE_HANDS_DGNFUNC		  0x01
#define DECODE_ANSWER_DGNFUNC		0x05

/***1018 Query special***/
#define QUERY_CONTROLLER_TYPE_F4	  0x00
#define QUERY_CONTROLLER_TYPE_B4    0x0C
#define QUERY_CONTROLLER_SN					0x01
#define QUERY_APP_SOFT_VERSION			0x03
/***1F52 Connect Requirement & Query  SubIndex***/
#define	DGN_CONNECT_REQ_SUBINDEX		0x01
#define DGN_DECODE_DATA_SUBINDEDX		0x02
#define DGN_PERMIS_LEVEL_SUBINDEX		0x03
#define DGN_CAR_TYPE_SUBINDEX				0x04
#define DGN_MENU_ID_SUBINDEX				0x05
#define DGN_MENU_TYPE_SUBINDEX			0x06
//*** Bit define for tEPDGN_DATA.Flag
#define RX_FLAG								(1 << 0)
#define RDOP_FLAG							(1 << 1)
#define WROP_FLAG							(1 << 2)
#define TX_FLAG							  (1 << 3)

#define	TX_PERIOD1			(6/ T_MS_PLC_PERIOD)  //n*10 ms 
/***** Struct define *****/
typedef struct tHCDGN_DATA
{
	INT16U SynFlag;			 //发送/接收同步标志位（同步）
	INT16U Q_AFlag;      //异步

	INT8U FuncCode;           //BYTE[0]
	INT8U SubIndex;           //BYTE[3]
	INT16U Index;             //BYTE[2:1]
	INT16U DataL16;           //BYTE[5:4]
	INT16U DataH16;           //BYTE[7:6]
}tHCDGN_DATA;

//加密 建立映射关系
typedef struct {
    char original;
    char replacement;
} CharMapping;

// 定义一个结构体来存储索引和地址对
typedef struct {
    INT32U indexAddress;  // 索引地址
    INT16U address;       // 对应的地址
    INT8U xiShu;          // 修改参数的索引
} IndexAddressMap;

typedef struct tHANGCHAAPP_PDO
{
  INT8U CanBuf_ID670R[8];
	INT8U CanBuf_ID651R[8];
	INT8U CanBuf_ID5D1T[8];
	
	INT16U CanBufTxState;
	INT16U CanBufRxState;
	INT16U CanIdState;  

	INT8U HandshakeFlag;
  INT8U SelectLanguage;
	
	INT8S BitAddr;
	INT32U IndexAddress; 
	INT16U Address;
	INT16U XiShu;
	INT8U SubFunID;
	INT8U GeneratePwdFlag;

	char RandPwdArr[4];
	//Data Dgn
	tHCDGN_DATA DgnDataRxTx;	
	
	INT8U ReadBitFlag;
	INT8U OriginalBitVal1[8];

	INT8U DataStateBit1;
	INT8U DataStateBit2;
	INT8U SendErrFlag;
	INT8U ErrcodeType;
	size_t ErrorTotalLength;
	INT8U CurErrNum;
	INT8U NumCount;
	INT8U ErrNum;
	tBoolean LastErrByte;
	INT8U ReqAnsyFlag;
	INT8U sendcnt;
}tHANGCHAAPP_PDO;

typedef struct Time_InitTypeDef    //设置使用时间占用位域结构体
{
	INT32U Hour:17;  
	INT32U Minute:6;
	INT32U Resvered:9;
} Time_InitTypeDef;

INT16S IndexToAddress(void);
void vGetRandPwd(tHANGCHAAPP_PDO *pCanopenPDO, INT8U length);
void vGetReplaceChar(char *oldpwd,char *newpwd);
INT8U iRemoteUnlockPWD(tHANGCHAAPP_PDO  *pCanopenPDO,char *myParsepwd);
void vGenerateKeyPro(char *Original,char *CodeKey);

INT16U vMonitorParaAdjust(tHANGCHAAPP_PDO *pCanopenPDO,INT16U OriginVal);

INT16U iModifyParaAdjust(tHANGCHAAPP_PDO *pCanopenPDO);
tBoolean bErrCodePackParse(tHANGCHAAPP_PDO *pCanopenPDO);
void vErrPackSendPro(INT8U length);
void ReceiveAPPDataUpdatePro(tHANGCHAAPP_PDO *pCanopenPDO);
extern void PDO_Prco_HANGCHA(void);
extern tHANGCHAAPP_PDO  HangCha_GDC_PDO;
extern Time_InitTypeDef TIME_InitStructure;
extern INT8U ErrorCodeDisp(INT8U ErrCode);
#endif

