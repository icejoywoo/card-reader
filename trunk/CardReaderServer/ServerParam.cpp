//////////////////////////////////////////////////////////////////////////
// FileName: ServerParam.cpp
// Creator: icejoywoo
// Date: 2011.12.05
// Comment: ������ServerParam��������������ò���, ���ʵ��
//////////////////////////////////////////////////////////////////////////
#include "ServerParam.h"

ServerParam* ServerParam::instance = new ServerParam();
ServerParam::ServerParam()
{
	// TODO: ����ʹ��
	readerIdSet.insert(1);
	readerIdSet.insert(2);
	readerIdSet.insert(3);
	readerIdSet.insert(4);

	// ����Ĭ�ϵ�split����
	split.SetSplitFlag(",");
	split.SetSequenceAsOne(TRUE);
}