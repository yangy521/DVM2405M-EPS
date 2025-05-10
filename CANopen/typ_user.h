#ifndef __TYP_USER_H
#define __TYP_USER_H
//#include "stm32f37x.h"
//#include "uart.h"

/**************************************************************************
GLOBAL TYPE DEFINITIONS
**************************************************************************/
//#define INT8U  unsigned char
//#define INT16U  unsigned short int
//#define uINT32S unsigned int
//#define int8_t   signed char
//#define int16_t  signed short int
//#define INT32S  signed int
	
typedef unsigned char		INT8U;       		/* Unsigned 16 bits quantity  */
typedef signed   char		INT8S;       		/* Signed   16 bits quantity  */
typedef unsigned short int	INT16U;       		/* Unsigned 16 bits quantity  */
typedef signed   short int  INT16S;       		/* Signed   16 bits quantity  */
typedef unsigned int		INT32U;       		/* Unsigned 32 bits quantity  */
typedef signed   int		INT32S;       		/* Signed   32 bits quantity  */
typedef unsigned long 	INT64U;				/* Unsigned 64 bits quantity  */
typedef signed   long 	INT64S;				/* Signed   64 bits quantity  */
typedef volatile INT8U		VINT8U;      		/* Unsigned volatile  8 bits  */
typedef volatile INT8S		VINT8S;      		/* Signed   volatile  8 bits  */
typedef volatile INT16U		VINT16U;      		/* Unsigned volatile 16 bits  */
typedef volatile INT16S		VINT16S;      		/* Signed   volatile 16 bits  */
typedef volatile INT32U		VINT32U;       		/* Unsigned volatile 32 bits  */
typedef volatile INT32S		VINT32S;       		/* Signed   volatile 32 bits  */
typedef volatile INT64U		VINT64U;      		/* Unsigned volatile 64 bits  */
typedef volatile INT64S		VINT64S;      		/* Signed   volatile 64 bits  */
typedef unsigned char tBoolean;
typedef signed char CHAR;
/* 2. Macro symbol definitions */
#define NULL				0
#define TRUE				((INT16S)1)
#define FALSE				((INT16S)0)
#define true				TRUE
#define false				FALSE
/* 3. **************************/
/* CAN波特率定义 */
#define CAN_500KBPS			1
#define CAN_250KBPS			2
#define CAN_125KBPS			3

typedef union   
{
    struct
    {
    volatile unsigned X00:1;				//0
    volatile unsigned X01:1;				//1
    volatile unsigned X02:1;				//2
    volatile unsigned X03:1;				//3
    volatile unsigned X04:1;				//4
    volatile unsigned X05:1;				//5
    volatile unsigned X06:1;				//6
    volatile unsigned X07:1;				//7
    volatile unsigned X08:1;				//8
    volatile unsigned X09:1;				//9
    volatile unsigned X0A:1;				//10
    volatile unsigned reserved1:1;	//11
    volatile unsigned X0C:1;				//12
    volatile unsigned reserved2:1;	//13
		volatile unsigned X0E:1;				//14
    volatile unsigned X0F:1;				//15
    volatile unsigned X10:1;				//16
    volatile unsigned X11:1;				//17
    volatile unsigned X12:1;				//18
    volatile unsigned X13:1;				//19
    volatile unsigned X14:1;				//20
    volatile unsigned reserved3:1;	//21
    volatile unsigned reserved4:1;	//22
		volatile unsigned X17:1;				//23
    volatile unsigned X18:1;				//24
    volatile unsigned reserved5:1;	//25
		volatile unsigned X1A:1;				//26
    volatile unsigned X1B:1;				//27
    volatile unsigned X1C:1;				//28
    volatile unsigned X1D:1;				//29
		volatile unsigned X1E:1;				//30
    volatile unsigned X1F:1;				//31
    }BITS;
    volatile unsigned int  Data;
}TYP_IO_X;

typedef union   
{
    struct
    {
    volatile unsigned Y30:1;				//0
    volatile unsigned Y31:1;				//1
    volatile unsigned Y32:1;				//2
    volatile unsigned Y33:1;				//3
    volatile unsigned Y34:1;				//4
    volatile unsigned Y35:1;				//5
    volatile unsigned Y36:1;				//6
    volatile unsigned Y37:1;				//7
    volatile unsigned Y38:1;				//8
    volatile unsigned Y39:1;				//9
    volatile unsigned Y3A:1;				//10
    volatile unsigned Y3B:1;				//11
		volatile unsigned reserved1:8;	//12-19
    volatile unsigned Y44:1;				//20
    volatile unsigned Y45:1;				//21
    volatile unsigned Y46:1;				//22
    }BITS;
    volatile unsigned int  Data;
}TYP_IO_Y;

typedef struct
{
	INT32S	Value1;
	INT32S	Value2;
	
}TYP_DW_DATA;


typedef	enum
{
	EMERGENCY_MASTER_RCV=0X0080,	//0X080+ID
	PDO1_MASTER_RCV=0X0180,				//0X180+ID
	PDO2_MASTER_RCV=0X0280,				//0X280+ID
	PDO3_MASTER_RCV=0X0380,				//0X380+ID
	PDO4_MASTER_RCV=0X0480,				//0X480+ID
	NMT_BOOTUP_MASTER_RCV=0X0700,	//0X700+ID
	SDO_MASTER_RCV=0X0580					//0X580+ID
	
}HEAD_CAN_MASTER_RCV;
typedef	enum
{
	NMT_CONTROL_MASTER_SEND=0X0000,			//0X000
	NMT_PROTECT_MASTER_SEND=0X0700,			//0X700+ID
	SDO_MASTER_SEND=0X0600,							//0X600+ID
}HEAD_CAN_MASTER_SEND;
typedef	enum
{
	NMT_CONTROL_SLAVE_RCV=0X0000,			//0X000
	NMT_PROTECT_SLAVE_RCV=0X0700,			//0X700+ID
	SDO_SLAVE_RCV=0X0600,							//0X600+ID
}HEAD_CAN_SLAVE_RCV;
typedef	enum
{
	EMERGENCY_SLAVE_SEND=0X0080,			//0X080+ID
	PDO1_SLAVE_SEND=0X0180,						//0X180+ID
	PDO2_SLAVE_SEND=0X0280,						//0X280+ID
	PDO3_SLAVE_SEND=0X0380,						//0X380+ID
	PDO4_SLAVE_SEND=0X0480,						//0X480+ID
	SDO_SLAVE_SEND=0X0580,						//0X580+ID
	NMT_BOOTUP_SLAVE_SEND=0X0700,			//0X700+ID
}HEAD_CAN_SLAVE_SEND;
typedef	enum
{
	candat_int8_t=1,
	candat_int16_t=2,
	candat_INT32S=3
}TYPE_CANDAT;
typedef	enum
{
	NMT_START=1,
	NMT_STOP=2,
	NMT_PREOPERATION=128,
	NMT_RESETNODE=129,
	NMT_RESETCOMM=130
}DS301_NMT_COMMAND;
typedef	enum
{
	DS301_Preoperation=127,
	DS301_Operational=5,
	DS301_Stoped=4	
}TYP_DS301_status;

typedef	struct
{
	INT8U	dat[32];
}TYP_CHAR_STR;

typedef struct {                                 
  INT8U	bytes;
	INT8U	dat[32];
} TYP_STRING_MESSAGE;

typedef struct  {
  INT32U	id;                                                    /*  29/11 位标识符              */
  INT8U		data[8];                                               /*  8字节数据场                 */
  INT8U		len;                                                   /*  数据场字节数                */
  INT8U		format;                                                /*  0 - 标准帧, 1- 扩展帧       */
  INT8U		type;                                                  /*  0 - 数据帧, 1 - 远程帧      */
} CAN_FRAME;
typedef	struct{
	INT8U	index_read;
	INT8U	index_write;
	CAN_FRAME	msg[8];
}TYP_CANMSG_BUF;
typedef struct
{
//										  ||---1---|
	INT8U	dat[13];	//0b0000RGBY
}TYP_LED_STATUS;
typedef	struct
{
	INT32S		slot1_x;
	INT32S		slot1_z;
	INT32S		slot13_x;
	INT32S		slot13_z;
	INT32S		get_prepare_y;
	INT32S		get_y;
	INT32S		get_finish_y;
	INT32S		put_prepare_y;
	INT32S		put_y;
	INT32S		put_finish_y;
}TYP_SAMPLEGROOVE;
typedef	struct
{
	INT8U					length;//bytes of dat
	TYP_CHAR_STR		str;
}TYP_BARCODE;

typedef struct
{
	TYP_CHAR_STR	str[8];
	INT8U	Index_Read;
	INT8U	Index_Write;
}TYP_UART_RECEIVE;


typedef struct {
	TYP_DS301_status	ds301_status;	
	INT16U	dict_603F;
	INT16U	dict_6040;
	INT16U	dict_6041;
	INT16U	dict_6060;
//	INT8U		ds301_mode;
	INT16U	can_id;
//
	INT32S	xaxis_pos_set;
	INT32S	xaxis_pos_now;
	
	INT32S	yaxis_pos_set;
	INT32S	yaxis_pos_now;

	INT32S	zaxis_pos_set;
	INT32S	zaxis_pos_now;

	INT32S	hand_set;
	INT32S	hand_now;
	
	INT32S	getrack_group;
	INT32S	getrack_slot;
	
	INT32S	putrack_group;
	INT32S	putrack_slot;

	TYP_SAMPLEGROOVE	groove[3];
	TYP_BARCODE	barcode[10];
//	TYP_UART_IN_STR	barcode[10];
	INT16U	tube_isexist;
	
	INT32S	scanbarcode_pos[10];
} TYP_SYS_RUN;
typedef	struct
{
	INT8U	bytes;
	INT8U	dat[20];
}TYP_STRING_BARCODE_SAMPLE;

typedef	struct
{
	INT8U	bytes;
	INT8U	dat[250];
}TYP_STRING_BARCODE_REAGENT;

//--------------------------------------------------------

#endif
