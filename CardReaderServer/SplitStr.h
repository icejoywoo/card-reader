//////////////////////////////////////////////////////////////////////////
// FileName: SplitStr.h
// Creator: icejoywoo
// Date: 2011.12.2
// $Revision$
// $LastChangedDate$
// Comment: 分割CString字符串的类
//////////////////////////////////////////////////////////////////////////
#ifndef _SPLIT_STR_H_
#define _SPLIT_STR_H_

#include <afx.h>
#include <windows.h>
#include <vector>

using namespace std;

class CSplitStr
{
private:
	//切分的标志符号
	CString m_sSplitFlag;
	//连续的切分的标志符号当成一个标志处理
	BOOL m_bSequenceAsOne;
	//被切分的文本
	CString m_sData;
public:
	//得到切分好的文本串
	void GetSplitStrArray(vector<CString> &array);
	//得到被切分的文本
	CString GetData();
	//设置被切分的文本
	void SetData(CString sData);
	//得到切分参数
	BOOL GetSequenceAsOne() {return m_bSequenceAsOne;};
	//设置切分参数
	void SetSequenceAsOne(BOOL bSequenceAsOne) {m_bSequenceAsOne = bSequenceAsOne;};
	//得到切分标志
	CString GetSplitFlag() {return m_sSplitFlag;};
	//设置切分标志
	void SetSplitFlag(CString sSplitFlag) {m_sSplitFlag = sSplitFlag;};

	CSplitStr();
	virtual ~CSplitStr();
};

#endif