// SimpleLog.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SimpleLog.h"

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
		// TODO: code your application's behavior here.
		CString strHello;
		strHello.LoadString(IDS_HELLO);
		cout << (LPCTSTR)strHello << endl;
		SimpleLog::warn("警告你了");
		SimpleLog::info("你有新消息了");
		SimpleLog::error("你又错了");
		Sleep(100);
		SimpleLog::warn("警告你了");
		SimpleLog::info("你有新消息了");
		SimpleLog::error("你又错了");
		Sleep(100);
		SimpleLog::warn("警告你了");
		SimpleLog::info("你有新消息了");
		SimpleLog::error("你又错了");
		//cout << SimpleLog::GetlogFileLocation() << endl;
		WinExec(CString("notepad ") + SimpleLog::GetlogFileLocation(), SW_SHOWNORMAL);
	}
	
	return nRetCode;
}


