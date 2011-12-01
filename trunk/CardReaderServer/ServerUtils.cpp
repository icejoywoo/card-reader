#include "ServerUtils.h"

ServerParam* ServerParam::instance = new ServerParam();

void appendTextToEdit(CEdit &mEdit, CString text)
{
	int len = mEdit.GetWindowTextLength();
	mEdit.SetSel(len,len);
	CString m_sCurrentTime = CTime::GetCurrentTime().Format("[%Y-%m-%d %X]");
	CString log = m_sCurrentTime + ": " + text;
    mEdit.ReplaceSel(log);
}

CString i2str(int a)
{
	CString str;
	str.Format("%d", a);
	return str;
}

UINT logHandler (LPVOID pParam)
{
	while (TRUE)
	{
		if (!Server::getInstance()->log.IsEmpty())
		{
			CEdit* logWindow = (CEdit*) pParam;
			int len = logWindow->GetWindowTextLength();
			logWindow->SetSel(len,len);
			logWindow->ReplaceSel(Server::getInstance()->log);
			Server::getInstance()->log = ""; // 清空日志
		}
		Sleep(500);
	}
	
	return 0;
}

CString formatLog(CString log)
{
	CString time;
	CString m_sCurrentTime = CTime::GetCurrentTime().Format("[%Y-%m-%d %X]");
	return m_sCurrentTime + ": " + log + "\r\n";
}

void GetIpAndPort(CString& ip, int& port, int id, ServerParam* param)
{
	// 每个ip对应32个读卡器, 每个读卡器对应一个port, port默认从10000开始
	const int defaultPort = 10000;
	if(id<=32&&id>=1)
	{
        ip=param->ip1;
		port=defaultPort+id;
	}
	else if(id>32&&id<=64)
	{
		ip=param->ip2;
		port=defaultPort+id-32;
	}
	else if(id>64&&id<96)
	{
		ip=param->ip3;
		port=defaultPort+id-64;
	}
	else if(id>96&&id<128)
	{
		ip=param->ip4;
		port=defaultPort+id-96;
	}
}

CString getIpAdress(CIPAddressCtrl& ip)
{
	BYTE b[4];
	ip.GetAddress(b[0], b[1], b[2], b[3]);
	CString result;
	result.Format("%d.%d.%d.%d", b[0], b[1], b[2], b[3]);
	return result;
}