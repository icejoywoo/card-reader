#include "ServerUtils.h"


/**
 * @brief 向CEdit中末尾添加记录
 * @return None
 */
void appendTextToEdit(CEdit &mEdit, CString text)
{
	int len = mEdit.GetWindowTextLength();
	mEdit.SetSel(len,len);
	CString m_sCurrentTime = CTime::GetCurrentTime().Format("[%Y-%m-%d %X]");
	CString log = m_sCurrentTime + ": " + text;
    mEdit.ReplaceSel(log);
}

// 将int转换为CString
CString i2str(int a)
{
	CString str;
	str.Format("%d", a);
	return str;
}

// 记录日志的线程
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

// 在日志前加时间
CString formatLog(CString log)
{
	CString time;
	CString m_sCurrentTime = CTime::GetCurrentTime().Format("[%Y-%m-%d %X]");
	return m_sCurrentTime + ": " + log + "\r\n";
}

