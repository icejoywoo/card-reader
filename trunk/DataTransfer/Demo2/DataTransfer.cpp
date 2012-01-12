#include "StdAfx.h"
#include "DataTransfer.h"
#include <direct.h>

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

TransferRule::~TransferRule()
{
}

void TransferRule::SetStart(DataType startType, char* startData)
{
	this->startType = startType;
	this->startData = startData;
}

void TransferRule::SetEnd(DataType endType, char* endData)
{
	this->endType = endType;
	this->endData = endData;
}

void TransferRule::SetTarget(CString target)
{
	this->target = target;
}

void TransferRule::SetTag(char* tag)
{
	this->tag = tag;
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
	char sql[128];
	// 删除同名表, 然后建表
	// 	this->startType,this->startData,this->endType,this->endData,this->tag
	sprintf(sql, "INSERT INTO %s VALUES(%d, '%s', %d, '%s', '%s')", name, this->startType, this->startData, this->endType, this->endData, this->tag);
	sqlite3_exec(db, sql, NULL, 0, &errMsg);
}

void TransferRule::load(sqlite3* db, const char* name)
{
// 	char* errMsg = 0;
// 	char sql[128];
// 	// 删除同名表, 然后建表
// 	// 	this->startType,this->startData,this->endType,this->endData,this->tag
// 	sprintf(sql, "select startType, startData, endType, endData, tag from %s", name);
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

DataTransfer::DataTransfer()
{
	if (sqlite3_open("data.db", &db) != SQLITE_OK)
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

void DataTransfer::HandleFile(const char* filename, const char* dirname /* = NULL*/)
{
	try
	{
		CStdioFile file(filename, CFile::modeRead);
		
		// 输出文件名
		char outFilename[128];
		if (dirname != NULL)
		{
			_mkdir(dirname);
			CString file(filename); 
			sprintf(outFilename, "%s\\%s", dirname, file.Mid(file.ReverseFind('\\')));
		}
		else
		{
			sprintf(outFilename, "%s_HDP5000", filename);
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
				char outSplitFilename[128];
				sprintf(outSplitFilename, "%s_%03d", outFilename, fileNo);
				
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

			result.Format("%06d [ROW]%s", lineNo, temp);
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

void DataTransfer::HandleDir(const char* dirname)
{
	try
	{
		CFileFind finder;
		CString filePattern;
		filePattern.Format("%s\\*.*", dirname); // 搜寻目录下所有文件
		BOOL working = finder.FindFile(_T(filePattern));
		
		CString targetFile;

		CString outDir; // 输出文件夹
		outDir.Format("%s_HDP5000", dirname);
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

void DataTransfer::Handle(const char* filename)
{
	CFileFind finder;
	BOOL working = finder.FindFile(filename);
	if (working)
	{
		working = finder.FindNextFile();
		if (finder.IsDirectory())
		{
			HandleDir(filename);
		}
		else
		{
			HandleFile(filename);
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
	char* sql = "drop table config;create table config (id integer not null, name text, primary key('id' ASC), CONSTRAINT 'name_unique' UNIQUE ('name'));";
	sqlite3_exec(db, sql, NULL, 0, &errMsg);
}

void DataTransfer::save(const char* name)
{
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

	char sql[128];
	// 删除同名表, 然后建表
	// 	this->startType,this->startData,this->endType,this->endData,this->tag
	sprintf(sql, "INSERT INTO config VALUES(%d, '%s');", id, name);
	sqlite3_exec(db, sql, NULL, 0, &errMsg);

	sprintf(sql, "CREATE TABLE %s (startType integer, startData text, endType integer, endData text, tag text);", name, name);
	sqlite3_exec(db, sql, NULL, 0, &errMsg);

	for (vector<TransferRule>::iterator iter = rules.begin();
		iter != rules.end(); ++iter)
	{
		iter->save(db, name);
	}
}

void DataTransfer::load(const char* name)
{
	char* errMsg = 0;
	int n; // rows
	int m; // columns
	char** result;
	char sql[128];
	sprintf(sql, "SELECT name FROM config WHERE name = '%s';", name);
	sqlite3_get_table(db, sql, &result, &n, &m, &errMsg);
	
	if (n == 1 && strcmp(result[1], name) == 0)
	{
		char* errMsg = 0;
		char sql[128];
		// 删除同名表, 然后建表
		// 	this->startType,this->startData,this->endType,this->endData,this->tag
		sprintf(sql, "select startType, startData, endType, endData, tag from %s", name);
		int n; // rows
		int m; // columns
		char** result;
		sqlite3_get_table(db, sql, &result, &n, &m, &errMsg); //(N+1)*M
		int i;
		cout << n << ", " << m << endl;
		for (i = 1; i <= n; ++i)
		{
			TransferRule rule;
			rule.SetStart((DataType)atoi(result[i*m + 0]), result[i*m + 1]);
			rule.SetEnd((DataType)atoi(result[i*m + 2]), result[i*m + 3]);
			rule.SetTag(result[i*m + 4]);
			this->AddRule(rule);
		}
	}
	else
	{
		AfxMessageBox("所加载的配置不存在!");
	}
}

void DataTransfer::del(const char* name)
{
	char* errMsg = 0;
	int n; // rows
	int m; // columns
	char** result;
	char sql[128];
	sprintf(sql, "SELECT name FROM config WHERE name = '%s';", name);
	sqlite3_get_table(db, sql, &result, &n, &m, &errMsg);
	
	if (n == 1 && strcmp(result[1], name) == 0)
	{
		sprintf(sql, "DELETE FROM config WHERE name = '%s';", name);
		sqlite3_exec(db, sql, NULL, NULL, &errMsg);

		sprintf(sql, "DROP TABLE %s;", name);
		sqlite3_exec(db, sql, NULL, NULL, &errMsg);
	}
	else
	{
		AfxMessageBox("所删除的配置不存在!");
	}
}