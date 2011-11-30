#include "ServerUtils.h"


/**
 * @brief ��CEdit��ĩβ��Ӽ�¼
 * @return None
 */
void appendTextToEdit(CEdit &mEdit, CString text)
{
	int len = mEdit.GetWindowTextLength();
	mEdit.SetSel(len,len);
	CString m_sCurrentTime = CTime::GetCurrentTime().Format("%Y-%m-%d %X");
	CString log = CString("[") + m_sCurrentTime + "]: " + text;
    mEdit.ReplaceSel(log);
}

// ��intת��ΪCString
CString i2str(int a)
{
	CString str;
	str.Format("%d", a);
	return str;
}