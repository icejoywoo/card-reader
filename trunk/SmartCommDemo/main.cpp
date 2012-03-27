#include "SmartCom.h"
#include <iostream.h>
#include <stdio.h>

#pragma comment(lib, "SmartCom")

int main(void)
{
	Communicator communicator;
	if (0 != GetOneCOMCommunicator(communicator, 2))
	{
		cout << "GetOneCOMCommunicatorÊ§°Ü" << endl;
		return -1;
	}

	// »ñÈ¡¶Á¿¨Æ÷id
	{
		char devID[512] = {0};
		int readerId = 0;
		if (0 != GetDevIDAndMacNo(communicator, devID, 512, readerId))
		{
			printf("GetDevIDAndMacNo Failed.");
		}
		cout << devID << ", " << readerId << endl;
	}
	SmartCom::string retCode;
	int ret = ResetCard(communicator, retCode);
	cout << retCode.c_str() << ", " << ret << endl;

	return 0;
}