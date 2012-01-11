#ifndef _DATA_TRANSFER_H_
#define _DATA_TRANSFER_H_

#include <vector>
#include <exception>

using namespace std;

// 定义两种位置信息, 一种是位置, 一种是标签
typedef enum _DataType
{
	POSITION_TYPE = 0,
	TAG_TYPE = 1,
} DataType;

//  保存分割字符串的信息, 转换数据的规则
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
	// 获取匹配的长度
	int GetLength();
	// 获取匹配的开始位置
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

	// 处理文件或文件夹的数据, filename是路径
	void Handle(const char* filename);

	// 处理文件数据
	void HandleFile(const char* filename);
	
	// 处理文件夹数据
	void HandleDir(const char* filename);

	void AddRule(TransferRule& rule); 
	
	// 保存配置
	void save();  
	// 加载配置
	void load();
private:
	// 转换规则
	vector<TransferRule> rules;
};

#endif