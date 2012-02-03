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
	void SetStart(DataType startType, CString startData);
	void SetStart(CString startType, CString startData);
	CString GetStartType();
	CString GetStartData();
	
	// ���ý������ͺ�����
	void SetEnd(DataType endType, CString endData);
	void SetEnd(CString endType, CString endData);
	CString GetEndType();
	CString GetEndData();

	// ���ñ�ǩ��
	void SetTag(CString tag);
	CString GetTag();

	// ��������, �����ش�����
	CString Handle(CString target);

	// operator= overload
	TransferRule& operator=(const TransferRule &rgt);
	bool operator==(const TransferRule &rgt);

	// ��������
	void save(sqlite3* db, const char* name);
	// ��������
	void load(sqlite3* db, const char* name);
private:
	// ��ȡ��Ӧ�ַ���������, ��ӦDataType
	DataType getType(CString type);
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
	// ɾ���������
	void DelRule(TransferRule& rule);
	// ��չ���
	void ClearRules();
	// ��ʼ�����ݿ�
	void init();
	// ��������
	void save(const char* name);
	// ��������
	void load(const char* name);
	CString getCurrentTemplate();
	// ɾ������
	void del(const char* name);
	// ��ȡ��������
	vector<CString> getConfigs();
	// ��ȡ���й���
	vector<TransferRule> getRules();
private:
	// �����ļ�����
	void HandleFile(const char* filename, const char* dirname = NULL);	
	// �����ļ�������
	void HandleDir(const char* filename);
	// ת������
	vector<TransferRule> rules;
	// ����sqlite3���ݿ�
	sqlite3* db;
	CString currentTemplate;
	static CString DBFILE;
};

#endif