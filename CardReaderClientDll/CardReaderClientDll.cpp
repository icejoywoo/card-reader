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
	// 初始化winsock环境
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

	server.sin_addr.s_addr=*((unsigned long*)hp->h_addr);
	server.sin_family=AF_INET;
	server.sin_port=htons(ClientParam::instance->serverPort);

	reader->s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 设置socket延时
	if(::setsockopt(reader->s, SOL_SOCKET, SO_SNDTIMEO, (char *)&socketTimeout,sizeof(socketTimeout)) == SOCKET_ERROR){
		return SETSOCKOPT_FAILED;
	}

	if (connect(reader->s, (sockaddr*)&server, sizeof(server)))
	{
		return CONNECT_FAILED;
	}
	char buf[512];
	// 将读卡器id发送过去
	if (-1 == ClientUtils::sendData(reader->s, reader->readerId))
	{
		return SEND_ERROR;
	}
	// 看是否成功
	ClientUtils::receiveData(reader->s, buf, 512);
	if (strcmp(buf, "id_ok") != 0)
	{
		closesocket(reader->s); // 关闭socket资源
		return -1; // 读卡器id错误
	}
	// 将客户定制延时发送到服务器
	ClientUtils::sendData(reader->s, customTimeout);
	ClientUtils::receiveData(reader->s, buf, 512);
	if (strcmp(buf, "timeout_ok") != 0)
	{
		closesocket(reader->s); // 关闭socket资源
		return -2; // 延时设置错误
	}

	// 看是否Ready
	ClientUtils::receiveData(reader->s, buf, 512);
	if (strcmp(buf, "Ready") != 0)
	{
		closesocket(reader->s); // 关闭socket资源
		return -3; // 等待失败
	} 
	
	return 0;
}

CARDREADERCLIENTDLL_API int ReleaseReader(Reader* reader)
{
	int retCode;
	if (-1 == ClientUtils::sendData(reader->s, "quit")) // 发出退出消息
	{
		cout << "发送数据出错" << endl;
	}
	ClientUtils::receiveData(reader->s, retCode);
	if (retCode != 0)
	{
		cout << "接收数据出错" << endl;
	}
	// 关闭资源
	closesocket(reader->s);
	reader->readerId = 0;
	return 0;
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
	char cmd[512];
	sprintf(cmd, "resetCard,%d", card);
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
	retCode = buf;

	int ret;
	if (ClientUtils::receiveData(reader->s, ret) == -1)
	{
		return RECV_ERROR;
	}
	return ret;
}

CARDREADERCLIENTDLL_API int CardApdu(Reader* reader, char* apdu, SmartCom::string& retCode,int card)
{
	char cmd[512];
	sprintf(cmd, "cardApdu,%s,%d", apdu, card);
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
	retCode = buf;
	
	int ret;
	if (ClientUtils::receiveData(reader->s, ret) == -1)
	{
		return RECV_ERROR;
	}
	return ret;
}

CARDREADERCLIENTDLL_API int ShutdownCard(Reader* reader)
{
	if (ClientUtils::sendData(reader->s, "shutdown") == SOCKET_ERROR)
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