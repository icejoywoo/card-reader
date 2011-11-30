// ReaderServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ReaderServer.h"
#include "Reader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;
//////////////////////////////////////////////////////////////////////////
// global variables declaration
//////////////////////////////////////////////////////////////////////////
#define TIMEOUT (1000)
SOCKET server; // server socket
CardReader cardReader[READER_COUNT]; // simulated card-reader
HANDLE mutex; // 保证输出的时候独有cout对象

//////////////////////////////////////////////////////////////////////////
// function declaration
//////////////////////////////////////////////////////////////////////////

// client-served thread
UINT ClientThread(LPVOID pParam);


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
		// TODO: code your application's behavior here.
///////////////////////demo///////////////////////////////////////////////
// 		CString strHello;
// 		strHello.LoadString(IDS_HELLO);
// 		cout << (LPCTSTR)strHello << endl;
// 		AfxMessageBox(strHello);
//////////////////////////////////////////////////////////////////////////
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2,2), &wsaData))
		{
			return EXIT_FAILURE;
		}
		cout << "Press ESCAPE to terminate program\n";
		int i;
		for (i = 0; i < READER_COUNT; ++i)
		{
			cardReader[i].reader = new Reader(i);
			cardReader[i].hMutex = CreateMutex(NULL, FALSE, NULL);
		}
		
		sockaddr_in local;
		local.sin_family = AF_INET;
		local.sin_addr.s_addr = INADDR_ANY;
		local.sin_port = htons(20248);
		// socket -> bind -> listen -> accept
		if ((server = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		{
			return EXIT_FAILURE;
		}
		
		if (bind(server, (sockaddr*)&local, sizeof(local)) != 0)
		{
			AfxMessageBox("端口已经被占用");
			return EXIT_FAILURE;
		}
		
		if (listen(server, 64) != 0)
		{
			return EXIT_FAILURE;
		}

		SOCKET client;
		sockaddr_in from;
		int fromlen = sizeof(from);
		SimpleLog::info("Server Ready");
		while (true)
		{
			client = accept(server, (struct sockaddr*) &from, &fromlen);
			//WaitForSingleObject(mutex, TIMEOUT);
			SimpleLog::info(CString("接收到一个客户端请求, 来自") + inet_ntoa(from.sin_addr));
			//ReleaseMutex(mutex);
			AfxBeginThread(ClientThread, (LPVOID)&client);
		}

		while (_getch() != 27) ;
		closesocket(server);
		WSACleanup();
	}

	return nRetCode;
}

UINT ClientThread(LPVOID pParam)
{
	SOCKET client = *((SOCKET*) pParam);

	char buff[512];
	
	WaitForSingleObject(mutex, TIMEOUT);
	int i;
	for (i = 0; i < READER_COUNT; ++i)
	{
		// receive the request of client, get the reader ID
		int size = recv(client, buff, 512, 0);
		buff[size] = '\0';
		int id = atoi(buff);
		if (size == -1)
		{
			id = -1;
			AfxMessageBox("数据接收失败");
			SimpleLog::error(CString("[数据接收失败]") + CString("接收数据, 长度: ") + i2str(size) + ", 数据: id:" + i2str(id));
		} else {
			SimpleLog::info(CString("接收数据, 长度: ") + i2str(size) + ", 数据: id:" + i2str(id));
		}
		
		memset(buff, 0, 512);
		if  (id >= 0 && id < READER_COUNT)
		{	
			WaitForSingleObject(cardReader[id].hMutex, TIMEOUT);
			int data = cardReader[id].reader->GetData();
			sprintf(buff, "%d", data);
			int size = send(client, buff, strlen(buff), 0);
			if (size == -1) {
				AfxMessageBox("数据发送失败");
				SimpleLog::error(CString("数据发送失败"));
			} else {
				SimpleLog::info(CString("发送数据, 长度: ") + i2str(size) + ", 数据: " + buff);
			}
			ReleaseMutex(cardReader[id].hMutex);
			memset(buff, 0, 512);
		} else {
			sprintf(buff, "The input id is wrong.");
			int size = send(client, buff, strlen(buff), 0);
			if (size == -1) {
				AfxMessageBox("数据发送失败");
				SimpleLog::error(CString("数据发送失败"));
			} else {
				SimpleLog::info(CString("发送数据, 长度: ") + i2str(size) + ", 数据: " + buff);
			}
			
			memset(buff, 0, 512);
			break;
		}
	} 
	ReleaseMutex(mutex);
	shutdown(client, SD_SEND);
	Sleep(1000);
	closesocket(client);

	return 0;
}