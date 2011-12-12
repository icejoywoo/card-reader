// UnitTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "UnitTest.h"
#include "ClientUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		WSADATA wsaData;
		int wsaret=WSAStartup(0x101,&wsaData);

		struct sockaddr_in server;
		struct hostent *hp;
		unsigned int addr;
		char* serverIp = "127.0.0.1";

		// 设置server地址
		if(inet_addr(serverIp) == INADDR_NONE)
		{
			hp=gethostbyname(serverIp);
		}
		else
		{
			addr=inet_addr(serverIp);
			hp=gethostbyaddr((char*)&addr,sizeof(addr),AF_INET);
		}
		
		server.sin_addr.s_addr=*((unsigned long*)hp->h_addr);
		server.sin_family=AF_INET;
		server.sin_port=htons(60000);

		SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		int socketTimeout = 1000;
		if(::setsockopt(s, SOL_SOCKET, SO_SNDTIMEO, (char *)&socketTimeout,sizeof(socketTimeout)) == SOCKET_ERROR){
			return -1;
		}
		
		if (connect(s, (sockaddr*)&server, sizeof(server)))
		{
			return -2;
		}
		char buf[512];
		ClientUtils::sendData(s, 1);
		ClientUtils::receiveData(s, buf, 512);
		printf("%s", buf);
		ClientUtils::sendData(s, 1000);
		ClientUtils::receiveData(s, buf, 512);
		printf("%s", buf);

		// 看是否Ready
// 		ClientUtils::receiveData(s, buf, 512);
// 		printf("%s", buf);
// 		cout << strcmp(buf, "Ready") << endl;
// 
// 		int i;
// 		ClientUtils::receiveData(s, i);
// 		printf("%d", i);

		ClientUtils::sendData(s, "quit");
		ClientUtils::receiveData(s, buf, 512);
		printf("%s", buf);

		closesocket(s);
		WSACleanup();
	}

	return nRetCode;
}


