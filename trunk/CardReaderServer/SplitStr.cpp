//////////////////////////////////////////////////////////////////////////
// FileName: SplitStr.cpp
// Creator: icejoywoo
// Date: 2011.12.2
// $Revision$
// $LastChangedDate$
// Comment: �ָ�CString�ַ��������ʵ��
//////////////////////////////////////////////////////////////////////////

#include "SplitStr.h"
#include <vector>

using namespace std;

//���캯��
CSplitStr::CSplitStr()
{
	SetData("");
	SetSequenceAsOne(TRUE);
	SetSplitFlag(",");
}

CSplitStr::~CSplitStr()
{
}

//�����ı�����
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
//�зֲ����������ܼ�ʵ�ðɣ�
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
			if (!sTemp.IsEmpty() && sTemp !="") ////�����ķָ�����Ϊ��������
			{
				array.push_back(sTemp);
			}
		}
		sData = sData.Right(sData.GetLength() - pos - 1);
	}
} 