#include <cstdio>
#include "CardReaderClientDll.h"

#pragma comment(lib, "CardReaderClientDll.lib")

int main(void)
{
	int   number   =   12345;  
	char   string[25];  
	
	itoa(number,   string,   10);  
	printf( "integer   =   %d   string   =   %s\n ",   number,   string);  
    return   0;   

	Reader reader;
	reader.readerId = 1;

	InitClient("127.0.0.1", 60000);

	if (0 != GetReader(reader, 1000, 1000))
	{
		printf("getReader Failed.");
	}
	char devID[512];
	int readerId;
	if (0 != GetDevIDAndReaderId(reader, devID, 512, readerId))
	{
		printf("GetDevIDAndReaderId Failed.");
	}
	
	if (0 != ReleaseReader(reader))
	{
		printf("ReleaseReader Failed.");
	}

	CleanUpClient();

	return 0;
}