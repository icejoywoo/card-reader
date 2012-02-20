#ifndef _DATA_TRANSFER_H_
#define _DATA_TRANSFER_H_

#include <vector>
#include <exception>

using namespace std;

// ��������λ����Ϣ, һ����λ��, һ���Ǳ�ǩ
typedef enum _DataType
{
	POSITION_TYPE = 0,
	TAG_TYPE = 1,
} DataType;

//  ����ָ��ַ�������Ϣ, ת�����ݵĹ���
class TransferRule
{
public:
	TransferRule();
	// copy constructor
	TransferRule(const TransferRule& rule);
	virtual ~TransferRule();

	void SetStart(int startPosition);
	void SetStart(char* startTag);

	void SetEnd(int endPosition);
	void SetEnd(char* endTag);
	
	void SetLength(int length);
	void SetTag(char* tag);

	void SetPrefix(char* prefix);
	void SetSuffix(char* suffix);

	CString Handle(CString target);
	// operator overload
	TransferRule& operator=(const TransferRule &rgt);
private:
	void SetTarget(CString target);
	// ��ȡƥ��ĳ���
	int GetLength();
	// ��ȡƥ��Ŀ�ʼλ��
	int GetStart();
	
	CString tag;
	CString target;

	DataType startType;
	int startPosition;
	CString startTag;

	DataType endType;
	int endPosition;
	CString endTag;

	CString prefix;
	CString suffix;
	
	int length;
};

class DataTransfer
{
public:
	DataTransfer();
	virtual ~DataTransfer();

	// �����ļ����ļ��е�����, filename��·��
	void Handle(const char* filename);

	// �����ļ�����
	void HandleFile(const char* filename);
	
	// �����ļ�������
	void HandleDir(const char* filename);

	void AddRule(TransferRule& rule); 
	
	// ��������
	void save();  
	// ��������
	void load();
private:
	// ת������
	vector<TransferRule> rules;
};

#endif