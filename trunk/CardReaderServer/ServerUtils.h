#ifndef _SERVER_UTILS_H_
#define _SERVER_UTILS_H_

#include "StdAfx.h"

/**
 * @brief 向CEdit中末尾添加记录
 * @return None
 */
void appendTextToEdit(CEdit &mEdit, CString text);

// 将int转换为CString
CString i2str(int a);

// 记录日志的线程
UINT logHandler (LPVOID pParam);

// 在日志前加时间
CString formatLog(CString log);


#endif