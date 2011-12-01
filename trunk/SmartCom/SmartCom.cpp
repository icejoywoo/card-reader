// SmartCom.cpp : Defines the entry point for the DLL application.
//
#include "stdafx.h"
#define SMARTCOM_EXPORTS_MACRO
#define SMARTCOMSTRING_EXPORTS_MACRO

#include "ASSERT.H"
#include "smartcom411.h"
#include "SmartCom.h"
#include "stdio.h"
#include "ContactManager.h"
#include "CustomConsts.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

//����ͨ��
 void CommProcess(Communicator&comm,BYTE* buf,int buflen,int nSendLen,int& sendRetCode,int& recLen);

/************************************************************************/
/* ��ʼ��udpͨ��                                                                     */
/************************************************************************/
int InitUDPComm()
{
  if(0==StartWinSocketEnv())
	  return 0;
  else
	  return -1;
}

/************************************************************************/
/* �ر�udpͨ��                                                                     */
/************************************************************************/
int CloseUDPComm()
{
	//�ȼ����ٳ�ʼ��,�����ȡ�����ɹ�һֱ�ȴ���
	WaitForSingleObject(Connections::hUDPInitMutex,INFINITE);
	UdpConnection* con=Connections::udpConnHead;
	UdpConnection* p=con;
	for(;con;)
	{
		if(CloseUDPSocket(con->s)<0)
		{
			Connections::udpConnHead=con;
			ReleaseMutex(Connections::hUDPInitMutex);
			return -1;
		}
		con=con->next;
		delete p;
		p=con;
	}
	Connections::udpConnHead=0;
	CloseWinSocketEnv();
	ReleaseMutex(Connections::hUDPInitMutex);
	return 0;
}

/************************************************************************/
/* �ر�comͨ��                                                                     */
/************************************************************************/
SMARTCOM_API int CloseCOMComm()
{
	WaitForSingleObject(Connections::hCOMInitMutex,INFINITE);
	ComConnection* p=Connections::comConnHead;
	ComConnection* p2=p;
    for(;p;)
	{
		if(CloseCom(p->comPort)<0)
		{
			Connections::comConnHead=p;
			ReleaseMutex(Connections::hCOMInitMutex);
			return -1;
		}
		p=p->next;
		delete p2;
        p2=p;
	}
	Connections::comConnHead=0;
	ReleaseMutex(Connections::hCOMInitMutex);
	return 0;
}
/************************************************************************/
/* ��ȡһ��udpͨ����                                                                     */
/************************************************************************/
int GetOneUDPCommunicator(Communicator& aCommunicator,const char* dstIP,int port,
						  int waitForSTX2Time,int normalWaitTime)
{
	//�ȼ����ٳ�ʼ��,�����ȡ�����ɹ�һֱ�ȴ���
	WaitForSingleObject(Connections::hUDPInitMutex,INFINITE);
	UdpConnection* p=Connections::udpConnHead;
	UdpConnection* prev=p;
	for(;p;)
	{
		if(0==strcmp(dstIP,p->dstIP)&&port==p->dstPort)
		{
			aCommunicator.udpConn=p;
			aCommunicator.m_nCommtype=COMM_UDP;
			ReleaseMutex(Connections::hUDPInitMutex);
			return 0;
		}
		prev=p;
		p=p->next;
	}
	SOCKET s;
	//��ʼ��ͨ����
	int newPort=port;
	while(TRUE)
	{
		int temp=GetOneLocalSocket(&s,newPort);
		if(temp!=0)
		{
			newPort+=10;
			if(newPort<port+100)
				continue;
			else
			{
				ReleaseMutex(Connections::hUDPInitMutex);
			    return -1;
			}
		}
		break;
	}

	UdpConnection* con=new UdpConnection(newPort,(char*)dstIP,port,s,waitForSTX2Time,normalWaitTime,0);
	if(NULL==Connections::udpConnHead)
	{
		Connections::udpConnHead=con;
	}
	else
	{
		prev->next=con;
	}
	aCommunicator.udpConn=con;
	aCommunicator.m_nCommtype=COMM_UDP;
	ReleaseMutex(Connections::hUDPInitMutex);
	return 0;
}

/************************************************************************/
/* ��ȡcomͨ����                                                                     */
/************************************************************************/
SMARTCOM_API int GetOneCOMCommunicator(Communicator& aCommunicator,int comPort,int rate,int waitForSTX2Time,int normalWaitTime)
{
	WaitForSingleObject(Connections::hCOMInitMutex,INFINITE);
	ComConnection* p=Connections::comConnHead;
	ComConnection* prev=p;
	for(;p;)
	{
		if(comPort==p->comPort)
		{
			aCommunicator.m_nCommtype=COMM_COM;
			aCommunicator.comConn=p;
			ReleaseMutex(Connections::hCOMInitMutex);
			return 0;
		}
		prev=p;
		p=p->next;
	}
	//��ʼ������
	if(0!=IniCom(comPort,rate))
	{
		ReleaseMutex(Connections::hCOMInitMutex);
		return -1;
	}
    p=new ComConnection(comPort,rate,waitForSTX2Time,normalWaitTime,0);
	if(NULL==Connections::comConnHead)
		Connections::comConnHead=p;
	else
		prev->next=p;
	aCommunicator.m_nCommtype=COMM_COM;
	aCommunicator.comConn=p;
	ReleaseMutex(Connections::hCOMInitMutex);
	return 0;
}

/************************************************************************/
/* ��ȡ�ն��豸ID�źͻ���                                                                   
/************************************************************************/
int GetDevIDAndMacNo(Communicator& comm,char* devID,int devIDLen,int& macNo)
{
	if(NOT_CONNECT==comm.m_nCommtype)
		return -2;
	int cmd=0xe1;
	int dataLen=0;
	BYTE tempBuffer[1];
	BYTE SRBuffer[64];
	int packetLen=PrepareBytes(255,cmd,tempBuffer,&dataLen,SRBuffer);

	//��������
	int retCode,recLen;
	CommProcess(comm,SRBuffer,64,packetLen,retCode,recLen);
	if(recLen<0)
		return -1;
	char t[8];
	int k=0;
	devID[0]='\0';
	assert(devIDLen>21);
	//���豸IDʮ������ת�����ַ���
	for(int i=4;i<11;i++) 
	{
       sprintf(t,"%02X",*(SRBuffer+i));
	   strcat(devID,t);
	   if(i!=10)
	   {
		  strcat(devID," ");
	   }
	}
	macNo=*(SRBuffer+11);
	if(SRBuffer[2]==0)
	      return 0;
	else
		return -3;
}

//���庯����smartcom string�汾
#ifdef USE_SMARTCOMSTRING
int GetDevIDAndMacNo(Communicator& comm,SmartCom::string& devID,int& macNo)
{
	if(NOT_CONNECT==comm.m_nCommtype)
		return -2;
	int cmd=0xe1;
	int dataLen=0;
	BYTE tempBuffer[1];
	BYTE SRBuffer[64];
	int packetLen=PrepareBytes(255,cmd,tempBuffer,&dataLen,SRBuffer);
	
	//��������
	int retCode,recLen;
	CommProcess(comm,SRBuffer,64,packetLen,retCode,recLen);
	if(recLen<0)
		return -1;
	char t[8];
	//���豸IDʮ������ת�����ַ���
	devID="";
	for(int i=4;i<11;i++) 
	{
		sprintf(t,"%02X",*(SRBuffer+i));
		devID+=t;
		if(i!=10)
		{
			devID+=" ";
		}
	}
	macNo=*(SRBuffer+11);
	if(SRBuffer[2]==0)
		return 0;
	else
		return -3;
}

#endif

/************************************************************************/
/* ͨ���ն��豸ID�Ÿ��ն��豸���û���                                             
/************************************************************************/
inline int RemBlankSpace(char* str,int len);

int SetMacNoByDevID(Communicator& comm,const char* devID,int macNo)
{
	if(NOT_CONNECT==comm.m_nCommtype)
		return -2;
	if(macNo>255||macNo<1)
		 return -3;
	//�ж�Ҫ���õĻ�����ԭ�������Ƿ�һ��
	SmartCom::string str;
	int tempMacNo=0;
    if(0!=GetDevIDAndMacNo(comm,str,tempMacNo))
		return -1;
	if(tempMacNo==macNo)
		return 0;
	int cmd=0xe3;
	int dataLen=8;
	BYTE tempBuffer[64];
	BYTE SRBuffer[64];
	assert(strlen(devID)<50);

	strcpy((char*)SRBuffer,devID);
	//ȥ���ַ����еĿո�
    RemBlankSpace((char*)SRBuffer,strlen((char*)SRBuffer));

	//���ַ�����ʾ��ʮ������ֵת��Ϊ��ֵ
	SVC_DSP_2_HEX(SRBuffer,tempBuffer,7);
	tempBuffer[7]=macNo;
    int packetLen=PrepareBytes(255,cmd,tempBuffer,&dataLen,SRBuffer);
	//��������
	int retCode,recLen;
	CommProcess(comm,SRBuffer,64,packetLen,retCode,recLen);
	if(recLen<0)
		return -1;
	if(SRBuffer[2]==0)
		return 0;
	else
		return -4;
}
//ȥ���ַ����е����пո�,���ش����ĳ���
 inline int RemBlankSpace(char* str,int len)
{
	char temp[512];
	assert(len<510);
	int j=0;
   for(int i=0;i<len;i++)
   {
	   if(' '==str[i])
		   continue;
	   else
	   {
		   temp[j++]=str[i];
	   }
   }
   //���¿�����ԭ����λ��
   memcpy(str,temp,j);
   str[j]='\0';
   return j;
}

 /************************************************************************/
 /* ������汾���ն�����                                                               
 /************************************************************************/
int GetAppVerAndDevType(Communicator& comm,char* appVersion,int Verlen,char* devType,int typeLen,
									 int MacNo)
 {
	 if(NOT_CONNECT==comm.m_nCommtype)
		 return -2;
	 if(MacNo>255||MacNo<1)
		 return -3;
	 assert(Verlen>30);
	 assert(typeLen>40);
	 int cmd=0xe4;
	 int dataLen=0;
	 BYTE tempBuffer[16];
	 BYTE SRBuffer[64];
	 int packetLen=PrepareBytes(MacNo,cmd,tempBuffer,&dataLen,SRBuffer);
	 //��������
	 int retCode,recLen;
	 CommProcess(comm,SRBuffer,64,packetLen,retCode,recLen);
	 if(recLen<0)
		return -1;
     char year[8],month[8],day[8],hour[8];
	 int j=0;
	 appVersion[0]='\0';
	 sprintf(year,"%u",*(SRBuffer+4));
     sprintf(month,"%u",*(SRBuffer+5));
	 sprintf(day,"%u",*(SRBuffer+6));
	 sprintf(hour,"%u",*(SRBuffer+7));

	 strcat(appVersion,year);
	 strcat(appVersion,"��");
	 strcat(appVersion,month);
	 strcat(appVersion,"��");
	 strcat(appVersion,day);
	 strcat(appVersion,"��");
	 strcat(appVersion,hour);
	 strcat(appVersion,"ʱ");

	 char t[8];
	 j=0;
	 devType[0]='\0';
	 sprintf(t,"%02X",*(SRBuffer+8));
	 strcat(devType,t);
	 sprintf(t,"%02X",*(SRBuffer+9));
	 strcat(devType,t);
	 switch(*(BYTE*)(SRBuffer+9))
	 {
	 case 1:
		 strcat(devType,"(�ſ���д��)");
		 break;
	 case 2:
		 strcat(devType,"(�Ӵ�ʽͬ�������洢���ͼ��ܿ�)");
		 break;
	 case 3:
		 strcat(devType,"(�Ӵ�ʽCPU����д��)");
		 break;
	 case 4:
		 strcat(devType,"(�ǽӴ�ʽ�洢����д��)");
		 break;
	 case 5:
		 strcat(devType,"(�ǽӴ�ʽCPU����д��)");
		 break;
	 case 6:
		 strcat(devType,"(˫���濨��д��)");
		 break;
	 }

	 if(SRBuffer[2]==0)
		 return 0;
	 else
		return -4;
 }

 //���庯����smartcom string�汾
#ifdef USE_SMARTCOMSTRING
int GetAppVerAndDevType(Communicator& comm,SmartCom::string& appVersion,SmartCom::string& devType,
									 int MacNo)
{
	if(NOT_CONNECT==comm.m_nCommtype)
		return -2;
	if(MacNo>255||MacNo<1)
		return -3;
	int cmd=0xe4;
	int dataLen=0;
	BYTE tempBuffer[16];
	BYTE SRBuffer[64];
	int packetLen=PrepareBytes(MacNo,cmd,tempBuffer,&dataLen,SRBuffer);
	appVersion="";
	devType="";
	//��������
	int retCode,recLen;
	CommProcess(comm,SRBuffer,64,packetLen,retCode,recLen);
	if(recLen<0)
		return -1;
	char year[8],month[8],day[8],hour[8];
	sprintf(year,"%u",*(SRBuffer+4));
	sprintf(month,"%u",*(SRBuffer+5));
	sprintf(day,"%u",*(SRBuffer+6));
	sprintf(hour,"%u",*(SRBuffer+7));
	
	appVersion+=year;
	appVersion+="��";
	appVersion+=month;
	appVersion+="��";
	appVersion+=day;
	appVersion+="��";
	appVersion+=hour;
	appVersion+="ʱ";
	
	char t[8];
	sprintf(t,"%02X",*(SRBuffer+8));
	devType+=t;
	sprintf(t,"%02X",*(SRBuffer+9));
	devType+=t;
	switch(*(BYTE*)(SRBuffer+9))
	{
	case 1:
	    devType+="(�ſ���д��)";
		break;
	case 2:
		devType+="(�Ӵ�ʽͬ�������洢���ͼ��ܿ�)";
		break;
	case 3:
		devType+="(�Ӵ�ʽCPU����д��)";
		break;
	case 4:
		devType+="(�ǽӴ�ʽ�洢����д��)";
		break;
	case 5:
		devType+="(�ǽӴ�ʽCPU����д��)";
		break;
	case 6:
		devType+="(˫���濨��д��)";
		break;
	}
	
	if(SRBuffer[2]==0)
		return 0;
	else
		return -4;
}
#endif

 /************************************************************************/
 /* ��λ�ն��豸                                                                     */
 /************************************************************************/
int ResetDev(Communicator& comm,int macNo /*=255*/)
 {
	 if(NOT_CONNECT==comm.m_nCommtype)
		 return -2;
	 if(macNo>255||macNo<1)
		 return -3;
	 int cmd=0xe8;
	 int dataLen=0;
	 BYTE tempBuffer[16];
	 BYTE SRBuffer[64];
	 int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	 //��������
	 int retCode;
	// CommProcess(comm,SRBuffer,packetLen,retCode,SRBuffer,recLen);
	 if(COMM_UDP==comm.m_nCommtype)
		 retCode=SendUDPData(comm.udpConn->s,comm.udpConn->dstIP,comm.udpConn->dstPort, SRBuffer,packetLen);
	 else if(COMM_COM==comm.m_nCommtype)
		 retCode=SendBytes(comm.comConn->comPort,SRBuffer,packetLen);
	 else if(COMM_TCPCLIENT==comm.m_nCommtype||COMM_TCPSERVER==comm.m_nCommtype)
		 retCode=SendData(comm.tcpClientConn->s,SRBuffer,packetLen);

	 if(retCode<0)
		return -1;
	 return 0;
 }

 /************************************************************************/
 /* ��ȡ�����ӿ�оƬID��                                                                     */
 /************************************************************************/
int GetChipID(Communicator& comm,char* chipID,int len,int macNo/* =255 */)
 {
     if(NOT_CONNECT==comm.m_nCommtype)
		 return -2;
	 if(macNo>255||macNo<1)
		 return -3;
	 int cmd=0x01;
	 int dataLen=0;
	 BYTE tempBuffer[16];
	 BYTE SRBuffer[64];
	 int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	 //��������
	 int retCode,recLen;
	 CommProcess(comm,SRBuffer,64,packetLen,retCode,recLen);
	 if(recLen<0)
		return -1;
	 sprintf((char*)tempBuffer,"%02X",*(SRBuffer+4));
	 tempBuffer[2]='\0';
	 assert(len>2);
	 strcpy(chipID,(char*)tempBuffer);
	 if(SRBuffer[2]==0)
		 return 0;
	 else
		return -4;
 }

//���庯����smartcom string�汾
#ifdef USE_SMARTCOMSTRING
int GetChipID(Communicator& comm,SmartCom::string& chipID,int macNo)
 {
     if(NOT_CONNECT==comm.m_nCommtype)
		 return -2;
	 if(macNo>255||macNo<1)
		 return -3;
	 int cmd=0x01;
	 int dataLen=0;
	 BYTE tempBuffer[16];
	 BYTE SRBuffer[64];
	 int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	 //��������
	 int retCode,recLen;
	 CommProcess(comm,SRBuffer,64,packetLen,retCode,recLen);
	 if(recLen<0)
		 return -1;
	 sprintf((char*)tempBuffer,"%02X",*(SRBuffer+4));
	 tempBuffer[2]='\0';
	 chipID=(char*)tempBuffer;
	 if(SRBuffer[2]==0)
		 return 0;
	 else
		return -4;
 }
#endif

 /************************************************************************/
 /* ���A�����󿨣�����B����SIM�������Ƿ��п�                                                                     */
 /************************************************************************/
int IsCardReady(Communicator& comm,int& cardA,int& cardB,int macNo/* =255 */)
 {
     if(NOT_CONNECT==comm.m_nCommtype)
		 return -2;
	 if(macNo>255||macNo<1)
		 return -3;
	 int cmd=0x02;
	 int dataLen=0;
	 BYTE tempBuffer[16];
	 BYTE SRBuffer[64];
	 int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	 //��������
	 int retCode,recLen;
	 CommProcess(comm,SRBuffer,64,packetLen,retCode,recLen);
	 if(recLen<0)
		return -1;
	 if((SRBuffer[4]&(0x04))!=0)
		 cardA=1;
	 else
		 cardA=0;
	 if((SRBuffer[4]&(0x08))!=0)
		 cardB=1;
	 else
		 cardB=0;
	 if(SRBuffer[2]==0)
		 return 0;
	 else
		return -4;
 }

 /************************************************************************/
 /* A,B����λӦ��                                                                     */
 /************************************************************************/
int ResetCard(Communicator& comm,SmartCom::string& retCode,int card /* =1 */,int macNo/* =255 */)
 {
	 retCode="";
     if(NOT_CONNECT==comm.m_nCommtype)
		 return -2;
	 if(macNo>255||macNo<1)
		 return -3;
	 int cmd=0x03;
	 if(2==card)
		 cmd=0x05;

	 int dataLen=0;
	 BYTE tempBuffer[4];
	 BYTE SRBuffer[64];
	 int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	 //��������
	 int ret,recLen;
	 CommProcess(comm,SRBuffer,64,packetLen,ret,recLen);
	 if(recLen<0)
		return -1;
	 for(int i=0;i<SRBuffer[3];i++)
	 {
		 sprintf((char*)tempBuffer,"%02X",SRBuffer[i+4]);
		 tempBuffer[2]='\0';
		 retCode+=(char*)tempBuffer;
	 }
	 if(0x3b==SRBuffer[4]||0x3f==SRBuffer[4])
	    return 0;
	 else
		return -4;
 }

 /************************************************************************/
 /* A,B��Ƭ����-APDU                                                                     */
 /************************************************************************/
int CardApdu(Communicator& comm,const char* apdu,SmartCom::string& retCode,int card /* =1 */,int macNo/* =255 */)
 {
	 retCode="";
     if(NOT_CONNECT==comm.m_nCommtype)
	 {
		 return -2;
	 }
	 if(macNo>255||macNo<1)
	 {
		 return -3;
	 }
	 int cmd=0x04;
	 if(2==card)
		 cmd=0x06;
	 int len=strlen(apdu);
	 int dataLen=len/2;
	 BYTE tempBuffer[1024];
	 BYTE SRBuffer[1024];
	 assert(len<1000);
	 memcpy((char*)SRBuffer,apdu,len);
	 //ȥ���ַ����еĿո�
	 //int len=RemBlankSpace((char*)SRBuffer,strlen(apdu));
	 
     
	 //���ַ�����ʾ��ʮ������ֵת��Ϊ��ֵ
	 SVC_DSP_2_HEX(SRBuffer,tempBuffer,dataLen);
	 

	 int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	 //��������
	 int ret,recLen;
	 CommProcess(comm,SRBuffer,1024,packetLen,ret,recLen);
	 if(recLen<0)
		return -1;
	 //���retCode
	 for(int i=0;i<SRBuffer[3];i++)
	 {
		 sprintf((char*)tempBuffer,"%02X",SRBuffer[4+i]);
		 tempBuffer[2]='\0';
		 retCode+=(char*)tempBuffer;
	 }
	 return 0;
 }

 /************************************************************************/
 /* ��Ƭ�µ�                                                                     */
 /************************************************************************/
int ShutdownCard(Communicator& comm,int macNo/* =255 */)
 {
     if(NOT_CONNECT==comm.m_nCommtype)
		 return -2;
	 if(macNo>255||macNo<1)
		 return -3;
	 int cmd=0x07;
	 int dataLen=0;
	 BYTE tempBuffer[4];
	 BYTE SRBuffer[32];
	 int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	 //��������
	 int retCode,recLen;
	 CommProcess(comm,SRBuffer,32,packetLen,retCode,recLen);
	 if(recLen<0)
		return -1;
	 if(0==SRBuffer[2])
		 return 0;
	 else
	     return -4;
 }

 /************************************************************************/
 /* �޸Ŀ�ͨ�Ų�����                                                                     */
 /************************************************************************/
int ModifyCardBraudRate(Communicator& comm,int braudRate,int macNo/* =255 */)
 {
     if(NOT_CONNECT==comm.m_nCommtype)
		 return -2;
	 if(macNo>255||macNo<1)
		 return -3;
	 int cmd=0x08;
	 int dataLen=1;
	 BYTE tempBuffer[4];
	 BYTE SRBuffer[32];
	 int index=0;
	 switch(braudRate)
	 {
	 case 115200:
		 index=1;
		 break;
	 case 57600:
		 index=2;
		 break;
	 case 38400:
		 index=3;
		 break;
	 case 28800:
		 index=4;
		 break;
	 case 23040:
		 index=5;
		 break;
	 case 19200:
		 index=6;
		 break;
	 case 14400:
		 index=8;
		 break;
	 case 12800:
		 index=9;
		 break;
	 case 9600:
		 index=12;
		 break;
	 default:
		 return -4;
	 }
	 tempBuffer[0]=index;
	 int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	 //��������
	 int retCode,recLen;
	 CommProcess(comm,SRBuffer,32,packetLen,retCode,recLen);
	 if(recLen<0)
		return -1;
	 if(0==SRBuffer[2]&&index==SRBuffer[4])
		 return 0;
	 else
		 return -4;
 }

 /************************************************************************/
 /* ��ȡ����ͨ�Ų�����                                                                     */
 /************************************************************************/
int GetCardBraudRate(Communicator& comm,int& braudRate,int macNo/* =255 */)
 {
	 if(NOT_CONNECT==comm.m_nCommtype)
		 return -2;
	 if(macNo>255||macNo<1)
		 return -3;
	 int cmd=0x09;
	 int dataLen=0;
	 BYTE tempBuffer[4];
	 BYTE SRBuffer[32];
	 int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	 //��������
	 int retCode,recLen;
	 CommProcess(comm,SRBuffer,32,packetLen,retCode,recLen);
	 if(recLen<0)
		return -1;
	 switch(*(BYTE*)(SRBuffer+4))
	 {
	 case 1:
		 braudRate=115200;
		 break;
	 case 2:
		 braudRate=57600;
		 break;
	 case 3:
		 braudRate=38400;
		 break;
	 case 4:
		 braudRate=28800;
		 break;
	 case 5:
		 braudRate=23040;
		 break;
	 case 6:
		 braudRate=19200;
		 break;
	 case 8:
		 braudRate=14400;
		 break;
	 case 9:
		 braudRate=12800;
		 break;
	 case 12:
		 braudRate=9600;
		 break;
	 default:
		 return -4;
	 }
	 return 0;
 }

 /************************************************************************/
 /* �޸Ŀ�Ƭ��Դ                                                                     */
 /************************************************************************/
int ModifyCardPower(Communicator& comm,int power,int card/* =1 */,int macNo/* =255 */)
{
    if(NOT_CONNECT==comm.m_nCommtype)
		return -2;
	if(macNo>255||macNo<1)
		return -3;
	int cmd=0x0a;
	if(2==card)
		cmd=0x0b;
	int dataLen=1;
	BYTE tempBuffer[4];
	BYTE SRBuffer[32];
	tempBuffer[0]=power-1;
	int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	//��������
	int retCode,recLen;
	CommProcess(comm,SRBuffer,32,packetLen,retCode,recLen);
	if(recLen<0)
		return -1;
	if(SRBuffer[4]==power-1)
		return 0;
	else
		return -4;
}

/************************************************************************/
/* ����ִ��������APDU����                                                                     */
/************************************************************************/
int ExcuteMulAPDU(Communicator& comm,int cmdNum,int card/* =1 */,int macNo/* =255 */)
{
    if(NOT_CONNECT==comm.m_nCommtype)
		return -2;
	if(macNo>255||macNo<1)
		return -3;
	int cmd=0x0c;
	int dataLen=3;
    BYTE tempBuffer[4];
	BYTE SRBuffer[32];
	tempBuffer[0]=card;
	tempBuffer[1]=(cmdNum>>8);
	tempBuffer[2]=(cmdNum&0x00ff);
    int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	//��������
	int retCode,recLen;
	CommProcess(comm,SRBuffer,32,packetLen,retCode,recLen);
	if(recLen<0)
		return -1;
	if(0==SRBuffer[2])
		return 0;
	else 
		return -4;

}

/************************************************************************/
/* ������������ƽű��ļ�                                                                     */
/************************************************************************/
int GetScriptData(Communicator& comm,int offset,BYTE bytes,char* strData,int strDataLen,int macNo/* =255 */)
{
	if(NOT_CONNECT==comm.m_nCommtype)
		return -2;
	if(macNo>255||macNo<1)
		return -3;
	int cmd=0x0d;
	int dataLen=5;
    BYTE tempBuffer[8];
	BYTE SRBuffer[300];
	tempBuffer[0]=(BYTE)(offset>>24);
	tempBuffer[1]=(BYTE)((offset>>16)&0x000000ff);
	tempBuffer[2]=(BYTE)((offset>>8)&0x000000ff);
	tempBuffer[3]=(BYTE)(offset&0x000000ff);
    tempBuffer[4]=bytes;
    int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	//��������
	int retCode,recLen;
	CommProcess(comm,SRBuffer,300,packetLen,retCode,recLen);
	if(recLen<0)
		return -1;
	assert(strDataLen>SRBuffer[3]*3);
	char t[4];
	strData[0]='\0';
	for(int i=0;i<SRBuffer[3];i++)
	{
         sprintf(t,"%02X",SRBuffer[4+i]);
         strcat(strData,t);
		 if(i!=SRBuffer[3]-1)
			 strcat(strData," ");
	}
	if(SRBuffer[2]==0)
		return 0;
	else
		return -4;
}

//���庯����smartcom string�汾
#ifdef USE_SMARTCOMSTRING
int GetScriptData(Communicator& comm,int offset,unsigned char bytes,SmartCom::string& strData,int macNo)
{
    if(NOT_CONNECT==comm.m_nCommtype)
		return -2;
	if(macNo>255||macNo<1)
		return -3;
	int cmd=0x0d;
	int dataLen=5;
    BYTE tempBuffer[8];
	BYTE SRBuffer[300];
	tempBuffer[0]=(BYTE)(offset>>24);
	tempBuffer[1]=(BYTE)((offset>>16)&0x000000ff);
	tempBuffer[2]=(BYTE)((offset>>8)&0x000000ff);
	tempBuffer[3]=(BYTE)(offset&0x000000ff);
    tempBuffer[4]=bytes;
    int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	//��������
	int retCode,recLen;
	CommProcess(comm,SRBuffer,300,packetLen,retCode,recLen);
	if(recLen<0)
		return -1;
	char t[4];
	strData="";
	for(int i=0;i<SRBuffer[3];i++)
	{
		sprintf(t,"%02X",SRBuffer[4+i]);
		strData+=t;
		if(i!=SRBuffer[3]-1)
			    strData+=" ";
	}
	if(SRBuffer[2]==0)
	      return 0;
	else
		return -4;
}
#endif

/************************************************************************/
/* ���������ļ�                                                                     */
/************************************************************************/
int DownloadFile(Communicator& comm,int flag,const char* fileName,int macNo/* =255 */)
{
    if(NOT_CONNECT==comm.m_nCommtype)
		return -2;
	if(macNo>255||macNo<1)
		return -3;
	int cmd=0x0e;
	if(2==flag)
		cmd=0x0f;
	int dataLen=0;
    BYTE tempBuffer[150];
	BYTE SRBuffer[150];
	//ÿ������m�ֽ�
	const int m=128;
	//���ļ�
	FILE* aFile=fopen(fileName,"rb");
	if(NULL==aFile)
		return -5;
	int readNum=0;
	UINT filePos=0;
	while((readNum=fread(tempBuffer+4,1,m,aFile))!=0)
	{
		 dataLen=4+readNum;
		//������������������
		tempBuffer[0]=filePos>>24;//�ļ�ƫ�Ƶ�ַ������ֽ�
		tempBuffer[1]=(filePos>>16)&0x000000ff;//�ļ�ƫ�Ƶ�ַ�Ĵθ��ֽ�
		tempBuffer[2]=(filePos>>8)&0x000000ff;//�ļ�ƫ�Ƶ�ַ�ĵ��ֽ�
		tempBuffer[3]=filePos&0x000000ff;//�ļ�ƫ�Ƶ�ַ������ֽ�
		int	packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
		//��������
		int retCode,recLen;
		CommProcess(comm,SRBuffer,150,packetLen,retCode,recLen);
		if(recLen<0)
		{
			fclose(aFile);
            return -1;
		}
		
		if(0!=SRBuffer[2])
		{
			fclose(aFile);
            return -4;
		}
		filePos+=readNum;
	}
	
	fclose(aFile);
	return 0;
}

/************************************************************************/
/*��ѯִ��������APDU���                                                                      */
/************************************************************************/
int CheckBatchResult(Communicator& comm,SmartCom::string& retCode,int macNo/* =255 */)
{
	retCode="";
	if(NOT_CONNECT==comm.m_nCommtype)
		return -2;
	if(macNo>255||macNo<1)
		return -3;
	int cmd=0x10;
	int dataLen=0;
    BYTE tempBuffer[4];
	BYTE SRBuffer[64];
	int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	//��������
	int ret,recLen;
	CommProcess(comm,SRBuffer,64,packetLen,ret,recLen);
	if(recLen<0)
		return -1;
	if(SRBuffer[3]>=3)
	{
		for(int i=0;i<SRBuffer[3]-2;i++)
		{
            sprintf((char*)tempBuffer,"%02X",SRBuffer[4+i+2]);
			tempBuffer[2]='\0';
			retCode+=(char*)tempBuffer;
		}
		return (SRBuffer[4]<<8)+SRBuffer[5];
	}
	else
	{
		for(int i=0;i<SRBuffer[3];i++)
		{
            sprintf((char*)tempBuffer,"%02X",SRBuffer[4+i]);
			tempBuffer[2]='\0';
			retCode+=(char*)tempBuffer;
		}
	    return 0;
	}
}

/************************************************************************/
/* ��SST25VF016B�洢��������Ƭ����                                                                     */
/************************************************************************/
int ClearMem(Communicator& comm,int macNo/* =255 */)
{
    if(NOT_CONNECT==comm.m_nCommtype)
		return -2;
	if(macNo>255||macNo<1)
		return -3;
	int cmd=0x11;
	int dataLen=0;
    BYTE tempBuffer[4];
	BYTE SRBuffer[32];
	int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	//��������
	int retCode,recLen;
	CommProcess(comm,SRBuffer,32,packetLen,retCode,recLen);
	if(recLen<0)
		return -1;
	if(0==SRBuffer[2])
		return 0;
	else
		return -4;
}

 //����ͨ��
 void CommProcess(Communicator&comm,BYTE* buf,int bufLen,int nSendLen,int& sendRetCode,int& recLen)
 {
	 int j=0;
	 BYTE sendBuf[1024];
	 memcpy(sendBuf,buf,nSendLen);
	 if(comm.m_nCommtype==COMM_COM)
	 {
		 j=0;
         do 
         {
			 j++;
			 if(j>3)
				 break;
			 if(j>1)
				 Sleep(10);
			 sendRetCode=SendBytes(comm.comConn->comPort,sendBuf,nSendLen);
		     recLen=ReceiveBytes(comm.comConn->comPort,comm.comConn->waitSTX2Time,comm.comConn->normalWaitTime ,buf);
			 if(-2==recLen||-9==recLen)
			 {
				 int temp=0;
				 do 
				 {
					 temp=ReceiveBytes(comm.comConn->comPort,100,100,buf);
				 } while (temp!=-4&&temp!=-6);
			 }
         } while (recLen<0);

	 }
	 else if(comm.m_nCommtype==COMM_UDP)
	 {
		 
        j=0;//���ͨ�Ų��ɹ�����3��
	    do{
			 j++;
			 if(j>3)
				 break;
			 if(j>1)
				 Sleep(10);
             sendRetCode=SendUDPData(comm.udpConn->s,comm.udpConn->dstIP,comm.udpConn->dstPort, sendBuf,nSendLen);
			 recLen=RecvUDPData(comm.udpConn->s,comm.udpConn->waitSTX2Time,comm.udpConn->normalWaitTime ,buf,bufLen);
			 //������ݽ��ո�ʽ����������ջ���
			 if(recLen==-9||recLen==-10)
			 {
				 int temp=0;
				 do{
					 temp=RecvUDPData(comm.udpConn->s,10,10,buf,bufLen);
				 }while(temp!=-4);
			 }
		 }while(recLen<0);	 	 
		 return;
	 }
	 else if(comm.m_nCommtype==COMM_TCPCLIENT||comm.m_nCommtype==COMM_TCPSERVER)
	 {
		 //��socket����
		 
		 sendRetCode=SendData(comm.tcpClientConn->s,buf,nSendLen);
		 recLen=ReceiveData(comm.tcpClientConn->s,comm.tcpClientConn->waitSTX2Time,comm.tcpClientConn->normalWaitTime ,buf);
	 }
 }

