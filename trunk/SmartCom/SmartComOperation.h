#ifndef __SmartComOperation_H__
#define __SmartComOperation_H__

#include "SmartComString.h"

#ifdef SMARTCOMOP_EXPORTS
#define SMARTCOMOP_API  __declspec(dllexport) 
#else 
#define SMARTCOMOP_API  __declspec(dllimport) 
#endif

typedef unsigned char BYTE;
struct Communicator;
//ops
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
非NULL：指向一个有效的通信器指针
SC_NULL：失败
/************************************************************************/
SMARTCOMOP_API Communicator* GetCOMCommunicator(int comPort,int rate=115200,
									   int waitForSTX2Time=500,int normalWaitTime=500 );

/************************************************************************
功能：
获取一个udp通信器。
入口参数：
dstIP:目的ip
port：目的端口
waitForSTX2Time：第一个字符超时，默认1000ms
normalWaitTime：中间字符超时，默认1000ms
出口参数:
无
返回值：
非NULL：指向一个有效的通信器指针
SC_NULL：失败
***********************************************************************/
SMARTCOMOP_API Communicator* GetUDPCommunicator(const char* dstIP,int port,
									   int waitForSTX2Time=500,int normalWaitTime=500);

/****************************************************************************
*功能：释放通信器
*入口参数
pcomm：指向要释放的通信器的指针
返回
SC_SUCCESS：成功
SCERR_OPERROR：失败
SCERR_INVALID_COMM: 通信器无效
****************************************************************************/
SMARTCOMOP_API int ReleaseCommunicator(Communicator* pcomm);

/************************************************************************
功能：
读取终端设备id号和机号
入口参数：
pcomm:用于通信的通信器
devIDBufLen: devID缓冲的长度
出口参数:
DevID：存放7字节id号,
MacNo:1字节机号
返回值：
SC_SUCCESS：读取成功
SCERR_TIMEOUT：通信超时错误
SCERR_INVALID_COMM: 通信器无效
SCERR_OPERROR: 读取失败
/************************************************************************/
SMARTCOMOP_API int GetDevIDAndMacNo(Communicator* pcomm,SmartCom::string& devID,int& macNo);

/************************************************************************/
/*功能：
通过终端设备ID号给终端设备设置机号
入口参数：
pcomm:用于通信的通信器
DevID:存放7个字节的设备ID
MacNo:要设置的机号
出口参数：无
返回值：
SC_SUCCESS：设置成功
SCERR_TIMEOUT：通信超时错误
SCERR_INVALID_COMM:通信器无效
SCERR_MACNO_OUTRANGE:机号范围错误
SCERR_OPERROR：设置失败                                                      */
/************************************************************************/
SMARTCOMOP_API int SetMacNoByDevID(Communicator* pcomm,const char* devID,int macNo);

/************************************************************************/
/* 功能：
读取程序版本和终端类型
入口参数：
pcomm:用于通信的通信器
机号：默认255
出口参数： 
appVersion:程序版本
devType:终端类型
返回值：
SC_SUCCESS：读取成功
SCERR_TIMEOUT：通信超时错误
SCERR_INVALID_COMM：通信器无效
SCERR_MACNO_OUTRANGE: 机号范围错误
SCERR_OPERROR：读取失败                                                     */
/************************************************************************/
SMARTCOMOP_API int GetAppVerAndDevType(Communicator* pcomm,SmartCom::string& appVersion,SmartCom::string& devType,
									 int MacNo=255);
/************************************************************************/
/* 功能：
获取读卡接口芯片ID号
入口参数：
comm:用于通信的通信器
macNo:机号，默认255
出口参数：
chipID
返回值：
SC_SUCCESS：成功
SCERR_TIMEOUT：通信超时错误
SCERR_INVALID_COMM：通信器无效
SCERR_MACNO_OUTRANGE:机号范围错误
SCERR_OPERROR：读取失败                                                          */
/************************************************************************/
SMARTCOMOP_API int GetChipID(Communicator* comm,SmartCom::string& chipID,int macNo=255);

/************************************************************************/
/* 功能：
检测A卡（大卡）座与B卡（SIM卡）座是否有卡
入口参数：
comm:用于通信的通信器
macNO:机号，默认255
出口参数：
card: 如果card&CARDA_FLAG=1,A卡就绪，如果card&CARDB_FLAG=1,B卡就绪
返回值：
SC_SUCCESS：检测成功
SCERR_TIMEOUT：通信超时错误
SCERR_INVALID_COMM：通信器无效
SCERR_MACNO_OUTRANGE:机号范围错误
SCERR_OPERROR：检测失败                                                                     */
/************************************************************************/
SMARTCOMOP_API int IsCardReady(Communicator* comm,int& card,int macNo=255);

/************************************************************************/
/* 功能：
卡片复位应答
入口参数：
comm:用于通信的通信器
card：CARD_A:A卡，CARD_B：B卡,默认选择A卡
macNO:机号，默认255
出口参数：
retCode:复位命令的返回值
retCode="F9"：卡座无卡
retCode="FD"：不可识别卡
返回值：
SC_SUCCESS：成功
SCERR_TIMEOUT：通信超时错误
SCERR_INVALID_COMM：通信器无效  
SCERR_MACNO_OUTRANGE: 机号范围错误
SCERR_OPERROR:复位失败                                                              */
/************************************************************************/
SMARTCOMOP_API int ResetCard(Communicator* comm,SmartCom::string& retCode,CARD_AB card=CARD_A,int macNo=255);

/************************************************************************/
/* 功能：
卡片操作-APDU
入口参数：
comm:用于通信的通信器
apdu:十六进制字符串表示的apdu命令
card：CARD_A:A卡，CARD_B：B卡,默认选择A卡
macNO:机号，默认255
出口参数：
retCode:执行apdu指令的返回值
retCode="F9"：卡座无卡
retCode="FD"：不可识别卡
retCode="F2"： 无效7816命令包
retCode="F0"： 没有先给卡进行上电复位
返回值：
SC_SUCCESS：通信成功
SCERR_TIMEOUT：通信超时错误
SCERR_INVALID_COMM：通信器无效 
SCERR_MACNO_OUTRANGE: 机号范围错误                                                                */
/************************************************************************/
SMARTCOMOP_API int CardApdu(Communicator* comm,const char* apdu,SmartCom::string& retCode,
							CARD_AB card=CARD_A,int macNo=255);

/************************************************************************/
/* 功能：
卡片操作-APDU,此函数可以多条指令一起执行，格式为每条指令后跟一个中括号包含的返回码
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
通过宏 取得具体定义,SC_SERIAL()宏取得的值为执行到第几条指令，
SC_CODE()宏取得的值为执行结果：
SC_SUCCESS:成功
SCERR_TIMEOUT:通信超时
SCERR_CMDFORMAT_ERR:命令格式错
SCERR_INVALID_COMM：通信器无效
SCERR_MACNO_OUTRANGE: 机号范围错误
SCERR_OPERROR:执行出错，retcode对应最后一条指令的返回码                              */
/************************************************************************/
SMARTCOMOP_API int CardApduK(Communicator* comm,const char* apdu,SmartCom::string& retCode,int card=1,int macNo=255);

/************************************************************************/
/* 功能：卡片下电
入口参数：
comm:用于通信的通信器
macNO:机号，默认255
出口参数：无
返回值：
SC_SUCCESS：下电成功
SCERR_TIMEOUT：通信超时错误
SCERR_INVALID_COMM：通信器无效
SCERR_MACNO_OUTRANGE: 机号范围错误
SCERR_OPERROR：下电失败
                                                    */
/************************************************************************/
SMARTCOMOP_API int ShutdownCard(Communicator* comm,int macNo=255);

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
SC_SUCCESS：修改成功
SCERR_TIMEOUT：通信超时错误
SCERR_INVALID_COMM：通信器无效
SCERR_MACNO_OUTRANGE: 机号范围错误
SCERR_OPERROR：修改失败
                                                              */
/************************************************************************/
SMARTCOMOP_API int ModifyCardBraudRate(Communicator* comm,int braudRate,int macNo=255);

/************************************************************************/
/* 功能：
读卡通信波特率
入口参数:
comm:用于通信的通信器
macNO:机号，默认255
出口参数：
braudRate：当前卡的通信波特率
返回值：
SC_SUCCESS：读取成功
SCERR_TIMEOUT：通信超时错误
SCERR_INVALID_COMM：通信器无效
SCERR_MACNO_OUTRANGE: 机号范围错误
SCERR_OPERROR：读取失败
                                                            */
/************************************************************************/
SMARTCOMOP_API int GetCardBraudRate(Communicator* comm,int& braudRate,int macNo=255);

/************************************************************************/
/* 功能：
修改卡片电源
入口参数:
comm:用于通信的通信器
power：电源：power=POWER_5V: 5v，power=POWER_3V: 3v，power=POWER_1_8V: 1.8v
card:1:A卡，2：B卡,默认选择A卡
macNO:机号，默认255
出口参数：无
返回值：
SC_SUCCESS：修改成功
SCERR_TIMEOUT：通信超时错误
SCERR_INVALID_COMM：通信器无效
SCERR_MACNO_OUTRANGE: 机号范围错误
SCERR_OPERROR:修改失败
                                                            */
/************************************************************************/
SMARTCOMOP_API int ModifyCardPower(Communicator* comm,CARD_POWER power,CARD_AB card=CARD_A,int macNo=255);

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
SC_SUCCESS：成功
SCERR_TIMEOUT：通信超时错误
SCERR_INVALID_COMM：通信器无效
SCERR_MACNO_OUTRANGE: 机号范围错误
SCERR_OPERROR: 发送失败
                                                               */
/************************************************************************/
SMARTCOMOP_API int  ExcuteMulAPDU(Communicator* comm,int cmdNum,CARD_AB card=CARD_A,int macNo=255);

/************************************************************************/
/* 功能：
发送执行批处理APDU命令,并等待批处理完成后才返回
入口参数：
comm:用于通信的通信器  
card:选择执行的卡，card=1为A卡，2为B卡。默认A卡
cmdNum:要执行的指令条数
macNO:机号，默认255
出口参数：无
返回值：
SC_SUCCESS：成功
SCERR_TIMEOUT：通信超时错误
SCERR_INVALID_COMM：通信器无效
SCERR_MACNO_OUTRANGE: 机号范围错误
SCERR_OPERROR: 发送失败
*/
/************************************************************************/
SMARTCOMOP_API int  ExcuteMulAPDUSyn(Communicator* comm,int cmdNum,CARD_AB card=CARD_A,int macNo=255);

/************************************************************************/
/* 功能：
读批处理二进制脚本文件
入口参数：
comm:用于通信的通信器
bytes:要读取的字节数
 macNO:机号，默认255 
 offset:读取数据的文件偏移地址
 出口参数：
 strData:读取的转换成十六进制字符串的数据
 返回值：
SC_SUCCESS：读取成功
SCERR_TIMEOUT：通信超时错误
SCERR_INVALID_COMM：通信器无效
SCERR_MACNO_OUTRANGE: 机号范围错误
SCERR_OPERROR: 读取失败
                                                              */
/************************************************************************/
SMARTCOMOP_API int GetScriptData(Communicator* comm,int offset,unsigned char bytes,SmartCom::string& strData,int macNo=255);

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
SC_SUCCESS：下载成功
SCERR_TIMEOUT：通信超时错误
SCERR_INVALID_COMM：通信器无效
SCERR_MACNO_OUTRANGE: 机号范围错误
SCERR_OPERROR: 下载失败
SCERR_OPENFILE_FAIL:文件打开失败
                                                           */
/************************************************************************/
SMARTCOMOP_API int DownloadFile(Communicator* comm,FILE_TYPE flag,const char* fileName,int macNo=255);

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
SC_SUCCESS：下载成功
SCERR_TIMEOUT：通信超时错误
SCERR_INVALID_COMM：通信器无效
SCERR_MACNO_OUTRANGE: 机号范围错误
SCERR_OPERROR: 下载失败
SCERR_OPENFILE_FAIL:文件打开失败
SCERR_DRIVER_NOTINSTALL:下载驱动未安装
                                                           */
/************************************************************************/
SMARTCOMOP_API int DownloadFileK(Communicator* comm,FILE_TYPE flag,const char* fileName,int macNo=255);

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
SC_EXCUTING：正在执行
SCERR_INVALID_COMM：通信器无效
SCERR_MACNO_OUTRANGE: 机号范围错误
                                                  */
/************************************************************************/
SMARTCOMOP_API int CheckBatchResult(Communicator* comm,SmartCom::string& retCode,int macNo=255);


/************************************************************************/
/* 功能：
对SST25VF016B存储器进行整片擦除
入口参数：
comm:用于通信的通信器
macNO:机号，默认255 
出口参数：无
 返回值：
SC_SUCCESS: 擦除成功
SCERR_TIMEOUT：通信超时错误
SCERR_INVALID_COMM：通信器无效
SCERR_MACNO_OUTRANGE: 机号范围错误
SCERR_OPERROR：擦除失败

/************************************************************************/
SMARTCOMOP_API int ClearMem(Communicator* comm,int macNo=255);

/************************************************************************/
/* 功能：
设置多条APDU批处理完成后自动给回答
入口参数：
comm:用于通信的通信器
macNO:机号，默认255 
出口参数：无
返回值：
SC_SUCCESS: 设置成功
SCERR_TIMEOUT：通信超时错误
SCERR_INVALID_COMM：通信器无效
SCERR_MACNO_OUTRANGE: 机号范围错误
SCERR_OPERROR：设置失败

/************************************************************************/
SMARTCOMOP_API int EnableAutoAnswer(Communicator* comm,int macNo=255);

/************************************************************************/
/* 功能：
禁止多条APDU批处理完成后自动给回答
入口参数：
comm:用于通信的通信器
macNO:机号，默认255 
出口参数：无
返回值：
SC_SUCCESS: 设置成功
SCERR_TIMEOUT：通信超时错误
SCERR_INVALID_COMM：通信器无效
SCERR_MACNO_OUTRANGE: 机号范围错误
SCERR_OPERROR：设置失败

/************************************************************************/
SMARTCOMOP_API int DisableAutoAnswer(Communicator* comm,int macNo=255);

/************************************************************************/
/* 功能：
设置发送数据时间间隔,实际间隔=5*（0～255）μS
入口参数：
comm:用于通信的通信器
interval:0~255,单位μS，实际间隔=5*（0～255）μS
macNO:机号，默认255 
出口参数：无
返回值：
SC_SUCCESS: 设置成功
SCERR_TIMEOUT：通信超时错误
SCERR_INVALID_COMM：通信器无效
SCERR_MACNO_OUTRANGE: 机号范围错误
SCERR_OPERROR：设置失败

/************************************************************************/
SMARTCOMOP_API int SetSendInterval(Communicator* comm,BYTE interval,int macNo=255);


#endif