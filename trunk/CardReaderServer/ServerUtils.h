#ifndef _SERVER_UTILS_H_
#define _SERVER_UTILS_H_

#include "StdAfx.h"

/**
 * @brief ��CEdit��ĩβ��Ӽ�¼
 * @return None
 */
void appendTextToEdit(CEdit &mEdit, CString text);

// ��intת��ΪCString
CString i2str(int a);

// ��¼��־���߳�
UINT logHandler (LPVOID pParam);

// ����־ǰ��ʱ��
CString formatLog(CString log);


#endif