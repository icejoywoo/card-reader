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
#include <cassert>
#include <time.h>

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

//////////////////////////////////////////////////////////////////////////
// CARDREADERCLIENTDLL_API int InitClient(char* serverIp, int serverPort)
// {
// 	// ��ʼ��winsock����
// 	WSADATA wsaData;
// 	int wsaret=WSAStartup(0x101,&wsaData);
// 	WaitForSingleObject(ClientParam::instance->mutex, INFINITE);
// 	ClientParam::instance->serverIp = serverIp;
// 	ClientParam::instance->serverPort = serverPort;
// 	ReleaseMutex(ClientParam::instance->mutex);
// 	return 0;
// }
// 
// CARDREADERCLIENTDLL_API int CleanUpClient()
// {
// 	WaitForSingleObject(ClientParam::instance->mutex, INFINITE);
// 	int ret = WSACleanup();
// 	ReleaseMutex(ClientParam::instance->mutex);
// 	if (0 != ret)
// 		return -1; 
// 	return 0;
// }
//////////////////////////////////////////////////////////////////////////


CARDREADERCLIENTDLL_API int GetReader(Reader* reader, long socketTimeout, long customTimeout)
{
// 	if (ClientParam::instance->isClientEmpty())
// 	{
// 		WSADATA wsaData;
// 		if (0 !=WSAStartup(0x101,&wsaData))
// 			return -4;
// 	}
	// ֻ��ʼ��һ��
	try
	{
	if (!ClientParam::instance->isInit)
	{
		WSADATA wsaData;
		WORD wVersionRequested = MAKEWORD(2,1);
		if (0 !=WSAStartup(wVersionRequested,&wsaData)) // ��ʼ��socket����
		{
			ClientUtils::error("socket������ʼ��ʧ��!", reader->readerId, "GetReader");
			return -4;
		} 
		else 
		{
			ClientUtils::info("socket������ʼ���ɹ�!", reader->readerId, "GetReader");
			ClientParam::instance->isInit = true;
		}
	}
	struct sockaddr_in server;
	// 2012.3.15 ��ʵ��hostent, ��֧����������������, ֱ��ʹ��ip
//	struct hostent *hp;
//	unsigned int addr;
// 	time(&t);
// 	fprintf(ClientParam::instance->log, "%s\t[������%d]GetReader��ȡ������: ������������ΪIP: %s, PORT: %d\n", 
// 		asctime(localtime(&t)), reader->readerId, ClientParam::instance->serverIp, ClientParam::instance->serverPort);
// 	fflush(ClientParam::instance->log);
	// ����server��ַ
// 	if(inet_addr(ClientParam::instance->serverIp) == INADDR_NONE)
// 	{
// 		hp=gethostbyname(ClientParam::instance->serverIp);
// 	}
// 	else
// 	{
// 		addr=inet_addr(ClientParam::instance->serverIp);
// 		hp=gethostbyaddr((char*)&addr,sizeof(addr),AF_INET);
// 	}
	
	// �ж�hostent�Ƿ��ȡ�ɹ�
// 	if (NULL == hp)
// 	{
// 		time(&t);
// 		fprintf(ClientParam::instance->log, "%s\t[������%d]GetReader��ȡ������: hp��ȡʧ��\n", 
// 			asctime(localtime(&t)), reader->readerId, ClientParam::instance->serverIp, ClientParam::instance->serverPort);
// 		fflush(ClientParam::instance->log);
// 		return -6;
// 	}
	// ����server��ip��port
//	server.sin_addr.s_addr=*((u_long FAR*)hp->h_addr);
	server.sin_addr.S_un.S_addr = inet_addr(ClientParam::instance->serverIp); // ��ʹ��hostent, ֱ�Ӹ�ֵ�ķ�ʽ
	server.sin_family=AF_INET;
	server.sin_port=htons(ClientParam::instance->serverPort);
	
	ClientUtils::info("��ʼ����socket...", reader->readerId, "GetReader");

	reader->s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (reader->s == INVALID_SOCKET)
	{
		ClientUtils::error("socket����ʧ��!", reader->readerId, "GetReader");
	}
	else
	{
		ClientUtils::info("socket�����ɹ�!", reader->readerId, "GetReader");
	}

	// ����socket��ʱ
	if(::setsockopt(reader->s, SOL_SOCKET, SO_SNDTIMEO, (char *)&socketTimeout,sizeof(socketTimeout)) == SOCKET_ERROR){
		ClientUtils::error("socket��ʱ����ʧ��!", reader->readerId, "GetReader");
		return SETSOCKOPT_FAILED;
	}

	// socket���ӷ�����
	if (connect(reader->s, (sockaddr*)&server, sizeof(server)))
	{
		ClientUtils::error("socket���ӷ�����ʧ��!", reader->readerId, "GetReader");
		return CONNECT_FAILED;
	}
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	// ��������id���͹�ȥ
	if (-1 == ClientUtils::sendData(reader->s, reader->readerId))
	{
		ClientUtils::error("socket��������ʧ��!", reader->readerId, "GetReader");
		return SEND_ERROR;
	}
	// ���Ƿ�ɹ�
	ClientUtils::receiveData(reader->s, buf, 1024);
	if (strcmp(buf, "id_ok") != 0)
	{
		ClientUtils::error("������id����ʧ��!", reader->readerId, "GetReader");
		ClientUtils::shutdownAndCloseSocket(reader->s);
		return -1; // ������id����
	}
	// ���ͻ�������ʱ���͵�������
	ClientUtils::sendData(reader->s, customTimeout);
	ClientUtils::receiveData(reader->s, buf, 1024);
	if (strcmp(buf, "timeout_ok") != 0)
	{
		ClientUtils::error("socket��ʱ����ʧ��!", reader->readerId, "GetReader");
		ClientUtils::shutdownAndCloseSocket(reader->s);
		return -2; // ��ʱ���ô���
	}

	// ���Ƿ�Ready
	ClientUtils::receiveData(reader->s, buf, 1024);
	if (strcmp(buf, "Ready") != 0)
	{
		ClientUtils::error("��������ȡʧ��! �ȴ���ʱ!", reader->readerId, "GetReader");
		ClientUtils::shutdownAndCloseSocket(reader->s);
		return -3; // �ȴ�ʧ��
	}
	else {
		ClientUtils::info("��������ȡ�ɹ�!", reader->readerId, "GetReader");
		return 0;
	}
	
	}
	catch (...) // GetReader�쳣����
	{
		ClientUtils::error("��ȡ�����������쳣!", reader->readerId, "GetReader");
		return -5;
	}
}

CARDREADERCLIENTDLL_API int ReleaseReader(Reader* reader)
{
	int retCode;
	try
	{
	if (-1 == ClientUtils::sendData(reader->s, "quit")) // �����˳���Ϣ
	{
		// �ر���Դ
		ClientUtils::error("socket��������ʧ��!", reader->readerId, "ReleaseReader");
		ClientUtils::shutdownAndCloseSocket(reader->s);
		reader->readerId = 0;
		return SEND_ERROR;
	}
	if (-1 != ClientUtils::receiveData(reader->s, retCode))
	{
		if (retCode != 0)
		{
			ClientUtils::error("�������ͷ�ʧ��!", reader->readerId, "ReleaseReader");
			return -1;
		}
	}
	else
	{
		ClientUtils::error("���շ�����ʧ��!", reader->readerId, "ReleaseReader");
		return -1;
	}
	
	// �ر���Դ
	ClientUtils::shutdownAndCloseSocket(reader->s);
// 	if (0 == closesocket(reader->s))
// 	{
// // 		time(&t);
// // 		fprintf(ClientParam::instance->log, "%s\t[������%d]ReleaseReader�ͷŶ�����: �������ͷųɹ�!\n", asctime(localtime(&t)), reader->readerId);
// // 		fflush(ClientParam::instance->log);
// 	}
// 	else
// 	{
// 		time(&t);
// 		fprintf(ClientParam::instance->log, "%s\t[������%d]ReleaseReader�ͷŶ�����: �������ͷ�ʧ��! ������:%d\n", 
// 			asctime(localtime(&t)), reader->readerId, WSAGetLastError());
// 		fflush(ClientParam::instance->log);
// 		return -2;
// 	}
	
//	ClientParam::instance->deleteClient();
	// ��reader��ʼ��Ϊ0
	reader->readerId = 0;
	// ���ǲ��ͷ�socket����, ���Ƿ񻹻��������
// 	if (ClientParam::instance->isClientEmpty())
// 	{
// 		WSACleanup();
// 	}
	return retCode;
	}
	catch (...) // ReleaseReader�쳣����
	{
		ClientUtils::error("�ͷŶ������쳣!", reader->readerId, "ReleaseReader");
		return -1;
	}
}

CARDREADERCLIENTDLL_API int GetDevIDAndReaderId(Reader* reader, char* devID, int devIDBufLen, int& readerMacId)
{
	if (ClientUtils::sendData(reader->s, "getDevIdAndReaderId") == SOCKET_ERROR)
	{
		return SEND_ERROR;
	}
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	int size = ClientUtils::receiveData(reader->s, buf, 512);
	if (size == -1)
	{
		return RECV_ERROR;
	}

	// �����ؽ��
	string first;
	string second;
	ClientUtils::splitString(buf, first, second);
	strcpy(devID, first.c_str());
	readerMacId = atoi(second.c_str());

	int serverRet;
	ClientUtils::receiveData(reader->s, serverRet); // ���շ���������ֵ
	return serverRet;
}

CARDREADERCLIENTDLL_API int SetReaderIdByDevID(Reader* reader, const char* devID, int readerMacId)
{
	char cmd[512];
	sprintf(cmd, "setReaderIdByDevID,%s,%d", devID, readerMacId);
	if (ClientUtils::sendData(reader->s, cmd) == SOCKET_ERROR)
	{
		return SEND_ERROR;
	}
	int serverRet;
	ClientUtils::receiveData(reader->s, serverRet);
	if (serverRet == 0)
	{
		reader->readerId = readerMacId;
	}
	return serverRet;
}

CARDREADERCLIENTDLL_API int GetAppVerAndDevType(Reader* reader, char* appVer, int appVerlen, char* devType, int devTypeLen)
{
	if (ClientUtils::sendData(reader->s, "getAppVerAndDevType") == SOCKET_ERROR)
	{
		return SEND_ERROR;
	}
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	int size = ClientUtils::receiveData(reader->s, buf, 512);
	if (size == -1)
	{
		return RECV_ERROR;
	}

	// �����ؽ��
	string first;
	string second;
	ClientUtils::splitString(buf, first, second);
	assert(appVerlen >= first.length());
	strcpy(appVer, first.c_str());
	assert(devTypeLen >= second.length());
	strcpy(devType, second.c_str());
	
	int retCode;
	size = ClientUtils::receiveData(reader->s, retCode);
	if (size == -1)
	{
		return RECV_ERROR;
	}
	return retCode;
}

CARDREADERCLIENTDLL_API int ResetDev(Reader* reader)
{
	if (ClientUtils::sendData(reader->s, "reset") == SOCKET_ERROR)
	{
		return SEND_ERROR;
	}

	int retCode;
	if (ClientUtils::receiveData(reader->s, retCode) == -1)
	{
		return RECV_ERROR;
	}
	return retCode;
}

CARDREADERCLIENTDLL_API int GetChipID(Reader* reader, char* chipID, int chipIDLen)
{
	if (ClientUtils::sendData(reader->s, "getChipID") == SOCKET_ERROR)
	{
		return SEND_ERROR;
	}
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	if (ClientUtils::receiveData(reader->s, buf, 512) == -1)
	{
		return RECV_ERROR;
	}
	assert(chipIDLen >= strlen(buf));
	strcpy(chipID, buf);

	int retCode;
	if (ClientUtils::receiveData(reader->s, retCode) == -1)
	{
		return RECV_ERROR;
	}
	return retCode;
}

CARDREADERCLIENTDLL_API int IsCardReady(Reader* reader, int& cardA,int& cardB)
{
	if (ClientUtils::sendData(reader->s, "isCardReady") == SOCKET_ERROR)
	{
		return SEND_ERROR;
	}

	char buf[1024];
	memset(buf, 0, sizeof(buf));
	int size = ClientUtils::receiveData(reader->s, buf, 512);
	if (size == -1)
	{
		return RECV_ERROR;
	}
	
	// �����ؽ��
	string first;
	string second;
	ClientUtils::splitString(buf, first, second);
	cardA = atoi(first.c_str());
	cardB = atoi(second.c_str());

	int retCode;
	if (ClientUtils::receiveData(reader->s, retCode) == -1)
	{
		return RECV_ERROR;
	}
	return retCode;
}

CARDREADERCLIENTDLL_API int ResetCard(Reader* reader, SmartCom::string& retCode,int card)
{
	try
	{
	char cmd[512];
	sprintf(cmd, "resetCard,%d", card);
	if (ClientUtils::sendData(reader->s, cmd) == SOCKET_ERROR)
	{
		ClientUtils::error("ָ��ʹ���!", reader->readerId, "ResetCard");
		return SEND_ERROR;
	}
	
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	int size = ClientUtils::receiveData(reader->s, buf, 512);
	if (size == -1)
	{
		ClientUtils::error("���ݽ��մ���!", reader->readerId, "ResetCard");
		return RECV_ERROR;
	}
	retCode = buf;

	int ret;
	if (ClientUtils::receiveData(reader->s, ret) == -1)
	{
		ClientUtils::error("����ֵ���մ���!", reader->readerId, "ResetCard");
		return RECV_ERROR;
	} else {
		ClientUtils::info("ָ��ִ�гɹ�!", reader->readerId, "ResetCard");
	}
	return ret;
	}
	catch (...) // �쳣����
	{
		ClientUtils::error("��Ƭ��λ�쳣!", reader->readerId, "ResetCard");
		return -1;
	}
}

CARDREADERCLIENTDLL_API int CardApdu(Reader* reader, char* apdu, SmartCom::string& retCode,int card)
{
	try
	{
		char cmd[512];
		sprintf(cmd, "cardApdu,%s,%d", apdu, card);
		if (ClientUtils::sendData(reader->s, cmd) == SOCKET_ERROR)
		{
			ClientUtils::error("ָ��ʹ���!", reader->readerId, "CardApdu");
			return SEND_ERROR;
		}
		
		char buf[1024];
		memset(buf, 0, sizeof(buf));
		int size = ClientUtils::receiveData(reader->s, buf, 512);
		if (size == -1)
		{
			ClientUtils::error("���ݽ��մ���!", reader->readerId, "CardApdu");
			return RECV_ERROR;
		}
		retCode = buf;
		
		int ret;
		if (ClientUtils::receiveData(reader->s, ret) == -1)
		{
			ClientUtils::error("������մ���!", reader->readerId, "CardApdu");
			return RECV_ERROR;
		} else {
			ClientUtils::info("ִ��ָ��ɹ�!", reader->readerId, "CardApdu");
			return ret;
		}
	
	}
	catch (...) // �쳣����
	{
		ClientUtils::info("��Ƭ��λ�쳣!", reader->readerId, "CardApdu");
		return -1;
	}
}

CARDREADERCLIENTDLL_API int ShutdownCard(Reader* reader)
{
	try
	{
		if (ClientUtils::sendData(reader->s, "shutdown") == SOCKET_ERROR)
		{
			ClientUtils::error("ָ��ʹ���!", reader->readerId, "ShutdownCard");
			return SEND_ERROR;
		}
		
		int ret;
		if (ClientUtils::receiveData(reader->s, ret) == -1)
		{
			ClientUtils::error("������մ���!", reader->readerId, "ShutdownCard");
			return RECV_ERROR;
		} else {
			ClientUtils::info("��Ƭ�µ�ɹ�!", reader->readerId, "ShutdownCard");
			return ret;
		}
	}
	catch (...) // �쳣����
	{
		ClientUtils::error("��Ƭ�µ��쳣!", reader->readerId, "ShutdownCard");
		return -1;
	}
}

CARDREADERCLIENTDLL_API int ModifyCardBraudRate(Reader* reader, int braudRate)
{
	char cmd[512];
	sprintf(cmd, "modifyBraudRate,%d", braudRate);
	if (ClientUtils::sendData(reader->s, cmd) == SOCKET_ERROR)
	{
		return SEND_ERROR;
	}

	int ret;
	if (ClientUtils::receiveData(reader->s, ret) == -1)
	{
		return RECV_ERROR;
	}
	return ret;
}

CARDREADERCLIENTDLL_API int GetCardBraudRate(Reader* reader, int& braudRate)
{
	if (ClientUtils::sendData(reader->s, "getBraudRate") == SOCKET_ERROR)
	{
		return SEND_ERROR;
	}
	
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	int size = ClientUtils::receiveData(reader->s, buf, 512);
	if (size == -1)
	{
		return RECV_ERROR;
	}
	braudRate = atoi(buf);

	int ret;
	if (ClientUtils::receiveData(reader->s, ret) == -1)
	{
		return RECV_ERROR;
	}
	return ret;
}

CARDREADERCLIENTDLL_API int ModifyCardPower(Reader* reader, int power,int card)
{
	char cmd[512];
	sprintf(cmd, "modifyCardPower,%d,%d", power, card);
	if (ClientUtils::sendData(reader->s, cmd) == SOCKET_ERROR)
	{
		return SEND_ERROR;
	}
	
	int ret;
	if (ClientUtils::receiveData(reader->s, ret) == -1)
	{
		return RECV_ERROR;
	}
	return ret;
}

CARDREADERCLIENTDLL_API int  ExcuteMulAPDU(Reader* reader, int cmdNum,int card)
{
	char cmd[512];
	sprintf(cmd, "executeMulApdu,%d,%d", cmdNum, card);
	if (ClientUtils::sendData(reader->s, cmd) == SOCKET_ERROR)
	{
		return SEND_ERROR;
	}

	int ret;
	if (ClientUtils::receiveData(reader->s, ret) == -1)
	{
		return RECV_ERROR;
	}
	return ret;
}

CARDREADERCLIENTDLL_API int GetScriptData(Reader* reader, int offset,unsigned char bytes,SmartCom::string& strData)
{
	char cmd[512];
	sprintf(cmd, "getScript,%d,%d", offset, bytes);
	if (ClientUtils::sendData(reader->s, cmd) == SOCKET_ERROR)
	{
		return SEND_ERROR;
	}
	
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	int size = ClientUtils::receiveData(reader->s, buf, 512);
	if (size == -1)
	{
		return RECV_ERROR;
	}
	strData = buf;

	int ret;
	if (ClientUtils::receiveData(reader->s, ret) == -1)
	{
		return RECV_ERROR;
	}
	return ret;
}

CARDREADERCLIENTDLL_API int DownloadFile(Reader* reader, int flag, const char* fileName)
{
	char cmd[512];
	sprintf(cmd, "downloadFile,%d,%s", flag, fileName);
	if (ClientUtils::sendData(reader->s, cmd) == SOCKET_ERROR)
	{
		return SEND_ERROR;
	}
	
	int ret;
	if (ClientUtils::receiveData(reader->s, ret) == -1)
	{
		return RECV_ERROR;
	}
	return ret;
}

CARDREADERCLIENTDLL_API int CheckBatchResult(Reader* reader, SmartCom::string& retCode)
{
	if (ClientUtils::sendData(reader->s, "checkBatchResult") == SOCKET_ERROR)
	{
		return SEND_ERROR;
	}
	
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	int size = ClientUtils::receiveData(reader->s, buf, 512);
	if (size == -1)
	{
		return RECV_ERROR;
	}
	retCode = buf;

	int ret;
	if (ClientUtils::receiveData(reader->s, ret) == -1)
	{
		return RECV_ERROR;
	}
	return ret;
}

CARDREADERCLIENTDLL_API int ClearMem(Reader* reader)
{
	if (ClientUtils::sendData(reader->s, "clearMemory") == SOCKET_ERROR)
	{
		return SEND_ERROR;
	}
	
	int ret;
	if (ClientUtils::receiveData(reader->s, ret) == -1)
	{
		return RECV_ERROR;
	}
	return ret;
}