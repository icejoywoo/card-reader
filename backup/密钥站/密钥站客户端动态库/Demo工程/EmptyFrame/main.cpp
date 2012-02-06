#include <stdio.h>
#include <iostream.h>
#include "CardReaderClientDll.h"

#pragma comment(lib, "CardReaderClientDll.lib")

int main(void)
{
	// ÅäÖÃ¶Á¿¨Æ÷
	Reader* reader = new Reader();
	reader->readerId = 248; // ¶Á¿¨Æ÷id
	
	// »ñÈ¡¶Á¿¨Æ÷
	if (0 != GetReader(reader, 10000, 10000))
	{
		printf("getReader Failed.");
		return -1;
	}
	
	// ½øÐÐ¶Á¿¨Æ÷µÄ²Ù×÷...
	cout << "µÈ´ý²Ù×÷¶Á¿¨Æ÷..." << endl;
	
	// ÊÍ·Å¶Á¿¨Æ÷
	if (0 != ReleaseReader(reader))
	{
		printf("ReleaseReader Failed.");
	}
	
	// ÊÍ·ÅÄÚ´æ
	delete reader;

	return 0;
}