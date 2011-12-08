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
	ClientParam::instance->serverIp = serverIp;
	ClientParam::instance->serverPort = serverPort;
	return 0;
}

CARDREADERCLIENTDLL_API int GetReader(Reader reader, long socketTimeout, long customTimeout)
{
	struct sockaddr_in server;
	struct hostent *hp;
	unsigned int addr;
	
	if(inet_addr(ClientParam::instance->serverIp)==INADDR_NONE)
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
	reader.s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(reader.s, (struct sockaddr*)&server, sizeof(server)))
	{
		return CONNECT_FAILED;
	}
	// TODO: timeout的实现
	return 0;
}

CARDREADERCLIENTDLL_API int ReleaseReader(Reader reader)
{
	ClientUtils::sendData(reader.s, "quit"); // 发出退出消息
	closesocket(reader.s);
	reader.readerId = 0;
	return 0;
}