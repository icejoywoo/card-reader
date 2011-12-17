//////////////////////////////////////////////////////////////////////////
// FileName: SplitStr.h
// Creator: icejoywoo
// Date: 2011.12.2
// $Revision$
// $LastChangedDate$
// Comment: �ָ�CString�ַ�������
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
	//�зֵı�־����
	CString m_sSplitFlag;
	//�������зֵı�־���ŵ���һ����־����
	BOOL m_bSequenceAsOne;
	//���зֵ��ı�
	CString m_sData;
public:
	//�õ��зֺõ��ı���
	void GetSplitStrArray(vector<CString> &array);
	//�õ����зֵ��ı�
	CString GetData();
	//���ñ��зֵ��ı�
	void SetData(CString sData);
	//�õ��зֲ���
	BOOL GetSequenceAsOne() {return m_bSequenceAsOne;};
	//�����зֲ���
	void SetSequenceAsOne(BOOL bSequenceAsOne) {m_bSequenceAsOne = bSequenceAsOne;};
	//�õ��зֱ�־
	CString GetSplitFlag() {return m_sSplitFlag;};
	//�����зֱ�־
	void SetSplitFlag(CString sSplitFlag) {m_sSplitFlag = sSplitFlag;};

	CSplitStr();
	virtual ~CSplitStr();
};

#endif