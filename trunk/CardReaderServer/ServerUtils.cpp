#include "ServerUtils.h"


/**
 * @brief ��CEdit��ĩβ��Ӽ�¼
 * @return None
 */
void appendTextToEdit(CEdit &mEdit, CString text)
{
	int len = mEdit.GetWindowTextLength();
	mEdit.SetSel(len,len);
    mEdit.ReplaceSel(text);
}

// ��intת��ΪCString
CString i2str(int a)
{
	CString str;
	str.Format("%d", a);
	return str;
}