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
 * ��������mutex��ɵĽṹ��, ģ�⻥����ʶ�����
 */
typedef struct _CardReader{
	/// ������
	Reader* reader;
	/// �ȴ��������
	HANDLE hMutex; 
} CardReader, *p_CardReader;

CardReader cardReader[READER_COUNT];
HANDLE hThread[CLIENT_COUNT];
HANDLE mutex = CreateMutex(NULL, FALSE, NULL);
//////////////////////////////////////////////////////////////////////////
// ȫ�ֺ�������
//////////////////////////////////////////////////////////////////////////

/**
 * @brief ��ʼ��reader��hThread
 * @return None
 */
void init(); 

/**
 * @brief �̶߳�Ӧ�ĺ���
 * @param lpParameter ��ֵ���߳�
 * @return DWORD
 */
DWORD WINAPI ThreadProc(LPVOID lpParameter);

/**
 * ������
 */
int main(void)
{
	int* order = randStr(READER_COUNT);
	printArray(order, READER_COUNT);

	init();
	WaitForMultipleObjects(CLIENT_COUNT, hThread, TRUE, INFINITE); /// �ȴ������߳̽���
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// ȫ�ֺ�������
//////////////////////////////////////////////////////////////////////////
void init()
{
	// ��ʼ��reader�ṹ��
	int i;
	for (i = 0; i < READER_COUNT; i++)
	{
		cardReader[i].reader = new Reader(i);
		// ��ʼ��������
		cardReader[i].hMutex = CreateMutex(NULL, FALSE, NULL);
		if (cardReader[i].hMutex)
		{
			// ������
			if(ERROR_ALREADY_EXISTS == GetLastError())
			{
				cerr << "only one instance can run!" << endl;
			} // end if(ERROR_ALREADY_EXISTS == GetLastError())
		} // end if (reader[i].hMutex)
	}// end for (i = 0; i < READER_COUNT; i++)
	
	// ��ʼ��hThread
	for (i = 0; i < CLIENT_COUNT; i++)
	{
		hThread[i] = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
		if (hThread[i] == NULL) 
		{
			cout << "Create thread failed: " << GetLastError() << endl;
		}
	} // end for (i = 0; i < CLIENT_COUNT; i++)
	
	// �ͷ�����mutex
// 	for (i = 0; i < READER_COUNT; i++)
// 	{
// 		ReleaseMutex(reader[i].hMutex);
// 	} // end for (i = 0; i < READER_COUNT; i++)
}

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	UNREFERENCED_PARAMETER(lpParameter);
	// ���ö�������˳��
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
				// �ͷŻ�����, �ͷŲ��ɹ�, Exception handler 
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

