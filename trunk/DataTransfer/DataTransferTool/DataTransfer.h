#ifndef _DATA_TRANSFER_H_
#define _DATA_TRANSFER_H_

#include <vector>
#include <exception>
#include "sqlite3.h"

using namespace std;

// ��������λ����Ϣ, һ����λ��, һ���Ǳ�ǩ
typedef enum _DataType
{
	POSITION_TYPE = 0, // λ��, int
	TAG_TYPE = 1, // ���, string
	LENGTH_TYPE = 2, // (ֻ�н���λ����)����, int
	UNDEFINED = 3,
} DataType;

//  ����ָ��ַ�������Ϣ, ת�����ݵĹ���
class TransferRule
{
public:
	TransferRule();
	// copy constructor
	TransferRule(const TransferRule& rule);
	virtual ~TransferRule();
	
	// ���ÿ�ʼ���ͺ�����
	void SetStart(DataType startType, char* startData);
	DataType GetStartType();
	CString GetStartData();
	
	// ���ý������ͺ�����
	void SetEnd(DataType endType, char* endData);
	DataType GetEndType();
	CString GetEndData();
	
	// ���ñ�ǩ��
	void SetTag(char* tag);
	CString GetTag();

	// ��������, �����ش�����
	CString Handle(CString target);

	// operator= overload
	TransferRule& operator=(const TransferRule &rgt);

	// ��������
	void save(sqlite3* db, const char* name);
	// ��������
	void load(sqlite3* db, const char* name);
private:
	// ���ô��������(�ڻ�ȡ���ȺͿ�ʼλ��֮ǰ����)
	void SetTarget(CString target);
	// ��ȡƥ��ĳ���
	int GetLength();
	// ��ȡƥ��Ŀ�ʼλ��
	int GetStart();
	
	CString tag; // ��ǩ��
	CString target; // ������Ŀ��

	DataType startType; // ��ʼ��������
	CString startData; // ��ʼ����

	DataType endType; // ������������
	CString endData; // ��������
};

class DataTransfer
{
public:
	DataTransfer();
	DataTransfer(CString dbfile);
	virtual ~DataTransfer();

	// �����ļ����ļ��е�����, filename��·��(�Ƽ�ʹ��)
	void Handle(const char* filename);

	// ��Ӵ������
	void AddRule(TransferRule& rule); 
	
	// ��ʼ�����ݿ�
	void init();
	// ��������
	void save(const char* name);
	// ��������
	void load(const char* name);
	// ɾ������
	void del(const char* name);
	// ��ȡ��������
	vector<CString> getConfigs();
private:
	// �����ļ�����
	void HandleFile(const char* filename, const char* dirname = NULL);
	
	// �����ļ�������
	void HandleDir(const char* filename);
	// ת������
	vector<TransferRule> rules;
	// ����sqlite3���ݿ�
	sqlite3* db;

	static CString DBFILE;
};

#endif