#include "StdAfx.h"

#define COMMUNICATOR_EXPORTS_MACRO

#include "Communicator.h"
#include "ContactManager.h"
#include "CustomConsts.h"

__declspec(dllexport) Communicator::Communicator()
{
	m_nCommtype=NOT_CONNECT;
	tcpClientConn=0;
	udpConn=0;
	comConn=0;
	waitTimeForGetComm=2000;
}