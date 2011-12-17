#include <cstdio>
#include <sstream>
#include <string>
#include <iostream>
#include "CardReaderClientDll.h"

using namespace std;

#pragma comment(lib, "CardReaderClientDll.lib")

string i2str(int a)
{
	char* str = new char[10];
	sprintf(str, "%d", a);
	return string(str);
}

int main(int argc, char* args[])
{
// 	int   number   =   12345;  
// 	char   string[25];  
// 	
// 	itoa(number,   string,   10);  
// 
// 	printf( "integer   =   %d   string   =   %s\n ",   number,   i2str(number).c_str());
// 	return   0;

// 	char* buf = "00 03 00 E7 00 2F 75,1";
// 	char devID[512];
// 	int readerId;
// 	string str(buf);
// 
// 	string::size_type loc = str.find(",", 0);
// 	string first = str.substr(0, loc);
// 	strcpy(devID, first.c_str());
// 	string second = str.substr(loc + 1);
// 	readerId = atoi(second.c_str());
// 	cout << devID << ", " << readerId << endl;
// 	return 0;

	Reader* reader = new Reader();
	reader->readerId = atoi(args[1]);
/*	reader->readerId = 4;*/

	// ��ʼ���ͻ���
	InitClient("127.0.0.1", 60000);

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

	// �����ͻ�����Դ
	CleanUpClient();
	delete reader; // �ͷ��ڴ�

	return 0;
}