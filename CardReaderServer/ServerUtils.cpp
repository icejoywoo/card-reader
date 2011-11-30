#include "ServerUtils.h"


/**
 * @brief 向CEdit中末尾添加记录
 * @return None
 */
void appendTextToEdit(CEdit &mEdit, CString text)
{
	int len = mEdit.GetWindowTextLength();
	mEdit.SetSel(len,len);
    mEdit.ReplaceSel(text);
}

// 将int转换为CString
CString i2str(int a)
{
	CString str;
	str.Format("%d", a);
	return str;
}