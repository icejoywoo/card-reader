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
	
	// ��λӦ��
	{
		SmartCom::string retCode = "empty";
		if (0 != ResetCard(reader, retCode))
		{
			printf("ResetCard failed.");
		}
		cout << "��λӦ��:" << retCode.c_str() << endl;
	}
	

	// �����洢��
	{
		if (0 != ClearMem(reader)) 
		{
			printf("�����洢��ʧ��\n");
		}
	}

	// �����ļ�(Attention:�ļ�Ӧ�÷��ڷ������˵�, �����ļ�֮ǰ�Ȳ����洢��)
	{
		if (0 != DownloadFile(reader, 2, "apdu_head.bin")) // ����ͷ�ļ�
		{
			printf("����ͷ�ļ�ʧ��\n");
		}
		if (0 != DownloadFile(reader, 1, "apdu_body.bin")) // �������ļ�
		{
			printf("�������ļ�ʧ��\n");
		}
	}
	
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

	// �����������
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

	// �ͷ��ڴ�
	delete reader;

	return 0;
}