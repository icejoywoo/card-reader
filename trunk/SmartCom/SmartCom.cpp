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
#include "SmartComDefine.h"

void on_init();
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			on_init();
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

void on_init()
{
	StartWinSocketEnv();
}

//处理通信
 void CommProcess(Communicator&comm,BYTE* buf,int buflen,int nSendLen,int& sendRetCode,int& recLen);

/************************************************************************/
/* 初始化udp通信                                                                     */
/************************************************************************/
int InitUDPComm()
{
  if(0==StartWinSocketEnv())
	  return 0;
  else
	  return -1;
}

/**************************************************************************/
/*初始化与卡片读写器的串口通信方式.                                       */
/**************************************************************************/
int InitCOMComm()
{
	return 0;
}

/************************************************************************/
/* 关闭udp通信                                                                     */
/************************************************************************/
int CloseUDPComm()
{
	return 0;
}

/************************************************************************/
/* 关闭com通信                                                                     */
/************************************************************************/
SMARTCOM_API int CloseCOMComm()
{
	return 0;
}
/************************************************************************/
/* 获取一个udp通信器                                                                     */
/************************************************************************/
int GetOneUDPCommunicator(Communicator& aCommunicator,const char* dstIP,int port,
						  int waitForSTX2Time,int normalWaitTime)
{
	//先加锁再初始化,如果获取锁不成功一直等待。
	WaitForSingleObject(Connections::hUDPInitMutex,INFINITE);
	SCPrint(("%d:enter getcomm\r\n",GetCurrentThreadId()));
	bool flag=false;//如果目的ip对应的udpcommmanger已经存在，则为true
	int size=Connections::udpCommManagerVector.size();
	for(int i=0;i<size;i++)
	{
		if(strcmp(dstIP,Connections::udpCommManagerVector[i].dstIP)==0)
		{
			std::list<UdpConnection*>::iterator it;
			std::list<UdpConnection*>::iterator end=Connections::udpCommManagerVector[i].udpCommList.end();
			for(it=Connections::udpCommManagerVector[i].udpCommList.begin();it!=end;++it)
			{
				if(port==(*it)->dstPort)
				{
					(*it)->reference++;
					aCommunicator.csIndex=i;
					aCommunicator.udpConn=*it;
					aCommunicator.m_nCommtype=COMM_UDP;
					SCPrint(("%d:leave getcomm,reference=%d\r\n",GetCurrentThreadId(),(*it)->reference));
					ReleaseMutex(Connections::hUDPInitMutex);
			        return 0;
				}
			}
			flag=true;
			break;
		}
	}
   //初始化通信
	SOCKET s;
	int newPort=port;
	int temp=GetOneLocalSocket(&s,newPort);
	if(temp!=0)
	{
		SCPrint(("%d:getone local socket error\r\n",GetCurrentThreadId()));
		ReleaseMutex(Connections::hUDPInitMutex);
	    return SCERR_OPERROR;
	}  
	UdpConnection* con=new UdpConnection(newPort,(char*)dstIP,port,s,waitForSTX2Time,normalWaitTime);
	SCPrint(("%d:new udpconn:%08X\r\n",GetCurrentThreadId(),con));
	UdpCommManager ucm(dstIP);
    if(!flag)
	{
		ucm.udpCommList.push_back(con);
		Connections::udpCommManagerVector.push_back(ucm);
		
	}
	else
	{
		Connections::udpCommManagerVector[i].udpCommList.push_back(con);
	}
	con->reference++;
	aCommunicator.csIndex=i;
	aCommunicator.udpConn=con;
	aCommunicator.m_nCommtype=COMM_UDP;
	SCPrint(("%d:leave getcomm,reference=%d\r\n",GetCurrentThreadId(),con->reference));
	ReleaseMutex(Connections::hUDPInitMutex);
	return 0;
}

/************************************************************************/
/* 获取com通信器                                                                     */
/************************************************************************/
SMARTCOM_API int GetOneCOMCommunicator(Communicator& aCommunicator,int comPort,int rate,int waitForSTX2Time,int normalWaitTime)
{
	ComConnection* p=Connections::comConnArr;
	if(comPort>CONNECTIONS_NUM-1)
		return SCERR_OPERROR;
	EnterCriticalSection(&p[comPort].cs_initilize);
	if(p[comPort].reference>0) //已经初始化
	{
       p[comPort].reference++;
	   aCommunicator.m_nCommtype=COMM_COM;
	   aCommunicator.comConn=&p[comPort];
	   LeaveCriticalSection(&p[comPort].cs_initilize);
	   return 0;
	}
	//未初始化,初始化串口
	if(0!=IniCom(comPort,rate,waitForSTX2Time,normalWaitTime))
	{
		LeaveCriticalSection(&p[comPort].cs_initilize);
		return SCERR_OPERROR;
	}
    p[comPort].reference++;
	p[comPort].comPort=comPort;
	p[comPort].waitSTX2Time=waitForSTX2Time;
	p[comPort].normalWaitTime=normalWaitTime;
	LeaveCriticalSection(&p[comPort].cs_initilize);
	aCommunicator.m_nCommtype=COMM_COM;
	aCommunicator.comConn=&p[comPort];
	return 0;
}

/****************************************************************************
*功能：释放com通信器
****************************************************************************/
int ReleaseCOMCommunicator(Communicator* p)
{
   if(p->m_nCommtype==COMM_COM)
   {
	   p->m_nCommtype=NOT_CONNECT;
	   EnterCriticalSection(&p->comConn->cs_initilize);
	   if(p->comConn->reference<=0)
	   {
		   p->comConn->reference=0;
		   LeaveCriticalSection(&p->comConn->cs_initilize);
		   return SCERR_INVALID_COMM;
	   }
	   p->comConn->reference--;
	   if(p->comConn->reference==0)
	   {
		   if(0!=CloseCom(p->comConn->comPort))
		   {
		//	   TRACE("reference:%d\n",p->comConn->reference);
			   LeaveCriticalSection(&p->comConn->cs_initilize);
			   return SCERR_OPERROR;
		   }
	   }
	   LeaveCriticalSection(&p->comConn->cs_initilize);
	   delete p;
	   return SC_SUCCESS;
   }
   return SCERR_INVALID_COMM;
}

/****************************************************************************
*功能：释放UDP通信器
****************************************************************************/
int ReleaseUDPCommunicator(Communicator* p)
{
	WaitForSingleObject(Connections::hUDPInitMutex,INFINITE);
	SCPrint(("%d:enter releasecomm\r\n",GetCurrentThreadId()));
	if(p->m_nCommtype==COMM_UDP)
	{
		p->m_nCommtype=NOT_CONNECT;
		if(p->udpConn->reference<=0)
		{
			p->udpConn->reference=0;
			ReleaseMutex(Connections::hUDPInitMutex);
			return SCERR_INVALID_COMM;
		}
		p->udpConn->reference--;
		if(p->udpConn->reference==0)
		{
			CloseUDPSocket(p->udpConn->s);
			Connections::udpCommManagerVector[p->csIndex].udpCommList.remove(p->udpConn);
			delete p->udpConn;
			SCPrint(("%d:delete udpconn:%08X\r\n",GetCurrentThreadId(),p->udpConn));
		}	
		
		SCPrint(("%d:delete communicatror:%08X,reference:%d\r\n",GetCurrentThreadId(),p,p->udpConn->reference));
		memset(p,0,sizeof(Communicator));
		delete p;
		ReleaseMutex(Connections::hUDPInitMutex);	
		return 0;
	}
	SCPrint(("leave releasecomm\r\n"));
	ReleaseMutex(Connections::hUDPInitMutex);
	return SCERR_INVALID_COMM;
}
/************************************************************************/
/* 读取终端设备ID号和机号                                                                   
/************************************************************************/
int GetDevIDAndMacNo(Communicator& comm,char* devID,int devIDLen,int& macNo)
{
	if(NOT_CONNECT==comm.m_nCommtype)
		return SCERR_INVALID_COMM;
	int cmd=0xe1;
	int dataLen=0;
	BYTE tempBuffer[1];
	BYTE SRBuffer[64];
	int packetLen=PrepareBytes(255,cmd,tempBuffer,&dataLen,SRBuffer);

	//发送命令
	int retCode,recLen;
	CommProcess(comm,SRBuffer,64,packetLen,retCode,recLen);
	if(recLen<0)
		return SCERR_TIMEOUT;
	char t[8];
	int k=0;
	devID[0]='\0';
	assert(devIDLen>21);
	//将设备ID十六进制转换成字符串
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
		return SCERR_OPERROR;
}

//定义函数的smartcom string版本
#ifdef USE_SMARTCOMSTRING
int GetDevIDAndMacNo(Communicator& comm,SmartCom::string& devID,int& macNo)
{
	if(NOT_CONNECT==comm.m_nCommtype)
		return SCERR_INVALID_COMM;
	int cmd=0xe1;
	int dataLen=0;
	BYTE tempBuffer[1];
	BYTE SRBuffer[64];
	int packetLen=PrepareBytes(255,cmd,tempBuffer,&dataLen,SRBuffer);
	
	//发送命令
	int retCode,recLen;
	CommProcess(comm,SRBuffer,64,packetLen,retCode,recLen);
	if(recLen<0)
		return SCERR_TIMEOUT;
	char t[8];
	//将设备ID十六进制转换成字符串
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
		return SCERR_OPERROR;
}

#endif

/************************************************************************/
/* 通过终端设备ID号给终端设备设置机号                                             
/************************************************************************/
inline int RemBlankSpace(char* str,int len);

int SetMacNoByDevID(Communicator& comm,const char* devID,int macNo)
{
	if(NOT_CONNECT==comm.m_nCommtype)
		return SCERR_INVALID_COMM;
	if(macNo>255||macNo<1)
		 return SCERR_MACNO_OUTRANGE;
	//判断要设置的机号与原来机号是否一致
	SmartCom::string str;
	int tempMacNo=0;
    if(0!=GetDevIDAndMacNo(comm,str,tempMacNo))
		return SCERR_TIMEOUT;
	if(tempMacNo==macNo)
		return 0;
	int cmd=0xe3;
	int dataLen=8;
	BYTE tempBuffer[64];
	BYTE SRBuffer[64];
	assert(strlen(devID)<50);

	strcpy((char*)SRBuffer,devID);
	//去掉字符串中的空格
    RemBlankSpace((char*)SRBuffer,strlen((char*)SRBuffer));

	//将字符串表示的十六进制值转换为数值
	SVC_DSP_2_HEX(SRBuffer,tempBuffer,7);
	tempBuffer[7]=macNo;
    int packetLen=PrepareBytes(255,cmd,tempBuffer,&dataLen,SRBuffer);
	//发送命令
	int retCode,recLen;
	CommProcess(comm,SRBuffer,64,packetLen,retCode,recLen);
	if(recLen<0)
		return SCERR_TIMEOUT;
	if(SRBuffer[2]==0)
		return SC_SUCCESS;
	else
		return SCERR_OPERROR;
}
//去掉字符串中的所有空格,返回处理后的长度
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
   //重新拷贝到原来的位置
   memcpy(str,temp,j);
   str[j]='\0';
   return j;
}

 /************************************************************************/
 /* 读程序版本和终端类型                                                               
 /************************************************************************/
int GetAppVerAndDevType(Communicator& comm,char* appVersion,int Verlen,char* devType,int typeLen,
									 int MacNo)
 {
	 if(NOT_CONNECT==comm.m_nCommtype)
		 return SCERR_INVALID_COMM;
	 if(MacNo>255||MacNo<1)
		 return SCERR_MACNO_OUTRANGE;
	 assert(Verlen>30);
	 assert(typeLen>40);
	 int cmd=0xe4;
	 int dataLen=0;
	 BYTE tempBuffer[16];
	 BYTE SRBuffer[64];
	 int packetLen=PrepareBytes(MacNo,cmd,tempBuffer,&dataLen,SRBuffer);
	 //发送命令
	 int retCode,recLen;
	 CommProcess(comm,SRBuffer,64,packetLen,retCode,recLen);
	 if(recLen<0)
		return SCERR_TIMEOUT;
     char year[8],month[8],day[8],hour[8];
	 int j=0;
	 appVersion[0]='\0';
	 sprintf(year,"%u",*(SRBuffer+4));
     sprintf(month,"%u",*(SRBuffer+5));
	 sprintf(day,"%u",*(SRBuffer+6));
	 sprintf(hour,"%u",*(SRBuffer+7));

	 strcat(appVersion,year);
	 strcat(appVersion,"年");
	 strcat(appVersion,month);
	 strcat(appVersion,"月");
	 strcat(appVersion,day);
	 strcat(appVersion,"日");
	 strcat(appVersion,hour);
	 strcat(appVersion,"时");

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
		 strcat(devType,"(磁卡读写器)");
		 break;
	 case 2:
		 strcat(devType,"(接触式同步卡，存储卡和加密卡)");
		 break;
	 case 3:
		 strcat(devType,"(接触式CPU卡读写器)");
		 break;
	 case 4:
		 strcat(devType,"(非接触式存储卡读写器)");
		 break;
	 case 5:
		 strcat(devType,"(非接触式CPU卡读写器)");
		 break;
	 case 6:
		 strcat(devType,"(双界面卡读写器)");
		 break;
	 }

	 if(SRBuffer[2]==0)
		 return SC_SUCCESS;
	 else
		return SCERR_OPERROR;
 }

 //定义函数的smartcom string版本
#ifdef USE_SMARTCOMSTRING
int GetAppVerAndDevType(Communicator& comm,SmartCom::string& appVersion,SmartCom::string& devType,
									 int MacNo)
{
	if(NOT_CONNECT==comm.m_nCommtype)
		return SCERR_INVALID_COMM;
	if(MacNo>255||MacNo<1)
		return SCERR_MACNO_OUTRANGE;
	int cmd=0xe4;
	int dataLen=0;
	BYTE tempBuffer[16];
	BYTE SRBuffer[64];
	int packetLen=PrepareBytes(MacNo,cmd,tempBuffer,&dataLen,SRBuffer);
	appVersion="";
	devType="";
	//发送命令
	int retCode,recLen;
	CommProcess(comm,SRBuffer,64,packetLen,retCode,recLen);
	if(recLen<0)
		return SCERR_TIMEOUT;
	if(SRBuffer[2]!=0)
		return SCERR_OPERROR;
	char timestr[32];
	int year,mon,day,hour;
	year=*(SRBuffer+6)>>4;
	year=year*10+(*(SRBuffer+6)&0xf);
	mon=*(SRBuffer+7)>>4;
	mon=mon*10+(*(SRBuffer+7)&0xf);
	day=*(SRBuffer+8)>>4;
	day=day*10+(*(SRBuffer+8)&0xf);
	hour=*(SRBuffer+9)>>4;
	hour=hour*10+(*(SRBuffer+9)&0xf);
	sprintf(timestr,"%d年%d月%d日%d时",year,mon,day,hour);
    appVersion=timestr;
	char t[8];
	sprintf(t,"%02X",*(SRBuffer+4));
	devType+=t;
	sprintf(t,"%02X",*(SRBuffer+5));
	devType+=t;
	switch(*(BYTE*)(SRBuffer+5))
	{
	case 1:
	    devType+="(磁卡读写器)";
		break;
	case 2:
		devType+="(接触式同步卡，存储卡和加密卡)";
		break;
	case 3:
		devType+="(接触式CPU卡读写器)";
		break;
	case 4:
		devType+="(非接触式存储卡读写器)";
		break;
	case 5:
		devType+="(非接触式CPU卡读写器)";
		break;
	case 6:
		devType+="(双界面卡读写器)";
		break;
	}
		
	return 0;	
}
#endif

 /************************************************************************/
 /* 复位终端设备                                                                     */
 /************************************************************************/
int ResetDev(Communicator& comm,int macNo /*=255*/)
 {
	 if(NOT_CONNECT==comm.m_nCommtype)
		 return SCERR_INVALID_COMM;
	 if(macNo>255||macNo<1)
		 return SCERR_MACNO_OUTRANGE;
	 int cmd=0xe8;
	 int dataLen=0;
	 BYTE tempBuffer[16];
	 BYTE SRBuffer[64];
	 int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	 //发送命令
	 int retCode=0;
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
 /* 获取读卡接口芯片ID号                                                                     */
 /************************************************************************/
int GetChipID(Communicator& comm,char* chipID,int len,int macNo/* =255 */)
 {
     if(NOT_CONNECT==comm.m_nCommtype)
		 return SCERR_INVALID_COMM;
	 if(macNo>255||macNo<1)
		 return SCERR_MACNO_OUTRANGE;
	 int cmd=0x01;
	 int dataLen=0;
	 BYTE tempBuffer[16];
	 BYTE SRBuffer[64];
	 int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	 //发送命令
	 int retCode,recLen;
	 CommProcess(comm,SRBuffer,64,packetLen,retCode,recLen);
	 if(recLen<0)
		return SCERR_TIMEOUT;
	 sprintf((char*)tempBuffer,"%02X",*(SRBuffer+4));
	 tempBuffer[2]='\0';
	 assert(len>2);
	 strcpy(chipID,(char*)tempBuffer);
	 if(SRBuffer[2]==0)
		 return 0;
	 else
		return SCERR_OPERROR;
 }

//定义函数的smartcom string版本
#ifdef USE_SMARTCOMSTRING
int GetChipID(Communicator& comm,SmartCom::string& chipID,int macNo)
 {
     if(NOT_CONNECT==comm.m_nCommtype)
		 return SCERR_INVALID_COMM;
	 if(macNo>255||macNo<1)
		 return SCERR_MACNO_OUTRANGE;
	 int cmd=0x01;
	 int dataLen=0;
	 BYTE tempBuffer[16];
	 BYTE SRBuffer[64];
	 int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	 //发送命令
	 int retCode,recLen;
	 CommProcess(comm,SRBuffer,64,packetLen,retCode,recLen);
	 if(recLen<0)
		 return SCERR_TIMEOUT;
	 sprintf((char*)tempBuffer,"%02X",*(SRBuffer+4));
	 tempBuffer[2]='\0';
	 chipID=(char*)tempBuffer;
	 if(SRBuffer[2]==0)
		 return 0;
	 else
		return SCERR_OPERROR;
 }
#endif

 /************************************************************************/
 /* 检测A卡（大卡）座与B卡（SIM卡）座是否有卡                                                                     */
 /************************************************************************/
int IsCardReady(Communicator& comm,int& cardA,int& cardB,int macNo/* =255 */)
 {
     if(NOT_CONNECT==comm.m_nCommtype)
		 return SCERR_INVALID_COMM;
	 if(macNo>255||macNo<1)
		 return SCERR_MACNO_OUTRANGE;
	 int cmd=0x02;
	 int dataLen=0;
	 BYTE tempBuffer[16];
	 BYTE SRBuffer[64];
	 int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	 //发送命令
	 int retCode,recLen;
	 CommProcess(comm,SRBuffer,64,packetLen,retCode,recLen);
	 if(recLen<0)
		return SCERR_TIMEOUT;
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
		return SCERR_OPERROR;
 }

 /************************************************************************/
 /* A,B卡复位应答                                                                     */
 /************************************************************************/
int ResetCard(Communicator& comm,SmartCom::string& retCode,int card /* =1 */,int macNo/* =255 */)
 {
	 retCode="";
     if(NOT_CONNECT==comm.m_nCommtype)
		 return SCERR_INVALID_COMM;
	 if(macNo>255||macNo<1)
		 return SCERR_MACNO_OUTRANGE;
	 int cmd=0x03;
	 if(2==card)
		 cmd=0x05;

	 int dataLen=0;
	 BYTE tempBuffer[4];
	 BYTE SRBuffer[64];
	 int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	 //发送命令
	 int ret,recLen;
	 CommProcess(comm,SRBuffer,64,packetLen,ret,recLen);
	 if(recLen<0)
		return SCERR_TIMEOUT;
	 for(int i=0;i<SRBuffer[3];i++)
	 {
		 sprintf((char*)tempBuffer,"%02X",SRBuffer[i+4]);
		 tempBuffer[2]='\0';
		 retCode+=(char*)tempBuffer;
	 }
	 if(0x3b==SRBuffer[4]||0x3f==SRBuffer[4])
	    return 0;
	 else
		return SCERR_OPERROR;
 }

 /************************************************************************/
 /* A,B卡片操作-APDU                                                                     */
 /************************************************************************/
int CardApdu(Communicator& comm,const char* apdu,SmartCom::string& retCode,int card /* =1 */,int macNo/* =255 */)
 {
	 retCode="";
     if(NOT_CONNECT==comm.m_nCommtype)
	 {
		 return SCERR_INVALID_COMM;
	 }
	 if(macNo>255||macNo<1)
	 {
		 return SCERR_MACNO_OUTRANGE;
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
	 //去掉字符串中的空格
	 //int len=RemBlankSpace((char*)SRBuffer,strlen(apdu));
	 
     
	 //将字符串表示的十六进制值转换为数值
	 SVC_DSP_2_HEX(SRBuffer,tempBuffer,dataLen);
	 

	 int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	 //发送命令
	 int ret,recLen;
	 CommProcess(comm,SRBuffer,1024,packetLen,ret,recLen);
	 if(recLen<0)
		return SCERR_TIMEOUT;
	 //填充retCode
	 for(int i=0;i<SRBuffer[3];i++)
	 {
		 sprintf((char*)tempBuffer,"%02X",SRBuffer[4+i]);
		 tempBuffer[2]='\0';
		 retCode+=(char*)tempBuffer;
	 }
	 return 0;
 }

 /************************************************************************/
 /* 卡片下电                                                                     */
 /************************************************************************/
int ShutdownCard(Communicator& comm,int macNo/* =255 */)
 {
     if(NOT_CONNECT==comm.m_nCommtype)
		 return SCERR_INVALID_COMM;
	 if(macNo>255||macNo<1)
		 return SCERR_MACNO_OUTRANGE;
	 int cmd=0x07;
	 int dataLen=0;
	 BYTE tempBuffer[4];
	 BYTE SRBuffer[32];
	 int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	 //发送命令
	 int retCode,recLen;
	 CommProcess(comm,SRBuffer,32,packetLen,retCode,recLen);
	 if(recLen<0)
		return SCERR_TIMEOUT;
	 if(0==SRBuffer[2])
		 return 0;
	 else
	     return SCERR_OPERROR;
 }

 /************************************************************************/
 /* 修改卡通信波特率                                                                     */
 /************************************************************************/
int ModifyCardBraudRate(Communicator& comm,int braudRate,int macNo/* =255 */)
 {
     if(NOT_CONNECT==comm.m_nCommtype)
		 return SCERR_INVALID_COMM;
	 if(macNo>255||macNo<1)
		 return SCERR_MACNO_OUTRANGE;
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
		 return SCERR_INVALID_DATA;
	 }
	 tempBuffer[0]=index;
	 int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	 //发送命令
	 int retCode,recLen;
	 CommProcess(comm,SRBuffer,32,packetLen,retCode,recLen);
	 if(recLen<0)
		return SCERR_TIMEOUT;
	 if(0==SRBuffer[2]&&index==SRBuffer[4])
		 return 0;
	 else
		 return SCERR_OPERROR;
 }

 /************************************************************************/
 /* 获取卡的通信波特率                                                                     */
 /************************************************************************/
int GetCardBraudRate(Communicator& comm,int& braudRate,int macNo/* =255 */)
 {
	 if(NOT_CONNECT==comm.m_nCommtype)
		 return SCERR_INVALID_COMM;
	 if(macNo>255||macNo<1)
		 return SCERR_MACNO_OUTRANGE;
	 int cmd=0x09;
	 int dataLen=0;
	 BYTE tempBuffer[4];
	 BYTE SRBuffer[32];
	 int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	 //发送命令
	 int retCode,recLen;
	 CommProcess(comm,SRBuffer,32,packetLen,retCode,recLen);
	 if(recLen<0)
		return SCERR_TIMEOUT;
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
		 return SCERR_INVALID_DATA;
	 }
	 return 0;
 }

 /************************************************************************/
 /* 修改卡片电源                                                                     */
 /************************************************************************/
int ModifyCardPower(Communicator& comm,int power,int card/* =1 */,int macNo/* =255 */)
{
    if(NOT_CONNECT==comm.m_nCommtype)
		return SCERR_INVALID_COMM;
	if(macNo>255||macNo<1)
		return SCERR_MACNO_OUTRANGE;
	int cmd=0x0a;
	if(2==card)
		cmd=0x0b;
	int dataLen=1;
	BYTE tempBuffer[4];
	BYTE SRBuffer[32];
	tempBuffer[0]=power-1;
	int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	//发送命令
	int retCode,recLen;
	CommProcess(comm,SRBuffer,32,packetLen,retCode,recLen);
	if(recLen<0)
		return SCERR_TIMEOUT;
	if(SRBuffer[4]==power-1)
		return 0;
	else
		return SCERR_OPERROR;
}

/************************************************************************/
/* 发送执行批处理APDU命令                                                                     */
/************************************************************************/
int ExcuteMulAPDU(Communicator& comm,int cmdNum,int card/* =1 */,int macNo/* =255 */)
{
    if(NOT_CONNECT==comm.m_nCommtype)
		return SCERR_INVALID_COMM;
	if(macNo>255||macNo<1)
		return SCERR_MACNO_OUTRANGE;
/*	int ret=DisableAutoAnswer(comm,macNo);
	if(ret<0)
		return ret;*/
	int cmd=0x0c;
	int dataLen=3;
    BYTE tempBuffer[4];
	BYTE SRBuffer[32];
	tempBuffer[0]=card;
	tempBuffer[1]=(cmdNum>>8);
	tempBuffer[2]=(cmdNum&0x00ff);
    int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	//发送命令
	int retCode,recLen;
	CommProcess(comm,SRBuffer,32,packetLen,retCode,recLen);
	if(recLen<0)
		return SCERR_TIMEOUT;
	if(0==SRBuffer[2])
		return 0;
	else 
		return SCERR_OPERROR;

}

/************************************************************************/
/* 发送执行批处理APDU命令                                                                     */
/************************************************************************/
int ExcuteMulAPDUAsyn(Communicator& comm,int cmdNum,int card=1,int macNo=255);
int ExcuteMulAPDUAsyn(Communicator& comm,int cmdNum,int card/* =1 */,int macNo/* =255 */)
{
    if(NOT_CONNECT==comm.m_nCommtype)
		return SCERR_INVALID_COMM;
	if(macNo>255||macNo<1)
		return SCERR_MACNO_OUTRANGE;
	int cmd=0x0c;
	int dataLen=3;
    BYTE tempBuffer[4];
	BYTE SRBuffer[32];
	tempBuffer[0]=card;
	tempBuffer[1]=(cmdNum>>8);
	tempBuffer[2]=(cmdNum&0x00ff);
    int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	//发送命令
	int retCode,recLen;
	CommProcess(comm,SRBuffer,32,packetLen,retCode,recLen);
	if(recLen<0)
		return SCERR_TIMEOUT;
	if(0==SRBuffer[2])
		return 0;
	else 
		return SCERR_OPERROR;
	
}
/*************************************************************************/
/*发送批处理命令，等待批处理完成时返回                                   */
/*************************************************************************/
int ExcuteMulAPDUSyn(Communicator& comm,int cmdNum,int card/* =1 */,int macNo/* =255 */)
{
/*	int ret=EnableAutoAnswer(comm,macNo);
	if(ret<0)
		return ret;*/
    int ret=ExcuteMulAPDUAsyn(comm,cmdNum,card,macNo);
	if(ret<0)
		return ret;
	BYTE buf[64];
	int recLen=0;
	//等待批处理返回
	if(comm.m_nCommtype==COMM_COM)
	{
        recLen=ReceiveBytes(comm.comConn->comPort,INFINITE/2,0 ,buf);
	}
	else if(comm.m_nCommtype==COMM_UDP)
	{
        recLen=RecvUDPData(comm.udpConn->s,INFINITE/2,0 ,buf,64);
	}
	else
		return SCERR_INVALID_COMM;
	return 0;
}

/************************************************************************/
/* 读批处理二进制脚本文件                                                                     */
/************************************************************************/
int GetScriptData(Communicator& comm,int offset,BYTE bytes,char* strData,int strDataLen,int macNo/* =255 */)
{
	if(NOT_CONNECT==comm.m_nCommtype)
		return SCERR_INVALID_COMM;
	if(macNo>255||macNo<1)
		return SCERR_MACNO_OUTRANGE;
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
	//发送命令
	int retCode,recLen;
	CommProcess(comm,SRBuffer,300,packetLen,retCode,recLen);
	if(recLen<0)
		return SCERR_TIMEOUT;
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
		return SCERR_OPERROR;
}

//定义函数的smartcom string版本
#ifdef USE_SMARTCOMSTRING
int GetScriptData(Communicator& comm,int offset,unsigned char bytes,SmartCom::string& strData,int macNo)
{
    if(NOT_CONNECT==comm.m_nCommtype)
		return SCERR_INVALID_COMM;
	if(macNo>255||macNo<1)
		return SCERR_MACNO_OUTRANGE;
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
	//发送命令
	int retCode,recLen;
	CommProcess(comm,SRBuffer,300,packetLen,retCode,recLen);
	if(recLen<0)
		return SCERR_TIMEOUT;
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
		return SCERR_OPERROR;
}
#endif


/************************************************************************/
/* 下载命令文件                                                                     */
/************************************************************************/
int DownloadFile(Communicator& comm,int flag,const char* fileName,int macNo/* =255 */)
{
    if(NOT_CONNECT==comm.m_nCommtype)
		return SCERR_INVALID_COMM;
	if(macNo>255||macNo<1)
		return SCERR_MACNO_OUTRANGE;
	int cmd=0x0e;
	if(2==flag)
		cmd=0x0f;
	int dataLen=0;
    BYTE tempBuffer[150];
	BYTE SRBuffer[150];
	//每次下载m字节
	const int m=128;
	//打开文件
	//FILE* aFile=fopen(fileName,"rb");
	HANDLE hFile=CreateFileA(fileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,0);
	//if(NULL==aFile)
		//return -5;
	if(INVALID_HANDLE_VALUE==hFile)
		return SCERR_OPENFILE_FAIL;
	unsigned long readNum=0;
	UINT filePos=0;
	BOOL bReturn=FALSE;
	OVERLAPPED olp;
	olp.Offset=0;
	olp.OffsetHigh=0;
	olp.hEvent=0;
	//while((readNum=fread(tempBuffer+4,1,m,aFile))!=0)
	while(true)
	{
		bReturn=ReadFile(hFile,tempBuffer+4,m,&readNum,&olp);
		if(readNum==0)
			break;
		if(bReturn==FALSE)
			return SCERR_OPERROR;
		dataLen=4+readNum;
		//填充下载命令的数据项
		tempBuffer[0]=filePos>>24;//文件偏移地址的最高字节
		tempBuffer[1]=(filePos>>16)&0x000000ff;//文件偏移地址的次高字节
		tempBuffer[2]=(filePos>>8)&0x000000ff;//文件偏移地址的低字节
		tempBuffer[3]=filePos&0x000000ff;//文件偏移地址的最低字节
		int	packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
		//发送命令
		int retCode,recLen;
		CommProcess(comm,SRBuffer,150,packetLen,retCode,recLen);
		if(recLen<0)
		{
			//fclose(aFile);
			CloseHandle(hFile);
            return SCERR_TIMEOUT;
		}
		
		if(0!=SRBuffer[2])
		{
			//fclose(aFile);
			CloseHandle(hFile);
            return SCERR_OPERROR;
		}
		filePos+=readNum;
		olp.Offset+=readNum;
	}
	
	//fclose(aFile);
	CloseHandle(hFile);
	return 0;
}

/***********************************************************************
* 下载文件，该函数效率比DownloadFile要高,但目前仅支持com通信方式
***********************************************************************/
#include <winioctl.h>
#define IOCTL_WRITE CTL_CODE(FILE_DEVICE_UNKNOWN,0x800,METHOD_BUFFERED,FILE_ANY_ACCESS)

extern HANDLE hCommDev[256];
int DownloadFileK(Communicator& comm,int flag,const char* fileName,int macNo/* =255 */)
{
	if(NOT_CONNECT==comm.m_nCommtype)
		return SCERR_INVALID_COMM;
	if(macNo>255||macNo<1)
		return SCERR_MACNO_OUTRANGE;
	SmartCom::string str="\\\\.\\";
	str+=DEVICE_NAME;
	HANDLE hDevice=CreateFile(str.c_str(),GENERIC_READ|GENERIC_WRITE,
		0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	if(hDevice==INVALID_HANDLE_VALUE)
	{
		return SCERR_DRIVER_NOTINSTALL;
	}
    HANDLE hFile=CreateFile(fileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	if(hFile==INVALID_HANDLE_VALUE)
	{
         return SCERR_OPENFILE_FAIL;
	}
	//将com句柄和下载文件句柄传递给驱动程序,数据结构为文件句柄，com句柄，标志，机号
	ULONG len=0;
	int retcode=0;
	KIOCTRL kctrl;
	kctrl.hFile=hFile;
	kctrl.hDevice=hCommDev[comm.comConn->comPort];
	kctrl.flag=flag;
	kctrl.macNo=macNo;
    kctrl.timeout=comm.comConn->normalWaitTime+comm.comConn->waitSTX2Time;
	BOOL bRet=DeviceIoControl(hDevice,IOCTL_WRITE,&kctrl,sizeof(KIOCTRL),&retcode,sizeof(int),&len,0);
	CloseHandle(hFile);
	CloseHandle(hDevice);
	return retcode;
}   

/***********************************************************************
* 该函数可以一次执行多条apdu命令，该函数效率比cardapdu要高,但目前仅支持com通信方式
***********************************************************************/  
#define IOCTL_APDU  CTL_CODE(FILE_DEVICE_UNKNOWN,0X801,METHOD_NEITHER,FILE_ANY_ACCESS)
 
int CardApduK(Communicator& comm,const char* apdu,SmartCom::string& retCode,int card/* =1 */,int macNo/* =255 */)
{
	if(NOT_CONNECT==comm.m_nCommtype)
		return SCERR_INVALID_COMM;
	if(macNo>255||macNo<1)
		return SCERR_MACNO_OUTRANGE;
	SmartCom::string str="\\\\.\\";
	str+=DEVICE_NAME;
	HANDLE hDevice=CreateFile(str.c_str(),GENERIC_READ|GENERIC_WRITE,
		0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	if(hDevice==INVALID_HANDLE_VALUE)
	{
		return SCERR_DRIVER_NOTINSTALL;
	}
	KIOCTRL_APDU kioapdu;
	kioapdu.apduStr=(BYTE*)apdu;
	kioapdu.card=card;
	kioapdu.kioctrl.hDevice=hCommDev[comm.comConn->comPort];;
	kioapdu.kioctrl.macNo=macNo;
	kioapdu.kioctrl.timeout=comm.comConn->normalWaitTime+comm.comConn->waitSTX2Time;
	ULONG len=0;
	int status;
	char outbuf[10];
    DeviceIoControl(hDevice,IOCTL_APDU,&kioapdu,sizeof(KIOCTRL_APDU),outbuf,10,&len,0);
	CloseHandle(hDevice);
	memcpy(&status,outbuf,sizeof(int));
	retCode=(outbuf+sizeof(int));
	return status;
}                       

/************************************************************************/
/* 下载命令文件                                                                     */
/************************************************************************/
int DownloadBin(Communicator& comm,int flag,const char* bin,unsigned int len,int macNo)
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
	//每次下载m字节
	const int m=128;
	unsigned long readNum=0;
	UINT filePos=0;
	unsigned int i=0;
	bool loop=true;
	while(loop)
	{
		if(i+m<len)
		{
           memcpy(tempBuffer+4,bin+i,m);
		   i+=m;
		   readNum=m;
		}
		else
		{
			int left=len-i;
			if(0==left)
				break;
			memcpy(tempBuffer+4,bin+i,left);
			loop=false;
			readNum=left;
		}
		dataLen=4+readNum;
		//填充下载命令的数据项
		tempBuffer[0]=filePos>>24;//文件偏移地址的最高字节
		tempBuffer[1]=(filePos>>16)&0x000000ff;//文件偏移地址的次高字节
		tempBuffer[2]=(filePos>>8)&0x000000ff;//文件偏移地址的低字节
		tempBuffer[3]=filePos&0x000000ff;//文件偏移地址的最低字节
		int	packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
		//发送命令
		int retCode,recLen;
		CommProcess(comm,SRBuffer,150,packetLen,retCode,recLen);
		if(recLen<0)
		{
            return -1;
		}
		
		if(0!=SRBuffer[2])
		{
            return -4;
		}
		filePos+=readNum;
	}
	return 0;
}

/************************************************************************/
/*查询执行批处理APDU结果                                                                      */
/************************************************************************/
int CheckBatchResult(Communicator& comm,SmartCom::string& retCode,int macNo/* =255 */)
{
	retCode="";
	if(NOT_CONNECT==comm.m_nCommtype)
		return SCERR_INVALID_COMM;
	if(macNo>255||macNo<1)
		return SCERR_MACNO_OUTRANGE;
	int cmd=0x10;
	int dataLen=0;
    BYTE tempBuffer[4];
	BYTE SRBuffer[64];
	int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	//发送命令
	int ret,recLen;
	CommProcess(comm,SRBuffer,64,packetLen,ret,recLen);
	if(recLen<0)
		return SCERR_TIMEOUT;
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
/* 对SST25VF016B存储器进行整片擦除                                                                     */
/************************************************************************/
int ClearMem(Communicator& comm,int macNo/* =255 */)
{
    if(NOT_CONNECT==comm.m_nCommtype)
		return SCERR_INVALID_COMM;
	if(macNo>255||macNo<1)
		return SCERR_MACNO_OUTRANGE;
	int cmd=0x11;
	int dataLen=0;
    BYTE tempBuffer[4];
	BYTE SRBuffer[32];
	int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	//发送命令
	int retCode,recLen;
	CommProcess(comm,SRBuffer,32,packetLen,retCode,recLen);
	if(recLen<0)
		return SCERR_TIMEOUT;
	if(0==SRBuffer[2])
		return 0;
	else
		return SCERR_OPERROR;
}

 //处理通信
 void CommProcess(Communicator&comm,BYTE* buf,int bufLen,int nSendLen,int& sendRetCode,int& recLen)
 {
	 int j=0;
	 BYTE sendBuf[1024];
	 memcpy(sendBuf,buf,nSendLen);
	 if(comm.m_nCommtype==COMM_UDP)
	 {
		 
		 j=0;//如果通信不成功，试3次
		 int index=comm.csIndex;
		 do{
			 j++;
			 if(j>3)
				 break;
			 while(true)   //控制在同一时间向同一工作站发送数据的线程不大于8个
			 {
				 EnterCriticalSection(&Connections::udpCommManagerVector[index].cs_workstation);			 
				 if(Connections::udpCommManagerVector[index].sendingThreadNum+1<=8)
				 {		 
					 Connections::udpCommManagerVector[index].sendingThreadNum++;
					 LeaveCriticalSection(&Connections::udpCommManagerVector[index].cs_workstation);
					 break;
				 }
				 LeaveCriticalSection(&Connections::udpCommManagerVector[index].cs_workstation);
				 Sleep(5);
			 }
			 EnterCriticalSection(&comm.udpConn->cs_rw);
             sendRetCode=SendUDPData(comm.udpConn->s,comm.udpConn->dstIP,comm.udpConn->dstPort, sendBuf,nSendLen);
			 Sleep(1);
			 recLen=RecvUDPData(comm.udpConn->s,comm.udpConn->waitSTX2Time,comm.udpConn->normalWaitTime ,buf,bufLen);
			 LeaveCriticalSection(&comm.udpConn->cs_rw);

			 EnterCriticalSection(&Connections::udpCommManagerVector[index].cs_workstation);
			 Connections::udpCommManagerVector[index].sendingThreadNum--;
			 LeaveCriticalSection(&Connections::udpCommManagerVector[index].cs_workstation);
			 //如果数据接收格式错误，清除接收缓冲
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
		 //对socket加锁
		 
		 sendRetCode=SendData(comm.tcpClientConn->s,buf,nSendLen);
		 recLen=ReceiveData(comm.tcpClientConn->s,comm.tcpClientConn->waitSTX2Time,comm.tcpClientConn->normalWaitTime ,buf);
	 }
	 else if(comm.m_nCommtype==COMM_COM)
	 {
		 j=0;
         do 
         {
			 j++;
			 if(j>3)
				 break;
			 EnterCriticalSection(&comm.comConn->cs_rw);
			 sendRetCode=SendBytes(comm.comConn->comPort,sendBuf,nSendLen);
			 Sleep(1);
		     recLen=ReceiveBytes(comm.comConn->comPort,comm.comConn->waitSTX2Time,comm.comConn->normalWaitTime ,buf);
			 if(-2==recLen||-9==recLen)
			 {
				 int temp=0;
				 do 
				 {
					 temp=ReceiveBytes(comm.comConn->comPort,100,100,buf);
				 } while (temp!=-4&&temp!=-6);
			 }
			 LeaveCriticalSection(&comm.comConn->cs_rw);

         } while (recLen<0);

	 }
	 
 }

 //禁止多条APDU批处理完成后自动给回答
 int DisableAutoAnswer(Communicator& comm,int macNo/*=255*/)
 {
	 if(NOT_CONNECT==comm.m_nCommtype)
		 return SCERR_INVALID_COMM;
	 if(macNo>255||macNo<1)
		 return SCERR_MACNO_OUTRANGE;
	 int cmd=0x13;
	 int dataLen=0;
	 BYTE tempBuffer[4];
	 BYTE SRBuffer[32];
	 int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	 //发送命令
	 int retCode,recLen;
	 CommProcess(comm,SRBuffer,32,packetLen,retCode,recLen);
	 if(recLen<0)
		 return SCERR_TIMEOUT;
	 if(0==SRBuffer[2])
		 return 0;
	 else
		 return SCERR_OPERROR;
 }
 
 
 //设置多条APDU批处理完成后自动给回答
 int EnableAutoAnswer(Communicator& comm,int macNo /*=255*/)
 {
     if(NOT_CONNECT==comm.m_nCommtype)
		 return SCERR_INVALID_COMM;
	 if(macNo>255||macNo<1)
		 return SCERR_MACNO_OUTRANGE;
	 int cmd=0x12;
	 int dataLen=0;
	 BYTE tempBuffer[4];
	 BYTE SRBuffer[32];
	 int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	 //发送命令
	 int retCode,recLen;
	 CommProcess(comm,SRBuffer,32,packetLen,retCode,recLen);
	 if(recLen<0)
		 return SCERR_TIMEOUT;
	 if(0==SRBuffer[2])
		 return 0;
	 else
		 return SCERR_OPERROR;
 }
 
 //设置发送数据时间间隔
 int SetSendInterval(Communicator& comm,BYTE interval,int macNo /*=255*/)
 {
     if(NOT_CONNECT==comm.m_nCommtype)
		 return SCERR_INVALID_COMM;
	 if(macNo>255||macNo<1)
		 return SCERR_MACNO_OUTRANGE;
	 int cmd=0xe8;
	 int dataLen=1;
	 BYTE tempBuffer[4];
	 BYTE SRBuffer[32];
	 tempBuffer[0]=interval;
	 int packetLen=PrepareBytes(macNo,cmd,tempBuffer,&dataLen,SRBuffer);
	 //发送命令
	 int retCode,recLen;
	 CommProcess(comm,SRBuffer,32,packetLen,retCode,recLen);
	 if(recLen<0)
		 return SCERR_TIMEOUT;
	 if(0==SRBuffer[2]&&interval==SRBuffer[4])
		 return 0;
	 else
		 return SCERR_OPERROR;
 }

 //////////或com句柄
 extern HANDLE hCommDev[256];
 HANDLE GetCOMHandle(int comport)
 {
	 return hCommDev[comport];
 }

