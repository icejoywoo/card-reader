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
	// ����Ĭ�ϵ�split����
	split.SetSplitFlag(",");
	split.SetSequenceAsOne(TRUE);
}