//////////////////////////////////////////////////////////////////////////
// FileName: ServerParam.cpp
// Creator: icejoywoo
// Date: 2011.12.05
// Comment: 服务器ServerParam类是用来存放配置参数, 类的实现
//////////////////////////////////////////////////////////////////////////
#include "ServerParam.h"

ServerParam* ServerParam::instance = new ServerParam();
ServerParam::ServerParam()
{
	// TODO: 测试使用
	for (int i = 1; i <= 8; ++i)
	{
		readerIdSet.insert(i);
	}
}