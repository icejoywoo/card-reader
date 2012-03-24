//////////////////////////////////////////////////////////////////////////
// FileName: CardReaderClientDll.cpp
// Creator: icejoywoo
// Date: 2011.12.03
// $Revision$
// Comment: 客户端操作读卡器的接口定义的实现
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
// 	// 初始化winsock环境
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
	// 只初始化一次
	try
	{
	if (!ClientParam::instance->isInit)
	{
		WSADATA wsaData;
		WORD wVersionRequested = MAKEWORD(2,1);
		if (0 !=WSAStartup(wVersionRequested,&wsaData)) // 初始化socket环境
		{
			ClientUtils::error("socket环境初始化失败!", reader->readerId, "GetReader");
			return -4;
		} 
		else 
		{
			ClientUtils::info("socket环境初始化成功!", reader->readerId, "GetReader");
			ClientParam::instance->isInit = true;
		}
	}
	struct sockaddr_in server;
	// 2012.3.15 不实用hostent, 不支持主机名解析功能, 直接使用ip
//	struct hostent *hp;
//	unsigned int addr;
// 	time(&t);
// 	fprintf(ClientParam::instance->log, "%s\t[读卡器%d]GetReader获取读卡器: 服务器的配置为IP: %s, PORT: %d\n", 
// 		asctime(localtime(&t)), reader->readerId, ClientParam::instance->serverIp, ClientParam::instance->serverPort);
// 	fflush(ClientParam::instance->log);
	// 设置server地址
// 	if(inet_addr(ClientParam::instance->serverIp) == INADDR_NONE)
// 	{
// 		hp=gethostbyname(ClientParam::instance->serverIp);
// 	}
// 	else
// 	{
// 		addr=inet_addr(ClientParam::instance->serverIp);
// 		hp=gethostbyaddr((char*)&addr,sizeof(addr),AF_INET);
// 	}
	
	// 判断hostent是否获取成功
// 	if (NULL == hp)
// 	{
// 		time(&t);
// 		fprintf(ClientParam::instance->log, "%s\t[读卡器%d]GetReader获取读卡器: hp获取失败\n", 
// 			asctime(localtime(&t)), reader->readerId, ClientParam::instance->serverIp, ClientParam::instance->serverPort);
// 		fflush(ClientParam::instance->log);
// 		return -6;
// 	}
	// 设置server的ip和port
//	server.sin_addr.s_addr=*((u_long FAR*)hp->h_addr);
	server.sin_addr.S_un.S_addr = inet_addr(ClientParam::instance->serverIp); // 不使用hostent, 直接赋值的方式
	server.sin_family=AF_INET;
	server.sin_port=htons(ClientParam::instance->serverPort);
	
	ClientUtils::info("开始建立socket...", reader->readerId, "GetReader");

	reader->s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (reader->s == INVALID_SOCKET)
	{
		ClientUtils::error("socket建立失败!", reader->readerId, "GetReader");
	}
	else
	{
		ClientUtils::info("socket建立成功!", reader->readerId, "GetReader");
	}

	// 设置socket延时
	if(::setsockopt(reader->s, SOL_SOCKET, SO_SNDTIMEO, (char *)&socketTimeout,sizeof(socketTimeout)) == SOCKET_ERROR){
		ClientUtils::error("socket延时设置失败!", reader->readerId, "GetReader");
		return SETSOCKOPT_FAILED;
	}

	// socket连接服务器
	if (connect(reader->s, (sockaddr*)&server, sizeof(server)))
	{
		ClientUtils::error("socket连接服务器失败!", reader->readerId, "GetReader");
		return CONNECT_FAILED;
	}
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	// 将读卡器id发送过去
	if (-1 == ClientUtils::sendData(reader->s, reader->readerId))
	{
		ClientUtils::error("socket发送数据失败!", reader->readerId, "GetReader");
		return SEND_ERROR;
	}
	// 看是否成功
	ClientUtils::receiveData(reader->s, buf, 1024);
	if (strcmp(buf, "id_ok") != 0)
	{
		ClientUtils::error("读卡器id设置失败!", reader->readerId, "GetReader");
		ClientUtils::shutdownAndCloseSocket(reader->s);
		return -1; // 读卡器id错误
	}
	// 将客户定制延时发送到服务器
	ClientUtils::sendData(reader->s, customTimeout);
	ClientUtils::receiveData(reader->s, buf, 1024);
	if (strcmp(buf, "timeout_ok") != 0)
	{
		ClientUtils::error("socket延时设置失败!", reader->readerId, "GetReader");
		ClientUtils::shutdownAndCloseSocket(reader->s);
		return -2; // 延时设置错误
	}

	// 看是否Ready
	ClientUtils::receiveData(reader->s, buf, 1024);
	if (strcmp(buf, "Ready") != 0)
	{
		ClientUtils::error("读卡器获取失败! 等待超时!", reader->readerId, "GetReader");
		ClientUtils::shutdownAndCloseSocket(reader->s);
		return -3; // 等待失败
	}
	else {
		ClientUtils::info("读卡器获取成功!", reader->readerId, "GetReader");
		return 0;
	}
	
	}
	catch (...) // GetReader异常捕获
	{
		ClientUtils::error("获取读卡器出现异常!", reader->readerId, "GetReader");
		return -5;
	}
}

CARDREADERCLIENTDLL_API int ReleaseReader(Reader* reader)
{
	int retCode;
	try
	{
	if (-1 == ClientUtils::sendData(reader->s, "quit")) // 发出退出消息
	{
		// 关闭资源
		ClientUtils::error("socket发送数据失败!", reader->readerId, "ReleaseReader");
		ClientUtils::shutdownAndCloseSocket(reader->s);
		reader->readerId = 0;
		return SEND_ERROR;
	}
	if (-1 != ClientUtils::receiveData(reader->s, retCode))
	{
		if (retCode != 0)
		{
			ClientUtils::error("读卡器释放失败!", reader->readerId, "ReleaseReader");
			return -1;
		}
	}
	else
	{
		ClientUtils::error("接收返回码失败!", reader->readerId, "ReleaseReader");
		return -1;
	}
	
	// 关闭资源
	ClientUtils::shutdownAndCloseSocket(reader->s);
// 	if (0 == closesocket(reader->s))
// 	{
// // 		time(&t);
// // 		fprintf(ClientParam::instance->log, "%s\t[读卡器%d]ReleaseReader释放读卡器: 读卡器释放成功!\n", asctime(localtime(&t)), reader->readerId);
// // 		fflush(ClientParam::instance->log);
// 	}
// 	else
// 	{
// 		time(&t);
// 		fprintf(ClientParam::instance->log, "%s\t[读卡器%d]ReleaseReader释放读卡器: 读卡器释放失败! 错误码:%d\n", 
// 			asctime(localtime(&t)), reader->readerId, WSAGetLastError());
// 		fflush(ClientParam::instance->log);
// 		return -2;
// 	}
	
//	ClientParam::instance->deleteClient();
	// 将reader初始化为0
	reader->readerId = 0;
	// 考虑不释放socket环境, 看是否还会出现问题
// 	if (ClientParam::instance->isClientEmpty())
// 	{
// 		WSACleanup();
// 	}
	return retCode;
	}
	catch (...) // ReleaseReader异常捕获
	{
		ClientUtils::error("释放读卡器异常!", reader->readerId, "ReleaseReader");
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

	// 处理返回结果
	string first;
	string second;
	ClientUtils::splitString(buf, first, second);
	strcpy(devID, first.c_str());
	readerMacId = atoi(second.c_str());

	int serverRet;
	ClientUtils::receiveData(reader->s, serverRet); // 接收服务器返回值
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

	// 处理返回结果
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
	
	// 处理返回结果
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
		ClientUtils::error("指令发送错误!", reader->readerId, "ResetCard");
		return SEND_ERROR;
	}
	
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	int size = ClientUtils::receiveData(reader->s, buf, 512);
	if (size == -1)
	{
		ClientUtils::error("数据接收错误!", reader->readerId, "ResetCard");
		return RECV_ERROR;
	}
	retCode = buf;

	int ret;
	if (ClientUtils::receiveData(reader->s, ret) == -1)
	{
		ClientUtils::error("返回值接收错误!", reader->readerId, "ResetCard");
		return RECV_ERROR;
	} else {
		ClientUtils::info("指令执行成功!", reader->readerId, "ResetCard");
	}
	return ret;
	}
	catch (...) // 异常捕获
	{
		ClientUtils::error("卡片复位异常!", reader->readerId, "ResetCard");
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
			ClientUtils::error("指令发送错误!", reader->readerId, "CardApdu");
			return SEND_ERROR;
		}
		
		char buf[1024];
		memset(buf, 0, sizeof(buf));
		int size = ClientUtils::receiveData(reader->s, buf, 512);
		if (size == -1)
		{
			ClientUtils::error("数据接收错误!", reader->readerId, "CardApdu");
			return RECV_ERROR;
		}
		retCode = buf;
		
		int ret;
		if (ClientUtils::receiveData(reader->s, ret) == -1)
		{
			ClientUtils::error("结果接收错误!", reader->readerId, "CardApdu");
			return RECV_ERROR;
		} else {
			ClientUtils::info("执行指令成功!", reader->readerId, "CardApdu");
			return ret;
		}
	
	}
	catch (...) // 异常捕获
	{
		ClientUtils::info("卡片复位异常!", reader->readerId, "CardApdu");
		return -1;
	}
}

CARDREADERCLIENTDLL_API int ShutdownCard(Reader* reader)
{
	try
	{
		if (ClientUtils::sendData(reader->s, "shutdown") == SOCKET_ERROR)
		{
			ClientUtils::error("指令发送错误!", reader->readerId, "ShutdownCard");
			return SEND_ERROR;
		}
		
		int ret;
		if (ClientUtils::receiveData(reader->s, ret) == -1)
		{
			ClientUtils::error("结果接收错误!", reader->readerId, "ShutdownCard");
			return RECV_ERROR;
		} else {
			ClientUtils::info("卡片下电成功!", reader->readerId, "ShutdownCard");
			return ret;
		}
	}
	catch (...) // 异常捕获
	{
		ClientUtils::error("卡片下电异常!", reader->readerId, "ShutdownCard");
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