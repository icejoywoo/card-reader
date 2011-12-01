#include "StdAfx.h"
#include "ContactManager.h"
#include "CustomConsts.h"
#include "assert.h"

//��ʼ�����Ӳ���
ComConnection* Connections::comConnHead=0;
UdpConnection* Connections::udpConnHead=0;
TcpClientConn* Connections::tcpClientConnHead=0;
int Connections::commType=NOT_CONNECT;
BOOL Connections::udpCommInited=FALSE;
BOOL Connections::comCommInited=FALSE;
HANDLE Connections::hCOMInitMutex=CreateMutex(NULL,FALSE,NULL);  //��ʼ��comͨ�Ż������
HANDLE Connections::hUDPInitMutex=CreateMutex(NULL,FALSE,NULL);  //��ʼ��udpͨ�Ż������
HANDLE Connections::hTCPCLientInitMutex=CreateMutex(NULL,FALSE,NULL); //��ʼ��tcpclientͨ�Ż������
HANDLE Connections::timeIntervalMutex=CreateMutex(NULL,FALSE,NULL); 
UINT Connections::lastSendTime=0;

UdpConnection::UdpConnection(int _localPort,char* _dstIP,int _dstPort,SOCKET _s,int _waitSTX2Time,int _normalWaitTime,UdpConnection* _next)
{
		  localPort=_localPort;
		  assert(strlen(_dstIP)<31);
		  strcpy(dstIP,_dstIP);
          dstPort=_dstPort;
		  s=_s;
		  waitSTX2Time=_waitSTX2Time;
		  normalWaitTime=_normalWaitTime;
		  next=_next;
}

ComConnection::ComConnection(int _port,int _rate,int first,int second,ComConnection* _next)
{
	comPort=_port;
	braudRate=_rate;
	waitSTX2Time=first;
	normalWaitTime=second;
	next=_next;
}
