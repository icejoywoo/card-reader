#include "stdafx.h"
#define SMARTCOMOP_EXPORTS
#define SMARTCOM_EXPORTS_MACRO
#define SMARTCOMSTRING_EXPORTS_MACRO
#define COMMUNICATOR_EXPORTS_MACRO
#include "SmartComDefine.h"
#include "SmartComOperation.h"
#include "SmartCom.h"
#include "CustomConsts.h"

//获取com通信器
Communicator* GetCOMCommunicator(int comPort,int rate/* =115200 */, 
								 int waitForSTX2Time/* =500 */,int normalWaitTime/* =500  */)
{
	Communicator* comm=new Communicator;
	if(0!=GetOneCOMCommunicator(*comm,comPort,rate,waitForSTX2Time,normalWaitTime))
		return SC_NULL;
	else 
		return comm;
}

//获取udp通信器
Communicator* GetUDPCommunicator(const char* dstIP,int port,
									   int waitForSTX2Time/*=500*/,int normalWaitTime/*=500*/)
{
	Communicator* comm=new Communicator;
	if(0!=GetOneUDPCommunicator(*comm,dstIP,port,waitForSTX2Time,normalWaitTime))
		return SC_NULL;
	else 
		return comm;
}

//释放通信器
int ReleaseCommunicator(Communicator* pcomm)
{
	if(pcomm==0)
		return SCERR_INVALID_COMM;
	if(pcomm->m_nCommtype==COMM_UDP)
		return ReleaseUDPCommunicator(pcomm);
	else if(pcomm->m_nCommtype==COMM_COM)
		return ReleaseCOMCommunicator(pcomm);
	else
		return SCERR_INVALID_COMM;
}

//获取机号
int GetDevIDAndMacNo(Communicator* pcomm,SmartCom::string& devID,int& macNo)
{
	return GetDevIDAndMacNo(*pcomm,devID,macNo);
}

//设置机号
int SetMacNoByDevID(Communicator* pcomm,const char* devID,int macNo)
{
	return SetMacNoByDevID(*pcomm,devID,macNo);
}

//读取程序版本和终端类型
int GetAppVerAndDevType(Communicator* pcomm,SmartCom::string& appVersion,SmartCom::string& devType,
									 int MacNo/*=255*/)
{
	return GetAppVerAndDevType(*pcomm,appVersion,devType,MacNo);
}

//获取芯片ID
int GetChipID(Communicator* comm,SmartCom::string& chipID,int macNo/* =255 */)
{
	return GetChipID(*comm,chipID,macNo);
}

//检测AB卡座是否有卡
int IsCardReady(Communicator* comm,int& card,int macNo/* =255 */)
{
	int ret=0,a=0,b=0;
	ret=IsCardReady(*comm,a,b,macNo);
	card=a|b;
	return ret;
}

//卡片复位应答
int ResetCard(Communicator* comm,SmartCom::string& retCode,CARD_AB card/* =CARD_A */,int macNo/* =255 */)
{
	return ResetCard(*comm,retCode,card,macNo);
}

//apdu
int CardApdu(Communicator* comm,const char* apdu,SmartCom::string& retCode, CARD_AB card/* =CARD_A */,int macNo/* =255 */)
{
	return CardApdu(*comm,apdu,retCode,card,macNo);
}

//
int CardApduK(Communicator* comm,const char* apdu,SmartCom::string& retCode,int card/* =1 */,int macNo/* =255 */)
{
	return CardApduK(*comm,apdu,retCode,card,macNo);
}

//卡片下电
int ShutdownCard(Communicator* comm,int macNo/* =255 */)
{
	return ShutdownCard(*comm,macNo);
}

//修改通信波特率
int ModifyCardBraudRate(Communicator* comm,int braudRate,int macNo/* =255 */)
{
	return ModifyCardBraudRate(*comm,braudRate,macNo);
}

//获取卡片通信波特率
int GetCardBraudRate(Communicator* comm,int& braudRate,int macNo/* =255 */)
{
	return GetCardBraudRate(*comm,braudRate,macNo);
}

//修改卡片电源
int ModifyCardPower(Communicator* comm,CARD_POWER power,CARD_AB card/* =CARD_A */,int macNo/* =255 */)
{
	return ModifyCardPower(*comm,power,card,macNo);
}

//发送执行批处理APDU命令
int ExcuteMulAPDU(Communicator* comm,int cmdNum,CARD_AB card/* =CARD_A */,int macNo/* =255 */)
{
	return ExcuteMulAPDU(*comm,cmdNum,card,macNo);
}

int ExcuteMulAPDUSyn(Communicator* comm,int cmdNum,CARD_AB card/* =CARD_A */,int macNo/* =255 */)
{
	return ExcuteMulAPDUSyn(*comm,cmdNum,card,macNo);
}

//读批处理二进制脚本文件
int GetScriptData(Communicator* comm,int offset,unsigned char bytes,SmartCom::string& strData,int macNo/* =255 */)
{
    return GetScriptData(*comm,offset,bytes,strData,macNo);
}

//下载文件
int DownloadFile(Communicator* comm,FILE_TYPE flag,const char* fileName,int macNo/* =255 */)
{
	return DownloadFile(*comm,flag,fileName,macNo);
}
int DownloadFileK(Communicator* comm,FILE_TYPE flag,const char* fileName,int macNo/* =255 */)
{
	return DownloadFileK(*comm,flag,fileName,macNo);
}

//查询执行批处理APDU结果
int CheckBatchResult(Communicator* comm,SmartCom::string& retCode,int macNo/* =255 */)
{
	return CheckBatchResult(*comm,retCode,macNo);
}

//对SST25VF016B存储器进行整片擦除
int ClearMem(Communicator* comm,int macNo/* =255 */)
{
	return ClearMem(*comm,macNo);
}

//设置多条APDU批处理完成后自动给回答
int EnableAutoAnswer(Communicator* comm,int macNo/* =255 */)
{
	return EnableAutoAnswer(*comm,macNo);
}

//禁止多条APDU批处理完成后自动给回答
int DisableAutoAnswer(Communicator* comm,int macNo/* =255 */)
{
	return DisableAutoAnswer(*comm,macNo);
}

//设置发送数据时间间隔
int SetSendInterval(Communicator* comm,BYTE interval,int macNo/* =255 */)
{
	return SetSendInterval(*comm,interval,macNo);
}
