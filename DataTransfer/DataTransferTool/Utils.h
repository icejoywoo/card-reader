#ifndef _UTILS_H_
#define _UTILS_H_
#include "StdAfx.h"
#include "DataTransfer.h"

// �������ݵ��߳�
UINT DataTransferThread(LPVOID pParam);

// ����ת��
CString Convert(CString str, int sourceCodepage, int targetCodepage);

#endif