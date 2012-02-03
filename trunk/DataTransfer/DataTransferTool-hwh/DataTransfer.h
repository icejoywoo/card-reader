#ifndef _DATA_TRANSFER_H_
#define _DATA_TRANSFER_H_
#include <vector>
#include <exception>
#include "sqlite3.h"
using namespace std;
// 定义两种位置信息, 一种是位置, 一种是标签
typedef enum _DataType
{
	POSITION_TYPE = 0, // 位置, int
	TAG_TYPE = 1, // 标记, string
	LENGTH_TYPE = 2, // (只有结束位可用)长度, int
	UNDEFINED = 3,
} DataType;

//  保存分割字符串的信息, 转换数据的规则
class TransferRule
{
public:
	TransferRule();
	// copy constructor
	TransferRule(const TransferRule& rule);
	virtual ~TransferRule();
	
	// 设置开始类型和数据
	void SetStart(DataType startType, CString startData);
	void SetStart(CString startType, CString startData);
	CString GetStartType();
	CString GetStartData();
	
	// 设置结束类型和数据
	void SetEnd(DataType endType, CString endData);
	void SetEnd(CString endType, CString endData);
	CString GetEndType();
	CString GetEndData();

	// 设置标签名
	void SetTag(CString tag);
	CString GetTag();

	// 处理数据, 并返回处理结果
	CString Handle(CString target);

	// operator= overload
	TransferRule& operator=(const TransferRule &rgt);
	bool operator==(const TransferRule &rgt);

	// 保存配置
	void save(sqlite3* db, const char* name);
	// 加载配置
	void load(sqlite3* db, const char* name);
private:
	// 获取对应字符串的类型, 对应DataType
	DataType getType(CString type);
	// 设置待处理对象(在获取长度和开始位置之前调用)
	void SetTarget(CString target);
	// 获取匹配的长度
	int GetLength();
	// 获取匹配的开始位置
	int GetStart();
	
	CString tag; // 标签名
	CString target; // 待处理目标

	DataType startType; // 起始数据类型
	CString startData; // 起始数据

	DataType endType; // 结束数据类型
	CString endData; // 结束数据
};

class DataTransfer
{
public:
	DataTransfer();
	DataTransfer(CString dbfile);
	virtual ~DataTransfer();
	// 处理文件或文件夹的数据, filename是路径(推荐使用)
	void Handle(const char* filename);
	// 添加处理规则
	void AddRule(TransferRule& rule); 
	// 删除处理规则
	void DelRule(TransferRule& rule);
	// 清空规则
	void ClearRules();
	// 初始化数据库
	void init();
	// 保存配置
	void save(const char* name);
	// 加载配置
	void load(const char* name);
	CString getCurrentTemplate();
	// 删除配置
	void del(const char* name);
	// 获取所有配置
	vector<CString> getConfigs();
	// 获取所有规则
	vector<TransferRule> getRules();
private:
	// 处理文件数据
	void HandleFile(const char* filename, const char* dirname = NULL);	
	// 处理文件夹数据
	void HandleDir(const char* filename);
	// 转换规则
	vector<TransferRule> rules;
	// 操作sqlite3数据库
	sqlite3* db;
	CString currentTemplate;
	static CString DBFILE;
};

#endif