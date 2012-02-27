#include "StdAfx.h"
#include "DataTransfer.h"
#include "Utils.h"
#include <direct.h>
#include <algorithm>
#include "DataTransferToolDlg.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////
// TransferRule
//////////////////////////////////////////////////////////////////////////

TransferRule::TransferRule()
{
	this->startType = UNDEFINED;
	this->endType = UNDEFINED;
}

TransferRule::TransferRule(const TransferRule& rule)
	: startType(rule.startType),
	startData(rule.startData),
	endType(rule.endType),
	endData(rule.endData),
//	target(rule.target), // 复制时, 只需要规则信息, 不需要复制待处理目标
	tag(rule.tag)
{
}

TransferRule& TransferRule::operator=(const TransferRule &rgt)
{
	this->startType = rgt.startType;
	this->startData = rgt.startData;
	this->endType = rgt.endType;
	this->endData = rgt.endData;
	this->tag = rgt.tag;
//	this->target = rgt.target;
	
	return *this;
}

bool TransferRule::operator==(const TransferRule &rgt)
{
	if (this->startType == rgt.startType && 
		this->startData == rgt.startData && 
		this->endType == rgt.endType && 
		this->endData == rgt.endData && 
		this->tag == rgt.tag)
	{
		return true;
	}
	else
	{
		return false;
	}
}

TransferRule::~TransferRule()
{
}

void TransferRule::SetStart(DataType startType, CString startData)
{
	this->startType = startType;
	this->startData = startData;
}

void TransferRule::SetStart(CString startType, CString startData)
{
	this->SetStart(this->getType(startType), startData);
}

void TransferRule::SetEnd(DataType endType, CString endData)
{
	this->endType = endType;
	this->endData = endData;
}

void TransferRule::SetEnd(CString endType, CString endData)
{
	this->SetEnd(this->getType(endType), endData);
}

void TransferRule::SetTarget(CString target)
{
	this->target = target;
}

void TransferRule::SetTag(CString tag)
{
	this->tag = tag;
}

// POSITION_TYPE = 0, // 位置, int
// TAG_TYPE = 1, // 标记, string
// LENGTH_TYPE = 2, // (只有结束位可用)长度, int
// UNDEFINED = 3,
CString TransferRule::GetStartType()
{
	switch (this->startType)
	{
	case 0:
		return "POSITION";
	case 1:
		return "TAG";
	default:
		return "UNDEFINED";
	}
}

CString TransferRule::GetEndType()
{
	switch (this->endType)
	{
	case 0:
		return "POSITION";
	case 1:
		return "TAG";
	case 2:
		return "LENGTH";
	default:
		return "UNDEFINED";
	};
}

DataType TransferRule::getType(CString type)
{
	if (type == "POSITION")
	{
		return POSITION_TYPE;
	} 
	else if (type == "TAG")
	{
		return TAG_TYPE;
	}
	else if (type == "LENGTH")
	{
		return LENGTH_TYPE;
	}
	else
	{
		return UNDEFINED;
	}
}

CString TransferRule::GetStartData()
{
	return this->startData;
}

CString TransferRule::GetEndData()
{
	return this->endData;
}

CString TransferRule::GetTag()
{
	return this->tag;
}

int TransferRule::GetStart()
{
	// 处理startData
	if (this->startType == POSITION_TYPE)
	{
		int position = atoi(this->startData.GetBuffer(this->startData.GetLength() + 1));
		return position;
	} 
	else if (this->startType == TAG_TYPE)
	{
		int start = this->target.Find(this->startData);
		return start + strlen(this->startData);
	} else {
		return 0;
	}
}

int TransferRule::GetLength()
{
	// 处理endData
	int startPosition = this->GetStart();
	if (this->endType == POSITION_TYPE)
	{
		int endPosition = atoi(this->endData.GetBuffer(this->endData.GetLength() + 1));
		return endPosition - startPosition;
	} 
	else if (this->endType == TAG_TYPE)
	{
		int endPosition = this->target.Find(this->endData);
		return endPosition - startPosition;
	}
	else if (this->endType == LENGTH_TYPE)
	{
		return atoi(this->endData.GetBuffer(this->endData.GetLength() + 1));
	}
	else
	{
		return this->target.GetLength() - startPosition;
	}
}

CString TransferRule::Handle(CString target)
{
	this->SetTarget(target);
	CString result; 
	if (this->startData.IsEmpty() && this->endData.IsEmpty()) // 默认为空
	{
		result.Format("<%s>%s</%s>", this->tag, target.Mid(0, 0), this->tag);
	}
	else 
	{
		result.Format("<%s>%s</%s>", this->tag, target.Mid(this->GetStart(), this->GetLength()), this->tag);
	}
	return result;
}


void TransferRule::save(sqlite3* db, const char* name)
{
	char* errMsg = 0;
	char sql[1024];
	// 删除同名表, 然后建表
	// 	this->startType,this->startData,this->endType,this->endData,this->tag
	sprintf(sql, "INSERT INTO '%s' VALUES(%d, '%s', %d, '%s', '%s')", name, this->startType, this->startData, this->endType, this->endData, this->tag);
	sqlite3_exec(db, sql, NULL, 0, &errMsg);
}

void TransferRule::load(sqlite3* db, const char* name)
{
// 	char* errMsg = 0;
// 	char sql[128];
// 	// 删除同名表, 然后建表
// 	// 	this->startType,this->startData,this->endType,this->endData,this->tag
// 	sprintf(sql, "select startType, startData, endType, endData, tag from '%s'", name);
// 	int n; // rows
// 	int m; // columns
// 	char** result;
// 	sqlite3_get_table(db, sql, &result, &n, &m, &errMsg); //(N+1)*M
// 	int i;
// 	for (i = 0; i < n; ++i)
// 	{
// 		this->startType = atoi(result[i*m + 0]);
// 		this->startData = result[i*m + 1];
// 		this->endType = result[i*m + 2];
// 		this->endData = result[i*m + 3];
// 		this->tag = result[i*m + 4];
// 	}
}

//////////////////////////////////////////////////////////////////////////
// DataTransfer
//////////////////////////////////////////////////////////////////////////
CString DataTransfer::DBFILE = "data.db";
DataTransfer::DataTransfer()
{
	// 获取应用程序下面的data.db
	CString m_FilePath;
	GetModuleFileName(NULL,m_FilePath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	m_FilePath.ReleaseBuffer();
	int m_iPosIndex;
	m_iPosIndex = m_FilePath.ReverseFind('\\'); 
	CString currentPath = m_FilePath.Left(m_iPosIndex);

	CString dbfile;
	dbfile.Format("%s\\data.db", currentPath);
	CFileStatus status;
	if (!CFile::GetStatus(dbfile, status))
	{
		if (sqlite3_open(Convert(dbfile, CP_ACP, CP_UTF8), &db) != SQLITE_OK)
		{
			AfxMessageBox("数据库初始化失败!");
		}
		this->init();
	}
	else
	{
		if (sqlite3_open(Convert(dbfile, CP_ACP, CP_UTF8), &db) != SQLITE_OK)
		{
			AfxMessageBox("数据库初始化失败!");
		}
	}
	
}

DataTransfer::DataTransfer(CString dbfile)
{
	if (sqlite3_open(dbfile, &db) != SQLITE_OK)
	{
		AfxMessageBox("数据库初始化失败!");
	}
}

DataTransfer::~DataTransfer()
{
	rules.clear();
	sqlite3_close(db);
}

void DataTransfer::AddRule(TransferRule& rule)
{
	TransferRule _rule(rule);
	this->rules.push_back(_rule);
}

void DataTransfer::AddRule(TransferRule& rule, vector<TransferRule>::iterator loc)
{
	TransferRule _rule(rule);
	this->rules.insert(loc, 1, _rule);
}

void DataTransfer::AddRule(TransferRule& rule, int loc)
{
	TransferRule _rule(rule);
	int i = 0;
	if (loc < 0)
	{
		AfxMessageBox("插入位置不可以是负数!");
	}
	
	for (vector<TransferRule>::iterator iter = rules.begin(); 
		iter != rules.end(); ++iter, ++i)
	{
		if (i == loc)
		{
			this->AddRule(_rule, iter);
			return;
		}
	}
	this->AddRule(_rule);
}

vector<TransferRule>::iterator DataTransfer::DelRule(TransferRule& rule)
{
	// 删除指定元素
//	remove(rules.begin(), rules.end(), rule); 
	vector<TransferRule>::iterator result;
	for (vector<TransferRule>::iterator iter = rules.begin();
		iter != rules.end(); ++iter)
	{
		if ((*iter) == rule)
		{
			result = rules.erase(iter);
			break;
		}
	}
	return result;
}

void DataTransfer::ClearRules()
{
	rules.clear();
}

void DataTransfer::HandleFile(const char* filename, const char* dirname /* = NULL*/)
{
	try
	{
		CStdioFile file(filename, CFile::modeRead);
		
		// 获取当前时间戳
		CTime t = CTime::GetCurrentTime();
		CString timestamp;
		timestamp.Format("%d%02d%02d%02d%02d%02d", t.GetYear(), t.GetMonth(), t.GetDay(), t.GetHour(), t.GetMinute(), t.GetSecond());

		// 输出文件名
		CString outFilename;
		if (dirname != NULL)
		{
			_mkdir(dirname);
			CString file(filename); 
			outFilename.Format("%s\\%s", dirname, file.Mid(file.ReverseFind('\\')));
		}
		else
		{
			outFilename.Format("%s_HDP5000_%s", filename, timestamp);
		}

		CStdioFile* outFile = new CStdioFile(outFilename, CFile::modeCreate | CFile::modeWrite);
		CString line;
		int lineNo = 0; // 行号
		int fileNo = 0; // 文件超过10000行, 会被分割

		while (file.ReadString(line))
		{
			++lineNo;
			if (lineNo > 10000) // 文本超过10000行, 文件名+fileNo
			{
				++fileNo;
				outFile->Close();
				CString outSplitFilename;
				outSplitFilename.Format("%s_%03d", outFilename, fileNo);
				CFile* temp = outFile;
				outFile = new CStdioFile(outSplitFilename, CFile::modeCreate | CFile::modeWrite);
				delete temp;

				lineNo = 1;
			}
			CString result;
			CString temp;
			

			for (vector<TransferRule>::iterator iter = rules.begin();
				iter != rules.end(); ++iter)
			{
				temp += iter->Handle(line);
			}

			result.Format("%06d [ROW]%s[ENDROW]", lineNo, temp);
			outFile->WriteString(result + "\n");
		}
		file.Close();
		outFile->Close();
		delete outFile;
	}
	catch (CFileException* e)
	{
		AfxMessageBox(_T("文件打开错误, 文件不存在!"));
	}
}

void DataTransfer::HandleDir(const char* dirname, const char* outputDir /*= NULL*/)
{
	try
	{
		CFileFind finder;
		CString filePattern;
		filePattern.Format("%s\\*.*", dirname); // 搜寻目录下所有文件
		BOOL working = finder.FindFile(_T(filePattern));
		
		CString targetFile;
		// 获取当前时间戳
		CTime t = CTime::GetCurrentTime();
		CString timestamp;
		timestamp.Format("%d%02d%02d%02d%02d%02d", t.GetYear(), t.GetMonth(), t.GetDay(), t.GetHour(), t.GetMinute(), t.GetSecond());
		
		CString outDir; // 输出文件夹
		if (outputDir == NULL)
		{
			outDir.Format("%s_HDP5000_%s", dirname, timestamp);
		}
		else
		{
			// dirname.Mid(dirname.ReverseFind('\\'))
			CString temp(dirname);
			outDir.Format("%s\\%s_HDP5000_%s", outputDir, temp.Mid(temp.ReverseFind('\\')), timestamp);
			TRACE(outDir);
		}
		
		CString outFile;

		while (working)
		{
			working = finder.FindNextFile();
			if (!finder.IsDirectory()) // 处理文件
			{
				targetFile.Format("%s\\%s", dirname, finder.GetFileName());
				HandleFile(targetFile, outDir);
			}
		}

		finder.Close();
	}
	catch (CFileException* e)
	{
		AfxMessageBox(_T("文件夹打开错误, 文件夹不存在!"));
	}
}

void DataTransfer::Handle(const char* filename, const char* outputDir /*= NULL*/)
{
	CFileFind finder;
	BOOL working = finder.FindFile(filename);
	if (working)
	{
		working = finder.FindNextFile();
		if (finder.IsDirectory())
		{
			HandleDir(filename, outputDir);
		}
		else
		{
			HandleFile(filename, outputDir);
		}
	}
	else
	{
		AfxMessageBox("所给文件名有错, 无法打开!");
	}
}

void DataTransfer::init()
{
	char* errMsg = 0;
	char* sql = "create table config (id integer not null, name text, comment text, inputPath text, outputPath text, primary key('id' ASC), CONSTRAINT 'name_unique' UNIQUE ('name'));";
	sqlite3_exec(db, sql, NULL, 0, &errMsg);
}

void DataTransfer::save(const char* name, const char* comment /* = "" */)
{
	CString utf8Name = Convert(name, CP_ACP, CP_UTF8);
	CString utf8Comment = Convert(comment, CP_ACP, CP_UTF8);
	CString utf8InputPath = Convert(this->inputPath, CP_ACP, CP_UTF8);
	CString utf8OutputPath = Convert(this->outputPath, CP_ACP, CP_UTF8);

	char* errMsg = 0;
	int id = 1;

	int n = 0; // rows
	int m = 0; // columns
	char** result;
	sqlite3_get_table(db, "SELECT max(id) FROM config;", &result, &n, &m, &errMsg); //(N+1)*M
	if (result[1] != NULL)
	{
		id = atoi(result[1]) + 1;
	}

	CString sql;
	sql.Format("SELECT name FROM config WHERE name = '%s';", utf8Name);
	sqlite3_get_table(db, sql, &result, &n, &m, &errMsg);
	
	if (n == 1 && strcmp(result[1], utf8Name) == 0) // 模板已经存在
	{
		sql.Format("UPDATE config SET comment = '%s' WHERE name = '%s';", utf8Comment, utf8Name);
		sqlite3_exec(db, sql, NULL, 0, &errMsg);
		sql.Format("UPDATE config SET inputPath = '%s' WHERE name = '%s';", utf8InputPath, utf8Name);
		sqlite3_exec(db, sql, NULL, 0, &errMsg);
		sql.Format("UPDATE config SET outputPath = '%s' WHERE name = '%s';", utf8OutputPath, utf8Name);
		sqlite3_exec(db, sql, NULL, 0, &errMsg);
	}
	else // 新建模板
	{
		sql.Format("INSERT INTO config VALUES(%d, '%s', '%s', '%s', '%s');", id, utf8Name, utf8Comment, utf8InputPath, utf8OutputPath);
		sqlite3_exec(db, sql, NULL, 0, &errMsg);
	}


	// TODO: 删除同名表, 然后建表
	sql.Format("DROP TABLE '%s';", utf8Name);
	sqlite3_exec(db, sql, NULL, 0, &errMsg);

	sql.Format("CREATE TABLE '%s' (startType integer, startData text, endType integer, endData text, tag text);", utf8Name, utf8Name);
	sqlite3_exec(db, sql, NULL, 0, &errMsg);

	for (vector<TransferRule>::iterator iter = rules.begin();
		iter != rules.end(); ++iter)
	{
		iter->save(db, utf8Name);
	}
}

void DataTransfer::load(const char* name)
{
	CString utf8Name = Convert(name, CP_ACP, CP_UTF8);
	char* errMsg = 0;
	int n; // rows
	int m; // columns
	char** result;
	char sql[1024];
	sprintf(sql, "SELECT name FROM config WHERE name = '%s';", utf8Name);
	sqlite3_get_table(db, sql, &result, &n, &m, &errMsg);

	if (n == 1 && strcmp(result[1], utf8Name) == 0)
	{
		sprintf(sql, "SELECT comment, inputPath, outputPath FROM config WHERE name = '%s';", utf8Name);
		sqlite3_get_table(db, sql, &result, &n, &m, &errMsg);
		this->templateComment = Convert(result[m + 0], CP_UTF8, CP_ACP);
		this->inputPath = Convert(result[m + 1], CP_UTF8, CP_ACP);
		this->outputPath = Convert(result[m + 2], CP_UTF8, CP_ACP);

		char* errMsg = 0;
		char sql[1024];
		
		sprintf(sql, "select startType, startData, endType, endData, tag from '%s'", utf8Name);
		int n; // rows
		int m; // columns
		char** result;
		this->rules.clear();
		sqlite3_get_table(db, sql, &result, &n, &m, &errMsg); //(N+1)*M
		int i;
		for (i = 1; i <= n; ++i)
		{
			TransferRule rule;
			rule.SetStart((DataType)atoi(result[i*m + 0]), result[i*m + 1]);
			rule.SetEnd((DataType)atoi(result[i*m + 2]), result[i*m + 3]);
			rule.SetTag(result[i*m + 4]);
			this->AddRule(rule);
		}
		currentTemplate = name;
	}
	else
	{
		AfxMessageBox("所加载的配置不存在!");
	}
}

void DataTransfer::del(const char* name)
{
	CString utf8Name = Convert(name, CP_ACP, CP_UTF8);
	char* errMsg = 0;
	int n; // rows
	int m; // columns
	char** result;
	char sql[1024];
	sprintf(sql, "SELECT name FROM config WHERE name = '%s';", utf8Name);
	sqlite3_get_table(db, sql, &result, &n, &m, &errMsg);
	
	if (n == 1 && strcmp(result[1], utf8Name) == 0)
	{
		sprintf(sql, "DELETE FROM config WHERE name = '%s';", utf8Name);
		sqlite3_exec(db, sql, NULL, NULL, &errMsg);

		sprintf(sql, "DROP TABLE '%s';", utf8Name);
		sqlite3_exec(db, sql, NULL, NULL, &errMsg);
	}
	else
	{
		AfxMessageBox("所删除的配置不存在!");
	}
}

vector<CString> DataTransfer::getConfigs()
{
	vector<CString> configs;
	char* errMsg = 0;
	int n; // rows
	int m; // columns
	char** result;
	char sql[1024];
	sprintf(sql, "SELECT name FROM config");
	sqlite3_get_table(db, sql, &result, &n, &m, &errMsg);	
	for (int i = 1; i <= n; ++i)
	{
		configs.push_back(result[i*m + 0]);
	}
	return configs;
}

vector<TransferRule> DataTransfer::getRules()
{
	return this->rules;
}

CString DataTransfer::getTemplateComment()
{
	return this->templateComment;
}