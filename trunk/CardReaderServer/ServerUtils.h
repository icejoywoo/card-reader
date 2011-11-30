#ifndef _SERVER_UTILS_H_
#define _SERVER_UTILS_H_

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

#endif