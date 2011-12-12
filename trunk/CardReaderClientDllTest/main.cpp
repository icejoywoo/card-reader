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

int main(void)
{
// 	int   number   =   12345;  
// 	char   string[25];  
// 	
// 	itoa(number,   string,   10);  
// 
// 	printf( "integer   =   %d   string   =   %s\n ",   number,   i2str(number).c_str());
// 	return   0;

	Reader* reader;
	reader->readerId = 1;

	InitClient("127.0.0.1", 60000);

	if (0 != GetReader(reader, 1000, 1000))
	{
		printf("getReader Failed.");
	}
// 	char devID[512];
// 	int readerId;
// 	if (0 != GetDevIDAndReaderId(reader, devID, 512, readerId))
// 	{
// 		printf("GetDevIDAndReaderId Failed.");
// 	}
//  	cout << devID << ", " << readerId << endl;
	Sleep(1000);
	if (0 != ReleaseReader(reader))
	{
		printf("ReleaseReader Failed.");
	}
	Sleep(1000);

/*	CleanUpClient();*/

	return 0;
}