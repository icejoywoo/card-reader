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
	
	// ���ж������Ĳ���...
	cout << "�ȴ�����������..." << endl;
	
	// �ͷŶ�����
	if (0 != ReleaseReader(reader))
	{
		printf("ReleaseReader Failed.");
	}
	
	// �ͷ��ڴ�
	delete reader;

	return 0;
}