/*******************************************************************************
* Filename: iCAN.h	                                             	 		   *
* Description:											   			 		   *
* Author:                                                           		   *
* Date:     														 		   *
* Revision:															 		   *
*******************************************************************************/
#ifndef __ICAN_H
#define __ICAN_H

#include		"KSDsys.h"
#ifdef MICRO_CANOPEN
	#include "mco.h"
#endif
/*******************************************************************************
* CAN定义														 		   																	*
*******************************************************************************/

/*******************************************************************************
* ICAN定义														 		   																	*
*******************************************************************************/
#define		ICAN_SLV_NUM			8		//ICAN从站数量
#define		MACID_TOTAL				0xFF	//从站MACID编号定义
//波特率宏定义
#define			CANBAUD_1M              0
#define			CANBAUD_500K            1
#define     CANBAUD_250K            2
#define     CANBAUD_125K            3
#define     CANBAUD_100k            4
#define     CANBAUD_50k	            5
#define     CANBAUD_25k							6
#define     CANBAUD_20k							7
#define     CANBAUD_10k							8
#define     CANBAUD_5k							9

//功能码定义
#define		ICAN_Func_WritePort 			0x01	//连续写端口
#define		ICAN_Func_ReadPort  			0x02	//连续读端口
#define		ICAN_Func_TransTriger			0x03	//事件触发传送
#define		ICAN_Func_SetConnect			0x04	//建立连接
#define		ICAN_Func_DelConnect			0x05	//删除连接
#define		ICAN_Func_SlvReset				0x06	//从站复位
#define		ICAN_Func_MacIDCheck			0x07	//MACID检测
#define		ICAN_Func_ErrAck					0x0f	//异常响应

//响应标识位定义
#define     ICAN_ACK_Enable         0	     //需要应答
#define     ICAN_ACK_Disable        1	     //不需要应答

// 异常响应码定义
#define			ICAN_Ack_ErrFuncID			0x01	//	功能码不存在
#define     ICAN_Ack_ErrSrcID 	  	0x02	//	资源不存在
#define     ICAN_Ack_ErrCommand	   	0x03	//	命令不支持
#define     ICAN_Ack_ErrFuncParms	 	0x04	//	功能码参数非法
#define     ICAN_Ack_ErrConnect			0x05	//	连接不存在
#define     ICAN_Ack_ErrOperation		0x06	//	操作无效
#define     ICAN_Ack_ErrTrans	    	0x07	//	分段传输过程出错

//从站节点状态
#define			ICAN_Slv_Idle               0		//	空闲
#define			ICAN_Slv_Post								1		//	正在发送
#define     ICAN_Slv_Pend               2		//	等待接收
#define     ICAN_Slv_Finished						3		//	接收完成，等待处理
#define     ICAN_Slv_Overtime           4		//	超时

//产品类型
#define		Prd_Move						0	//主牵引控制器
#define		Prd_Lift						1	//提升控制器
#define		Prd_Steer						2	//转向控制器
#define		Prd_Move_Second			3	//从牵引控制器
#define		Prd_Logic						4	//逻辑控制器
#define		Prd_HMI							5	//仪表
#define		Prd_PC							6	//PC终端

//资源节点地址定义
#define		ICAN_Addr_DI 			0x01	//连续写端口
#define		ICAN_Addr_DO 			0x02	//连续读端口
#define		ICAN_Addr_AI			0x03	//事件触发传送
#define		ICAN_Addr_AO			0x04	//建立连接

#pragma pack(1) //让编译器对这个结构作1字节对齐
//结构体声明
//#ifdef ICAN_SLAVE
//定Prd_Move结构体
typedef struct _tPrd_Move
{
		//资源节点信息
	//unsigned char  ucPageNmuber;		//	仪表显示页面 		 SoruceID:0x00
	unsigned char  ucPrdState;			//	设备工作状态显示 SoruceID:0x20
	unsigned short usPrdSpd;			  //	设备运行速度		 SoruceID:0x21,0x22
	unsigned char  ucErrorCode;			//	故障代码 				 SoruceID:0x23
	unsigned char  ucDIState;		    // 开关输入状态      SoruceID:0x26
	unsigned char  ucDOState;		    // 开关输出状态      SoruceID:0x27
	unsigned char  ucThrottleInput;	//	踏板输入状态     SoruceID:0x28
	unsigned char  ucMotorSpeedF;		//	电机工作频率 		 SoruceID:0x2A
	unsigned short usPhaseCurrent; //	相电流 		 			   SoruceID:0x2B,0x2C
	unsigned short usPhaseVoltage; //	相电流 		 			   SoruceID:0x2B,0x2C
	unsigned short usBusVoltage;	  //	母线电压低字节   SoruceID:0x2D,0x2E
	unsigned char  ucControllerTmp;	//	控制器温度       SoruceID:0x2F
	unsigned char  ucMotorTmp;			//	电机温度         SoruceID:0x30
	
}tPrd_Move;

//定义Prd_Lift结构体
typedef struct _tPrd_Lift
{
		//资源节点信息
	unsigned char  ucPrdState;			//	设备工作状态显示 SoruceID:0x20
	unsigned char  ucErrorCode;			//	故障代码 				 SoruceID:0x23
	unsigned char  ucDIState;		    // 开关输入状态      SoruceID:0x26
	unsigned char  ucDOState;		    // 开关输出状态      SoruceID:0x27
	unsigned char  ucThrottleInput;	//	踏板输入状态     SoruceID:0x28
	unsigned char  ucAIInput;				//	模拟量输入 			 SoruceID:0x29
	unsigned char  ucMotorSpeedF;		//	电机工作频率 		 SoruceID:0x2A
	unsigned short usPhaseCurrent; //	相电流 		 			   SoruceID:0x2B,0x2C
	unsigned short usPhaseVoltage; //	相电流 		 			   SoruceID:0x2B,0x2C
	unsigned short usBusVoltage;	  //	母线电压低字节   SoruceID:0x2D,0x2E
	unsigned char  ucControllerTmp;	//	控制器温度       SoruceID:0x2F
	unsigned char  ucMotorTmp;			//	电机温度         SoruceID:0x30
	
}tPrd_Lift;
//定Prd_Steer结构体
typedef struct _tPrd_Steer
{
		//资源节点信息
	unsigned char  ucPrdState;			//	设备工作状态显示 SoruceID:0x20
	unsigned char  ucErrorCode;			//	故障代码 				 SoruceID:0x23
	unsigned short usSteerAngle;		//	转向角度   			 SoruceID:0x24,0x25
	unsigned char  ucDIState;		    // 开关输入状态      SoruceID:0x26
	unsigned char  ucDOState;		    // 开关输出状态      SoruceID:0x27
	unsigned char  ucDirEncoder;	  //	编码器方向盘输入 SoruceID:0x28,0x29
	unsigned char  ucMotorSpeedF;		//	电机工作频率 		 SoruceID:0x2A
	unsigned short usPhaseCurrent; //	相电流 		 			   SoruceID:0x2B,0x2C
	unsigned short usPhaseVoltage; //	相电流 		 			   SoruceID:0x2B,0x2C	
	unsigned short usBusVoltage;	  //	母线电压低字节   SoruceID:0x2D,0x2E
	unsigned char  ucControllerTmp;	//	控制器温度       SoruceID:0x2F
	unsigned char  ucMotorTmp;			//	电机温度         SoruceID:0x30
	
}tPrd_Steer;
//定Prd_Move_Sec结构体
typedef struct _tPrd_Move_Sec
{
		//资源节点信息
	unsigned char  ucPrdState;			//	设备工作状态显示 SoruceID:0x20
	unsigned char  ucErrorCode;			//	故障代码 				 SoruceID:0x23
	unsigned char  ucDOState;		    // 开关输出状态      SoruceID:0x27
	unsigned char  ucMotorSpeedF;		//	电机工作频率 		 SoruceID:0x2A
	unsigned short usPhaseCurrent;  //	相电流 		 			 SoruceID:0x2B,0x2C
	unsigned short usPhaseVoltage; //	相电流 		 			   SoruceID:0x2B,0x2C	
	unsigned short usBusVoltage;	  //	母线电压低字节   SoruceID:0x2D,0x2E
	unsigned char  ucControllerTmp;	//	控制器温度       SoruceID:0x2F
	unsigned char  ucMotorTmp;			//	电机温度         SoruceID:0x30
	
}tPrd_Move_Sec;
//#endif
//定义iCAN帧结构体
typedef struct _tICANFrame	 
{
	INT8U  ucSrcMacID;		//	源节点地址
	INT8U  ucDestMacID;		//	目标节点地址
	INT8U  ucACK;					//	响应标识位
	INT8U  ucFuncID;			//	功能码
	INT8U  ucSourceID;		//	资源节点地址
	INT8U  ucDataLength;	//	有效数据长度
	INT8U  ucData[8];			//  8字节数据
}tICANFrame;

//定义从站节点结构体（从站镜像）
#define SLV_RXBUF_LEN   32
typedef struct _tICANSlave
{
	//节点信息
	INT8U	ucMacID;		//	从站ID
	INT8U	ucType;			//	从站产品类型
	INT32U	ulSN;			//	从站产品序列号
	INT8U ucDILength;	//
	INT8U ucDOLength;	//
	INT8U ucAILength;	//
	INT8U ucAOLength;	//
	//网络状态
	tBoolean  bIsConnect;			//	是否与主站建立连接
	INT8U  ucStatus;		//	从站节点镜像状态
	tBoolean  bIsOnline;			//
	INT8U     ucErrCount;		// 错误计数
	INT8U ucTime;						//参数及数据读写节拍
	//数据信息
	INT8U ucDataAddress;	//
	tICANFrame icanFrame;			//
	INT8U ucRxBuffer[SLV_RXBUF_LEN];	//	从站的接收数据缓冲区
	INT8U ucRxBufLength;	//从站的接收数据缓冲区有效长度
	//资源节点信息
	//DI
	INT8U ucSource0x00;	//PCWorkSetting
	INT8U ucSource0x01;	
	INT8U ucSource0x02;
	INT8U ucSource0x03;
	INT8U ucSource0x04;
	INT8U ucSource0x05;
	INT8U ucSource0x06;
	INT8U ucSource0x07;
	INT8U ucSource0x08;
	INT8U ucSource0x09;
	INT8U ucSource0x0A;
	INT8U ucSource0x0B;
	INT8U ucSource0x0C;
	INT8U ucSource0x0D;
	//INDEX 1~6
	INT8U ucSource0x0E;	//PARAIndex1
	INT8U ucSource0x0F;	//PARAValueH1
	INT8U ucSource0x10;	//PARAValueL1
	INT8U ucSource0x11;	//PARAIndex2
	INT8U ucSource0x12;	//PARAValueH2
	INT8U ucSource0x13;	//PARAValueL2
	INT8U ucSource0x14;	//PARAIndex3
	INT8U ucSource0x15;	//PARAValueH3
	INT8U ucSource0x16;	//PARAValueL3
	INT8U ucSource0x17;	//PARAIndex4
	INT8U ucSource0x18;	//PARAValueH4
	INT8U ucSource0x19;	//PARAValueL4
  INT8U ucSource0x1A;	//PARAIndex5
	INT8U ucSource0x1B;	//PARAValueH5
	INT8U ucSource0x1C;	//PARAValueL5
  INT8U ucSource0x1D;	//PARAIndex6
	INT8U ucSource0x1E;	//PARAValueH6
	INT8U ucSource0x1F;	//PARAValueL6

  //DO
	INT8U ucSource0x20;		//WorkSetting
	INT8U ucSource0x21;	//仪表：ICANNetCfg
	INT8U ucSource0x22;	//仪表：ErrMove
	INT8U ucSource0x23;	//仪表：ErrLift
	INT8U ucSource0x24;	//仪表：ErrSteer
	INT8U ucSource0x25;	//仪表：ErrMoveSecond
	INT8U ucSource0x26;
	INT8U ucSource0x27;
	INT8U ucSource0x28;
	INT8U ucSource0x29;
	INT8U ucSource0x2A;
	INT8U ucSource0x2B;
	INT8U ucSource0x2C;
	INT8U ucSource0x2D;
	//INDEX 1~6
	INT8U ucSource0x2E;	//PARAIndex1
	INT8U ucSource0x2F;	//PARAValueH1 
	INT8U ucSource0x30; //PARAValueL1
	INT8U ucSource0x31;	//PARAIndex2
	INT8U ucSource0x32;	//PARAValueH2
	INT8U ucSource0x33;	//PARAValueL2
	INT8U ucSource0x34;	//DIPARAIndex3
	INT8U ucSource0x35;	//PARAValueH3
	INT8U ucSource0x36;	//PARAValueL3
	INT8U ucSource0x37;	//PARAIndex4
	INT8U ucSource0x38;	//PARAValueH4
	INT8U ucSource0x39;	//PARAValueL4
	INT8U ucSource0x3A;	//PARAIndex5
	INT8U ucSource0x3B;	//PARAValueH5
	INT8U ucSource0x3C;	//PARAValueL5
	INT8U ucSource0x3D;	//PARAIndex6
	INT8U ucSource0x3E;	//PARAValueH6
	INT8U ucSource0x3F;	//PARAValueL6	

	INT8U ucSource0xE2; //产品类型
}tICANSlave;

//定义主站节点结构体
typedef struct _tICANMaster
{
	//节点信息
	INT8U	ucMacID;		//	主站ID
	INT8U	ucBand;  		//  波特率
	INT8U	ucCycle;		//	ICAN网络主站定时循环参数，范围1~255，单位10ms
	//产品信息
	INT8U	ucType;			//	主站产品类型
	INT32U	ulSN;			//	主站产品序列号
	//网络状态
	tBoolean 		bIsOnline;		//	是否上线
	INT8U  ucStatus;		//	主站节点镜像状态				
	//从站镜像数组
	INT8U  ucIdtoSlvArrayIndex[ICAN_SLV_NUM]; // ID 和 从站在pICANSlvArray中的位置索引
	INT32U ucNetCfg;   //id connect bit flag, order by id
	tICANSlave	pICANSlvArray[ICAN_SLV_NUM];		//	保存从站镜像的数组指针
	INT8U ucSlvArrLength;	//	从站镜像数组有效长度
	INT8U ucCurSlvIndex;	//	当前轮训从站节点
	INT8U REMABUF[8];
}tICANMaster;

#pragma pack() //取消1字节对齐，恢复为默认4字节对齐

extern tICANMaster	icanMaster;			//定义主站
extern tICANSlave icanSlave;	 //定义从站
extern void ICANSend(tICANFrame icanFrame);
extern void ICANInitialize_Master(void);		//ICAN初始化
extern void ICANInitialize_Slave(void);		//ICAN初始化
extern void ICANDataInManage_Master(void);
extern void ICANDataInManage_Slave(void);
extern void ICANNetManage_Master(void);
extern void ICANNetManage_Slave(void);
extern void ICANDataOutManage_Master(void);
extern void ICANDataOutManage_Slave(void);

#endif //#define __ICAN_H

