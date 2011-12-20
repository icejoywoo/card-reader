//////////////////////////////////////////////////////////////////////////
// FileName: Handlers.h
// Creator: icejoywoo
// Date: 2011.12.05
// Comment: ���������̶߳���
//////////////////////////////////////////////////////////////////////////
#ifndef _HANDLERS_H_
#define _HANDLERS_H_

#include "StdAfx.h"

/**
 * @brief ��¼��־���߳�
 * @param 
 *	pParam δʹ��
 */
UINT logHandler(LPVOID pParam);

// /**
//  * @brief ���½����е�CTreeCtrl�ؼ�, ���ݵ�ǰ�Ŀͻ�������ʾ
//  * @param
//  *	pParam	�ؼ�����
//  */
// UINT updateTree(LPVOID pParam); // ������ʾ��

/************************************************************************/
/* Ĭ�Ϸ�������handlers                                                 */
/************************************************************************/

/**
 * @brief Ĭ�ϵ�������
 * @param 
 *	pParam	serverʵ��
 */
UINT defaultServerHandler (LPVOID pParam );

/**
 * @brief ����������еĵȴ�����
 * @param 
 *	pParam	δʹ��
 * 
 * ѭ���ȴ�, ֱ���������еĵȴ�����������Ҫ���������<br/>
 * ÿ����������Ӧһ���������, ÿ��ÿ����������ֻ�ܴ���һ������
 */
UINT defaultWaitListHandler (LPVOID pParam );

/**
 * @brief ����������е�timeout����
 * @param 
 *	pParam	δʹ��
 * 
 * ѭ���ȴ�, �鿴�ͻ��˵���ʱʱ���Ƿ��ѵ�, ��ʱʱ�䵽����Զ��ر�
 */
UINT defaultTimeoutListHandler (LPVOID pParam );

/**
 * @brief Ĭ�ϵ�������
 * @param 
 *	pParam	����Ķ�������cardId
 */
UINT defaultClientHandler (LPVOID pParam );

/**
 * @brief  ���Ե���������, �����ַ���"Hello", just for test!!!
 * @param 
 *	pParam	�ͻ��������socket
 */
UINT helloClientHandler (LPVOID pParam);

#endif