//////////////////////////////////////////////////////////////////////////
// FileName: CardReaderClientDll.cpp
// Creator: icejoywoo
// Date: 2011.12.03
// $Revision$
// Comment: �ͻ��˲����������Ľӿڶ����ʵ��
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CardReaderClientDll.h"
#include "ClientParam.h"
#include "ClientUtils.h"
#include <iostream>
#include <string>

using namespace std;

// #define CARDREADERCLIENTDLL_EXPORTS
// #define SMARTCOMSTRING_EXPORTS_MACRO

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


// This is an example of an exported variable
// CARDREADERCLIENTDLL_API int nCardReaderClientDll=0;

// This is an example of an exported function.
// CARDREADERCLIENTDLL_API int fnCardReaderClientDll(void)
// {
// 	return 42;
// }

// This is the constructor of a class that has been exported.
// see CardReaderClientDll.h for the class definition
// CCardReaderClientDll::CCardReaderClientDll()
// { 
// 	return; 
// }


CARDREADERCLIENTDLL_API int InitClient(char* serverIp, int serverPort)
{
	// ��ʼ��winsock����
	WSADATA wsaData;
	int wsaret=WSAStartup(0x101,&wsaData);

	ClientParam::instance->serverIp = serverIp;
	ClientParam::instance->serverPort = serverPort;
	return 0;
}

CARDREADERCLIENTDLL_API int CleanUpClient()
{
	if (0 != WSACleanup())
		return -1; 
	return 0;
}

CARDREADERCLIENTDLL_API int GetReader(Reader* reader, long socketTimeout, long customTimeout)
{
	struct sockaddr_in server;
	struct hostent *hp;
	unsigned int addr;

	// ����server��ַ
	if(inet_addr(ClientParam::instance->serverIp) == INADDR_NONE)
	{
		hp=gethostbyname(ClientParam::instance->serverIp);
	}
	else
	{
		addr=inet_addr(ClientParam::instance->serverIp);
		hp=gethostbyaddr((char*)&addr,sizeof(addr),AF_INET);
	}

	server.sin_addr.s_addr=*((unsigned long*)hp->h_addr);
	server.sin_family=AF_INET;
	server.sin_port=htons(ClientParam::instance->serverPort);

	reader->s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// ����socket��ʱ
	if(::setsockopt(reader->s, SOL_SOCKET, SO_SNDTIMEO, (char *)&socketTimeout,sizeof(socketTimeout)) == SOCKET_ERROR){
		return SETSOCKOPT_FAILED;
	}

	if (connect(reader->s, (sockaddr*)&server, sizeof(server)))
	{
		return CONNECT_FAILED;
	}
	char buf[512];
	// ��������id���͹�ȥ
	if (-1 == ClientUtils::sendData(reader->s, reader->readerId))
	{
		return SEND_ERROR;
	}
	// ���Ƿ�ɹ�
	ClientUtils::receiveData(reader->s, buf, 512);
	if (strcmp(buf, "id_ok") != 0)
	{
		closesocket(reader->s); // �ر�socket��Դ
		return -1; // ������id����
	}
	// ���ͻ�������ʱ���͵�������
	ClientUtils::sendData(reader->s, customTimeout);
	ClientUtils::receiveData(reader->s, buf, 512);
	if (strcmp(buf, "timeout_ok") != 0)
	{
		closesocket(reader->s); // �ر�socket��Դ
		return -2; // ��ʱ���ô���
	}

	// ���Ƿ�Ready
	ClientUtils::receiveData(reader->s, buf, 512);
	if (strcmp(buf, "Ready") != 0)
	{
		closesocket(reader->s); // �ر�socket��Դ
		return -3; // �ȴ�ʧ��
	}
	
	return 0;
}

CARDREADERCLIENTDLL_API int ReleaseReader(Reader* reader)
{
	int retCode;
	if (0 != ClientUtils::sendData(reader->s, "quit")) // �����˳���Ϣ
	{
		cout << "�������ݳ���" << endl;
	}
	ClientUtils::receiveData(reader->s, retCode);
	if (retCode != 0)
	{
		cout << "�������ݳ���" << endl;
	}
	// �ر���Դ
	closesocket(reader->s);
	reader->readerId = 0;
	return 0;
}

CARDREADERCLIENTDLL_API int GetDevIDAndReaderId(Reader reader, char* devID, int devIDBufLen, int& readerId)
{
	if (ClientUtils::sendData(reader.s, "getDevIdAndReaderId") == SOCKET_ERROR)
	{
		return SEND_ERROR;
	}
	char buf[512];
	int size = ClientUtils::receiveData(reader.s, buf, 512);
	if (size == -1)
	{
		return RECV_ERROR;
	}

	sscanf(buf, "%s,%d", devID, readerId);
	int serverRet;
	ClientUtils::receiveData(reader.s, serverRet);
	return serverRet;
}

CARDREADERCLIENTDLL_API int SetReaderIdByDevID(Reader reader, const char* devID, int readerId)
{
	char cmd[512];
	sprintf(cmd, "getDevIdAndReaderId,%s,%d", devID, readerId);
	if (ClientUtils::sendData(reader.s, cmd) == SOCKET_ERROR)
	{
		return SEND_ERROR;
	}
	int serverRet;
	ClientUtils::receiveData(reader.s, serverRet);
	return serverRet;
}

CARDREADERCLIENTDLL_API int GetAppVerAndDevType(Reader reader, char* appVer, int appVerlen, char* devType, int devTypeLen)
{

	return 0;
}