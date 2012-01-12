// Demo2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Demo2.h"
#include "DataTransfer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

int main(int argc, TCHAR* argv[], TCHAR* envp[])
{
	DataTransfer transfer;
	
	TransferRule rule1;
	rule1.SetStart(POSITION_TYPE, "0");
	rule1.SetEnd(POSITION_TYPE, "2");
	rule1.SetTag("BANKCODE");
	transfer.AddRule(rule1);
	
	TransferRule rule2;
	rule2.SetStart(POSITION_TYPE, "2");
	rule2.SetEnd(LENGTH_TYPE, "40");
	rule2.SetTag("FEEDBACKNAME");
	transfer.AddRule(rule2);

	TransferRule rule3;
	rule3.SetStart(POSITION_TYPE, "42");
	rule3.SetEnd(LENGTH_TYPE, "9");
	rule3.SetTag("OCR1");
	transfer.AddRule(rule3);

	TransferRule rule4;
	rule4.SetStart(POSITION_TYPE, "51");
	rule4.SetEnd(LENGTH_TYPE, "18");
	rule4.SetTag("OCR2");
	transfer.AddRule(rule4);

	TransferRule rule5;
	rule5.SetTag("OCR3");
	transfer.AddRule(rule5);

	TransferRule rule6; // 不设置的情况下, 不截取任何数据, 数据为空
	rule6.SetTag("ENC1");
	transfer.AddRule(rule6);

	TransferRule rule7;
	rule7.SetStart(POSITION_TYPE, "69");
	rule7.SetEnd(LENGTH_TYPE, "40");
	rule7.SetTag("ENC2");
	transfer.AddRule(rule7);

	TransferRule rule8;
	rule8.SetStart(POSITION_TYPE, "109");
	rule8.SetEnd(LENGTH_TYPE, "107");
	rule8.SetTag("ENC3");
	transfer.AddRule(rule8);

	TransferRule rule9;
	rule9.SetStart(TAG_TYPE, "$$"); // 不设置结束, 表示一直截取到行尾
	rule9.SetTag("IC-DATA");
	transfer.AddRule(rule9);
	
	// Simple Test 简单测试成功
	
	// test Handle (推荐使用) [测试使用文件: CQJRSB-200907100031-交通银行-ICInfo-test 行数 20011]
//	transfer.Handle("CQJRSB-200907100031-交通银行-ICInfo-test");
//	transfer.Handle("重庆金融社保IC卡-0110-ICInfo");
//	transfer.Handle("F:\\明森\\card-reader\\DataTransfer\\Demo2\\重庆金融社保IC卡-0110-ICInfo");

	// 保存配置
// 	transfer.init();
// 	transfer.save("Test");
	// 加载配置
//	transfer.load("Test");
//	transfer.Handle("重庆金融社保IC卡-0110-ICInfo");
	// 删除配置
	transfer.del("Test");

	return 0;
}


