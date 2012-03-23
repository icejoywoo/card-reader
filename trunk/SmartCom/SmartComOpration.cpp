#include "stdafx.h"
#define SMARTCOMOP_EXPORTS
#define SMARTCOM_EXPORTS_MACRO
#define SMARTCOMSTRING_EXPORTS_MACRO
#define COMMUNICATOR_EXPORTS_MACRO
#include "SmartComDefine.h"
#include "SmartComOperation.h"
#include "SmartCom.h"
#include "CustomConsts.h"

//��ȡcomͨ����
Communicator* GetCOMCommunicator(int comPort,int rate/* =115200 */, 
								 int waitForSTX2Time/* =500 */,int normalWaitTime/* =500  */)
{
	Communicator* comm=new Communicator;
	if(0!=GetOneCOMCommunicator(*comm,comPort,rate,waitForSTX2Time,normalWaitTime))
		return SC_NULL;
	else 
		return comm;
}

//��ȡudpͨ����
Communicator* GetUDPCommunicator(const char* dstIP,int port,
									   int waitForSTX2Time/*=500*/,int normalWaitTime/*=500*/)
{
	Communicator* comm=new Communicator;
	if(0!=GetOneUDPCommunicator(*comm,dstIP,port,waitForSTX2Time,normalWaitTime))
		return SC_NULL;
	else 
		return comm;
}

//�ͷ�ͨ����
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

//��ȡ����
int GetDevIDAndMacNo(Communicator* pcomm,SmartCom::string& devID,int& macNo)
{
	return GetDevIDAndMacNo(*pcomm,devID,macNo);
}

//���û���
int SetMacNoByDevID(Communicator* pcomm,const char* devID,int macNo)
{
	return SetMacNoByDevID(*pcomm,devID,macNo);
}

//��ȡ����汾���ն�����
int GetAppVerAndDevType(Communicator* pcomm,SmartCom::string& appVersion,SmartCom::string& devType,
									 int MacNo/*=255*/)
{
	return GetAppVerAndDevType(*pcomm,appVersion,devType,MacNo);
}

//��ȡоƬID
int GetChipID(Communicator* comm,SmartCom::string& chipID,int macNo/* =255 */)
{
	return GetChipID(*comm,chipID,macNo);
}

//���AB�����Ƿ��п�
int IsCardReady(Communicator* comm,int& card,int macNo/* =255 */)
{
	int ret=0,a=0,b=0;
	ret=IsCardReady(*comm,a,b,macNo);
	card=a|b;
	return ret;
}

//��Ƭ��λӦ��
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

//��Ƭ�µ�
int ShutdownCard(Communicator* comm,int macNo/* =255 */)
{
	return ShutdownCard(*comm,macNo);
}

//�޸�ͨ�Ų�����
int ModifyCardBraudRate(Communicator* comm,int braudRate,int macNo/* =255 */)
{
	return ModifyCardBraudRate(*comm,braudRate,macNo);
}

//��ȡ��Ƭͨ�Ų�����
int GetCardBraudRate(Communicator* comm,int& braudRate,int macNo/* =255 */)
{
	return GetCardBraudRate(*comm,braudRate,macNo);
}

//�޸Ŀ�Ƭ��Դ
int ModifyCardPower(Communicator* comm,CARD_POWER power,CARD_AB card/* =CARD_A */,int macNo/* =255 */)
{
	return ModifyCardPower(*comm,power,card,macNo);
}

//����ִ��������APDU����
int ExcuteMulAPDU(Communicator* comm,int cmdNum,CARD_AB card/* =CARD_A */,int macNo/* =255 */)
{
	return ExcuteMulAPDU(*comm,cmdNum,card,macNo);
}

int ExcuteMulAPDUSyn(Communicator* comm,int cmdNum,CARD_AB card/* =CARD_A */,int macNo/* =255 */)
{
	return ExcuteMulAPDUSyn(*comm,cmdNum,card,macNo);
}

//������������ƽű��ļ�
int GetScriptData(Communicator* comm,int offset,unsigned char bytes,SmartCom::string& strData,int macNo/* =255 */)
{
    return GetScriptData(*comm,offset,bytes,strData,macNo);
}

//�����ļ�
int DownloadFile(Communicator* comm,FILE_TYPE flag,const char* fileName,int macNo/* =255 */)
{
	return DownloadFile(*comm,flag,fileName,macNo);
}
int DownloadFileK(Communicator* comm,FILE_TYPE flag,const char* fileName,int macNo/* =255 */)
{
	return DownloadFileK(*comm,flag,fileName,macNo);
}

//��ѯִ��������APDU���
int CheckBatchResult(Communicator* comm,SmartCom::string& retCode,int macNo/* =255 */)
{
	return CheckBatchResult(*comm,retCode,macNo);
}

//��SST25VF016B�洢��������Ƭ����
int ClearMem(Communicator* comm,int macNo/* =255 */)
{
	return ClearMem(*comm,macNo);
}

//���ö���APDU��������ɺ��Զ����ش�
int EnableAutoAnswer(Communicator* comm,int macNo/* =255 */)
{
	return EnableAutoAnswer(*comm,macNo);
}

//��ֹ����APDU��������ɺ��Զ����ش�
int DisableAutoAnswer(Communicator* comm,int macNo/* =255 */)
{
	return DisableAutoAnswer(*comm,macNo);
}

//���÷�������ʱ����
int SetSendInterval(Communicator* comm,BYTE interval,int macNo/* =255 */)
{
	return SetSendInterval(*comm,interval,macNo);
}
