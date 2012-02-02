#include <cstdio>
#include <sstream>
#include <string>
#include <iostream>
#include <cmath>
#include <time.h>
#include "CardReaderClientDll.h"

using namespace std;

#pragma comment(lib, "CardReaderClientDll.lib")

#define readerNum (8)
#define ThreadNum (1)

DWORD WINAPI ReaderTestThread(LPVOID lpParam);

int main(int argc, char* args[])
{
	HANDLE threads[ThreadNum];
	for (int i = 0; i < ThreadNum; ++i)
	{
		DWORD threadId;
		threads[i] = CreateThread(NULL, 0, ReaderTestThread, 0, 0, &threadId);
		//cout << floor(rand() % (readerNum) + 1) << endl;
	}

	WaitForMultipleObjects(ThreadNum, threads, TRUE, INFINITE);
	
	return 0;
}

DWORD WINAPI ReaderTestThread(LPVOID lpParam)
{
	UNREFERENCED_PARAMETER(lpParam); // δʹ�õĲ���
	
	// ���ö�����
	Reader* reader = new Reader();
	//reader->readerId = floor(rand() % (readerNum) + 1); // ���������id
	reader->readerId = 5;
	char log[512];
	sprintf(log, "������id %d\n", reader->readerId);
	OutputDebugString(log);

//	InitClient("127.0.0.1", 60000);

	// ��ȡ������
	if (0 != GetReader(reader, 10000, 10000))
	{
		printf("getReader Failed.");
		return -1;
	}


	// �޸Ķ�����id
// 	{
// 		char devID[512];
// 		int readerId;
// 		if (0 != GetDevIDAndReaderId(reader, devID, 512, readerId))
// 		{
// 			printf("GetDevIDAndReaderId Failed.");
// 		}
// 		cout << devID << ", " << readerId << endl;
// 	
// 		
// 		if (0 != SetReaderIdByDevID(reader, devID, 4))
// 		{
// 			printf("SetReaderIdByDevID Failed.");
// 		}
// 	}
	
	// ��ȡ������id
	{
		char devID[512] = {0};
		int readerId = 0;
		if (0 != GetDevIDAndReaderId(reader, devID, 512, readerId))
		{
			printf("GetDevIDAndReaderId Failed.");
		}
 		cout << devID << ", " << readerId << endl;
	}

	// ��ȡ����汾���ն�����
	{
		char appVer[512] = {0};
		char devType[512] = {0};
		if (0 != GetAppVerAndDevType(reader, appVer, 512, devType, 512))
		{
			printf("GetAppVerAndDevType Failed.");
		}
		cout << appVer << ", " << devType << endl;
	}

	// ��ȡоƬid(���ø�λ֮��������, �����)
	{
		char chipID[512] = {0};
		if (0 != GetChipID(reader, chipID, 512))
		{
			printf("GetChipID failed.");
		}
		cout << chipID << endl;
	}

	// ���A����B�����Ƿ��п�
	{
		int cardA = -1;
		int cardB = -1;
		if (0 != IsCardReady(reader, cardA, cardB))
		{
			printf("IsCardReady failed.");
		}
		cout << cardA << ", " << cardB << endl;
	}
	
	// ��λӦ��
	{
		SmartCom::string retCode = "empty";
		if (0 != ResetCard(reader, retCode))
		{
			printf("ResetCard failed.");
		}
		cout << "��λӦ��:" << retCode.c_str() << endl;
	}

	// ִ�е�������(ִ��ǰ��Ҫ�ȸ�λӦ��)
	{
		SmartCom::string retCode = "empty";
		char* apdu = "00820000083132333435363738";
		if (0 != CardApdu(reader, apdu, retCode, 1))
		{
			printf("CardApdu failed.");
		}
		cout << retCode.c_str() << endl;
	}

	// �޸Ĳ�����
// 	{
// 		if (0 != ModifyCardBraudRate(reader, 1))
// 		{
// 			printf("ModifyCardBraudRate failed.");
// 		}
// 	}

	// �鿴������
	{
		int braudRate = 0;
		if (0 != GetCardBraudRate(reader, braudRate))
		{
			printf("ModifyCardBraudRate failed.");
		}
		cout << braudRate << endl;
	}

	// �޸ĵ�Դ
// 	{
// 		if (0 != ModifyCardPower(reader, 1))
// 		{
// 			printf("ModifyCardBraudRate failed.");
// 		}
// 	}
	
	// �����洢��
// 	{
// 		if (0 != ClearMem(reader)) 
// 		{
// 			printf("�����洢��ʧ��\n");
// 		}
// 	}

	// �����ļ�(Attention:�ļ�Ӧ�÷��ڷ������˵�, �����ļ�֮ǰ�Ȳ����洢��)
// 	{
// 		if (0 != DownloadFile(reader, 2, "apdu_head.bin")) // ����ͷ�ļ�
// 		{
// 			printf("����ͷ�ļ�ʧ��\n");
// 		}
// 		if (0 != DownloadFile(reader, 1, "apdu_body.bin")) // �������ļ�
// 		{
// 			printf("�������ļ�ʧ��\n");
// 		}
// 	}
	
	// ��ȡ�ű�����(��Ҫ�������ļ�)
	{
		SmartCom::string strData = "empty";
		if (0 != GetScriptData(reader, 0, 128, strData))
		{
			printf("GetScriptDataʧ��\n");
		}
		cout << strData.c_str() << endl;
	}

	// ִ�ж���apdu(��Ҫ�������ļ�)
	{
		int ret = ExcuteMulAPDU(reader, 5);
		if (0 != ret) // ����ͷ�ļ�
		{
			printf("ExcuteMulAPDUʧ��\n");
		}
	}

	// CheckBatchResult
	{
		SmartCom::string retCode = "empty"; // ״̬������
		int result = -1000; // ��ִ�е�����
		if ((result = CheckBatchResult(reader, retCode)) < 0)
		{
			printf("CheckBatchResultʧ��\n");
		}
		cout << result << "ִ��," <<retCode.c_str() << endl;
	}

	// ��Ƭ�µ�
	{
		if (0 != ShutdownCard(reader))
		{
			printf("ShutdownCard failed.");
		}
	}

	// �ͷŶ�����
	if (0 != ReleaseReader(reader))
	{
		printf("ReleaseReader Failed.");
	}
	
//	CleanUpClient();
	delete reader; // �ͷ��ڴ�

	return 0;
}