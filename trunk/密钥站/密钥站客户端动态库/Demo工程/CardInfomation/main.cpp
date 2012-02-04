#include <stdio.h>
#include <iostream.h>
#include "CardReaderClientDll.h"

#pragma comment(lib, "CardReaderClientDll.lib")

int main(void)
{
	// ���ö�����
	Reader* reader = new Reader();
	reader->readerId = 248; // ������id
	
	// ��ȡ������
	if (0 != GetReader(reader, 10000, 10000))
	{
		printf("getReader Failed.");
		return -1;
	}
	
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
		cout << "����汾: " << appVer << ", �ն�����: " << devType << endl;
	}

	// ��ȡоƬid(���ø�λ֮��������, �����)
	{
		char chipID[512] = {0};
		if (0 != GetChipID(reader, chipID, 512))
		{
			printf("GetChipID failed.");
		}
		cout << "оƬid: " << chipID << endl;
	}

	// �鿴������
	{
		int braudRate = 0;
		if (0 != GetCardBraudRate(reader, braudRate))
		{
			printf("ModifyCardBraudRate failed.");
		}
		cout << "������: " << braudRate << endl;
	}
	
	// �ͷ��ڴ�
	delete reader;

	return 0;
}