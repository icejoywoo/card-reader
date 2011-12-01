#include "ServerUtils.h"


/**
 * @brief ��CEdit��ĩβ��Ӽ�¼
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

// ��intת��ΪCString
CString i2str(int a)
{
	CString str;
	str.Format("%d", a);
	return str;
}

// ��¼��־���߳�
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
			Server::getInstance()->log = ""; // �����־
		}
		Sleep(500);
	}
	
	return 0;
}

// ����־ǰ��ʱ��
CString formatLog(CString log)
{
	CString time;
	CString m_sCurrentTime = CTime::GetCurrentTime().Format("[%Y-%m-%d %X]");
	return m_sCurrentTime + ": " + log + "\r\n";
}

