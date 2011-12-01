//////////////////////////////////////////////////////////////////////////
// FileName: main.cpp
// Creator : icejoywoo
// Date    : 2011.11.4
// Comment : Just a demo
//////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Reader.h"
#include "utils.h"
#include "Constants.h"

using namespace std;

/**
 * 读卡器和mutex组成的结构体, 模拟互斥访问读卡器
 */
typedef struct _CardReader{
	/// 读卡器
	Reader* reader;
	/// 等待处理队列
	HANDLE hMutex; 
} CardReader, *p_CardReader;

CardReader cardReader[READER_COUNT];
HANDLE hThread[CLIENT_COUNT];
HANDLE mutex = CreateMutex(NULL, FALSE, NULL);
//////////////////////////////////////////////////////////////////////////
// 全局函数声明
//////////////////////////////////////////////////////////////////////////

/**
 * @brief 初始化reader和hThread
 * @return None
 */
void init(); 

/**
 * @brief 线程对应的函数
 * @param lpParameter 传值给线程
 * @return DWORD
 */
DWORD WINAPI ThreadProc(LPVOID lpParameter);

/**
 * 主函数
 */
int main(void)
{
	int* order = randStr(READER_COUNT);
	printArray(order, READER_COUNT);

	init();
	WaitForMultipleObjects(CLIENT_COUNT, hThread, TRUE, INFINITE); /// 等待所有线程结束
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// 全局函数定义
//////////////////////////////////////////////////////////////////////////
void init()
{
	// 初始化reader结构体
	int i;
	for (i = 0; i < READER_COUNT; i++)
	{
		cardReader[i].reader = new Reader(i);
		// 初始化互斥量
		cardReader[i].hMutex = CreateMutex(NULL, FALSE, NULL);
		if (cardReader[i].hMutex)
		{
			// 错误处理
			if(ERROR_ALREADY_EXISTS == GetLastError())
			{
				cerr << "only one instance can run!" << endl;
			} // end if(ERROR_ALREADY_EXISTS == GetLastError())
		} // end if (reader[i].hMutex)
	}// end for (i = 0; i < READER_COUNT; i++)
	
	// 初始化hThread
	for (i = 0; i < CLIENT_COUNT; i++)
	{
		hThread[i] = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
		if (hThread[i] == NULL) 
		{
			cout << "Create thread failed: " << GetLastError() << endl;
		}
	} // end for (i = 0; i < CLIENT_COUNT; i++)
	
	// 释放所有mutex
// 	for (i = 0; i < READER_COUNT; i++)
// 	{
// 		ReleaseMutex(reader[i].hMutex);
// 	} // end for (i = 0; i < READER_COUNT; i++)
}

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	UNREFERENCED_PARAMETER(lpParameter);
	// 调用读卡器的顺序
	// int order[READER_COUNT] = {0, 2, 1, 3};
	int* order = randStr(READER_COUNT);
	
// 	int k;
// 	cout << "randStr: ";
// 	for (k = 0; k < READER_COUNT; k++)
// 	{
// 		cout << order[k] << ", ";
// 	}
// 	cout << endl;

	int j;
	DWORD dwWaitResult;
	for (j = 0; j < READER_COUNT; j++)
	{
		int index = order[j];
		dwWaitResult = WaitForSingleObject(cardReader[index].hMutex, INFINITE);
		switch(dwWaitResult)
		{
		case WAIT_OBJECT_0:
			__try
			{
				WaitForSingleObject(mutex, INFINITE);
				cout << "thread "<< GetCurrentThreadId() << ", reader " << index << ": "<< endl;
				cardReader[index].reader->GetData();
				ReleaseMutex(mutex);
				Sleep(20);
			}
			__finally
			{
				// 释放互斥量, 释放不成功, Exception handler 
				if (!ReleaseMutex(cardReader[index].hMutex))
				{
					cout << "Release Mutex error: " << GetLastError() << endl;
				}
			}
			break;
		default:
			cout << "Get Mutex error: " << GetLastError() << endl;
			return FALSE;
		}
	}// end for (j = 0; j < READER_COUNT; j++)
	WaitForSingleObject(mutex, INFINITE);
	cout << "thread "<< GetCurrentThreadId() << " over" << endl;
	ReleaseMutex(mutex);
	return TRUE;
}

