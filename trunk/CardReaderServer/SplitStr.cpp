//////////////////////////////////////////////////////////////////////////
// FileName: SplitStr.cpp
// Creator: icejoywoo
// Date: 2011.12.2
// $Revision$
// $LastChangedDate$
// Comment: 分割CString字符串的类的实现
//////////////////////////////////////////////////////////////////////////

#include "SplitStr.h"
#include <vector>

using namespace std;

//构造函数
CSplitStr::CSplitStr()
{
	SetData("");
	SetSequenceAsOne(TRUE);
	SetSplitFlag(",");
}

CSplitStr::~CSplitStr()
{
}

//设置文本函数
void CSplitStr::SetData(CString sData)
{
	m_sData = sData;
	m_sData.TrimLeft();
	m_sData.TrimRight();
}

CString CSplitStr::GetData()
{
return m_sData;
}
//切分操作函数（很简单实用吧）
void CSplitStr::GetSplitStrArray(vector<CString> &array)
{
	CString sData = GetData();
	CString sSplitFlag = GetSplitFlag();
	if (sData.Right(1) != sSplitFlag) sData +=sSplitFlag;

	CString sTemp;
	int pos =-1;
	while ((pos=sData.Find(sSplitFlag,0)) != -1)
	{
		sTemp = sData.Left(pos);
		if (!GetSequenceAsOne())
		{
			array.push_back(sTemp);
		}
		else
		{
			if (!sTemp.IsEmpty() && sTemp !="") ////连续的分隔符视为单个处理
			{
				array.push_back(sTemp);
			}
		}
		sData = sData.Right(sData.GetLength() - pos - 1);
	}
} 