#ifndef __SmartCom_h__
#define __SmartCom_h__

#include "Communicator.h"
#include "SmartComString.h"
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SMARTCOM_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SMARTCOM_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef SMARTCOM_EXPORTS_MACRO
#define SMARTCOM_API __declspec(dllexport)
#else
#define SMARTCOM_API __declspec(dllimport)
#endif

#define USE_SMARTCOMSTRING
/********************************************
功能:
初始化与卡片读写器的通信.
入口参数：无
出口参数：无
返回值：
-1：初始化失败
0：成功
*********************************************/
SMARTCOM_API int InitUDPComm();



/************************************************************************/
/* 
功能：
获取一个com通信器
入口参数：
comPort:要通信的端口号
rate:波特率，默认115200
waitForSTX2Time：第一个字符超时，默认1000ms
normalWaitTime：中间字符超时，默认1000ms
出口参数：无
返回值：
0：成功
-1：失败
/************************************************************************/
SMARTCOM_API int GetOneCOMCommunicator(Communicator& aCommunicator,int comPort,int rate=115200,
									   int waitForSTX2Time=1000,int normalWaitTime=1000 );

/************************************************************************
功能：
关闭COM通信
入口参数：无
出口参数:无
返回值：
0：成功
-1：失败
***********************************************************************/
SMARTCOM_API int CloseCOMComm();

/************************************************************************
功能：
关闭udp通信
入口参数：无
出口参数:无
返回值：
0：成功
-1：失败
***********************************************************************/
SMARTCOM_API int CloseUDPComm();

/************************************************************************
功能：
获取一个udp通信器。
入口参数：
dstIP:目的ip
port：目的端口
waitForSTX2Time：第一个字符超时，默认1000ms
normalWaitTime：中间字符超时，默认1000ms
出口参数:
aCommunicator:返回的通信器
返回值：
0：成功
-1：失败
***********************************************************************/
SMARTCOM_API int GetOneUDPCommunicator(Communicator& aCommunicator,const char* dstIP,int port,
									   int waitForSTX2Time=1000,int normalWaitTime=1000);

/************************************************************************
功能：
读取终端设备id号和机号
入口参数：
comm:用于通信的通信器
devIDBufLen: devID缓冲的长度
出口参数:
DevID：存放7字节id号,
MacNo:1字节机号
返回值：
0：读取成功
-1：通信超时错误
-2: 通信器无效
-3: 读取失败

/************************************************************************/
SMARTCOM_API int GetDevIDAndMacNo(Communicator& comm,char* devID,int devIDBufLen,int& macNo);

#ifdef USE_SMARTCOMSTRING
SMARTCOM_API int GetDevIDAndMacNo(Communicator& comm, SmartCom::string& devID,int& macNo);
#endif
/************************************************************************/
/*功能：
通过终端设备ID号给终端设备设置机号
入口参数：
comm:用于通信的通信器
DevID:存放7个字节的设备ID
MacNo:要设置的机号
出口参数：无
返回值：
0：设置成功
-1：通信超时错误
-2:通信器无效
-3:机号范围错误
-4：设置失败
                                                      */
/************************************************************************/
SMARTCOM_API int SetMacNoByDevID(Communicator& comm,const char* devID,int macNo);

/************************************************************************/
/* 功能：
读取程序版本和终端类型
入口参数：
comm:用于通信的通信器
verLen:存放appversion的缓冲长度
typelen：存放终端类型的缓冲长度
机号：默认255
出口参数： 
appVersion:程序版本
devType:终端类型
返回值：
0：读取成功
-1：通信超时错误
-2：通信器无效
-3: 机号范围错误
-4：读取失败
                                                     */
/************************************************************************/
SMARTCOM_API int GetAppVerAndDevType(Communicator& comm,char* appVersion,int Verlen,char* devType,int typeLen,
									 int MacNo=255);
#ifdef USE_SMARTCOMSTRING
SMARTCOM_API int GetAppVerAndDevType(Communicator& comm,SmartCom::string& appVersion,SmartCom::string& devType,
									 int MacNo=255);
#endif
/************************************************************************/
/* 功能：
复位终端设备
入口参数：
comm:用于通信的通信器
macNo:机号，默认255
出口参数：无
返回值：
0：成功
-1：通信超时错误
-2：通信器无效
-3:机号范围错误
                                                                    */
/************************************************************************/
SMARTCOM_API int ResetDev(Communicator& comm,int macNo=255);

/************************************************************************/
/* 功能：
获取读卡接口芯片ID号
入口参数：
comm:用于通信的通信器
chipIDLen:存放接口芯片ID的缓存长度
macNo:机号，默认255
出口参数：
chipID
返回值：
0：成功
-1：通信超时错误
-2：通信器无效
-3:机号范围错误
-4：读取失败
                                                                    */
/************************************************************************/
SMARTCOM_API int GetChipID(Communicator& comm,char* chipID,int chipIDLen,int macNo=255);

#ifdef USE_SMARTCOMSTRING
SMARTCOM_API int GetChipID(Communicator& comm,SmartCom::string& chipID,int macNo=255);
#endif
/************************************************************************/
/* 功能：
检测A卡（大卡）座与B卡（SIM卡）座是否有卡
入口参数：
comm:用于通信的通信器
macNO:机号，默认255
出口参数：
cardA:1,A卡座有卡；0，A卡座无卡
cardB:1,B卡座有卡；0，B卡座无卡
返回值：
0：检测成功
-1：通信超时错误
-2：通信器无效
-3:机号范围错误
-4：检测失败
                                                                      */
/************************************************************************/
SMARTCOM_API int IsCardReady(Communicator& comm,int& cardA,int& cardB,int macNo=255);

/************************************************************************/
/* 功能：
卡片复位应答
入口参数：
comm:用于通信的通信器
card：1:A卡，2：B卡,默认选择A卡
macNO:机号，默认255
出口参数：
retCode:复位命令的返回值
retCode="F9"：卡座无卡
retCode="FD"：不可识别卡
返回值：
0：成功
-1：通信超时错误
-2：通信器无效  
-3: 机号范围错误
 -4:复位失败                                                              */
/************************************************************************/
SMARTCOM_API int ResetCard(Communicator& comm,SmartCom::string& retCode,int card=1,int macNo=255);

/************************************************************************/
/* 功能：
卡片操作-APDU
入口参数：
comm:用于通信的通信器
apdu:十六进制字符串表示的apdu命令
card：1:A卡，2：B卡,默认选择A卡
macNO:机号，默认255
出口参数：
retCode:执行apdu指令的返回值
retCode="F9"：卡座无卡
retCode="FD"：不可识别卡
retCode="F2"： 无效7816命令包
retCode="F0"： 没有先给卡进行上电复位
返回值：
0：通信成功
-1：通信超时错误
-2：通信器无效 
-3: 机号范围错误
                                                                 */
/************************************************************************/
SMARTCOM_API int CardApdu(Communicator& comm,const char* apdu,SmartCom::string& retCode,int card=1,int macNo=255);


/************************************************************************/
/* 功能：卡片下电
入口参数：
comm:用于通信的通信器
macNO:机号，默认255
出口参数：无
返回值：
0：下电成功
-1：通信超时错误
-2：通信器无效
-3: 机号范围错误
-4：下电失败
                                                    */
/************************************************************************/
SMARTCOM_API int ShutdownCard(Communicator& comm,int macNo=255);

/************************************************************************/
/* 功能：
修改卡通信波特率
入口参数:
comm:用于通信的通信器
braudRate:要修改的波特率，只能选如下值：
115200，57600，38400，28800，23040，19200，14400，12800，9600
macNO:机号，默认255
出口参数：无
返回值：
0：修改成功
-1：通信超时错误
-2：通信器无效
-3: 机号范围错误
-4：修改失败
                                                              */
/************************************************************************/
SMARTCOM_API int ModifyCardBraudRate(Communicator& comm,int braudRate,int macNo=255);

/************************************************************************/
/* 功能：
读卡通信波特率
入口参数:
comm:用于通信的通信器
macNO:机号，默认255
出口参数：
braudRate：当前卡的通信波特率
返回值：
0：读取成功
-1：通信超时错误
-2：通信器无效
-3: 机号范围错误
-4：读取失败

                                                            */
/************************************************************************/
SMARTCOM_API int GetCardBraudRate(Communicator& comm,int& braudRate,int macNo=255);

/************************************************************************/
/* 功能：
修改卡片电源
入口参数:
comm:用于通信的通信器
power：电源：power=1: 5v，power=2: 3v，power=3: 1.8v
card:1:A卡，2：B卡,默认选择A卡
macNO:机号，默认255
出口参数：无
返回值：
0：修改成功
-1：通信超时错误
-2：通信器无效
-3: 机号范围错误
-4:修改失败
                                                            */
/************************************************************************/
SMARTCOM_API int ModifyCardPower(Communicator& comm,int power,int card=1,int macNo=255);

/************************************************************************/
/* 功能：
发送执行批处理APDU命令
入口参数：
comm:用于通信的通信器  
card:选择执行的卡，card=1为A卡，2为B卡。默认A卡
cmdNum:要执行的指令条数
macNO:机号，默认255
出口参数：无
返回值：
0：成功
-1：通信超时错误
-2：通信器无效
-3: 机号范围错误
-4: 发送失败
                                                               */
/************************************************************************/
SMARTCOM_API int  ExcuteMulAPDU(Communicator& comm,int cmdNum,int card=1,int macNo=255);

/************************************************************************/
/* 功能：
读批处理二进制脚本文件
入口参数：
comm:用于通信的通信器
bytes:要读取的字节数
 macNO:机号，默认255 
 strDataLen：存放读取的十六进制字符串数据的缓存长度
 offset:读取数据的文件偏移地址
 出口参数：
 strData:读取的转换成十六进制字符串的数据
 返回值：
 0：读取成功
 -1：通信超时错误
 -2：通信器无效
 -3: 机号范围错误
 -4: 读取失败
                                                              */
/************************************************************************/
SMARTCOM_API int GetScriptData(Communicator& comm,int offset,unsigned char bytes,char* strData,int strDataLen,int macNo=255);

#ifdef USE_SMARTCOMSTRING
SMARTCOM_API int GetScriptData(Communicator& comm,int offset,unsigned char bytes,SmartCom::string& strData,int macNo=255);
#endif
/************************************************************************/
/* 功能：
下载文件
入口参数：
comm:用于通信的通信器
flag:flag=1,下载命令体文件，flag=2，下载命令头文件
fileName:文件名
macNO:机号，默认255 
出口参数：无
 返回值：：
 0：下载成功
 -1：通信超时错误
-2：通信器无效 
-3: 机号范围错误
- 4: 下载失败
-5:文件打开失败
                                                           */
/************************************************************************/
SMARTCOM_API int DownloadFile(Communicator& comm,int flag,const char* fileName,int macNo=255);

/************************************************************************/
/* 功能：
查询执行批处理APDU结果
入口参数：
comm:用于通信的通信器
macNO:机号，默认255 
出口参数：
retCode:最后一条指令的返回值 
retCode="F1": 未选定卡或无卡或卡复位失败(卡已失效)，APDU响应超时（或无效的APDU命令）等错误。
返回值：
>=0的数：已经执行的命令条数
-1：通信超时错误
-2：通信器无效 
-3：机号范围错误
                                                  */
/************************************************************************/
SMARTCOM_API int CheckBatchResult(Communicator& comm,SmartCom::string& retCode,int macNo=255);

/************************************************************************/
/* 功能：
对SST25VF016B存储器进行整片擦除
入口参数：
comm:用于通信的通信器
macNO:机号，默认255 
出口参数：无
 返回值：
0: 擦除成功
-1：通信超时错误
-2：通信器无效
-3：机号范围错误
-4：擦除失败

/************************************************************************/
SMARTCOM_API int ClearMem(Communicator& comm,int macNo=255);

#endif