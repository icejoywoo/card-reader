//////////////////////////////////////////////////////////////////////////
// FileName: Handlers.h
// Creator: icejoywoo
// Date: 2011.12.05
// Comment: 服务器的线程定义
//////////////////////////////////////////////////////////////////////////
#ifndef _HANDLERS_H_
#define _HANDLERS_H_

#include "StdAfx.h"

/**
 * @brief 记录日志的线程
 * @param 
 *	pParam 未使用
 */
UINT logHandler(LPVOID pParam);

/************************************************************************/
/* 默认服务器的handlers                                                 */
/************************************************************************/

/**
 * @brief 默认的请求处理
 * @param 
 *	pParam	server实例
 */
UINT defaultServerHandler (LPVOID pParam );

/**
 * @brief 处理服务器中的等待队列
 * @param 
 *	pParam	未使用
 * 
 * 循环等待, 直到服务器中的等待队列中有需要处理的请求<br/>
 * 每个读卡器对应一个请求队列, 每次每个读卡器都只能处理一个请求
 */
UINT defaultWaitListHandler (LPVOID pParam );

/**
 * @brief 默认的请求处理
 * @param 
 *	pParam	请求的读卡器号cardId
 */
UINT defaultClientHandler (LPVOID pParam );

/**
 * @brief  测试的请求处理器, 回显字符串"Hello", just for test!!!
 * @param 
 *	pParam	客户端请求的socket
 */
UINT helloClientHandler (LPVOID pParam);

#endif