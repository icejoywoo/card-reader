// ReaderClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ReaderClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////////////////////////////////
// global variables declaration


#define TIMEOUT (1000)
SOCKET client[CLIENT_COUNT]; // the sockets of client
HANDLE hThread[CLIENT_COUNT];
HANDLE mutex; // 保证独有cout
struct sockaddr_in server;

//////////////////////////////////////////////////////////////////////////
// function declaration
// client-side thread
UINT ClientThread(LPVOID pParam);
// 将int转换为CString
CString i2str(int a)
{
	CString str;
	str.Format("%d", a);
	return str;
}
/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
	mutex = CreateMutex(NULL, FALSE, NULL);
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
		if (WSAStartup(MAKEWORD(2,2), &wsaData))
		{
			return EXIT_FAILURE;
		}

		// 设置server地址
		struct hostent *hp;
		unsigned int addr;
		const char* servername="127.0.0.1";
		
		if(inet_addr(servername)==INADDR_NONE)
		{
			hp=gethostbyname(servername);
		}
		else
		{
			addr=inet_addr(servername);
			hp=gethostbyaddr((char*)&addr,sizeof(addr),AF_INET);
		}
		server.sin_addr.s_addr=*((unsigned long*)hp->h_addr);
		server.sin_family=AF_INET;
		server.sin_port=htons(20248);

		cout << "Press ESCAPE to terminate program\n";
		int i; // iterator factor

		for (i = 0; i < CLIENT_COUNT; i++)
		{
			client[i] = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			hThread[i] = AfxBeginThread(ClientThread, (LPVOID)client[i]);
		}
		
		// wait for the ESCAPE key
		while (_getch() != 27) ;
		
		// close all client socket 
		for (i = 0; i < CLIENT_COUNT; i++)
		{
			closesocket(client[i]);
			CloseHandle(hThread[i]);
		}
		
		WSACleanup();
	}

	return nRetCode;
}

UINT ClientThread(LPVOID pParam)
{
	SOCKET conn = (SOCKET) pParam;
	
	// 连接服务器
	if (connect(conn, (struct sockaddr*)&server, sizeof(server)))
	{
		closesocket(conn);
		return EXIT_FAILURE;
	}
	SimpleLog::info(CString("连接服务器成功"));
	int i;
	for (i = 0; i < READER_COUNT; ++i)
	{
		char buff[512];
		sprintf(buff, "%d", i); // 发送id
		buff[strlen(buff)] = '\0';
		SimpleLog::info(CString("请求id: ") + buff);
		int size = send(conn, buff, strlen(buff), 0);
		if (size == -1) {
			AfxMessageBox("数据发送失败");
			SimpleLog::error(CString("数据发送失败"));
		} else {
			SimpleLog::info(CString("发送数据, 长度: ") + i2str(size) + ", 数据: " + buff);
		}
		memset(buff, 0, 512);
		size = recv(conn, buff, 512, 0);
		if (size == -1) {
			AfxMessageBox("数据发送失败");
			SimpleLog::error(CString("数据发送失败"));
		} else {
			SimpleLog::info(CString("接收数据, 长度: ") + i2str(size) + ", 数据: " + buff);
		}
	}

	closesocket(conn);
	return EXIT_SUCCESS;
}
