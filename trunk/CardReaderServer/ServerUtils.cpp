#include "ServerUtils.h"


/**
 * @brief 向CEdit中末尾添加记录
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

// 将int转换为CString
CString i2str(int a)
{
	CString str;
	str.Format("%d", a);
	return str;
}