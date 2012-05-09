#include <cstdio>
#include <sstream>
#include <string>
#include <iostream>
#include <cmath>
#include <time.h>
#include "CardReaderClientDll.h"

using namespace std;

#pragma comment(lib, "CardReaderClientDll.lib")

#define readerNum (4)
#define ThreadNum (1)

int errors = 0;
int okNumber = 0;
int errorNumber = 0;

DWORD WINAPI ReaderTestThread(LPVOID lpParam);
int operateReader(int readerId);

int main(int argc, char* args[])
{
	HANDLE threads[ThreadNum];
	for (int i = 0; i < ThreadNum; ++i)
	{
		DWORD threadId;
		threads[i] = CreateThread(NULL, 0, ReaderTestThread, 0, 0, &threadId);
	}

	WaitForMultipleObjects(ThreadNum, threads, TRUE, INFINITE);
	cout << "Errors: " << errors << endl;
	cout << "OK: " << okNumber << ", ERROR: " << errorNumber << endl;
	return 0;
}

DWORD WINAPI ReaderTestThread(LPVOID lpParam)
{
	UNREFERENCED_PARAMETER(lpParam); // δʹ�õĲ���
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 1; j <= readerNum; ++j)
		{
			if (0 == operateReader(j) )
				++okNumber;
			else 
				++errorNumber;
		}
	}
	return 0;
}

int operateReader(int readerId)
{
	// ���ö�����
	Reader* reader = new Reader();
	reader->readerId = readerId;

	// ��ȡ������
	if (0 != GetReader(reader, 10000, 10000))
	{
		printf("ERROR: GetReader Failed, reader -> %d.\n", readerId);
		++errors;
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
// 	{
// 		char devID[512] = {0};
// 		int readerId = 0;
// 		if (0 != GetDevIDAndReaderId(reader, devID, 512, readerId))
// 		{
// 			printf("GetDevIDAndReaderId Failed.");
// 		}
//  		cout << devID << ", " << readerId << endl;
// 	}

	// ��ȡ����汾���ն�����
// 	{
// 		char appVer[512] = {0};
// 		char devType[512] = {0};
// 		if (0 != GetAppVerAndDevType(reader, appVer, 512, devType, 512))
// 		{
// 			printf("GetAppVerAndDevType Failed.");
// 		}
// 		cout << appVer << ", " << devType << endl;
// 	}

	// ��ȡоƬid(���ø�λ֮��������, �����)
// 	{
// 		char chipID[512] = {0};
// 		if (0 != GetChipID(reader, chipID, 512))
// 		{
// 			printf("GetChipID failed.");
// 		}
// 		cout << chipID << endl;
// 	}

	// ���A����B�����Ƿ��п�
// 	{
// 		int cardA = -1;
// 		int cardB = -1;
// 		if (0 != IsCardReady(reader, cardA, cardB))
// 		{
// 			printf("IsCardReady failed.");
// 		}
// 		cout << cardA << ", " << cardB << endl;
// 	}
	
	// ��λӦ��
	{
		SmartCom::string retCode = "empty";
		if (0 != ResetCard(reader, retCode))
		{
			printf("ResetCard failed, reader -> %d.\n", readerId);
			++errors;
		}
		cout << "Reader -> " << readerId <<", ��λӦ�� -> " << retCode.c_str() << endl;
	}

	// ִ�е�������(ִ��ǰ��Ҫ�ȸ�λӦ��)
	{
		SmartCom::string retCode = "empty";
		char* apdu = "00820000083132333435363738";
		if (0 != CardApdu(reader, apdu, retCode, 1))
		{
			printf("CardApdu failed, reader -> %d.\n", readerId);
			++errors;
			return -1;
		}
		cout << "Reader -> " << readerId << ", apdu -> " << apdu << ", ret -> " << retCode.c_str() << endl;
	}
	{
		SmartCom::string retCode = "empty";
		char* apdu = "00A4000002EF05";
		if (0 != CardApdu(reader, apdu, retCode, 1))
		{
			printf("CardApdu failed, reader -> %d.\n", readerId);
			++errors;
			return -1;
		}
		cout << "Reader -> " << readerId << ", apdu -> " << apdu << ", ret -> " << retCode.c_str() << endl;
	}
	{
		SmartCom::string retCode = "empty";
		char* apdu = "00A4000002DDF1";
		if (0 != CardApdu(reader, apdu, retCode, 1))
		{
			printf("CardApdu failed, reader -> %d.\n", readerId);
			++errors;
			return -1;
		}
		cout << "Reader -> " << readerId << ", apdu -> " << apdu << ", ret -> " << retCode.c_str() << endl;
	}
	{
		SmartCom::string retCode = "empty";
		char* apdu = "00B2020420";
		if (0 != CardApdu(reader, apdu, retCode, 1))
		{
			printf("CardApdu failed, reader -> %d.\n", readerId);
			++errors;
			return -1;
		}
		cout << "Reader -> " << readerId << ", apdu -> " << apdu << ", ret -> " << retCode.c_str() << endl;
	}
	{
		SmartCom::string retCode = "empty";
		char* apdu = "0084000008";
		if (0 != CardApdu(reader, apdu, retCode, 1))
		{
			printf("CardApdu failed, reader -> %d.\n", readerId);
			++errors;
			return -1;
		}
		cout << "Reader -> " << readerId << ", apdu -> " << apdu << ", ret -> " << retCode.c_str() << endl;
	}

	// �޸Ĳ�����
// 	{
// 		if (0 != ModifyCardBraudRate(reader, 1))
// 		{
// 			printf("ModifyCardBraudRate failed.");
// 		}
// 	}

	// �鿴������
// 	{
// 		int braudRate = 0;
// 		if (0 != GetCardBraudRate(reader, braudRate))
// 		{
// 			printf("ModifyCardBraudRate failed.");
// 		}
// 		cout << braudRate << endl;
// 	}

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
// 	{
// 		SmartCom::string strData = "empty";
// 		if (0 != GetScriptData(reader, 0, 128, strData))
// 		{
// 			printf("GetScriptDataʧ��\n");
// 		}
// 		cout << strData.c_str() << endl;
// 	}

	// ִ�ж���apdu(��Ҫ�������ļ�)
// 	{
// 		int ret = ExcuteMulAPDU(reader, 5);
// 		if (0 != ret) // ����ͷ�ļ�
// 		{
// 			printf("ExcuteMulAPDUʧ��\n");
// 		}
// 	}

	// CheckBatchResult
// 	{
// 		SmartCom::string retCode = "empty"; // ״̬������
// 		int result = -1000; // ��ִ�е�����
// 		if ((result = CheckBatchResult(reader, retCode)) < 0)
// 		{
// 			printf("CheckBatchResultʧ��\n");
// 		}
// 		cout << result << "ִ��," <<retCode.c_str() << endl;
// 	}

	// ��Ƭ�µ�
	{
		if (0 != ShutdownCard(reader))
		{
			printf("ShutdownCard failed, reader -> %d.\n", readerId);
			++errors;
			return -1;
		}
	}

	// �ͷŶ�����
	if (0 != ReleaseReader(reader))
	{
		printf("ReleaseReader Failed, reader -> %d.\n", readerId);
		++errors;
		return -1;
	}
	
	delete reader; // �ͷ��ڴ�
	return 0;
}