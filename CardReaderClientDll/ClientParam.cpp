//////////////////////////////////////////////////////////////////////////
// FileName: ClientParam.cpp
// Creator: icejoywoo
// Date: 2011.12.05
// Comment: ClientParam用来存放客户端配置参数, ClientParam的实现
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "ClientParam.h"

ClientParam::ClientParam() {}
ClientParam::~ClientParam() {}

ClientParam* ClientParam::instance = new ClientParam();