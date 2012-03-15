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



CARDREADERCLIENTDLL_API int GetReader(Reader* reader, long socketTimeout, long customTimeout)
{
// 	if (ClientParam::instance->isClientEmpty())
// 	{
// 		WSADATA wsaData;
// 		if (0 !=WSAStartup(0x101,&wsaData))
// 			return -4;
// 	}
	// 只初始化一次
	time_t t; // 当前时间
	if (!ClientParam::instance->isInit)
	{
		WSADATA wsaData;
		if (0 !=WSAStartup(0x101,&wsaData))
			return -4;
		time(&t);
		fprintf(ClientParam::instance->log, "%s\t[读卡器%d]GetReader获取读卡器: WSAStartup初始化成功!\n", asctime(localtime(&t)), reader->readerId);
		fflush(ClientParam::instance->log);
		ClientParam::instance->isInit = true;
	}
	struct sockaddr_in server;
	struct hostent *hp;
	unsigned int addr;

	// 设置server地址
	if(inet_addr(ClientParam::instance->serverIp) == INADDR_NONE)
	{
		hp=gethostbyname(ClientParam::instance->serverIp);
	}
	else
	{
		addr=inet_addr(ClientParam::instance->serverIp);
		hp=gethostbyaddr((char*)&addr,sizeof(addr),AF_INET);
	}

	server.sin_addr.s_addr=*((u_long FAR*)hp->h_addr);
	server.sin_family=AF_INET;
	server.sin_port=htons(ClientParam::instance->serverPort);
	
	time(&t);
	fprintf(ClientParam::instance->log, "%s\t[读卡器%d]GetReader获取读卡器: 开始建立socket...\n", asctime(localtime(&t)), reader->readerId);
	fflush(ClientParam::instance->log);

	reader->s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (reader->s == INVALID_SOCKET)
	{
		time(&t);
		fprintf(ClientParam::instance->log, "%s\t[读卡器%d]GetReader获取读卡器: socket建立失败!\n", asctime(localtime(&t)), reader->readerId);
		fflush(ClientParam::instance->log);
	}
	else
	{
		time(&t);
		fprintf(ClientParam::instance->log, "%s\t[读卡器%d]GetReader获取读卡器: socket建立成功!\n", asctime(localtime(&t)), reader->readerId);
		fflush(ClientParam::instance->log);
	}

	// 设置socket延时
	if(::setsockopt(reader->s, SOL_SOCKET, SO_SNDTIMEO, (char *)&socketTimeout,sizeof(socketTimeout)) == SOCKET_ERROR){
		time(&t);
		fprintf(ClientParam::instance->log, "%s\t[读卡器%d]GetReader获取读卡器: socket延时设置失败!\n", asctime(localtime(&t)), reader->readerId);
		fflush(ClientParam::instance->log);
		return SETSOCKOPT_FAILED;
	}

	if (connect(reader->s, (sockaddr*)&server, sizeof(server)))
	{
		time(&t);
		fprintf(ClientParam::instance->log, "%s\t[读卡器%d]GetReader获取读卡器: socket连接服务器失败!\n", asctime(localtime(&t)), reader->readerId);
		fflush(ClientParam::instance->log);
		return CONNECT_FAILED;
	}
	char buf[1024];
	// 将读卡器id发送过去
	if (-1 == ClientUtils::sendData(reader->s, reader->readerId))
	{
		time(&t);
		fprintf(ClientParam::instance->log, "%s\t[读卡器%d]GetReader获取读卡器: socket发送数据失败!\n", asctime(localtime(&t)), reader->readerId);
		fflush(ClientParam::instance->log);
		return SEND_ERROR;
	}
	// 看是否成功
	ClientUtils::receiveData(reader->s, buf, 1024);
	if (strcmp(buf, "id_ok") != 0)
	{
		shutdown(reader->s, SD_BOTH);
		closesocket(reader->s); // 关闭socket资源
		return -1; // 读卡器id错误
	}
	// 将客户定制延时发送到服务器
	ClientUtils::sendData(reader->s, customTimeout);
	ClientUtils::receiveData(reader->s, buf, 1024);
	if (strcmp(buf, "timeout_ok") != 0)
	{
		time(&t);
		fprintf(ClientParam::instance->log, "%s\t[读卡器%d]GetReader获取读卡器: socket延时设置失败!\n", asctime(localtime(&t)), reader->readerId);
		fflush(ClientParam::instance->log);
		shutdown(reader->s, SD_BOTH);
		closesocket(reader->s); // 关闭socket资源
		return -2; // 延时设置错误
	}

	// 看是否Ready
	ClientUtils::receiveData(reader->s, buf, 1024);
	if (strcmp(buf, "Ready") != 0)
	{
		time(&t);
		fprintf(ClientParam::instance->log, "%s\t[读卡器%d]GetReader获取读卡器: 读卡器获取失败! 等待超时!\n", asctime(localtime(&t)), reader->readerId);
		fflush(ClientParam::instance->log);
		shutdown(reader->s, SD_BOTH);
		closesocket(reader->s); // 关闭socket资源
		return -3; // 等待失败
	} 
	time(&t);
	fprintf(ClientParam::instance->log, "%s\t[读卡器%d]GetReader获取读卡器: 读卡器获取成功!\n", asctime(localtime(&t)), reader->readerId);
//	ClientParam::instance->addClient();
	fflush(ClientParam::instance->log);
	return 0;
}

CARDREADERCLIENTDLL_API int ReleaseReader(Reader* reader)
{
	time_t t;
	int retCode;
	if (-1 == ClientUtils::sendData(reader->s, "quit")) // 发出退出消息
	{
		// 关闭资源
		shutdown(reader->s, SD_BOTH);
		closesocket(reader->s);
		reader->readerId = 0;
		time(&t);
		fprintf(ClientParam::instance->log, "%s\t[读卡器%d]ReleaseReader释放读卡器: socket发送数据失败!\n", asctime(localtime(&t)), reader->readerId);
		fflush(ClientParam::instance->log);
		return SEND_ERROR;
	}
	ClientUtils::receiveData(reader->s, retCode);
	if (retCode != 0)
	{
		time(&t);
		fprintf(ClientParam::instance->log, "%s\t[读卡器%d]ReleaseReader释放读卡器: 读卡器释放失败!\n", asctime(localtime(&t)), reader->readerId);
		fflush(ClientParam::instance->log);
		return -1;
	}
	// 关闭资源
	shutdown(reader->s, SD_BOTH);
	closesocket(reader->s);
	reader->readerId = 0;
//	ClientParam::instance->deleteClient();
	time(&t);
	fprintf(ClientParam::instance->log, "%s\t[读卡器%d]ReleaseReader释放读卡器: 读卡器释放成功!\n", asctime(localtime(&t)), reader->readerId);
	fflush(ClientParam::instance->log);
	// 考虑不释放socket环境, 看是否还会出现问题
// 	if (ClientParam::instance->isClientEmpty())
// 	{
// 		WSACleanup();
// 	}
	return retCode;
}

CARDREADERCLIENTDLL_API int GetDevIDAndReaderId(Reader* reader, char* devID, int devIDBufLen, int& readerMacId)
{
	if (ClientUtils::sendData(reader->s, "getDevIdAndReaderId") == SOCKET_ERROR)
	{
		return SEND_ERROR;
	}
	char buf[512];
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
	char buf[512];
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
	char buf[512];
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

	char buf[512];
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
	time_t t;
	char cmd[512];
	sprintf(cmd, "resetCard,%d", card);
	if (ClientUtils::sendData(reader->s, cmd) == SOCKET_ERROR)
	{
		time(&t);
		fprintf(ClientParam::instance->log, "%s\t[读卡器%d]ResetCard复位应答: 指令发送错误!\n", asctime(localtime(&t)), reader->readerId);
		fflush(ClientParam::instance->log);
		return SEND_ERROR;
	}
	
	char buf[512];
	int size = ClientUtils::receiveData(reader->s, buf, 512);
	if (size == -1)
	{
		time(&t);
		fprintf(ClientParam::instance->log, "%s\t[读卡器%d]ResetCard复位应答: 数据接收错误!\n", asctime(localtime(&t)), reader->readerId);
		fflush(ClientParam::instance->log);
		return RECV_ERROR;
	}
	retCode = buf;

	int ret;
	if (ClientUtils::receiveData(reader->s, ret) == -1)
	{
		time(&t);
		fprintf(ClientParam::instance->log, "%s\t[读卡器%d]ResetCard复位应答: 返回值接收错误!\n", asctime(localtime(&t)), reader->readerId);
		fflush(ClientParam::instance->log);
		return RECV_ERROR;
	}
	time(&t);
	fprintf(ClientParam::instance->log, "%s\t[读卡器%d]ResetCard复位应答: 指令执行成功!\n", asctime(localtime(&t)), reader->readerId);
	fflush(ClientParam::instance->log);
	return ret;
}

CARDREADERCLIENTDLL_API int CardApdu(Reader* reader, char* apdu, SmartCom::string& retCode,int card)
{
	time_t t;
	char cmd[512];
	sprintf(cmd, "cardApdu,%s,%d", apdu, card);
	if (ClientUtils::sendData(reader->s, cmd) == SOCKET_ERROR)
	{
		time(&t);
		fprintf(ClientParam::instance->log, "%s\t[读卡器%d]CardApdu执行指令: 指令发送错误!\n", asctime(localtime(&t)), reader->readerId);
		fflush(ClientParam::instance->log);
		return SEND_ERROR;
	}
	
	char buf[512];
	int size = ClientUtils::receiveData(reader->s, buf, 512);
	if (size == -1)
	{
		time(&t);
		fprintf(ClientParam::instance->log, "%s\t[读卡器%d]CardApdu执行指令: 数据接收错误!\n", asctime(localtime(&t)), reader->readerId);
		fflush(ClientParam::instance->log);
		return RECV_ERROR;
	}
	retCode = buf;
	
	int ret;
	if (ClientUtils::receiveData(reader->s, ret) == -1)
	{
		time(&t);
		fprintf(ClientParam::instance->log, "%s\t[读卡器%d]CardApdu执行指令: 结果接收错误!\n", asctime(localtime(&t)), reader->readerId);
		fflush(ClientParam::instance->log);
		return RECV_ERROR;
	}
	time(&t);
	fprintf(ClientParam::instance->log, "%s\t[读卡器%d]CardApdu执行指令: 执行指令成功!\n", asctime(localtime(&t)), reader->readerId);
	fflush(ClientParam::instance->log);
	return ret;
}

CARDREADERCLIENTDLL_API int ShutdownCard(Reader* reader)
{
	time_t t;
	if (ClientUtils::sendData(reader->s, "shutdown") == SOCKET_ERROR)
	{
		time(&t);
		fprintf(ClientParam::instance->log, "%s\t[读卡器%d]ShutdownCard卡片下电: 指令发送错误!\n", asctime(localtime(&t)), reader->readerId);
		fflush(ClientParam::instance->log);
		return SEND_ERROR;
	}
	
	int ret;
	if (ClientUtils::receiveData(reader->s, ret) == -1)
	{
		time(&t);
		fprintf(ClientParam::instance->log, "%s\t[读卡器%d]ShutdownCard卡片下电: 结果接收错误!\n", asctime(localtime(&t)), reader->readerId);
		fflush(ClientParam::instance->log);
		return RECV_ERROR;
	}
	time(&t);
	fprintf(ClientParam::instance->log, "%s\t[读卡器%d]ShutdownCard卡片下电: 卡片下电成功!\n", asctime(localtime(&t)), reader->readerId);
	fflush(ClientParam::instance->log);
	return ret;
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
	
	char buf[512];
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
	
	char buf[512];
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
	
	char buf[512];
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